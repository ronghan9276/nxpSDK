/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _MCDRV_TWR_KV46F150M_H_
#define _MCDRV_TWR_KV46F150M_H_

#include "fsl_device_registers.h"
#include "mcdrv_pwm3ph_pwma.h"
#include "mcdrv_mosfet_predrv_spi.h"
#include "mcdrv_adc_adc12.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Structure used during clocks and modulo calculations */
typedef struct _clock_setup
{
    uint32_t ui32FastPeripheralClock;
    uint32_t ui32BusClock;
    uint16_t ui16PwmFreq;
    uint16_t ui16PwmDeadTime;
    uint16_t ui16PwmModulo;
    uint16_t ui16SpeedLoopFreq;
    uint16_t ui16SpeedLoopModulo;
} clock_setup_t;

/* define motor 1 ADC periphery (ADC12) */
#define M1_MCDRV_ADC (MCDRV_ADC12)

/* define motor 1 3-ph PWM periphery */
#define M1_MCDRV_PWM3PH (MCDRV_PWMA)

/* define motor 1 driver */
#define M1_MCDRV_SPI_DRV3PH (MCDRV_SPI_DRV)

/* define motor 1 slow control loop timer */
#define M1_MCDRV_TMR_SLOWLOOP (MCDRV_FTM0)

/*******************************************************************************
 * FreeMASTER communication constants
 ******************************************************************************/
/*! @brief The UART to use for FreeMASTER communication */
#define BOARD_FMSTR_UART   (1) 
#define BOARD_FMSTR_LPUART (2) 
#define BOARD_FMSTR_UART_PORT UART1
#define BOARD_FMSTR_UART_BAUDRATE 115200
#define BOARD_FMSTR_UART_TYPE BOARD_FMSTR_UART 
#define BOARD_FMSTR_USE_TSA (1)

/******************************************************************************
 * Clock & PWM definition
 ******************************************************************************/
/* PWM frequency */
#define M1_PWM_FREQ (10000)
/* FOC calculation is called every n-th PWM reload */
#define M1_FOC_FREQ_VS_PWM_FREQ (1)
/* Speed loop frequency */
#define M1_SPEED_LOOP_FREQ (1000)
/* Output PWM deadtime value in nanoseconds */
#define M1_PWM_DEADTIME (500)

/* Assignment of PWM Submodules to motor phases
 * 0 - PWM Submodule 0
 * 1 - PWM Submodule 1
 * 2 - PWM Submodule 2
 * 3 - PWM Submodule 3
 */
#define M1_PWM_PAIR_PHA (0)
#define M1_PWM_PAIR_PHB (1)
#define M1_PWM_PAIR_PHC (2)

/* Over-current Fault detection */
#define M1_FAULT_NUM (0)

/******************************************************************************
 * ADC measurement definition
 ******************************************************************************/
/* Configuration table of ADC channels according to the input pin signals:
 * Valid for Kinetis KV46 Tower board (TWR-KV46F256) together with TWR-MC-LV3PH
 *
 * Proper ADC channel assignment needs to follow these rules:
 *   - at least one phase current must be assigned to both ADC modules
 *   - two other phase current channels must be assigned to different ADC modules
 *   - Udcb and auxiliary channels must be assigned to different ADC modules
 *
 *   Quantity         | ADC Module A  | ADC Module B
 *   --------------------------------------------------------------------------
 *   I_A              | ADCA_CH3      | ADCB_CH1
 *   I_B              | --------      | ADCB_CH3
 *   I_C              | ADCA_CH1      | --------
 *   U_DCB            | --------      | ADCB_CH0
 */
/* Phase current A assigned to ADC0 only */
#define M1_ADC0_PH_A (3)
#define M1_ADC1_PH_A (1)
/* Phase current A assigned to ADC1 only */
#define M1_ADC0_PH_B (MCDRV_CHAN_OFF)
#define M1_ADC1_PH_B (3)
/* Phase current A assigned to ADC0 and ADC1 */
#define M1_ADC0_PH_C (1)
#define M1_ADC1_PH_C (MCDRV_CHAN_OFF)
/* DC-bus voltage is assigned to ADC0 only */
#define M1_ADC0_UDCB (MCDRV_CHAN_OFF)
#define M1_ADC1_UDCB (0)
/* Aux channel is assigned to ADC1 only */
#define M1_ADC0_AUX (30)
#define M1_ADC1_AUX (MCDRV_CHAN_OFF)

/* offset measurement filter window */     
#define ADC_OFFSET_WINDOW (3)
/******************************************************************************
 * MC driver macro definition and check - do not change this part
 ******************************************************************************/
/******************************************************************************
 * Define motor 1 ADC control functions
 ******************************************************************************/
#ifdef M1_MCDRV_ADC
#if (M1_MCDRV_ADC == MCDRV_ADC12)
#define M1_MCDRV_ADC_PERIPH_INIT() (InitADC12())
#define M1_MCDRV_ADC_GET(par) \
    MCDRV_Curr3Ph2ShGet(par); \
    MCDRV_VoltDcBusGet(par);  \
    MCDRV_AuxValGet(par);
