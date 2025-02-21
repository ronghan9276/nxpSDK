/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* Board specific includes */
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_adc16.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

/* Board specific accelerometer driver include */
#if defined(BOARD_ACCEL_FXOS)
#include "fsl_fxos.h"
#elif defined(BOARD_ACCEL_MMA)
#include "fsl_mma.h"
#endif

/* DAC driver include */
#ifdef BOARD_DAC_BASEADDR
#include "fsl_dac.h"
#endif

/* eRPC includes */
#include "erpc_arbitrated_client_setup.h"
#include "erpc_error_handler.h"
#include "erpc_server_setup.h"
#include "erpc_transport_setup.h"

/* App 0 service code, server part */
#include "erpc_remote_control_app_0.h"
#include "erpc_remote_control_app_0_server.h"

/* App 1 service code, client part */
#include "erpc_remote_control_app_1.h"

#include "fsl_uart_cmsis.h"
#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_ADC16_BASEADDR      ADC0
#define DEMO_ADC16_CHANNEL_GROUP 0U
#define DEMO_ADC16_USER_CHANNEL  8U /* ADC0_SE8 */

#define DEMO_ADC16_IRQn             ADC0_IRQn
#define DEMO_ADC16_IRQ_HANDLER_FUNC ADC0_IRQHandler

#define BOARD_LED_GPIO     BOARD_LED_GREEN_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_GREEN_GPIO_PIN

/* I2C source clock */
#define I2C_BAUDRATE          100000U
#define ACCEL_I2C_ADDR        1CU
#define ACCEL_I2C_CLK_SRC     I2C0_CLK_SRC
#define I2C_RELEASE_SDA_PORT  PORTA
#define I2C_RELEASE_SCL_PORT  PORTA
#define I2C_RELEASE_SDA_GPIO  GPIOA
#define I2C_RELEASE_SDA_PIN   1U
#define I2C_RELEASE_SCL_GPIO  GPIOA
#define I2C_RELEASE_SCL_PIN   2U
#define I2C_RELEASE_BUS_COUNT 100U

#define ERPC_DEMO_UART                Driver_USART1
#define ERPC_DEMO_UART_RX_TX_IRQn     BOARD_UART_IRQ
#define ERPC_DEMO_UART_RX_TX_IRQ_PRIO (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1U)
/* ADC configuration */
#define VREF_BRD 3.300
#define SE_12BIT 4096.0

/* Interrupt priority */
#define SW_NVIC_PRIO 2

/* Accelerometer driver specific defines */
#if defined(BOARD_ACCEL_FXOS)
#define XYZ_DATA_CFG                          XYZ_DATA_CFG_REG
#define ACCEL_INIT(handle, config)            FXOS_Init(handle, config)
#define ACCEL_READ_REG(handle, reg, val)      FXOS_ReadReg(handle, reg, val, 1)
#define ACCELL_READ_SENSOR_DATA(handle, data) FXOS_ReadSensorData(handle, data)

#elif defined(BOARD_ACCEL_MMA)
#define XYZ_DATA_CFG                          kMMA8451_XYZ_DATA_CFG
#define ACCEL_INIT(handle, config)            MMA_Init(handle, config)
#define ACCEL_READ_REG(handle, reg, val)      MMA_ReadReg(handle, reg, val)
#define ACCELL_READ_SENSOR_DATA(handle, data) MMA_ReadSensorData(handle, data)
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_I2C_ReleaseBus(void);

/*!
 * @brief Initialize and configure DAC and ADC
 */
static void init_dac_adc(void);

/*!
 * @brief Initialize GPIO pins
 */
static void init_pins(void);

/*!
 * @brief Initialize magnetometer and accelerometer sensor
 *
 * @return kStatus_Success If initialization was successful
 * @return kStatus_Fail If initialization has failed
 */
static status_t init_mag_accel(void);

/*!
 * @brief Server task creates transport arbitrator and creates remote control service
 */
static void server_task(void *pvParameters);

/*!
 * @brief Client task
 */
static void client_task(void *pvParameters);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static adc16_channel_config_t adc16ChannelConfigStruct;
static erpc_transport_t transportArbitrator = NULL; /*! eRPC transport arbitrator */
static erpc_mbf_t message_buffer_factory    = NULL; /* MessageBufferFactory */
static uint8_t swButton                     = 0;    /*! Which SW button was pressed */
extern bool g_erpc_error_occurred;

/* FreeRTOS task handles */
TaskHandle_t serverTaskHandle = NULL;
TaskHandle_t clientTaskHandle = NULL;

