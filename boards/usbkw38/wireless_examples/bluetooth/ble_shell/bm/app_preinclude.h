/*! *********************************************************************************
 * \defgroup app
 * @{
 ********************************************************************************** */
/*!
 * Copyright 2019 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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
#define gKeyBoardSupported_d        0

/* Specifies the number of required LEDs for the LED module */
#define gLEDsOnTargetBoardCnt_c 2

/* Specifies if the LED operation is inverted. LED On = GPIO Set */
#define gLED_InvertedMode_d     1


/*! *********************************************************************************
 * 	App Configuration
 ********************************************************************************** */


/* Enable Advertising Extension shell commands */
#define BLE_SHELL_AE_SUPPORT    1

#if BLE_SHELL_AE_SUPPORT

#define gGapSimultaneousEAChainedReports_c     2

/* Enable Shell Break Key (CTRL+C) */
#define SHELL_BREAK_KEY         1

/* Allow one connection on legacy set and one on the extended set */
#define gAppMaxConnections_c           (2U)

/* User defined payload pattern and length of extended advertising data */
#define SHELL_EXT_ADV_DATA_PATTERN      "\n\rEXTENDED_ADVERTISING_DATA_LARGE_PAYLOAD"
#define SHELL_EXT_ADV_DATA_SIZE         500U
#endif /* BLE_SHELL_AE_SUPPORT */

/*! Repeated Attempts - Mitigation for pairing attacks */
#define gRepeatedAttempts_d             0
/*! *********************************************************************************
 *     Framework Configuration
 ********************************************************************************** */
/* enable NVM to be used as non volatile storage management by the host stack */
#define gAppUseNvm_d                    1

/* Defines Rx Buffer Size for Serial Manager */
#define gSerialMgrRxBufSize_c   1000

/* Defines Tx Queue Size for Serial Manager */
#define gSerialMgrTxQueueSize_c 30

/* Defines Size for Serial Manager Task*/
#define gSerialTaskStackSize_c  500

#if BLE_SHELL_AE_SUPPORT
#define AppPoolsDetails_c \
         _block_size_  32  _number_of_blocks_    6 _eol_  \
         _block_size_  64  _number_of_blocks_    3 _eol_  \
         _block_size_ 128  _number_of_blocks_    8 _eol_  \
         _block_size_ 1200  _number_of_blocks_   10 _eol_
#else
/* Defines pools by block size and number of blocks. Must be aligned to 4 bytes.*/
#define AppPoolsDetails_c \
         _block_size_  32  _number_of_blocks_    6 _eol_  \
         _block_size_  64  _number_of_blocks_    3 _eol_  \
         _block_size_ 128  _number_of_blocks_    8 _eol_  \
         _block_size_ 324  _number_of_blocks_    50 _eol_  \
         _block_size_ 512  _number_of_blocks_    8 _eol_
#endif /* BLE_SHELL_AE_SUPPORT */
/* Defines number of timers needed by the application */
#if gRepeatedAttempts_d
#define gTmrApplicationTimers_c         5
#else
#define gTmrApplicationTimers_c         4
#endif

/* Set this define TRUE if the PIT frequency is an integer number of MHZ */
#define gTMR_PIT_FreqMultipleOfMHZ_d    0

/* Enables / Disables the precision timers platform component */
#define gTimestamp_Enabled_d            1

/* Enable/Disable Low Power Timer */
#define gTMR_EnableLowPowerTimers       0

/* Number of commands the shell supports*/
#define SHELL_MAX_COMMANDS  6
/*! *********************************************************************************
 *     RTOS Configuration
 ********************************************************************************** */
/* Defines number of OS events used */
#define osNumberOfEvents        6

/*! *********************************************************************************
 *     BLE Stack Configuration
 ********************************************************************************** */

/* Enable Dynamic GATT database */
#define gGattDbDynamic_d    1
#define gUseHciTransport_d  0
/*! *********************************************************************************
 *     BLE LL Configuration
 ***********************************************************************************/
/*  ble_ll_config.h file lists the parameters with their default values. User can override
 *    the parameter here by defining the parameter to a user defined value. */
#define gAppExtAdvEnable_d                      1
#define gLlScanPeriodicAdvertiserListSize_c     8

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
