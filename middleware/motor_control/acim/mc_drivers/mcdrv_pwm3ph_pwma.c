/*
 * Copyright 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mcdrv_pwm3ph_pwma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

static bool_t s_statusPass;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Function updates FTM value register
 *
 * @param this   Pointer to the current object
 *
 * @return boot_t true on success
 */
bool_t MCDRV_eFlexPwm3PhSet(mcdrv_pwm3ph_pwma_t *this)
{
    frac16_t f16DutyCycle, f16DutyCycleTemp, f16ModuloTemp;
    GMCLIB_3COOR_T_F16 sUABCtemp;

    s_statusPass = TRUE;

    /* pointer to duty cycle structure */
    sUABCtemp = *this->psUABC;

    /* get modulo value from module 0 VAL1 register  */
    f16ModuloTemp = this->pui32PwmBaseAddress->SM[this->ui16PhASubNum].VAL1 + 1;

    /* phase A */
    f16DutyCycle                                            = MLIB_Mul_F16(f16ModuloTemp, sUABCtemp.f16A);
    f16DutyCycleTemp                                        = MLIB_Neg_F16(f16DutyCycle);
    this->pui32PwmBaseAddress->SM[this->ui16PhASubNum].VAL2 = f16DutyCycleTemp;
    this->pui32PwmBaseAddress->SM[this->ui16PhASubNum].VAL3 = f16DutyCycle;

    /* phase B */
    f16DutyCycle                                            = MLIB_Mul_F16(f16ModuloTemp, sUABCtemp.f16B);
    f16DutyCycleTemp                                        = MLIB_Neg_F16(f16DutyCycle);
    this->pui32PwmBaseAddress->SM[this->ui16PhBSubNum].VAL2 = f16DutyCycleTemp;
    this->pui32PwmBaseAddress->SM[this->ui16PhBSubNum].VAL3 = f16DutyCycle;

    /* phase C */
    f16DutyCycle                                            = MLIB_Mul_F16(f16ModuloTemp, sUABCtemp.f16C);
    f16DutyCycleTemp                                        = MLIB_Neg_F16(f16DutyCycle);
    this->pui32PwmBaseAddress->SM[this->ui16PhCSubNum].VAL2 = f16DutyCycleTemp;
    this->pui32PwmBaseAddress->SM[this->ui16PhCSubNum].VAL3 = f16DutyCycle;

    /* set LDOK bits */
    this->pui32PwmBaseAddress->MCTRL |= PWM_MCTRL_LDOK_MASK;

    return (s_statusPass);
}

/*!
 * @brief Function enables PWM outputs
 *
 * @param this   Pointer to the current object
 *
 * @return boot_t true on success
 */
bool_t MCDRV_eFlexPwm3PhOutEn(mcdrv_pwm3ph_pwma_t *this)
{
    s_statusPass = TRUE;

    /* PWM outputs of sub-modules 0,1 and 2 enabled */
    /* PWM_A output */
    this->pui32PwmBaseAddress->OUTEN =
        (this->pui32PwmBaseAddress->OUTEN & ~PWM_OUTEN_PWMA_EN_MASK) | PWM_OUTEN_PWMA_EN(0x7);

    /* PWM_B output */
    this->pui32PwmBaseAddress->OUTEN =
        (this->pui32PwmBaseAddress->OUTEN & ~PWM_OUTEN_PWMB_EN_MASK) | PWM_OUTEN_PWMB_EN(0x7);

    return (s_statusPass);
}

/*!
 * @brief Function disables PWM outputs
 *
 * @param this   Pointer to the current object
 *
 * @return boot_t true on success
 */
bool_t MCDRV_eFlexPwm3PhOutDis(mcdrv_pwm3ph_pwma_t *this)
{
    s_statusPass = TRUE;

    /* PWM outputs of sub-modules 0,1 and 2 disabled */
    /* PWM_A output */
    this->pui32PwmBaseAddress->OUTEN =
        (this->pui32PwmBaseAddress->OUTEN & ~PWM_OUTEN_PWMA_EN_MASK) | PWM_OUTEN_PWMA_EN(0x0);

    /* PWM_B output */
    this->pui32PwmBaseAddress->OUTEN =
        (this->pui32PwmBaseAddress->OUTEN & ~PWM_OUTEN_PWMB_EN_MASK) | PWM_OUTEN_PWMB_EN(0x0);

    return (s_statusPass);
}

/*!
 * @brief Function return actual value of over current flag
 *
 * @param this   Pointer to the current object
 *
 * @return boot_t true on success
 */
bool_t MCDRV_eFlexPwm3PhFltGet(mcdrv_pwm3ph_pwma_t *this)
{
    /* read over-current flags */
    s_statusPass = (((this->pui32PwmBaseAddress->FSTS & PWM_FSTS_FFPIN_MASK) >> 8) &
                    (1 << this->ui16FaultFixNum | 1 << this->ui16FaultAdjNum));

    /* clear faults flag */
    this->pui32PwmBaseAddress->FSTS = ((this->pui32PwmBaseAddress->FSTS & ~(PWM_FSTS_FFLAG_MASK)) |
                                       (1 << this->ui16FaultFixNum | 1 << this->ui16FaultAdjNum));

    return ((s_statusPass > 0));
}
