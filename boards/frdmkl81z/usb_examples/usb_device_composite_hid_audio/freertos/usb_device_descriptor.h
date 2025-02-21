/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __USB_DEVICE_DESCRIPTOR_H__
#define __USB_DEVICE_DESCRIPTOR_H__

/*******************************************************************************
* Definitions
******************************************************************************/

#define USB_DEVICE_SPECIFIC_BCD_VERSION (0x0200U)
#define USB_DEVICE_DEMO_BCD_VERSION (0x0101U)

#define USB_DEVICE_MAX_POWER (0x32U)

/* usb descriptor length */
#define USB_DESCRIPTOR_LENGTH_CONFIGURATION_ALL (sizeof(g_UsbDeviceConfigurationDescriptor))
#define USB_ENDPOINT_AUDIO_DESCRIPTOR_LENGTH (9)
#define USB_DESCRIPTOR_LENGTH_HID (9U)
#define USB_DESCRIPTOR_LENGTH_HID_MOUSE_REPORT (sizeof(g_UsbDeviceHidMouseReportDescriptor))
#define USB_DESCRIPTOR_LENGTH_AC_INTERRUPT_ENDPOINT (9)
#define USB_AUDIO_CONTROL_INTERFACE_HEADER_LENGTH (9)
#define USB_AUDIO_INPUT_TERMINAL_ONLY_DESC_SIZE (12)
#define USB_AUDIO_OUTPUT_TERMINAL_ONLY_DESC_SIZE (9)
#define USB_AUDIO_FEATURE_UNIT_ONLY_DESC_SIZE (9)
#define USB_AUDIO_STREAMING_IFACE_DESC_SIZE (7)
#define USB_AUDIO_STREAMING_ENDP_DESC_SIZE (7)
#define USB_AUDIO_STREAMING_TYPE_I_DESC_SIZE (11)

/* Configuration, interface and endpoint. */
#define USB_DEVICE_CONFIGURATION_COUNT (1)
#define USB_DEVICE_STRING_COUNT (3)
#define USB_DEVICE_LANGUAGE_COUNT (1)
#define USB_DEVICE_INTERFACE_COUNT (3)
#define USB_AUDIO_ENDPOINT_COUNT (1)

#define USB_AUDIO_GENERATOR_CONFIGURE_INDEX (1)
#define USB_COMPOSITE_CONFIGURE_INDEX (1)
#define USB_AUDIO_CONTROL_INTERFACE_INDEX (0)
#define USB_AUDIO_STREAM_INTERFACE_INDEX (1)
#define USB_HID_MOUSE_INTERFACE_INDEX (2)

#define USB_AUDIO_STREAM_ENDPOINT_COUNT (1)
#define USB_AUDIO_CONTROL_ENDPOINT_COUNT (1)
#define USB_HID_MOUSE_ENDPOINT_COUNT (1)

#define USB_AUDIO_STREAM_ENDPOINT (4)
#define USB_AUDIO_CONTROL_ENDPOINT (1)
#define USB_HID_MOUSE_ENDPOINT (2)

#define USB_AUDIO_GENERATOR_INTERFACE_COUNT \
    (USB_AUDIO_GENERATOR_CONTROL_INTERFACE_COUNT + USB_AUDIO_GENERATOR_STREAM_INTERFACE_COUNT)
#define USB_AUDIO_GENERATOR_CONTROL_INTERFACE_COUNT (1)
#define USB_AUDIO_GENERATOR_STREAM_INTERFACE_COUNT (1)
#define USB_HID_MOUSE_INTERFACE_COUNT (1)

