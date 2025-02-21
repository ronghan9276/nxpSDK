/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "board.h"
#include "math.h"
#include "fsl_fxos.h"
#include "fsl_i2c.h"
#include "fsl_ftm.h"

#include "fsl_common.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* The Flextimer instance/channel used for board */
#define BOARD_FTM_BASEADDR FTM0
#define BOARD_FIRST_TIMER_CHANNEL 0U
#define BOARD_SECOND_TIMER_CHANNEL 1U
#define BOARD_FIRST_CHANNEL_INT kFTM_Chnl0InterruptEnable
#define BOARD_SECOND_CHANNEL_INT kFTM_Chnl1InterruptEnable
#define BOARD_FTM_IRQ_HANDLER_FUNC FTM0_IRQHandler
#define BOARD_FTM_IRQ_ID FTM0_IRQn
#define BOARD_FTM_PRESCALE_DIVIDER kFTM_Prescale_Divide_128
/* Get source clock for TPM driver */
#define BOARD_TIMER_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)
/* I2C source clock */
#define I2C_BAUDRATE 100000U

#define I2C_RELEASE_SDA_PORT PORTE
#define I2C_RELEASE_SCL_PORT PORTE
#define I2C_RELEASE_SDA_GPIO GPIOE
#define I2C_RELEASE_SDA_PIN 25U
#define I2C_RELEASE_SCL_GPIO GPIOE
#define I2C_RELEASE_SCL_PIN 24U
#define I2C_RELEASE_BUS_COUNT 100U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_I2C_ReleaseBus(void);
static void Board_UpdatePwm(uint16_t x, uint16_t y);
/*******************************************************************************
 * Variables
 ******************************************************************************/
i2c_master_handle_t g_MasterHandle;
volatile int16_t g_xAngle = 0;
volatile int16_t g_yAngle = 0;
/* FXOS device address */
const uint8_t g_accel_address[] = {0x1CU, 0x1DU, 0x1EU, 0x1FU};

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
    uint8_t i = 0;
    gpio_pin_config_t pin_config;
    port_pin_config_t i2c_pin_config = {0};

    /* Config pin mux as gpio */
    i2c_pin_config.pullSelect = kPORT_PullUp;
    i2c_pin_config.mux        = kPORT_MuxAsGpio;

    pin_config.pinDirection = kGPIO_DigitalOutput;
    pin_config.outputLogic  = 1U;
    CLOCK_EnableClock(kCLOCK_PortE);
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
/* Initialize timer module */
static void Timer_Init(void)
{
    ftm_config_t ftmInfo;
    ftm_chnl_pwm_signal_param_t ftmParam[2];

    /* Configure ftm params with frequency 24kHZ */
    ftmParam[0].chnlNumber            = (ftm_chnl_t)BOARD_FIRST_TIMER_CHANNEL;
    ftmParam[0].level                 = kFTM_LowTrue;
    ftmParam[0].dutyCyclePercent      = 0U;
    ftmParam[0].firstEdgeDelayPercent = 0U;

    ftmParam[1].chnlNumber            = (ftm_chnl_t)BOARD_SECOND_TIMER_CHANNEL;
    ftmParam[1].level                 = kFTM_LowTrue;
    ftmParam[1].dutyCyclePercent      = 0U;
    ftmParam[1].firstEdgeDelayPercent = 0U;

    /*
     * ftmInfo.prescale = kFTM_Prescale_Divide_1;
     * ftmInfo.bdmMode = kFTM_BdmMode_0;
     * ftmInfo.pwmSyncMode = kFTM_SoftwareTrigger;
     * ftmInfo.reloadPoints = 0;
     * ftmInfo.faultMode = kFTM_Fault_Disable;
     * ftmInfo.faultFilterValue = 0;
     * ftmInfo.deadTimePrescale = kFTM_Deadtime_Prescale_1;
     * ftmInfo.deadTimeValue = 0;
     * ftmInfo.extTriggers = 0;
     * ftmInfo.chnlInitState = 0;
     * ftmInfo.chnlPolarity = 0;
     * ftmInfo.useGlobalTimeBase = false;
     */
    FTM_GetDefaultConfig(&ftmInfo);

    /* Initialize FTM module */
    FTM_Init(BOARD_FTM_BASEADDR, &ftmInfo);

    FTM_EnableInterrupts(BOARD_FTM_BASEADDR,
                         BOARD_FIRST_CHANNEL_INT | BOARD_SECOND_CHANNEL_INT | kFTM_TimeOverflowInterruptEnable);
    NVIC_EnableIRQ(BOARD_FTM_IRQ_ID);
    FTM_SetupPwm(BOARD_FTM_BASEADDR, ftmParam, 2U, kFTM_EdgeAlignedPwm, 24000U, BOARD_TIMER_SOURCE_CLOCK);
    FTM_StartTimer(BOARD_FTM_BASEADDR, kFTM_SystemClock);
}

