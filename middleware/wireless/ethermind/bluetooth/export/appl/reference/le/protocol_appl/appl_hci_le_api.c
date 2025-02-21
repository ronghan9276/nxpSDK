
/**
 *  \file appl_hci_api.c
 *
 *  Source File for HCI Command Line Application.
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

/* ----------------------------------------- Header File Inclusion */
#include "appl_hci_le.h"

#ifdef BT_LE

/* ----------------------------------------- External Global Variables */


/* ----------------------------------------- Exported Global Variables */


/* ----------------------------------------- Static Global Variables */
#ifdef BT_5_0
#define MAX_NUM_OF_ANTENNA_ELEMENTS         0xFFU
#define MAX_EXTENDED_ADVERTISING_DATA_SIZE  0xFCU
#define MAX_SCAN_RSP_DATA_SIZE              0xFCU
#define APPL_MAX_LE_SCAN_TYPE               0x02U
#define APPL_MAX_LE_SCAN_INTERVAL           0x04U
#define APPL_MAX_LE_SCAN_WINDOW             0x04U
#define APPL_MAX_OWN_TYPE                   0x02U
#define APPL_MAX_PEER_ADDR_TYPE             0x02U
#define APPL_MAX_PEER_ADDR                  0x12U
#define APPL_MAX_SCANNING_FILTER_POLICY     0x02U
#define APPL_MAX_NO_OF_SETS                 0x3FU
#define APPL_USE_LEGACY_ADV_FIELD_IS_SET    0x04U

/* Maximum number of Initiating PHYs */
#define APPL_MAX_NUM_OF_INIT_PHYS           0x03U
/* Maximum number of Scanning PHYs */
#define APPL_MAX_NUM_OF_SCAN_PHYS           0x02U
#endif /* BT_5_0 */

/* Application data */
static UCHAR  appl_l2cap_le_fixed_data[L2CAP_HDR_LEN + 100U];

