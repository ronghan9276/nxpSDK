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
 * K32W061_TRANSCEIVER
 *
 * If WIFI_IW416_BOARD_AW_AM510MA used, define marco WIFI_IW416_BOARD_AW_AM510MA in following.
 * If WIFI_88W8987_BOARD_AW_CM358MA used, define marco WIFI_88W8987_BOARD_AW_CM358MA in following.
 * If Murata Type 1XK module(EAR00385 M2 only) used, define macro WIFI_IW416_BOARD_MURATA_1XK_M2 in following.
 * If Murata Type 1ZM module(EAR00364 M2 only) used , define macro WIFI_88W8987_BOARD_MURATA_1ZM_M2 in following.
 * If transceiver k32w061 is used, the macro K32W061_TRANSCEIVER should be defined
 */

/* @TEST_ANCHOR */
#define WIFI_IW416_BOARD_AW_AM510MA
/* @END_TEST_ANCHOR */
/*#define WIFI_88W8987_BOARD_AW_CM358MA*/
/*#define WIFI_IW416_BOARD_AW_AM510MA*/
/*#define WIFI_IW416_BOARD_MURATA_1XK_M2*/
/*#define WIFI_88W8987_BOARD_MURATA_1ZM_M2*/
/*#define K32W061_TRANSCEIVER*/

#if defined(WIFI_IW416_BOARD_AW_AM510MA) || defined(WIFI_88W8987_BOARD_AW_CM358MA) || defined(K32W061_TRANSCEIVER) || \
    defined(WIFI_IW416_BOARD_MURATA_1XK_M2) || defined(WIFI_88W8987_BOARD_MURATA_1ZM_M2)
#include "bt_module_config.h"
#include "wifi_config.h"
#else
#error The transceiver module is unsupported
#endif

#define CONFIG_BT_DEVICE_NAME           "central_ipsp"
#define CONFIG_BT_SMP                   1
#define CONFIG_BT_SETTINGS              1
#define CONFIG_BT_HOST_CRYPTO           1
#define CONFIG_BT_KEYS_OVERWRITE_OLDEST 1
#define CONFIG_BT_RX_STACK_SIZE         2200

#include "edgefast_bluetooth_config.h"
