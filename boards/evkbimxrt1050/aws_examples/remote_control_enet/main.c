/*
 * FreeRTOS V1.0.0
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software. If you wish to use our Amazon
 * FreeRTOS name, please do so in a fair use way that does not cause confusion.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

///////////////////////////////////////////////////////////////////////////////
//  Includes
///////////////////////////////////////////////////////////////////////////////
/* SDK Included Files */
#include "fsl_debug_console.h"
#include "ksdk_mbedtls.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
/* FreeRTOS Demo Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "iot_logging_task.h"
#include "iot_system_init.h"
#include "aws_dev_mode_key_provisioning.h"
#include "platform/iot_threads.h"
#include "types/iot_network_types.h"
#include "aws_demo.h"

/* Board specific accelerometer driver include */
#if defined(BOARD_ACCEL_FXOS)
#include "fsl_fxos.h"
#elif defined(BOARD_ACCEL_MMA)
#include "fsl_mma.h"
#endif

#include "fsl_phy.h"
/* lwIP Includes */
#include "lwip/tcpip.h"
#include "lwip/dhcp.h"
#include "lwip/prot/dhcp.h"
#include "netif/ethernet.h"
#include "enet_ethernetif.h"
#include "lwip/netifapi.h"
#include "fsl_gpio.h"
#include "fsl_iomuxc.h"
#include "fsl_phyksz8081.h"
#include "fsl_enet_mdio.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef EXAMPLE_NETIF_INIT_FN
/*! @brief Network interface initialization function. */
#define EXAMPLE_NETIF_INIT_FN ethernetif0_init
#endif /* EXAMPLE_NETIF_INIT_FN */

#define INIT_SUCCESS 0
#define INIT_FAIL    1

/* MAC address configuration. */
#define configMAC_ADDR                     \
    {                                      \
        0x02, 0x12, 0x13, 0x10, 0x15, 0x25 \
    }

/* Address of PHY interface. */
#define EXAMPLE_PHY_ADDRESS BOARD_ENET0_PHY_ADDRESS

/* MDIO operations. */
#define EXAMPLE_MDIO_OPS enet_ops

/* PHY operations. */
#define EXAMPLE_PHY_OPS phyksz8081_ops

/* ENET clock frequency. */
#define EXAMPLE_CLOCK_FREQ CLOCK_GetFreq(kCLOCK_IpgClk)

/* LPI2C */
/* Select USB1 PLL (480 MHz) as LPI2C's clock source */
#define BOARD_ACCEL_I2C_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for LPI2C clock source */
#define BOARD_ACCEL_I2C_CLOCK_SOURCE_DIVIDER (5U)
#define BOARD_ACCEL_I2C_CLOCK_FREQ           (CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8 / (BOARD_ACCEL_I2C_CLOCK_SOURCE_DIVIDER + 1U))
#define LOGGING_TASK_PRIORITY   (tskIDLE_PRIORITY + 1)
#define LOGGING_TASK_STACK_SIZE (200)
#define LOGGING_QUEUE_LENGTH    (16)

/* Accelerometer driver specific defines */
#if defined(BOARD_ACCEL_FXOS)
#define XYZ_DATA_CFG                          XYZ_DATA_CFG_REG
#define ACCEL_INIT(handle, config)            FXOS_Init(handle, config)
#define ACCEL_READ_REG(handle, reg, val)      FXOS_ReadReg(handle, reg, val, 1)
#define ACCELL_READ_SENSOR_DATA(handle, data) FXOS_ReadSensorData(handle, data)
#define ACCEL_GET_RESOLUTION()                FXOS_GetResolutionBits()
#elif defined(BOARD_ACCEL_MMA)
#define XYZ_DATA_CFG                          kMMA8652_XYZ_DATA_CFG
#define ACCEL_INIT(handle, config)            MMA_Init(handle, config)
#define ACCEL_READ_REG(handle, reg, val)      MMA_ReadReg(handle, reg, val)
#define ACCELL_READ_SENSOR_DATA(handle, data) MMA_ReadSensorData(handle, data)
#define ACCEL_GET_RESOLUTION()                MMA_GetResolutionBits()
#endif