#define M1_MCDRV_CURR_3PH_CHAN_ASSIGN(par) (MCDRV_Curr3Ph2ShChanAssign(par))
#define M1_MCDRV_CURR_3PH_CALIB_INIT(par) (MCDRV_Curr3Ph2ShCalibInit(par))
#define M1_MCDRV_CURR_3PH_CALIB(par) (MCDRV_Curr3Ph2ShCalib(par))
#define M1_MCDRV_CURR_3PH_CALIB_SET(par) (MCDRV_Curr3Ph2ShCalibSet(par))
#else
#error MCDRV: Unsupported ADC periphery!
#endif
#else
#error MCDRV: ADC periphery was not specified!
#endif

/******************************************************************************
 * Define motor 1 3-ph PWM control functions
 ******************************************************************************/
#ifdef M1_MCDRV_PWM3PH
#if (M1_MCDRV_PWM3PH == MCDRV_PWMA)
#define M1_MCDRV_PWM_PERIPH_INIT() (InitPWMA())
#define M1_MCDRV_PWM3PH_SET(par) (MCDRV_eFlexPwm3PhSet(par))
#define M1_MCDRV_PWM3PH_EN(par) (MCDRV_eFlexPwm3PhOutEn(par))
#define M1_MCDRV_PWM3PH_DIS(par) (MCDRV_eFlexPwm3PhOutDis(par))
#define M1_MCDRV_PWM3PH_FLT_GET(par) (MCDRV_eFlexPwm3PhFltGet(par))
#else
#error MCDRV: Unsupported PWM periphery!
#endif
#else
#error MCDRV: PWM periphery was not specified!
#endif

/******************************************************************************
 * Define motor 1 slow control loop timer
 ******************************************************************************/
#ifdef M1_MCDRV_TMR_SLOWLOOP
#if (M1_MCDRV_TMR_SLOWLOOP == MCDRV_FTM2)
#define M1_MCDRV_TMR_SLOWLOOP_INIT() InitFTM0()
#else
#error MCDRV: Unsupported Timer periphery!
#endif
#else
#error MCDRV: Timer periphery was not specified!
#endif

/******************************************************************************
* Define motor 1 3-ph driver control functions
******************************************************************************/
#ifdef M1_MCDRV_SPI_DRV3PH
#if (M1_MCDRV_SPI_DRV3PH == MCDRV_SPI_DRV)
#define M1_MCDRV_DRV3PH_INIT() InitSPI()
#define M1_MCDRV_DRV3PH_RD_OC(par) (MCDRV_Driver3PhReadOc(par))
#define M1_MCDRV_DRV3PH_RD_INT(par) (MCDRV_Driver3PhReadInt(par))
#define M1_MCDRV_DRV3PH_CLR_FLG(par) (MCDRV_Driver3PhClearFlags(par))
#define M1_MCDRV_DRV3PH_RD_S0(par) (MCDRV_Driver3PhGetSr0(par))
#define M1_MCDRV_DRV3PH_RD_S1(par) (MCDRV_Driver3PhGetSr1(par))
#define M1_MCDRV_DRV3PH_RD_S2(par) (MCDRV_Driver3PhGetSr2(par))
#define M1_MCDRV_DRV3PH_RD_S3(par) (MCDRV_Driver3PhGetSr3(par))
#else
#error MCDRV: Unsupported SPI periphery!
#endif
#else
#define M1_MCDRV_DRV3PH_T void
#define M1_MCDRV_DRV3PH_RD_OC(par)
#define M1_MCDRV_DRV3PH_RD_INT(par)
#define M1_MCDRV_DRV3PH_CLR_FLG(par)
#define M1_MCDRV_DRV3PH_RD_S0(par)
#define M1_MCDRV_DRV3PH_RD_S1(par)
#define M1_MCDRV_DRV3PH_RD_S2(par)
#define M1_MCDRV_DRV3PH_RD_S3(par)
#endif

/* Check whether ADC channel assignment is correct */
#if !(((M1_ADC0_PH_A != MCDRV_CHAN_OFF) && (M1_ADC1_PH_A != MCDRV_CHAN_OFF)) || \
      ((M1_ADC0_PH_B != MCDRV_CHAN_OFF) && (M1_ADC1_PH_B != MCDRV_CHAN_OFF)) || \
      ((M1_ADC0_PH_C != MCDRV_CHAN_OFF) && (M1_ADC1_PH_C != MCDRV_CHAN_OFF)))
#error MCDRV: None of phase current is assigned to both ADCs!
#endif

#if (M1_ADC0_UDCB != MCDRV_CHAN_OFF) && (M1_ADC0_AUX != MCDRV_CHAN_OFF) || \
    (M1_ADC1_UDCB != MCDRV_CHAN_OFF) && (M1_ADC1_AUX != MCDRV_CHAN_OFF)
#error MCDRV: The DC-bus voltage and Aux cannot be measured at the same ADC!
#endif

/******************************************************************************
 * global variable definitions
 ******************************************************************************/
extern mcdrv_pwm3ph_pwma_t g_sM1Pwm3ph;
extern mcdrv_adc12_t g_sM1AdcSensor;
extern mcdrv_spi_drv3ph_t g_sM1Driver3ph;
extern clock_setup_t g_sClockSetup;

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

void InitClock(void);
void MCDRV_Init_M1(void);
void InitPWMA(void);
void InitSPI(void);
void InitFTM0(void);
void InitADC12(void);

#ifdef __cplusplus
}
#endif
#endif /* _MCDRV_TWR_KV46F150M_H_ */
