/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "usb_host_config.h"
#include "usb_host.h"
#include "fsl_device_registers.h"
#include "usb_host_hid.h"
#include "board.h"
#include "host_mouse.h"
#include "fsl_common.h"
#if (defined(FSL_FEATURE_SOC_MPU_COUNT) && (FSL_FEATURE_SOC_MPU_COUNT > 0U))
#include "fsl_mpu.h"
#endif /* FSL_FEATURE_SOC_MPU_COUNT */
#if ((defined USB_HOST_CONFIG_EHCI) && (USB_HOST_CONFIG_EHCI))
#include "usb_phy.h"
#endif /* USB_HOST_CONFIG_EHCI */

#if ((!USB_HOST_CONFIG_KHCI) && (!USB_HOST_CONFIG_EHCI))
#error Please enable USB_HOST_CONFIG_KHCI or USB_HOST_CONFIG_EHCI in file usb_host_config.
#endif

#include "fsl_gpio.h"
#include "pin_mux.h"
#include <stdbool.h>
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* USB clock source and frequency*/
#define USB_FS_CLK_SRC kCLOCK_UsbSrcPll0
#define USB_FS_CLK_FREQ CLOCK_GetFreq(kCLOCK_PllFllSelClk)
#if ((defined USB_HOST_CONFIG_KHCI) && (USB_HOST_CONFIG_KHCI))
#define CONTROLLER_ID kUSB_ControllerKhci0
#endif /* USB_HOST_CONFIG_KHCI */
#if ((defined USB_HOST_CONFIG_EHCI) && (USB_HOST_CONFIG_EHCI))
#define CONTROLLER_ID kUSB_ControllerEhci0
#endif /* USB_HOST_CONFIG_EHCI */

#define USB_HOST_INTERRUPT_PRIORITY (3U)

#define USB_HOST_UCOSIII_APP_TASK_STACK_SIZE (2000U)
#define USB_HOST_UCOSIII_HOST_TASK_STACK_SIZE (2000U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

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
 * @brief host ucosiii task function.
 *
 * @param g_HostHandle   host handle
 */
static void USB_HostTask(void *param);

/*!
 * @brief host mouse ucosiii task function.
 *
 * @param param   the host mouse instance pointer.
 */
static void USB_HostApplicationTask(void *param);

void BOARD_InitHardware(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief USB host mouse instance global variable */
extern usb_host_mouse_instance_t g_HostHidMouse;
usb_host_handle g_HostHandle;

static uint8_t s_UsbHostApplicationTaskStack[USB_HOST_UCOSIII_APP_TASK_STACK_SIZE];
static uint8_t s_UsbHostTaskStack[USB_HOST_UCOSIII_HOST_TASK_STACK_SIZE];
static OS_TCB s_UsbHostApplicationTaskBlock;
static OS_TCB s_UsbHostTaskBlock;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief USB isr function.
 */
#if ((defined USB_HOST_CONFIG_KHCI) && (USB_HOST_CONFIG_KHCI))
void USB0_IRQHandler(void)
{
    USB_HostKhciIsrFunction(g_HostHandle);
}
#endif /* USB_HOST_CONFIG_KHCI */
#if ((defined USB_HOST_CONFIG_EHCI) && (USB_HOST_CONFIG_EHCI))
void USBHS_IRQHandler(void)
{
    USB_HostEhciIsrFunction(g_HostHandle);
}
#endif /* USB_HOST_CONFIG_EHCI */

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

        default:
            break;
    }
    return status;
}

