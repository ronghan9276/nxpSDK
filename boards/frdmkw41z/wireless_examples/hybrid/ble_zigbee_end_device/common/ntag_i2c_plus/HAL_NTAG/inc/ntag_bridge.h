/*
* Copyright (c) 2016-2018, NXP Semiconductor
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*/
#ifndef _NTAG_BRIDGE_H_
#define _NTAG_BRIDGE_H_
/** @file ntag_bridge.h
 * \brief Public interface for using an NTAG I2C tag as I2C<->NFC bridge.
 */

/***********************************************************************/
/* INCLUDES                                                            */
/***********************************************************************/
#include "EmbeddedTypes.h"
#include "ntag_driver.h"

/***********************************************************************/
/* DEFINES                                                             */
/***********************************************************************/

/***********************************************************************/
/* TYPES                                                               */
/***********************************************************************/
typedef enum
{
    RF_SWITCHED_OFF_00b = (0x0 << 4),
    HALT_OR_RF_SWITCHED_OFF_01b = (0x1 << 4),
    LAST_NDEF_BLOCK_READ_OR_RF_SWITCHED_OFF_10b = (0x2 << 4),
    I2C_LAST_DATA_READ_OR_WRITTEN_OR_RF_SWITCHED_OFF_11b = (0x3 << 4)
} NTAG_FD_OFF_FUNCTIONS_T;

typedef enum
{
    RF_SWITCHED_ON_00b = (0x0 << 2),
    FIRST_VALID_SoF_01b = (0x1 << 2),
    SELECTION_OF_TAG_10b = (0x2 << 2),
    DATA_READY_BY_I2C_OR_DATA_READ_BY_RF_11b = (0x3 << 2)
} NTAG_FD_ON_FUNCTIONS_T;

typedef enum
{
    RF_TO_I2C = NTAG_NC_REG_MASK_TRANSFER_DIR,
    I2C_TO_RF = 0
} NTAG_TRANSFER_DIR_T;

typedef enum
{
#ifdef HAVE_NTAG_INTERRUPT
    NTAG_EVENT_FD_PIN_HI_INTERRUPT,
    NTAG_EVENT_FD_PIN_LO_INTERRUPT,
    NTAG_EVENT_RF_FIELD_PRESENT_INTERRUPT,
    NTAG_EVENT_RF_FIELD_NOT_PRESENT_INTERRUPT,
    NTAG_EVENT_HALT_STATE,
    NTAG_EVENT_NDEF_DATA_READ_INTERRUPT,
    NTAG_EVENT_SoF,
    NTAG_EVENT_SELECT,
    NTAG_EVENT_RF_WROTE_SRAM_INTERRUPT,
    NTAG_EVENT_RF_READ_SRAM_INTERRUPT,
#endif
    NTAG_EVENT_NDEF_DATA_READ_POLLED,
    NTAG_EVENT_RF_FIELD_PRESENT_POLLED,
    NTAG_EVENT_RF_FIELD_NOT_PRESENT_POLLED,
    NTAG_EVENT_RF_WROTE_SRAM_POLLED,
    NTAG_EVENT_RF_READ_SRAM_POLLED
} NTAG_EVENT_T;

/***********************************************************************/
/* GLOBAL VARIABLES                                                    */
/***********************************************************************/

/***********************************************************************/
/* GLOBAL FUNCTION PROTOTYPES                                          */
/***********************************************************************/

/**
 * \brief wait for selected event
 *
 *	This functions waits until the selected event occurs or the timeout value is
 *	reached. See NTAG_EVENT_T for possible events to be waited on.
 *	If you want to use the Interrupted Events set the FD function accordingly
 *	before calling this function. Notice that some Interrupted Events are
 *	indistinguishable, so it will trigger at a false event.
 *
 * \param	ntag      	handle to identify the NTAG device instance
 * \param	event     	event to be waited for
 * \param	timeout_ms	timeout value in ms
 * \param   set_fd_pin_function   when using an INTERRUPT EVENT
 * 								  if true FD_ON/FD_OFF is set to the according funtion priore to waiting for the event.
 * 								  if false nothing is done, so you should set the FD Pin function prior to calling this.
 * 								  when using an POLLING EVENT this param is ignored
 *
 * \return			TRUE on timeout
 */
