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
 *
 * If aw am510 uSD used, define marco WIFI_IW416_BOARD_AW_AM510_USD in following.
 * If aw am457 uSD used, define marco WIFI_IW416_BOARD_AW_AM457_USD in following.
 * If aw cm358 uSD used, define marco WIFI_88W8987_BOARD_AW_CM358_USD in following.
 * If Murata Type 1XK module with uSD-M2 adapter used, define macro WIFI_IW416_BOARD_MURATA_1XK_USD in following.
 * If Murata Type 1ZM module with uSD-M2 adapter used, define macro WIFI_88W8987_BOARD_MURATA_1ZM_USD in following.
 */

/* @TEST_ANCHOR */
#define WIFI_IW416_BOARD_AW_AM510_USD
/* @END_TEST_ANCHOR */
/*#define WIFI_IW416_BOARD_AW_AM457_USD*/
/*#define WIFI_88W8987_BOARD_AW_CM358_USD*/
/*#define WIFI_IW416_BOARD_AW_AM510_USD*/
/*#define WIFI_IW416_BOARD_MURATA_1XK_USD*/
/*#define WIFI_88W8987_BOARD_MURATA_1ZM_USD*/

#if defined(WIFI_IW416_BOARD_AW_AM510_USD) || defined(WIFI_IW416_BOARD_AW_AM457_USD) ||     \
    defined(WIFI_88W8987_BOARD_AW_CM358_USD) || defined(WIFI_IW416_BOARD_MURATA_1XK_USD) || \
    defined(WIFI_88W8987_BOARD_MURATA_1ZM_USD)
#include "bt_module_config.h"
#include "wifi_config.h"
#else
#error The transceiver module is unsupported
#endif

#define CONFIG_BT_PERIPHERAL           1
#define CONFIG_BT_CENTRAL              1
#define CONFIG_BT_L2CAP_IFRAME_SUPPORT 1

#define CONFIG_BT_RFCOMM                    1
#define CONFIG_BT_HFP_HF                    1
#define CONFIG_BT_A2DP                      1
#define CONFIG_BT_A2DP_SOURCE               1
#define CONFIG_BT_A2DP_SINK                 1
#define CONFIG_BT_A2DP_CP_SERVICE           1
#define CONFIG_BT_A2DP_RECOVERY_SERVICE     1
#define CONFIG_BT_A2DP_REPORTING_SERVICE    1
#define CONFIG_BT_A2DP_DR_SERVICE           1
#define CONFIG_BT_A2DP_HC_SERVICE           1
#define CONFIG_BT_A2DP_MULTIPLEXING_SERVICE 1
#define CONFIG_BT_AVRCP                     1
#define CONFIG_BT_AVRCP_CT                  1
#define CONFIG_BT_AVRCP_TG                  1
#define CONFIG_BT_AVRCP_BROWSING            1
#define CONFIG_BT_AVRCP_COVER_ART           1
#define CONFIG_BT_AVRCP_COVER_ART_INITIATOR 1
#define CONFIG_BT_AVRCP_COVER_ART_RESPONDER 1

#define CONFIG_BT_DEVICE_NAME_DYNAMIC   1
#define CONFIG_BT_ID_MAX                4
#define CONFIG_BT_PRIVACY               1
#define CONFIG_BT_SETTINGS              1
#define CONFIG_BT_HOST_CRYPTO           1
#define CONFIG_BT_MAX_PAIRED            16
#define CONFIG_BT_KEYS_OVERWRITE_OLDEST 1
#define CONFIG_BT_SIGNING               1
#define CONFIG_BT_GATT_SERVICE_CHANGED  1
#define CONFIG_BT_GATT_CACHING          1
#define CONFIG_BT_L2CAP_TX_BUF_COUNT    8
#define CONFIG_BT_L2CAP_DYNAMIC_CHANNEL 1
#define CONFIG_BT_DATA_LEN_UPDATE       1
#define CONFIG_BT_USER_DATA_LEN_UPDATE  1
#define CONFIG_BT_FILTER_ACCEPT_LIST    1
#define CONFIG_BT_PHY_UPDATE            1
#define CONFIG_BT_USER_PHY_UPDATE       1
#if 0
#define CONFIG_BT_EXT_ADV 1
#define CONFIG_BT_PER_ADV 1
#endif

#define CONFIG_BT_SNOOP        1
#define CONFIG_BT_RF_TEST_MODE 1
#if 0
#define CONFIG_BT_SMP_SELFTEST 1

#define CONFIG_BT_DEBUG 1

#define CONFIG_NET_BUF_LOG        1
#define CONFIG_NET_BUF_POOL_USAGE 1
#endif

#ifdef K32W061_TRANSCEIVER
#undef CONFIG_BT_BREDR
#endif

#include "edgefast_bluetooth_config.h"

#define CONFIG_WORK_QUEUE_TASK_STACK_SIZE 4096

#define SHELL_BUFFER_SIZE 512
#define SHELL_MAX_ARGS    20
