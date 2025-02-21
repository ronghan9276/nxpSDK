/*! *********************************************************************************
* \defgroup GATT_SERVER GATT - Server APIs
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* Copyright 2016-2020 NXP
* All rights reserved.
* 
* \file
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef GATT_SERVER_INTERFACE_H
#define GATT_SERVER_INTERFACE_H

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "gatt_interface.h"

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/
/*! GATT Server Event type enumeration */
typedef enum {
    gEvtMtuChanged_c                        = 0x00, /*!< ATT_MTU was changed after the MTU exchange. */
    gEvtHandleValueConfirmation_c           = 0x01, /*!< Received a Handle Value Confirmation from the Client. */
    gEvtAttributeWritten_c                  = 0x02, /*!< An attribute registered with GattServer_RegisterHandlesForWriteNotifications was written.
                                                         After receiving this event, application must call GattServer_SendAttributeWrittenStatus.
                                                         Application must write the Attribute in the Database if it considers necessary. */
    gEvtCharacteristicCccdWritten_c         = 0x03, /*!< A CCCD was written. Application should save the CCCD value with Gap_SaveCccd. */
    gEvtAttributeWrittenWithoutResponse_c   = 0x04, /*!< An attribute registered with GattServer_RegisterHandlesForWriteNotifications was written without response (with ATT Write Command).
                                                         Application must write the Attribute Value in the Database if it considers necessary. */
    gEvtError_c                             = 0x05, /*!< An error appeared during a Server-initiated procedure. */
    gEvtLongCharacteristicWritten_c         = 0x06, /*!< A long characteristic was written. */
    gEvtAttributeRead_c                     = 0x07, /*!< An attribute registered with GattServer_RegisterHandlesForReadNotifications is being read.
                                                         After receiving this event, application must call GattServer_SendAttributeReadStatus. */
} gattServerEventType_t;

/*! GATT Server MTU Changed Event structure */
typedef struct {
    uint16_t newMtu;    /*!< Value of the agreed ATT_MTU for this connection. */
} gattServerMtuChangedEvent_t;

/*! GATT Server Attribute Written Event structure */
typedef struct {
    uint16_t    handle;         /*!< Handle of the attribute. */
    uint16_t    cValueLength;   /*!< Length of the attribute value array. */
    uint8_t*    aValue;         /*!< Attribute value array attempted to be written. */
} gattServerAttributeWrittenEvent_t;

/*! GATT Server Long Characteristic Written Event structure */
typedef struct {
    uint16_t    handle;         /*!< Handle of the Characteristic Value. */
    uint16_t    cValueLength;   /*!< Length of the value written. */
    uint8_t*    aValue;         /*!< Pointer to the attribute value in the database. */
} gattServerLongCharacteristicWrittenEvent_t;

/*! GATT Server CCCD Written Event structure */
typedef struct {
    uint16_t          handle;       /*!< Handle of the CCCD attribute. */
    gattCccdFlags_t   newCccd;      /*!< New value of the CCCD. */
} gattServerCccdWrittenEvent_t;

/*! GATT Server Attribute Read Event structure */
typedef struct {
    uint16_t    handle;         /*!< Handle of the attribute. */
} gattServerAttributeReadEvent_t;

/*! Server-initiated procedure type enumeration */
typedef enum {
    gSendAttributeWrittenStatus_c,      /*!< Procedure initiated by GattServer_SendAttributeWrittenStatus. */
    gSendAttributeReadStatus_c,         /*!< Procedure initiated by GattServer_SendAttributeReadStatus. */
    gSendNotification_c,                /*!< Procedure initiated by GattServer_SendNotification. */
    gSendIndication_c                   /*!< Procedure initiated by GattServer_SendIndication. */
} gattServerProcedureType_t;

/*! Server-initiated procedure error structure */
typedef struct {
    gattServerProcedureType_t   procedureType;  /*!< Procedure that generated error. */
    bleResult_t                 error;          /*!< Error generated. */
} gattServerProcedureError_t;