bool_t NTAG_WaitForEvent(NTAG_HANDLE_T ntag, NTAG_EVENT_T event, uint32_t timeout_ms, bool_t set_fd_pin_function);

/**
 * \brief enable/disable the I2C_RST
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	on		true enables the I2C_RST , false disable the I2C_RST
 *
 * \return	error code as defined in ntag_defines.h
 */
bool_t NTAG_SetI2CRstOnOff(NTAG_HANDLE_T ntag, bool_t on);

/**
 * \brief get the status of the I2C_RST
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	on		status of the I2C_RST, true is on, false is off
 *
 * \return	error code as defined in ntag_defines.h
 */
bool_t NTAG_GetI2CRstOnOff(NTAG_HANDLE_T ntag, bool_t *on);

/**
 * \brief Locks the write of the Configuration from RF, note that this is
 *        one time programmable
 *
 * \param	ntag	handle to identify the NTAG device instance
 *
 * \return			TRUE on failure*
 */
bool_t NTAG_SetRFConfigurationWrite(NTAG_HANDLE_T ntag);

/**
 * \brief Gets the Lock status of the RF Configuration Lock
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	locked	true RF writes to the Configuration is locked
 * 					false RF writes to the Configuration is possible
 *
 * \return			TRUE on failure*
 */
bool_t NTAG_GetRFConfigurationLock(NTAG_HANDLE_T ntag, bool_t *locked);

/**
 * \brief Locks the write of the Configuration from I2C, note that this is
 *        one time programmable
 *
 * \param	ntag	handle to identify the NTAG device instance
 *
 * \return			TRUE on failure*
 */
bool_t NTAG_SetI2CConfigurationWrite(NTAG_HANDLE_T ntag);

/**
 * \brief Gets the Lock status of the I2C Configuration Lock
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	locked	true I2C writes to the Configuration is locked
 * 					false I2C writes to the Configuration is possible
 *
 * \return			TRUE on failure*
 */
bool_t NTAG_GetI2CConfigurationLock(NTAG_HANDLE_T ntag, bool_t *locked);

/**
 * \brief get the I2C_CLOCK_STR
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	clk		the I2C_CLOCK_STR setting
 *
 * \return			TRUE on failure*
 */
bool_t NTAG_GetI2CClockStr(NTAG_HANDLE_T ntag, bool_t *clk);

/**
 * \brief Sets the I2C_LOCKED bit to 0 to free the LOCK immediately
 *
 * \param	ntag	handle to identify the NTAG device instance
 *
 * \return			TRUE on failure*
 */
bool_t NTAG_ReleaseI2CLocked(NTAG_HANDLE_T ntag);

/**
 * \brief set the transfer direction
 *
 * If the PT direction is already the desired direction nothing is done.
 * If the Pthru is switched on, it will be switched off and back on after the direction change.
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	dir		Direction of the transfer
 *
 * \return			TRUE on failure*
 */
bool_t NTAG_SetTransferDir(NTAG_HANDLE_T ntag, NTAG_TRANSFER_DIR_T dir);

/**
 * \brief get the transfer direction
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	dir		Direction of the transfer
 *
 * \return			TRUE on failure*
 */
bool_t NTAG_GetTransferDir(NTAG_HANDLE_T ntag, NTAG_TRANSFER_DIR_T *dir);

/**
 * \brief set the FD ON function
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	func	Function which should be set
 *
 * \return			TRUE on failure*
 */
bool_t NTAG_SetFDOnFunction(NTAG_HANDLE_T ntag, NTAG_FD_ON_FUNCTIONS_T func);

/**
 * \brief get the FD ON function
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	func	Function which is set
 *
 * \return			TRUE on failure*
 */
