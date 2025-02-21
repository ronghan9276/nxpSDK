/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016,2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __USB_AUDIO_H__
#define __USB_AUDIO_H__ 1

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define AUDIO_IN_SAMPLING_RATE_KHZ (48)
#define AUDIO_OUT_SAMPLING_RATE_KHZ (48)
#if (AUDIO_IN_SAMPLING_RATE_KHZ != AUDIO_OUT_SAMPLING_RATE_KHZ)
/*defalut in sample rate and out sample rate are same, if the sample setting is different,please remove this error
 manually, then check the AUDIO_SAMPLING_RATE .*/
#error This application default configuration requires AUDIO_IN_SAMPLING_RATE_KHZ eaual to AUDIO_OUT_SAMPLING_RATE_KHZ.
#endif
#define AUDIO_SAMPLING_RATE_16KHZ (16)
/*reference macro for audio sample macro */
#define AUDIO_IN_SAMPLING_RATE (AUDIO_IN_SAMPLING_RATE_KHZ * 1000)
#define AUDIO_OUT_SAMPLING_RATE (AUDIO_OUT_SAMPLING_RATE_KHZ * 1000)
/*if audio in and audio out sample rate are different, please use AUDIO_OUT_SAMPLING_RATE and AUDIO_IN_SAMPLING_RATE
to initialize out and in sample rate respectively*/
#define AUDIO_SAMPLING_RATE (AUDIO_OUT_SAMPLING_RATE)
/*audio data buffer depth*/
#define AUDIO_RECORDER_DATA_WHOLE_BUFFER_LENGTH (32)
#define AUDIO_SPEAKER_DATA_WHOLE_BUFFER_LENGTH (32)
#define AUDIO_BUFFER_UPPER_LIMIT(x) (((x)*5) / 8)
#define AUDIO_BUFFER_LOWER_LIMIT(x) (((x)*3) / 8)
#define AUDIO_CALCULATE_Ff_INTERVAL (1024)
#define TSAMFREQ2BYTES(f) (f & 0xFFU), ((f >> 8U) & 0xFFU), ((f >> 16U) & 0xFFU)
#define TSAMFREQ2BYTESHS(f) (f & 0xFFU), ((f >> 8U) & 0xFFU), ((f >> 16U) & 0xFFU), ((f >> 24U) & 0xFFU)
#define AUDIO_ADJUST_MIN_STEP (0x01)
#if defined(USB_DEVICE_AUDIO_USE_SYNC_MODE) && (USB_DEVICE_AUDIO_USE_SYNC_MODE > 0U)
/**********************************************************************
Audio PLL contants
      AUDIO_PLL_USB1_SOF_INTERVAL_COUNT
      The Audio PLL clock is 24.576Mhz, and the USB1_SOF_TOGGLE frequency is 4kHz when the device is attached,
      so AUDIO_PLL_USB1_SOF_INTERVAL_COUNT = (24576000 * 100 (stands for counter interval)) /4000 = 614400
      AUDIO_PLL_FRACTIONAL_CHANGE_STEP
      The Audio input clock is 24Mhz, and denominator is 4500, divider is 15 and PFD is 26.
      so AUDIO_PLL_FRACTIONAL_CHANGE_STEP = (24000000 * 100 (stands for counter interval) * 18) / (27000 * 26 * 15
*4000) + 1
**********************************************************************/
#define AUDIO_PLL_USB1_SOF_INTERVAL_COUNT (614400)  /* The USB1_SOF_TOGGLE's frequency is 4kHz. */
#define AUDIO_PLL_USB1_SOF_INTERVAL_COUNT1 (491520) /* The USB1_SOF_TOGGLE's frequency is 4kHz. */
#define AUDIO_PLL_FRACTIONAL_CHANGE_STEP (2)
#endif

#define MUTE_CODEC_TASK (1UL << 0U)
#define UNMUTE_CODEC_TASK (1UL << 1U)
#define VOLUME_CHANGE_TASK (1UL << 2U)

typedef struct _usb_audio_composite_struct
{
    usb_device_handle deviceHandle; /* USB device handle.                   */
    uint8_t copyProtect;
    uint8_t curMute;
    uint8_t curVolume[2];
    uint8_t minVolume[2];
    uint8_t maxVolume[2];
    uint8_t resVolume[2];
    uint8_t curBass;
    uint8_t minBass;
    uint8_t maxBass;
    uint8_t resBass;
    uint8_t curMid;
    uint8_t minMid;
    uint8_t maxMid;
    uint8_t resMid;
    uint8_t curTreble;
    uint8_t minTreble;
    uint8_t maxTreble;
    uint8_t resTreble;
    uint8_t curAutomaticGain;
    uint8_t curDelay[2];
    uint8_t minDelay[2];
    uint8_t maxDelay[2];
    uint8_t resDelay[2];
    uint8_t curLoudness;
    uint8_t curSamplingFrequency[3];
    uint8_t minSamplingFrequency[3];
    uint8_t maxSamplingFrequency[3];
    uint8_t resSamplingFrequency[3];
    uint8_t currentConfiguration;
    uint8_t currentInterfaceAlternateSetting[USB_AUDIO_COMPOSITE_INTERFACE_COUNT];
    uint8_t speed;
    uint8_t attach;
    volatile uint8_t startPlay;
    volatile uint8_t startPlayHalfFull;
    volatile uint8_t startRec;
    volatile uint8_t startRecHalfFull;
    volatile uint32_t tdReadNumberPlay;
    volatile uint32_t tdWriteNumberPlay;
    volatile uint32_t tdReadNumberRec;
    volatile uint32_t tdWriteNumberRec;
    volatile uint32_t audioSendCount;
    volatile uint32_t lastAudioSendCount;
    volatile uint32_t usbRecvCount;
    volatile uint32_t audioSendTimes;
    volatile uint32_t usbRecvTimes;
    volatile uint32_t audioRecvCount;
    volatile uint32_t usbSendTimes;
    volatile uint32_t speakerIntervalCount;
    volatile uint32_t speakerReservedSpace;
    volatile uint32_t recorderReservedSpace;
    volatile uint32_t timesFeedbackCalculate;
    volatile uint32_t speakerDetachOrNoInput;
    volatile uint32_t codecTask;
#if defined(USB_DEVICE_AUDIO_USE_SYNC_MODE) && (USB_DEVICE_AUDIO_USE_SYNC_MODE > 0U)
    volatile uint32_t curAudioPllFrac;
    volatile uint32_t audioPllTicksPrev;
    volatile int32_t audioPllTicksDiff;
    volatile int32_t audioPllTicksEma;
    volatile int32_t audioPllTickEmaFrac;
    volatile int32_t audioPllStep;
#endif
} usb_audio_composite_struct_t;

#endif /* __USB_AUDIO_GENERATOR_H__ */
