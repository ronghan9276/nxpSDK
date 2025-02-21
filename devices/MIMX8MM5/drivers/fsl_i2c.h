/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_I2C_H_
#define _FSL_I2C_H_

#include "fsl_common.h"

/*!
 * @addtogroup i2c_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief I2C driver version 2.0.4. */
#define FSL_I2C_DRIVER_VERSION (MAKE_VERSION(2, 0, 4))
/*@}*/

/*! @brief Timeout times for waiting flag. */
#ifndef I2C_WAIT_TIMEOUT
#define I2C_WAIT_TIMEOUT 0U /* Define to zero means keep waiting until the flag is assert/deassert. */
#endif

/*! @brief  I2C status return codes. */
enum _i2c_status
{
    kStatus_I2C_Busy            = MAKE_STATUS(kStatusGroup_I2C, 0), /*!< I2C is busy with current transfer. */
    kStatus_I2C_Idle            = MAKE_STATUS(kStatusGroup_I2C, 1), /*!< Bus is Idle. */
    kStatus_I2C_Nak             = MAKE_STATUS(kStatusGroup_I2C, 2), /*!< NAK received during transfer. */
    kStatus_I2C_ArbitrationLost = MAKE_STATUS(kStatusGroup_I2C, 3), /*!< Arbitration lost during transfer. */
    kStatus_I2C_Timeout         = MAKE_STATUS(kStatusGroup_I2C, 4), /*!< Timeout poling status flags. */
    kStatus_I2C_Addr_Nak        = MAKE_STATUS(kStatusGroup_I2C, 5), /*!< NAK received during the address probe. */
};

/*!
 * @brief I2C peripheral flags
 *
 * The following status register flags can be cleared:
 * - #kI2C_ArbitrationLostFlag
 * - #kI2C_IntPendingFlag
 *
 * @note These enumerations are meant to be OR'd together to form a bit mask.
 *
 */
enum _i2c_flags
{
    kI2C_ReceiveNakFlag        = I2C_I2SR_RXAK_MASK, /*!< I2C receive NAK flag. */
    kI2C_IntPendingFlag        = I2C_I2SR_IIF_MASK,  /*!< I2C interrupt pending flag. */
    kI2C_TransferDirectionFlag = I2C_I2SR_SRW_MASK,  /*!< I2C transfer direction flag. */
    kI2C_ArbitrationLostFlag   = I2C_I2SR_IAL_MASK,  /*!< I2C arbitration lost flag. */
    kI2C_BusBusyFlag           = I2C_I2SR_IBB_MASK,  /*!< I2C bus busy flag. */
    kI2C_AddressMatchFlag      = I2C_I2SR_IAAS_MASK, /*!< I2C address match flag. */
    kI2C_TransferCompleteFlag  = I2C_I2SR_ICF_MASK,
    /*!< I2C transfer complete flag. */
};

/*! @brief I2C feature interrupt source. */
enum _i2c_interrupt_enable
{
    kI2C_GlobalInterruptEnable = I2C_I2CR_IIEN_MASK, /*!< I2C global interrupt. */
};

/*! @brief The direction of master and slave transfers. */
typedef enum _i2c_direction
{
    kI2C_Write = 0x0U, /*!< Master transmits to the slave. */
    kI2C_Read  = 0x1U, /*!< Master receives from the slave. */
} i2c_direction_t;

/*! @brief I2C transfer control flag. */
enum _i2c_master_transfer_flags
{
    kI2C_TransferDefaultFlag = 0x0U,       /*!< A transfer starts with a start signal, stops with a stop signal. */
    kI2C_TransferNoStartFlag = 0x1U,       /*!< A transfer starts without a start signal, only support write only or
                                        write+read with no start flag, do not support read only with no start flag. */
    kI2C_TransferRepeatedStartFlag = 0x2U, /*!< A transfer starts with a repeated start signal. */
    kI2C_TransferNoStopFlag        = 0x4U, /*!< A transfer ends without a stop signal. */
};

