/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/

#include <time.h>
#include <stdlib.h>
#include "fsl_common.h"
#include "mflash_drv.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "mcuboot_app_support.h"
#include "sample_config.h"

#include "nx_api.h"
#ifndef SAMPLE_DHCP_DISABLE
#include "nxd_dhcp_client.h"
#endif /* SAMPLE_DHCP_DISABLE */

#include "nxd_dns.h"
#include "nxd_sntp_client.h"
#include "nx_secure_tls_api.h"


#include "fsl_iomuxc.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Define the helper thread for running Azure SDK on ThreadX (THREADX IoT Platform).  */
#ifndef SAMPLE_HELPER_STACK_SIZE
#define SAMPLE_HELPER_STACK_SIZE        (4096)
#endif /* SAMPLE_HELPER_STACK_SIZE  */

#ifndef SAMPLE_HELPER_THREAD_PRIORITY
#define SAMPLE_HELPER_THREAD_PRIORITY   (4)
#endif /* SAMPLE_HELPER_THREAD_PRIORITY  */

/* Define user configurable symbols. */
#ifndef SAMPLE_IP_STACK_SIZE
#define SAMPLE_IP_STACK_SIZE            (2048)
#endif /* SAMPLE_IP_STACK_SIZE  */

#ifndef SAMPLE_PACKET_COUNT
#define SAMPLE_PACKET_COUNT             (32)
#endif /* SAMPLE_PACKET_COUNT  */

#ifndef SAMPLE_PACKET_SIZE
#define SAMPLE_PACKET_SIZE              (1536)
#endif /* SAMPLE_PACKET_SIZE  */

#define SAMPLE_POOL_SIZE                ((SAMPLE_PACKET_SIZE + sizeof(NX_PACKET)) * SAMPLE_PACKET_COUNT)

#ifndef SAMPLE_ARP_CACHE_SIZE
#define SAMPLE_ARP_CACHE_SIZE           (512)
#endif /* SAMPLE_ARP_CACHE_SIZE  */

#ifndef SAMPLE_IP_THREAD_PRIORITY
#define SAMPLE_IP_THREAD_PRIORITY       (1)
#endif /* SAMPLE_IP_THREAD_PRIORITY */

#ifdef SAMPLE_DHCP_DISABLE
#ifndef SAMPLE_IPV4_ADDRESS
/*#define SAMPLE_IPV4_ADDRESS           IP_ADDRESS(192, 168, 100, 33)*/
#error "SYMBOL SAMPLE_IPV4_ADDRESS must be defined. This symbol specifies the IP address of device. "
#endif /* SAMPLE_IPV4_ADDRESS */

#ifndef SAMPLE_IPV4_MASK
/*#define SAMPLE_IPV4_MASK              0xFFFFFF00UL*/
#error "SYMBOL SAMPLE_IPV4_MASK must be defined. This symbol specifies the IP address mask of device. "
#endif /* SAMPLE_IPV4_MASK */

#ifndef SAMPLE_GATEWAY_ADDRESS
/*#define SAMPLE_GATEWAY_ADDRESS        IP_ADDRESS(192, 168, 100, 1)*/
#error "SYMBOL SAMPLE_GATEWAY_ADDRESS must be defined. This symbol specifies the gateway address for routing. "
#endif /* SAMPLE_GATEWAY_ADDRESS */

#ifndef SAMPLE_DNS_SERVER_ADDRESS
/*#define SAMPLE_DNS_SERVER_ADDRESS     IP_ADDRESS(192, 168, 100, 1)*/
#error "SYMBOL SAMPLE_DNS_SERVER_ADDRESS must be defined. This symbol specifies the dns server address for routing. "
#endif /* SAMPLE_DNS_SERVER_ADDRESS */
#else
#define SAMPLE_IPV4_ADDRESS             IP_ADDRESS(0, 0, 0, 0)
#define SAMPLE_IPV4_MASK                IP_ADDRESS(0, 0, 0, 0)
#endif /* SAMPLE_DHCP_DISABLE */


/* Using SNTP to get unix time.  */
/* Define the address of SNTP Server. If not defined, use DNS module to
 * resolve the host name SAMPLE_SNTP_SERVER_NAME.
 */
/*
#define SAMPLE_SNTP_SERVER_ADDRESS      IP_ADDRESS(118, 190, 21, 209)
*/

#ifndef SAMPLE_SNTP_SYNC_MAX
#define SAMPLE_SNTP_SYNC_MAX            1
#endif /* SAMPLE_SNTP_SYNC_MAX */

