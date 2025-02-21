/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __USB_VIDEO_CAMERA_H__
#define __USB_VIDEO_CAMERA_H__

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0U)
#define CONTROLLER_ID kUSB_ControllerEhci0
#endif
#if defined(USB_DEVICE_CONFIG_KHCI) && (USB_DEVICE_CONFIG_KHCI > 0U)
#define CONTROLLER_ID kUSB_ControllerKhci0
#endif

#define USB_DEVICE_INTERRUPT_PRIORITY (3U)

typedef struct _usb_video_virtual_camera_struct
{
    usb_device_handle deviceHandle;
    class_handle_t videoHandle;
    uint32_t currentMaxPacketSize;
    uint8_t *imageBuffer;
    uint32_t imageBufferLength;
    usb_device_video_probe_and_commit_controls_struct_t probeStruct;
    usb_device_video_probe_and_commit_controls_struct_t commitStruct;
    usb_device_video_still_probe_and_commit_controls_struct_t stillProbeStruct;
    usb_device_video_still_probe_and_commit_controls_struct_t stillCommitStruct;
    uint32_t imageIndex;
    uint32_t currentTime;
    uint32_t classRequestBuffer[(sizeof(usb_device_video_probe_and_commit_controls_struct_t) >> 2U) + 1U];
    uint32_t imagePosition;
    uint8_t image_header[sizeof(usb_device_video_mjpeg_payload_header_struct_t)];
    uint8_t currentFrameId;
    uint8_t waitForNewInterval;
    uint8_t currentStreamInterfaceAlternateSetting;
    uint8_t probeLength;
    uint8_t commitLength;
    uint8_t probeInfo;
    uint8_t commitInfo;
    uint8_t stillProbeLength;
    uint8_t stillCommitLength;
    uint8_t stillProbeInfo;
    uint8_t stillCommitInfo;
    uint8_t stillImageTransmission;
    volatile uint8_t stillImageTriggerControl;
    uint8_t fullBufferIndex;
    uint8_t currentConfiguration;
    uint8_t currentInterfaceAlternateSetting[USB_VIDEO_CAMERA_INTERFACE_COUNT];
    uint8_t speed;
    uint8_t attach;
} usb_video_flexio_camera_struct_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#endif /* __USB_VIDEO_CAMERA_H__ */