/*! @brief I2C master user configuration. */
typedef struct _i2c_master_config
{
    bool enableMaster;     /*!< Enables the I2C peripheral at initialization time. */
    uint32_t baudRate_Bps; /*!< Baud rate configuration of I2C peripheral. */
} i2c_master_config_t;

/*! @brief I2C master handle typedef. */
typedef struct _i2c_master_handle i2c_master_handle_t;

/*! @brief I2C master transfer callback typedef. */
typedef void (*i2c_master_transfer_callback_t)(I2C_Type *base,
                                               i2c_master_handle_t *handle,
                                               status_t status,
                                               void *userData);

/*! @brief I2C master transfer structure. */
typedef struct _i2c_master_transfer
{
    uint32_t flags;            /*!< A transfer flag which controls the transfer. */
    uint8_t slaveAddress;      /*!< 7-bit slave address. */
    i2c_direction_t direction; /*!< A transfer direction, read or write. */
    uint32_t subaddress;       /*!< A sub address. Transferred MSB first. */
    uint8_t subaddressSize;    /*!< A size of the command buffer. */
    uint8_t *volatile data;    /*!< A transfer buffer. */
    volatile size_t dataSize;  /*!< A transfer size. */
} i2c_master_transfer_t;

/*! @brief I2C master handle structure. */
struct _i2c_master_handle
{
    i2c_master_transfer_t transfer;                    /*!< I2C master transfer copy. */
    size_t transferSize;                               /*!< Total bytes to be transferred. */
    uint8_t state;                                     /*!< A transfer state maintained during transfer. */
    i2c_master_transfer_callback_t completionCallback; /*!< A callback function called when the transfer is finished. */
    void *userData;                                    /*!< A callback parameter passed to the callback function. */
};

/*!
 * @brief Set of events sent to the callback for nonblocking slave transfers.
 *
 * These event enumerations are used for two related purposes. First, a bit mask created by OR'ing together
 * events is passed to I2C_SlaveTransferNonBlocking() to specify which events to enable.
 * Then, when the slave callback is invoked, it is passed the current event through its @a transfer
 * parameter.
 *
 * @note These enumerations are meant to be OR'd together to form a bit mask of events.
 */
typedef enum _i2c_slave_transfer_event
{
    kI2C_SlaveAddressMatchEvent = 0x01U, /*!< Received the slave address after a start or repeated start. */
    kI2C_SlaveTransmitEvent     = 0x02U, /*!< A callback is requested to provide data to transmit
                                                (slave-transmitter role). */
    kI2C_SlaveReceiveEvent = 0x04U,      /*!< A callback is requested to provide a buffer in which to place received
                                                 data (slave-receiver role). */
    kI2C_SlaveTransmitAckEvent = 0x08U,  /*!< A callback needs to either transmit an ACK or NACK. */
    kI2C_SlaveCompletionEvent  = 0x20U,  /*!< A stop was detected or finished transfer, completing the transfer. */
    /*! A bit mask of all available events. */
    kI2C_SlaveAllEvents =
        kI2C_SlaveAddressMatchEvent | kI2C_SlaveTransmitEvent | kI2C_SlaveReceiveEvent | kI2C_SlaveCompletionEvent,
} i2c_slave_transfer_event_t;

/*! @brief I2C slave handle typedef. */
typedef struct _i2c_slave_handle i2c_slave_handle_t;

/*! @brief I2C slave user configuration. */
typedef struct _i2c_slave_config
{
    bool enableSlave;      /*!< Enables the I2C peripheral at initialization time. */
    uint16_t slaveAddress; /*!< A slave address configuration. */
} i2c_slave_config_t;