#ifndef SAMPLE_SNTP_UPDATE_MAX
#define SAMPLE_SNTP_UPDATE_MAX          2
#endif /* SAMPLE_SNTP_UPDATE_MAX */

#ifndef SAMPLE_SNTP_UPDATE_INTERVAL
#define SAMPLE_SNTP_UPDATE_INTERVAL     (NX_IP_PERIODIC_RATE / 2)
#endif /* SAMPLE_SNTP_UPDATE_INTERVAL */

/* Default time. */

#ifndef SAMPLE_SYSTEM_TIME
#define SAMPLE_SYSTEM_TIME              1647518618
#endif /* SAMPLE_SYSTEM_TIME  */

/* Seconds between Unix Epoch (1/1/1970) and NTP Epoch (1/1/1999) */
#define SAMPLE_UNIX_TO_NTP_EPOCH_SECOND 0x83AA7E80

#define KEY_FILE_NAME       "conn_string.txt"

#define CONN_STR_HOSTNAME   "HostName"
#define CONN_STR_DEVICEID   "DeviceId"
#define CONN_STR_ACCESS_KEY "SharedAccessKey"

/*******************************************************************************
 * Variables
 ******************************************************************************/

char host_name[80];
char device_id[80];
char device_symmetric_key[256];

static TX_THREAD        sample_helper_thread;
static NX_PACKET_POOL   pool_0;
static NX_IP            ip_0;
static NX_DNS           dns_0;
#ifndef SAMPLE_DHCP_DISABLE
AT_NONCACHEABLE_SECTION_ALIGN(NX_DHCP dhcp_0, 64);
#endif /* SAMPLE_DHCP_DISABLE  */
static NX_SNTP_CLIENT   sntp_client;

/* System clock time for UTC.  */
static ULONG            unix_time_base;

/* Define the stack/cache for ThreadX.  */
static ULONG sample_ip_stack[SAMPLE_IP_STACK_SIZE / sizeof(ULONG)];
#ifndef SAMPLE_POOL_STACK_USER
AT_NONCACHEABLE_SECTION_ALIGN(ULONG sample_pool_stack[SAMPLE_POOL_SIZE / sizeof(ULONG)], 64);
static ULONG sample_pool_stack_size = sizeof(sample_pool_stack);
#else
extern ULONG sample_pool_stack[];
extern ULONG sample_pool_stack_size;
#endif
static ULONG sample_arp_cache_area[SAMPLE_ARP_CACHE_SIZE / sizeof(ULONG)];
static ULONG sample_helper_thread_stack[SAMPLE_HELPER_STACK_SIZE / sizeof(ULONG)];

static const CHAR *sntp_servers[] =
{
    "0.pool.ntp.org",
    "1.pool.ntp.org",
    "2.pool.ntp.org",
    "3.pool.ntp.org",
};
static UINT sntp_server_index;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/* Define the prototypes for sample thread.  */
static void sample_helper_thread_entry(ULONG parameter);

#ifndef SAMPLE_DHCP_DISABLE
static void dhcp_wait();
#endif /* SAMPLE_DHCP_DISABLE */

static UINT dns_create();
static UINT sntp_time_sync();
static UINT unix_time_get(ULONG *unix_time);


/* Include the platform IP driver. */
extern VOID nx_driver_imx(NX_IP_DRIVER *driver_req_ptr);

extern uint32_t get_seed(void);

extern VOID sample_entry(NX_IP* ip_ptr, NX_PACKET_POOL* pool_ptr,
                         NX_DNS* dns_ptr, UINT (*unix_time_callback)(ULONG *unix_time));

extern status_t secure_storage_init(char *filename);
extern status_t secure_save_file(char *filename, uint8_t *data, uint32_t data_len);
extern status_t secure_read_file(char *filename, uint8_t *data, uint32_t *data_len);

/*******************************************************************************
 * Code
 ******************************************************************************/
static void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 1000000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

/* return the ENET MDIO interface clock frequency */
uint32_t BOARD_GetMDIOClock(void)
{
    return CLOCK_GetFreq(kCLOCK_IpgClk);
}


static void update_swaptype(void)
{
    status_t status;

    status = bl_update_image_state(kSwapType_Permanent);
    if (status != kStatus_Success && status != kStatus_NoData)
    {
        PRINTF("Failed to mark the new image as permanent (ret=%d)\r\n", status);
        goto err;
    }

    return;

err:
    while (1)
    {
        tx_thread_sleep(TX_TIMER_TICKS_PER_SECOND);
    }
}

