/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "usb_device_config.h"
#include "usb.h"
#include "usb_device.h"

#include "usb_device_class.h"
#include "usb_device_hid.h"
#include "usb_device_audio.h"
#include "usb_device_ch9.h"
#include "usb_device_descriptor.h"
#include "fsl_adapter_audio.h"
#include "composite.h"

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#if (defined(FSL_FEATURE_SOC_SYSMPU_COUNT) && (FSL_FEATURE_SOC_SYSMPU_COUNT > 0U))
#include "fsl_sysmpu.h"
#endif /* FSL_FEATURE_SOC_SYSMPU_COUNT */
#if ((defined FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U))
#include "usb_phy.h"
#endif

#include "usb_audio_config.h"
#include "fsl_i2c.h"
#include "fsl_i2s.h"
#include "fsl_i2s_dma.h"
#include "fsl_wm8904.h"
#include "fsl_codec_common.h"
#include "fsl_codec_adapter.h"
#include "fsl_power.h"
#include "fsl_inputmux.h"
#include "fsl_pint.h"
#if defined(USB_DEVICE_AUDIO_USE_SYNC_MODE) && (USB_DEVICE_AUDIO_USE_SYNC_MODE > 0U)
#include "fsl_ctimer.h"
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_DMA_INSTANCE_INDEX    (0U)
#define DEMO_I2S_TX_INSTANCE_INDEX (3U)
#define DEMO_I2S_TX_CHANNEL        (7)
#define DEMO_I2S_TX_MODE           kHAL_AudioSlave
#define DEMO_I2S_RX_INSTANCE_INDEX (1U)
#define DEMO_I2S_RX_CHANNEL        (2)
#define DEMO_I2S_RX_MODE           kHAL_AudioMaster
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern uint32_t USB_AudioSpeakerBufferSpaceUsed(void);
#if defined(USB_DEVICE_AUDIO_USE_SYNC_MODE) && (USB_DEVICE_AUDIO_USE_SYNC_MODE > 0U)
void CTIMER_SOF_TOGGLE_HANDLER_PLL(uint32_t i);
#else
extern void USB_DeviceCalculateFeedback(void);
#endif
void BOARD_InitHardware(void);
void USB_DeviceClockInit(void);
void USB_DeviceIsrEnable(void);
#if USB_DEVICE_CONFIG_USE_TASK
void USB_DeviceTaskFn(void *deviceHandle);
#endif

usb_status_t USB_DeviceCallback(usb_device_handle handle, uint32_t event, void *param);
extern usb_status_t USB_DeviceHidKeyboardAction(void);
extern char *SW_GetName(void);
extern void USB_AudioCodecTask(void);
extern void USB_AudioSpeakerResetTask(void);
extern void USB_DeviceAudioSpeakerStatusReset(void);
extern void AUDIO_DMA_EDMA_Start();
extern void BOARD_Codec_Init();
/*******************************************************************************
 * Variables
 ******************************************************************************/
extern usb_device_composite_struct_t g_composite;
extern uint8_t audioPlayDataBuff[AUDIO_SPEAKER_DATA_WHOLE_BUFFER_COUNT_NORMAL * AUDIO_PLAY_BUFFER_SIZE_ONE_FRAME];
extern uint8_t audioRecDataBuff[AUDIO_RECORDER_DATA_WHOLE_BUFFER_COUNT_NORMAL * FS_ISO_IN_ENDP_PACKET_SIZE];
volatile bool g_ButtonPress = false;
static hal_audio_transfer_t s_TxTransfer;
static hal_audio_transfer_t s_RxTransfer;
HAL_AUDIO_HANDLE_DEFINE(audioTxHandle);
HAL_AUDIO_HANDLE_DEFINE(audioRxHandle);
hal_audio_config_t audioTxConfig;
hal_audio_config_t audioRxConfig;
hal_audio_dma_config_t dmaTxConfig;
hal_audio_dma_config_t dmaRxConfig;
USB_DMA_NONINIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE)
static uint8_t audioPlayDMATempBuff[AUDIO_PLAY_BUFFER_SIZE_ONE_FRAME];
USB_DMA_NONINIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE)
static uint8_t audioRecDMATempBuff[FS_ISO_IN_ENDP_PACKET_SIZE];
codec_handle_t codecHandle;

wm8904_config_t wm8904Config = {
    .i2cConfig          = {.codecI2CInstance = BOARD_CODEC_I2C_INSTANCE},
    .recordSource       = kWM8904_RecordSourceLineInput,
    .recordChannelLeft  = kWM8904_RecordChannelLeft2,
    .recordChannelRight = kWM8904_RecordChannelRight2,
    .playSource         = kWM8904_PlaySourceDAC,
    .slaveAddress       = WM8904_I2C_ADDRESS,
    .protocol           = kWM8904_ProtocolI2S,
    .format             = {.sampleRate = kWM8904_SampleRate48kHz, .bitWidth = kWM8904_BitWidth16},
    .master             = false,
};
codec_config_t boardCodecConfig = {.codecDevType = kCODEC_WM8904, .codecDevConfig = &wm8904Config};

