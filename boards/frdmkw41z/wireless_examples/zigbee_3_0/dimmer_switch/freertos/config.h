/*
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef _ZIGBEE_DIMMER_SWITCH_CONFIG_H_
#define _ZIGBEE_DIMMER_SWITCH_CONFIG_H_

/*!=================================================================================================
\file       config.h
\brief      This is the header file for the configuration of the Zigbee Dimmer Switch demo
            application.
==================================================================================================*/

/*==================================================================================================
CONFIG APPLICATION
==================================================================================================*/
/* Zigbee stack debug config */
#ifdef DEBUG
#define DBG_ENABLE
    //#define DEBUG_APP
    //#define DEBUG_BDB
    //#define DEBUG_ZCL
    //#define DEBUG_APP_BDB
    //#define DEBUG_APP_EVENT
    //#define DEBUG_LIGHT_NODE
#endif

/*!   TRUE =  1: Use PowerDown functions (Normal)
      FALSE = 0: Don't use PowerDown. Useful for debugging and test purposes
 */
#define cPWR_UsePowerDownMode 1
/*!  If TRUE - do not use  PWM_FOR_RGB_LED */
#define gLpmIncluded_d        cPWR_UsePowerDownMode
#define SLEEP_ENABLE          cPWR_UsePowerDownMode
#define DEEP_SLEEP_ENABLE     cPWR_UsePowerDownMode

#define asm __asm

#define DimmerSwitch

/*! FreeRTOS heap size */
#define gTotalHeapSize_c 11000

/*! Main Task stack size */
#define gMainThreadStackSize_c 4500

/*! Enable wdog from ksdk */
#define DISABLE_WDOG 0

/*! OTA Update support */
//#define BUILD_OTA

#ifdef BUILD_OTA
#define gKBD_TsiElectdCount_c 0
#define gKBD_KeysCount_c 2
#endif

#define mDeviceInfo "Kinetis_KW41Z Dimmer Switch"

/************************************************************************************
*
*       CONFIG STACK
*
************************************************************************************/
/*! Enable little endian build option */
#define LITTLE_ENDIAN_PROCESSOR

/*! Device type zigbee end device */ 
#define ZBPRO_DEVICE_TYPE_ZED

/*! Enable Network Steering Capability */
#define BDB_SUPPORT_NWK_STEERING

/*! Enable find and bind intitiator Capability */
#define BDB_SUPPORT_FIND_AND_BIND_INITIATOR

/*! Aplication PDM ID */
#define PDM_APP_ID  PDM_ID_APP_ZED

/*! The default value for sleepy end device (SED) polling interval */
#ifndef ZB_POLLING_INTERVAL_MS
    #define ZB_POLLING_INTERVAL_MS                  3000     /* Milliseconds */
#endif

#define BDB_SET_DEFAULT_TC_POLICY TRUE
#define BDB_JOIN_USES_INSTALL_CODE_KEY TRUE

/************************************************************************************
*
*       CONFIG FRAMEWORK
*
************************************************************************************/
/*! Number of timers needed by the protocol stack */
#define gTmrStackTimers_c       13

/************************************************************************************
*
*      COMMON MODULES CONFIGURATIONS FILES
*
************************************************************************************/
/*! Common framework configuration of all zigbee demo applications */
#include "app_framework_config.h"

/*! Common mac/phy configuration of all zigbee demo applications */
#include "app_mac_config.h"

/************************************************************************************
*
*      CHECKS
*
************************************************************************************/

#endif /* _ZIGBEE_DIMMER_SWITCH_CONFIG_H_ */
