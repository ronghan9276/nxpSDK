#define NX_ENABLE_DHCP

#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "tx_api.h"
#include "nx_api.h"
#ifdef NX_ENABLE_DHCP
#include "nxd_dhcp_client.h"
#endif

#include "fsl_iomuxc.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Define demo stack size.   */
#define NX_PACKET_POOL_SIZE ((1536 + sizeof(NX_PACKET)) * 40)
#define DEMO_STACK_SIZE     2048
#define HTTP_STACK_SIZE     2048
#define IPERF_STACK_SIZE    2048

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Define the ThreadX and NetX object control blocks...  */
TX_THREAD thread_0;
NX_PACKET_POOL pool_0;
NX_IP ip_0;
#ifdef NX_ENABLE_DHCP
AT_NONCACHEABLE_SECTION_ALIGN(NX_DHCP dhcp_client, 64);
UCHAR ip_address[4];
UCHAR network_mask[4];
#endif
ULONG thread_0_stack[DEMO_STACK_SIZE / sizeof(ULONG)];
ULONG http_stack[HTTP_STACK_SIZE / sizeof(ULONG)];
ULONG iperf_stack[IPERF_STACK_SIZE / sizeof(ULONG)];
#ifdef FEATURE_NX_IPV6
NXD_ADDRESS ipv6_address;
#endif

/* Define the IP thread's stack area.  */
ULONG ip_thread_stack[2 * 1024 / sizeof(ULONG)];

/* Define packet pool for the demonstration.  */
AT_NONCACHEABLE_SECTION_ALIGN(ULONG packet_pool_area[NX_PACKET_POOL_SIZE / 4 + 4], 64);

/* Define the ARP cache area.  */
ULONG arp_space_area[1024 / sizeof(ULONG)];

/* Define the counters used in the demo application...  */
ULONG error_counter;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* Define thread prototypes.  */
VOID thread_0_entry(ULONG thread_input);
extern VOID nx_iperf_entry(NX_PACKET_POOL *pool_ptr,
                           NX_IP *ip_ptr,
                           UCHAR *http_stack,
                           ULONG http_stack_size,
                           UCHAR *iperf_stack,
                           ULONG iperf_stack_size);

/***** Substitute your ethernet driver entry function here *********/
extern VOID nx_driver_imx(NX_IP_DRIVER *);

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

int main(void)
{
    /* Init board hardware. */
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

    PRINTF("Start the iperf example...\r\n");

    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();

    return 0;
}