static status_t parse_str(char *string, char *key_name, char** data, uint32_t *size)
{
    char *ptr;

    ptr = strstr(string, key_name);
    if (ptr == NULL)
    {
        return kStatus_NoData;
    }

    ptr = strchr(ptr, (int)'=');
    if (ptr == NULL)
    {
        return kStatus_NoData;
    }

    *data = ptr + 1;

    ptr = strchr(ptr, (int)';');
    if (ptr == NULL)
    {
        return kStatus_NoData;
    }

    *size = ptr - *data;

    return kStatus_Success;
}

static void get_input_string(char *key_name, char *output)
{
    char buf[150];
    size_t size;

    PRINTF("Please input %s: ", key_name);
    SCANF("%s", buf);
    PRINTF("\r\n");
    size = strlen(buf);
    memcpy(output, buf, size);
    output[size] = 0;
}

static status_t get_new_device_string(void)
{
	status_t status;
	char buf[250];

	PRINTF("Please input a device connection string.\r\n");

	get_input_string(CONN_STR_HOSTNAME, host_name);
	get_input_string(CONN_STR_DEVICEID, device_id);
	get_input_string(CONN_STR_ACCESS_KEY, device_symmetric_key);

	sprintf(buf, "%s=%s;%s=%s;%s=%s;", CONN_STR_HOSTNAME, host_name,
			CONN_STR_DEVICEID, device_id, CONN_STR_ACCESS_KEY, device_symmetric_key);

	status = secure_save_file(KEY_FILE_NAME, (uint8_t *)buf, strlen(buf) + 1);
	if (status != kStatus_Success)
	{
		return status;
	}

	return kStatus_Success;
}

static status_t get_secure_conn_string(void)
{
    status_t status;
    char buf[250];
    char *str;
    uint32_t size;

    /* read the stored connection string from a file */
    status = secure_read_file(KEY_FILE_NAME, (uint8_t *)buf, &size);
    if (status != kStatus_Success)
    {
        PRINTF("Did not find any device connection string.\r\n");
        get_new_device_string();
        return kStatus_Success;
    }

    PRINTF("Get the device connection string from an encrypted file.\r\n");

    /* Parse the device connection string. */
    /* Format: HostName=<>;DeviceId=<>;SharedAccessKey=<>; */

    status = parse_str(buf, CONN_STR_HOSTNAME, &str, &size);
    if (status != kStatus_Success)
    {
        return kStatus_NoData;
    }
    memcpy(host_name, str, size);
    host_name[size] = 0;

    status = parse_str(buf, CONN_STR_DEVICEID, &str, &size);
    if (status != kStatus_Success)
    {
        return kStatus_NoData;
    }
    memcpy(device_id, str, size);
    device_id[size] = 0;

    status = parse_str(buf, CONN_STR_ACCESS_KEY, &str, &size);
    if (status != kStatus_Success)
    {
        return kStatus_NoData;
    }
    memcpy(device_symmetric_key, str, size);
    device_symmetric_key[size] = 0;

    PRINTF("%s: %s\r\n", CONN_STR_HOSTNAME, host_name);
    PRINTF("%s: %s\r\n", CONN_STR_DEVICEID, device_id);
    /* Print the key for debug */
    PRINTF("%s: %s\r\n", CONN_STR_ACCESS_KEY, device_symmetric_key);

    PRINTF("\r\nDo you want to update the device information? (Y/N) ");
    while (1)
    {
        int input = GETCHAR();

        PRINTF("\r\n\r\n");
        if (input == 'y' || input == 'Y')
        {
            get_new_device_string();
            break;
        }

        if (input == 'n' || input == 'N')
        {
            break;
        }

    }

    return kStatus_Success;
}

