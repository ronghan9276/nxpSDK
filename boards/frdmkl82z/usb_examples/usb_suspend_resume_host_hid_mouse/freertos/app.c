/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "usb_host_config.h"
#include "usb_host.h"
#include "fsl_device_registers.h"
#include "usb_host_hid.h"
#include "board.h"
#include "host_mouse.h"
#include "pin_mux.h"
#include "fsl_common.h"
#if (defined(FSL_FEATURE_SOC_SYSMPU_COUNT) && (FSL_FEATURE_SOC_SYSMPU_COUNT > 0U))
#include "fsl_sysmpu.h"
#endif /* FSL_FEATURE_SOC_SYSMPU_COUNT */
#include "app.h"
#include "board.h"

#include "usb_io.h"
#include "usb_timer.h"
#include "fsl_debug_console.h"
#if ((!USB_HOST_CONFIG_KHCI) && (!USB_HOST_CONFIG_EHCI) && (!USB_HOST_CONFIG_OHCI) && (!USB_HOST_CONFIG_IP3516HS))
#error Please enable USB_HOST_CONFIG_KHCI, USB_HOST_CONFIG_EHCI, USB_HOST_CONFIG_OHCI, or USB_HOST_CONFIG_IP3516HS in file usb_host_config.
#endif

#include <stdbool.h>
#include "clock_config.h"
#include "fsl_pit.h"
#include "fsl_port.h"
#include "fsl_smc.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void USB_WaitClockLocked(void);

/*!
 * @brief host callback function.
 *
 * device attach/detach callback function.
 *
 * @param deviceHandle          device handle.
 * @param configurationHandle   attached device's configuration descriptor information.
 * @param eventCode             callback event code, please reference to enumeration host_event_t.
 *
 * @retval kStatus_USB_Success              The host is initialized successfully.
 * @retval kStatus_USB_NotSupported         The application don't support the configuration.
 */
static usb_status_t USB_HostEvent(usb_device_handle deviceHandle,
                                  usb_host_configuration_handle configurationHandle,
                                  uint32_t eventCode);

/*!
 * @brief application initialization.
 */
static void USB_HostApplicationInit(void);

/*!
 * @brief host freertos task function.
 *
 * @param g_HostHandle   host handle
 */
static void USB_HostTask(void *param);

/*!
 * @brief host mouse freertos task function.
 *
 * @param param   the host mouse instance pointer.
 */
static void USB_HostApplicationTask(void *param);

extern void USB_HostClockInit(void);
extern void USB_HostIsrEnable(void);
extern void USB_HostTaskFn(void *param);
void BOARD_InitHardware(void);

status_t DbgConsole_Deinit(void);

