/*
* Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef _THREAD_LPED_OTA_CLIENT_CONFIG_H_
#define _THREAD_LPED_OTA_CLIENT_CONFIG_H_

/*!=================================================================================================
\file       config.h
\brief      This is the header file for the configuration of the Thread low power end device OTA
            client demo application.
==================================================================================================*/

/*==================================================================================================
CONFIG APPLICATION
==================================================================================================*/

#define SOCK_DEMO                                   0

#define UDP_ECHO_PROTOCOL                           0

#define USE_TEMPERATURE_SENSOR                      1

#define THREAD_USE_SHELL                            0

#define THREAD_USE_THCI                             0

#define gLpmIncluded_d                              1

#define cPWR_UsePowerDownMode                       1

/* Set USE_SED_RESYNC_TO_PARENT to 1 to enable periodic resync between SED and parent */
#define USE_SED_RESYNC_TO_PARENT                    0

#if THREAD_USE_SHELL
/* Enable CoAP Observe Client */
#define COAP_OBSERVE_CLIENT                         0

/* Enable CoAP Observe Server */
#define COAP_OBSERVE_SERVER                         0
#endif

#define APP_NAME_c                                  "OTA Low Power End Device Application Demo"

/*! End device main task stack size*/
#define gMainThreadStackSize_c                      1400

#define gEnableOTAServer_d                          0
#define gEnableOTAClient_d                          1

/* external eeprom type */
/*  FRDM_KW41Z512  gEepromDevice_AT45DB041E_c */
/*  FRDM_KW24D512  gEepromDevice_AT45DB161E_c */
#if (defined(TWR_KW24D512)|| defined(FRDM_KW24)) 
    #define gEepromType_d                           gEepromDevice_AT45DB161E_c
#elif defined(FRDM_KW41Z)
    #define gEepromType_d                           gEepromDevice_AT45DB041E_c
#else
    #define gEepromType_d                           gEepromDevice_InternalFlash_c
#endif


/*!=================================================================================================
  CONFIG STACK
==================================================================================================*/
/*! End device Thread FreeRtos tasks (THREAD and SESSION) stack sizes */
#if FSL_RTOS_FREE_RTOS
    #ifndef  THREAD_TASK_STACK_SIZE
        #define THREAD_TASK_STACK_SIZE              1800
    #endif
#endif

#ifndef SESSION_TASK_STACK_SIZE
    #define SESSION_TASK_STACK_SIZE                 800
#endif

#define STACK_THREAD                                1
#define THREAD_ED_CONFIG                            1


/* Node which cannot start network nor become its Leader nor act as Active Router */
#define THR_DEFAULT_CAN_CREATE_NEW_NETWORK          0
#define THR_DEFAULT_CAN_BECOME_ACTIVE_ROUTER        0
#define THR_DEFAULT_IS_FULL_END_DEVICE              0
#define THR_DEFAULT_IS_POLLING_END_DEVICE           1


#define THR_ENABLE_EVENT_MONITORING                 1

/*! The default value for sleepy end device (SED) polling interval */
#ifndef THR_SED_POLLING_INTERVAL_MS
    #define THR_SED_POLLING_INTERVAL_MS             3000    /* Milliseconds */
#endif

/*! The Timeout period used by the parent to consider a sleepy end device (SED) disconnected
    (in seconds ).
    NOTE: This is higher than usual for the LPED OTA Client application to avoid the parent from
    expiring the SED while the device is rebooted with a new image in case of an OTA Update. */
#ifndef THR_SED_TIMEOUT_PERIOD_SEC
    #define THR_SED_TIMEOUT_PERIOD_SEC              120     /* Seconds */
#endif 

/*! The maximum number of radio range neighbors with which the Thread device can communicate with
    MUST be equal to gNumKeyDeviceListEntries_c macro found in the MAC configuration */
#ifndef THR_MAX_NEIGHBORS
    #define THR_MAX_NEIGHBORS                       2
#endif

/*! The maximum number of Thread Sleepy End Device radio range neighbors */
#ifndef THR_MAX_SLEEPY_ED_NEIGHBORS
    #define THR_MAX_SLEEPY_ED_NEIGHBORS             0