#if defined(USB_DEVICE_AUDIO_USE_SYNC_MODE) && (USB_DEVICE_AUDIO_USE_SYNC_MODE > 0U)
ctimer_callback_t *cb_func_pll[] = {(ctimer_callback_t *)CTIMER_SOF_TOGGLE_HANDLER_PLL};
static ctimer_config_t ctimerInfoPll;
#endif
#define BOARD_SW1_NAME         "SW1"
#define DEMO_PINT_PIN_INT0_SRC kINPUTMUX_GpioPort1Pin1ToPintsel /* SW1 */
/* Composite device structure. */
USB_DMA_NONINIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE)
usb_device_composite_struct_t g_composite;
extern usb_device_class_struct_t g_UsbDeviceHidMouseClass;
extern usb_device_class_struct_t g_UsbDeviceAudioClassRecorder;
extern usb_device_class_struct_t g_UsbDeviceAudioClassSpeaker;
extern volatile bool g_ButtonPress;
extern usb_device_composite_struct_t *g_UsbDeviceComposite;
extern usb_device_composite_struct_t *g_deviceAudioComposite;
extern uint8_t audioFeedBackBuffer[4];
extern hal_audio_config_t audioTxConfig;
extern hal_audio_config_t audioRxConfig;
extern HAL_AUDIO_HANDLE_DEFINE(audioTxHandle);
extern HAL_AUDIO_HANDLE_DEFINE(audioRxHandle);
/* USB device class information */
static usb_device_class_config_struct_t g_CompositeClassConfig[3] = {{
                                                                         USB_DeviceHidKeyboardCallback,
                                                                         (class_handle_t)NULL,
                                                                         &g_UsbDeviceHidMouseClass,
                                                                     },
                                                                     {
                                                                         USB_DeviceAudioCompositeCallback,
                                                                         (class_handle_t)NULL,
                                                                         &g_UsbDeviceAudioClassRecorder,
                                                                     },
                                                                     {
                                                                         USB_DeviceAudioCompositeCallback,
                                                                         (class_handle_t)NULL,
                                                                         &g_UsbDeviceAudioClassSpeaker,
                                                                     }

};

/* USB device class configuration information */
static usb_device_class_config_list_struct_t g_UsbDeviceCompositeConfigList = {
    g_CompositeClassConfig,
    USB_DeviceCallback,
    3,
};

/*******************************************************************************
 * Code
 ******************************************************************************/
static void i2c_release_bus_delay(void)
{
    uint32_t i = 0;
    for (i = 0; i < 100; i++)
    {
        __NOP();
    }
}

