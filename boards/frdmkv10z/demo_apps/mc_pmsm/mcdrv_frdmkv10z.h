/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _MCDRV_FRDM_KV10_Z32_H
#define _MCDRV_FRDM_KV10_Z32_H

#include "fsl_device_registers.h"
#include "mcdrv_ftm_pwm3ph.h"
#include "mcdrv_adc_adc16.h"
#include "m1_sm_demo.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Structure used during clocks and modulo calculations */
typedef struct _clock_setup
{
    uint32_t ui32CoreSystemClock;
    uint32_t ui32BusClock;
    uint16_t ui16PwmFreq;
    uint16_t ui16PwmModulo;
    uint16_t ui16SpeedLoopFreq;
    uint16_t ui16SpeedLoopModulo;
} clock_setup_t;

/* define motor 1 ADC periphery (ADC16) */
#define M1_MCDRV_ADC (MCDRV_ADC16)

/* define motor 1 3-ph PWM periphery */
#define M1_MCDRV_PWM3PH (MCDRV_FTM0)

/* define motor 1 slow control loop timer */
#define M1_MCDRV_TMR_SLOWLOOP (MCDRV_FTM2)

/* define motor 1 ADC trigger PDB */
#define M1_MCDRV_PDB (MCDRV_PDB0)

/* define motor 1 CMP for over current detection */
#define M1_MCDRV_CMP (MCDRV_CMP1)

/******************************************************************************
 * Clock & PWM definition
 ******************************************************************************/
#define M1_PWM_FREQ (10000)         /* eFlexPWM frequency */
#define M1_FOC_FREQ_VS_PWM_FREQ (1) /* FOC calculation is called every n-th PWM reload */
#define M1_SPEED_LOOP_FREQ (1000)   /* Speed loop frequency */

/* assignment of FTM channels to motor phases
 * 0 - FTM channels 0&1
 * 2 - FTM channels 2&3
 * 4 - FTM channels 4&5 */
#define M1_PWM_PAIR_PHA (0)
#define M1_PWM_PAIR_PHB (2)
#define M1_PWM_PAIR_PHC (4)

/* Over Current Fault detection */
#define M1_FAULT_NUM (1)

/******************************************************************************
 * ADC measurement definition
 ******************************************************************************/
/* MCDRV I/O variables */
#define M1_MCDRV_ADCIO_UDCB_MEAS (gsM1Drive.sFocPMSM.f16UDcBus)
#define M1_MCDRV_ADCIO_IABC_MEAS (gsM1Drive.sFocPMSM.sIABC)
#define M1_MCDRV_ADCIO_SVMSECTOR (gsM1Drive.sFocPMSM.ui16SectorSVM)
#define M1_MCDRV_ADCIO_AUX_MEAS (gsM1Drive.f16AdcAuxSample)
#define M1_MCDRV_PWMIO_DUTY (gsM1Drive.sFocPMSM.sDutyABC)

/* Configuration table of ADC channels according to the input pin signals:
 * Valid for Kinetis KV10 Freedom board (FRDM-K10Z32) together with FRDM-MC-LVPMSM
 *
 * Proper ADC channel assignment needs to follow these rules:
 *   - at least one phase current must be assigned to both ADC modules
 *   - two other phase current channels must be assigned to different ADC modules
 *   - Udcb and auxiliary channels must be assigned to different ADC modules

 *   Quantity         | ADC Module 0  | ADC Module 1
 *   --------------------------------------------------------------------------
 *   I_A              | ADCA_CH6      | --------
 *   I_B              | --------      | ADCB_CH9
 *   I_C              | ADCA_CH7      | ADCB_CH7
 *   U_DCB            | ADCA_CH5      | --------
 */