#endif

/*! The number of cache entries a Thread device can maintain */
#ifndef THR_MAX_DEV_ADDR_QUERY_CACHE_ENTRIES
    #define THR_MAX_DEV_ADDR_QUERY_CACHE_ENTRIES    1
#endif

/*! The maximum number of DHCPv6 servers that can be started on the device */
#ifndef DHCP6_SERVER_MAX_INSTANCES
    #define DHCP6_SERVER_MAX_INSTANCES              1
#endif

/*! The maximum number of DHCPv6 clients that the device can service as a DHCPv6 server */
#ifndef DHCP6_SERVER_MAX_CLIENTS
    #define DHCP6_SERVER_MAX_CLIENTS                1
#endif

/*! The maximum number of DHCPv6 clients that can be started on the device */
#ifndef DHCP6_CLIENT_MAX_INSTANCES
    #define DHCP6_CLIENT_MAX_INSTANCES              1
#endif

/*! Set device type */
#ifndef THR_DEVICE_TYPE
    #define THR_DEVICE_TYPE                         gThrDevType_EndNode_c
#endif

/*!=================================================================================================
   DTLS
==================================================================================================*/
#ifndef DTLS_MAX_CONTEXTS
    #define DTLS_MAX_CONTEXTS                       1
#endif

/*!=================================================================================================
   COAP
==================================================================================================*/

/*! The maximum number of COAP sessions that can be established at one time */
#ifndef COAP_MAX_SESSIONS
    #define COAP_MAX_SESSIONS                       2
#endif

/*! The maximum number of coap callbacks per instance */
#ifndef COAP_MAX_CALLBACKS
    #define COAP_MAX_CALLBACKS                      20
#endif

/*!< Maximum number of callbacks registered for non-piggybacked responses */
#ifndef COAP_MAX_NON_PIGGYBACKED_RSP
    #define COAP_MAX_NON_PIGGYBACKED_RSP            (3U)
#endif


/*! Used for keeping track of duplicate CoAP messages */
#ifndef COAP_MAX_MSG_IDs
    #define COAP_MAX_MSG_IDs                        (5U)
#endif
/*!=================================================================================================
   MLE
==================================================================================================*/

/*! Macro that defines how many security keys the MLE module can store at one time */
#ifndef MLE_KEY_DESCRIPTOR_TABLE_SIZE
    #define MLE_KEY_DESCRIPTOR_TABLE_SIZE           2
#endif

/*! Lync Sync min jitter apply during network start with NVM */
#define THR_MIN_LINK_SYNC_JITTER_MS                 100

/*! Lync Sync max jitter apply during network start with NVM */
#define THR_MAX_LINK_SYNC_JITTER_MS                 200

/*!=================================================================================================
   IP
==================================================================================================*/

/*! The maximum number of IP route entries */
#ifndef IP_IP6_ROUTING_TBL_SIZE
    #define IP_IP6_ROUTING_TBL_SIZE                 5
#endif

/*! The maximum supported number of IP interfaces */
#ifndef IP_IF_NB
    #define IP_IF_NB                                2
#endif

/*! The maximum number of IPv6 addresses. This is regardless of how many interfaces are available */
#ifndef IP_IF_IP6_ADDR_NB
    #define IP_IF_IP6_ADDR_NB                       6
#endif

/*! The maximum number of supported multicast addresses */
#ifndef IP_IF_IP6_MULTICAST_ADDR_NB
    #define IP_IF_IP6_MULTICAST_ADDR_NB             8
#endif

/*! The maximum number of IP transport services that can be supported. Ex. UDP, TCP. */
#ifndef IP_TRANSPORT_SERVICE_NB
    #define IP_TRANSPORT_SERVICE_NB                 3
#endif

/*! Number representing how many IP packet fragments can be stored at one time */
#ifndef IP_IP_REASSEMBLY_QUEUE_SIZE
    #define IP_IP_REASSEMBLY_QUEUE_SIZE             1
#endif

/*!=================================================================================================
   MPL
==================================================================================================*/