void BOARD_I3C_ReleaseBus(void)
{
    uint8_t i = 0;

    GPIO_PortInit(BOARD_INITI3CPINSASGPIO_I3C0_SDA_PERIPHERAL, BOARD_INITI3CPINSASGPIO_I3C0_SDA_PORT);
    GPIO_PortInit(BOARD_INITI3CPINSASGPIO_I3C0_SCL_PERIPHERAL, BOARD_INITI3CPINSASGPIO_I3C0_SCL_PORT);

    BOARD_InitI3CPinsAsGPIO();

    /* Drive SDA low first to simulate a start */
    GPIO_PinWrite(BOARD_INITI3CPINSASGPIO_I3C0_SDA_PERIPHERAL, BOARD_INITI3CPINSASGPIO_I3C0_SDA_PORT,
                  BOARD_INITI3CPINSASGPIO_I3C0_SDA_PIN, 0U);
    i2c_release_bus_delay();

    /* Send 9 pulses on SCL */
    for (i = 0; i < 9; i++)
    {
        GPIO_PinWrite(BOARD_INITI3CPINSASGPIO_I3C0_SCL_PERIPHERAL, BOARD_INITI3CPINSASGPIO_I3C0_SCL_PORT,
                      BOARD_INITI3CPINSASGPIO_I3C0_SCL_PIN, 0U);
        i2c_release_bus_delay();

        GPIO_PinWrite(BOARD_INITI3CPINSASGPIO_I3C0_SDA_PERIPHERAL, BOARD_INITI3CPINSASGPIO_I3C0_SDA_PORT,
                      BOARD_INITI3CPINSASGPIO_I3C0_SDA_PIN, 1U);
        i2c_release_bus_delay();

        GPIO_PinWrite(BOARD_INITI3CPINSASGPIO_I3C0_SCL_PERIPHERAL, BOARD_INITI3CPINSASGPIO_I3C0_SCL_PORT,
                      BOARD_INITI3CPINSASGPIO_I3C0_SCL_PIN, 1U);
        i2c_release_bus_delay();
        i2c_release_bus_delay();
    }

    /* Send stop */
    GPIO_PinWrite(BOARD_INITI3CPINSASGPIO_I3C0_SCL_PERIPHERAL, BOARD_INITI3CPINSASGPIO_I3C0_SCL_PORT,
                  BOARD_INITI3CPINSASGPIO_I3C0_SCL_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_PinWrite(BOARD_INITI3CPINSASGPIO_I3C0_SDA_PERIPHERAL, BOARD_INITI3CPINSASGPIO_I3C0_SDA_PORT,
                  BOARD_INITI3CPINSASGPIO_I3C0_SDA_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_PinWrite(BOARD_INITI3CPINSASGPIO_I3C0_SCL_PERIPHERAL, BOARD_INITI3CPINSASGPIO_I3C0_SCL_PORT,
                  BOARD_INITI3CPINSASGPIO_I3C0_SCL_PIN, 1U);
    i2c_release_bus_delay();

    GPIO_PinWrite(BOARD_INITI3CPINSASGPIO_I3C0_SDA_PERIPHERAL, BOARD_INITI3CPINSASGPIO_I3C0_SDA_PORT,
                  BOARD_INITI3CPINSASGPIO_I3C0_SDA_PIN, 1U);
    i2c_release_bus_delay();
}

void pint_intr_callback(pint_pin_int_t pintr, uint32_t pmatch_status)
{
    g_ButtonPress = true;
}

void BOARD_USB_AUDIO_KEYBOARD_Init(void)
{
    INPUTMUX_Init(INPUTMUX);
    INPUTMUX_AttachSignal(INPUTMUX, kPINT_PinInt0, DEMO_PINT_PIN_INT0_SRC);
    INPUTMUX_Deinit(INPUTMUX);

    /* Initialize PINT */
    PINT_Init(PINT);

    /* Setup Pin Interrupt 0 for rising edge */
    PINT_PinInterruptConfig(PINT, kPINT_PinInt0, kPINT_PinIntEnableRiseEdge, pint_intr_callback);
    /* Enable callbacks for PINT0 by Index */
    PINT_EnableCallbackByIndex(PINT, kPINT_PinInt0);
}

char *SW_GetName(void)
{
    return BOARD_SW1_NAME;
}

void BOARD_Codec_Init()
{
    if (CODEC_Init(&codecHandle, &boardCodecConfig) != kStatus_Success)
    {
        assert(false);
    }
    if (CODEC_SetVolume(&codecHandle, kCODEC_PlayChannelHeadphoneLeft | kCODEC_PlayChannelHeadphoneRight, 0x0020) !=
        kStatus_Success)
    {
        assert(false);
    }
}

void BOARD_SetCodecMuteUnmute(bool mute)
{
    if (CODEC_SetMute(&codecHandle, kCODEC_PlayChannelHeadphoneLeft | kCODEC_PlayChannelHeadphoneRight, mute) !=
        kStatus_Success)
    {
        assert(false);
    }
}

static void TxCallback(hal_audio_handle_t handle, hal_audio_status_t completionStatus, void *callbackParam)
{
    uint32_t audioSpeakerPreReadDataCount = 0U;
    uint32_t preAudioSendCount            = 0U;

    if ((USB_AudioSpeakerBufferSpaceUsed() < (g_composite.audioUnified.audioPlayTransferSize)) &&
        (g_composite.audioUnified.startPlayFlag == 1U))
    {
        g_composite.audioUnified.startPlayFlag          = 0;
        g_composite.audioUnified.speakerDetachOrNoInput = 1;
    }
    if (0U != g_composite.audioUnified.startPlayFlag)
    {
#if defined(USB_DEVICE_AUDIO_USE_SYNC_MODE) && (USB_DEVICE_AUDIO_USE_SYNC_MODE > 0U)
#else
        USB_DeviceCalculateFeedback();
#endif
        s_TxTransfer.dataSize = g_composite.audioUnified.audioPlayTransferSize;
        s_TxTransfer.data     = audioPlayDataBuff + g_composite.audioUnified.tdReadNumberPlay;
        preAudioSendCount     = g_composite.audioUnified.audioSendCount[0];
        g_composite.audioUnified.audioSendCount[0] += g_composite.audioUnified.audioPlayTransferSize;
        if (preAudioSendCount > g_composite.audioUnified.audioSendCount[0])
        {
            g_composite.audioUnified.audioSendCount[1] += 1U;
        }
        g_composite.audioUnified.audioSendTimes++;
        g_composite.audioUnified.tdReadNumberPlay += g_composite.audioUnified.audioPlayTransferSize;
        if (g_composite.audioUnified.tdReadNumberPlay >= g_composite.audioUnified.audioPlayBufferSize)
        {
            g_composite.audioUnified.tdReadNumberPlay = 0;
        }
        audioSpeakerPreReadDataCount = g_composite.audioUnified.audioSpeakerReadDataCount[0];
        g_composite.audioUnified.audioSpeakerReadDataCount[0] += g_composite.audioUnified.audioPlayTransferSize;
        if (audioSpeakerPreReadDataCount > g_composite.audioUnified.audioSpeakerReadDataCount[0])
        {
            g_composite.audioUnified.audioSpeakerReadDataCount[1] += 1U;
        }
    }
    else
    {
        if (0U != g_composite.audioUnified.audioPlayTransferSize)
        {
            s_TxTransfer.dataSize = g_composite.audioUnified.audioPlayTransferSize;
        }
        else
        {
            s_TxTransfer.dataSize = HS_ISO_OUT_ENDP_PACKET_SIZE;
        }
        s_TxTransfer.data = audioPlayDMATempBuff;
    }
    HAL_AudioTransferSendNonBlocking(handle, &s_TxTransfer);
}

static void RxCallback(hal_audio_handle_t handle, hal_audio_status_t completionStatus, void *callbackParam)
{
    if (g_composite.audioUnified.startRec)
    {
        s_RxTransfer.dataSize = FS_ISO_IN_ENDP_PACKET_SIZE;
        s_RxTransfer.data     = audioRecDataBuff + g_composite.audioUnified.tdWriteNumberRec;
        g_composite.audioUnified.tdWriteNumberRec += FS_ISO_IN_ENDP_PACKET_SIZE;
        if (g_composite.audioUnified.tdWriteNumberRec >=
            AUDIO_RECORDER_DATA_WHOLE_BUFFER_COUNT_NORMAL * FS_ISO_IN_ENDP_PACKET_SIZE)
        {
            g_composite.audioUnified.tdWriteNumberRec = 0;
        }
    }
    else
    {
        s_RxTransfer.dataSize = FS_ISO_IN_ENDP_PACKET_SIZE;
        s_RxTransfer.data     = audioRecDMATempBuff;
    }
    HAL_AudioTransferReceiveNonBlocking(handle, &s_RxTransfer);
}

void AUDIO_DMA_EDMA_Start()
{
    usb_echo("Init Audio SAI and CODEC\r\n");
    s_TxTransfer.dataSize = HS_ISO_OUT_ENDP_PACKET_SIZE;
    s_TxTransfer.data     = audioPlayDMATempBuff;
    s_RxTransfer.dataSize = FS_ISO_IN_ENDP_PACKET_SIZE;
    s_RxTransfer.data     = audioRecDMATempBuff;

    HAL_AudioTxInstallCallback((hal_audio_handle_t)&audioTxHandle[0], TxCallback, (void *)&s_TxTransfer);
    HAL_AudioRxInstallCallback((hal_audio_handle_t)&audioRxHandle[0], RxCallback, (void *)&s_RxTransfer);

    /* need to queue two receive buffers so when the first one is filled,
     * the other is immediatelly starts to be filled */
    HAL_AudioTransferReceiveNonBlocking((hal_audio_handle_t)&audioRxHandle[0], &s_RxTransfer);
    HAL_AudioTransferReceiveNonBlocking((hal_audio_handle_t)&audioRxHandle[0], &s_RxTransfer);

    HAL_AudioTransferSendNonBlocking((hal_audio_handle_t)&audioTxHandle[0], &s_TxTransfer);
}

#if defined(USB_DEVICE_AUDIO_USE_SYNC_MODE) && (USB_DEVICE_AUDIO_USE_SYNC_MODE > 0U)
void USB_AudioPllChange(void)
{
    CLKCTL1->AUDIOPLL0NUM = g_composite.audioUnified.curAudioPllFrac;
}

void CTIMER_CaptureInit(void)
{
    INPUTMUX->CT32BIT_CAP_SEL[0][0] = 0x12U; /* 0xFU for USB1.*/
    CTIMER_GetDefaultConfig(&ctimerInfoPll);

    /* Initialize CTimer module */
    CTIMER_Init(CTIMER0, &ctimerInfoPll);

    CTIMER_SetupCapture(CTIMER0, kCTIMER_Capture_0, kCTIMER_Capture_RiseEdge, true);

    CTIMER_RegisterCallBack(CTIMER0, (ctimer_callback_t *)&cb_func_pll[0], kCTIMER_SingleCallback);

    /* Start the L counter */
    CTIMER_StartTimer(CTIMER0);
}
#endif
void USB_IRQHandler(void)
{
    USB_DeviceLpcIp3511IsrFunction(g_composite.deviceHandle);
}

void USB_DeviceClockInit(void)
{
    uint8_t usbClockDiv = 1;
    uint32_t usbClockFreq;
    usb_phy_config_struct_t phyConfig = {
        BOARD_USB_PHY_D_CAL,
        BOARD_USB_PHY_TXCAL45DP,
        BOARD_USB_PHY_TXCAL45DM,
    };

    /* enable USB IP clock */
    CLOCK_SetClkDiv(kCLOCK_DivPfc1Clk, 5);
    CLOCK_AttachClk(kXTALIN_CLK_to_USB_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivUsbHsFclk, usbClockDiv);
    CLOCK_EnableUsbhsDeviceClock();
    RESET_PeripheralReset(kUSBHS_PHY_RST_SHIFT_RSTn);
    RESET_PeripheralReset(kUSBHS_DEVICE_RST_SHIFT_RSTn);
    RESET_PeripheralReset(kUSBHS_HOST_RST_SHIFT_RSTn);
    RESET_PeripheralReset(kUSBHS_SRAM_RST_SHIFT_RSTn);
    /*Make sure USDHC ram buffer has power up*/
    POWER_DisablePD(kPDRUNCFG_APD_USBHS_SRAM);
    POWER_DisablePD(kPDRUNCFG_PPD_USBHS_SRAM);
    POWER_ApplyPD();

    /* save usb ip clock freq*/
    usbClockFreq = g_xtalFreq / usbClockDiv;
    /* enable USB PHY PLL clock, the phy bus clock (480MHz) source is same with USB IP */
    CLOCK_EnableUsbHs0PhyPllClock(kXTALIN_CLK_to_USB_CLK, usbClockFreq);

#if defined(FSL_FEATURE_USBHSD_USB_RAM) && (FSL_FEATURE_USBHSD_USB_RAM)
    for (int i = 0; i < FSL_FEATURE_USBHSD_USB_RAM; i++)
    {
        ((uint8_t *)FSL_FEATURE_USBHSD_USB_RAM_BASE_ADDRESS)[i] = 0x00U;
    }
#endif
    USB_EhciPhyInit(CONTROLLER_ID, BOARD_XTAL_SYS_CLK_HZ, &phyConfig);

    /* the following code should run after phy initialization and should wait some microseconds to make sure utmi clock
     * valid */
    /* enable usb1 host clock */
    CLOCK_EnableClock(kCLOCK_UsbhsHost);
    /*  Wait until host_needclk de-asserts */
    while (SYSCTL0->USBCLKSTAT & SYSCTL0_USBCLKSTAT_HOST_NEED_CLKST_MASK)
    {
        __ASM("nop");
    }
    /*According to reference mannual, device mode setting has to be set by access usb host register */
    USBHSH->PORTMODE |= USBHSH_PORTMODE_DEV_ENABLE_MASK;
    /* disable usb1 host clock */
    CLOCK_DisableClock(kCLOCK_UsbhsHost);
}
void USB_DeviceIsrEnable(void)
{
    uint8_t irqNumber;

    uint8_t usbDeviceIP3511Irq[] = USBHSD_IRQS;
    irqNumber                    = usbDeviceIP3511Irq[CONTROLLER_ID - kUSB_ControllerLpcIp3511Hs0];

    /* Install isr, set priority, and enable IRQ. */
    NVIC_SetPriority((IRQn_Type)irqNumber, USB_DEVICE_INTERRUPT_PRIORITY);
    EnableIRQ((IRQn_Type)irqNumber);
}
#if USB_DEVICE_CONFIG_USE_TASK
void USB_DeviceTaskFn(void *deviceHandle)
{
    USB_DeviceLpcIp3511TaskFunction(deviceHandle);
}
#endif

/*!
 * @brief USB device callback function.
 *
 * This function handles the usb device specific requests.
 *
 * @param handle		  The USB device handle.
 * @param event 		  The USB device event type.
 * @param param 		  The parameter of the device specific request.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceCallback(usb_device_handle handle, uint32_t event, void *param)
{
    usb_status_t error = kStatus_USB_InvalidRequest;
    uint16_t *temp16   = (uint16_t *)param;
    uint8_t *temp8     = (uint8_t *)param;
    uint8_t count      = 0U;

    switch (event)
    {
        case kUSB_DeviceEventBusReset:
        {
            for (count = 0U; count < USB_DEVICE_INTERFACE_COUNT; count++)
            {
                g_composite.currentInterfaceAlternateSetting[count] = 0U;
            }
            /* reset audio speaker status to be the initialized status */
            USB_DeviceAudioSpeakerStatusReset();
#if defined(USB_DEVICE_AUDIO_USE_SYNC_MODE) && (USB_DEVICE_AUDIO_USE_SYNC_MODE > 0U)
#else
            /* reset the the last feedback value */
            g_composite.audioUnified.lastFeedbackValue             = 0U;
#endif
            g_composite.attach               = 0U;
            g_composite.currentConfiguration = 0U;
            error                            = kStatus_USB_Success;
#if (defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0U)) || \
    (defined(USB_DEVICE_CONFIG_LPCIP3511HS) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0U))
            /* Get USB speed to configure the device, including max packet size and interval of the endpoints. */
            if (kStatus_USB_Success == USB_DeviceClassGetSpeed(CONTROLLER_ID, &g_composite.speed))
            {
                USB_DeviceSetSpeed(handle, g_composite.speed);
            }
            if (USB_SPEED_HIGH == g_composite.speed)
            {
#if defined(USB_DEVICE_AUDIO_USE_SYNC_MODE) && (USB_DEVICE_AUDIO_USE_SYNC_MODE > 0U)
                g_composite.audioUnified.currentStreamOutMaxPacketSize = (HS_ISO_OUT_ENDP_PACKET_SIZE);
#else
                g_composite.audioUnified.currentStreamOutMaxPacketSize =
                    (HS_ISO_OUT_ENDP_PACKET_SIZE + AUDIO_OUT_FORMAT_CHANNELS * AUDIO_OUT_FORMAT_SIZE);
                g_composite.audioUnified.currentFeedbackMaxPacketSize = HS_ISO_FEEDBACK_ENDP_PACKET_SIZE;
#endif /* USB_DEVICE_AUDIO_USE_SYNC_MODE */
#if (USB_DEVICE_CONFIG_AUDIO_CLASS_2_0)
                /* high speed and audio 2.0, audio play interval is set by HS EP packet size */
                g_composite.audioUnified.audioPlayTransferSize = HS_ISO_OUT_ENDP_PACKET_SIZE;
                /* use short play buffer size, only use two elements */
                g_composite.audioUnified.audioPlayBufferSize =
                    AUDIO_PLAY_BUFFER_SIZE_ONE_FRAME * AUDIO_SPEAKER_DATA_WHOLE_BUFFER_COUNT;
#if defined(USB_DEVICE_AUDIO_USE_SYNC_MODE) && (USB_DEVICE_AUDIO_USE_SYNC_MODE > 0U)
#else
#if defined(USB_DEVICE_CONFIG_LPCIP3511HS) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0U)
                AUDIO_UPDATE_FEEDBACK_DATA(audioFeedBackBuffer, AUDIO_SAMPLING_RATE_TO_16_16_SPECIFIC);
#else
                AUDIO_UPDATE_FEEDBACK_DATA(audioFeedBackBuffer, AUDIO_SAMPLING_RATE_TO_16_16);
#endif
#endif
#else
                /* high speed and audio 1.0, audio play interval is 1 ms using this play size */
                g_composite.audioUnified.audioPlayTransferSize = AUDIO_PLAY_BUFFER_SIZE_ONE_FRAME;
                /* use the whole play buffer size */
                g_composite.audioUnified.audioPlayBufferSize =
                    AUDIO_SPEAKER_DATA_WHOLE_BUFFER_COUNT_NORMAL * AUDIO_PLAY_BUFFER_SIZE_ONE_FRAME;
#if defined(USB_DEVICE_AUDIO_USE_SYNC_MODE) && (USB_DEVICE_AUDIO_USE_SYNC_MODE > 0U)
#else
                AUDIO_UPDATE_FEEDBACK_DATA(audioFeedBackBuffer, AUDIO_SAMPLING_RATE_TO_10_14);
#endif
#endif /* USB_DEVICE_CONFIG_AUDIO_CLASS_2_0 */
                g_deviceAudioComposite->audioUnified.speed = USB_SPEED_HIGH;
            }
            else
            {
#if defined(USB_DEVICE_AUDIO_USE_SYNC_MODE) && (USB_DEVICE_AUDIO_USE_SYNC_MODE > 0U)
                g_composite.audioUnified.currentStreamOutMaxPacketSize = (FS_ISO_OUT_ENDP_PACKET_SIZE);
#else
                g_composite.audioUnified.currentStreamOutMaxPacketSize =
                    (FS_ISO_OUT_ENDP_PACKET_SIZE + AUDIO_OUT_FORMAT_CHANNELS * AUDIO_OUT_FORMAT_SIZE);
                g_composite.audioUnified.currentFeedbackMaxPacketSize = FS_ISO_FEEDBACK_ENDP_PACKET_SIZE;
                AUDIO_UPDATE_FEEDBACK_DATA(audioFeedBackBuffer, AUDIO_SAMPLING_RATE_TO_10_14);
#endif
                /* full speed, audio play interval is 1 ms using this play size */
                g_composite.audioUnified.audioPlayTransferSize = AUDIO_PLAY_BUFFER_SIZE_ONE_FRAME;
                /* use the whole play buffer size */
                g_composite.audioUnified.audioPlayBufferSize =
                    AUDIO_SPEAKER_DATA_WHOLE_BUFFER_COUNT_NORMAL * AUDIO_PLAY_BUFFER_SIZE_ONE_FRAME;
            }
#else
#if defined(USB_DEVICE_AUDIO_USE_SYNC_MODE) && (USB_DEVICE_AUDIO_USE_SYNC_MODE > 0U)
            g_composite.audioUnified.currentStreamOutMaxPacketSize = (FS_ISO_OUT_ENDP_PACKET_SIZE);
#else
            g_composite.audioUnified.currentStreamOutMaxPacketSize =
                (FS_ISO_OUT_ENDP_PACKET_SIZE + AUDIO_OUT_FORMAT_CHANNELS * AUDIO_OUT_FORMAT_SIZE);
            g_composite.audioUnified.currentFeedbackMaxPacketSize = FS_ISO_FEEDBACK_ENDP_PACKET_SIZE;
            AUDIO_UPDATE_FEEDBACK_DATA(audioFeedBackBuffer, AUDIO_SAMPLING_RATE_TO_10_14);
            /* reset the the last feedback value */
            g_deviceAudioComposite->audioUnified.lastFeedbackValue = 0U;
#endif
            /* full speed, audio play interval is 1 ms using this play size */
            g_composite.audioUnified.audioPlayTransferSize = AUDIO_PLAY_BUFFER_SIZE_ONE_FRAME;
            /* use the whole play buffer size */
            g_composite.audioUnified.audioPlayBufferSize =
                AUDIO_SPEAKER_DATA_WHOLE_BUFFER_COUNT_NORMAL * AUDIO_PLAY_BUFFER_SIZE_ONE_FRAME;
#endif /* USB_DEVICE_CONFIG_EHCI, USB_DEVICE_CONFIG_LPCIP3511HS */
        }
        break;
        case kUSB_DeviceEventSetConfiguration:
            if (0U == (*temp8))
            {
                g_composite.attach               = 0U;
                g_composite.currentConfiguration = 0U;
                error                            = kStatus_USB_Success;
            }
            else if (USB_COMPOSITE_CONFIGURE_INDEX == (*temp8))
            {
                g_composite.attach               = 1U;
                g_composite.currentConfiguration = *temp8;
                USB_DeviceAudioCompositeSetConfigure(g_composite.audioUnified.audioSpeakerHandle, *temp8);
                USB_DeviceAudioCompositeSetConfigure(g_composite.audioUnified.audioRecorderHandle, *temp8);
                USB_DeviceHidKeyboardSetConfigure(g_composite.hidKeyboard.hidHandle, *temp8);
                error = kStatus_USB_Success;
            }
            else
            {
            }
            break;
        case kUSB_DeviceEventSetInterface:

            if (g_composite.attach)
            {
                uint8_t interface        = (uint8_t)((*temp16 & 0xFF00U) >> 0x08U);
                uint8_t alternateSetting = (uint8_t)(*temp16 & 0x00FFU);

                switch (interface)
                {
                    case USB_AUDIO_CONTROL_INTERFACE_INDEX:
                        if (alternateSetting < USB_AUDIO_CONTROL_INTERFACE_ALTERNATE_COUNT)
                        {
                            error = kStatus_USB_Success;
                        }
                        break;
                    case USB_AUDIO_RECORDER_STREAM_INTERFACE_INDEX:
                        if (alternateSetting < USB_AUDIO_RECORDER_STREAM_INTERFACE_ALTERNATE_COUNT)
                        {
                            error = USB_DeviceAudioRecorderSetInterface(g_composite.audioUnified.audioRecorderHandle,
                                                                        interface, alternateSetting);
                        }
                        break;
                    case USB_AUDIO_SPEAKER_STREAM_INTERFACE_INDEX:
                        if (alternateSetting < USB_AUDIO_SPEAKER_STREAM_INTERFACE_ALTERNATE_COUNT)
                        {
                            error = USB_DeviceAudioSpeakerSetInterface(g_composite.audioUnified.audioSpeakerHandle,
                                                                       interface, alternateSetting);
#if defined(USB_DEVICE_AUDIO_USE_SYNC_MODE) && (USB_DEVICE_AUDIO_USE_SYNC_MODE > 0U)
                            if (USB_AUDIO_SPEAKER_STREAM_INTERFACE_ALTERNATE_1 == alternateSetting)
                            {
                                g_composite.audioUnified.stopDataLengthAudioAdjust = 0U;
                            }
                            else if (USB_AUDIO_SPEAKER_STREAM_INTERFACE_ALTERNATE_0 == alternateSetting)
                            {
                                g_composite.audioUnified.stopDataLengthAudioAdjust = 1U;
                            }
#else
                            /* usb host stops the speaker, so there is no need for feedback */
                            if ((1U == g_composite.audioUnified.startPlayFlag) &&
                                (USB_AUDIO_SPEAKER_STREAM_INTERFACE_ALTERNATE_0 == alternateSetting))
                            {
                                g_composite.audioUnified.stopFeedbackUpdate = 1U;
                            }

                            /* usb host start the speaker, discard the feedback for AUDIO_SPEAKER_FEEDBACK_DISCARD_COUNT
                             * times */
                            if (USB_AUDIO_SPEAKER_STREAM_INTERFACE_ALTERNATE_1 == alternateSetting)
                            {
                                g_composite.audioUnified.stopFeedbackUpdate              = 0U;
                                g_deviceAudioComposite->audioUnified.feedbackDiscardFlag = 1U;
                                g_deviceAudioComposite->audioUnified.feedbackDiscardTimes =
                                    AUDIO_SPEAKER_FEEDBACK_DISCARD_COUNT;
                            }
#endif
                        }
                        break;
                    case USB_HID_KEYBOARD_INTERFACE_INDEX:
                        if (alternateSetting < USB_HID_KEYBOARD_INTERFACE_ALTERNATE_COUNT)
                        {
                            error = kStatus_USB_Success;
                        }
                        break;
                    default:
                        break;
                }

                if (kStatus_USB_Success == error)
                {
                    g_composite.currentInterfaceAlternateSetting[interface] = alternateSetting;
                }
            }
            break;
        case kUSB_DeviceEventGetConfiguration:
            if (param)
            {
                *temp8 = g_composite.currentConfiguration;
                error  = kStatus_USB_Success;
            }
            break;
        case kUSB_DeviceEventGetInterface:
            if (param)
            {
                uint8_t interface = (uint8_t)((*temp16 & 0xFF00U) >> 0x08U);
                if (interface < USB_DEVICE_INTERFACE_COUNT)
                {
                    *temp16 = (*temp16 & 0xFF00U) | g_composite.currentInterfaceAlternateSetting[interface];
                    error   = kStatus_USB_Success;
                }
            }
            break;
        case kUSB_DeviceEventGetDeviceDescriptor:
            if (param)
            {
                error = USB_DeviceGetDeviceDescriptor(handle, (usb_device_get_device_descriptor_struct_t *)param);
            }
            break;
        case kUSB_DeviceEventGetConfigurationDescriptor:
            if (param)
            {
                error = USB_DeviceGetConfigurationDescriptor(handle,
                                                             (usb_device_get_configuration_descriptor_struct_t *)param);
            }
            break;
        case kUSB_DeviceEventGetStringDescriptor:
            if (param)
            {
                error = USB_DeviceGetStringDescriptor(handle, (usb_device_get_string_descriptor_struct_t *)param);
            }
            break;
        case kUSB_DeviceEventGetHidReportDescriptor:
            if (param)
            {
                error =
                    USB_DeviceGetHidReportDescriptor(handle, (usb_device_get_hid_report_descriptor_struct_t *)param);
            }
            break;
