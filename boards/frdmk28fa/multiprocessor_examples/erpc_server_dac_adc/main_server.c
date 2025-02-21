/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_adc16.h"
#include "fsl_gpio.h"
#include "erpc_server_setup.h"
#include "erpc_transport_setup.h"
#include "erpc_dac_adc_server.h"
#include "erpc_error_handler.h"
#include "erpc_dac_adc.h"
#include "string.h" //strcpy
#ifdef BOARD_DAC_BASEADDR
#include "fsl_dac.h"
#endif

#include "fsl_port.h"
#include "fsl_common.h"
#include "fsl_lpuart_cmsis.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_ADC16_BASEADDR      ADC0
#define DEMO_ADC16_CHANNEL_GROUP 0U
#define DEMO_ADC16_USER_CHANNEL  10U /* ADC0_SE10 */

#define DEMO_ADC16_IRQn             ADC0_IRQn
#define DEMO_ADC16_IRQ_HANDLER_FUNC ADC0_IRQHandler

#define BOARD_LED_GPIO     BOARD_LED_GREEN_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_GREEN_GPIO_PIN

/* I2C source clock */
#define I2C_BAUDRATE   100000U
#define ACCEL_I2C_ADDR 1CU

#define I2C_RELEASE_SDA_PORT  PORTC
#define I2C_RELEASE_SCL_PORT  PORTC
#define I2C_RELEASE_SDA_GPIO  GPIOC
#define I2C_RELEASE_SDA_PIN   28U
#define I2C_RELEASE_SCL_GPIO  GPIOC
#define I2C_RELEASE_SCL_PIN   29U
#define I2C_RELEASE_BUS_COUNT 100U

#define ERPC_DEMO_UART Driver_USART0

#define VREF_BRD 3.300
#define SE_12BIT 4096.0

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_I2C_ReleaseBus(void);
int32_t init_mag_accel(void);
void Sensor_ReadData(int16_t *Ax, int16_t *Ay, int16_t *Az, int16_t *Mx, int16_t *My, int16_t *Mz);
void Delay(uint32_t ticks);

/*******************************************************************************
 * Variables
 ******************************************************************************/
adc16_channel_config_t g_adc16ChannelConfigStruct;