/*! The maximum number of MPL instances. This must be correlated to IP_IF_NB. */
#ifndef MPL_INSTANCE_SET_SIZE
    #define MPL_INSTANCE_SET_SIZE                   1
#endif

/*! The maximum number of seeds the MPL module can store at one time */
#ifndef MPL_SEED_SET_SIZE
    #define MPL_SEED_SET_SIZE                       3
#endif

/*! The maximum number of MPL transmited messages that can be buffered at one time */
#ifndef MPL_BUFFERED_MESSAGE_SET_SIZE
    #define MPL_BUFFERED_MESSAGE_SET_SIZE           5
#endif

/*!=================================================================================================
   TRICKLE
==================================================================================================*/
/*! The maximum number of TRICKLE instances. This must be correlated to IP_IF_NB. */
#ifndef TRICKLE_INSTANCE_SET_SIZE
    #define TRICKLE_INSTANCE_SET_SIZE               1
#endif

/*! The maximum number of Trickle events */
#ifndef TRICKLE_LIST_SIZE
    #define TRICKLE_LIST_SIZE                       2
#endif

/*!=================================================================================================
   SIXLOWPAN
==================================================================================================*/

/*! The maximum number of 6LoWPAN instaces. MUST not be greater than IP_IF_NB. */
#ifndef SLWPCFG_INSTANCES_NB
    #define SLWPCFG_INSTANCES_NB                    1
#endif



/*!=================================================================================================
     CONFIG FRAMEWORK
==================================================================================================*/

#define gKeyBoardSupported_d                        1

#if THREAD_USE_THCI
    #define gFsciIncluded_c                         1
#endif

#if (!THREAD_USE_SHELL && !THREAD_USE_THCI)
    #define gSerialManagerMaxInterfaces_c           (0)
#endif

/*! FREE_RTOS HEAP SIZE (used for rtos tasks stacks and rtos objects)*/                      
#ifdef FSL_RTOS_FREE_RTOS
    #ifdef CPU_MKW24D512VHA5
        /* For usb enabled - increase the heap size to 0x4400 */
        #define gTotalHeapSize_c                    0x2A00
    #elif  defined(CPU_MK64FN1M0VMD12)
        #define gTotalHeapSize_c                    0x8000
    #elif defined(CPU_MKL46Z256VLL4)
        #define gTotalHeapSize_c                    0x2A00
    #else
        #define gTotalHeapSize_c                    0x2A00
    #endif 
#endif

#ifdef FSL_RTOS_FREE_RTOS
    #define USB_STACK_FREERTOS                      1
#endif

/*! Thread stack pools configuration */
#ifndef ThreadPoolsDetails_c
    #define ThreadPoolsDetails_c\
              _block_size_  16     _number_of_blocks_     22  _pool_id_(ThrPoolId_d)    _eol_  \
              _block_size_  68     _number_of_blocks_     8   _pool_id_(ThrPoolId_d)    _eol_  \
              _block_size_  160    _number_of_blocks_     12  _pool_id_(ThrPoolId_d)    _eol_  \
              _block_size_  440    _number_of_blocks_     3   _pool_id_(ThrPoolId_d)    _eol_  \
              _block_size_  540    _number_of_blocks_     1   _pool_id_(ThrPoolId_d)    _eol_  \
              _block_size_  1300   _number_of_blocks_     2   _pool_id_(ThrPoolId_d)    _eol_
#endif
/*! Application pools configuration */
#ifndef AppPoolsDetails_c
    #define AppPoolsDetails_c\
              _block_size_  16    _number_of_blocks_     28 _pool_id_(AppPoolId_d)    _eol_  \
              _block_size_  160   _number_of_blocks_     6 _pool_id_(AppPoolId_d)    _eol_
#endif


/*! End device Framework FreeRtos tasks (Timer, Serial) stack sizes */
#if FSL_RTOS_FREE_RTOS
    #ifndef gTmrTaskStackSize_c
        #define gTmrTaskStackSize_c                 600
    #endif
    #ifndef  gSerialTaskStackSize_c
        #define gSerialTaskStackSize_c              800
    #endif