/*! GATT Server Event structure: type + data. */
typedef struct {
    gattServerEventType_t eventType;    /*!< Event type. */
    union {
        gattServerMtuChangedEvent_t                 mtuChangedEvent;        /*!< For event type gEvtMtuChanged_c: the new value of the ATT_MTU. */
        gattServerAttributeWrittenEvent_t           attributeWrittenEvent;  /*!< For event types gEvtAttributeWritten_c, gEvtAttributeWrittenWithoutResponse_c: handle and value of the attempted write. */
        gattServerCccdWrittenEvent_t                charCccdWrittenEvent;   /*!< For event type gEvtCharacteristicCccdWritten_c: handle and value of the CCCD. */
        gattServerProcedureError_t                  procedureError;         /*!< For event type gEvtError_c: error that terminated a Server-initiated procedure. */
        gattServerLongCharacteristicWrittenEvent_t  longCharWrittenEvent;   /*!< For event type gEvtLongCharacteristicWritten_c: handle and value. */
        gattServerAttributeReadEvent_t              attributeReadEvent;     /*!< For event types gEvtAttributeRead_c: handle of the attempted read. */
    } eventData;                            /*!< Event data : selected according to event type. */
} gattServerEvent_t;

/*! GATT Server Callback prototype */
typedef void (*gattServerCallback_t)
(
    deviceId_t          deviceId,       /*!< Device ID identifying the active connection. */
    gattServerEvent_t*  pServerEvent    /*!< Server event. */
);

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
* \brief  Initializes the GATT Server module.
*
* \return  gBleSuccess_c or error.
*
* \remarks Application does not need to call this function if Gatt_Init() is called.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
bleResult_t GattServer_Init(void);

/*! *********************************************************************************
* \brief  Installs an application callback for the GATT Server module.
*
* \param[in] callback Application-defined callback to be triggered by this module.
*
* \return  gBleSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
bleResult_t GattServer_RegisterCallback
(
    gattServerCallback_t callback
);

/*! *********************************************************************************
* \brief  Registers the attribute handles that will be notified through the
* GATT Server callback when a GATT Client attempts to modify the attributes' values.
*
* \param[in] handleCount        Number of handles in array.
* \param[in] aAttributeHandles  Array of handles.
*
* \return  gBleSuccess_c or error.
*
* \remarks The application is responsible for actually writing the new requested values
* in the GATT database. Service and profile-specific control-point characteristics
* should have their value handles in this list so that the application may get notified
* when a GATT Client writes it.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
bleResult_t GattServer_RegisterHandlesForWriteNotifications
(
    uint8_t           handleCount,
    const uint16_t*   aAttributeHandles
);

/*! *********************************************************************************
* \brief  Unregisters the attribute handles that will be notified through the
* GATT Server callback when a GATT Client attempts to modify the attributes' values.
*
* \param[in] handleCount        Number of handles in array.
* \param[in] aAttributeHandles  Array of handles.
*
* \return  gBleSuccess_c or error.
*
* \remarks To unregister all the list, pass 0 count and NULL.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
bleResult_t GattServer_UnregisterHandlesForWriteNotifications
(
    uint8_t           handleCount,
    const uint16_t*   aAttributeHandles
);

/*! *********************************************************************************
* \brief  Responds to an intercepted attribute write operation.
*
* \param[in] deviceId           The device ID of the connected peer.
* \param[in] attributeHandle    The attribute handle that was written.
* \param[in] status             The status of the write operation.
*                               If this parameter is equal to gAttErrCodeNoError_c then
*                               an ATT Write Response will be sent to the peer.
*                               Else an ATT Error Response with the provided status will
*                               be sent to the peer.
*
* \remarks This function must be called by the application when receiving the gEvtAttributeWritten_c Server event.
* The status value may contain application- or profile-defined error codes.
*
********************************************************************************** */
bleResult_t GattServer_SendAttributeWrittenStatus
(
    deviceId_t      deviceId,
    uint16_t        attributeHandle, 
    uint8_t         status
);