#if (defined(USB_DEVICE_CONFIG_CV_TEST) && (USB_DEVICE_CONFIG_CV_TEST > 0U))
        case kUSB_DeviceEventGetDeviceQualifierDescriptor:
            if (param)
            {
                /* Get device descriptor request */
                error = USB_DeviceGetDeviceQualifierDescriptor(
                    handle, (usb_device_get_device_qualifier_descriptor_struct_t *)param);
            }
            break;
#endif
        default:
            break;
    }

    return error;
}

/*!
 * @brief Application initialization function.
 *
 * This function initializes the application.
 *
 * @return None.
 */
void APPInit(void)
{
    USB_DeviceClockInit();
#if (defined(FSL_FEATURE_SOC_SYSMPU_COUNT) && (FSL_FEATURE_SOC_SYSMPU_COUNT > 0U))
    SYSMPU_Enable(SYSMPU, 0);
#endif /* FSL_FEATURE_SOC_SYSMPU_COUNT */

    g_composite.speed                            = USB_SPEED_FULL;
    g_composite.attach                           = 0U;
    g_composite.audioUnified.audioSpeakerHandle  = (class_handle_t)NULL;
    g_composite.audioUnified.audioRecorderHandle = (class_handle_t)NULL;
    g_composite.hidKeyboard.hidHandle            = (class_handle_t)NULL;
    g_composite.deviceHandle                     = NULL;

    if (kStatus_USB_Success !=
        USB_DeviceClassInit(CONTROLLER_ID, &g_UsbDeviceCompositeConfigList, &g_composite.deviceHandle))
    {
        usb_echo("USB device composite demo init failed\r\n");
        return;
    }
    else
    {
        usb_echo("USB device composite demo\r\n");
        usb_echo("Please Press switch(%s) to mute/unmute device audio speaker.\r\n", SW_GetName());

        g_composite.hidKeyboard.hidHandle            = g_UsbDeviceCompositeConfigList.config[0].classHandle;
        g_composite.audioUnified.audioRecorderHandle = g_UsbDeviceCompositeConfigList.config[1].classHandle;
        g_composite.audioUnified.audioSpeakerHandle  = g_UsbDeviceCompositeConfigList.config[2].classHandle;

        USB_DeviceAudioCompositeInit(&g_composite);
        USB_DeviceHidKeyboardInit(&g_composite);
    }

    /*Initialize audio interface and codec.*/
    HAL_AudioTxInit((hal_audio_handle_t)audioTxHandle, &audioTxConfig);
    HAL_AudioRxInit((hal_audio_handle_t)audioRxHandle, &audioRxConfig);
    BOARD_Codec_Init();
    AUDIO_DMA_EDMA_Start();

    USB_DeviceIsrEnable();

    /*Add one delay here to make the DP pull down long enough to allow host to detect the previous disconnection.*/
    SDK_DelayAtLeastUs(5000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    USB_DeviceRun(g_composite.deviceHandle);
}

#if defined(__CC_ARM) || (defined(__ARMCC_VERSION)) || defined(__GNUC__)
int main(void)
#else
void main(void)
#endif
{
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
    BOARD_I3C_ReleaseBus();
    BOARD_InitI3CPins();

    CLOCK_EnableClock(kCLOCK_InputMux);

    /* attach main clock to I3C (500MHz / 20 = 25MHz). */
    CLOCK_AttachClk(kMAIN_CLK_to_I3C_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivI3cClk, 20);

    /* attach AUDIO PLL clock to FLEXCOMM1 (I2S1) */
    CLOCK_AttachClk(kAUDIO_PLL_to_FLEXCOMM1);
    /* attach AUDIO PLL clock to FLEXCOMM3 (I2S3) */
    CLOCK_AttachClk(kAUDIO_PLL_to_FLEXCOMM3);

    /* attach AUDIO PLL clock to MCLK */
    CLOCK_AttachClk(kAUDIO_PLL_to_MCLK_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivMclkClk, 1);
    SYSCTL1->MCLKPINDIR = SYSCTL1_MCLKPINDIR_MCLKPINDIR_MASK;

    wm8904Config.i2cConfig.codecI2CSourceClock = CLOCK_GetI3cClkFreq();
    wm8904Config.mclk_HZ                       = CLOCK_GetMclkClkFreq();

    /* Set shared signal set 0: SCK, WS from Flexcomm1 */
    SYSCTL1->SHAREDCTRLSET[0] = SYSCTL1_SHAREDCTRLSET_SHAREDSCKSEL(1) | SYSCTL1_SHAREDCTRLSET_SHAREDWSSEL(1);
    /* Set flexcomm3 SCK, WS from shared signal set 0 */
    SYSCTL1->FCCTRLSEL[3] = SYSCTL1_FCCTRLSEL_SCKINSEL(1) | SYSCTL1_FCCTRLSEL_WSINSEL(1);
#if defined(USB_DEVICE_AUDIO_USE_SYNC_MODE) && (USB_DEVICE_AUDIO_USE_SYNC_MODE > 0U)
    /* attach AUDIO PLL clock to SCTimer input7. */
    CLOCK_AttachClk(kAUDIO_PLL_to_CTIMER0);
    g_composite.audioUnified.curAudioPllFrac = CLKCTL1->AUDIOPLL0NUM;
#endif
    BOARD_USB_AUDIO_KEYBOARD_Init();

    dmaTxConfig.instance            = DEMO_DMA_INSTANCE_INDEX;
    dmaTxConfig.channel             = DEMO_I2S_TX_CHANNEL;
    dmaTxConfig.priority            = kHAL_AudioDmaChannelPriority3;
    audioTxConfig.dmaConfig         = &dmaTxConfig;
    audioTxConfig.instance          = DEMO_I2S_TX_INSTANCE_INDEX;
    audioTxConfig.srcClock_Hz       = 24576000;
    audioTxConfig.sampleRate_Hz     = 48000;
    audioTxConfig.msaterSlave       = DEMO_I2S_TX_MODE;
    audioTxConfig.bclkPolarity      = kHAL_AudioSampleOnRisingEdge;
    audioTxConfig.frameSyncPolarity = kHAL_AudioBeginAtFallingEdge;
    audioTxConfig.frameSyncWidth    = kHAL_AudioFrameSyncWidthHalfFrame;
    audioTxConfig.dataFormat        = kHAL_AudioDataFormatI2sClassic;
    audioTxConfig.bitWidth          = (uint8_t)kHAL_AudioWordWidth16bits;
    audioTxConfig.lineChannels      = kHAL_AudioStereo;

    dmaRxConfig.instance            = DEMO_DMA_INSTANCE_INDEX;
    dmaRxConfig.channel             = DEMO_I2S_RX_CHANNEL;
    dmaRxConfig.priority            = kHAL_AudioDmaChannelPriority2;
    audioRxConfig.dmaConfig         = &dmaRxConfig;
    audioRxConfig.instance          = DEMO_I2S_RX_INSTANCE_INDEX;
    audioRxConfig.srcClock_Hz       = 24576000;
    audioRxConfig.sampleRate_Hz     = 48000;
    audioRxConfig.msaterSlave       = DEMO_I2S_RX_MODE;
    audioRxConfig.bclkPolarity      = kHAL_AudioSampleOnRisingEdge;
    audioRxConfig.frameSyncPolarity = kHAL_AudioBeginAtFallingEdge;
    audioRxConfig.frameSyncWidth    = kHAL_AudioFrameSyncWidthHalfFrame;
    audioRxConfig.dataFormat        = kHAL_AudioDataFormatI2sClassic;
    audioRxConfig.bitWidth          = (uint8_t)kHAL_AudioWordWidth16bits;
    audioRxConfig.lineChannels      = kHAL_AudioStereo;

    APPInit();

    while (1)
    {
        USB_DeviceHidKeyboardAction();

        USB_AudioCodecTask();

        USB_AudioSpeakerResetTask();

#if USB_DEVICE_CONFIG_USE_TASK
        USB_DeviceTaskFn(g_composite.deviceHandle);
#endif
    }
}