/* Define main entry point.  */
int main(void)
{
    status_t status;

    /* Setup the hardware. */
    gpio_pin_config_t gpio_config        = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};
    const clock_enet_pll_config_t config = {.enableClkOutput = true, .enableClkOutput25M = false, .loopDivider = 1};

    /* Enable cycle counter for tx_exection_profile.c use */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->LAR = 0xC5ACCE55;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    CLOCK_InitEnetPll(&config);
    delay();

    IOMUXC_EnableMode(IOMUXC_GPR, kIOMUXC_GPR_ENET1TxClkOutputDir, true);

    GPIO_PinInit(GPIO1, 9, &gpio_config);
    GPIO_PinInit(GPIO1, 10, &gpio_config);
    /* pull up the ENET_INT before RESET. */
    GPIO_WritePinOutput(GPIO1, 10, 1);
    GPIO_WritePinOutput(GPIO1, 9, 0);
    delay();
    GPIO_WritePinOutput(GPIO1, 9, 1);

    PRINTF("Start the azure_iot_embedded_sdk_adu example (v%s)\r\n", SAMPLE_UPDATE_ID_VERSION);

    status = secure_storage_init(KEY_FILE_NAME);
    if (status != kStatus_Success)
    {
        PRINTF("Failed to init secure storage\r\n");
        return -1;
    }

    /* This could be moved to other places where the new update is deemed valid. */
    update_swaptype();

    status = get_secure_conn_string();
    if (status != kStatus_Success)
    {
        PRINTF("Failed to retrive a device connection string\r\n");
        return -1;
    }

    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();

    return 0;
}

/* Define what the initial system looks like.  */
void tx_application_define(void *first_unused_memory)
{

    UINT  status;

    NX_PARAMETER_NOT_USED(first_unused_memory);

    /* Initialize the NetX system.  */
    nx_system_initialize();

    /* Create a packet pool.  */
    status = nx_packet_pool_create(&pool_0, "NetX Main Packet Pool", SAMPLE_PACKET_SIZE,
                                   (UCHAR *)sample_pool_stack , sample_pool_stack_size);

    /* Check for pool creation error.  */
    if (status)
    {
        PRINTF("ERR: nx_packet_pool_create() failed: %u\r\n", status);
        return;
    }

    /* Create an IP instance.  */
    status = nx_ip_create(&ip_0, "NetX IP Instance 0",
                          SAMPLE_IPV4_ADDRESS, SAMPLE_IPV4_MASK,
                          &pool_0, nx_driver_imx,
                          (UCHAR*)sample_ip_stack, sizeof(sample_ip_stack),
                          SAMPLE_IP_THREAD_PRIORITY);

    /* Check for IP create errors.  */
    if (status)
    {
        PRINTF("ERR: nx_ip_create() failed: %u\r\n", status);
        return;
    }

    /* Enable ARP and supply ARP cache memory for IP Instance 0.  */
    status = nx_arp_enable(&ip_0, (VOID *)sample_arp_cache_area, sizeof(sample_arp_cache_area));

    /* Check for ARP enable errors.  */
    if (status)
    {
        PRINTF("ERR: nx_arp_enable() failed: %u\r\n", status);
        return;
    }

#ifndef SAMPLE_ICMP_DISABLE
    /* Enable ICMP traffic.  */
    status = nx_icmp_enable(&ip_0);

    /* Check for ICMP enable errors.  */
    if (status)
    {
        PRINTF("ERR: nx_icmp_enable() failed: %u\r\n", status);
        return;
    }
#endif

    /* Enable TCP traffic.  */
    status = nx_tcp_enable(&ip_0);

    /* Check for TCP enable errors.  */
    if (status)
    {
        PRINTF("ERR: nx_tcp_enable() failed: %u\r\n", status);
        return;
    }

    /* Enable UDP traffic.  */
    status = nx_udp_enable(&ip_0);

    /* Check for UDP enable errors.  */
    if (status)
    {
        PRINTF("ERR: nx_udp_enable() failed: %u\r\n", status);
        return;
    }

    /* Initialize TLS.  */
    nx_secure_tls_initialize();

    /* Create sample helper thread. */
    status = tx_thread_create(&sample_helper_thread, "Demo Thread",
                              sample_helper_thread_entry, 0,
                              sample_helper_thread_stack, SAMPLE_HELPER_STACK_SIZE,
                              SAMPLE_HELPER_THREAD_PRIORITY, SAMPLE_HELPER_THREAD_PRIORITY,
                              TX_NO_TIME_SLICE, TX_AUTO_START);
    if (status)
    {
        PRINTF("ERR: The demo thread creation failed: %u\r\n", status);
        return;
    }
}