void BOARD_InitPins(void);
void BOARD_DeinitPins(void);
void SW_IntControl(uint8_t enable);
char *SW_GetName(void);
void HW_TimerControl(uint8_t enable);
void USB_LowpowerModeInit(void);
void USB_PreLowpowerMode(void);
uint8_t USB_EnterLowpowerMode(void);
void USB_PostLowpowerMode(void);
void USB_ControllerSuspended(void);
void USB_WaitClockLocked(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
extern usb_host_mouse_instance_t g_HostHidMouse;
extern usb_host_handle g_HostHandle;
/*! @brief USB host mouse instance global variable */
extern usb_host_mouse_instance_t g_HostHidMouse;
usb_host_handle g_HostHandle;

#if defined(configUSE_TICKLESS_IDLE) && (configUSE_TICKLESS_IDLE == 1U)
SemaphoreHandle_t s_wakeupSig;
SemaphoreHandle_t s_wakeupSig1;
extern uint8_t s_suspendResumeState;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief De-initialize all pins used in this example
 *
 * @param disablePortClockAfterInit disable port clock after pin
 * initialization or not.
 */
void BOARD_DeinitPins(void)
{
    /* Affects PORTB_PCR16 register */
    PORT_SetPinMux(PORTB, 16u, kPORT_PinDisabledOrAnalog);
    /* Affects PORTB_PCR17 register */
    PORT_SetPinMux(PORTB, 17u, kPORT_PinDisabledOrAnalog);

    /* Gate the port clock */
    CLOCK_DisableClock(kCLOCK_PortB);
}

void LLWU_SW_IRQ_HANDLER(void)
{
    if ((1U << LLWU_SW_GPIO_PIN) & PORT_GetPinsInterruptFlags(LLWU_SW_PORT))
    {
        /* Disable interrupt. */
        PORT_SetPinInterruptConfig(LLWU_SW_PORT, LLWU_SW_GPIO_PIN, kPORT_InterruptOrDMADisabled);
        PORT_ClearPinsInterruptFlags(LLWU_SW_PORT, (1U << LLWU_SW_GPIO_PIN));
        g_HostHidMouse.selfWakeup = 1U;
    }
}

void SW_IntControl(uint8_t enable)
{
    if (enable)
    {
        g_HostHidMouse.selfWakeup = 0U;
        PORT_SetPinInterruptConfig(LLWU_SW_PORT, LLWU_SW_GPIO_PIN, kPORT_InterruptFallingEdge);
    }
    else
    {
        PORT_SetPinInterruptConfig(LLWU_SW_PORT, LLWU_SW_GPIO_PIN, kPORT_InterruptOrDMADisabled);
    }
}

void SW_Callback(void)
{
    g_HostHidMouse.selfWakeup = 1U;
    SW_IntControl(0);
}

void SW_Init(void)
{
    NVIC_SetPriority(LLWU_SW_IRQ, 1U);
    NVIC_EnableIRQ(LLWU_SW_IRQ);
}

char *SW_GetName(void)
{
    return LLWU_SW_NAME;
}

void HW_TimerCallback(void)
{
    g_HostHidMouse.hwTick++;
    USB_HostUpdateHwTick(g_HostHandle, g_HostHidMouse.hwTick);
}

void HW_TimerInit(void)
{
    USB_TimerInit(0, 1000U, CLOCK_GetFreq(kCLOCK_BusClk), HW_TimerCallback);
}

void HW_TimerControl(uint8_t enable)
{
    USB_TimerInt(0, enable);
}

void USB_LowpowerModeInit(void)
{
    /* Set to allow entering vlps mode */
    SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeVlp);
    SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;
    RTC->CR |= RTC_CR_OSCE_MASK;
#if (defined(FSL_FEATURE_SIM_OPT_HAS_USB_PHY) && (FSL_FEATURE_SIM_OPT_HAS_USB_PHY > 0))
    SIM->SOPT2 |= SIM_SOPT2_USBSLSRC_MASK;
#endif
    SW_Init();
    HW_TimerInit();
}

void USB_PreLowpowerMode(void)
{
    SMC_PreEnterStopModes();
}

uint8_t USB_EnterLowpowerMode(void)
{
    /* Enter Deep Sleep mode */
    return SMC_SetPowerModeVlps(SMC);
}

void USB_PostLowpowerMode(void)
{
    USB_WaitClockLocked();
    SMC_PostExitStopModes();
}

void USB_ControllerSuspended(void)
{
}

void USB_WaitClockLocked(void)
{
#if (defined(FSL_FEATURE_SOC_MCG_COUNT) && (FSL_FEATURE_SOC_MCG_COUNT > 0U))
    /* Wait for PLL lock. */
    while (!(kMCG_Pll0LockFlag & CLOCK_GetStatusFlags()))
    {
    }
    CLOCK_SetPeeMode();
#endif
}

void USB0_IRQHandler(void)
{
    USB_HostKhciIsrFunction(g_HostHandle);
}

void USB_HostClockInit(void)
{
    SystemCoreClockUpdate();
    CLOCK_EnableUsbfs0Clock(kCLOCK_UsbSrcPll0, CLOCK_GetFreq(kCLOCK_PllFllSelClk));
}