/* Phase current A assignment to ADC0 only */
#define M1_ADC0_PH_A (6)
#define M1_ADC1_PH_A (MCDRV_CHAN_OFF)
/* Phase current A assignment to ADC1 only */
#define M1_ADC0_PH_B (MCDRV_CHAN_OFF)
#define M1_ADC1_PH_B (9)
/* Phase current A assignment to ADC0 and ADC1 */
#define M1_ADC0_PH_C (7)
#define M1_ADC1_PH_C (7)
/* Udc bus voltage is assigned to ADC0 only */
#define M1_ADC0_UDCB (5)
#define M1_ADC1_UDCB (MCDRV_CHAN_OFF)
/* Aux channel is assigned to ADC1 only */
#define M1_ADC0_AUX (MCDRV_CHAN_OFF)
#define M1_ADC1_AUX (30)

/******************************************************************************
 * MC driver macro definition and check - do not change this part
 ******************************************************************************/
/******************************************************************************
 * define motor 1 ADC control functions
 ******************************************************************************/
#ifdef M1_MCDRV_ADC
#if (M1_MCDRV_ADC == MCDRV_ADC16)
#define M1_MCDRV_ADC_PERIPH_INIT() (InitADC16())
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
 * define motor 1 3-ph PWM control functions                                  *
 ******************************************************************************/

#ifdef M1_MCDRV_PWM3PH
#if (M1_MCDRV_PWM3PH == MCDRV_FTM)
#define M1_MCDRV_PWM_PERIPH_INIT() (InitFTM0())
#define M1_MCDRV_PWM3PH_SET(par) (MCDRV_FtmPwm3PhSet(par))
#define M1_MCDRV_PWM3PH_EN(par) (MCDRV_FtmPwm3PhOutEn(par))
#define M1_MCDRV_PWM3PH_DIS(par) (MCDRV_FtmPwm3PhOutDis(par))
#define M1_MCDRV_PWM3PH_FLT_GET(par) (MCDRV_FtmPwm3PhFltGet(par))
#else
#error MCDRV: Unsupported PWM periphery!
#endif
#else
#error MCDRV: PWM periphery was not specified!
#endif

/******************************************************************************
 * define motor 1 slow control loop timer
 ******************************************************************************/
#ifdef M1_MCDRV_TMR_SLOWLOOP
#if (M1_MCDRV_TMR_SLOWLOOP == MCDRV_FTM2)
#define M1_MCDRV_TMR_SLOWLOOP_INIT() InitFTM2()
#else
#error MCDRV: Unsupported Timer periphery!
#endif
#else
#error MCDRV: Timer periphery was not specified!
#endif

/******************************************************************************
 * define motor 1 ADC trigger PDB
 ******************************************************************************/
#ifdef M1_MCDRV_PDB
#if (M1_MCDRV_PDB == MCDRV_PDB0)
#define M1_MCDRV_PDB_INIT() InitPDB()
#else
#error MCDRV: Unsupported PDB periphery!
#endif
#else
#error MCDRV: PDB periphery was not specified!
#endif

/******************************************************************************
 * define motor 1 CMP for overcurrent detection                               *
 ******************************************************************************/
#ifdef M1_MCDRV_CMP
#if (M1_MCDRV_CMP == MCDRV_CMP1)
#define M1_MCDRV_CMP_INIT() InitCMP1()
#else
#error MCDRV: Unsupported CMP periphery!
#endif
#else
#error MCDRV: CMP periphery was not specified!
#endif

/******************************************************************************
 * define motor 1 3-ph driver control functions                               *
 ******************************************************************************/
#ifdef M1_MCDRV_SPI_DRV3PH
#if (M1_MCDRV_SPI_DRV3PH == MCDRV_SPI_DRV)
#define M1_MCDRV_DRV3PH_T MCDRV_SPI_DRV3PH_T
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

/* check whether ADC channel assignment is correct */
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
extern mcdrv_ftm_pwm3ph_t g_sM1Pwm3ph;
extern mcdrv_adc16_t g_sM1AdcSensor;
extern clock_setup_t g_sClockSetup;

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

void InitFTM0(void);
void InitFTM2(void);
void InitPDB(void);
void InitADC16(void);
void InitCMP1(void);
void MCDRV_Init_M1(void);
void InitClock(void);

#ifdef __cplusplus
}
#endif
#endif /* _MCDRV_FRDM_KV10_Z32_H  */