/* Accelerometer and magnetometer */
#if defined(BOARD_ACCEL_FXOS)
fxos_handle_t accelHandle           = {0};
static const uint8_t accelAddress[] = {0x1CU, 0x1EU, 0x1DU, 0x1FU};
fxos_config_t config                = {0};
#elif defined(BOARD_ACCEL_MMA)
mma_handle_t accelHandle            = {0};
static const uint8_t accelAddress[] = {0x1CU, 0x1DU, 0x1EU, 0x1FU};
mma_config_t config                 = {0};
#endif

/* Accelerometer data scale */
uint8_t g_accelDataScale = 0;
/* Resolution of accelerometer (14 bit or 12 bit) */
uint8_t g_accelResolution = 0;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_InitLEDs(void);
extern void vStartLedDemoTask(void);
extern int initNetwork(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static mdio_handle_t mdioHandle = {.ops = &EXAMPLE_MDIO_OPS};
static phy_handle_t phyHandle   = {.phyAddr = EXAMPLE_PHY_ADDRESS, .mdioHandle = &mdioHandle, .ops = &EXAMPLE_PHY_OPS};

struct netif netif;
#if defined(FSL_FEATURE_SOC_LPC_ENET_COUNT) && (FSL_FEATURE_SOC_LPC_ENET_COUNT > 0)
mem_range_t non_dma_memory[] = NON_DMA_MEMORY_ARRAY;
#endif /* FSL_FEATURE_SOC_LPC_ENET_COUNT */
/* Count of LED */
uint8_t ledCount = 0;
/* Array of LED names */
char *ledName[] = {""};
/* Array of LED colors in JSON */
char ledColors[] = "[]";

/*******************************************************************************
 * Code
 ******************************************************************************/
int initNetwork(void)
{
    ip4_addr_t netif_ipaddr, netif_netmask, netif_gw;
    ethernetif_config_t enet_config = {
        .phyHandle  = &phyHandle,
        .macAddress = configMAC_ADDR,
#if defined(FSL_FEATURE_SOC_LPC_ENET_COUNT) && (FSL_FEATURE_SOC_LPC_ENET_COUNT > 0)
        .non_dma_memory = non_dma_memory,
#endif /* FSL_FEATURE_SOC_LPC_ENET_COUNT */
    };

    mdioHandle.resource.csrClock_Hz = EXAMPLE_CLOCK_FREQ;

    IP4_ADDR(&netif_ipaddr, 0, 0, 0, 0);
    IP4_ADDR(&netif_netmask, 0, 0, 0, 0);
    IP4_ADDR(&netif_gw, 0, 0, 0, 0);

    tcpip_init(NULL, NULL);

    netifapi_netif_add(&netif, &netif_ipaddr, &netif_netmask, &netif_gw, &enet_config, EXAMPLE_NETIF_INIT_FN,
                       tcpip_input);
    netifapi_netif_set_default(&netif);
    netifapi_netif_set_up(&netif);

    configPRINTF(("Getting IP address from DHCP ...\r\n"));
    netifapi_dhcp_start(&netif);

    struct dhcp *dhcp;
    dhcp = (struct dhcp *)netif_get_client_data(&netif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP);

    while (dhcp->state != DHCP_STATE_BOUND)
    {
        vTaskDelay(1000);
    }

    if (dhcp->state == DHCP_STATE_BOUND)
    {
        configPRINTF(("IPv4 Address: %u.%u.%u.%u\r\n", ((u8_t *)&netif.ip_addr.addr)[0],
                      ((u8_t *)&netif.ip_addr.addr)[1], ((u8_t *)&netif.ip_addr.addr)[2],
                      ((u8_t *)&netif.ip_addr.addr)[3]));
    }
    configPRINTF(("DHCP OK\r\n"));

    return INIT_SUCCESS;
}
void turnOnLed(uint8_t id)
{
}

void turnOffLed(uint8_t id)
{
}

/*!
 * @brief Initialize pin for control LED
 */
void BOARD_InitLEDs()
{
}

void BOARD_InitModuleClock(void)
{
    const clock_enet_pll_config_t config = {.enableClkOutput = true, .enableClkOutput25M = false, .loopDivider = 1};
    CLOCK_InitEnetPll(&config);
}

void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 1000000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

void print_string(const char *string)
{
    PRINTF(string);
}

#if defined(BOARD_ACCEL_FXOS) || defined(BOARD_ACCEL_MMA)
/*!
 * @brief Initialize accelerometer sensor
 */
status_t init_mag_accel(uint8_t *accelDataScale, uint8_t *accelResolution)
{
    uint8_t arrayAddrSize = 0;
    uint8_t sensorRange   = 0;
    uint16_t i            = 0;
    status_t result       = kStatus_Fail;

    /* Configure the I2C function */
    config.I2C_SendFunc    = BOARD_Accel_I2C_Send;
    config.I2C_ReceiveFunc = BOARD_Accel_I2C_Receive;

    /* Initialize sensor devices */
    arrayAddrSize = sizeof(accelAddress) / sizeof(accelAddress[0]);
    for (i = 0; i < arrayAddrSize; i++)
    {
        config.slaveAddress = accelAddress[i];
        /* Initialize accelerometer sensor */
        result = ACCEL_INIT(&accelHandle, &config);
        if (result == kStatus_Success)
        {
            break;
        }
    }

    if (result != kStatus_Success)
    {
        PRINTF("\r\nSensor device initialize failed!\r\n");
        PRINTF("\r\nPlease check the sensor chip\r\n");
        return result;
    }

    *accelResolution = ACCEL_GET_RESOLUTION();

    /* Get sensor range */
    if (kStatus_Success != ACCEL_READ_REG(&accelHandle, XYZ_DATA_CFG, &sensorRange))
    {
        return kStatus_Fail;
    }
    if (sensorRange == 0x00)
    {
        *accelDataScale = 2U;
    }
    else if (sensorRange == 0x01)
    {
        *accelDataScale = 4U;
    }
    else if (sensorRange == 0x10)
    {
        *accelDataScale = 8U;
    }

    return kStatus_Success;
}
#endif

void main_task(void *pvParameters)
{
    /* A simple example to demonstrate key and certificate provisioning in
     * microcontroller flash using PKCS#11 interface. This should be replaced
     * by production ready key provisioning mechanism. */
    vDevModeKeyProvisioning();

    if (SYSTEM_Init() == pdPASS)
    {
        if (initNetwork() != 0)
        {
            configPRINTF(("Network init failed, stopping demo.\r\n"));
            vTaskDelete(NULL);
        }
        else
        {
            vStartLedDemoTask();
        }
    }

    vTaskDelete(NULL);
}

int main(void)
{
    gpio_pin_config_t gpio_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};

    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_I2C_ConfigurePins();
    BOARD_InitDebugConsole();
    BOARD_InitModuleClock();

    IOMUXC_EnableMode(IOMUXC_GPR, kIOMUXC_GPR_ENET1TxClkOutputDir, true);

    GPIO_PinInit(GPIO1, 9, &gpio_config);
    GPIO_PinInit(GPIO1, 10, &gpio_config);
    /* pull up the ENET_INT before RESET. */
    GPIO_WritePinOutput(GPIO1, 10, 1);
    GPIO_WritePinOutput(GPIO1, 9, 0);
    delay();
    GPIO_WritePinOutput(GPIO1, 9, 1);

    BOARD_InitLEDs();

    /* Clock setting for LPI2C */
    CLOCK_SetMux(kCLOCK_Lpi2cMux, BOARD_ACCEL_I2C_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, BOARD_ACCEL_I2C_CLOCK_SOURCE_DIVIDER);
    CRYPTO_InitHardware();

#if defined(BOARD_ACCEL_FXOS) || defined(BOARD_ACCEL_MMA)
    /* Initialize I2C */
    BOARD_Accel_I2C_Init();

    /* Initialize magnetometer and accelerometer */
    if (kStatus_Success != init_mag_accel(&g_accelDataScale, &g_accelResolution))
    {
        /* Failed to initialize accelerometer */
        for (;;)
            ;
    }
#endif

    if (xTaskCreate(main_task, "main_task", configMINIMAL_STACK_SIZE * 8, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
    {
        PRINTF("Main task creation failed!.\r\n");
        while (1)
            ;
    }

    xLoggingTaskInitialize(LOGGING_TASK_STACK_SIZE, LOGGING_TASK_PRIORITY, LOGGING_QUEUE_LENGTH);

    vTaskStartScheduler();
    for (;;)
        ;
}

void *pvPortCalloc(size_t xNum, size_t xSize)
{
    void *pvReturn;

    pvReturn = pvPortMalloc(xNum * xSize);
    if (pvReturn != NULL)
    {
        memset(pvReturn, 0x00, xNum * xSize);
    }

    return pvReturn;
}