/* Accelerometer and magnetometer */
#if defined(BOARD_ACCEL_FXOS)
static fxos_handle_t accelHandle    = {0};
static const uint8_t accelAddress[] = {0x1CU, 0x1EU, 0x1DU, 0x1FU};
fxos_config_t config                = {0};
#elif defined(BOARD_ACCEL_MMA)
static mma_handle_t accelHandle     = {0};
static const uint8_t accelAddress[] = {0x1CU, 0x1DU, 0x1EU, 0x1FU};
mma_config_t config                 = {0};
#endif
static uint8_t accelDataScale = 0; /*! Accelerometer data scale */

/* GPIO LED configuration */
gpio_pin_config_t led_config = {
    kGPIO_DigitalOutput,
    0,
};

/* GPIO SW buttons configuration */
gpio_pin_config_t sw_config = {
    kGPIO_DigitalInput,
    0,
};

/*******************************************************************************
 * Code
 ******************************************************************************/

static void i2c_release_bus_delay(void)
{
    uint32_t i = 0;
    for (i = 0; i < I2C_RELEASE_BUS_COUNT; i++)
    {
        __NOP();
    }
}

void BOARD_I2C_ReleaseBus(void)
{
    CLOCK_EnableClock(kCLOCK_PortB);

    uint8_t i = 0;
    gpio_pin_config_t pin_config;
    port_pin_config_t i2c_pin_config = {0};

    /* Config pin mux as gpio */
    i2c_pin_config.pullSelect = kPORT_PullUp;
    i2c_pin_config.mux        = kPORT_MuxAsGpio;

    pin_config.pinDirection = kGPIO_DigitalOutput;
    pin_config.outputLogic  = 1U;
    CLOCK_EnableClock(kCLOCK_PortB);
    PORT_SetPinConfig(I2C_RELEASE_SCL_PORT, I2C_RELEASE_SCL_PIN, &i2c_pin_config);
    PORT_SetPinConfig(I2C_RELEASE_SDA_PORT, I2C_RELEASE_SDA_PIN, &i2c_pin_config);

    GPIO_PinInit(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, &pin_config);
    GPIO_PinInit(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, &pin_config);

    /* Drive SDA low first to simulate a start */
    GPIO_PinWrite(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 0U);
    i2c_release_bus_delay();

    /* Send 9 pulses on SCL and keep SDA high */
    for (i = 0; i < 9; i++)
    {
        GPIO_PinWrite(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 0U);
        i2c_release_bus_delay();

        GPIO_PinWrite(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 1U);
        i2c_release_bus_delay();

        GPIO_PinWrite(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 1U);
        i2c_release_bus_delay();
        i2c_release_bus_delay();
    }

    /* Send stop */
    GPIO_PinWrite(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_PinWrite(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_PinWrite(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 1U);
    i2c_release_bus_delay();

    GPIO_PinWrite(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 1U);
    i2c_release_bus_delay();
}

uint32_t UART1_GetFreq(void)
{
    return CLOCK_GetFreq(UART1_CLK_SRC);
}

/*!
 * @brief Get board configuration (if DAC and RGB LEDs are present)
 */
void get_board_config(BoardConfig *config)
{
    /* default values */
    config->DAC    = false;
    config->MAG    = false;
    config->RGB[0] = false;
    config->RGB[1] = false;
    config->RGB[2] = false;

#ifdef BOARD_DAC_BASEADDR
    config->DAC = true;
#endif

#ifdef BOARD_ACCEL_FXOS
    config->MAG = true;
#endif

#ifdef BOARD_LED_RED_GPIO_PORT
    config->RGB[0] = true;
#endif

#ifdef BOARD_LED_GREEN_GPIO_PORT
    config->RGB[1] = true;
#endif

#ifdef BOARD_LED_BLUE_GPIO_PORT
    config->RGB[2] = true;
#endif
}

/*!
 * @brief Get ADC configuration
 */
void get_adc_config(AdcConfig *config)
{
    config->vref        = VREF_BRD;
    config->atomicSteps = SE_12BIT;
}

/*!
 * @brief Initialize and configure DAC and ADC
 */
static void init_dac_adc(void)
{
    adc16_config_t adc16ConfigStruct;
#ifdef BOARD_DAC_BASEADDR
    dac_config_t dacConfigStruct;

    /* Configure the DAC. */
    DAC_GetDefaultConfig(&dacConfigStruct);
    DAC_Init(BOARD_DAC_BASEADDR, &dacConfigStruct);
    DAC_Enable(BOARD_DAC_BASEADDR, true);
#endif

    /* Configure the ADC16. */
    ADC16_GetDefaultConfig(&adc16ConfigStruct);
    ADC16_Init(DEMO_ADC16_BASEADDR, &adc16ConfigStruct);

    /* Make sure the software trigger is used. */
    ADC16_EnableHardwareTrigger(DEMO_ADC16_BASEADDR, false);

#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    if (kStatus_Success != ADC16_DoAutoCalibration(DEMO_ADC16_BASEADDR))
    {
        // ADC16_DoAutoCalibration() Failed
    }
#endif

    /* Prepare ADC channel setting */
    adc16ChannelConfigStruct.channelNumber                        = DEMO_ADC16_USER_CHANNEL;
    adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;

#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    adc16ChannelConfigStruct.enableDifferentialConversion = false;
#endif
}

/*!
 * @brief Initialize GPIO pins
 */
static void init_pins(void)
{
/* Initialize pins for LEDs */
#if defined(BOARD_LED_RED_GPIO_PORT)
    GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, &led_config);
    LED_RED_OFF();
#endif
#if defined(BOARD_LED_GREEN_GPIO_PORT)
    GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, &led_config);
    LED_GREEN_OFF();
#endif
#if defined(BOARD_LED_BLUE_GPIO_PORT)
    GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, &led_config);
    LED_BLUE_OFF();
#endif

/* Initialize pins for SW buttons */
#if defined(BOARD_SW1_GPIO)
    GPIO_PinInit(BOARD_SW1_GPIO, BOARD_SW1_GPIO_PIN, &sw_config);
    PORT_SetPinInterruptConfig(BOARD_SW1_PORT, BOARD_SW1_GPIO_PIN, kPORT_InterruptFallingEdge);
    NVIC_SetPriority(BOARD_SW1_IRQ, SW_NVIC_PRIO);
    EnableIRQ(BOARD_SW1_IRQ);
#endif
#if defined(BOARD_SW2_GPIO)
    GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_GPIO_PIN, &sw_config);
    PORT_SetPinInterruptConfig(BOARD_SW2_PORT, BOARD_SW2_GPIO_PIN, kPORT_InterruptFallingEdge);
    NVIC_SetPriority(BOARD_SW2_IRQ, SW_NVIC_PRIO);
    EnableIRQ(BOARD_SW2_IRQ);
#endif
#if defined(BOARD_SW3_GPIO)
    GPIO_PinInit(BOARD_SW3_GPIO, BOARD_SW3_GPIO_PIN, &sw_config);
    PORT_SetPinInterruptConfig(BOARD_SW3_PORT, BOARD_SW3_GPIO_PIN, kPORT_InterruptFallingEdge);
    NVIC_SetPriority(BOARD_SW3_IRQ, SW_NVIC_PRIO);
    EnableIRQ(BOARD_SW3_IRQ);
#endif
}

/* SW buttons interrupts */
#if defined(BOARD_SW1_GPIO) && !defined(BOARD_SW2_GPIO)
void BOARD_SW1_IRQ_HANDLER(void)
{
    /* Save which SW button was pressed */
    swButton = 1;

    /* Clear external interrupt flag. */
    GPIO_PortClearInterruptFlags(BOARD_SW1_GPIO, 1U << BOARD_SW1_GPIO_PIN);
    SDK_ISR_EXIT_BARRIER;
}
#endif
#if defined(BOARD_SW2_SW3_SHARED_IRQ_HANDLER)
void BOARD_SW2_IRQ_HANDLER(void)
{
    uint32_t intMask;

    /* Save which SW button was pressed */
    intMask = GPIO_PortGetInterruptFlags(BOARD_SW2_GPIO);
    if ((intMask & (1U << BOARD_SW2_GPIO_PIN)) != 0)
    {
        swButton = 2;
        GPIO_PortClearInterruptFlags(BOARD_SW2_GPIO, 1U << BOARD_SW2_GPIO_PIN);
    }
    intMask = GPIO_PortGetInterruptFlags(BOARD_SW3_GPIO);
    if ((intMask & (1U << BOARD_SW3_GPIO_PIN)) != 0)
    {
        swButton = 3;
        GPIO_PortClearInterruptFlags(BOARD_SW3_GPIO, 1U << BOARD_SW3_GPIO_PIN);
    }
    SDK_ISR_EXIT_BARRIER;
}
#else
#if defined(BOARD_SW2_GPIO)
void BOARD_SW2_IRQ_HANDLER(void)
{
    /* Save which SW button was pressed */
    swButton = 2;

    /* Clear external interrupt flag. */
    GPIO_PortClearInterruptFlags(BOARD_SW2_GPIO, 1U << BOARD_SW2_GPIO_PIN);
    SDK_ISR_EXIT_BARRIER;
}
#endif
#if defined(BOARD_SW3_GPIO)
void BOARD_SW3_IRQ_HANDLER(void)
{
    /* Save which SW button was pressed */
    swButton = 3;

    /* Clear external interrupt flag. */
    GPIO_PortClearInterruptFlags(BOARD_SW3_GPIO, 1U << BOARD_SW3_GPIO_PIN);
    SDK_ISR_EXIT_BARRIER;
}
#endif
#endif
/*!
 * @brief Initialize magnetometer and accelerometer sensor
 */
static status_t init_mag_accel(void)
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
        return result;
    }

    /* Get sensor range */
    if (kStatus_Success != ACCEL_READ_REG(&accelHandle, XYZ_DATA_CFG, &sensorRange))
    {
        return kStatus_Fail;
    }
    if (sensorRange == 0x00)
    {
        accelDataScale = 2U;
    }
    else if (sensorRange == 0x01)
    {
        accelDataScale = 4U;
    }
    else if (sensorRange == 0x10)
    {
        accelDataScale = 8U;
    }

    return kStatus_Success;
}

/*******************************************************************************
 * eRPC functions
 ******************************************************************************/
/*!
 * @brief Convert number to analog value through DAC and check it with ADC
 */
void convert_dac_adc(uint32_t numberToConvert, uint32_t *result)
{
#ifdef BOARD_DAC_BASEADDR
    DAC_SetBufferValue(BOARD_DAC_BASEADDR, 0U, numberToConvert);
#endif
    ADC16_SetChannelConfig(DEMO_ADC16_BASEADDR, DEMO_ADC16_CHANNEL_GROUP, &adc16ChannelConfigStruct);

    while (0U == (kADC16_ChannelConversionDoneFlag &
                  ADC16_GetChannelStatusFlags(DEMO_ADC16_BASEADDR, DEMO_ADC16_CHANNEL_GROUP)))
    {
    }

    *result = ADC16_GetChannelConversionValue(DEMO_ADC16_BASEADDR, DEMO_ADC16_CHANNEL_GROUP);
}

/*!
 * @brief Turn on selected LED and turn off other ones
 */
void set_led(uint8_t whichLed)
{
#if defined(BOARD_LED_RED_GPIO_PORT) && defined(BOARD_LED_GREEN_GPIO_PORT)
    switch (whichLed)
    {
        /* Red */
        case 1:
            LED_RED_ON();
            LED_GREEN_OFF();
#if defined(BOARD_LED_BLUE_GPIO_PORT)
            LED_BLUE_OFF();
#endif
            break;

        /* Green */
        case 2:
            LED_RED_OFF();
            LED_GREEN_ON();
#if defined(BOARD_LED_BLUE_GPIO_PORT)
            LED_BLUE_OFF();
#endif
            break;
        /* Blue */
        case 3:
            LED_RED_OFF();
            LED_GREEN_OFF();
#if defined(BOARD_LED_BLUE_GPIO_PORT)
            LED_BLUE_ON();
#endif
            break;
        /* None */
        default:
            LED_RED_OFF();
            LED_GREEN_OFF();
#if defined(BOARD_LED_BLUE_GPIO_PORT)
            LED_BLUE_OFF();
#endif
            break;
    }
#endif /* BOARD_LED_RED_GPIO_PORT && BOARD_LED_GREEN_GPIO_PORT */
}

/*!
 * @brief Read magnetometer and accelerometer sensor value
 */
