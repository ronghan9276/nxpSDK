/*
 *  Copyright 2020-2021 NXP
 *  All rights reserved.
 *
 *  SPDX-License-Identifier: BSD-3-Clause
 */

#define USB_HOST_CONFIG_IP3516HS (1U)
#define CONTROLLER_ID            kUSB_ControllerIp3516Hs0

/* Controller config
 * Supported controller list,
 * WIFI_IW416_BOARD_AW_AM510_USD
 * WIFI_IW416_BOARD_AW_AM457_USD
 * WIFI_88W8987_BOARD_AW_CM358_USD
 * WIFI_IW416_BOARD_MURATA_1XK_USD
 * WIFI_88W8987_BOARD_MURATA_1ZM_USD
 * K32W061_TRANSCEIVER
 *
 * If aw am510 uSD used, define marco WIFI_IW416_BOARD_AW_AM510_USD in following.
 * If aw am457 uSD used, define marco WIFI_IW416_BOARD_AW_AM457_USD in following.
 * If aw cm358 uSD used, define marco WIFI_88W8987_BOARD_AW_CM358_USD in following.
 * If Murata Type 1XK module with uSD-M2 adapter used, define macro WIFI_IW416_BOARD_MURATA_1XK_USD in following.
 * If Murata Type 1ZM module with uSD-M2 adapter used, define macro WIFI_88W8987_BOARD_MURATA_1ZM_USD in following.
 * If transceiver k32w061 is used, the macro K32W061_TRANSCEIVER should be defined
 */

/* @TEST_ANCHOR */
#define WIFI_IW416_BOARD_AW_AM510_USD
/* @END_TEST_ANCHOR */
/*#define WIFI_IW416_BOARD_AW_AM457_USD*/
/*#define WIFI_88W8987_BOARD_AW_CM358_USD*/
/*#define K32W061_TRANSCEIVER*/
/*#define WIFI_IW416_BOARD_AW_AM510_USD*/
/*#define WIFI_IW416_BOARD_MURATA_1XK_USD*/
/*#define WIFI_88W8987_BOARD_MURATA_1ZM_USD*/

#if defined(WIFI_IW416_BOARD_AW_AM510_USD) || defined(WIFI_IW416_BOARD_AW_AM457_USD) || \
    defined(WIFI_88W8987_BOARD_AW_CM358_USD) || defined(K32W061_TRANSCEIVER) ||         \
    defined(WIFI_IW416_BOARD_MURATA_1XK_USD) || defined(WIFI_88W8987_BOARD_MURATA_1ZM_USD)
#include "bt_module_config.h"
#include "wifi_config.h"
#else
#error The transceiver module is unsupported
#endif

#define CONFIG_BT_DEVICE_NAME           "central_pxm"
#define CONFIG_BT_SMP                   1
#define CONFIG_BT_SETTINGS              1
#define CONFIG_BT_HOST_CRYPTO           1
#define CONFIG_BT_KEYS_OVERWRITE_OLDEST 1
#define CONFIG_BT_RX_STACK_SIZE         2200

#include "edgefast_bluetooth_config.h"
