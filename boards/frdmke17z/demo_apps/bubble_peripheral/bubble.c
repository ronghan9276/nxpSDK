/*
 * Copyright 2018-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "math.h"
#include "fsl_fxos.h"
#include "pin_mux.h"
#include "peripherals.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Accelerometer Reset PIN */
#define BOARD_ACCEL_RESET_GPIO GPIOB
#define BOARD_ACCEL_RESET_PIN  9U

/* The Flextimer instance/channel used for board */
#define BOARD_FTM_BASEADDR         FTM2
#define BOARD_FIRST_TIMER_CHANNEL  0U
#define BOARD_SECOND_TIMER_CHANNEL 1U
#define BOARD_FIRST_CHANNEL_INT    kFTM_Chnl0InterruptEnable
#define BOARD_SECOND_CHANNEL_INT   kFTM_Chnl1InterruptEnable
#define BOARD_FTM_IRQ_HANDLER_FUNC FTM2_IRQHandler

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_ACCEL_Reset(void);
extern void FXOS_master_callback(LPI2C_Type *base, lpi2c_master_handle_t *handle, status_t status, void *userData);
static void Board_UpdatePwm(uint16_t x, uint16_t y);
/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile int16_t xAngle = 0;
volatile int16_t yAngle = 0;
/* FXOS device address */
const uint8_t g_accel_address[] = {0x1CU, 0x1DU, 0x1EU, 0x1FU};

/*******************************************************************************
 * Code
 ******************************************************************************/

void BOARD_ACCEL_Reset(void)
{
    uint32_t i;

    /* Reset sensor by reset pin*/
    BOARD_Init_ACCEL_Reset();
    /* Delay to ensure reliable sensor reset */
    for (i = 0; i < SystemCoreClock / 1000U; i++)
    {
        __NOP();
    }
    GPIO_PinWrite(BOARD_ACCEL_RESET_GPIO, BOARD_ACCEL_RESET_PIN, 0);

    /* Delay to wait sensor stable after reset */
    for (i = 0; i < SystemCoreClock / 1000U; i++)
    {
        __NOP();
    }
}
/* Update the duty cycle of an active pwm signal */
static void Board_UpdatePwm(uint16_t x, uint16_t y)
{
    /* Start PWM mode with updated duty cycle */
    FTM_UpdatePwmDutycycle(BOARD_TIMER_PERIPHERAL, kFTM_Chnl_0, kFTM_EdgeAlignedPwm, x);
    FTM_UpdatePwmDutycycle(BOARD_TIMER_PERIPHERAL, kFTM_Chnl_1, kFTM_EdgeAlignedPwm, y);
    /* Software trigger to update registers */
    FTM_SetSoftwareTrigger(BOARD_TIMER_PERIPHERAL, true);
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
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_ACCEL_Reset();
    BOARD_I2C_ConfigurePins();
    BOARD_InitDebugConsole();
    /* Select the clock source for the LPI2C module as fast internal RC oscillator */
    CLOCK_SetIpSrc(kCLOCK_Lpi2c0, kCLOCK_IpSrcFircAsync);
    /* Select the clock source for the FTM counter as fast internal RC oscillator */
    CLOCK_SetIpSrc(kCLOCK_Ftm2, kCLOCK_IpSrcFircAsync);
    BOARD_InitPeripherals();

    /* Configure the I2C function */
    config.I2C_SendFunc    = BOARD_Accel_I2C_Send;
    config.I2C_ReceiveFunc = BOARD_Accel_I2C_Receive;

    /* Initialize sensor devices */
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
    /* Start timer */
    FTM_StartTimer(BOARD_TIMER_PERIPHERAL, kFTM_SystemClock);

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
        xAngle = (int16_t)floor((double)xData * (double)dataScale * 90 / 8192);
        if (xAngle < 0)
        {
            xAngle *= -1;
        }
        yAngle = (int16_t)floor((double)yData * (double)dataScale * 90 / 8192);
        if (yAngle < 0)
        {
            yAngle *= -1;
        }

        /* Update the duty cycle of PWM */
        Board_UpdatePwm(xAngle, yAngle);

        /* Print out the angle data. */
        PRINTF("x= %2d y = %2d\r\n", xAngle, yAngle);
    }
}