/*! *********************************************************************************
* \brief  Registers the attribute handles that will be notified through the
* GATT Server callback when a GATT Client attempts to read the attributes' values.
*
* \param[in] handleCount        Number of handles in array.
* \param[in] aAttributeHandles  Array of handles.
*
* \return  gBleSuccess_c or error.
*
* \remarks The application may modify the attribute's value in the GATT Database before
* sending the response with GattServer_SendAttributeReadStatus.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
bleResult_t GattServer_RegisterHandlesForReadNotifications
(
    uint8_t           handleCount,
    const uint16_t*   aAttributeHandles
);

/*! *********************************************************************************
* \brief  Unregisters the attribute handles that will be notified through the
* GATT Server callback when a GATT Client attempts to read the attributes' values.
*
* \param[in] handleCount        Number of handles in array.
* \param[in] aAttributeHandles  Array of handles.
*
* \return  gBleSuccess_c or error.
*
* \remarks To unregister all the list, pass 0 count and NULL.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
bleResult_t GattServer_UnregisterHandlesForReadNotifications
(
    uint8_t           handleCount,
    const uint16_t*   aAttributeHandles
);

/*! *********************************************************************************
* \brief  Responds to an intercepted attribute read operation.
*
* \param[in] deviceId           The device ID of the connected peer.
* \param[in] attributeHandle    The attribute handle that was being read.
* \param[in] status             The status of the read operation.
*                               If this parameter is equal to gAttErrCodeNoError_c then
*                               an ATT Read Response will be sent to the peer containing
*                               the attribute value from the GATT Database.
*                               Else an ATT Error Response with the provided status will
*                               be sent to the peer.
*
* \remarks This function must be called by the application when receiving the gEvtAttributeRead_c Server event.
* The status value may contain application- or profile-defined error codes.
*
********************************************************************************** */
bleResult_t GattServer_SendAttributeReadStatus
(
    deviceId_t      deviceId,
    uint16_t        attributeHandle, 
    uint8_t         status
);

/*! *********************************************************************************
* \brief  Sends a notification to a peer GATT Client using the Characteristic Value
* from the GATT Database.
*
* \param[in] deviceId           The device ID of the connected peer.
* \param[in] handle             Handle of the Value of the Characteristic to be notified.
*
* \return  gBleSuccess_c or error.
*
********************************************************************************** */
bleResult_t GattServer_SendNotification
(
    deviceId_t              deviceId,
    uint16_t                handle
);

/*! *********************************************************************************
* \brief  Sends an indication to a peer GATT Client using the Characteristic Value
* from the GATT Database.
*
* \param[in] deviceId           The device ID of the connected peer.
* \param[in] handle             Handle of the Value of the Characteristic to be indicated.
*
* \return  gBleSuccess_c or error.
*
********************************************************************************** */
bleResult_t GattServer_SendIndication
(
    deviceId_t              deviceId,
    uint16_t                handle
);

/*! *********************************************************************************
* \brief  Sends a notification to a peer GATT Client with data given as parameter, 
* ignoring the GATT Database.
*
* \param[in] deviceId           The device ID of the connected peer.
* \param[in] handle             Handle of the Value of the Characteristic to be notified.
* \param[in] valueLength        Length of data to be notified.
* \param[in] aValue             Data to be notified.
*
* \return  gBleSuccess_c or error.
*
********************************************************************************** */
bleResult_t GattServer_SendInstantValueNotification
(
    deviceId_t              deviceId,
    uint16_t                handle,
    uint16_t                valueLength,
    const uint8_t*          aValue
);

/*! *********************************************************************************
* \brief  Sends an indication to a peer GATT Client with data given as parameter, 
* ignoring the GATT Database.
*
* \param[in] deviceId           The device ID of the connected peer.
* \param[in] handle             Handle of the Value of the Characteristic to be indicated.
* \param[in] valueLength        Length of data to be indicated.
* \param[in] aValue             Data to be indicated.
*
* \return  gBleSuccess_c or error.
*
********************************************************************************** */
bleResult_t GattServer_SendInstantValueIndication
(
    deviceId_t              deviceId,
    uint16_t                handle,
    uint16_t                valueLength,
    const uint8_t*          aValue
);

/*! *********************************************************************************
* \brief  Registers all GATT DB dynamic attribute handles with unique value buffers 
* to be notified through the GATT Server callback when a GATT Client attempts to 
* read/write the attributes' values.
*
* \param[in] bWrite   Enables/Disables write notifications.
* \param[in] bRead    Enables/Disables read notifications.
*
* \return  gBleSuccess_c or error.
*
* \remarks This function executes synchronously.
* \remarks This function should be called when adding GATT DB unique value buffer
*  characteristics or descriptors.
*
********************************************************************************** */
bleResult_t GattServer_RegisterUniqueHandlesForNotifications
(
    bool_t bWrite,
    bool_t bRead
);

#ifdef __cplusplus
}
#endif

#endif /* GATT_SERVER_INTERFACE_H */

/*! *********************************************************************************
* @}
********************************************************************************** */