/* ----------------------------------------- Functions */
/* Send HCI_LE_SET_EVENT_MASK */
void appl_hci_le_set_event_mask(void)
{
    API_RESULT   retval;
    UCHAR        le_event_mask[8U];
    UINT32       index;
    unsigned int read_val;

    APPL_TRC("Enter le_event_mask : \n");
    for(index = 0U; index < 8U; index++)
    {
        scanf("%X", &read_val);
        le_event_mask[index] = (UCHAR) read_val;
    }
    retval = BT_hci_le_set_event_mask
             (
                 le_event_mask
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_READ_BUFFER_SIZE */
void appl_hci_le_read_buffer_size(void)
{
    API_RESULT retval;
    retval = BT_hci_le_read_buffer_size();

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_READ_LOCAL_SUPPORTED_FEATURES */
void appl_hci_le_read_local_supported_features(void)
{
    API_RESULT retval;
    retval = BT_hci_le_read_local_supported_features();

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_SET_RANDOM_ADDRESS */
void appl_hci_le_set_random_address(void)
{
    API_RESULT   retval;
    UCHAR        appl_random_address[BT_BD_ADDR_SIZE];

    APPL_TRC("Enter random_address : \n");
    appl_get_bd_addr(appl_random_address);

    retval = BT_hci_le_set_random_address
             (
                 appl_random_address
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_SET_ADVERTISING_PARAMETERS */
void appl_hci_le_set_advertising_parameters(void)
{
    API_RESULT   retval;
    UCHAR        advertising_channel_map;
    UCHAR        advertising_filter_policy;
    UCHAR        advertising_type;
    UCHAR        appl_direct_addr[BT_BD_ADDR_SIZE];
    UCHAR        direct_addr_type;
    UCHAR        own_addr_type;
    UINT16       advertising_interval_max;
    UINT16       advertising_interval_min;
    unsigned int read_val;

    BT_mem_set(appl_direct_addr, 0, BT_BD_ADDR_SIZE);
    direct_addr_type = 0U;

    APPL_TRC("Enter advertising_interval_min : \n");
    scanf("%X",&read_val);
    advertising_interval_min = (UINT16) read_val;

    APPL_TRC("Enter advertising_interval_max : \n");
    scanf("%X",&read_val);
    advertising_interval_max = (UINT16) read_val;

    APPL_TRC("Enter advertising_type : \n");
    scanf("%X",&read_val);
    advertising_type = (UCHAR) read_val;

    APPL_TRC("Enter own_addr_type : \n");
    scanf("%X",&read_val);
    own_addr_type = (UCHAR) read_val;

    APPL_TRC("Enter direct_addr_type : \n");
    scanf("%X",&read_val);
    direct_addr_type = (UCHAR) read_val;

    APPL_TRC("Enter direct_addr : \n");
    appl_get_bd_addr(appl_direct_addr);

    APPL_TRC("Enter advertising_channel_map : \n");
    scanf("%X",&read_val);
    advertising_channel_map = (UCHAR) read_val;

    APPL_TRC("Enter advertising_filter_policy : \n");
    scanf("%X",&read_val);
    advertising_filter_policy = (UCHAR) read_val;

    retval = BT_hci_le_set_advertising_parameters
             (
                 advertising_interval_min,
                 advertising_interval_max,
                 advertising_type,
                 own_addr_type,
                 direct_addr_type,
                 appl_direct_addr,
                 advertising_channel_map,
                 advertising_filter_policy
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_READ_ADVERTISING_CHANNEL_TX_POWER */
void appl_hci_le_read_advertising_channel_tx_power(void)
{
    API_RESULT retval;
    retval = BT_hci_le_read_advertising_channel_tx_power();

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_SET_ADVERTISING_DATA */
void appl_hci_le_set_advertising_data(void)
{
    API_RESULT   retval;
    UCHAR        advertising_data[31U];
    UCHAR        advertising_data_len;
    UINT32       index;
    unsigned int read_val;

    BT_mem_set(advertising_data, 0, 31U);

    APPL_TRC("Enter advertising_data_len : \n");
    scanf("%X", &read_val);
    advertising_data_len = (UCHAR) read_val;

    APPL_TRC("Enter advertising_data : \n");
    for(index = 0U; index<advertising_data_len; index++)
    {
        scanf("%X", &read_val);
        advertising_data[index] = (UCHAR) read_val;
    }
    retval = BT_hci_le_set_advertising_data
             (
                 advertising_data_len,
                 advertising_data
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_SET_SCAN_RESPONSE_DATA */
void appl_hci_le_set_scan_response_data(void)
{
    API_RESULT   retval;
    UCHAR        scan_data[31U];
    UCHAR        scan_data_len;
    UINT32       index;
    unsigned int read_val;

    BT_mem_set(scan_data, 0, 31U);

    APPL_TRC("Enter scan_data_len : \n");
    scanf("%X", &read_val);
    scan_data_len = (UCHAR) read_val;

    APPL_TRC("Enter scan_data : \n");
    for(index = 0U; index<scan_data_len; index++)
    {
        scanf("%X", &read_val);
        scan_data[index] = (UCHAR) read_val;
    }

    retval = BT_hci_le_set_scan_response_data
             (
                 scan_data_len,
                 scan_data
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_SET_ADVERTISING_ENABLE */
void appl_hci_le_set_advertising_enable(void)
{
    API_RESULT   retval;
    UCHAR        advertising_enable;
    unsigned int read_val;

    advertising_enable = 0x00U;

    APPL_TRC("Enter advertising_enable : \n");
    scanf("%X", &read_val);

    if (read_val == 1U)
    {
        printf("Advertising enable\n");
    }
    else if (read_val == 0U)
    {
        printf("Advertising disable\n");
    }
    else
    {
        advertising_enable = 0xFFU;
        printf("Invalid option\n");
    }

    if (0xFFU != advertising_enable)
    {
        advertising_enable = (UCHAR) read_val;

        retval = BT_hci_le_set_advertising_enable
                 (
                    advertising_enable
                 );

        if(API_SUCCESS != retval)
        {
            APPL_TRC("FAILED !!! Error code = %04X\n", retval);
        }
        else
        {
            APPL_TRC("API returned success...\n");
        }
    }

    return;
}

/* Send HCI_LE_SET_SCAN_PARAMETERS */
void appl_hci_le_set_scan_parameters(void)
{
    API_RESULT   retval;
    UCHAR        le_scan_type;
    UCHAR        own_addr_type;
    UCHAR        scan_filter_policy;
    UINT16       le_scan_interval;
    UINT16       le_scan_window;
    unsigned int read_val;

    APPL_TRC("Enter le_scan_type : \n");
    scanf("%X", &read_val);
    le_scan_type = (UCHAR) read_val;

    APPL_TRC("Enter le_scan_interval : \n");
    scanf("%X", &read_val);
    le_scan_interval = (UINT16) read_val;

    APPL_TRC("Enter le_scan_window : \n");
    scanf("%X", &read_val);
    le_scan_window = (UINT16) read_val;

    APPL_TRC("Enter own_addr_type : \n");
    scanf("%X", &read_val);
    own_addr_type = (UCHAR) read_val;

    APPL_TRC("Enter scan_filter_policy : \n");
    scanf("%X", &read_val);
    scan_filter_policy = (UCHAR) read_val;

    retval = BT_hci_le_set_scan_parameters
             (
                 le_scan_type,
                 le_scan_interval,
                 le_scan_window,
                 own_addr_type,
                 scan_filter_policy
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_SET_SCAN_ENABLE */
void appl_hci_le_set_scan_enable(void)
{
    API_RESULT   retval;
    UCHAR        filter_dups;
    UCHAR        le_scan_enable;
    unsigned int read_val;

    APPL_TRC("Enter le_scan_enable : \n");
    scanf("%X", &read_val);
    le_scan_enable = (UCHAR) read_val;

    APPL_TRC("Enter filter_dups : \n");
    scanf("%X", &read_val);
    filter_dups = (UCHAR) read_val;

    retval = BT_hci_le_set_scan_enable
             (
                 le_scan_enable,
                 filter_dups
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_CREATE_CONNECTION */
void appl_hci_le_create_connection(void)
{
    API_RESULT   retval;
    UCHAR        initiator_filter_policy;
    UCHAR        own_address_type;
    UCHAR        peer_address[BT_BD_ADDR_SIZE];
    UCHAR        peer_address_type;
    UINT16       conn_interval_max;
    UINT16       conn_interval_min;
    UINT16       conn_latency;
    UINT16       le_scan_interval;
    UINT16       le_scan_window;
    UINT16       maximum_ce_length;
    UINT16       minimum_ce_length;
    UINT16       supervision_timeout;
    unsigned int read_val;

    APPL_TRC("Set Default: Yes (1), No (0)\n");
    scanf("%X", &read_val);

    if (1U == read_val)
    {
        le_scan_interval        = (UINT16) 0x0040U;
        le_scan_window          = (UINT16) 0x0040U;
        initiator_filter_policy = (UCHAR) 0x00U;
        peer_address_type       = (UCHAR) 0x00U;

        CONSOLE_OUT("Enter peer_address : \n");
        appl_get_bd_addr(peer_address);

        CONSOLE_OUT("\n0 - Public\n1 - Random\n");
        CONSOLE_OUT("Enter Peer Address Type : \n");
        CONSOLE_IN("%u", &read_val);
        peer_address_type       = (UCHAR) read_val;

        CONSOLE_OUT("\n0 - Public\n1 - Random\n");
        CONSOLE_OUT("Enter Own Address Type : \n");
        CONSOLE_IN("%u", &read_val);
        own_address_type        = (UCHAR) read_val;

        conn_interval_min       = (UINT16) 0x0006U;
        conn_interval_max       = (UINT16) 0x0006U;
        conn_latency            = (UINT16) 0x0000U;
        supervision_timeout     = (UINT16) 0x03BBU;
        maximum_ce_length       = (UINT16) 0x0000U;
        minimum_ce_length       = (UINT16) 0x0000U;
    }
    else
    {
        APPL_TRC("Enter le_scan_interval : \n");
        scanf("%X", &read_val);
        le_scan_interval        = (UINT16) read_val;

        APPL_TRC("Enter le_scan_window : \n");
        scanf("%X", &read_val);
        le_scan_window          = (UINT16) read_val;

        APPL_TRC("Enter initiator_filter_policy : \n");
        scanf("%X", &read_val);
        initiator_filter_policy = (UCHAR) read_val;

        APPL_TRC("Enter peer_address_type : \n");
        scanf("%X", &read_val);
        peer_address_type       = (UCHAR) read_val;

        APPL_TRC("Enter peer_address : \n");
        appl_get_bd_addr(peer_address);

        APPL_TRC("Enter own_address_type : \n");
        scanf("%X", &read_val);
        own_address_type        = (UCHAR) read_val;

        APPL_TRC("Enter conn_interval_min : \n");
        scanf("%X", &read_val);
        conn_interval_min       = (UINT16) read_val;

        APPL_TRC("Enter conn_interval_max : \n");
        scanf("%X", &read_val);
        conn_interval_max       = (UINT16) read_val;

        APPL_TRC("Enter conn_latency : \n");
        scanf("%X", &read_val);
        conn_latency            = (UINT16) read_val;

        APPL_TRC("Enter supervision_timeout : \n");
        scanf("%X", &read_val);
        supervision_timeout     = (UINT16) read_val;

        APPL_TRC("Enter maximum_ce_length : \n");
        scanf("%X", &read_val);
        maximum_ce_length       = (UINT16) read_val;

        APPL_TRC("Enter minimum_ce_length : \n");
        scanf("%X", &read_val);
        minimum_ce_length       = (UINT16) read_val;
    }

    retval = BT_hci_le_create_connection
              (
                   le_scan_interval,
                   le_scan_window,
                   initiator_filter_policy,
                   peer_address_type,
                   peer_address,
                   own_address_type,
                   conn_interval_min,
                   conn_interval_max,
                   conn_latency,
                   supervision_timeout,
                   maximum_ce_length,
                   minimum_ce_length
              );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_CREATE_CONNECTION_CANCEL */
void appl_hci_le_create_connection_cancel(void)
{
    API_RESULT retval;
    retval = BT_hci_le_create_connection_cancel();

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_READ_WHITE_LIST_SIZE */
void appl_hci_le_read_white_list_size(void)
{
    API_RESULT retval;
    retval = BT_hci_le_read_white_list_size();

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_CLEAR_WHITE_LIST */
void appl_hci_le_clear_white_list(void)
{
    API_RESULT retval;
    retval = BT_hci_le_clear_white_list();

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_ADD_DEVICE_TO_WHITE_LIST */
void appl_hci_le_add_device_to_white_list(void)
{
    API_RESULT   retval;
    UCHAR        addr[BT_BD_ADDR_SIZE];
    UCHAR        addr_type;
    unsigned int read_val;

    APPL_TRC("Enter addr_type : \n");
    scanf("%X", &read_val);
    addr_type = (UCHAR) read_val;

    APPL_TRC("Enter addr : \n");
    appl_get_bd_addr(addr);

    retval = BT_hci_le_add_device_to_white_list
             (
                 addr_type,
                 addr
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_REMOVE_DEVICE_FROM_WHITE_LIST */
void appl_hci_le_remove_device_from_white_list(void)
{
    API_RESULT   retval;
    UCHAR        addr[BT_BD_ADDR_SIZE];
    UCHAR        addr_type;
    unsigned int read_val;

    APPL_TRC("Enter addr_type : \n");
    scanf("%X", &read_val);
    addr_type = (UCHAR) read_val;

    APPL_TRC("Enter addr : \n");
    appl_get_bd_addr(addr);

    retval = BT_hci_le_remove_device_from_white_list
             (
                 addr_type,
                 addr
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_CONNECTION_UPDATE */
void appl_hci_le_connection_update(void)
{
    API_RESULT   retval;
    UINT16       conn_interval_max;
    UINT16       conn_interval_min;
    UINT16       conn_latency;
    UINT16       connection_handle;
    UINT16       maximum_ce_length;
    UINT16       minimum_ce_length;
    UINT16       supervision_timeout;
    unsigned int read_val;

    APPL_TRC("Enter connection_handle : \n");
    scanf("%X", &read_val);
    connection_handle = (UINT16) read_val;

    APPL_TRC("Enter conn_interval_min : \n");
    scanf("%X", &read_val);
    conn_interval_min = (UINT16) read_val;

    APPL_TRC("Enter conn_interval_max : \n");
    scanf("%X", &read_val);
    conn_interval_max = (UINT16) read_val;

    APPL_TRC("Enter conn_latency : \n");
    scanf("%X", &read_val);
    conn_latency = (UINT16) read_val;

    APPL_TRC("Enter supervision_timeout : \n");
    scanf("%X", &read_val);
    supervision_timeout = (UINT16) read_val;

    APPL_TRC("Enter minimum_ce_length : \n");
    scanf("%X", &read_val);
    minimum_ce_length = (UINT16) read_val;

    APPL_TRC("Enter maximum_ce_length : \n");
    scanf("%X", &read_val);
    maximum_ce_length = (UINT16) read_val;

    retval = BT_hci_le_connection_update
             (
                 connection_handle,
                 conn_interval_min,
                 conn_interval_max,
                 conn_latency,
                 supervision_timeout,
                 minimum_ce_length,
                 maximum_ce_length
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_SET_HOST_CHANNEL_CLASSIFICATION */
void appl_hci_le_set_host_channel_classification(void)
{
    API_RESULT   retval;
    UCHAR        le_channel_map[5U];
    UINT32       index;
    unsigned int read_val;

    APPL_TRC("Enter le_channel_map (5 octets[LSB-MSB]): \n");
    for(index = 0U; index < 5U; index++)
    {
        scanf("%X", &read_val);
        le_channel_map[index] = (UCHAR) read_val;
    }

    retval = BT_hci_le_set_host_channel_classification
             (
                 le_channel_map
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_READ_CHANNEL_MAP */
void appl_hci_le_read_channel_map(void)
{
    API_RESULT   retval;
    UINT16       connection_handle;
    unsigned int read_val;

    APPL_TRC("Enter connection_handle : \n");
    scanf("%X", &read_val);
    connection_handle = (UINT16) read_val;

    retval = BT_hci_le_read_channel_map
             (
                 connection_handle
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_READ_REMOTE_USED_FEATURES */
void appl_hci_le_read_remote_used_features(void)
{
    API_RESULT   retval;
    UINT16       connection_handle;
    unsigned int read_val;

    APPL_TRC("Enter connection_handle : \n");
    scanf("%X", &read_val);
    connection_handle = (UINT16) read_val;
    retval = BT_hci_le_read_remote_used_features
             (
                 connection_handle
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_ENCRYPT */
void appl_hci_le_encrypt(void)
{
    API_RESULT   retval;
    UCHAR        key[16U];
    UCHAR        plain_text[16U];
    UINT32       index;
    unsigned int read_val;

    APPL_TRC("Enter key : \n");
    for(index = 0U; index < 16U; index++)
    {
        scanf("%X", &read_val);
        key[index] = (UCHAR) read_val;
    }

    APPL_TRC("Enter plain_text : \n");
    for(index = 0U; index < 16U; index++)
    {
        scanf("%X", &read_val);
        plain_text[index] = (UCHAR) read_val;
    }

    retval = BT_hci_le_encrypt
             (
                 key,
                 plain_text,
                 NULL
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_RAND */
void appl_hci_le_rand(void)
{
    API_RESULT retval;
    retval = BT_hci_le_rand();

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_START_ENCRYPTION */
void appl_hci_le_start_encryption(void)
{
    API_RESULT   retval;
    UCHAR        long_term_key[16U];
    UCHAR        random_number[8U];
    UINT16       conn_handle;
    UINT16       encrypted_diversifier;
    UINT32       index;
    unsigned int read_val;

    APPL_TRC("Enter conn_handle : \n");
    scanf("%X", &read_val);
    conn_handle = (UINT16) read_val;

    APPL_TRC("Enter random_number : \n");
    for(index = 0U; index < 8U; index++)
    {
        scanf("%X", &read_val);
        random_number[index] = (UCHAR) read_val;
    }

    APPL_TRC("Enter encrypted_diversifier : \n");
    scanf("%X", &read_val);
    encrypted_diversifier = (UINT16) read_val;

    APPL_TRC("Enter long_term_key : \n");
    for(index = 0U; index < 16U; index++)
    {
        scanf("%X", &read_val);
        long_term_key[index] = (UCHAR) read_val;
    }

    retval = BT_hci_le_start_encryption
             (
                 conn_handle,
                 random_number,
                 encrypted_diversifier,
                 long_term_key
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_LONG_TERM_KEY_REQUESTED_REPLY */
void appl_hci_le_long_term_key_requested_reply(void)
{
    API_RESULT   retval;
    UCHAR        long_term_key[16U];
    UINT16       connection_handle;
    UINT32       index;
    unsigned int read_val;

    APPL_TRC("Enter connection_handle : \n");
    scanf("%X", &read_val);
    connection_handle = (UINT16) read_val;

    APPL_TRC("Enter long_term_key : \n");
    for(index = 0U; index < 16U; index++)
    {
        scanf("%X", &read_val);
        long_term_key[index] = (UCHAR) read_val;
    }

    retval = BT_hci_le_long_term_key_requested_reply
             (
                 connection_handle,
                 long_term_key
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_LONG_TERM_KEY_REQUESTED_NEGATIVE_REPLY */
void appl_hci_le_long_term_key_requested_negative_reply(void)
{
    API_RESULT   retval;
    UINT16       connection_handle;
    unsigned int read_val;

    APPL_TRC("Enter connection_handle : \n");
    scanf("%X", &read_val);
    connection_handle = (UINT16) read_val;

    retval = BT_hci_le_long_term_key_requested_negative_reply
             (
                 connection_handle
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_READ_SUPPORTED_STATES */
void appl_hci_le_read_supported_states(void)
{
    API_RESULT retval;
    retval = BT_hci_le_read_supported_states();

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}


/* Send HCI_READ_TRANSMIT_POWER_LEVEL */
void appl_hci_read_transmit_power_level(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UCHAR        power_type;
    UINT16       handle;

    APPL_TRC("Read Transmit Power Leve. Enter Required Information ...\n");

    APPL_TRC("Connection Handle (in Hex) = "); fflush(stdout);
    scanf("%x", &read_val);
    handle = (UINT16)read_val;

    APPL_TRC("[Transmit Power Level: 0x00->Current, 0x01->Maximum]");
    APPL_TRC("Power Type (in Hex) = "); fflush(stdout);

    scanf("%x", &read_val);
    power_type = (UCHAR)read_val;

    APPL_TRC("\n");
    APPL_TRC("Starting Reat Transmit Power Level ...\n"); fflush(stdout);
    retval = BT_hci_read_transmit_power_level (handle, power_type);
    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !! Error Code = 0x%04x\n", retval);
    }
    else
    {
        APPL_TRC("Successfully started.\n");
    }

    return;
}

/* Send HCI_LE_RECEIVER_TEST_COMMAND */
void appl_hci_le_receiver_test_command(void)
{
    API_RESULT   retval;
    UCHAR        rx_frequency;
    unsigned int read_val;

    APPL_TRC("Enter rx_frequency : \n");
    scanf("%X", &read_val);
    rx_frequency = (UCHAR) read_val;
    retval = BT_hci_le_receiver_test_command
             (
                 rx_frequency
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

/* Send HCI_LE_TRANSMITTER_TEST_COMMAND */
void appl_hci_le_transmitter_test_command(void)
{
#ifdef HCI_TESTING_COMMANDS
    API_RESULT   retval;
    UCHAR        packet_payload;
    UCHAR        rx_frequency;
    UCHAR        test_data_length;
    unsigned int read_val;

    APPL_TRC("Enter rx_frequency : \n");
    scanf("%X", &read_val);
    rx_frequency = (UCHAR) read_val;

    APPL_TRC("Enter test_data_length : \n");
    scanf("%X", &read_val);
    test_data_length = (UCHAR) read_val;

    APPL_TRC("Enter packet_payload : \n");
    scanf("%X", &read_val);
    packet_payload = (UCHAR) read_val;

    retval = BT_hci_le_transmitter_test_command
             (
                 rx_frequency,
                 test_data_length,
                 packet_payload
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
#else /* HCI_TESTING_COMMANDS */
    APPL_TRC("Defien HCI_TESTING_COMMANDS for testing commands.\n");
#endif /* HCI_TESTING_COMMANDS */

    return;
}

/* Send HCI_LE_TEST_END */
void appl_hci_le_test_end(void)
{
#ifdef HCI_TESTING_COMMANDS
    API_RESULT retval;
    retval = BT_hci_le_test_end();

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
#else /* HCI_TESTING_COMMANDS */
    APPL_TRC("Defien HCI_TESTING_COMMANDS for testing commands.\n");
#endif /* HCI_TESTING_COMMANDS */

    return;
}

#ifdef HCI_LL_TOPOLOGY_CONN_UPDATE_SUPPORT
/* Remote Connection Parameter Request Reply */
void appl_hci_le_remote_conn_param_req_reply(void)
{
    API_RESULT   retval;
    UINT16       conn_interval_max;
    UINT16       conn_interval_min;
    UINT16       conn_latency;
    UINT16       connection_handle;
    UINT16       maximum_ce_length;
    UINT16       minimum_ce_length;
    UINT16       supervision_timeout;
    unsigned int read_val;

    APPL_TRC("Enter connection_handle : \n");
    scanf("%X", &read_val);
    connection_handle = (UINT16) read_val;

    APPL_TRC("Enter conn_interval_min : \n");
    scanf("%X", &read_val);
    conn_interval_min = (UINT16) read_val;

    APPL_TRC("Enter conn_interval_max : \n");
    scanf("%X", &read_val);
    conn_interval_max = (UINT16) read_val;

    APPL_TRC("Enter conn_latency : \n");
    scanf("%X", &read_val);
    conn_latency = (UINT16) read_val;

    APPL_TRC("Enter supervision_timeout : \n");
    scanf("%X", &read_val);
    supervision_timeout = (UINT16) read_val;

    APPL_TRC("Enter minimum_ce_length : \n");
    scanf("%X", &read_val);
    minimum_ce_length = (UINT16) read_val;

    APPL_TRC("Enter maximum_ce_length : \n");
    scanf("%X", &read_val);
    maximum_ce_length = (UINT16) read_val;

    retval = BT_hci_le_remote_conn_param_req_reply
             (
                  connection_handle,
                  conn_interval_min,
                  conn_interval_max,
                  conn_latency,
                  supervision_timeout,
                  minimum_ce_length,
                  maximum_ce_length
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
}

/* Remote Connection Parameter Request Negative Reply */
void appl_hci_le_remote_conn_param_req_negtive_reply(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UCHAR        reason;
    UINT16       handle;

    APPL_TRC("Remote Connection Parameter Request Negative Reply. Enter Required Information ...\n");

    APPL_TRC("LE Connection Handle (in Hex) = "); fflush(stdout);
    scanf("%x", &read_val);
    handle = (UINT16)read_val;

    APPL_TRC("Reason for Reject (in Hex) = "); fflush(stdout);
    scanf("%x", &read_val);
    reason = (UCHAR)read_val;

    APPL_TRC("\n");
    APPL_TRC("Starting Remote Connection Parameter Request Negative Reply ...\n"); fflush(stdout);

    retval = BT_hci_le_remote_conn_param_req_negtive_reply ( handle, reason );

    if ( retval != API_SUCCESS )
    {
        APPL_TRC("FAILED !! Error Code = 0x%04x\n", retval);
    }
    else
    {
        APPL_TRC("Successfully started.\n");
        APPL_TRC("Please wait for Remote Connection Parameter Request Negative Reply Complete.\n");
    }
}
#endif /* HCI_LL_TOPOLOGY_CONN_UPDATE_SUPPORT */

/* Read Authenticated Payload Timeout */
#ifdef HCI_READ_AUTHENTICATED_PAYLOAD_TIMEOUT_SUPPORT
void appl_hci_read_authenticated_payload_timeout(void)
{
    API_RESULT   retval;
    UINT16       connection_handle;
    unsigned int read_val;

    APPL_TRC("Enter connection_handle : \n");
    scanf("%X", &read_val);
    connection_handle = (UINT16)read_val;

    retval = BT_hci_read_authenticated_payload_timeout
        (
            connection_handle
        );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
}
#endif /* HCI_READ_AUTHENTICATED_PAYLOAD_TIMEOUT_SUPPORT */

/* Write Authenticated Payload Timeout */
#ifdef HCI_WRITE_AUTHENTICATED_PAYLOAD_TIMEOUT_SUPPORT
void appl_hci_write_authenticated_payload_timeout(void)
{
    API_RESULT   retval;
    UINT16       connection_handle, authenticated_payload_timeout;
    unsigned int read_val;

    APPL_TRC("Enter connection_handle : \n");
    scanf("%X", &read_val);
    connection_handle = (UINT16)read_val;

    APPL_TRC("Enter Autheticated Payload Timeout : \n");
    scanf("%X", &read_val);
    authenticated_payload_timeout = (UINT16)read_val;

    retval = BT_hci_write_authenticated_payload_timeout
        (
            connection_handle,
            authenticated_payload_timeout
        );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
}
#endif /* HCI_WRITE_AUTHENTICATED_PAYLOAD_TIMEOUT_SUPPORT */

void appl_le_send_data(void)
{
    API_RESULT     retval;
    BT_DEVICE_ADDR bd_addr;
    DEVICE_HANDLE  handle;
    unsigned int   read_val;
    UINT16         len;
    UINT16         lcid;
    UINT32         index;

    APPL_TRC("Enter Bluetooth address : \n");
    appl_get_bd_addr(bd_addr.addr);

    APPL_TRC("Enter bd_addr_type ");
    scanf("%X", &read_val);
    BT_BD_ADDR_TYPE(&bd_addr) = (UCHAR) read_val;

    APPL_TRC("On which lcid? ");
    scanf("%X", &read_val);
    lcid = (UINT16) read_val;

    APPL_TRC("Enter data length (<= %d) [in decimal]: ",
    (sizeof(appl_l2cap_le_fixed_data) - L2CAP_HDR_LEN));

    scanf("%d", &read_val);
    len = (UINT16) read_val;

    if (len > (sizeof(appl_l2cap_le_fixed_data) - L2CAP_HDR_LEN))
    {
        len = sizeof(appl_l2cap_le_fixed_data) - L2CAP_HDR_LEN;
    }

    APPL_TRC("Enter data : \n");
    for(index = 0U; index < len; index++)
    {
        scanf("%X", &read_val);
        appl_l2cap_le_fixed_data[index + L2CAP_HDR_LEN] = (UCHAR) read_val;
    }
    len += L2CAP_HDR_LEN;

    retval = device_queue_search_le_remote_addr (&handle,&bd_addr);

    retval = l2cap_fixed_channel_data_write
             (
                  &handle,
                  lcid,
                  appl_l2cap_le_fixed_data,
                  len
             );

    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
}

/* BT 4.2 related HCI LE Commands */
#ifdef BT_4_2

void appl_hci_le_set_data_length(void)
{
#ifdef HCI_LE_SET_DATA_LENGTH_SUPPORT
    UINT16       connection_handle;
    UINT16       tx_octets;
    UINT16       tx_time;
    unsigned int read_val;
    API_RESULT   retval;

    APPL_TRC("Enter connection_handle(in Hex): \n");
    scanf("%X", &read_val);
    connection_handle = (UINT16) read_val;

    APPL_TRC("Enter tx octets(in Hex): \n");
    scanf("%X", &read_val);
    tx_octets = (UINT16) read_val;

    APPL_TRC("Enter tx time(in Hex): \n");
    scanf("%X", &read_val);
    tx_time = (UINT16) read_val;

    retval = BT_hci_le_set_data_length
             (
                 connection_handle,
                 tx_octets,
                 tx_time
             );
    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
#else
    APPL_TRC("Define HCI_LE_SET_DATA_LENGTH_SUPPORT feature flag\n");
#endif /* HCI_LE_SET_DATA_LENGTH_SUPPORT */

    return;
}

void appl_hci_le_read_suggested_default_data_length(void)
{
#ifdef HCI_LE_READ_SUGGESTED_DEFAULT_DATA_LEN_SUPPORT
    API_RESULT retval;

    retval = BT_hci_le_read_suggested_default_data_length();
    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
#else
    APPL_TRC("Define HCI_LE_READ_SUGGESTED_DEFAULT_DATA_LEN_SUPPORT feature flag\n");
#endif /* HCI_LE_READ_SUGGESTED_DEFAULT_DATA_LEN_SUPPORT */

    return;
}

void appl_hci_le_write_suggested_default_data_length(void)
{
#ifdef HCI_LE_WRITE_SUGGESTED_DEFAULT_DATA_LEN_SUPPORT
    API_RESULT   retval;
    UINT16       tx_octets;
    UINT16       tx_time;
    unsigned int read_val;

    APPL_TRC("Enter tx octets(in Hex): \n");
    scanf("%X", &read_val);
    tx_octets = (UINT16) read_val;

    APPL_TRC("Enter tx time(in Hex): \n");
    scanf("%X", &read_val);
    tx_time = (UINT16) read_val;

    retval = BT_hci_le_write_suggested_default_data_length
            (
                tx_octets,
                tx_time
            );
    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
#else
    APPL_TRC("Define HCI_LE_WRITE_SUGGESTED_DEFAULT_DATA_LEN_SUPPORT feature flag\n");
#endif /* HCI_LE_WRITE_SUGGESTED_DEFAULT_DATA_LEN_SUPPORT */

    return;
}

void appl_hci_le_read_local_p256_public_key(void)
{
#ifdef HCI_LE_READ_LOCAL_P_256_PUBLIC_KEY_SUPPORT
    API_RESULT retval;

    retval = BT_hci_le_read_local_p256_public_key();
    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
#else
    APPL_TRC("HCI_LE_READ_LOCAL_P_256_PUBLIC_KEY_SUPPORT is not defined\n");
#endif /* HCI_LE_READ_LOCAL_P_256_PUBLIC_KEY_SUPPORT */

    return;
}

void appl_hci_le_generate_dhkey(void)
{
#ifdef HCI_LE_GENERATE_DHKEY_SUPPORT
    API_RESULT   retval;
    UCHAR        remote_public_key[64U];
    UCHAR        index;
    unsigned int read_val;

    APPL_TRC("Enter remote public key: \n");
    for(index = 0U; index < 64U; index++)
    {
        scanf("%X", &read_val);
        remote_public_key[index] = (UCHAR) read_val;
    }

    retval = BT_hci_le_generate_dhkey(remote_public_key);
    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
#else
    APPL_TRC("HCI_LE_GENERATE_DHKEY_SUPPORT is not defined\n");
#endif /* HCI_LE_GENERATE_DHKEY_SUPPORT */

    return;
}

void appl_hci_le_add_device_to_resolving_list(void)
{
#ifdef HCI_LE_ADD_DEV_TO_RESOLVING_LIST_SUPPORT
    API_RESULT   retval;
    UCHAR        peer_id_addr_type;
    UCHAR        peer_id_addr[BT_BD_ADDR_SIZE];
    UCHAR        peer_irk[16U];
    UCHAR        local_irk[16U];
    UCHAR        index;
    unsigned int read_val;

    APPL_TRC("Enter peer addr type: \n");
    scanf("%d", &read_val);
    peer_id_addr_type = (UCHAR )read_val;

    APPL_TRC("Enter peer identity addr: \n");
    appl_get_bd_addr(peer_id_addr);

    APPL_TRC("Enter peer IRK: \n");
    for(index = 0U; index < 16U; index++)
    {
        scanf("%X", &read_val);
        peer_irk[index] = (UCHAR) read_val;
    }

    APPL_TRC("Enter local IRK: \n");
    for(index = 0U; index < 16U; index++)
    {
        scanf("%X", &read_val);
        local_irk[index] = (UCHAR) read_val;
    }

    retval = BT_hci_le_add_device_to_resolving_list
                (
                    peer_id_addr_type,
                    peer_id_addr,
                    peer_irk,
                    local_irk
                );
    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
#else
    APPL_TRC("Define HCI_LE_ADD_DEV_TO_RESOLVING_LIST_SUPPORT feature flag\n");
#endif /* HCI_LE_ADD_DEV_TO_RESOLVING_LIST_SUPPORT */

    return;
}

void appl_hci_le_remove_device_from_resolving_list(void)
{
#ifdef HCI_LE_REMOVE_DEV_FROM_RESOLVING_LIST_SUPPORT
    API_RESULT   retval;
    UCHAR        peer_id_addr_type;
    UCHAR        peer_id_addr[BT_BD_ADDR_SIZE];
    unsigned int read_val;

    APPL_TRC("Enter peer addr type: \n");
    scanf("%d", &read_val);
    peer_id_addr_type = (UCHAR )read_val;

    APPL_TRC("Enter peer identity addr: \n");
    appl_get_bd_addr(peer_id_addr);

    retval = BT_hci_le_remove_device_from_resolving_list
                (
                    peer_id_addr_type,
                    peer_id_addr
                );
    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
#else
    APPL_TRC("Define HCI_LE_REMOVE_DEV_FROM_RESOLVING_LIST_SUPPORT feature flag\n");
#endif /* HCI_LE_REMOVE_DEV_FROM_RESOLVING_LIST_SUPPORT */

    return;
}

void appl_hci_le_clear_resolving_list(void)
{
#ifdef HCI_LE_CLR_RESOLVING_LIST_SUPPORT
    API_RESULT retval;

    retval = BT_hci_le_clear_resolving_list();
    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
#else
    APPL_TRC("Define HCI_LE_CLR_RESOLVING_LIST_SUPPORT feature flag\n");
#endif /* HCI_LE_CLR_RESOLVING_LIST_SUPPORT */

    return;
}

void appl_hci_le_read_resolving_list_size(void)
{
#ifdef HCI_LE_READ_RESOLVING_LIST_SIZE_SUPPORT
    API_RESULT retval;

    retval = BT_hci_le_read_resolving_list_size();
    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
#else
    APPL_TRC("Defined HCI_LE_READ_RESOLVING_LIST_SIZE_SUPPORT feature flag\n");
#endif /* HCI_LE_READ_RESOLVING_LIST_SIZE_SUPPORT */

    return;
}

void appl_hci_le_read_peer_resolvable_address(void)
{
#ifdef HCI_LE_READ_PEER_RESOLVABLE_ADDR_SUPPORT
    API_RESULT   retval;
    UCHAR        peer_id_addr_type;
    UCHAR        peer_id_addr[BT_BD_ADDR_SIZE];
    unsigned int read_val;

    APPL_TRC("Enter peer addr type: \n");
    scanf("%d", &read_val);
    peer_id_addr_type = (UCHAR )read_val;

    APPL_TRC("Enter peer identity addr: \n");
    appl_get_bd_addr(peer_id_addr);

    retval = BT_hci_le_read_peer_resolvable_address
                (
                    peer_id_addr_type,
                    peer_id_addr
                );
    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
#else
    APPL_TRC("Define HCI_LE_READ_PEER_RESOLVABLE_ADDR_SUPPORT feature flag\n");
#endif /* HCI_LE_READ_PEER_RESOLVABLE_ADDR_SUPPORT */

    return;
}

void appl_hci_le_read_local_resolvable_address(void)
{
#ifdef HCI_LE_READ_LOCAL_RESOLVABLE_ADDR_SUPPORT
    API_RESULT   retval;
    UCHAR        peer_id_addr_type;
    UCHAR        peer_id_addr[BT_BD_ADDR_SIZE];
    unsigned int read_val;

    APPL_TRC("Enter peer addr type: \n");
    scanf("%d", &read_val);
    peer_id_addr_type = (UCHAR )read_val;

    APPL_TRC("Enter peer identity addr: \n");
    appl_get_bd_addr(peer_id_addr);

    retval = BT_hci_le_read_local_resolvable_address
                (
                    peer_id_addr_type,
                    peer_id_addr
                );
    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
#else
    APPL_TRC("Define HCI_LE_READ_LOCAL_RESOLVABLE_ADDR_SUPPORT feature flag\n");
#endif /* HCI_LE_READ_LOCAL_RESOLVABLE_ADDR_SUPPORT */

    return;
}

void appl_hci_le_set_address_resolution_enable(void)
{
#ifdef HCI_LE_SET_ADDR_RESOLUTION_ENABLE_SUPPORT
    API_RESULT   retval;
    UCHAR        addr_resolution_enable;
    unsigned int read_val;

    APPL_TRC("Enter addr resolution enable: \n");
    APPL_TRC("    0 -> Disable\n");
    APPL_TRC("    1 -> Enable\n");
    scanf("%X", &read_val);
    addr_resolution_enable = (UCHAR) read_val;

    retval = BT_hci_le_set_address_resolution_enable(addr_resolution_enable);
    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
#endif /* HCI_LE_SET_ADDR_RESOLUTION_ENABLE_SUPPORT */

    return;
}

void appl_hci_le_set_resolvable_private_address_timeout(void)
{
#ifdef HCI_LE_SET_RESOLVABLE_PRIVATE_ADDR_TIMEOUT_SUPPORT
    UINT16       rpa_timeout;
    API_RESULT   retval;
    unsigned int read_val;

    APPL_TRC("Enter RPA timeout(in Hex): \n");
    scanf("%X",  &read_val);
    rpa_timeout = (UINT16) read_val;

    retval = BT_hci_le_set_resolvable_private_address_timeout (rpa_timeout);
    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
#else
    APPL_TRC("Define HCI_LE_SET_RESOLVABLE_PRIVATE_ADDR_TIMEOUT_SUPPORT feature flag\n");
#endif /* HCI_LE_SET_RESOLVABLE_PRIVATE_ADDR_TIMEOUT_SUPPORT */

    return;
}

void appl_hci_le_read_maximum_data_length(void)
{
#ifdef HCI_LE_READ_MAXIMUM_DATA_LEN_SUPPORT
    API_RESULT retval;

    retval = BT_hci_le_read_maximum_data_length();
    if(API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
#else
    APPL_TRC("Define HCI_LE_READ_MAXIMUM_DATA_LEN_SUPPORT feature flag\n");
#endif /* HCI_LE_READ_MAXIMUM_DATA_LEN_SUPPORT */

    return;
}
#endif /* BT_4_2 */

#ifdef BT_5_0
/* Send HCI_LE_READ_PHY */
void appl_hci_le_read_phy(void)
{
    API_RESULT    retval;
    unsigned int  read_val;
    UINT16        handle;

    APPL_TRC("ACL Connection Handle (in Hex) = \n");
    scanf("%x", &read_val);
    handle = (UINT16)read_val;

    retval = BT_hci_read_phy(handle);

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
}

/* Send HCI_LE_SET_DEFAULT_PHY */
void appl_hci_le_set_default_phy(void)
{
    API_RESULT   retval;
    UCHAR        allphy;
    UCHAR        txphy;
    UCHAR        rxphy;
    unsigned int read_val;

    APPL_TRC("ALL Phy (in Hex) = \n");
    scanf("%x", &read_val);
    allphy = (UCHAR)read_val;

    APPL_TRC("TX Phy (in Hex) = \n");
    scanf("%x", &read_val);
    txphy = (UCHAR)read_val;

    APPL_TRC("RX Phy (in Hex) = \n");
    scanf("%x", &read_val);
    rxphy = (UCHAR)read_val;

    retval = BT_hci_le_set_default_phy(allphy, txphy, rxphy);

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
}

/* Send HCI_LE_SET_PHY */
void appl_hci_le_set_phy(void)
{
    API_RESULT   retval;
    UINT16       handle;
    UCHAR        allphy;
    UCHAR        txphy;
    UCHAR        rxphy;
    UINT16       phy_options;
    unsigned int read_val;

    APPL_TRC("Connection handle (in Hex) = \n");
    scanf("%x", &read_val);
    handle = (UINT16)read_val;

    APPL_TRC("ALL Phy (in Hex) = \n");
    scanf("%x", &read_val);
    allphy = (UCHAR)read_val;

    APPL_TRC("TX Phy (in Hex) = \n");
    scanf("%x", &read_val);
    txphy = (UCHAR)read_val;

    APPL_TRC("RX Phy (in Hex) = \n");
    scanf("%x", &read_val);
    rxphy = (UCHAR)read_val;

    APPL_TRC("PHY_options (in Hex) = \n");
    scanf("%x", &read_val);
    phy_options = (UINT16)read_val;

    retval = BT_hci_le_set_phy
             (
                 handle,
                 allphy,
                 txphy,
                 rxphy,
                 phy_options
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
}

void appl_hci_le_set_extended_advertising_params(void)
{
    int     read_val;
    UCHAR   adv_handle;
    UINT32  pri_adv_intval_min;
    UINT32  pri_adv_intval_max;
    UCHAR   channel_map;
    UCHAR   own_addr_type;
    UCHAR   peer_addr_type;
    UCHAR   peer_addr[BT_BD_ADDR_SIZE];
    UCHAR   adv_filter_policy;
    CHAR    adv_tx_power;
    UCHAR   pri_adv_phy;
    UCHAR   sec_adv_max_skip;
    UCHAR   sec_adv_phy;
    UCHAR   adv_sid;
    UCHAR   scan_rsp_ntf_enable;
    UCHAR   adv_event_prty;
    API_RESULT retval;

    APPL_TRC("Enter adv_handle : \n");
    scanf("%x", &read_val);
    adv_handle = (UCHAR)read_val;

    APPL_TRC("Enter adv_event_prty: \n");
    scanf("%x", &read_val);
    adv_event_prty = (UCHAR)read_val;

    APPL_TRC("Enter Primary_Advertising_Interval_Min: \n");
    scanf("%x", &read_val);
    pri_adv_intval_min = (UINT32)read_val;

    APPL_TRC("Enter Primary_Advertising_Interval_Max : \n");
    scanf("%x", &read_val);
    pri_adv_intval_max = (UINT32)read_val;

    APPL_TRC("Enter channel_map : \n");
    scanf("%x", &read_val);
    channel_map = (UCHAR)read_val;

    APPL_TRC("Enter own_addr_type : \n");
    scanf("%x", &read_val);
    own_addr_type = (UCHAR)read_val;

    APPL_TRC("Enter peer address type : \n");
    scanf("%x", &read_val);
    peer_addr_type = (UCHAR)read_val;

    APPL_TRC("Enter peer address : \n");
    appl_get_bd_addr(peer_addr);

    APPL_TRC("Enter advertising_filter_policy : \n");
    scanf("%x", &read_val);
    adv_filter_policy = (UCHAR)read_val;

    APPL_TRC("Enter adv_tx_power [in Decimal] : \n");
    scanf("%d", &read_val);
    adv_tx_power = (CHAR)read_val;

    APPL_TRC("Enter Primary_Advertising_PHY : \n");
    scanf("%x", &read_val);
    pri_adv_phy = (UCHAR)read_val;

    APPL_TRC("Enter sec_adv_max_skip : \n");
    scanf("%x", &read_val);
    sec_adv_max_skip = (UCHAR)read_val;

    APPL_TRC("Enter Secondary_Advertising_PHY : \n");
    scanf("%x", &read_val);
    sec_adv_phy = (UCHAR)read_val;

    APPL_TRC("Enter Advertising_SID [In HEX] : \n");
    scanf("%x", &read_val);
    adv_sid = (UCHAR)read_val;

    APPL_TRC("Enter Scan_Request_Notification_Enable: \n");
    scanf("%x", &read_val);
    scan_rsp_ntf_enable = (UCHAR)read_val;

    retval = BT_hci_le_set_extended_advertising_parameters
             (
                 adv_handle,
                 adv_event_prty,
                 pri_adv_intval_min,
                 pri_adv_intval_max,
                 channel_map,
                 own_addr_type,
                 peer_addr_type,
                 peer_addr,
                 adv_filter_policy,
                 adv_tx_power,
                 pri_adv_phy,
                 sec_adv_max_skip,
                 sec_adv_phy,
                 adv_sid,
                 scan_rsp_ntf_enable
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
}

void appl_hci_le_set_periodic_adv_params(void)
{
    int        read_val;
    UCHAR      periodic_adv_hndl;
    UINT16     periodic_adv_intval_min;
    UINT16     periodic_adv_intval_max;
    UINT16     periodic_adv_prtys;
    API_RESULT retval;

    APPL_TRC("Enter advertising Handle : \n");
    scanf("%x", &read_val);
    periodic_adv_hndl = (UCHAR)read_val;

    APPL_TRC("Enter Periodic Avertising interval Minimum : \n");
    scanf("%x", &read_val);
    periodic_adv_intval_min = (UINT16)read_val;

    APPL_TRC("Enter Periodic Avertising interval Maximum : \n");
    scanf("%x", &read_val);
    periodic_adv_intval_max = (UINT16)read_val;

    APPL_TRC("Enter Periodic Advertising Properties : \n");
    scanf("%x", &read_val);
    periodic_adv_prtys = (UINT16)read_val;

    retval = BT_hci_le_set_periodic_advertising_parameters
             (
                 periodic_adv_hndl,
                 periodic_adv_intval_min,
                 periodic_adv_intval_max,
                 periodic_adv_prtys
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
}

void appl_hci_le_set_extended_advertising_data(void)
{
    unsigned int read_val;
    UCHAR        adv_handle;
    UCHAR        optns;
    UINT32       index;
    UCHAR        frgment_pref;
    UCHAR        adv_data_len;
    UCHAR        data[MAX_EXTENDED_ADVERTISING_DATA_SIZE];

    API_RESULT retval;

    APPL_TRC("Enter Advertising Handle : \n");
    scanf("%x", &read_val);
    adv_handle = (UCHAR)read_val;

    APPL_TRC("Enter Operations: \n");
    scanf("%x", &read_val);
    optns = (UCHAR)read_val;

    APPL_TRC("Fragment_Preference: \n");
    scanf("%x", &read_val);
    frgment_pref = (UCHAR)read_val;

    APPL_TRC("Enter Extended Advertertising data length in[DECIMAL]: \n");
    scanf("%d", &read_val);
    adv_data_len = (UCHAR)read_val;

    /* Initialize the Advertising Response Data field */
    BT_mem_set
    (
        &data[0U],
        0x00,
        MAX_EXTENDED_ADVERTISING_DATA_SIZE
    );

    APPL_TRC("Enter Extended Advertertising data: \n");
    for (index = 0U; index < adv_data_len; index++)
    {
        scanf("%x", &read_val);
        data[index] = (UCHAR)read_val;
    }

    retval = BT_hci_le_set_extended_advertising_data
             (
                 adv_handle,
                 optns,
                 frgment_pref,
                 adv_data_len,
                 data
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
}

void appl_hci_le_set_extended_scan_response_data(void)
{
    unsigned int read_val;
    UCHAR        adv_handle;
    UCHAR        optns;
    UCHAR        frag_pref;
    UINT32       index;
    UCHAR        scan_rsp_data_len;
    UCHAR        scan_rsp_data[MAX_SCAN_RSP_DATA_SIZE];
    API_RESULT   retval;

    APPL_TRC("Enter advertising_handle: \n");
    scanf("%x", &read_val);
    adv_handle = (UCHAR)read_val;

    APPL_TRC("Enter Operations: \n");
    scanf("%x", &read_val);
    optns = (UCHAR)read_val;

    APPL_TRC("Enter fragment Preference: \n");
    scanf("%x", &read_val);
    frag_pref = (UCHAR)read_val;

    APPL_TRC("Enter Scan Response data length [in Decimal]: \n");
    scanf("%d", &read_val);
    scan_rsp_data_len = (UCHAR)read_val;

    APPL_TRC("Enter Extended Scan Response data: \n");
    for (index = 0U; index < scan_rsp_data_len; index++)
    {
        scanf("%x", &read_val);
        scan_rsp_data[index] = (UCHAR)read_val;
    }

    retval = BT_hci_le_set_extended_scan_response_data
             (
                 adv_handle,
                 optns,
                 frag_pref,
                 scan_rsp_data_len,
                 scan_rsp_data
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
}

void appl_hci_le_set_extended_advertise_enable(void)
{
    unsigned int read_val;
    UCHAR        enable;
    UCHAR        no_of_sets;
    UCHAR        adv_handle[APPL_MAX_NO_OF_SETS];
    UINT16       duration[APPL_MAX_NO_OF_SETS];
    UCHAR        max_ext_adv_events[APPL_MAX_NO_OF_SETS];
    UCHAR        i;
    API_RESULT   retval;

    APPL_TRC("Enter enable : \n");
    scanf("%x", &read_val);
    enable = (UCHAR)read_val;

    APPL_TRC("Enter number of sets : \n");
    scanf("%x", &read_val);
    no_of_sets = (UCHAR)read_val;

    for (i = 0U; i < no_of_sets; i++)
    {
        APPL_TRC("Enter advertising handle for %dth\n", i);
        scanf("%x", &read_val);
        adv_handle[i] = (UCHAR)read_val;

        APPL_TRC("Enter duration for %dth\n", i);
        scanf("%x", &read_val);
        duration[i] = (UINT16)read_val;

        APPL_TRC("Enter Max Extended Advertising Event for %dth\n", i);
        scanf("%x", &read_val);
        max_ext_adv_events[i] = (UCHAR)read_val;
    }

    retval = BT_hci_le_set_extended_advertising_enable
             (
                 enable,
                 no_of_sets,
                 adv_handle,
                 duration,
                 max_ext_adv_events
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
}

void appl_hci_le_read_max_advertising_data_length(void)
{
    APPL_TRC("\nReading the maximum advertising data length\n\n");
    (BT_IGNORE_RETURN_VALUE) BT_hci_le_read_maximum_advertising_data_length();
}

void appl_hci_le_read_num_supported_advertising_sets(void)
{
    APPL_TRC("\nReading the number of supported advertising sets\n\n");
    (BT_IGNORE_RETURN_VALUE) BT_hci_le_read_num_supported_advertising_sets();
}

void appl_hci_le_read_transmit_power(void)
{
    APPL_TRC("\nReading the advertising transmit power\n\n");
    (BT_IGNORE_RETURN_VALUE) BT_hci_le_read_transmit_power();
}

void appl_hci_le_remove_advertising_set(void)
{
    unsigned int read_val;
    UCHAR        adv_handle;

    APPL_TRC("Enter advertising Handle : \n");
    scanf("%x", &read_val);
    adv_handle = (UCHAR)read_val;

    APPL_TRC("\nRemoving the advertising set\n\n");
    (BT_IGNORE_RETURN_VALUE) BT_hci_le_remove_advertising_set(adv_handle);
}

void appl_hci_le_clear_advertising_sets(void)
{
    APPL_TRC("\nClearing the advertising sets\n\n");
    (BT_IGNORE_RETURN_VALUE) BT_hci_le_clear_advertising_sets();
}

void appl_hci_le_set_extended_scan_parameters(void)
{
    unsigned int read_val;
    UCHAR        own_addr_type;
    UCHAR        scanning_filr_policy;
    UCHAR        scan_phy;

    UCHAR        scan_type[APPL_MAX_NUM_OF_SCAN_PHYS];
    UINT16       scan_intval[APPL_MAX_NUM_OF_SCAN_PHYS];
    UINT16       scan_window[APPL_MAX_NUM_OF_SCAN_PHYS];
    API_RESULT   retval;
    UCHAR        index;

    BT_mem_set(scan_type, 0x00, sizeof(scan_type));
    BT_mem_set(scan_intval, 0x00, sizeof(scan_intval));
    BT_mem_set(scan_window, 0x00, sizeof(scan_window));

    APPL_TRC("Enter own_address_type: \n");
    scanf("%x", &read_val);
    own_addr_type = (UCHAR)read_val;

    APPL_TRC("Enter scanning_filter_policy: \n");
    scanf("%x", &read_val);
    scanning_filr_policy = (UCHAR)read_val;

    APPL_TRC("Enter scanning_phy : \n");
    APPL_TRC("0x01 for LE 1M PHY\n");
    APPL_TRC("0x04 for LE Coded PHY\n");
    APPL_TRC("0x05 for both 1M and LE Coded PHY\n");
    scanf("%x", &read_val);
    scan_phy = (UCHAR)read_val;

    index = 0U;
    if (0U != (HCI_LE_SET_EXT_SCAN_PARAM_1M_PHY_MASK & scan_phy))
    {
        APPL_TRC("For LE 1M PHY: \n");

        APPL_TRC("Enter le_scan_type: \n");
        scanf("%x", &read_val);
        scan_type[index] = (UCHAR)read_val;

        APPL_TRC("Enter le_scan_interval: \n");
        scanf("%x", &read_val);
        scan_intval[index] = (UINT16)read_val;

        APPL_TRC("Enter le_scan_window: \n");
        scanf("%x", &read_val);
        scan_window[index] = (UINT16)read_val;

        index += 1U;
    }

    if (0U != (HCI_LE_SET_EXT_SCAN_PARAM_CODED_PHY_MASK & scan_phy))
    {
        APPL_TRC("For LE Coded PHY: \n");

        APPL_TRC("Enter le_scan_type: \n");
        scanf("%x", &read_val);
        scan_type[index] = (UCHAR)read_val;

        APPL_TRC("Enter le_scan_interval: \n");
        scanf("%x", &read_val);
        scan_intval[index] = (UINT16)read_val;

        APPL_TRC("Enter le_scan_window: \n");
        scanf("%x", &read_val);
        scan_window[index] = (UINT16)read_val;
    }

    retval = BT_hci_le_set_extended_scan_parameters
             (
                 own_addr_type,
                 scanning_filr_policy,
                 scan_phy,
                 scan_type,
                 scan_intval,
                 scan_window
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
}

void appl_hci_le_set_extended_scan_enable(void)
{
    UINT32     read_val;
    UCHAR      enable;
    UCHAR      fter_duplicates;
    UINT16     durn;
    UINT16     period;
    API_RESULT retval;

    APPL_TRC("Enter enable : \n");
    scanf("%x", &read_val);
    enable = (UCHAR)read_val;

    APPL_TRC("Enter filter_duplicates : \n");
    scanf("%x", &read_val);
    fter_duplicates = (UCHAR)read_val;

    APPL_TRC("Enter duration : \n");
    scanf("%x", &read_val);
    durn = (UINT16)read_val;

    APPL_TRC("Enter Period : \n");
    scanf("%x", &read_val);
    period = (UINT16)read_val;

    retval = BT_hci_le_set_extended_scan_enable
             (
                 enable,
                 fter_duplicates,
                 durn,
                 period
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }
}

void appl_hci_le_periodic_adv_create_sync(void)
{
    unsigned int read_val;
    UCHAR        options;
    UCHAR        adv_sid;
    UCHAR        addr_type;
    UCHAR        addr[BT_BD_ADDR_SIZE];
    UINT16       skip;
    UINT16       sync_timeout;
    UCHAR        sync_cte_type;
    API_RESULT   retval;

    APPL_TRC("Enter Options: \n");
    scanf("%x", &read_val);
    options = (UCHAR)read_val;

    APPL_TRC("Enter Advertising_SID: \n");
    scanf("%x", &read_val);
    adv_sid = (UCHAR)read_val;

    APPL_TRC("Enter Peer address_type: \n");
    scanf("%x", &read_val);
    addr_type = (UCHAR)read_val;

    APPL_TRC("Enter Peer address : \n");
    appl_get_bd_addr(addr);

    APPL_TRC("Enter skip: \n");
    scanf("%x", &read_val);
    skip = (UINT16)read_val;

    APPL_TRC("Enter sync_timeout: \n");
    scanf("%x", &read_val);
    sync_timeout = (UINT16)read_val;

    APPL_TRC("Enter sync_cte_type: \n");
    scanf("%x", &read_val);
    sync_cte_type = (UCHAR)read_val;

    retval = BT_hci_le_periodic_adv_create_sync
             (
                 options,
                 adv_sid,
                 addr_type,
                 addr,
                 skip,
                 sync_timeout,
                 sync_cte_type
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_add_dev_to_periodic_advertiser_list(void)
{
    unsigned int read_val;
    UCHAR        addr_type;
    UCHAR        addr[BT_BD_ADDR_SIZE];
    UCHAR        adv_sid;
    API_RESULT   retval;

    APPL_TRC("Enter Advertiser_Address_Type: \n");
    scanf("%x", &read_val);
    addr_type = (UCHAR)read_val;

    APPL_TRC("Enter Advertiser_Address : \n");
    appl_get_bd_addr(addr);

    APPL_TRC("Enter Advertising_SID: \n");
    scanf("%x", &read_val);
    adv_sid = (UCHAR)read_val;

    retval = BT_hci_le_add_device_to_periodic_advertiser_list
             (
                 addr_type,
                 addr,
                 adv_sid
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_rm_dev_from_periodic_advertiser_list(void)
{
    unsigned int read_val;
    UCHAR        addr_type;
    UCHAR        addr[BT_BD_ADDR_SIZE];
    UCHAR        adv_sid;
    API_RESULT   retval;

    APPL_TRC("Enter Advertiser_Address_Type: \n");
    scanf("%x", &read_val);
    addr_type = (UCHAR)read_val;

    APPL_TRC("Enter Advertiser_Address : \n");
    appl_get_bd_addr(addr);

    APPL_TRC("Enter Advertising_SID: \n");
    scanf("%x", &read_val);
    adv_sid = (UCHAR)read_val;

    retval = BT_hci_le_remove_device_from_periodic_advertiser_list
             (
                 addr_type,
                 addr,
                 adv_sid
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_clear_periodic_advertiser_list(void)
{
    APPL_TRC("\nClearning the periodic advertising list\n\n");
    (BT_IGNORE_RETURN_VALUE) BT_hci_le_clear_periodic_advertiser_list();

    return;
}

void appl_hci_le_read_periodic_advertiser_list_size(void)
{
    APPL_TRC("\nReading the periodic advertising list size\n\n");
    (BT_IGNORE_RETURN_VALUE) BT_hci_le_read_periodic_advertiser_list_size();

    return;
}

void appl_hci_le_write_rf_path_compensation(void)
{
    unsigned int  read_val;
    UINT16        rf_tx_path_compn_val;
    UINT16        rf_rx_path_compn_val;
    API_RESULT    retval;

    APPL_TRC("Enter rf_tx_path_compn_val : \n");
    scanf("%x", &read_val);
    rf_tx_path_compn_val = (UINT16)read_val;

    APPL_TRC("Enter rf_rx_path_compn_val : \n");
    scanf("%x", &read_val);
    rf_rx_path_compn_val = (UINT16)read_val;

    retval = BT_hci_le_write_rf_path_compensation
             (
                 rf_tx_path_compn_val,
                 rf_rx_path_compn_val
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_read_rf_path_compensation(void)
{
    APPL_TRC("\nReading the RF Path Compensation\n");
    (BT_IGNORE_RETURN_VALUE) BT_hci_le_read_rf_path_compensation();

    return;
}

void appl_hci_le_set_advertising_random_address(void)
{
    unsigned int  read_val;
    UCHAR         adv_handle;
    UCHAR         random_addr[BT_BD_ADDR_SIZE];
    API_RESULT    retval;

    APPL_TRC("Enter advertising_handle in[HEX]: \n");
    scanf("%x", &read_val);
    adv_handle = (UCHAR)read_val;

    APPL_TRC("Enter random_address in[HEX]: \n");
    appl_get_bd_addr(random_addr);

    retval = BT_hci_le_set_adv_set_random_address
             (
                 adv_handle,
                 random_addr
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_set_periodic_advertising_data(void)
{
    unsigned int  read_val;
    UCHAR         adv_hndl;
    UCHAR         oprtn;
    UCHAR         adv_data_len;
    UCHAR         adv_data[MAX_EXTENDED_ADVERTISING_DATA_SIZE];
    UINT32        index;
    API_RESULT    retval;

    APPL_TRC("Enter Advertising handle in[HEX]: \n");
    scanf("%x", &read_val);
    adv_hndl = (UCHAR)read_val;

    APPL_TRC("Enter Operation in[HEX]: \n");
    scanf("%x", &read_val);
    oprtn = (UCHAR)read_val;

    APPL_TRC("Enter adv_data_len in[DECIMAL]: \n");
    scanf("%d", &read_val);
    adv_data_len = (UCHAR)read_val;

    APPL_TRC("Enter periodic advertising data in[HEX]: \n");
    for (index = 0U; index < adv_data_len; index++)
    {
        scanf("%x", &read_val);
        adv_data[index] = (UCHAR)read_val;
    }

    retval = BT_hci_le_set_periodic_advertising_data
             (
                 adv_hndl,
                 oprtn,
                 adv_data_len,
                 adv_data
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_set_periodic_advertising_enable(void)
{
    unsigned int  read_val;
    UCHAR         adv_hndl;
    UCHAR         enable;
    API_RESULT    retval;

    APPL_TRC("Enter Enable : \n");
    scanf("%x", &read_val);
    enable = (UCHAR)read_val;

    APPL_TRC("Enter Advertising_Handle: \n");
    scanf("%x", &read_val);
    adv_hndl = (UCHAR)read_val;

    retval = BT_hci_le_set_periodic_advertising_enable
             (
                 enable,
                 adv_hndl
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_periodic_advertising_create_sync_cancel(void)
{
    APPL_TRC("\nSending Periodic Advertising Receive Cancel Command\n");
    (BT_IGNORE_RETURN_VALUE) BT_hci_le_periodic_advertising_create_sync_cancel();

    return;
}

void appl_hci_le_periodic_adv_terminate_sync(void)
{
    unsigned int  read_val;
    UINT16        sync_hndl;
    API_RESULT    retval;

    APPL_TRC("Enter Sync_Handle : \n");
    scanf("%x", &read_val);
    sync_hndl = (UINT16)read_val;

    retval = BT_hci_le_periodic_adv_terminate_sync
    (
        sync_hndl
    );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_extended_create_connection(void)
{
    unsigned int  read_val;
    UINT32        i;

    UCHAR   init_filr_policy;
    UCHAR   own_addr_type;
    UCHAR   peer_addr_type;
    UCHAR   peer_addr[BT_BD_ADDR_SIZE];
    UCHAR   init_phy;

    UINT16  scan_intval[APPL_MAX_NUM_OF_INIT_PHYS];
    UINT16  scan_window[APPL_MAX_NUM_OF_INIT_PHYS];
    UINT16  conn_interval_min[APPL_MAX_NUM_OF_INIT_PHYS];
    UINT16  conn_interval_max[APPL_MAX_NUM_OF_INIT_PHYS];
    UINT16  conn_latency[APPL_MAX_NUM_OF_INIT_PHYS];
    UINT16  supn_timeout[APPL_MAX_NUM_OF_INIT_PHYS];
    UINT16  min_ce_len[APPL_MAX_NUM_OF_INIT_PHYS];
    UINT16  max_ce_len[APPL_MAX_NUM_OF_INIT_PHYS];
    API_RESULT retval;

    APPL_TRC("Enter initiator_filter_policy: \n");
    scanf("%x", &read_val);
    init_filr_policy = (UCHAR)read_val;

    APPL_TRC("Enter own_address_type: \n");
    scanf("%x", &read_val);
    own_addr_type = (UCHAR)read_val;

    APPL_TRC("Enter peer address type: \n");
    scanf("%x", &read_val);
    peer_addr_type = (UCHAR)read_val;

    APPL_TRC("Enter peer_address: \n");
    appl_get_bd_addr(peer_addr);

    /**
    * Initiating Phy values are
    * 0x01: controller needs to scan the connectable extn adv packets coming
    * on primary channel using 1M phy and use 1M connection parameter for
    * connection
    *
    * 0x03: controller needs to scan the connectable extn adv packets coming
    * on primary channel using only 1M phy and use either 2M or 1M Phy
    * connection parameters for connection
    *
    * 0x04: controller needs to scan the connectable extn adv packets coming
    * on primary channel using LE coded phy and use LE coded connection parameters
    * connection
    *
    * 0x05: controller needs to scan the connectable extn adv packets coming
    * on primary channel using either 1M phy or LE coded phy and use either 1M or
    * LE coded connection parameters for connection
    *
    * 0x06: controller needs to scan the connectable extn adv packets coming
    * on primary channel using only LE coded phy and use either 2M or LE coded
    * connection parameters for connection
    *
    * 0x07: controller needs to scan the connectable extn adv packets coming
    * on primary channel using either 1M phy or LE coded phy's and use either 1M
    * or 2M Phy or LE coded connection parameters for connection
    *
    * Did not added '0x02 for 2M PHY' option for Initiating
    * phy parameter because 0x02 value for initiating phy parameter in
    * HCI_le_extended_create_connection command indicates to the controller
    * that, host is provided only the connection parameters for 2M PHY
    * controller will not scan for any adv packets for hci connection
    */

    APPL_TRC("Enter Initiating PHY's : \n");
    APPL_TRC("0x01 for LE 1M PHY\n");
    APPL_TRC("0x03 for both 2M and 1M PHY\n");
    APPL_TRC("0x04 for LE Coded PHY\n");
    APPL_TRC("0x05 for both 1M and LE Coded PHY\n");
    APPL_TRC("0x06 for both 2M and LE Coded PHY\n");
    APPL_TRC("0x07 for 1M and 2M and LE Coded PHY\n");
    scanf("%x", &read_val);
    init_phy = (UCHAR)read_val;

    i = 0U;
    if (0U != (HCI_LE_SET_EXT_SCAN_PARAM_1M_PHY_MASK & init_phy))
    {
        APPL_TRC("For LE 1M PHY: \n");
        APPL_TRC("Enter scan_interval\n");
        scanf("%x", &read_val);
        scan_intval[i] = (UINT16)read_val;

        APPL_TRC("Enter scan_window\n");
        scanf("%x", &read_val);
        scan_window[i] = (UINT16)read_val;

        APPL_TRC("Enter conn_interval_min: \n");
        scanf("%x", &read_val);
        conn_interval_min[i] = (UINT16)read_val;

        APPL_TRC("Enter conn_interval_max: \n");
        scanf("%x", &read_val);
        conn_interval_max[i] = (UINT16)read_val;

        APPL_TRC("Enter conn_latency: \n");
        scanf("%x", &read_val);
        conn_latency[i] = (UINT16)read_val;

        APPL_TRC("Enter supn_timeout: \n");
        scanf("%x", &read_val);
        supn_timeout[i] = (UINT16)read_val;

        APPL_TRC("Enter min_ce_len: \n");
        scanf("%x", &read_val);
        min_ce_len[i] = (UINT16)read_val;

        APPL_TRC("Enter max_ce_len: \n");
        scanf("%x", &read_val);
        max_ce_len[i] = (UINT16)read_val;

        i += 1U;
    }

    if (0U != (HCI_LE_SET_EXT_SCAN_PARAM_2M_PHY_MASK & init_phy))
    {
        APPL_TRC("For LE 2M PHY: \n");
        APPL_TRC("Enter scan_interval\n");
        scanf("%x", &read_val);
        scan_intval[i] = (UINT16)read_val;

        APPL_TRC("Enter scan_window\n");
        scanf("%x", &read_val);
        scan_window[i] = (UINT16)read_val;

        APPL_TRC("Enter conn_interval_min: \n");
        scanf("%x", &read_val);
        conn_interval_min[i] = (UINT16)read_val;

        APPL_TRC("Enter conn_interval_max: \n");
        scanf("%x", &read_val);
        conn_interval_max[i] = (UINT16)read_val;

        APPL_TRC("Enter conn_latency: \n");
        scanf("%x", &read_val);
        conn_latency[i] = (UINT16)read_val;

        APPL_TRC("Enter supn_timeout: \n");
        scanf("%x", &read_val);
        supn_timeout[i] = (UINT16)read_val;

        APPL_TRC("Enter min_ce_len: \n");
        scanf("%x", &read_val);
        min_ce_len[i] = (UINT16)read_val;

        APPL_TRC("Enter max_ce_len: \n");
        scanf("%x", &read_val);
        max_ce_len[i] = (UINT16)read_val;

        i += 1U;
    }

    if (0U != (HCI_LE_SET_EXT_SCAN_PARAM_CODED_PHY_MASK & init_phy))
    {
        APPL_TRC("For LE Coded PHY: \n");
        APPL_TRC("Enter scan_interval\n");
        scanf("%x", &read_val);
        scan_intval[i] = (UINT16)read_val;

        APPL_TRC("Enter scan_window\n");
        scanf("%x", &read_val);
        scan_window[i] = (UINT16)read_val;

        APPL_TRC("Enter conn_interval_min: \n");
        scanf("%x", &read_val);
        conn_interval_min[i] = (UINT16)read_val;

        APPL_TRC("Enter conn_interval_max: \n");
        scanf("%x", &read_val);
        conn_interval_max[i] = (UINT16)read_val;

        APPL_TRC("Enter conn_latency: \n");
        scanf("%x", &read_val);
        conn_latency[i] = (UINT16)read_val;

        APPL_TRC("Enter supn_timeout: \n");
        scanf("%x", &read_val);
        supn_timeout[i] = (UINT16)read_val;

        APPL_TRC("Enter min_ce_len: \n");
        scanf("%x", &read_val);
        min_ce_len[i] = (UINT16)read_val;

        APPL_TRC("Enter max_ce_len: \n");
        scanf("%x", &read_val);
        max_ce_len[i] = (UINT16)read_val;
    }

    retval = BT_hci_le_extended_create_connection
             (
                 init_filr_policy,
                 own_addr_type,
                 peer_addr_type,
                 peer_addr,
                 init_phy,
                 scan_intval,
                 scan_window,
                 conn_interval_min,
                 conn_interval_max,
                 conn_latency,
                 supn_timeout,
                 min_ce_len,
                 max_ce_len
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_set_privacy_mode(void)
{
    unsigned int read_val;
    UCHAR        peer_identity_addr_type;
    UCHAR        peer_identity_addr[BT_BD_ADDR_SIZE];
    UCHAR        privacy_mode;
    API_RESULT   retval;

    APPL_TRC("Enter peer_identity_address_type : \n");
    scanf("%x", &read_val);
    peer_identity_addr_type = (UCHAR)read_val;

    APPL_TRC("Enter peer_identity_address : \n");
    appl_get_bd_addr(peer_identity_addr);

    APPL_TRC("Enter privacy_mode : \n");
    scanf("%x", &read_val);
    privacy_mode = (UCHAR)read_val;

    retval = BT_hci_le_set_privacy_mode
             (
                 peer_identity_addr_type,
                 peer_identity_addr,
                 privacy_mode
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}
#endif /* BT_5_0 */

#ifdef BT_5_1
void appl_hci_le_receiver_test_v3(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UCHAR        rx_channel;
    UCHAR        phy;
    UCHAR        modulation_index;
    UCHAR        expected_cte_length;
    UCHAR        extension_cte_type;
    UCHAR        slot_duration;
    UCHAR        length_of_switching_pattern;
    UCHAR *      antenna_ids;
    UINT32       index;

    APPL_TRC("Enter rx_channel :\n");
    scanf("%x", &read_val);
    rx_channel = (UCHAR)read_val;

    APPL_TRC("Enter phy :\n");
    scanf("%x", &read_val);
    phy = (UCHAR)read_val;

    APPL_TRC("Enter modulation_index :\n");
    scanf("%x", &read_val);
    modulation_index = (UCHAR)read_val;

    APPL_TRC("Enter expected_cte_length :\n");
    scanf("%x", &read_val);
    expected_cte_length = (UCHAR)read_val;

    APPL_TRC("Enter extension_cte_type :\n");
    scanf("%x", &read_val);
    extension_cte_type = (UCHAR)read_val;

    APPL_TRC("Enter slot_duration :\n");
    scanf("%x", &read_val);
    slot_duration = (UCHAR)read_val;

    APPL_TRC("Enter length_of_switching_pattern :\n");
    scanf("%x", &read_val);
    length_of_switching_pattern = (UCHAR)read_val;

    /* Allocate memory for antenna_ids */
    antenna_ids = (UCHAR *)BT_alloc_mem(sizeof(UCHAR) * length_of_switching_pattern);
    if (NULL == antenna_ids)
    {
        APPL_TRC("Memory allocation for antenna_ids Failed. Returning\n");

        /* return; */
    }
    else
    {
        APPL_TRC("Enter antenna_ids :\n");
        for(index = 0U; index < length_of_switching_pattern; index++)
        {
            scanf("%x", &read_val);
            antenna_ids[index] = (UCHAR)read_val;
        }

        retval = BT_hci_le_receiver_test_v3
                 (
                     rx_channel,
                     phy,
                     modulation_index,
                     expected_cte_length,
                     extension_cte_type,
                     slot_duration,
                     length_of_switching_pattern,
                     antenna_ids
                 );

        if (API_SUCCESS != retval)
        {
            APPL_TRC("FAILED !!! Error code = %04X\n", retval);
        }
        else
        {
            APPL_TRC("API returned success...\n");
        }

        BT_free_mem(antenna_ids);
    }

    return;
}

void appl_hci_le_transmitter_test_v3(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UCHAR        tx_channel;
    UCHAR        length_of_test_data;
    UCHAR        packet_payload;
    UCHAR        phy;
    UCHAR        cte_length;
    UCHAR        cte_type;
    UCHAR        length_of_switching_pattern;
    UCHAR *      antenna_ids;
    UINT32       index;

    APPL_TRC("Enter tx_channel :\n");
    scanf("%x", &read_val);
    tx_channel = (UCHAR)read_val;

    APPL_TRC("Enter length_of_test_data :\n");
    scanf("%x", &read_val);
    length_of_test_data = (UCHAR)read_val;

    APPL_TRC("Enter packet_payload :\n");
    scanf("%x", &read_val);
    packet_payload = (UCHAR)read_val;

    APPL_TRC("Enter phy :\n");
    scanf("%x", &read_val);
    phy = (UCHAR)read_val;

    APPL_TRC("Enter cte_length :\n");
    scanf("%x", &read_val);
    cte_length = (UCHAR)read_val;

    APPL_TRC("Enter cte_type :\n");
    scanf("%x", &read_val);
    cte_type = (UCHAR)read_val;

    APPL_TRC("Enter length_of_switching_pattern :\n");
    scanf("%x", &read_val);
    length_of_switching_pattern = (UCHAR)read_val;

    /* Allocate memory for antenna_ids */
    antenna_ids = (UCHAR *)BT_alloc_mem(sizeof(UCHAR) * length_of_switching_pattern);
    if (NULL == antenna_ids)
    {
        APPL_TRC("Memory allocation for antenna_ids Failed. Returning\n");

        /* return; */
    }
    else
    {
        APPL_TRC("Enter antenna_ids :\n");
        for(index = 0U; index < length_of_switching_pattern; index++)
        {
            scanf("%x", &read_val);
            antenna_ids[index] = (UCHAR)read_val;
        }

        retval = BT_hci_le_transmitter_test_v3
                 (
                     tx_channel,
                     length_of_test_data,
                     packet_payload,
                     phy,
                     cte_length,
                     cte_type,
                     length_of_switching_pattern,
                     antenna_ids
                 );

        if (API_SUCCESS != retval)
        {
            APPL_TRC("FAILED !!! Error code = %04X\n", retval);
        }
        else
        {
            APPL_TRC("API returned success...\n");
        }

        BT_free_mem(antenna_ids);
    }

    return;
}

void appl_hci_le_set_connectionless_cte_transmit_parameters(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UCHAR        advertising_handle;
    UCHAR        cte_length;
    UCHAR        cte_type;
    UCHAR        cte_count;
    UCHAR        length_of_switching_pattern;
    UCHAR *      antenna_ids;
    UINT32       index;

    APPL_TRC("Enter advertising_handle :\n");
    scanf("%x", &read_val);
    advertising_handle = (UCHAR)read_val;

    APPL_TRC("Enter cte_length :\n");
    scanf("%x", &read_val);
    cte_length = (UCHAR)read_val;

    APPL_TRC("Enter cte_type :\n");
    scanf("%x", &read_val);
    cte_type = (UCHAR)read_val;

    APPL_TRC("Enter cte_count :\n");
    scanf("%x", &read_val);
    cte_count = (UCHAR)read_val;

    APPL_TRC("Enter length_of_switching_pattern :\n");
    scanf("%x", &read_val);
    length_of_switching_pattern = (UCHAR)read_val;

    /* Allocate memory for antenna_ids */
    antenna_ids = (UCHAR *)BT_alloc_mem(sizeof(UCHAR) * length_of_switching_pattern);
    if (NULL == antenna_ids)
    {
        APPL_TRC("Memory allocation for antenna_ids Failed. Returning\n");

        /* return; */
    }
    else
    {
        APPL_TRC("Enter antenna_ids :\n");
        for(index = 0U; index < length_of_switching_pattern; index++)
        {
            scanf("%x", &read_val);
            antenna_ids[index] = (UCHAR)read_val;
        }

        retval = BT_hci_le_set_connectionless_cte_transmit_parameters
                 (
                     advertising_handle,
                     cte_length,
                     cte_type,
                     cte_count,
                     length_of_switching_pattern,
                     antenna_ids
                 );

        if (API_SUCCESS != retval)
        {
            APPL_TRC("FAILED !!! Error code = %04X\n", retval);
        }
        else
        {
            APPL_TRC("API returned success...\n");
        }

        BT_free_mem(antenna_ids);
    }

    return;
}

void appl_hci_le_set_connectionless_cte_transmit_enable(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UCHAR        advertising_handle;
    UCHAR        cte_enable;

    APPL_TRC("Enter advertising_handle :\n");
    scanf("%x", &read_val);
    advertising_handle = (UCHAR)read_val;

    APPL_TRC("Enter cte_enable :\n");
    scanf("%x", &read_val);
    cte_enable = (UCHAR)read_val;

    retval = BT_hci_le_set_connectionless_cte_transmit_enable
             (
                 advertising_handle,
                 cte_enable
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_set_connectionless_iq_sampling_enable(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UINT16       sync_handle;
    UCHAR        sampling_enable;
    UCHAR        slot_duration;
    UCHAR        max_sampled_ctes;
    UCHAR        length_of_switching_pattern;
    UCHAR *      antenna_ids;
    UINT32       index;

    APPL_TRC("Enter sync_handle :\n");
    scanf("%x", &read_val);
    sync_handle = (UINT16)read_val;

    APPL_TRC("Enter sampling_enable :\n");
    scanf("%x", &read_val);
    sampling_enable = (UCHAR)read_val;

    APPL_TRC("Enter slot_duration :\n");
    scanf("%x", &read_val);
    slot_duration = (UCHAR)read_val;

    APPL_TRC("Enter max_sampled_ctes :\n");
    scanf("%x", &read_val);
    max_sampled_ctes = (UCHAR)read_val;

    APPL_TRC("Enter length_of_switching_pattern :\n");
    scanf("%x", &read_val);
    length_of_switching_pattern = (UCHAR)read_val;

    /* Allocate memory for antenna_ids */
    antenna_ids = (UCHAR *)BT_alloc_mem(sizeof(UCHAR) * length_of_switching_pattern);
    if (NULL == antenna_ids)
    {
        APPL_TRC("Memory allocation for antenna_ids Failed. Returning\n");

        /* return; */
    }
    else
    {
        APPL_TRC("Enter antenna_ids :\n");
        for(index = 0U; index < length_of_switching_pattern; index++)
        {
            scanf("%x", &read_val);
            antenna_ids[index] = (UCHAR)read_val;
        }

        retval = BT_hci_le_set_connectionless_iq_sampling_enable
                 (
                     sync_handle,
                     sampling_enable,
                     slot_duration,
                     max_sampled_ctes,
                     length_of_switching_pattern,
                     antenna_ids
                 );

        if (API_SUCCESS != retval)
        {
            APPL_TRC("FAILED !!! Error code = %04X\n", retval);
        }
        else
        {
            APPL_TRC("API returned success...\n");
        }

        BT_free_mem(antenna_ids);
    }

    return;
}

void appl_hci_le_set_connection_cte_receive_parameters(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UINT16       connection_handle;
    UCHAR        sampling_enable;
    UCHAR        slot_duration;
    UCHAR        length_of_switching_pattern;
    UCHAR *      antenna_ids;
    UINT32       index;

    APPL_TRC("Enter connection_handle :\n");
    scanf("%x", &read_val);
    connection_handle = (UINT16)read_val;

    APPL_TRC("Enter sampling_enable :\n");
    scanf("%x", &read_val);
    sampling_enable = (UCHAR)read_val;

    APPL_TRC("Enter slot_duration :\n");
    scanf("%x", &read_val);
    slot_duration = (UCHAR)read_val;

    APPL_TRC("Enter length_of_switching_pattern :\n");
    scanf("%x", &read_val);
    length_of_switching_pattern = (UCHAR)read_val;

    /* Allocate memory for antenna_ids */
    antenna_ids = (UCHAR *)BT_alloc_mem(sizeof(UCHAR) * length_of_switching_pattern);
    if (NULL == antenna_ids)
    {
        APPL_TRC("Memory allocation for antenna_ids Failed. Returning\n");

        /* return; */
    }
    else
    {
        APPL_TRC("Enter antenna_ids :\n");
        for(index = 0U; index < length_of_switching_pattern; index++)
        {
            scanf("%x", &read_val);
            antenna_ids[index] = (UCHAR)read_val;
        }

        retval = BT_hci_le_set_connection_cte_receive_parameters
                 (
                     connection_handle,
                     sampling_enable,
                     slot_duration,
                     length_of_switching_pattern,
                     antenna_ids
                 );

        if (API_SUCCESS != retval)
        {
            APPL_TRC("FAILED !!! Error code = %04X\n", retval);
        }
        else
        {
            APPL_TRC("API returned success...\n");
        }

        BT_free_mem(antenna_ids);
    }

    return;
}

void appl_hci_le_set_connection_cte_transmit_parameters(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UINT16       connection_handle;
    UCHAR        cte_types;
    UCHAR        length_of_switching_pattern;
    UCHAR *      antenna_ids;
    UINT32       index;

    APPL_TRC("Enter connection_handle :\n");
    scanf("%x", &read_val);
    connection_handle = (UINT16)read_val;

    APPL_TRC("Enter cte_types :\n");
    scanf("%x", &read_val);
    cte_types = (UCHAR)read_val;

    APPL_TRC("Enter length_of_switching_pattern :\n");
    scanf("%x", &read_val);
    length_of_switching_pattern = (UCHAR)read_val;

    /* Allocate memory for antenna_ids */
    antenna_ids = (UCHAR *)BT_alloc_mem(sizeof(UCHAR) * length_of_switching_pattern);
    if (NULL == antenna_ids)
    {
        APPL_TRC("Memory allocation for antenna_ids Failed. Returning\n");

        /* return; */
    }
    else
    {
        APPL_TRC("Enter antenna_ids :\n");
        for(index = 0U; index < length_of_switching_pattern; index++)
        {
            scanf("%x", &read_val);
            antenna_ids[index] = (UCHAR)read_val;
        }

        retval = BT_hci_le_set_connection_cte_transmit_parameters
                 (
                     connection_handle,
                     cte_types,
                     length_of_switching_pattern,
                     antenna_ids
                 );

        if (API_SUCCESS != retval)
        {
            APPL_TRC("FAILED !!! Error code = %04X\n", retval);
        }
        else
        {
            APPL_TRC("API returned success...\n");
        }

        BT_free_mem(antenna_ids);
    }

    return;
}

void appl_hci_le_set_connection_cte_request_enable(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UINT16       connection_handle;
    UCHAR        enable;
    UINT16       cte_request_interval;
    UCHAR        requested_cte_length;
    UCHAR        requested_cte_type;

    APPL_TRC("Enter connection_handle :\n");
    scanf("%x", &read_val);
    connection_handle = (UINT16)read_val;

    APPL_TRC("Enter enable :\n");
    scanf("%x", &read_val);
    enable = (UCHAR)read_val;

    APPL_TRC("Enter cte_request_interval :\n");
    scanf("%x", &read_val);
    cte_request_interval = (UINT16)read_val;

    APPL_TRC("Enter requested_cte_length :\n");
    scanf("%x", &read_val);
    requested_cte_length = (UCHAR)read_val;

    APPL_TRC("Enter requested_cte_type :\n");
    scanf("%x", &read_val);
    requested_cte_type = (UCHAR)read_val;

    retval = BT_hci_le_set_connection_cte_request_enable
             (
                 connection_handle,
                 enable,
                 cte_request_interval,
                 requested_cte_length,
                 requested_cte_type
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_set_connection_cte_response_enable(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UINT16       connection_handle;
    UCHAR        enable;

    APPL_TRC("Enter connection_handle :\n");
    scanf("%x", &read_val);
    connection_handle = (UINT16)read_val;

    APPL_TRC("Enter enable :\n");
    scanf("%x", &read_val);
    enable = (UCHAR)read_val;

    retval = BT_hci_le_set_connection_cte_response_enable
             (
                 connection_handle,
                 enable
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_read_antenna_information(void)
{
    API_RESULT retval;

    retval = BT_hci_le_read_antenna_information();

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_set_periodic_advertising_receive_enable(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UINT16       sync_handle;
    UCHAR        enable;

    APPL_TRC("Enter sync_handle :\n");
    scanf("%x", &read_val);
    sync_handle = (UINT16)read_val;

    APPL_TRC("Enter enable :\n");
    scanf("%x", &read_val);
    enable = (UCHAR)read_val;

    retval = BT_hci_le_set_periodic_advertising_receive_enable
             (
                 sync_handle,
                 enable
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_periodic_advertising_sync_transfer(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UINT16       connection_handle;
    UINT16       service_data;
    UINT16       sync_handle;

    APPL_TRC("Enter connection_handle :\n");
    scanf("%x", &read_val);
    connection_handle = (UINT16)read_val;

    APPL_TRC("Enter service_data :\n");
    scanf("%x", &read_val);
    service_data = (UINT16)read_val;

    APPL_TRC("Enter sync_handle :\n");
    scanf("%x", &read_val);
    sync_handle = (UINT16)read_val;

    retval = BT_hci_le_periodic_advertising_sync_transfer
             (
                 connection_handle,
                 service_data,
                 sync_handle
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_periodic_advertising_set_info_transfer(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UINT16       connection_handle;
    UINT16       service_data;
    UCHAR        advertising_handle;

    APPL_TRC("Enter connection_handle :\n");
    scanf("%x", &read_val);
    connection_handle = (UINT16)read_val;

    APPL_TRC("Enter service_data :\n");
    scanf("%x", &read_val);
    service_data = (UINT16)read_val;

    APPL_TRC("Enter advertising_handle :\n");
    scanf("%x", &read_val);
    advertising_handle = (UCHAR)read_val;

    retval = BT_hci_le_periodic_advertising_set_info_transfer
             (
                 connection_handle,
                 service_data,
                 advertising_handle
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_set_periodic_advertising_sync_transfer_parameters(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UINT16       connection_handle;
    UCHAR        mode;
    UINT16       skip;
    UINT16       sync_timeout;
    UCHAR        cte_type;

    APPL_TRC("Enter connection_handle :\n");
    scanf("%x", &read_val);
    connection_handle = (UINT16)read_val;

    APPL_TRC("Enter mode :\n");
    scanf("%x", &read_val);
    mode = (UCHAR)read_val;

    APPL_TRC("Enter skip :\n");
    scanf("%x", &read_val);
    skip = (UINT16)read_val;

    APPL_TRC("Enter sync_timeout :\n");
    scanf("%x", &read_val);
    sync_timeout = (UINT16)read_val;

    APPL_TRC("Enter cte_type :\n");
    scanf("%x", &read_val);
    cte_type = (UCHAR)read_val;

    retval = BT_hci_le_set_periodic_advertising_sync_transfer_parameters
             (
                 connection_handle,
                 mode,
                 skip,
                 sync_timeout,
                 cte_type
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_set_default_periodic_advertising_sync_transfer_parameters(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UCHAR        mode;
    UINT16       skip;
    UINT16       sync_timeout;
    UCHAR        cte_type;

    APPL_TRC("Enter mode :\n");
    scanf("%x", &read_val);
    mode = (UCHAR)read_val;

    APPL_TRC("Enter skip :\n");
    scanf("%x", &read_val);
    skip = (UINT16)read_val;

    APPL_TRC("Enter sync_timeout :\n");
    scanf("%x", &read_val);
    sync_timeout = (UINT16)read_val;

    APPL_TRC("Enter cte_type :\n");
    scanf("%x", &read_val);
    cte_type = (UCHAR)read_val;

    retval = BT_hci_le_set_default_periodic_advertising_sync_transfer_parameters
             (
                 mode,
                 skip,
                 sync_timeout,
                 cte_type
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

void appl_hci_le_generate_dhkey_v2(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UCHAR *      remote_p_256_public_key;
    UCHAR        key_type;
    UINT32       index;

    APPL_TRC("Enter remote_p_256_public_key :\n");
    /* Allocate memory for remote_p_256_public_key */
    remote_p_256_public_key = (UCHAR *)BT_alloc_mem(64U);
    if (NULL == remote_p_256_public_key)
    {
        APPL_TRC("Memory allocation for remote_p_256_public_key Failed. Returning\n");

        /* return; */
    }
    else
    {
        for(index = 0U; index < 64U; index++)
        {
            scanf("%x", &read_val);
            remote_p_256_public_key[index] = (UCHAR)read_val;
        }

        APPL_TRC("Enter key_type :\n");
        scanf("%x", &read_val);
        key_type = (UCHAR)read_val;

        retval = BT_hci_le_generate_dhkey_v2
                 (
                     remote_p_256_public_key,
                     key_type
                 );

        if (API_SUCCESS != retval)
        {
            APPL_TRC("FAILED !!! Error code = %04X\n", retval);
        }
        else
        {
            APPL_TRC("API returned success...\n");
        }

        BT_free_mem(remote_p_256_public_key);
    }

    return;
}

void appl_hci_le_modify_sleep_clock_accuracy(void)
{
    unsigned int read_val;
    API_RESULT   retval;
    UCHAR        action;

    APPL_TRC("Enter action :\n");
    scanf("%x", &read_val);
    action = (UCHAR)read_val;

    retval = BT_hci_le_modify_sleep_clock_accuracy
             (
                 action
             );

    if (API_SUCCESS != retval)
    {
        APPL_TRC("FAILED !!! Error code = %04X\n", retval);
    }
    else
    {
        APPL_TRC("API returned success...\n");
    }

    return;
}

#endif /* BT_5_1 */

#endif /* BT_LE */