/* Define sample helper thread entry.  */
void sample_helper_thread_entry(ULONG parameter)
{
    UINT    status;
    ULONG   ip_address = 0;
    ULONG   network_mask = 0;
    ULONG   gateway_address = 0;

    NX_PARAMETER_NOT_USED(parameter);

#ifndef SAMPLE_DHCP_DISABLE
    dhcp_wait();
#else
    nx_ip_gateway_address_set(&ip_0, SAMPLE_GATEWAY_ADDRESS);
#endif /* SAMPLE_DHCP_DISABLE  */

    /* Get IP address and gateway address. */
    nx_ip_address_get(&ip_0, &ip_address, &network_mask);
    nx_ip_gateway_address_get(&ip_0, &gateway_address);

    /* Output IP address and gateway address. */
    PRINTF("IP address: %lu.%lu.%lu.%lu\r\n",
           (ip_address >> 24),
           (ip_address >> 16 & 0xFF),
           (ip_address >> 8 & 0xFF),
           (ip_address & 0xFF));
    PRINTF("Mask: %lu.%lu.%lu.%lu\r\n",
           (network_mask >> 24),
           (network_mask >> 16 & 0xFF),
           (network_mask >> 8 & 0xFF),
           (network_mask & 0xFF));
    PRINTF("Gateway: %lu.%lu.%lu.%lu\r\n",
           (gateway_address >> 24),
           (gateway_address >> 16 & 0xFF),
           (gateway_address >> 8 & 0xFF),
           (gateway_address & 0xFF));

    /* Create DNS. */
    status = dns_create();

    /* Check for DNS create errors.  */
    if (status)
    {
        PRINTF("ERR: dns_create() failed: %u\r\n", status);
        return;
    }

    /* Sync up time by SNTP at start up.  */
    for (UINT i = 0; i < SAMPLE_SNTP_SYNC_MAX; i++)
    {

        /* Start SNTP to sync the local time.  */
        status = sntp_time_sync();

        /* Check status.  */
        if(status == NX_SUCCESS)
            break;

        /* Switch SNTP server every time.  */
        sntp_server_index = (sntp_server_index + 1) %
                            (sizeof(sntp_servers) / sizeof(sntp_servers[0]));
    }

    /* Check status.  */
    if (status)
    {
        PRINTF("SNTP Time Sync failed.\r\n");
        PRINTF("Set Time to default value: SAMPLE_SYSTEM_TIME.\r\n");
        unix_time_base = SAMPLE_SYSTEM_TIME;
    }
    else
    {
        PRINTF("SNTP Time Sync successfully.\r\n");
    }

    /* Use real rand on device.  */
    srand(get_seed());

    /* Start sample.  */
    sample_entry(&ip_0, &pool_0, &dns_0, unix_time_get);
}

#ifndef SAMPLE_DHCP_DISABLE
static void dhcp_wait()
{
    ULONG actual_status;

    PRINTF("DHCP In Progress...\r\n");

    /* Create the DHCP instance.  */
    nx_dhcp_create(&dhcp_0, &ip_0, "DHCP Client");

    /* Start the DHCP Client.  */
    nx_dhcp_start(&dhcp_0);

    /* Wait util address is solved. */
    nx_ip_status_check(&ip_0, NX_IP_ADDRESS_RESOLVED, &actual_status, NX_WAIT_FOREVER);
}
#endif /* SAMPLE_DHCP_DISABLE  */

static UINT dns_create()
{

    UINT    status;
    ULONG   dns_server_address[3];
    UINT    dns_server_address_size = 12;

    /* Create a DNS instance for the Client.  Note this function will create
       the DNS Client packet pool for creating DNS message packets intended
       for querying its DNS server. */
    status = nx_dns_create(&dns_0, &ip_0, (UCHAR *)"DNS Client");
    if (status)
    {
        return status;
    }

#ifdef NX_DNS_CLIENT_USER_CREATE_PACKET_POOL

    status = nx_dns_packet_pool_set(&dns_0, ip_0.nx_ip_default_packet_pool);
    if (status)
    {
        nx_dns_delete(&dns_0);
        return status;
    }
#endif /* NX_DNS_CLIENT_USER_CREATE_PACKET_POOL */

#ifndef SAMPLE_DHCP_DISABLE
    /* Retrieve DNS server address.  */
    nx_dhcp_interface_user_option_retrieve(&dhcp_0, 0, NX_DHCP_OPTION_DNS_SVR,
                                           (UCHAR *)(dns_server_address),
                                           &dns_server_address_size);
#else
    dns_server_address[0] = SAMPLE_DNS_SERVER_ADDRESS;
#endif /* SAMPLE_DHCP_DISABLE */

    /* Add an IPv4 server address to the Client list. */
    status = nx_dns_server_add(&dns_0, dns_server_address[0]);
    if (status)
    {
        nx_dns_delete(&dns_0);
        return status;
    }

    /* Output DNS Server address.  */
    PRINTF("DNS Server address: %lu.%lu.%lu.%lu\r\n",
           (dns_server_address[0] >> 24),
           (dns_server_address[0] >> 16 & 0xFF),
           (dns_server_address[0] >> 8 & 0xFF),
           (dns_server_address[0] & 0xFF));

    return NX_SUCCESS;
}

