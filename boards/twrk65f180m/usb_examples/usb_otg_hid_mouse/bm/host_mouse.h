/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016, 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HOST_MOUSE_H_
#define _HOST_MOUSE_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define USB_HOST_OTG_POLL_HNP_INTERVAL (100)
/*! @brief buffer for receiving report descriptor and data */
#define HID_BUFFER_SIZE 200

/*! @brief host app device attach/detach status */
typedef enum _usb_host_app_state
{
    kStatus_DEV_Idle = 0, /*!< there is no device attach/detach */
    kStatus_DEV_Attached, /*!< device is attached */
    kStatus_DEV_Detached, /*!< device is detached */
} usb_host_app_state_t;

/*! @brief host app run status */
typedef enum _usb_host_mouse_run_state
{
    kUSB_HostHidRunIdle = 0, /*!< idle */
    kUSB_HostHidRunIdlePoll,
    kUSB_HostHidRunParseOtgDescriptor,      /*!< parse device descriptor */
    kUSB_HostHidRunWaitParseOtgDescriptor,  /*!< wait the set feature transfer */
    kUSB_HostHidRunSetInterface,            /*!< execute set interface code */
    kUSB_HostHidRunWaitSetInterface,        /*!< wait set interface done */
    kUSB_HostHidRunSetInterfaceDone,        /*!< set interface is done, execute next step */
    kUSB_HostHidRunWaitSetIdle,             /*!< wait set idle done */
    kUSB_HostHidRunSetIdleDone,             /*!< set idle is done, execute next step */
    kUSB_HostHidRunWaitGetReportDescriptor, /*!< wait get report descriptor done */
    kUSB_HostHidRunGetReportDescriptorDone, /*!< get report descriptor is done, execute next step */
    kUSB_HostHidRunWaitSetProtocol,         /*!< wait set protocol done */
    kUSB_HostHidRunSetProtocolDone,         /*!< set protocol is done, execute next step */
    kUSB_HostHidRunWaitDataReceived,        /*!< wait interrupt in data */
    kUSB_HostHidRunDataReceived,            /*!< interrupt in data received */
    kUSB_HostHidRunPrimeDataReceive,        /*!< prime interrupt in receive */
} usb_host_mouse_run_state_t;

/*! @brief USB host mouse instance structure */
typedef struct _usb_host_mouse_instance
{
    usb_host_handle hostHandle;
    usb_host_configuration_handle configHandle; /*!< the mouse's configuration handle */
    usb_device_handle deviceHandle;             /*!< the mouse's device handle */
    usb_host_class_handle classHandle;          /*!< the mouse's class handle */
    usb_host_interface_handle interfaceHandle;  /*!< the mouse's interface handle */
    usb_host_transfer_t *HNPTransfer;
    uint32_t pollHNPInterval;
    uint8_t pollHNPValue;
    uint8_t deviceState;    /*!< device attach/detach status */
    uint8_t prevState;      /*!< device attach/detach previous status */
    uint8_t runState;       /*!< mouse application run status */
    uint8_t runWaitState;   /*!< mouse application wait status, go to next run status when the wait status success */
    uint16_t maxPacketSize; /*!< Interrupt in max packet size */
    uint8_t *mouseBuffer;   /*!< use to receive report descriptor and data */
} usb_host_mouse_instance_t;

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
* @brief host mouse task function.
*
* This function implements the host mouse action, it is used to create task.
*
* @param param   the host mouse instance pointer.
*/
extern void USB_HostHidMouseTask(void);

/*!
 * @brief host mouse callback function.
 *
 * This function should be called in the host callback function.
 *
 * @param deviceHandle        device handle.
 * @param configurationHandle attached device's configuration descriptor information.
 * @param eventCode           callback event code, please reference to enumeration host_event_t.
 *
 * @retval kStatus_USB_Success              The host is initialized successfully.
 * @retval kStatus_USB_NotSupported         The configuration don't contain hid mouse interface.
 */
extern usb_status_t USB_HostHidMouseEvent(usb_device_handle deviceHandle,
                                          usb_host_configuration_handle configurationHandle,
                                          uint32_t eventCode);

#endif /* _HOST_MOUSE_H_ */