/* Define what the initial system looks like.  */
VOID tx_application_define(void *first_unused_memory)
{
    UINT status;

    NX_PARAMETER_NOT_USED(first_unused_memory);

    /* Initialize the NetX system.  */
    nx_system_initialize();

    /* Create a packet pool.  */
    status = nx_packet_pool_create(&pool_0, "NetX Main Packet Pool", 1536,
                                   (ULONG *)(((int)packet_pool_area + 15) & ~15), NX_PACKET_POOL_SIZE);

    /* Check for packet pool create errors.  */
    if (status)
        error_counter++;

    /* Create an IP instance.  */
    status = nx_ip_create(&ip_0, "NetX IP Instance 0",
#ifdef NX_ENABLE_DHCP
                          IP_ADDRESS(0, 0, 0, 0), IP_ADDRESS(0, 0, 0, 0),
#else
                          IP_ADDRESS(192, 168, 111, 2), 0xFFFFFF00UL,
#endif
                          &pool_0, nx_driver_imx, (UCHAR *)ip_thread_stack, sizeof(ip_thread_stack), 1);

    /* Check for IP create errors.  */
    if (status)
        error_counter++;

    /* Enable ARP and supply ARP cache memory for IP Instance 0.  */
    status = nx_arp_enable(&ip_0, (void *)arp_space_area, sizeof(arp_space_area));

    /* Check for ARP enable errors.  */
    if (status)
        error_counter++;

    /* Enable ICMP */
    status = nx_icmp_enable(&ip_0);

    /* Check for ICMP enable errors.  */
    if (status)
        error_counter++;

    /* Enable UDP traffic.  */
    status = nx_udp_enable(&ip_0);

    /* Check for UDP enable errors.  */
    if (status)
        error_counter++;

    /* Enable TCP traffic.  */
    status = nx_tcp_enable(&ip_0);

    /* Check for TCP enable errors.  */
    if (status)
        error_counter++;

    /* Create the main thread.  */
    tx_thread_create(&thread_0, "thread 0", thread_0_entry, 0, thread_0_stack, sizeof(thread_0_stack), 4, 4,
                     TX_NO_TIME_SLICE, TX_AUTO_START);

#ifdef FEATURE_NX_IPV6
    /* Set up the IPv6 address here. */
    ipv6_address.nxd_ip_address.v6[3] = 0x3;
    ipv6_address.nxd_ip_address.v6[2] = 0x0;
    ipv6_address.nxd_ip_address.v6[1] = 0x0;
    ipv6_address.nxd_ip_address.v6[0] = 0xfe800000;
    ipv6_address.nxd_ip_version       = NX_IP_VERSION_V6;

    /* Enable ICMPv6 services. */
    status = nxd_icmp_enable(&ip_0);
    if (status)
        error_counter++;

    /* Enable IPv6 services. */
    status = nxd_ipv6_enable(&ip_0);
    if (status)
        error_counter++;

    status = nxd_ipv6_address_set(&ip_0, 0, &ipv6_address, 10, NX_NULL);
    if (status)
        error_counter++;
#endif
}

/* Define the test threads.  */
VOID thread_0_entry(ULONG thread_input)
{
    NX_PARAMETER_NOT_USED(thread_input);

#ifdef NX_ENABLE_DHCP
    UINT status;
    ULONG actual_status;
    ULONG temp;

    /* Create the DHCP instance.  */
    PRINTF("DHCP In Progress...\r\n");

    nx_dhcp_create(&dhcp_client, &ip_0, "dhcp_client");

    /* Start the DHCP Client.  */
    nx_dhcp_start(&dhcp_client);

    /* Wait util address is solved. */
    status = nx_ip_status_check(&ip_0, NX_IP_ADDRESS_RESOLVED, &actual_status, 1000);

    if (status)
    {
        /* DHCP Failed...  no IP address! */
        PRINTF("Can't resolve address\r\n");
    }
    else
    {
        /* Get IP address. */
        nx_ip_address_get(&ip_0, (ULONG *)&ip_address[0], (ULONG *)&network_mask[0]);

        /* Convert IP address & network mask from little endian.  */
        temp = *((ULONG *)&ip_address[0]);
        NX_CHANGE_ULONG_ENDIAN(temp);
        *((ULONG *)&ip_address[0]) = temp;

        temp = *((ULONG *)&network_mask[0]);
        NX_CHANGE_ULONG_ENDIAN(temp);
        *((ULONG *)&network_mask[0]) = temp;

        /* Output IP address. */
        PRINTF("IP address: %d.%d.%d.%d\r\nMask: %d.%d.%d.%d\r\n", (UINT)(ip_address[0]), (UINT)(ip_address[1]),
               (UINT)(ip_address[2]), (UINT)(ip_address[3]), (UINT)(network_mask[0]), (UINT)(network_mask[1]),
               (UINT)(network_mask[2]), (UINT)(network_mask[3]));
    }
#endif

#ifdef FEATURE_NX_IPV6
    tx_thread_sleep(NX_IP_PERIODIC_RATE);
#endif

    /* Call entry function to start iperf test.  */
    nx_iperf_entry(&pool_0, &ip_0, (UCHAR *)http_stack, sizeof(http_stack), (UCHAR *)iperf_stack, sizeof(iperf_stack));
}