void USB_HostIsrEnable(void)
{
    uint8_t irqNumber;

    uint8_t usbHOSTKhciIrq[] = USB_IRQS;
    irqNumber = usbHOSTKhciIrq[CONTROLLER_ID - kUSB_ControllerKhci0];

/* Install isr, set priority, and enable IRQ. */
#if defined(__GIC_PRIO_BITS)
    GIC_SetPriority((IRQn_Type)irqNumber, USB_HOST_INTERRUPT_PRIORITY);
#else
    NVIC_SetPriority((IRQn_Type)irqNumber, USB_HOST_INTERRUPT_PRIORITY);
#endif
    EnableIRQ((IRQn_Type)irqNumber);
}

void USB_HostTaskFn(void *param)
{
    USB_HostKhciTaskFunction(param);
}

/*!
 * @brief USB isr function.
 */

static void USB_HostRemoteWarkupCallback(void *param, usb_host_transfer_t *transfer, usb_status_t status)
{
    if (NULL == param)
    {
        return;
    }
    USB_HostFreeTransfer(param, transfer);

    if (kStatus_USB_Success == status)
    {
        if (kStatus_SuspendWaitClearRemoteWakeup == g_HostHidMouse.suspendResumeState)
        {
            usb_echo("Remote wakeup feature cleared.\r\n");
            g_HostHidMouse.isSetRemoteWakeup = 0U;
            g_HostHidMouse.suspendResumeState = kStatus_Suspending;
        }
        else if (kStatus_SuspendWaitSetRemoteWakeup == g_HostHidMouse.suspendResumeState)
        {
            usb_echo("Remote wakeup feature set.\r\n");
            g_HostHidMouse.isSetRemoteWakeup = 1U;
            g_HostHidMouse.suspendResumeState = kStatus_Suspending;
        }
        else
        {
        }
    }
    else
    {
        g_HostHidMouse.suspendResumeState = kStatus_SuspendFailRemoteWakeup;
        usb_echo(
            "\tSend clear remote wakeup feature request failed. \r\nWhether need to continue? "
            "Please ENTER y(es) or n(o): ");
    }
    DbgConsole_Flush();
}

usb_status_t USB_HostControlRemoteWakeup(usb_host_handle hostHandle,
                                         usb_device_handle deviceHandle,
                                         host_inner_transfer_callback_t callbackFn,
                                         void *callbackParam,
                                         uint8_t enable)
{
    usb_host_transfer_t *transfer;
    uint32_t infoValue;

    if (hostHandle == NULL)
    {
        return kStatus_USB_InvalidHandle;
    }

    /* malloc one transfer */
    if (USB_HostMallocTransfer(hostHandle, &transfer) != kStatus_USB_Success)
    {
#ifdef HOST_ECHO
        usb_echo("error to get transfer\r\n");
#endif
        return kStatus_USB_Busy;
    }
    /* initialize transfer */
    transfer->transferBuffer = NULL;
    transfer->transferLength = 0;
    transfer->callbackFn = callbackFn;
    transfer->callbackParam = callbackParam;
    transfer->setupPacket->bmRequestType =
        USB_REQUEST_TYPE_RECIPIENT_DEVICE | USB_REQUEST_TYPE_DIR_OUT | USB_REQUEST_TYPE_TYPE_STANDARD;
    transfer->setupPacket->bRequest = (enable ? USB_REQUEST_STANDARD_SET_FEATURE : USB_REQUEST_STANDARD_CLEAR_FEATURE);
    transfer->setupPacket->wValue =
        USB_SHORT_TO_LITTLE_ENDIAN(USB_REQUEST_STANDARD_FEATURE_SELECTOR_DEVICE_REMOTE_WAKEUP);
    transfer->setupPacket->wIndex = USB_SHORT_TO_LITTLE_ENDIAN(0x00U);
    transfer->setupPacket->wLength = USB_SHORT_TO_LITTLE_ENDIAN(0x00U);

    USB_HostHelperGetPeripheralInformation(deviceHandle, kUSB_HostGetDeviceControlPipe, &infoValue);

    if (USB_HostSendSetup(hostHandle, (usb_host_pipe_handle)infoValue, transfer) !=
        kStatus_USB_Success) /* call host driver api */
    {
#ifdef HOST_ECHO
        usb_echo("failed for USB_HostControlRemoteWakeup\r\n");
#endif
        USB_HostFreeTransfer(hostHandle, transfer);
        return kStatus_USB_Error;
    }
    return kStatus_USB_Success;
}