#else
    #ifndef  gTmrTaskStackSize_c
        #define gTmrTaskStackSize_c                 800
    #endif
#endif


#ifndef gTmrStackTimers_c
    #define gTmrStackTimers_c                       16
#endif

#ifdef FRDM_KW24
    #define gLedRgbEnabled_d                        1 
    #define gLEDsOnTargetBoardCnt_c                 4
    #define gKBD_KeysCount_c                        4
#elif defined(USB_KW24)
    #define gLEDsOnTargetBoardCnt_c                 2
    #define gKBD_KeysCount_c                        1
    #define gSerialMgrUseUSB_c                      1
    #define gSerialMgrUseUart_c                     0
#elif defined(FRDM_K64F)
    #define gLedRgbEnabled_d                        1
    #define gLEDsOnTargetBoardCnt_c                 4
    #define gKBD_KeysCount_c                        4
#elif defined(FRDM_KL46Z)
    #define gKBD_KeysCount_c                        4
    #define gLedRgbEnabled_d                        1
    #define gLEDBlipEnabled_d                       1
    #define gLEDsOnTargetBoardCnt_c                 4
    #define gSerialMgrUseUart_c                     1
    #define gSerialMgrUseUSB_c                      0
#elif defined(FRDM_KW41Z)
    #define gLedRgbEnabled_d                        1
    #define gLEDsOnTargetBoardCnt_c                 4
    #define gKBD_TsiElectdCount_c                   0
    #define gKBD_KeysCount_c                        2
#elif defined(USB_KW41)
    #define gLedRgbEnabled_d                        0
    #define gKBD_KeysCount_c                        1
    #define gLEDsOnTargetBoardCnt_c                 2
#endif
                  
/*!=================================================================================================
     CONFIG KSDK
==================================================================================================*/

/* Declare  CLOCK_FllStableDelay in hardware_init.c */
#define MCG_USER_CONFIG_FLL_STABLE_DELAY_EN         1
extern void CLOCK_FllStableDelay(void);
/*!=================================================================================================
        CONFIG Mac/Phy
==================================================================================================*/
#define gNumKeyDeviceListEntries_c                  2

/*! End device mac FreeRtos task stack size*/
#if FSL_RTOS_FREE_RTOS
    #define gMacTaskStackSize_c                     1400
#endif

/*! Enables/Disables the MAC Filtering number */
#ifndef MAC_FILTERING_ENABLED
  #define MAC_FILTERING_ENABLED                     0
#endif

/*! The maximum number of entries in the MAC filtering table */
#ifndef MAC_FILTERING_TABLE_SIZE
    #define MAC_FILTERING_TABLE_SIZE                1
#endif
/*! The neighbor table size from PHY. This table is used to generate the ACK with Frame Pending bit set.
   When a poll request is received from a sleepy child which is not in this table,
   an ACK with Frame Pending bit set will be automatically generated. A neighbor used 2 entries:
   one for the short address and another one for the extended address.
*/
#define gPhyNeighborTableSize_d                     0


#if defined(CPU_MKW24D512VHA5)||defined(CPU_MK64FN1M0VMD12)
    #define gMacFeatureSet_d                        gMacFeatureSet_THRRFD_M4_d
#else
    #define gMacFeatureSet_d                        gMacFeatureSet_THRRFD_M0_d
#endif

#if defined(CPU_MKL46Z256VLL4)
    #define gMCR20_ClkOutFreq_d                     gCLK_OUT_FREQ_DISABLE
#endif
/************************************************************************************
*
*      COMMON MODULES CONFIGURATIONS FILES
*
************************************************************************************/
#include "app_config.h"
#include "app_stack_config.h"
#include "app_framework_config.h"
#include "app_mac_config.h"

/************************************************************************************
*
*      CHECKS
*
************************************************************************************/
#if SERIAL_TUN_IF && (gFsciIncluded_c == 0)
#error "Serial Tun interface must have FSCI enabled"
#endif

#endif /* _THREAD_LPED_OTA_CLIENT_CONFIG_H_  */
