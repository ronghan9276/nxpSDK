/*
 * Copyright 2020-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define USB_HOST_CONFIG_IP3516HS (1U)
#define CONTROLLER_ID            kUSB_ControllerIp3516Hs0

/* Controller config
 * Supported controller list,
 * WIFI_IW416_BOARD_AW_AM510MA
 * WIFI_88W8987_BOARD_AW_CM358MA
 * WIFI_IW416_BOARD_MURATA_1XK_M2
 * WIFI_88W8987_BOARD_MURATA_1ZM_M2
 *
 * If WIFI_IW416_BOARD_AW_AM510MA used, define marco WIFI_IW416_BOARD_AW_AM510MA in following.
 * If WIFI_88W8987_BOARD_AW_CM358MA used, define marco WIFI_88W8987_BOARD_AW_CM358MA in following.
 * If Murata Type 1XK module(EAR00385 M2 only) used, define macro WIFI_IW416_BOARD_MURATA_1XK_M2 in following.
 * If Murata Type 1ZM module(EAR00364 M2 only) used , define macro WIFI_88W8987_BOARD_MURATA_1ZM_M2 in following.
 */

/* @TEST_ANCHOR */
#define WIFI_IW416_BOARD_AW_AM510MA
/* @END_TEST_ANCHOR */
/*#define WIFI_88W8987_BOARD_AW_CM358MA*/
/*#define WIFI_IW416_BOARD_AW_AM510MA*/
/*#define WIFI_IW416_BOARD_MURATA_1XK_M2*/
/*#define WIFI_88W8987_BOARD_MURATA_1ZM_M2*/

#if defined(WIFI_IW416_BOARD_AW_AM510MA) || defined(WIFI_88W8987_BOARD_AW_CM358MA) || \
    defined(WIFI_IW416_BOARD_MURATA_1XK_M2) || defined(WIFI_88W8987_BOARD_MURATA_1ZM_M2)
#include "bt_module_config.h"
#include "wifi_config.h"
#else
#error The Wi-Fi module is unsupported
#endif

#define CONFIG_BT_RFCOMM                1
#define CONFIG_BT_HFP_AG                1
#define CONFIG_BT_DEBUG                 0
#define CONFIG_BT_DEBUG_HCI_CORE        0
#define CONFIG_BT_DEBUG_CONN            0
#define CONFIG_BT_DEBUG_GATT            0
#define CONFIG_BT_DEBUG_ATT             0
#define CONFIG_BT_DEBUG_SMP             0
#define CONFIG_BT_DEBUG_KEYS            0
#define CONFIG_BT_DEBUG_L2CAP           0
#define CONFIG_BT_DEBUG_SERVICE         0
#define CONFIG_BT_DEBUG_HFP_AG          0
#define CONFIG_BT_SETTINGS              1
#define CONFIG_BT_KEYS_OVERWRITE_OLDEST 1

#include "edgefast_bluetooth_config.h"
