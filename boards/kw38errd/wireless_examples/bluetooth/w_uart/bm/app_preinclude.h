/*! *********************************************************************************
 * \defgroup app
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
 * Copyright 2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */


#ifndef _APP_PREINCLUDE_H_
#define _APP_PREINCLUDE_H_

/*!
 *  Application specific configuration file only
 *  Board Specific Configuration shall be added to board.h file directly such as :
 *  - Number of button on the board,
 *  - Number of LEDs,
 *  - etc...
 */
/*! *********************************************************************************
 *     Board Configuration
 ********************************************************************************** */
 /* Defines the number of required keys for the keyboard module */
#if !defined(gBoard_ExtPaChlCtrl_d) || (gBoard_ExtPaChlCtrl_d <= 0)
#define gKBD_KeysCount_c        2
#else
#define gKBD_KeysCount_c        1
#endif

/* Specifies the number of required LEDs for the LED module */
#define gLEDsOnTargetBoardCnt_c 1

#define  gLEDBlipEnabled_d     0

/* Specifies if the LED operation is inverted. LED On = GPIO Set */
#define gLED_InvertedMode_d     1

/*! *********************************************************************************
 *     App Configuration
 ********************************************************************************** */
/*! Maximum number of connections supported for this application */
#define gAppMaxConnections_c    8

/*! Enable/disable use of bonding capability */
#define gAppUseBonding_d        0

/*! Enable/disable use of pairing procedure */
#define gAppUsePairing_d        0

/*! Enable/disable use of privacy */
#define gAppUsePrivacy_d        0

#define gPasskeyValue_c    999999

/*! Enable/disable central role */
#define gWuart_CentralRole_c 1

/*! Enable/disable peripheral role */
#define gWuart_PeripheralRole_c 1

/*! Repeated Attempts - Mitigation for pairing attacks */
#define gRepeatedAttempts_d             0
/*! *********************************************************************************
 *     Framework Configuration
 ********************************************************************************** */
/* enable NVM to be used as non volatile storage management by the host stack */
#define gAppUseNvm_d            0

/* Defines pools by block size and number of blocks. Must be aligned to 4 bytes.*/
#define AppPoolsDetails_c \
         _block_size_  32  _number_of_blocks_     4 _eol_  \
         _block_size_  80  _number_of_blocks_     6 _eol_  \
         _block_size_ 288  _number_of_blocks_    16 _eol_  \
         _block_size_ 312  _number_of_blocks_     1 _eol_  \
         _block_size_ 400  _number_of_blocks_     2 _eol_

/* Defines number of timers needed by the application */
#if gRepeatedAttempts_d
#define gTmrApplicationTimers_c         5
#else
#define gTmrApplicationTimers_c         4
#endif

/* Set this define TRUE if the PIT frequency is an integer number of MHZ */
#define gTMR_PIT_FreqMultipleOfMHZ_d    0

/* Enables / Disables the precision timers platform component */
#define gTimestamp_Enabled_d            0

/* Enable/Disable Low Power Timer */
#define gTMR_EnableLowPowerTimers       0

/*! Enables / Disables the DCDC platform component */
#define gDCDC_Enabled_d 0

/*! Default DCDC Mode used by the application gDCDC_Buck_c or gDCDC_Bypass_c */
#define APP_DCDC_MODE gDCDC_Bypass_c

/*! Enables / Disables the usage of the external power amplifier */
#define gBoard_ExtPaSupport_d           1

/*! *********************************************************************************
 *     RTOS Configuration
 ********************************************************************************** */
/* Defines number of OS events used */
#define osNumberOfEvents        5

/*! *********************************************************************************
 *     BLE Stack Configuration
 ********************************************************************************** */
#define gMaxServicesCount_d             6
#define gMaxServiceCharCount_d          6

/*! *********************************************************************************
 *     BLE LL Configuration
 ***********************************************************************************/
/*  ble_ll_config.h file lists the parameters with their default values. User can override
 *    the parameter here by defining the parameter to a user defined value. */

/*
 * Specific configuration of LL pools by block size and number of blocks for this application.
 * Optimized using the MEM_OPTIMIZE_BUFFER_POOL feature in MemManager,
 * we find that the most optimized combination for LL buffers.
 *
 * If LlPoolsDetails_c is not defined, default LL buffer configuration in app_preinclude_common.h
 * will be applied.
 */

/* Include common configuration file and board configuration file */
#include "app_preinclude_common.h"
#endif /* _APP_PREINCLUDE_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */
