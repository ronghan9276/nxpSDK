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

/*******************************************************************************
 * Includes
 ******************************************************************************/
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

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* LPI2C */
#define BOARD_ACCEL_I2C_BASEADDR LPI2C1
/* Select USB1 PLL (480 MHz) as LPI2C's clock source */
#define BOARD_ACCEL_I2C_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for LPI2C clock source */
#define BOARD_ACCEL_I2C_CLOCK_SOURCE_DIVIDER (5U)
#define BOARD_ACCEL_I2C_CLOCK_FREQ           (CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8 / (BOARD_ACCEL_I2C_CLOCK_SOURCE_DIVIDER + 1U))
#define LOGGING_TASK_PRIORITY   (tskIDLE_PRIORITY + 1)
#define LOGGING_TASK_STACK_SIZE (200)
#define LOGGING_QUEUE_LENGTH    (16)

#define DEMO_TASK_STACK_SIZE (configMINIMAL_STACK_SIZE * 15)
#define DEMO_TASK_PRIORITY   (tskIDLE_PRIORITY + 1)

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
/* Declaration of demo function. */
extern int RunRemoteControlDemo(bool awsIotMqttMode,
                                const char *pIdentifier,
                                void *pNetworkServerInfo,
                                void *pNetworkCredentialInfo,
                                const IotNetworkInterface_t *pNetworkInterface);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Count of LED which can be controlled */
uint8_t ledCount = 1;
/* Array of LED names */
char *ledName[] = {"LED"};
/* Array of LED colors in JSON */
char ledColors[] = "[\"green\"]";

/*******************************************************************************
 * Code
 ******************************************************************************/
void turnOnLed(uint8_t id)
{
    if (id == 0)
    {
        USER_LED_ON();
    }
}

void turnOffLed(uint8_t id)
{
    if (id == 0)
    {
        USER_LED_OFF();
    }
}

/*!
 * @brief Initialize pin for control LED
 */
void BOARD_InitLEDs()
{
    USER_LED_INIT(LOGIC_LED_OFF);
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

void vApplicationDaemonTaskStartupHook(void)
{
    /* A simple example to demonstrate key and certificate provisioning in
     * microcontroller flash using PKCS#11 interface. This should be replaced
     * by production ready key provisioning mechanism. */
    vDevModeKeyProvisioning();

    if (SYSTEM_Init() == pdPASS)
    {
        static demoContext_t mqttDemoContext = {.networkTypes                = AWSIOT_NETWORK_TYPE_WIFI,
                                                .demoFunction                = RunRemoteControlDemo,
                                                .networkConnectedCallback    = NULL,
                                                .networkDisconnectedCallback = NULL};

        Iot_CreateDetachedThread(runDemoTask, &mqttDemoContext, DEMO_TASK_PRIORITY, DEMO_TASK_STACK_SIZE);
    }
}

int main(void)
{
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_I2C_ConfigurePins();
    BOARD_InitDebugConsole();

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