static usb_status_t USB_HostEvent(usb_device_handle deviceHandle,
                                  usb_host_configuration_handle configurationHandle,
                                  uint32_t eventCode)
{
    usb_status_t status = kStatus_USB_Success;

    switch (eventCode)
    {
        case kUSB_HostEventAttach:
            status = USB_HostHidMouseEvent(deviceHandle, configurationHandle, eventCode);
            break;

        case kUSB_HostEventNotSupported:
            usb_echo("device not supported.\r\n");
            break;

        case kUSB_HostEventEnumerationDone:
            status = USB_HostHidMouseEvent(deviceHandle, configurationHandle, eventCode);
            break;

        case kUSB_HostEventDetach:
            status = USB_HostHidMouseEvent(deviceHandle, configurationHandle, eventCode);
            break;
        case kUSB_HostEventNotSuspended:
            if (kStatus_Idle != g_HostHidMouse.suspendResumeState)
            {
                if (g_HostHidMouse.suspendBus)
                {
                    usb_echo("Suspend BUS failed.\r\n");
                }
                else
                {
                    usb_echo("Suspend device failed.\r\n");
                }
            }
            g_HostHidMouse.suspendResumeState = kStatus_Idle;
            break;
        case kUSB_HostEventSuspended:
            if (kStatus_Idle != g_HostHidMouse.suspendResumeState)
            {
                USB_ControllerSuspended();
                g_HostHidMouse.suspendResumeState = kStatus_Suspended;
            }
            else
            {
                g_HostHidMouse.suspendResumeState = kStatus_Idle;
            }
            break;
        case kUSB_HostEventDetectResume:
            if (kStatus_Idle != g_HostHidMouse.suspendResumeState)
            {
                USB_WaitClockLocked();
            }
            break;
        case kUSB_HostEventResumed:
            if (kStatus_Idle != g_HostHidMouse.suspendResumeState)
            {
                if (g_HostHidMouse.suspendBus)
                {
                    usb_echo("BUS has been resumed.\r\n");
                }
                else
                {
                    usb_echo("Device has been resumed.\r\n");
                }
                DbgConsole_Flush();
            }
            g_HostHidMouse.suspendResumeState = kStatus_Idle;
            break;
        default:
            break;
    }
    return status;
}

static void USB_HostApplicationInit(void)
{
    usb_status_t status = kStatus_USB_Success;

    USB_HostClockInit();

#if ((defined FSL_FEATURE_SOC_SYSMPU_COUNT) && (FSL_FEATURE_SOC_SYSMPU_COUNT))
    SYSMPU_Enable(SYSMPU, 0);
#endif /* FSL_FEATURE_SOC_SYSMPU_COUNT */

    status = USB_HostInit(CONTROLLER_ID, &g_HostHandle, USB_HostEvent);
    if (status != kStatus_USB_Success)
    {
        usb_echo("host init error\r\n");
        return;
    }
    USB_HostIsrEnable();

    usb_echo("host init done\r\n");
}


void USB_PowerPreSwitchHook(void)
{
    HW_TimerControl(0U);

    DbgConsole_Deinit();

    BOARD_DeinitPins();

    USB_PreLowpowerMode();

    vTaskSuspendAll();
}

void USB_PowerPostSwitchHook(void)
{
    USB_WaitClockLocked();
    USB_PostLowpowerMode();
    BOARD_InitPins();
    BOARD_InitDebugConsole();
    HW_TimerControl(1U);
    xTaskResumeAll();
}