static void USB_HostApplicationInit(void)
{
    usb_status_t status = kStatus_USB_Success;
    IRQn_Type usbIrq;

#if ((defined USB_HOST_CONFIG_KHCI) && (USB_HOST_CONFIG_KHCI))
    IRQn_Type usbFsIrqs[] = USB_IRQS;
    usbIrq = usbFsIrqs[CONTROLLER_ID - kUSB_ControllerKhci0];
    CLOCK_EnableUsbfs0Clock(USB_FS_CLK_SRC, USB_FS_CLK_FREQ);
#endif /* USB_HOST_CONFIG_KHCI */
#if ((defined USB_HOST_CONFIG_EHCI) && (USB_HOST_CONFIG_EHCI))
    IRQn_Type usbHsIrqs[] = USBHS_IRQS;
    usbIrq = usbHsIrqs[CONTROLLER_ID - kUSB_ControllerEhci0];
    CLOCK_EnableUsbhs0PhyPllClock(USB_HS_PHY_CLK_SRC, USB_HS_PHY_CLK_FREQ);
    CLOCK_EnableUsbhs0Clock(USB_HS_CLK_SRC, USB_HS_CLK_FREQ);
    USB_EhciPhyInit(CONTROLLER_ID, BOARD_XTAL0_CLK_HZ);
#endif /* USB_HOST_CONFIG_EHCI */
#if ((defined FSL_FEATURE_SOC_MPU_COUNT) && (FSL_FEATURE_SOC_MPU_COUNT))
    MPU_Enable(MPU, 0);
#endif /* FSL_FEATURE_SOC_MPU_COUNT */

    status = USB_HostInit(CONTROLLER_ID, &g_HostHandle, USB_HostEvent);
    if (status != kStatus_USB_Success)
    {
        usb_echo("host init error\r\n");
        return;
    }
    NVIC_SetPriority(usbIrq, USB_HOST_INTERRUPT_PRIORITY);
    NVIC_EnableIRQ(usbIrq);

    usb_echo("host init done\r\n");
}

static void USB_HostTask(void *param)
{
    while (1)
    {
#if ((defined USB_HOST_CONFIG_KHCI) && (USB_HOST_CONFIG_KHCI))
        USB_HostKhciTaskFunction(param);
#endif /* USB_HOST_CONFIG_KHCI */
#if ((defined USB_HOST_CONFIG_EHCI) && (USB_HOST_CONFIG_EHCI))
        USB_HostEhciTaskFunction(param);
#endif /* USB_HOST_CONFIG_EHCI */
    }
}

static void USB_HostApplicationTask(void *param)
{
    OS_ERR error;

    OS_CPU_SysTickInit(SystemCoreClock); /* MUST be called after OSStart() */

    USB_HostApplicationInit();

    OSTaskCreate(&s_UsbHostTaskBlock,                                     /* Task control block handle */
                 "usb host task",                                         /* Task Name */
                 USB_HostTask,                                            /* pointer to the task */
                 g_HostHandle,                                            /* Task input parameter */
                 3,                                                       /* Task priority */
                 (CPU_STK *)&s_UsbHostTaskStack[0],                       /* Task stack base address */
                 0,                                                       /* Task stack limit */
                 USB_HOST_UCOSIII_HOST_TASK_STACK_SIZE / sizeof(CPU_STK), /* Task stack size */
                 0, /* Mumber of messages can be sent to the task */
                 0, /* Default time_quanta */
                 0, /* Task extension */
                 0, /* Task save FP */
                 &error);
    if (error != OS_ERR_NONE)
    {
        usb_echo("create host task error\r\n");
    }

    while (1)
    {
        USB_HostHidMouseTask(param);
    }
}

int main(void)
{
    OS_ERR error;

    gpio_pin_config_t pinConfig;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* enable usb host vbus */
    pinConfig.pinDirection = kGPIO_DigitalOutput;
    pinConfig.outputLogic = 1;

    GPIO_PinInit(GPIOC, 19, &pinConfig);

    OSInit(&error);
#if OS_CFG_SCHED_ROUND_ROBIN_EN > 0u
    /* Enable task round robin. */
    OSSchedRoundRobinCfg((CPU_BOOLEAN)1, 0, &error);
#endif

    OSTaskCreate(&s_UsbHostApplicationTaskBlock,                         /* Task control block handle */
                 "app task",                                             /* Task Name */
                 USB_HostApplicationTask,                                /* pointer to the task */
                 &g_HostHidMouse,                                        /* Task input parameter */
                 4,                                                      /* Task priority */
                 (CPU_STK *)&s_UsbHostApplicationTaskStack[0],           /* Task stack base address */
                 0,                                                      /* Task stack limit */
                 USB_HOST_UCOSIII_APP_TASK_STACK_SIZE / sizeof(CPU_STK), /* Task stack size */
                 0, /* Mumber of messages can be sent to the task */
                 0, /* Default time_quanta */
                 0, /* Task extension */
                 0, /* Task save FP */
                 &error);
    if (error != OS_ERR_NONE)
    {
        usb_echo("create host task error\r\n");
    }

    OSStart(&error);

    while (1)
    {
        ;
    }
}