gpio_pin_config_t led_config = {
    kGPIO_DigitalOutput,
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
    CLOCK_EnableClock(kCLOCK_PortA);

    uint8_t i = 0;
    gpio_pin_config_t pin_config;
    port_pin_config_t i2c_pin_config = {0};

    /* Config pin mux as gpio */
    i2c_pin_config.pullSelect = kPORT_PullUp;
    i2c_pin_config.mux        = kPORT_MuxAsGpio;

    pin_config.pinDirection = kGPIO_DigitalOutput;
    pin_config.outputLogic  = 1U;
    CLOCK_EnableClock(kCLOCK_PortC);
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

uint32_t LPUART0_GetFreq(void)
{
    return CLOCK_GetOsc0ErClkFreq();
}

uint32_t LPUART1_GetFreq(void)
{
    return CLOCK_GetOsc0ErClkFreq();
}

uint32_t LPUART2_GetFreq(void)
{
    return CLOCK_GetOsc0ErClkFreq();
}

uint32_t LPUART3_GetFreq(void)
{
    return CLOCK_GetOsc0ErClkFreq();
}

uint32_t LPUART4_GetFreq(void)
{
    return CLOCK_GetOsc0ErClkFreq();
}
void board_get_name(char *name)
{
    strcpy(name, BOARD_NAME);
}

void convert_dac_adc(uint32_t numberToConvert, uint32_t *result)
{
#ifdef BOARD_DAC_BASEADDR
    DAC_SetBufferValue(BOARD_DAC_BASEADDR, 0U, numberToConvert);
#endif
    ADC16_SetChannelConfig(DEMO_ADC16_BASEADDR, DEMO_ADC16_CHANNEL_GROUP, &g_adc16ChannelConfigStruct);

    while (0U == (kADC16_ChannelConversionDoneFlag &
                  ADC16_GetChannelStatusFlags(DEMO_ADC16_BASEADDR, DEMO_ADC16_CHANNEL_GROUP)))
    {
    }

    *result = ADC16_GetChannelConversionValue(DEMO_ADC16_BASEADDR, DEMO_ADC16_CHANNEL_GROUP);
}

void adc_get_config(AdcConfig *config)
{
    config->vref        = VREF_BRD;
    config->atomicSteps = SE_12BIT;
}

void set_led(uint8_t whichLed)
{
#if defined(BOARD_LED_BLUE_GPIO_PORT) && defined(BOARD_LED_RED_GPIO_PORT) && defined(BOARD_LED_GREEN_GPIO_PORT)
    switch (whichLed)
    {
        case 1:
            LED_RED_ON();
            LED_GREEN_OFF();
            LED_BLUE_OFF();
            break;
        case 2:
            LED_RED_OFF();
            LED_BLUE_OFF();
            LED_GREEN_ON();
            break;
        case 3:
            LED_RED_OFF();
            LED_GREEN_OFF();
            LED_BLUE_ON();
            break;
        default:
            LED_BLUE_ON();
            LED_RED_ON();
            LED_GREEN_ON();
            break;
    }
#else
    switch (whichLed)
    {
        case 1:
            LED_RED_ON();
            LED_GREEN_OFF();
            break;
        case 2:
            LED_GREEN_ON();
            LED_RED_OFF();
            break;
        case 3:
            LED_RED_OFF();
            LED_GREEN_OFF();
            break;
        default:
            LED_RED_ON();
            LED_GREEN_ON();
            break;
    }
#endif
}

void DAC_ADC_Init(void)
{
    adc16_config_t adc16ConfigStruct;
#ifdef BOARD_DAC_BASEADDR
    dac_config_t dacConfigStruct;
    /* Configure the DAC. */
    /*
     * dacConfigStruct.referenceVoltageSource = kDAC_ReferenceVoltageSourceVref2;
     * dacConfigStruct.enablLowPowerMode = false;
     */
    DAC_GetDefaultConfig(&dacConfigStruct);
    DAC_Init(BOARD_DAC_BASEADDR, &dacConfigStruct);
    DAC_Enable(BOARD_DAC_BASEADDR, true); /* Enable output. */
#endif
    /* Configure the ADC16. */
    /*
     * adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceVref;
     * adc16ConfigStruct.clockSource = kADC16_ClockSourceAsynchronousClock;
     * adc16ConfigStruct.enableAsynchronousClock = true;
     * adc16ConfigStruct.clockDivider = kADC16_ClockDivider8;
     * adc16ConfigStruct.resolution = kADC16_ResolutionSE12Bit;
     * adc16ConfigStruct.longSampleMode = kADC16_LongSampleDisabled;
     * adc16ConfigStruct.enableHighSpeed = false;
     * adc16ConfigStruct.enableLowPower = false;
     * adc16ConfigStruct.enableContinuousConversion = false;
     */
    ADC16_GetDefaultConfig(&adc16ConfigStruct);
    ADC16_Init(DEMO_ADC16_BASEADDR, &adc16ConfigStruct);

    /* Make sure the software trigger is used. */
    ADC16_EnableHardwareTrigger(DEMO_ADC16_BASEADDR, false);
#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    if (kStatus_Success == ADC16_DoAutoCalibration(DEMO_ADC16_BASEADDR))
    {
        /* ADC16_DoAutoCalibration() Done. */
    }
    else
    {
        /* ADC16_DoAutoCalibration() Failed.*/
    }
#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */

    /* Prepare ADC channel setting */
    g_adc16ChannelConfigStruct.channelNumber                        = DEMO_ADC16_USER_CHANNEL;
    g_adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;

#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    g_adc16ChannelConfigStruct.enableDifferentialConversion = false;
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */
}

void read_senzor_mag_accel(Vector *results)
{
    Sensor_ReadData(&results->A_x, &results->A_y, &results->A_z, &results->M_x, &results->M_y, &results->M_z);
}

void erpc_init(void)
{
    erpc_transport_t transport = {0};

    transport = erpc_transport_cmsis_uart_init((void *)&ERPC_DEMO_UART);

    /* MessageBufferFactory initialization */
    erpc_mbf_t message_buffer_factory;
    message_buffer_factory = erpc_mbf_dynamic_init();

    erpc_server_init(transport, message_buffer_factory);
}

void led_init()
{
#if defined(BOARD_LED_BLUE_GPIO_PORT)
    GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, &led_config);
    LED_BLUE_OFF();
#endif
#if defined(BOARD_LED_RED_GPIO_PORT)
    GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, &led_config);
    LED_RED_OFF();
#endif
#if defined(BOARD_LED_GREEN_GPIO_PORT)
    GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, &led_config);
    LED_GREEN_OFF();
#endif
}

/*!
 * @brief Main function
 */
int main(void)
{
    /*board init*/
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_I2C_ReleaseBus();
    BOARD_I2C_ConfigurePins();
    BOARD_InitDebugConsole();
    CLOCK_SetLpuartClock(2U);

    /*i2c inic*/
    BOARD_Accel_I2C_Init();

    /* Initialize magnetometer and accelerometer */
    if (0 != init_mag_accel())
    {
        /* Failed to initialize magnetometer and accelerometer */
        for (;;)
            ;
    }

    /* DAC and ADC init */
    DAC_ADC_Init();

    /* GPIO LED init */
    led_init();

    /* eRPC server side initialization */
    erpc_init();

    /* adding the service to the server */
    erpc_service_t service = create_dac_adc_service();
    erpc_add_service_to_server(service);

    while (1)
    {
        /* process message */
        erpc_status_t status = erpc_server_run();

        /* handle error status */
        if (status != kErpcStatus_Success)
        {
            /* print error description */
            erpc_error_handler(status, 0);

            /* removing the service from the server */
            erpc_remove_service_from_server(service);
            destroy_dac_adc_service();

            /* stop erpc server */
            erpc_server_stop();

            /* print error description */
            erpc_server_deinit();

            /* exit program loop */
            break;
        }
    }
    while (1)
    {
    }
}