void read_mag_accel(Vector *results, bool *status)
{
#if defined(BOARD_ACCEL_FXOS)
    fxos_data_t sensorData = {0};
#elif defined(BOARD_ACCEL_MMA)
    mma_data_t sensorData = {0};
#endif
    if (kStatus_Success != ACCELL_READ_SENSOR_DATA(&accelHandle, &sensorData))
    {
        // Failed to read magnetometer and accelerometer data!
        *status = false;
        return;
    }

    /* Get the accelerometer data from the sensor */
    results->A_x = ((int16_t)((uint16_t)((uint16_t)sensorData.accelXMSB << 8) | (uint16_t)sensorData.accelXLSB) / 4U) *
                   accelDataScale;
    results->A_y = ((int16_t)((uint16_t)((uint16_t)sensorData.accelYMSB << 8) | (uint16_t)sensorData.accelYLSB) / 4U) *
                   accelDataScale;
    results->A_z = ((int16_t)((uint16_t)((uint16_t)sensorData.accelZMSB << 8) | (uint16_t)sensorData.accelZLSB) / 4U) *
                   accelDataScale;

/* Get the magnetometer data from the sensor */
#ifdef BOARD_ACCEL_FXOS
    results->M_x = (int16_t)((uint16_t)((uint16_t)sensorData.magXMSB << 8) | (uint16_t)sensorData.magXLSB);
    results->M_y = (int16_t)((uint16_t)((uint16_t)sensorData.magYMSB << 8) | (uint16_t)sensorData.magYLSB);
    results->M_z = (int16_t)((uint16_t)((uint16_t)sensorData.magZMSB << 8) | (uint16_t)sensorData.magZLSB);
#endif

    *status = true;
}

/*******************************************************************************
 * FreeRTOS
 ******************************************************************************/

/*!
 * @brief Server task creates transport arbitrator and creates remote control service
 */
static void server_task(void *pvParameters)
{
    /* Wait until client initializes transport arbitrator */
    while (!transportArbitrator)
    {
        /* Sleep */
        vTaskDelay(100);
    }

    /* Initialize eRPC server with arbitrator transport */
    erpc_server_init(transportArbitrator, message_buffer_factory);

    /* Add service to the server */
    erpc_service_t service = create_remote_control_app_0_service();
    erpc_add_service_to_server(service);

    while (1)
    {
        /* Process message */
        erpc_status_t status = erpc_server_poll();

        /* Sleep */
        vTaskDelay(100);

        /* Handle error status */
        if (kErpcStatus_Success != status)
        {
            /* Error occurred */
            erpc_error_handler(status, 0);

            /* removing the service from the server */
            erpc_remove_service_from_server(service);
            destroy_remote_control_app_0_service(service);

            /* stop erpc server */
            erpc_server_stop();

            /* print error description */
            erpc_server_deinit();

            /* exit program loop */
            break;
        }
    }
}

/*!
 * @brief Client task
 */
static void client_task(void *pvParameters)
{
    /* Initialize CMSIS UART transport */
    erpc_transport_t transport = erpc_transport_cmsis_uart_init((void *)&ERPC_DEMO_UART);

    /* FreeRTOS kernel API is used in UART ISR, so need to set proper IRQ priority. */
    NVIC_SetPriority(ERPC_DEMO_UART_RX_TX_IRQn, ERPC_DEMO_UART_RX_TX_IRQ_PRIO);

    /* MessageBufferFactory initialization */
    message_buffer_factory = erpc_mbf_dynamic_init();

    /* Initialize transport arbitrator */
    transportArbitrator = erpc_arbitrated_client_init(transport, message_buffer_factory);

    /* Register error handler */
    erpc_arbitrated_client_set_error_handler(erpc_error_handler);

    while (1)
    {
        if (swButton)
        {
            /* Call eRPC function for SW button press */
            button_pressed(swButton);

            /* Check if some error occurred in eRPC */
            if (g_erpc_error_occurred)
            {
                /* Exit program loop */
                break;
            }

            /* Clear info about pressed button */
            swButton = 0;
        }

        /* Sleep */
        vTaskDelay(100);
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Initialize board hardware  */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_I2C_ReleaseBus();
    BOARD_I2C_ConfigurePins();
    BOARD_InitDebugConsole();

    /* Initialize GPIO of LED and SW */
    init_pins();

    /* Initialize I2C */
    BOARD_Accel_I2C_Init();

    /* Initialize magnetometer and accelerometer */
    if (kStatus_Success != init_mag_accel())
    {
        /* Failed to initialize magnetometer and accelerometer */
        for (;;)
            ;
    }

    /* Initialize DAC and ADC */
    init_dac_adc();

    /* Create FreeRTOS tasks */
    (void)xTaskCreate(client_task, "CLIENT", 256, NULL, tskIDLE_PRIORITY + 3, &clientTaskHandle);
    (void)xTaskCreate(server_task, "SERVER", 256, NULL, tskIDLE_PRIORITY + 2, &serverTaskHandle);

    /* Start FreeRTOS scheduler */
    vTaskStartScheduler();
    for (;;)
        ;
}