void BOARD_FTM_IRQ_HANDLER_FUNC(void)
{
    uint32_t status = FTM_GetStatusFlags(BOARD_FTM_BASEADDR);

    if (status & kFTM_TimeOverflowFlag)
    {
        Board_UpdatePwm(g_xAngle, g_yAngle);
        if (g_xAngle)
        {
            LED_GREEN_ON();
        }
        else
        {
            LED_GREEN_OFF();
        }
        if (g_yAngle)
        {
            LED_RED_ON();
        }
        else
        {
            LED_RED_OFF();
        }
        FTM_ClearStatusFlags(BOARD_FTM_BASEADDR, kFTM_TimeOverflowFlag);
    }
    if (status & kFTM_Chnl0Flag)
    {
        LED_GREEN_OFF();
        FTM_ClearStatusFlags(BOARD_FTM_BASEADDR, kFTM_Chnl0Flag);
    }
    if (status & kFTM_Chnl1Flag)
    {
        LED_RED_OFF();
        FTM_ClearStatusFlags(BOARD_FTM_BASEADDR, kFTM_Chnl1Flag);
    }
    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
    exception return operation might vector to incorrect interrupt */
    __DSB();
}

/* Update the duty cycle of an active pwm signal */
static void Board_UpdatePwm(uint16_t x, uint16_t y)
{
    /* Start PWM mode with updated duty cycle */
    FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR, (ftm_chnl_t)BOARD_FIRST_TIMER_CHANNEL, kFTM_EdgeAlignedPwm, x);
    FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR, (ftm_chnl_t)BOARD_SECOND_TIMER_CHANNEL, kFTM_EdgeAlignedPwm, y);
    /* Software trigger to update registers */
    FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR, true);
}

int main(void)
{
    fxos_handle_t fxosHandle = {0};
    fxos_data_t sensorData   = {0};
    fxos_config_t config     = {0};
    uint8_t sensorRange      = 0;
    uint8_t dataScale        = 0;
    int16_t xData            = 0;
    int16_t yData            = 0;
    uint8_t i                = 0;
    uint8_t array_addr_size  = 0;
    status_t result          = kStatus_Fail;

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_I2C_ReleaseBus();
    BOARD_I2C_ConfigurePins();
    BOARD_InitDebugConsole();

    /* I2C initialize */
    BOARD_Accel_I2C_Init();

    /* Configure the I2C function */
    config.I2C_SendFunc    = BOARD_Accel_I2C_Send;
    config.I2C_ReceiveFunc = BOARD_Accel_I2C_Receive;

    array_addr_size = sizeof(g_accel_address) / sizeof(g_accel_address[0]);
    for (i = 0; i < array_addr_size; i++)
    {
        config.slaveAddress = g_accel_address[i];
        /* Initialize accelerometer sensor */
        result = FXOS_Init(&fxosHandle, &config);
        if (result == kStatus_Success)
        {
            break;
        }
    }

    if (result != kStatus_Success)
    {
        PRINTF("\r\nSensor device initialize failed!\r\n");
        return -1;
    }

    /* Get sensor range */
    if (FXOS_ReadReg(&fxosHandle, XYZ_DATA_CFG_REG, &sensorRange, 1) != kStatus_Success)
    {
        return -1;
    }
    if (sensorRange == 0x00)
    {
        dataScale = 2U;
    }
    else if (sensorRange == 0x01)
    {
        dataScale = 4U;
    }
    else if (sensorRange == 0x10)
    {
        dataScale = 8U;
    }
    else
    {
    }

    LED_GREEN_INIT(0);
    LED_RED_INIT(0);

    /* Init timer */
    Timer_Init();

    /* Print a note to terminal */
    PRINTF("\r\nWelcome to the BUBBLE example\r\n");
    PRINTF("\r\nYou will see the change of angle data and LED brightness when change the angles of board\r\n");

    /* Main loop. Get sensor data and update duty cycle */
    while (1)
    {
        /* Get new accelerometer data. */
        if (FXOS_ReadSensorData(&fxosHandle, &sensorData) != kStatus_Success)
        {
            return -1;
        }

        /* Get the X and Y data from the sensor data structure in 14 bit left format data*/
        xData = (int16_t)((uint16_t)((uint16_t)sensorData.accelXMSB << 8) | (uint16_t)sensorData.accelXLSB) / 4U;
        yData = (int16_t)((uint16_t)((uint16_t)sensorData.accelYMSB << 8) | (uint16_t)sensorData.accelYLSB) / 4U;

        /* Convert raw data to angle (normalize to 0-90 degrees). No negative angles. */
        g_xAngle = (int16_t)floor((double)xData * (double)dataScale * 90 / 8192);
        if (g_xAngle < 0)
        {
            g_xAngle *= -1;
        }
        g_yAngle = (int16_t)floor((double)yData * (double)dataScale * 90 / 8192);
        if (g_yAngle < 0)
        {
            g_yAngle *= -1;
        }

        /* Print out the angle. */
        PRINTF("x= %2d y = %2d\r\n", g_xAngle, g_yAngle);
    }
}
