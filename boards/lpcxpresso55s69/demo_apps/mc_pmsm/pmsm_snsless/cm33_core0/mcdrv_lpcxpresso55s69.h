/*
 * Copyright 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _MCDRV_LPCXPRESSO55S69_H_
#define _MCDRV_LPCXPRESSO55S69_H_

#include "fsl_ctimer.h"
#include "fsl_lpadc.h"
#include "fsl_common.h"
#include "fsl_power.h"
#include "fsl_sctimer.h"
#include "fsl_cmp.h"

#include "mcdrv_adc_lpc.h"
#include "mcdrv_sctimer_lpc.h"
#include "m1_pmsm_appconfig.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Version info */
#define MCRSP_VER "2.0.0" /* motor control package version */

#define CTIMER_CLK_FREQ CLOCK_GetCTimerClkFreq(2U)

/* Application info */
typedef struct _app_ver
{
    char cBoardID[15];
    char cMotorType[4];
    char cAppVer[5];
} app_ver_t;

/* Structure used during clocks and modulo calculations */
typedef struct _clock_setup
{
    uint32_t ui32FastPeripheralClock;
    uint32_t ui32BusClock;
    uint32_t ui32SysPllClock;
    uint16_t ui16M1SpeedLoopFreq;
    uint16_t ui16M1SpeedLoopModulo;
    uint16_t ui16M1PwmFreq;
    uint16_t ui16M1PwmModulo;
    uint16_t ui16M1PwmDeadTime;
} clock_setup_t;

/******************************************************************************
 * Clock & PWM definition for motor 1
 ******************************************************************************/
#define M1_PWM_FREQ (10000)         /* PWM frequency - 10kHz */
#define M1_FOC_FREQ_VS_PWM_FREQ (1) /* FOC calculation is called every n-th PWM reload */
#define M1_SPEED_LOOP_FREQ (1000)   /* Speed loop frequency */

#define M1_FAST_LOOP_TS ((float_t)1.0 / (float_t)(M1_PWM_FREQ / M1_FOC_FREQ_VS_PWM_FREQ))
#define M1_SLOW_LOOP_TS ((float_t)1.0 / (float_t)(M1_SLOW_LOOP_FREQ))
#define M1_TIME_ONESEC_COUNT (M1_PWM_FREQ / M1_FOC_FREQ_VS_PWM_FREQ)

/* Over Current Fault detection */
#define M1_FAULT_NUM (0)

/* Braking resistor macros */
#define M1_BRAKE_SET()
#define M1_BRAKE_CLEAR()

/******************************************************************************
 * ADC measurement definition for motor 1
 ******************************************************************************/
/* Configuration table of ADC channels according to the input pin signals:
 * Valid for lpc55s69 together with FRDM-MC-LVPMSM
 *
 * Motor 1
 * Quantity     | Module A (ADC1)       | Module B (ADC2)
 * --------------------------------------------------------------------------
 * M1_I_A       | ADC1_CH0              | ADC2_CH0
 * M1_I_B       | ADC1_CH5              | ADC2_CH5
 * M1_I_C       | ADC1_CH6              | ADC2_CH6
 * M1_U_DCB     | ADC1_CH7              | ADC2_CH7
 *
 */

/* Phase current A assigned to ADC1 and ADC2 */
#define M1_ADC1_PH_A (0)
#define M1_ADC2_PH_A (0)
/* Phase current A assigned to ADC1 and ADC2 */
#define M1_ADC1_PH_B (5)
#define M1_ADC2_PH_B (5)
/* Phase current A assigned to ADC1 and ADC2 */
#define M1_ADC1_PH_C (6)
#define M1_ADC2_PH_C (6)
/* Phase current A assigned to ADC1 and ADC2 */
#define M1_ADC1_UDCB (7)
#define M1_ADC2_UDCB (7)

/* offset measurement filter window */
#define ADC_OFFSET_WINDOW (3)
/******************************************************************************
 * MC driver macro definition and check - do not change this part
 ******************************************************************************/
/******************************************************************************
 * Define common ADC control functions for motor 1
 ******************************************************************************/
#define M1_MCDRV_ADC_PERIPH_INIT() (InitADC())
#define M1_MCDRV_ADC_GET(par) MCDRV_CurrAndVoltDcBusGet(par);

#define M1_MCDRV_CURR_3PH_CHAN_ASSIGN(par)
#define M1_MCDRV_CURR_3PH_CALIB_INIT(par) (MCDRV_Curr3Ph2ShCalibInit(par))
#define M1_MCDRV_CURR_3PH_CALIB(par) (MCDRV_Curr3Ph2ShCalib(par))
#define M1_MCDRV_CURR_3PH_CALIB_SET(par) (MCDRV_Curr3Ph2ShCalibSet(par))

/******************************************************************************
 * Define CMP for overcurrent detection
 ******************************************************************************/
#define M1_MCDRV_CMP_INIT() InitCMP()

/******************************************************************************
 * Define motor 1 slow control loop timer
 ******************************************************************************/
#define M1_MCDRV_TMR_SLOWLOOP_INIT() InitCTMR2()

/******************************************************************************
 * Define 3-ph PWM control functions for motor 1
 ******************************************************************************/
#define M1_MCDRV_PWM_PERIPH_INIT() (M1_InitPWM())
#define M1_MCDRV_PWM3PH_SET(par) (MCDRV_scTmrPwm3PhSet(par))
#define M1_MCDRV_PWM3PH_EN(par) (MCDRV_scTmrPwm3PhOutEn(par))
#define M1_MCDRV_PWM3PH_DIS(par) (MCDRV_scTmrPwm3PhOutDis(par))
#define M1_MCDRV_PWM3PH_FLT_GET(par) (MCDRV_scTmrPwm3PhFltGet(par))

/******************************************************************************
 * Define position and speed sensor - quadrature encoder for motor 1
 ******************************************************************************/
#define M1_MCDRV_QD_PERIPH_INIT() M1_InitQD()
#define M1_MCDRV_QD_GET(par) (MCDRV_QdEncGet(par))
#define M1_MCDRV_QD_SET_DIRECTION(par) (MCDRV_QdEncSetDirection(par))
#define M1_MCDRV_QD_CLEAR(par) (MCDRV_QdEncClear(par))

/******************************************************************************
 * Global variable definitions
 ******************************************************************************/
extern mcdrv_adc_t g_sM1AdcSensor;
extern mcdrv_sctimer_pwm_t g_sM1Pwm3ph;
extern clock_setup_t g_sClockSetup;

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

void MCDRV_Init_M1(void);
void InitClock(void);
void InitCTMR2(void);

void InitADC(void);
void M1_InitPWM(void);
void InitCMP(void);

#ifdef __cplusplus
}
#endif

#endif /* _MCDRV_LPCXPRESSO55S69_H_  */