/* Packet size and interval. */
#define HS_INTERRUPT_IN_PACKET_SIZE (8)
#define FS_INTERRUPT_IN_PACKET_SIZE (8)
#define HS_INTERRUPT_IN_INTERVAL (0x07)
#define FS_INTERRUPT_IN_INTERVAL (0x08)
#if defined(AUDIO_DATA_SOURCE_DMIC) && (AUDIO_DATA_SOURCE_DMIC > 0U)
#define HS_ISO_IN_ENDP_PACKET_SIZE (32)
#define FS_ISO_IN_ENDP_PACKET_SIZE (32)
#else
#define HS_ISO_IN_ENDP_PACKET_SIZE (8)
#define FS_ISO_IN_ENDP_PACKET_SIZE (8)
#endif
#define HS_ISO_IN_ENDP_INTERVAL (0x04)
#define FS_ISO_IN_ENDP_INTERVAL (0x01)
#define ISO_IN_ENDP_INTERVAL (0x01)

/* String descriptor length. */
#define USB_DESCRIPTOR_LENGTH_STRING0 (sizeof(g_UsbDeviceString0))
#define USB_DESCRIPTOR_LENGTH_STRING1 (sizeof(g_UsbDeviceString1))
#define USB_DESCRIPTOR_LENGTH_STRING2 (sizeof(g_UsbDeviceString2))

/* Class code. */
#define USB_DEVICE_CLASS (0x00)
#define USB_DEVICE_SUBCLASS (0x00)
#define USB_DEVICE_PROTOCOL (0x00)

#define USB_AUDIO_CLASS (0x01)
#define USB_SUBCLASS_AUDIOCONTROL (0x01)
#define USB_SUBCLASS_AUDIOSTREAM (0x02)
#define USB_AUDIO_PROTOCOL (0x00)

#define USB_HID_MOUSE_CLASS (0x03)
#define USB_HID_MOUSE_SUBCLASS (0x01)
#define USB_HID_MOUSE_PROTOCOL (0x02)

#define USB_AUDIO_FORMAT_TYPE_I (0x01)
#define USB_AUDIO_STREAM_ENDPOINT_DESCRIPTOR (0x25)
#define USB_AUDIO_EP_GENERAL_DESCRIPTOR_SUBTYPE (0x01)

#define USB_AUDIO_CONTROL_INPUT_TERMINAL_ID (0x01)
#define USB_AUDIO_CONTROL_FEATURE_UNIT_ID (0x02)
#define USB_AUDIO_CONTROL_OUTPUT_TERMINAL_ID (0x03)

/*******************************************************************************
* API
******************************************************************************/
/*!
 * @brief USB device set speed function.
 *
 * This function sets the speed of the USB device.
 *
 * @param handle The USB device handle.
 * @param speed Speed type. USB_SPEED_HIGH/USB_SPEED_FULL/USB_SPEED_LOW.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
extern usb_status_t USB_DeviceSetSpeed(usb_device_handle handle, uint8_t speed);
/*!
 * @brief USB device get device descriptor function.
 *
 * This function gets the device descriptor of the USB device.
 *
 * @param handle The USB device handle.
 * @param deviceDescriptor The pointer to the device descriptor structure.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceGetDeviceDescriptor(usb_device_handle handle,
                                           usb_device_get_device_descriptor_struct_t *deviceDescriptor);
/*!
 * @brief USB device get configuration descriptor function.
 *
 * This function gets the configuration descriptor of the USB device.
 *
 * @param handle The USB device handle.
 * @param configurationDescriptor The pointer to the configuration descriptor structure.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceGetConfigurationDescriptor(
    usb_device_handle handle, usb_device_get_configuration_descriptor_struct_t *configurationDescriptor);

usb_status_t USB_DeviceGetStringDescriptor(usb_device_handle handle,
                                           usb_device_get_string_descriptor_struct_t *stringDescriptor);

usb_status_t USB_DeviceGetHidReportDescriptor(usb_device_handle handle,
                                              usb_device_get_hid_report_descriptor_struct_t *hidReportDescriptor);
#if (defined(USB_DEVICE_CONFIG_CV_TEST) && (USB_DEVICE_CONFIG_CV_TEST > 0U))
/* Get device qualifier descriptor request */
usb_status_t USB_DeviceGetDeviceQualifierDescriptor(
    usb_device_handle handle, usb_device_get_device_qualifier_descriptor_struct_t *deviceQualifierDescriptor);
#endif

#endif