/* Sync up the local time.  */
static UINT sntp_time_sync()
{
    UINT    status;
    UINT    server_status;
    ULONG   sntp_server_address;
    UINT    i;

#ifndef SAMPLE_SNTP_SERVER_ADDRESS
    PRINTF("SNTP Time Sync...%s\r\n", sntp_servers[sntp_server_index]);

    /* Look up SNTP Server address. */
    status = nx_dns_host_by_name_get(&dns_0, (UCHAR *)sntp_servers[sntp_server_index],
                                     &sntp_server_address, 5 * NX_IP_PERIODIC_RATE);
    if (status)
    {
        return status;
    }
#else /* !SAMPLE_SNTP_SERVER_ADDRESS */

    PRINTF("SNTP Time Sync...\r\n");
    sntp_server_address = SAMPLE_SNTP_SERVER_ADDRESS;
#endif /* SAMPLE_SNTP_SERVER_ADDRESS */

    /* Create the SNTP Client to run in broadcast mode.. */
    status =  nx_sntp_client_create(&sntp_client, &ip_0, 0, &pool_0,
                                    NX_NULL,
                                    NX_NULL,
                                    NX_NULL /* no random_number_generator callback */);
    if (status)
    {
        return status;
    }

    /* Use the IPv4 service to initialize the Client and set the IPv4 SNTP server. */
    status = nx_sntp_client_initialize_unicast(&sntp_client, sntp_server_address);
    if (status)
    {
        nx_sntp_client_delete(&sntp_client);
        return status;
    }

    /* Set local time to 0 */
    status = nx_sntp_client_set_local_time(&sntp_client, 0, 0);
    if (status)
    {
        nx_sntp_client_delete(&sntp_client);
        return status;
    }

    /* Run Unicast client */
    status = nx_sntp_client_run_unicast(&sntp_client);
    if (status)
    {
        nx_sntp_client_stop(&sntp_client);
        nx_sntp_client_delete(&sntp_client);
        return status;
    }

    /* Wait till updates are received */
    for (i = 0; i < SAMPLE_SNTP_UPDATE_MAX; i++)
    {
        /* First verify we have a valid SNTP service running. */
        status = nx_sntp_client_receiving_updates(&sntp_client, &server_status);
        if ((status == NX_SUCCESS) && (server_status == NX_TRUE))
        {
            /* Server status is good. Now get the Client local time. */
            ULONG sntp_seconds, sntp_fraction;
            ULONG system_time_in_second;

            /* Get the local time.  */
            status = nx_sntp_client_get_local_time(&sntp_client, &sntp_seconds, &sntp_fraction, NX_NULL);

            /* Check status.  */
            if (status != NX_SUCCESS)
            {
                continue;
            }

            /* Get the system time in second.  */
            system_time_in_second = tx_time_get() / TX_TIMER_TICKS_PER_SECOND;

            /* Convert to Unix epoch and minus the current system time.  */
            unix_time_base = (sntp_seconds - (system_time_in_second + SAMPLE_UNIX_TO_NTP_EPOCH_SECOND));

            /* Time sync successfully.  */

            /* Stop and delete SNTP.  */
            nx_sntp_client_stop(&sntp_client);
            nx_sntp_client_delete(&sntp_client);

            return NX_SUCCESS;
        }

        tx_thread_sleep(SAMPLE_SNTP_UPDATE_INTERVAL);
    }

    /* Time sync failed.  */

    /* Stop and delete SNTP.  */
    nx_sntp_client_stop(&sntp_client);
    nx_sntp_client_delete(&sntp_client);

    return NX_NOT_SUCCESSFUL;
}

static UINT unix_time_get(ULONG *unix_time)
{
    /* Return number of seconds since Unix Epoch (1/1/1970 00:00:00).  */
    *unix_time =  unix_time_base + (tx_time_get() / TX_TIMER_TICKS_PER_SECOND);

    return NX_SUCCESS;
}