/*! @brief I2C slave transfer structure. */
typedef struct _i2c_slave_transfer
{
    i2c_slave_transfer_event_t event; /*!< A reason that the callback is invoked. */
    uint8_t *volatile data;           /*!< A transfer buffer. */
    volatile size_t dataSize;         /*!< A transfer size. */
    status_t completionStatus;        /*!< Success or error code describing how the transfer completed. Only applies for
                                         #kI2C_SlaveCompletionEvent. */
    size_t transferredCount; /*!< A number of bytes actually transferred since the start or since the last repeated
                                start. */
} i2c_slave_transfer_t;

/*! @brief I2C slave transfer callback typedef. */
typedef void (*i2c_slave_transfer_callback_t)(I2C_Type *base, i2c_slave_transfer_t *xfer, void *userData);

/*! @brief I2C slave handle structure. */
struct _i2c_slave_handle
{
    volatile uint8_t state;                 /*!< A transfer state maintained during transfer. */
    i2c_slave_transfer_t transfer;          /*!< I2C slave transfer copy. */
    uint32_t eventMask;                     /*!< A mask of enabled events. */
    i2c_slave_transfer_callback_t callback; /*!< A callback function called at the transfer event. */
    void *userData;                         /*!< A callback parameter passed to the callback. */
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /*_cplusplus. */

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initializes the I2C peripheral. Call this API to ungate the I2C clock
 * and configure the I2C with master configuration.
 *
 * @note This API should be called at the beginning of the application.
 * Otherwise, any operation to the I2C module can cause a hard fault
 * because the clock is not enabled. The configuration structure can be custom filled
 * or it can be set with default values by using the I2C_MasterGetDefaultConfig().
 * After calling this API, the master is ready to transfer.
 * This is an example.
 * @code
 * i2c_master_config_t config = {
 * .enableMaster = true,
 * .baudRate_Bps = 100000
 * };
 * I2C_MasterInit(I2C0, &config, 12000000U);
 * @endcode
 *
 * @param base I2C base pointer
 * @param masterConfig A pointer to the master configuration structure
 * @param srcClock_Hz I2C peripheral clock frequency in Hz
 */
void I2C_MasterInit(I2C_Type *base, const i2c_master_config_t *masterConfig, uint32_t srcClock_Hz);

/*!
 * @brief De-initializes the I2C master peripheral. Call this API to gate the I2C clock.
 * The I2C master module can't work unless the I2C_MasterInit is called.
 * @param base I2C base pointer
 */
void I2C_MasterDeinit(I2C_Type *base);

/*!
 * @brief  Sets the I2C master configuration structure to default values.
 *
 * The purpose of this API is to get the configuration structure initialized for use in the I2C_MasterInit().
 * Use the initialized structure unchanged in the I2C_MasterInit() or modify
 * the structure before calling the I2C_MasterInit().
 * This is an example.
 * @code
 * i2c_master_config_t config;
 * I2C_MasterGetDefaultConfig(&config);
 * @endcode
 * @param masterConfig A pointer to the master configuration structure.
 */
void I2C_MasterGetDefaultConfig(i2c_master_config_t *masterConfig);

/*!
 * @brief Initializes the I2C peripheral. Call this API to ungate the I2C clock
 * and initialize the I2C with the slave configuration.
 *
 * @note This API should be called at the beginning of the application.
 * Otherwise, any operation to the I2C module can cause a hard fault
 * because the clock is not enabled. The configuration structure can partly be set
 * with default values by I2C_SlaveGetDefaultConfig() or it can be custom filled by the user.
 * This is an example.
 * @code
 * i2c_slave_config_t config = {
 * .enableSlave = true,
 * .slaveAddress = 0x1DU,
 * };
 * I2C_SlaveInit(I2C0, &config);
 * @endcode
 *
 * @param base I2C base pointer
 * @param slaveConfig A pointer to the slave configuration structure
 * @param srcClock_Hz I2C peripheral clock frequency in Hz
 */
void I2C_SlaveInit(I2C_Type *base, const i2c_slave_config_t *slaveConfig);

/*!
 * @brief De-initializes the I2C slave peripheral. Calling this API gates the I2C clock.
 * The I2C slave module can't work unless the I2C_SlaveInit is called to enable the clock.
 * @param base I2C base pointer
 */
void I2C_SlaveDeinit(I2C_Type *base);

/*!
 * @brief  Sets the I2C slave configuration structure to default values.
 *
 * The purpose of this API is to get the configuration structure initialized for use in the I2C_SlaveInit().
 * Modify fields of the structure before calling the I2C_SlaveInit().
 * This is an example.
 * @code
 * i2c_slave_config_t config;
 * I2C_SlaveGetDefaultConfig(&config);
 * @endcode
 * @param slaveConfig A pointer to the slave configuration structure.
 */
void I2C_SlaveGetDefaultConfig(i2c_slave_config_t *slaveConfig);

/*!
 * @brief Enables or disables the I2C peripheral operation.
 *
 * @param base I2C base pointer
 * @param enable Pass true to enable and false to disable the module.
 */
static inline void I2C_Enable(I2C_Type *base, bool enable)
{
    if (enable)
    {
        base->I2CR |= I2C_I2CR_IEN_MASK;
    }
    else
    {
        base->I2CR &= ~I2C_I2CR_IEN_MASK;
    }
}

/* @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the I2C status flags.
 *
 * @param base I2C base pointer
 * @return status flag, use status flag to AND #_i2c_flags to get the related status.
 */
static inline uint32_t I2C_MasterGetStatusFlags(I2C_Type *base)
{
    return base->I2SR;
}

/*!
 * @brief Clears the I2C status flag state.
 *
 * The following status register flags can be cleared kI2C_ArbitrationLostFlag and kI2C_IntPendingFlag.
 *
 * @param base I2C base pointer
 * @param statusMask The status flag mask, defined in type i2c_status_flag_t.
 *      The parameter can be any combination of the following values:
 *          @arg kI2C_ArbitrationLostFlag
 *          @arg kI2C_IntPendingFlagFlag
 */
static inline void I2C_MasterClearStatusFlags(I2C_Type *base, uint32_t statusMask)
{
    base->I2SR = (uint8_t)statusMask;
}

/*!
 * @brief Gets the I2C status flags.
 *
 * @param base I2C base pointer
 * @return status flag, use status flag to AND #_i2c_flags to get the related status.
 */
static inline uint32_t I2C_SlaveGetStatusFlags(I2C_Type *base)
{
    return I2C_MasterGetStatusFlags(base);
}

/*!
 * @brief Clears the I2C status flag state.
 *
 * The following status register flags can be cleared kI2C_ArbitrationLostFlag and kI2C_IntPendingFlag
 *
 * @param base I2C base pointer
 * @param statusMask The status flag mask, defined in type i2c_status_flag_t.
 *      The parameter can be any combination of the following values:
 *          @arg kI2C_IntPendingFlagFlag
 */
static inline void I2C_SlaveClearStatusFlags(I2C_Type *base, uint32_t statusMask)
{
    I2C_MasterClearStatusFlags(base, statusMask);
}

/* @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables I2C interrupt requests.
 *
 * @param base I2C base pointer
 * @param mask interrupt source
 *     The parameter can be combination of the following source if defined:
 *     @arg kI2C_GlobalInterruptEnable
 *     @arg kI2C_StopDetectInterruptEnable/kI2C_StartDetectInterruptEnable
 *     @arg kI2C_SdaTimeoutInterruptEnable
 */
void I2C_EnableInterrupts(I2C_Type *base, uint32_t mask);

/*!
 * @brief Disables I2C interrupt requests.
 *
 * @param base I2C base pointer
 * @param mask interrupt source
 *     The parameter can be combination of the following source if defined:
 *     @arg kI2C_GlobalInterruptEnable
 *     @arg kI2C_StopDetectInterruptEnable/kI2C_StartDetectInterruptEnable
 *     @arg kI2C_SdaTimeoutInterruptEnable
 */
void I2C_DisableInterrupts(I2C_Type *base, uint32_t mask);

/* @} */
/*!
 * @name Bus Operations
 * @{
 */

/*!
 * @brief Sets the I2C master transfer baud rate.
 *
 * @param base I2C base pointer
 * @param baudRate_Bps the baud rate value in bps
 * @param srcClock_Hz Source clock
 */
void I2C_MasterSetBaudRate(I2C_Type *base, uint32_t baudRate_Bps, uint32_t srcClock_Hz);

/*!
 * @brief Sends a START on the I2C bus.
 *
 * This function is used to initiate a new master mode transfer by sending the START signal.
 * The slave address is sent following the I2C START signal.
 *
 * @param base I2C peripheral base pointer
 * @param address 7-bit slave device address.
 * @param direction Master transfer directions(transmit/receive).
 * @retval kStatus_Success Successfully send the start signal.
 * @retval kStatus_I2C_Busy Current bus is busy.
 */
status_t I2C_MasterStart(I2C_Type *base, uint8_t address, i2c_direction_t direction);

/*!
 * @brief Sends a STOP signal on the I2C bus.
 *
 * @retval kStatus_Success Successfully send the stop signal.
 * @retval kStatus_I2C_Timeout Send stop signal failed, timeout.
 */
status_t I2C_MasterStop(I2C_Type *base);

/*!
 * @brief Sends a REPEATED START on the I2C bus.
 *
 * @param base I2C peripheral base pointer
 * @param address 7-bit slave device address.
 * @param direction Master transfer directions(transmit/receive).
 * @retval kStatus_Success Successfully send the start signal.
 * @retval kStatus_I2C_Busy Current bus is busy but not occupied by current I2C master.
 */
status_t I2C_MasterRepeatedStart(I2C_Type *base, uint8_t address, i2c_direction_t direction);

/*!
 * @brief Performs a polling send transaction on the I2C bus.
 *
 * @param base  The I2C peripheral base pointer.
 * @param txBuff The pointer to the data to be transferred.
 * @param txSize The length in bytes of the data to be transferred.
 * @param flags Transfer control flag to decide whether need to send a stop, use kI2C_TransferDefaultFlag
 *  to issue a stop and kI2C_TransferNoStop to not send a stop.
 * @retval kStatus_Success Successfully complete the data transmission.
 * @retval kStatus_I2C_ArbitrationLost Transfer error, arbitration lost.
 * @retval kStataus_I2C_Nak Transfer error, receive NAK during transfer.
 */
status_t I2C_MasterWriteBlocking(I2C_Type *base, const uint8_t *txBuff, size_t txSize, uint32_t flags);

/*!
 * @brief Performs a polling receive transaction on the I2C bus.
 *
 * @note The I2C_MasterReadBlocking function stops the bus before reading the final byte.
 * Without stopping the bus prior for the final read, the bus issues another read, resulting
 * in garbage data being read into the data register.
 *
 * @param base I2C peripheral base pointer.
 * @param rxBuff The pointer to the data to store the received data.
 * @param rxSize The length in bytes of the data to be received.
 * @param flags Transfer control flag to decide whether need to send a stop, use kI2C_TransferDefaultFlag
 *  to issue a stop and kI2C_TransferNoStop to not send a stop.
 * @retval kStatus_Success Successfully complete the data transmission.
 * @retval kStatus_I2C_Timeout Send stop signal failed, timeout.
 */
status_t I2C_MasterReadBlocking(I2C_Type *base, uint8_t *rxBuff, size_t rxSize, uint32_t flags);

/*!
 * @brief Performs a polling send transaction on the I2C bus.
 *
 * @param base  The I2C peripheral base pointer.
 * @param txBuff The pointer to the data to be transferred.
 * @param txSize The length in bytes of the data to be transferred.
 * @retval kStatus_Success Successfully complete the data transmission.
 * @retval kStatus_I2C_ArbitrationLost Transfer error, arbitration lost.
 * @retval kStataus_I2C_Nak Transfer error, receive NAK during transfer.
 */
status_t I2C_SlaveWriteBlocking(I2C_Type *base, const uint8_t *txBuff, size_t txSize);

/*!
 * @brief Performs a polling receive transaction on the I2C bus.
 *
 * @param base I2C peripheral base pointer.
 * @param rxBuff The pointer to the data to store the received data.
 * @param rxSize The length in bytes of the data to be received.
 */
status_t I2C_SlaveReadBlocking(I2C_Type *base, uint8_t *rxBuff, size_t rxSize);

/*!
 * @brief Performs a master polling transfer on the I2C bus.
 *
 * @note The API does not return until the transfer succeeds or fails due
 * to arbitration lost or receiving a NAK.
 *
 * @param base I2C peripheral base address.
 * @param xfer Pointer to the transfer structure.
 * @retval kStatus_Success Successfully complete the data transmission.
 * @retval kStatus_I2C_Busy Previous transmission still not finished.
 * @retval kStatus_I2C_Timeout Transfer error, wait signal timeout.
 * @retval kStatus_I2C_ArbitrationLost Transfer error, arbitration lost.
 * @retval kStataus_I2C_Nak Transfer error, receive NAK during transfer.
 */
status_t I2C_MasterTransferBlocking(I2C_Type *base, i2c_master_transfer_t *xfer);

/* @} */

/*!
 * @name Transactional
 * @{
 */

/*!
 * @brief Initializes the I2C handle which is used in transactional functions.
 *
 * @param base I2C base pointer.
 * @param handle pointer to i2c_master_handle_t structure to store the transfer state.
 * @param callback pointer to user callback function.
 * @param userData user parameter passed to the callback function.
 */
void I2C_MasterTransferCreateHandle(I2C_Type *base,
                                    i2c_master_handle_t *handle,
                                    i2c_master_transfer_callback_t callback,
                                    void *userData);

/*!
 * @brief Performs a master interrupt non-blocking transfer on the I2C bus.
 *
 * @note Calling the API returns immediately after transfer initiates. The user needs
 * to call I2C_MasterGetTransferCount to poll the transfer status to check whether
 * the transfer is finished. If the return status is not kStatus_I2C_Busy, the transfer
 * is finished.
 *
 * @param base I2C base pointer.
 * @param handle pointer to i2c_master_handle_t structure which stores the transfer state.
 * @param xfer pointer to i2c_master_transfer_t structure.
 * @retval kStatus_Success Successfully start the data transmission.
 * @retval kStatus_I2C_Busy Previous transmission still not finished.
 * @retval kStatus_I2C_Timeout Transfer error, wait signal timeout.
 */
status_t I2C_MasterTransferNonBlocking(I2C_Type *base, i2c_master_handle_t *handle, i2c_master_transfer_t *xfer);

/*!
 * @brief Gets the master transfer status during a interrupt non-blocking transfer.
 *
 * @param base I2C base pointer.
 * @param handle pointer to i2c_master_handle_t structure which stores the transfer state.
 * @param count Number of bytes transferred so far by the non-blocking transaction.
 * @retval kStatus_InvalidArgument count is Invalid.
 * @retval kStatus_Success Successfully return the count.
 */
status_t I2C_MasterTransferGetCount(I2C_Type *base, i2c_master_handle_t *handle, size_t *count);

/*!
 * @brief Aborts an interrupt non-blocking transfer early.
 *
 * @note This API can be called at any time when an interrupt non-blocking transfer initiates
 * to abort the transfer early.
 *
 * @param base I2C base pointer.
 * @param handle pointer to i2c_master_handle_t structure which stores the transfer state
 * @retval kStatus_I2C_Timeout Timeout during polling flag.
 * @retval kStatus_Success Successfully abort the transfer.
 */
status_t I2C_MasterTransferAbort(I2C_Type *base, i2c_master_handle_t *handle);

/*!
 * @brief Master interrupt handler.
 *
 * @param base I2C base pointer.
 * @param i2cHandle pointer to i2c_master_handle_t structure.
 */
void I2C_MasterTransferHandleIRQ(I2C_Type *base, void *i2cHandle);

/*!
 * @brief Initializes the I2C handle which is used in transactional functions.
 *
 * @param base I2C base pointer.
 * @param handle pointer to i2c_slave_handle_t structure to store the transfer state.
 * @param callback pointer to user callback function.
 * @param userData user parameter passed to the callback function.
 */
void I2C_SlaveTransferCreateHandle(I2C_Type *base,
                                   i2c_slave_handle_t *handle,
                                   i2c_slave_transfer_callback_t callback,
                                   void *userData);

/*!
 * @brief Starts accepting slave transfers.
 *
 * Call this API after calling the I2C_SlaveInit() and I2C_SlaveTransferCreateHandle() to start processing
 * transactions driven by an I2C master. The slave monitors the I2C bus and passes events to the
 * callback that was passed into the call to I2C_SlaveTransferCreateHandle(). The callback is always invoked
 * from the interrupt context.
 *
 * The set of events received by the callback is customizable. To do so, set the @a eventMask parameter to
 * the OR'd combination of #i2c_slave_transfer_event_t enumerators for the events you wish to receive.
 * The #kI2C_SlaveTransmitEvent and #kLPI2C_SlaveReceiveEvent events are always enabled and do not need
 * to be included in the mask. Alternatively, pass 0 to get a default set of only the transmit and
 * receive events that are always enabled. In addition, the #kI2C_SlaveAllEvents constant is provided as
 * a convenient way to enable all events.
 *
 * @param base The I2C peripheral base address.
 * @param handle Pointer to #i2c_slave_handle_t structure which stores the transfer state.
 * @param eventMask Bit mask formed by OR'ing together #i2c_slave_transfer_event_t enumerators to specify
 *      which events to send to the callback. Other accepted values are 0 to get a default set of
 *      only the transmit and receive events, and #kI2C_SlaveAllEvents to enable all events.
 *
 * @retval #kStatus_Success Slave transfers were successfully started.
 * @retval #kStatus_I2C_Busy Slave transfers have already been started on this handle.
 */
status_t I2C_SlaveTransferNonBlocking(I2C_Type *base, i2c_slave_handle_t *handle, uint32_t eventMask);

/*!
 * @brief Aborts the slave transfer.
 *
 * @note This API can be called at any time to stop slave for handling the bus events.
 *
 * @param base I2C base pointer.
 * @param handle pointer to i2c_slave_handle_t structure which stores the transfer state.
 */
void I2C_SlaveTransferAbort(I2C_Type *base, i2c_slave_handle_t *handle);

/*!
 * @brief Gets the slave transfer remaining bytes during a interrupt non-blocking transfer.
 *
 * @param base I2C base pointer.
 * @param handle pointer to i2c_slave_handle_t structure.
 * @param count Number of bytes transferred so far by the non-blocking transaction.
 * @retval kStatus_InvalidArgument count is Invalid.
 * @retval kStatus_Success Successfully return the count.
 */
status_t I2C_SlaveTransferGetCount(I2C_Type *base, i2c_slave_handle_t *handle, size_t *count);

/*!
 * @brief Slave interrupt handler.
 *
 * @param base I2C base pointer.
 * @param i2cHandle pointer to i2c_slave_handle_t structure which stores the transfer state
 */
void I2C_SlaveTransferHandleIRQ(I2C_Type *base, void *i2cHandle);

/* @} */
#if defined(__cplusplus)
}
#endif /*_cplusplus. */
/*@}*/

#endif /* _FSL_I2C_H_*/
