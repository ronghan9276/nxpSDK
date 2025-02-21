/*
 * Amazon FreeRTOS Wi-Fi
 *
 *  Copyright 2019-2020 NXP
 *
 *  NXP CONFIDENTIAL
 *  The source code contained or described herein and all documents related to
 *  the source code ("Materials") are owned by NXP, its
 *  suppliers and/or its licensors. Title to the Materials remains with NXP,
 *  its suppliers and/or its licensors. The Materials contain
 *  trade secrets and proprietary and confidential information of NXP, its
 *  suppliers and/or its licensors. The Materials are protected by worldwide copyright
 *  and trade secret laws and treaty provisions. No part of the Materials may be
 *  used, copied, reproduced, modified, published, uploaded, posted,
 *  transmitted, distributed, or disclosed in any way without NXP's prior
 *  express written permission.
 *
 *  No license under any patent, copyright, trade secret or other intellectual
 *  property right is granted to or conferred upon you by disclosure or delivery
 *  of the Materials, either expressly, by implication, inducement, estoppel or
 *  otherwise. Any license under such intellectual property rights must be
 *  express and approved by NXP in writing.
 *
 */

/**
 * @file iot_wifi.c
 * @brief Wi-Fi Interface.
 */

/* Socket and Wi-Fi interface includes. */
#include "FreeRTOS.h"
#include "list.h"
#include "iot_wifi.h"

/* Wi-Fi configuration includes. */
#include "aws_wifi_config.h"

#include <wlan.h>
#include <wmlog.h>
#include <wm_net.h>

#if defined(SD8801)
#include "sd8801_wlan.h"
#elif defined(SD8977)
#include "sduart8977_wlan_bt.h"
#elif defined(SD8978)
#include "sduart8978_wlan_bt.h"
#elif defined(SD8987)
#include "sduart8987_wlan_bt.h"
#elif defined(SD8997)
#include "sduart8997_wlan_bt.h"
#elif defined(SD9097)
#include "pvt_sd9097_wlan.h"
#elif defined(SD9098)
#include "pvt_sd9098_wlan.h"
#endif

#include "fsl_debug_console.h"

#if (defined(IOT_WIFI_ENABLE_SAVE_NETWORK) && (IOT_WIFI_ENABLE_SAVE_NETWORK > 0))
#include "NVM_Interface.h"
#include "nvm_adapter.h"
#endif

#ifndef IOT_WIFI_MAX_SAVED_NETWORKS
#define IOT_WIFI_MAX_SAVED_NETWORKS 8
#endif