void USB_HostSuspendResumeTask(void)
{
    usb_status_t usb_error;
    uint8_t command;

    if (kStatus_USB_Success != DbgConsole_TryGetchar((char *)&command))
    {
        command = 0;
    }
    switch (g_HostHidMouse.suspendResumeState)
    {
        case kStatus_Idle:
            if ('s' == command)
            {
                g_HostHidMouse.suspendResumeState = kStatus_SartSuspend;
                usb_echo("Start suspend USB BUS...\r\n");

            }
            else
            {
                if (command)
                {
                    usb_echo("Please Enter 's' to start suspend test\r\n");
                }
            }
            break;
        case kStatus_SartSuspend:
            g_HostHidMouse.suspendBus = 1;
            if (g_HostHidMouse.supportRemoteWakeup)
            {
                usb_echo(
                    "\r\nPlease Enter: \r\n\t1. Enable remote wakeup feature.\r\n\t2. Disable remote wakeup "
                    "feature.\r\n");
                g_HostHidMouse.suspendResumeState = kStatus_SuspendSetRemoteWakeup;
            }
            else
            {
                g_HostHidMouse.suspendResumeState = kStatus_Suspending;
            }
            break;
        case kStatus_SuspendSetRemoteWakeup:
            if ('1' == command)
            {
                usb_echo("1");
                usb_error = USB_HostControlRemoteWakeup(g_HostHandle, g_HostHidMouse.deviceHandle,
                                                        USB_HostRemoteWarkupCallback, g_HostHandle, 1);
                if (kStatus_USB_Success == usb_error)
                {
                    g_HostHidMouse.suspendResumeState = kStatus_SuspendWaitSetRemoteWakeup;
                }
                else
                {
                    g_HostHidMouse.suspendResumeState = kStatus_SuspendFailRemoteWakeup;
                    usb_echo(
                        "\tSend set remote wakeup feature request failed. \r\nWhether need to continue? "
                        "Please ENTER y(es) or n(o): ");
                }
            }
            else if ('2' == command)
            {
                usb_echo("2");
                usb_error = USB_HostControlRemoteWakeup(g_HostHandle, g_HostHidMouse.deviceHandle,
                                                        USB_HostRemoteWarkupCallback, g_HostHandle, 0);
                if (kStatus_USB_Success == usb_error)
                {
                    g_HostHidMouse.suspendResumeState = kStatus_SuspendWaitClearRemoteWakeup;
                }
                else
                {
                    g_HostHidMouse.suspendResumeState = kStatus_SuspendFailRemoteWakeup;
                    usb_echo(
                        "\tSend clear remote wakeup feature request failed. \r\nWhether need to continue? "
                        "Please ENTER y(es) or n(o): ");
                }
            }
            else
            {
            }
            DbgConsole_Flush();
            break;
        case kStatus_SuspendWaitSetRemoteWakeup:
        case kStatus_SuspendWaitClearRemoteWakeup:
            break;
        case kStatus_SuspendFailRemoteWakeup:
            if ('y' == command)
            {
                usb_echo("y");
                g_HostHidMouse.suspendResumeState = kStatus_Suspending;
            }
            else if ('n' == command)
            {
                usb_echo("n");
                g_HostHidMouse.suspendResumeState = kStatus_Idle;
            }
            else
            {
            }
            break;
        case kStatus_Suspending:
            g_HostHidMouse.suspendResumeState = kStatus_SuspendRequest;
            if (kStatus_USB_Success ==
                USB_HostSuspendDeviceResquest(g_HostHandle,
                                              g_HostHidMouse.suspendBus ? NULL : g_HostHidMouse.deviceHandle))
            {
            }
            else
            {
                usb_echo("Send suspend request failed.\r\n");
                g_HostHidMouse.suspendResumeState = kStatus_Idle;
            }
            break;
        case kStatus_SuspendRequest:
            break;
        case kStatus_Suspended:
            DbgConsole_Flush();
            if (g_HostHidMouse.suspendBus)
            {
                usb_echo("BUS has been suspended.\r\n");
            }
            else
            {
                usb_echo("Device has been suspended.\r\n");
            }
            DbgConsole_Flush();
            usb_echo("Please Press wakeup switch(%s) to start resume test.\r\n", SW_GetName());
            if (g_HostHidMouse.isSetRemoteWakeup)
            {
                usb_echo("Or, wait for device sends resume signal.\r\n");
            }
            /*flush the output befor enter lowpower*/
            DbgConsole_Flush();
            USB_PowerPreSwitchHook();
            SW_IntControl(1);

            g_HostHidMouse.suspendResumeState = kStatus_WaitResume;
#if defined(configUSE_TICKLESS_IDLE) && (configUSE_TICKLESS_IDLE == 1U)
#else
            vTaskSuspendAll();
#endif
            if (kStatus_Success != USB_EnterLowpowerMode())
            {
                g_HostHidMouse.selfWakeup = 1U;
                USB_PowerPostSwitchHook();
                usb_echo("Enter VLPS mode failed!\r\n");
            }
            else
            {
                USB_PowerPostSwitchHook();
            }
#if defined(configUSE_TICKLESS_IDLE) && (configUSE_TICKLESS_IDLE == 1U)
#else
            xTaskResumeAll();
#endif

            if (g_HostHidMouse.isSetRemoteWakeup)
            {
            }
            break;
        case kStatus_WaitResume:
            if (g_HostHidMouse.selfWakeup)
            {
                g_HostHidMouse.selfWakeup = 0U;
                usb_echo("Start resume the device.\r\n");
                g_HostHidMouse.suspendResumeState = kStatus_ResumeRequest;
                if (kStatus_USB_Success ==
                    USB_HostResumeDeviceResquest(g_HostHandle,
                                                 g_HostHidMouse.suspendBus ? NULL : g_HostHidMouse.deviceHandle))
                {
                }
                else
                {
                    g_HostHidMouse.suspendResumeState = kStatus_Idle;
                    usb_echo("Send resume signal failed.\r\n");
                }
            }
            break;
        case kStatus_ResumeRequest:
            break;
        default:
            break;
    }
    command = 0;
}