bool_t NTAG_GetFDOnFunction(NTAG_HANDLE_T ntag, NTAG_FD_ON_FUNCTIONS_T *func);

/**
 * \brief set the FD OFF functionFF
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	func	Function which should be set
 *
 * \return			TRUE on failure*
 */
bool_t NTAG_SetFDOffFunction(NTAG_HANDLE_T ntag, NTAG_FD_OFF_FUNCTIONS_T func);

/**
 * \brief get the FD OFF function
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	func	Function which is set
 *
 * \return			TRUE on failure*
 */
bool_t NTAG_GetFDOffFunction(NTAG_HANDLE_T ntag, NTAG_FD_OFF_FUNCTIONS_T *func);

/**
 * \brief enable/disable the I2C<->NFC bridge
 *
 * Activates the pass-through mode, that uses the NTAG's 64 Byte SRAM
 * for communication between a NFC device and the I2C bus
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	on		true enables the Pthru , false disable the Pthru
 *
 * \return	error code as defined in ntag_defines.h
 */
bool_t NTAG_SetPthruOnOff(NTAG_HANDLE_T ntag, bool_t on);

/**
 * \brief get the status of the Pthru
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	on		status of Pthru, true is on, false is off
 *
 * \return	error code as defined in ntag_defines.h
 */
bool_t NTAG_GetPthruOnOff(NTAG_HANDLE_T ntag, bool_t *on);

/**
 * \brief enable/disable SRAM projection to user memory addresses
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	on		true enables the SRAM Mirror , false disable the SRAM Mirror
 *
 * \return			TRUE on failure*
 */
bool_t NTAG_SetSRAMMirrorOnOff(NTAG_HANDLE_T ntag, bool_t on);

/**
 * \brief get the status of the SRAM Mirror to user memory
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	on		status of the SRAM Mirror, true is on, false is off
 *
 * \return			TRUE on failure*
 */
bool_t NTAG_GetSRAMMirrorOnOff(NTAG_HANDLE_T ntag, bool_t *on);

/**
 * \brief change the LAST_NDEF_BLOCK
 *
 *  Change the first block of user memory when using the LAST_NDEF_BLOCK.
 *  Granularity is 4 pages(4bytes each), so block * 4 is the real page address.
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	block	block address, 0x74 is the highest allowed value
 * \return			TRUE on failure*
 */
bool_t NTAG_SetLastNDEFBlock(NTAG_HANDLE_T ntag, uint8_t block);

/**
 * \brief get the LAST_NDEF_BLOCK
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	block	LAST_NDEF_BLOCK
 *
 * \return			TRUE on failure*
 */
bool_t NTAG_GetLastNDEFBlock(NTAG_HANDLE_T ntag, uint8_t *block);

/**
 * \brief change the first block of user memory for the SRAM Mirror
 *
 *  Change the first block of user memory when mirroring the SRAM.
 *  Granularity is 4 pages(4bytes each), so block * 4 is the real page address.
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	block	block to which the SRAM should be mirrored
 * \return			TRUE on failure*
 */
bool_t NTAG_SetSRAMMirrorBlock(NTAG_HANDLE_T ntag, uint8_t block);

/**
 * \brief get the first block of user memory for the SRAM Mirror
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	block	block to which the SRAM is mirrored
 * \return			TRUE on failure*
 */
bool_t NTAG_GetSRAMMirrorBlock(NTAG_HANDLE_T ntag, uint8_t *block);

/**
 * \brief change the value of the watchdog timer
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	time	new time value of the watchdog timer
 * \return			TRUE on failure*
 */
bool_t NTAG_SetWatchdogTime(NTAG_HANDLE_T ntag, uint16_t time);

/**
 * \brief get the value of the watchdog timer
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	time	Watchdog time
 * \return			TRUE on failure*
 */
bool_t NTAG_GetWatchdogTime(NTAG_HANDLE_T ntag, uint16_t *time);

#endif /* _NTAG_BRIDGE_H_ */