#define wm_wlan_e(...)                             \
    wmlog_e("wm_wlan", ##__VA_ARGS__)
#define wm_wlan_w(...)                             \
    wmlog_w("wm_wlan", ##__VA_ARGS__)
#define wm_wlan_d(...)                             \
    wmlog("wm_wlan", ##__VA_ARGS__)

#define wmprintf(...) wmlog("wm_wlan", ##__VA_ARGS__)

static os_semaphore_t scan_protection_sem;

static os_semaphore_t wlan_init_sem;
static os_mutex_t wlan_mtx;
static IotNetworkStateChangeEventCallback_t xEventCallback = NULL;

#if (defined(IOT_WIFI_ENABLE_SAVE_NETWORK) && (IOT_WIFI_ENABLE_SAVE_NETWORK > 0))
static int WIFI_NvmBackendInit(void);
#if defined(__IAR_SYSTEMS_ICC__)
_Pragma("location=\"NVM_TABLE\"") __root NVM_DataEntry_t iotWifiNvDataTable[IOT_WIFI_MAX_SAVED_NETWORKS + 1];
NVM_ADAPTER_TABLE(nvm_adapter_table_t iotWifiNvAdapterDataTable[]) =
{
    iotWifiNvDataTable,
    IOT_WIFI_MAX_SAVED_NETWORKS + 1,
    WIFI_NvmBackendInit
};
#elif (defined(__CC_ARM) || defined(__ARMCC_VERSION))
static NVM_DataEntry_t iotWifiNvDataTable[IOT_WIFI_MAX_SAVED_NETWORKS + 1] __attribute__((section("NVM_TABLE"), used));
NVM_ADAPTER_TABLE(nvm_adapter_table_t iotWifiNvAdapterDataTable[]) =
{
    {
        iotWifiNvDataTable,
        IOT_WIFI_MAX_SAVED_NETWORKS + 1,
        WIFI_NvmBackendInit,
    },
};
#elif defined(__GNUC__)
static NVM_DataEntry_t iotWifiNvDataTable[IOT_WIFI_MAX_SAVED_NETWORKS + 1] __attribute__((section(".NVM_TABLE"), used));
NVM_ADAPTER_TABLE(nvm_adapter_table_t iotWifiNvAdapterDataTable[]) =
{
    {
        iotWifiNvDataTable,
        IOT_WIFI_MAX_SAVED_NETWORKS + 1,
        WIFI_NvmBackendInit,
    },
};
#else
#error "Must define iotWifiNvDataTable"
#endif

static WIFINetworkProfile_t NvmSavedWifiNetworkProfile[IOT_WIFI_MAX_SAVED_NETWORKS];
static uint8_t NvmSavedWifiNetworkProfileIndex;
#endif

static int wlan_event_callback(enum wlan_event_reason event, void *data)
{
    int ret;
    struct wlan_ip_config addr;
    char ip[16];

    /* After successful wlan subsytem initialization */
    if (event == WLAN_REASON_INITIALIZED) {
        wmprintf("WLAN_REASON_INITIALIZED\r\n");

        ret = os_mutex_create(&wlan_mtx, "wlanmtx",
                OS_MUTEX_INHERIT);
        if (ret != WM_SUCCESS) {
            return eWiFiFailure;
        }
        os_semaphore_put(&wlan_init_sem);
    }

    if (event == WLAN_REASON_SUCCESS) {
        ret = wlan_get_address(&addr);
        if (ret != WM_SUCCESS) {
            wmprintf("failed to get IP address\r\n");
            return 0;
        }

        net_inet_ntoa(addr.ipv4.address, ip);

        wmprintf("Connected to with IP = [%s]\r\n", ip);
    }

    if (event == WLAN_REASON_USER_DISCONNECT) {
	    wmprintf("Dis-connected\r\n");
    }

    return 0;
}

#if (defined(IOT_WIFI_ENABLE_SAVE_NETWORK) && (IOT_WIFI_ENABLE_SAVE_NETWORK > 0))
static int WIFI_NvmBackendInit(void)
{
    /* NVM Init */
    for (uint32_t index = 0; index < IOT_WIFI_MAX_SAVED_NETWORKS; index++)
    {
        iotWifiNvDataTable[index].pData         = &NvmSavedWifiNetworkProfile[index];
        iotWifiNvDataTable[index].ElementSize   = sizeof(NvmSavedWifiNetworkProfile[index]);
        iotWifiNvDataTable[index].ElementsCount = 1;
        iotWifiNvDataTable[index].DataEntryID   = 0xfA01 + index;
        iotWifiNvDataTable[index].DataEntryType = gNVM_MirroredInRam_c;
    }
    iotWifiNvDataTable[IOT_WIFI_MAX_SAVED_NETWORKS].pData         = &NvmSavedWifiNetworkProfileIndex;
    iotWifiNvDataTable[IOT_WIFI_MAX_SAVED_NETWORKS].ElementSize   = sizeof(NvmSavedWifiNetworkProfileIndex);
    iotWifiNvDataTable[IOT_WIFI_MAX_SAVED_NETWORKS].ElementsCount = 1;
    iotWifiNvDataTable[IOT_WIFI_MAX_SAVED_NETWORKS].DataEntryID   = 0xfA01 + IOT_WIFI_MAX_SAVED_NETWORKS;
    iotWifiNvDataTable[IOT_WIFI_MAX_SAVED_NETWORKS].DataEntryType = gNVM_MirroredInRam_c;
    return 0;
}
#endif

/*-----------------------------------------------------------*/
WIFIReturnCode_t WIFI_On( void )
{
    int rv;
    static bool wifi_init_done = false;

    if(wifi_init_done)
	return eWiFiSuccess;

#if (defined(IOT_WIFI_ENABLE_SAVE_NETWORK) && (IOT_WIFI_ENABLE_SAVE_NETWORK > 0))

    NVM_AdapterInit();

    for (uint32_t index = 0; index < IOT_WIFI_MAX_SAVED_NETWORKS; index++)
    {
        NvRestoreDataSet(&NvmSavedWifiNetworkProfile[index], false);
    }
    NvRestoreDataSet(&NvmSavedWifiNetworkProfileIndex, false);
#endif

    rv = os_semaphore_create(&wlan_init_sem, "wlansem");
    if (rv != WM_SUCCESS) {
            return eWiFiFailure;
    }

    /* Consume so that 'get' blocks when used later */
    os_semaphore_get(&wlan_init_sem, OS_WAIT_FOREVER);

    rv = wlan_init(wlan_fw_bin, wlan_fw_bin_len);
    if (rv != WM_SUCCESS) {
        os_semaphore_delete(&wlan_init_sem);
        return eWiFiFailure;
    }

    rv = wlan_start(wlan_event_callback);
    if (rv != WM_SUCCESS) {
        os_semaphore_delete(&wlan_init_sem);
        return eWiFiFailure;
    }

    /* Wait till app framework is initialized */
    rv = os_semaphore_get(&wlan_init_sem, OS_WAIT_FOREVER);
    if (rv != WM_SUCCESS) {
        os_semaphore_delete(&wlan_init_sem);
        return eWiFiFailure;
    }

    os_semaphore_delete(&wlan_init_sem);

    wifi_init_done = true;
    return eWiFiSuccess;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_Off( void )
{
    return eWiFiSuccess;
}
/*-----------------------------------------------------------*/

#define IS_SSID_LEN_VALID(x) \
        ((x) <=  wificonfigMAX_SSID_LEN && (x) > 0)
#define IS_PASSPHRASE_LEN_VALID(x) \
        ((x) <= wificonfigMAX_PASSPHRASE_LEN && (x) > 0)

WIFIReturnCode_t WIFI_ConnectAP( const WIFINetworkParams_t * const pxNetworkParams )
{
    int ret = eWiFiFailure;
    struct wlan_network home_nw;
    enum wlan_connection_state state;
    size_t ssid_len;

    int retry_cnt = 3;
    int connect_retry = 10;

    if (os_mutex_get(&wlan_mtx, OS_WAIT_FOREVER) != WM_SUCCESS)
           return eWiFiFailure;

    if(pxNetworkParams == NULL)
        goto fail;

    if (pxNetworkParams->pcSSID == NULL || pxNetworkParams->xSecurity ==
            eWiFiSecurityNotSupported) {
        goto fail;
    }

    if (pxNetworkParams->xSecurity != eWiFiSecurityOpen && pxNetworkParams->pcPassword == NULL) {
        goto fail;
    }

    if (!IS_SSID_LEN_VALID(pxNetworkParams->ucSSIDLength) ||
            (pxNetworkParams->xSecurity != eWiFiSecurityOpen &&
            !IS_PASSPHRASE_LEN_VALID(pxNetworkParams->ucPasswordLength))) {
	goto fail;
    }

    if (wlan_get_connection_state(&state)) {
		wmprintf("Error: unable to get "
				"connection state\r\n");
	goto fail;
    }

    if (state == WLAN_CONNECTED) {
        int connect_retry = 200;
        ret = wlan_disconnect();
        if (ret != WM_SUCCESS)
            goto fail;

        do {
            /* wait for interface up */
            os_thread_sleep(os_msec_to_ticks(50));

            if (wlan_get_connection_state(&state)) {
            wmprintf("Error: unable to get "
                    "connection state\r\n");
                continue;
            }

            if (state == WLAN_DISCONNECTED || connect_retry == 0)
                break;
        } while (connect_retry--);

        if (state != WLAN_DISCONNECTED) {
            wmprintf("Error: Not connected.\r\n");
            goto fail;
        }
    }

    memset(&home_nw, 0, sizeof(home_nw));

    strncpy(home_nw.name, "aws_network", WLAN_NETWORK_NAME_MAX_LENGTH);

    ssid_len = strlen(pxNetworkParams->pcSSID);
    if (ssid_len > IEEEtypes_SSID_SIZE)
    {
        ssid_len = IEEEtypes_SSID_SIZE;
    }

    /* Set SSID as passed by the user */
    strncpy(home_nw.ssid, pxNetworkParams->pcSSID, ssid_len);

    if(pxNetworkParams->pcPassword) {
        /* Set the passphrase */
        //strncpy(home_nw.security.psk, pxNetworkParams->pcPassword, PASSWORD_MAX_LENGTH);
        strcpy(home_nw.security.psk, pxNetworkParams->pcPassword);

        /* Set the passphrase length */
        home_nw.security.psk_len = strlen(home_nw.security.psk);
    }

    home_nw.channel = pxNetworkParams->cChannel;

    if (pxNetworkParams->xSecurity == eWiFiSecurityOpen)
        home_nw.security.type = WLAN_SECURITY_NONE;
    else if (pxNetworkParams->xSecurity == eWiFiSecurityWEP)
        home_nw.security.type = WLAN_SECURITY_WEP_OPEN;
    else if (pxNetworkParams->xSecurity == eWiFiSecurityWPA)
        home_nw.security.type = WLAN_SECURITY_WPA;
    else if (pxNetworkParams->xSecurity == eWiFiSecurityWPA2)
        home_nw.security.type = WLAN_SECURITY_WPA2;

    home_nw.type = WLAN_BSS_TYPE_STA;
    home_nw.role = WLAN_BSS_ROLE_STA;
    home_nw.ip.ipv4.addr_type = ADDR_TYPE_DHCP;

    ret = wlan_remove_network("aws_network");
    if (ret != WM_SUCCESS && ret != -WM_E_INVAL) {
	wmprintf(" Failed to add network %d\r\n", ret);
	goto fail;
    }

    ret = wlan_add_network(&home_nw);
    if (ret != WM_SUCCESS) {
	wmprintf(" Failed to add network %d\r\n", ret);
	goto fail;
    }


    do {
        wmprintf("Connecting to %s .....\r\n", home_nw.ssid);

        ret = wlan_connect(home_nw.name);

        if (ret != 0) {
            wmprintf("Failed to connect %d\r\n", ret);
            goto retry;
        }

        connect_retry = 2000;

        do {
            /* wait for interface up */
            os_thread_sleep(os_msec_to_ticks(50));

            if (wlan_get_connection_state(&state)) {
                wmprintf("Error: unable to get "
                        "connection state\r\n");
                continue;
            }

            if (state == WLAN_CONNECTED || connect_retry == 0)
                break;
        } while (connect_retry--);

        if (state != WLAN_CONNECTED) {
            wmprintf("Error: Not connected.\r\n");
            goto retry;
        }

        if (os_mutex_put(&wlan_mtx) != WM_SUCCESS)
            return eWiFiFailure;

        if( xEventCallback != NULL )
        {
            xEventCallback( AWSIOT_NETWORK_TYPE_WIFI, eNetworkStateEnabled );
        }
        return eWiFiSuccess;
retry:
        retry_cnt--;
        wmprintf("Connect to AP FAIL ! Retrying ..... \r\n");

    } while (retry_cnt != 0);

    if (retry_cnt == 0) {
        os_thread_sleep(os_msec_to_ticks(500));

	wmprintf("Connection Failed !\r\n");

	ret = wlan_disconnect();
	if (ret != 0) {
	    wmprintf("Failed to disconnect \r\n");
	    if (os_mutex_put(&wlan_mtx) != WM_SUCCESS)
                return eWiFiFailure;
        return eWiFiFailure;
        }
        if (os_mutex_put(&wlan_mtx) != WM_SUCCESS)
            return eWiFiFailure;
        return eWiFiFailure;
    }

fail:

    if (os_mutex_put(&wlan_mtx) != WM_SUCCESS)
        return eWiFiFailure;

    if (ret != 0)
    {
        return eWiFiFailure;
    }
    else
    {
        return eWiFiSuccess;
    }
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_Disconnect( void )
{
    int ret = eWiFiFailure;
    enum wlan_connection_state state;
    int connect_retry = 200;

    if (os_mutex_get(&wlan_mtx, OS_WAIT_FOREVER) != WM_SUCCESS)
           return eWiFiFailure;

    ret = wlan_disconnect();
    if (ret != WM_SUCCESS)
	    goto fail;

    do {
        /* wait for interface up */
        os_thread_sleep(os_msec_to_ticks(50));

        if (wlan_get_connection_state(&state)) {
            wmprintf("Error: unable to get "
                "connection state\r\n");
            continue;
        }

        if (state == WLAN_DISCONNECTED || connect_retry == 0)
            break;
    } while (connect_retry--);

    if (state != WLAN_DISCONNECTED) {
        wmprintf("Error: Not connected.\r\n");
        goto fail;
    }

    if( xEventCallback != NULL )
    {
        xEventCallback( AWSIOT_NETWORK_TYPE_WIFI, eNetworkStateDisabled );
    }
fail:

    if (os_mutex_put(&wlan_mtx) != WM_SUCCESS)
           return eWiFiFailure;

    if (ret != 0)
    {
        return eWiFiFailure;
    }
    else
    {
        return eWiFiSuccess;
    }
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_Reset( void )
{
    return eWiFiNotSupported;
}
/*-----------------------------------------------------------*/

//#define CONFIG_MAX_AP_ENTRIES 20
#define MAX_SITES CONFIG_MAX_AP_ENTRIES

struct site_survey {
    struct wlan_scan_result sites[MAX_SITES];
    unsigned int num_sites;
    os_mutex_t lock;
} survey;

static int prov_handle_scan_results(unsigned int count)
{
    int i, j = 0;

    /* WLAN firmware does not provide Noise Floor (NF) value with
     * every scan result. We call the function below to update a
     * global NF value so that /sys/scan can provide the latest NF value */
    wlan_get_current_nf();

    /* lock the scan results */
    if (os_mutex_get(&survey.lock, OS_WAIT_FOREVER) != WM_SUCCESS)
        return 0;

    /* clear out and refresh the site survey table */
    memset(survey.sites, 0, sizeof(survey.sites));

    /*
     * Loop through till we have results to process or
     * run out of space in survey.sites
     */
    for (i = 0; i < count && j < MAX_SITES; i++) {
        if (wlan_get_scan_result(i, &survey.sites[j]))
            break;

        if (survey.sites[j].ssid[0] != 0)
            j++;
    }
    survey.num_sites = j;

    /* unlock the site survey table */
    os_mutex_put(&survey.lock);
    /* Give up the semaphore to process next scan/prov_stop request */
    os_semaphore_put(&scan_protection_sem);
    return 0;
}

#define DEFAULT_SCAN_PROTECTION_TIMEOUT 1000

WIFIReturnCode_t WIFI_Scan( WIFIScanResult_t * pxBuffer,
                            uint8_t ucNumNetworks )
{
    int ret = 0;
    int i = 0;

    if (os_mutex_get(&wlan_mtx, OS_WAIT_FOREVER) != WM_SUCCESS)
           return eWiFiFailure;

    if (pxBuffer == NULL) {
           os_mutex_put(&wlan_mtx);
           return eWiFiFailure;
    }

    memset(pxBuffer, 0, sizeof(WIFIScanResult_t) * ucNumNetworks);

    ret = os_semaphore_create(&scan_protection_sem, "scanprotsem");
    if (ret != WM_SUCCESS) {
        os_mutex_put(&wlan_mtx);
        return eWiFiFailure;
    }

    ret = os_mutex_create(&survey.lock, "survey-mtx",
			OS_MUTEX_INHERIT);
    if (ret != WM_SUCCESS) {
        os_semaphore_delete(&scan_protection_sem);
        os_mutex_put(&wlan_mtx);
        return eWiFiFailure;
    }

    ret = os_semaphore_get(&scan_protection_sem, os_msec_to_ticks(
            DEFAULT_SCAN_PROTECTION_TIMEOUT * 1000));

    if (ret != WM_SUCCESS) {
        wm_wlan_e("Scan protection timeout occurred."
                   " Failed to get the scan protection for scan start"
                   " semaphore", ret);
        os_mutex_delete(&survey.lock);
        os_semaphore_delete(&scan_protection_sem);
        os_mutex_put(&wlan_mtx);
        return eWiFiFailure;
    }

    ret = wlan_scan(prov_handle_scan_results);
    if (ret != WM_SUCCESS)
    {
        os_mutex_delete(&survey.lock);
        os_semaphore_delete(&scan_protection_sem);
        os_mutex_put(&wlan_mtx);
        return eWiFiFailure;
    }

    ret = os_semaphore_get(&scan_protection_sem, os_msec_to_ticks(
            DEFAULT_SCAN_PROTECTION_TIMEOUT * 1000));
    if (ret != WM_SUCCESS) {
        wm_wlan_e("Scan protection timeout occurred."
                   " Failed to get the scan protection for scan result"
                   " semaphore", ret);
        os_mutex_delete(&survey.lock);
        os_semaphore_delete(&scan_protection_sem);
        os_mutex_put(&wlan_mtx);
        return eWiFiFailure;
    }

    if(survey.num_sites < ucNumNetworks ) {
        ucNumNetworks = survey.num_sites;
    }

    for(i = 0; i < ucNumNetworks; i++) {
        pxBuffer[i].cChannel = survey.sites[i].channel;
        pxBuffer[i].cRSSI = survey.sites[i].rssi;

        if (survey.sites[i].rssi < 128)
        {
            pxBuffer[i].cRSSI = pxBuffer[i].cRSSI * (-1);
        }

        if (survey.sites[i].ssid_len) {
            strncpy(pxBuffer[i].cSSID, survey.sites[i].ssid, survey.sites[i].ssid_len);
            pxBuffer[i].ucHidden = 0;
        } else {
//            strncpy(pxBuffer[i].cSSID, survey.sites[i].ssid, wificonfigMAX_SSID_LEN + 1);
            pxBuffer[i].ucHidden = 1;
        }

        memcpy((char *)pxBuffer[i].ucBSSID, survey.sites[i].bssid, wificonfigMAX_BSSID_LEN);

        if(survey.sites[i].wep) {
             pxBuffer[i].xSecurity = eWiFiSecurityWEP;
        }
        else if (survey.sites[i].wpa) {
             pxBuffer[i].xSecurity = eWiFiSecurityWPA;
        }
        else if (survey.sites[i].wpa2) {
             pxBuffer[i].xSecurity = eWiFiSecurityWPA2;
        }
        else if (survey.sites[i].wpa2_entp || survey.sites[i].wpa3_sae) {
             pxBuffer[i].xSecurity = eWiFiSecurityNotSupported;
        }
        else {
             pxBuffer[i].xSecurity = eWiFiSecurityOpen;
        }
    }

    os_mutex_delete(&survey.lock);
    os_semaphore_delete(&scan_protection_sem);

    if (os_mutex_put(&wlan_mtx) != WM_SUCCESS)
        return eWiFiFailure;

    return eWiFiSuccess;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_SetMode( WIFIDeviceMode_t xDeviceMode )
{
    /* FIX ME. */
    return eWiFiNotSupported;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_GetMode( WIFIDeviceMode_t * pxDeviceMode )
{
    /* FIX ME. */
    return eWiFiNotSupported;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_NetworkAdd( const WIFINetworkProfile_t * const pxNetworkProfile,
                                  uint16_t * pusIndex )
{
    /* FIX ME. */
#if (defined(IOT_WIFI_ENABLE_SAVE_NETWORK) && (IOT_WIFI_ENABLE_SAVE_NETWORK > 0))
    WIFIReturnCode_t ret = eWiFiSuccess;
    uint8_t savedIndex = IOT_WIFI_MAX_SAVED_NETWORKS;

    if ((NULL == pusIndex) || (NULL == pxNetworkProfile))
    {
        ret = eWiFiFailure;
    }

    if (eWiFiSuccess == ret)
    {
        for (uint8_t index = 0; index < IOT_WIFI_MAX_SAVED_NETWORKS; index ++ )
        {
            if (0 == strlen(NvmSavedWifiNetworkProfile[index].cSSID))
            {
                savedIndex = index;
                break;
            }
        }
        if (IOT_WIFI_MAX_SAVED_NETWORKS == savedIndex)
        {
            savedIndex = 0;
        }

        memcpy(&NvmSavedWifiNetworkProfile[savedIndex], pxNetworkProfile, sizeof(NvmSavedWifiNetworkProfile[savedIndex]));
        NvSyncSave(&NvmSavedWifiNetworkProfile[savedIndex], false);
        *pusIndex = savedIndex;
        NvmSavedWifiNetworkProfileIndex = savedIndex;
        NvSyncSave(&NvmSavedWifiNetworkProfileIndex, false);
    }
    return ret;
#else
    return eWiFiNotSupported;
#endif
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_NetworkGet( WIFINetworkProfile_t * pxNetworkProfile,
                                  uint16_t usIndex )
{
    /* FIX ME. */
#if (defined(IOT_WIFI_ENABLE_SAVE_NETWORK) && (IOT_WIFI_ENABLE_SAVE_NETWORK > 0))
    WIFIReturnCode_t ret = eWiFiSuccess;

    if ((NULL == pxNetworkProfile))
    {
        ret = eWiFiFailure;
    }

    if ((eWiFiSuccess == ret) && (usIndex >= IOT_WIFI_MAX_SAVED_NETWORKS))
    {
        ret = eWiFiNotSupported;
    }

    if (eWiFiSuccess == ret)
    {
        if (0 == strlen(NvmSavedWifiNetworkProfile[usIndex].cSSID))
        {
            ret = eWiFiNotSupported;
        }
        else
        {
            memcpy(pxNetworkProfile, &NvmSavedWifiNetworkProfile[usIndex], sizeof(*pxNetworkProfile));
        }
    }
    return ret;
#else
    return eWiFiNotSupported;
#endif
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_NetworkDelete( uint16_t usIndex )
{
    /* FIX ME. */
#if (defined(IOT_WIFI_ENABLE_SAVE_NETWORK) && (IOT_WIFI_ENABLE_SAVE_NETWORK > 0))
    WIFIReturnCode_t ret = eWiFiSuccess;

    if ((eWiFiSuccess == ret) && (usIndex >= IOT_WIFI_MAX_SAVED_NETWORKS))
    {
        ret = eWiFiNotSupported;
    }

    if (eWiFiSuccess == ret)
    {
        memset(&NvmSavedWifiNetworkProfile[usIndex], 0, sizeof(NvmSavedWifiNetworkProfile[usIndex]));
        NvSyncSave(&NvmSavedWifiNetworkProfile[usIndex], false);
    }
    return ret;
#else
    return eWiFiNotSupported;
#endif
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_Ping( uint8_t * pucIPAddr,
                            uint16_t usCount,
                            uint32_t ulIntervalMS )
{
    /* FIX ME. */
    return eWiFiNotSupported;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_GetIP( uint8_t * pucIPAddr )
{
    struct wlan_ip_config ip_addr;
    int ret;

    if (pucIPAddr == NULL) {
        return eWiFiFailure;
    }

    ret = wlan_get_address(&ip_addr);

    if (ret != WM_SUCCESS) {
        wm_wlan_e("app_network_config: failed to get IP address");
        memset(pucIPAddr, 0, 4);
        return eWiFiFailure;
     }

    memcpy(pucIPAddr, &(ip_addr.ipv4.address), 4);

    return eWiFiSuccess;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_GetMAC( uint8_t * pucMac )
{
    if (pucMac == NULL) {
        return eWiFiFailure;
    }

    if (WM_SUCCESS != wlan_get_mac_address(pucMac)) {
        return eWiFiFailure;
    }

    return eWiFiSuccess;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_GetHostIP( char * pcHost,
                                 uint8_t * pucIPAddr )
{
    /* FIX ME. */
    return eWiFiNotSupported;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_StartAP( void )
{
    /* FIX ME. */
    return eWiFiNotSupported;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_StopAP( void )
{
    /* FIX ME. */
    return eWiFiNotSupported;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_ConfigureAP( const WIFINetworkParams_t * const pxNetworkParams )
{
    /* FIX ME. */
    return eWiFiNotSupported;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_SetPMMode( WIFIPMMode_t xPMModeType,
                                 const void * pvOptionValue )
{
    /* FIX ME. */
    return eWiFiNotSupported;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_GetPMMode( WIFIPMMode_t * pxPMModeType,
                                 void * pvOptionValue )
{
    /* FIX ME. */
    return eWiFiNotSupported;
}
/*-----------------------------------------------------------*/

BaseType_t WIFI_IsConnected(void)
{
    if(is_sta_connected())
        return pdTRUE;

    return pdFALSE;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_RegisterNetworkStateChangeEventCallback( IotNetworkStateChangeEventCallback_t xCallback  )
{
    xEventCallback = xCallback;
    return eWiFiSuccess;
}