static void USB_HostTask(void *param)
{
    while (1)
    {
        USB_HostTaskFn(param);
    }
}

static void USB_HostSuspendResume(void *param)
{
    while (1)
    {
        USB_HostSuspendResumeTask();
        vTaskDelay(1);
    }
}

static void USB_HostApplicationTask(void *param)
{
#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
    USB_LowpowerModeInit();
#endif

    USB_HostApplicationInit();

#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
    HW_TimerControl(1);
    usb_echo("Please Enter 's' to start suspend test\r\n");
#endif

    if (xTaskCreate(USB_HostTask, "usb host task", 2000L / sizeof(portSTACK_TYPE), g_HostHandle, 4, NULL) != pdPASS)
    {
        usb_echo("usb host task create failed!\r\n");
        return;
    }

    if (xTaskCreate(USB_HostSuspendResume, "host suspend resume task", 2000L / sizeof(portSTACK_TYPE), param, 4,
                    NULL) != pdPASS)
    {
        usb_echo("usb host suspend/resume task create failed!\r\n");
        return;
    }

    while (1)
    {
#if defined(configUSE_TICKLESS_IDLE) && (configUSE_TICKLESS_IDLE == 1U)
        if (!s_suspendResumeState)
        {
            USB_HostHidMouseTask(param);
        }
        else
        {
            xSemaphoreTake(s_wakeupSig1, portMAX_DELAY);
            s_suspendResumeState = 0;
        }
#else
        USB_HostHidMouseTask(param);
#endif
    }
}

int main(void)
{
    gpio_pin_config_t pinConfig = {kGPIO_DigitalInput, 1U};

    BOARD_InitPins();
    BOARD_BootClockRUN();

    BOARD_InitDebugConsole();

    /* Set the LLWU pin */
    GPIO_PinInit(LLWU_SW_GPIO, LLWU_SW_GPIO_PIN, &pinConfig);

    if (xTaskCreate(USB_HostApplicationTask, "app task", 2000L / sizeof(portSTACK_TYPE), &g_HostHidMouse, 3, NULL) !=
        pdPASS)
    {
        usb_echo("create mouse task error\r\n");
    }

    vTaskStartScheduler();

    while (1)
    {
        ;
    }
}
