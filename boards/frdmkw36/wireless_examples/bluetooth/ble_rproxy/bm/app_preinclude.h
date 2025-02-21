/*! *********************************************************************************
 * \defgroup app
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
* Copyright 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2019 NXP
* All rights reserved.
*
* \file
*
* This file is the app configuration file which is pre included.
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */


#ifndef APP_PREINCLUDE_H
#define APP_PREINCLUDE_H

/*! *********************************************************************************
 *  Board Configuration
 ********************************************************************************** */
 /* Defines the number of available keys for the keyboard module */
#define gKBD_KeysCount_c        2

/* Specifies the number of physical LEDs on the target board */
#define gLEDsOnTargetBoardCnt_c 4

/* Specifies if the LED operation is inverted. LED On = GPIO Set */
#define gLED_InvertedMode_d     1


/*! *********************************************************************************
 *  App Configuration
 ********************************************************************************** */

/*! Number of connections supported by the application */
#define gAppMaxConnections_c   2

/*! Number of credit-based channels supported */
#define gL2caMaxLeCbChannels_c         2

/*! Enable/disable use of bonding capability */
#define gAppUseBonding_d   0

/*! Enable/disable use of pairing procedure */
#define gAppUsePairing_d   0

/*! Enable/disable use of privacy */
#define gAppUsePrivacy_d   0

#define gPasskeyValue_c                999999

#if (gAppUseBonding_d) && (!gAppUsePairing_d)
  #error "Enable pairing to make use of bonding"
#endif

/*! Repeated Attempts - Mitigation for pairing attacks */
#define gRepeatedAttempts_d             0

/* Number of devices identified by address to keep track of for Repeated Attempts */
#define gRepeatedAttemptsNoOfDevices_c  (4U)

/* Minimum timeout after a pairing failure before the same peer can re-attempt it */
#define gRepeatedAttemptsTimeoutMin_c   (10U) /* seconds */

/* Maximum timeout after a pairing failure before the same peer can re-attempt it */
#define gRepeatedAttemptsTimeoutMax_c   (640U) /* seconds */
/*! *********************************************************************************
 *  Framework Configuration
 ********************************************************************************** */
/* enable NVM to be used as non volatile storage management by the host stack */
#define gAppUseNvm_d                    1

/* Defines pools by block size and number of blocks. Must be aligned to 4 bytes.*/
#define AppPoolsDetails_c \
         _block_size_   64 _number_of_blocks_  10 _eol_ \
         _block_size_  112 _number_of_blocks_   5 _eol_ \
         _block_size_  160 _number_of_blocks_   2 _eol_ \
         _block_size_  248 _number_of_blocks_   2 _eol_ \
         _block_size_  312 _number_of_blocks_   2 _eol_ \
         _block_size_  400 _number_of_blocks_   2 _eol_ \
         _block_size_  544 _number_of_blocks_   1 _eol_ \
         _block_size_ 1024 _number_of_blocks_   1 _eol_

/* Defines number of timers needed by the application */
#if gRepeatedAttempts_d
#define gTmrApplicationTimers_c         5
#else
#define gTmrApplicationTimers_c         4
#endif

/* Defines number of timers needed by the protocol stack */
#if defined(gAppMaxConnections_c) && defined(gL2caMaxLeCbChannels_c)
    #define gTmrStackTimers_c (3 + (gAppMaxConnections_c * 2) + gL2caMaxLeCbChannels_c)
#else
    #define gTmrStackTimers_c (7)
#endif

/* Set this define TRUE if the PIT frequency is an integer number of MHZ */
#define gTMR_PIT_FreqMultipleOfMHZ_d    0

/* Enables / Disables the precision timers platform component */
#define gTimestamp_Enabled_d            0

/*! *********************************************************************************
 *  RTOS Configuration
 ********************************************************************************** */
/* Defines number of OS events used */
#define osNumberOfEvents        6

/*! *********************************************************************************
 *  BLE Stack Configuration
 ********************************************************************************** */

/* Maximum number of handles that can be registered for write notifications. */
#define gMaxWriteNotificationHandles_c       30

/* Maximum number of handles that can be registered for read notifications. */
#define gMaxReadNotificationHandles_c        30

/* Enable Dynamic GATT database */
#define gGattDbDynamic_d    1
#define gUseHciTransport_d  0

/*! *********************************************************************************
 *  NVM Module Configuration - gAppUseNvm_d shall be defined above as 1 or 0
 ********************************************************************************** */

#if gAppUseNvm_d
    /* configure NVM module */
    #define  gNvStorageIncluded_d                (1)
    #define  gNvFragmentation_Enabled_d          (1)
    #define  gNvUseFlexNVM_d                     (0)
    #if gNvUseFlexNVM_d
        #define  gUnmirroredFeatureSet_d         (0)
    #else
        #define  gUnmirroredFeatureSet_d         (1)
    #endif
    #define  gNvRecordsCopiedBufferSize_c        (128)
#endif

/*! *********************************************************************************
 *  Memory Pools Configuration
 ********************************************************************************** */ 

/* Defines pools by block size and number of blocks. Must be aligned to 4 bytes.
 * DO NOT MODIFY THIS DIRECTLY. CONFIGURE AppPoolsDetails_c
 * If gMaxBondedDevices_c increases, adjust memory pools
*/
#define PoolsDetails_c \
     AppPoolsDetails_c


#endif /* APP_PREINCLUDE_H */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */
