/*
 * Copyright 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mcdrv_adcetc1010_imxrt.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Reads and calculates 3 phase samples based on SVM sector
 *
 * @param this   Pointer to the current object
 *
 * @return none
 */
RAM_FUNC_LIB
void MCDRV_Curr3Ph2ShGet(mcdrv_adcetc_t *this)
{
    GMCLIB_3COOR_T_F16 sIABCtemp;

    switch (*this->pui16SVMSector)
    {
        case 2:
        case 3:
            /* direct sensing of phase A and C, calculation of B */
            sIABCtemp.f16A = MLIB_ShLSat_F16(
                ((frac16_t)((int16_t)(ADC_ETC_TRIGn_RESULT_1_0_DATA0_MASK & (ADC_ETC->TRIG[0U].TRIGn_RESULT_1_0)) << 3U) -
                 this->sCurrSec23.ui16OffsetPhaA),
                1);

            sIABCtemp.f16C = MLIB_ShLSat_F16(
                ((frac16_t)((int16_t)((ADC_ETC->TRIG[0U].TRIGn_RESULT_1_0) >> ADC_ETC_TRIGn_RESULT_1_0_DATA1_SHIFT) << 3U) -
                 this->sCurrSec23.ui16OffsetPhaC),
                1);

            sIABCtemp.f16B = MLIB_Neg_F16(MLIB_AddSat_F16(sIABCtemp.f16A, sIABCtemp.f16C));
            break;

        case 4:
        case 5:
            /* direct sensing of phase A and B, calculation of C */
            sIABCtemp.f16A = MLIB_ShLSat_F16(
                ((frac16_t)((int16_t)(ADC_ETC_TRIGn_RESULT_1_0_DATA0_MASK & (ADC_ETC->TRIG[0U].TRIGn_RESULT_1_0)) << 3U) -
                 this->sCurrSec45.ui16OffsetPhaA),
                1);

            sIABCtemp.f16B = MLIB_ShLSat_F16(
                ((frac16_t)((int16_t)((ADC_ETC->TRIG[0U].TRIGn_RESULT_1_0) >> ADC_ETC_TRIGn_RESULT_1_0_DATA1_SHIFT) << 3U) -
                 this->sCurrSec45.ui16OffsetPhaB),
                1);

            sIABCtemp.f16C = MLIB_Neg_F16(MLIB_AddSat_F16(sIABCtemp.f16A, sIABCtemp.f16B));
            break;

        case 1:
        case 6:
        default:
            /* direct sensing of phase B and C, calculation of A */
            sIABCtemp.f16B = MLIB_ShLSat_F16(
                ((frac16_t)((int16_t)(ADC_ETC_TRIGn_RESULT_1_0_DATA0_MASK & (ADC_ETC->TRIG[0U].TRIGn_RESULT_1_0)) << 3U) -
                 this->sCurrSec16.ui16OffsetPhaB),
                1);

            sIABCtemp.f16C = MLIB_ShLSat_F16(
                ((frac16_t)((int16_t)((ADC_ETC->TRIG[0U].TRIGn_RESULT_1_0) >> ADC_ETC_TRIGn_RESULT_1_0_DATA1_SHIFT) << 3U) -
                 this->sCurrSec16.ui16OffsetPhaC),
                1);

            sIABCtemp.f16A = MLIB_Neg_F16(MLIB_AddSat_F16(sIABCtemp.f16B, sIABCtemp.f16C));
            break;
    }

    /* pass measured phase currents to the main module structure */
    this->psIABC->f16A = sIABCtemp.f16A;
    this->psIABC->f16B = sIABCtemp.f16B;
    this->psIABC->f16C = sIABCtemp.f16C;

}

/*!
 * @brief Set initial channel assignment for phase currents & DCB voltage
 *
 * @param this   Pointer to the current object
 *
 * @return none
 */
RAM_FUNC_LIB
void MCDRV_Curr3Ph2ShChanAssignInit(mcdrv_adcetc_t *this)
{


}

/*!
 * @brief Set new channel assignment for next sampling based on SVM sector
 *
 * @param this   Pointer to the current object
 *
 * @return none
 */
RAM_FUNC_LIB
void MCDRV_Curr3Ph2ShChanAssign(mcdrv_adcetc_t *this)
{

    switch (*this->pui16SVMSector)
    {
        /* direct sensing of phases A and C */
        case 2:
        case 3:            
            ADC_ETC->TRIG[0].TRIGn_CHAIN_1_0 = (ADC_ETC->TRIG[0].TRIGn_CHAIN_1_0 & (~ADC_ETC_TRIGn_CHAIN_1_0_CSEL0_MASK)) 
              | ADC_ETC_TRIGn_CHAIN_1_0_CSEL0(this->sCurrSec23.ui16ChanNumPhaA);
                        
            
            ADC_ETC->TRIG[0].TRIGn_CHAIN_1_0 = (ADC_ETC->TRIG[0].TRIGn_CHAIN_1_0 & (~ADC_ETC_TRIGn_CHAIN_1_0_CSEL1_MASK)) 
              | ADC_ETC_TRIGn_CHAIN_1_0_CSEL1(this->sCurrSec23.ui16ChanNumPhaC);
            
            
            break;

        /* direct sensing of phases A and B  */
        case 4:
        case 5:
            ADC_ETC->TRIG[0].TRIGn_CHAIN_1_0 = (ADC_ETC->TRIG[0].TRIGn_CHAIN_1_0 & (~ADC_ETC_TRIGn_CHAIN_1_0_CSEL0_MASK)) 
              | ADC_ETC_TRIGn_CHAIN_1_0_CSEL0(this->sCurrSec45.ui16ChanNumPhaA);
            
            
            
            
            ADC_ETC->TRIG[0].TRIGn_CHAIN_1_0 = (ADC_ETC->TRIG[0].TRIGn_CHAIN_1_0 & (~ADC_ETC_TRIGn_CHAIN_1_0_CSEL1_MASK)) 
              | ADC_ETC_TRIGn_CHAIN_1_0_CSEL1(this->sCurrSec45.ui16ChanNumPhaB);
            
            
            break;

        /* direct sensing of phases B and C */
        case 1:
        case 6:
        default: 
            ADC_ETC->TRIG[0].TRIGn_CHAIN_1_0 = (ADC_ETC->TRIG[0].TRIGn_CHAIN_1_0 & (~ADC_ETC_TRIGn_CHAIN_1_0_CSEL0_MASK)) 
              | ADC_ETC_TRIGn_CHAIN_1_0_CSEL0(this->sCurrSec16.ui16ChanNumPhaB);
            
            
            
            ADC_ETC->TRIG[0].TRIGn_CHAIN_1_0 = (ADC_ETC->TRIG[0].TRIGn_CHAIN_1_0 & (~ADC_ETC_TRIGn_CHAIN_1_0_CSEL1_MASK)) 
              | ADC_ETC_TRIGn_CHAIN_1_0_CSEL1(this->sCurrSec16.ui16ChanNumPhaC);
            
            
            break;
    }

}

/*!
 * @brief Initializes phase current channel offset measurement
 *
 * @param this   Pointer to the current object
 *
 * @return none
 */
RAM_FUNC_LIB
void MCDRV_Curr3Ph2ShCalibInit(mcdrv_adcetc_t *this)
{

    /* clear offset values */
    this->sCurrSec16.ui16OffsetPhaB = 0;
    this->sCurrSec16.ui16OffsetPhaC = 0;
    this->sCurrSec23.ui16OffsetPhaA = 0;
    this->sCurrSec23.ui16OffsetPhaC = 0;
    this->sCurrSec45.ui16OffsetPhaA = 0;
    this->sCurrSec45.ui16OffsetPhaB = 0;

    this->sCurrSec16.ui16CalibPhaB = 0;
    this->sCurrSec16.ui16CalibPhaC = 0;
    this->sCurrSec23.ui16CalibPhaA = 0;
    this->sCurrSec23.ui16CalibPhaC = 0;
    this->sCurrSec45.ui16CalibPhaA = 0;
    this->sCurrSec45.ui16CalibPhaB = 0;

    /* initialize offset filters */
    this->sCurrSec16.ui16FiltPhaB.u16Sh = this->ui16OffsetFiltWindow;
    this->sCurrSec16.ui16FiltPhaC.u16Sh = this->ui16OffsetFiltWindow;
    this->sCurrSec23.ui16FiltPhaA.u16Sh = this->ui16OffsetFiltWindow;
    this->sCurrSec23.ui16FiltPhaC.u16Sh = this->ui16OffsetFiltWindow;
    this->sCurrSec45.ui16FiltPhaA.u16Sh = this->ui16OffsetFiltWindow;
    this->sCurrSec45.ui16FiltPhaB.u16Sh = this->ui16OffsetFiltWindow;

    GDFLIB_FilterMAInit_F16((frac16_t)0, &this->sCurrSec16.ui16FiltPhaB);
    GDFLIB_FilterMAInit_F16((frac16_t)0, &this->sCurrSec16.ui16FiltPhaC);
    GDFLIB_FilterMAInit_F16((frac16_t)0, &this->sCurrSec23.ui16FiltPhaA);
    GDFLIB_FilterMAInit_F16((frac16_t)0, &this->sCurrSec23.ui16FiltPhaC);
    GDFLIB_FilterMAInit_F16((frac16_t)0, &this->sCurrSec45.ui16FiltPhaA);
    GDFLIB_FilterMAInit_F16((frac16_t)0, &this->sCurrSec45.ui16FiltPhaB);

}

/*!
 * @brief Function reads current samples and filter them based on SVM sector
 *
 * @param this   Pointer to the current object
 *
 * @return none
 */
RAM_FUNC_LIB
void MCDRV_Curr3Ph2ShCalib(mcdrv_adcetc_t *this)
{

    switch (*this->pui16SVMSector)
    {
        case 2:
        case 3:
            /* sensing of offset IA -> ADC1 and IC -> ADC2 */
            this->sCurrSec23.ui16CalibPhaA =
                GDFLIB_FilterMA_F16((frac16_t)((ADC_ETC_TRIGn_RESULT_1_0_DATA0_MASK & (ADC_ETC->TRIG[0U].TRIGn_RESULT_1_0)) << 3),
                                    &this->sCurrSec23.ui16FiltPhaA);
            this->sCurrSec23.ui16CalibPhaC =
                GDFLIB_FilterMA_F16((frac16_t)(((ADC_ETC->TRIG[0U].TRIGn_RESULT_1_0) >> ADC_ETC_TRIGn_RESULT_1_0_DATA1_SHIFT) << 3),
                                    &this->sCurrSec23.ui16FiltPhaC);
            break;

        case 4:
        case 5:
            /* sensing of offset IA -> ADC1 and IB -> ADC2 */
            this->sCurrSec45.ui16CalibPhaA =
                GDFLIB_FilterMA_F16((frac16_t)((ADC_ETC_TRIGn_RESULT_1_0_DATA0_MASK & (ADC_ETC->TRIG[0U].TRIGn_RESULT_1_0)) << 3),
                                    &this->sCurrSec45.ui16FiltPhaA);
            this->sCurrSec45.ui16CalibPhaB =
                GDFLIB_FilterMA_F16((frac16_t)(((ADC_ETC->TRIG[0U].TRIGn_RESULT_1_0) >> ADC_ETC_TRIGn_RESULT_1_0_DATA1_SHIFT) << 3),
                                    &this->sCurrSec45.ui16FiltPhaB);
            break;

        case 1:
        case 6:
        default:
            /* sensing of offset IB -> ADC1 and IC -> ADC2 */
            this->sCurrSec16.ui16CalibPhaB =
                GDFLIB_FilterMA_F16((frac16_t)((ADC_ETC_TRIGn_RESULT_1_0_DATA0_MASK & (ADC_ETC->TRIG[0U].TRIGn_RESULT_1_0)) << 3),
                                    &this->sCurrSec16.ui16FiltPhaB);
            this->sCurrSec16.ui16CalibPhaC =
                GDFLIB_FilterMA_F16((frac16_t)(((ADC_ETC->TRIG[0U].TRIGn_RESULT_1_0) >> ADC_ETC_TRIGn_RESULT_1_0_DATA1_SHIFT) << 3),
                                    &this->sCurrSec16.ui16FiltPhaC);
            break;
    }

}

/*!
 * @brief Function passes measured offset values to main structure
 *
 * @param this   Pointer to the current object
 *
 * @return none
 */
RAM_FUNC_LIB
void MCDRV_Curr3Ph2ShCalibSet(mcdrv_adcetc_t *this)
{

    /* pass calibration data for sector 1 and 6 */
    this->sCurrSec16.ui16OffsetPhaB = this->sCurrSec16.ui16CalibPhaB;
    this->sCurrSec16.ui16OffsetPhaC = this->sCurrSec16.ui16CalibPhaC;

    /* pass calibration data for sector 2 and 3 */
    this->sCurrSec23.ui16OffsetPhaA = this->sCurrSec23.ui16CalibPhaA;
    this->sCurrSec23.ui16OffsetPhaC = this->sCurrSec23.ui16CalibPhaC;

    /* pass calibration data for sector 4 and 5 */
    this->sCurrSec45.ui16OffsetPhaA = this->sCurrSec45.ui16CalibPhaA;
    this->sCurrSec45.ui16OffsetPhaB = this->sCurrSec45.ui16CalibPhaB;

}

/*!
 * @brief Function reads and passes DCB voltage sample
 *
 * @param this   Pointer to the current object
 *
 * @return none
 */
RAM_FUNC_LIB
void MCDRV_VoltDcBusGet(mcdrv_adcetc_t *this)
{

    /* read DC-bus voltage sample from defined ADC1 result register */ 
    *this->pf16UDcBus = (frac16_t)((ADC_ETC_TRIGn_RESULT_3_2_DATA2_MASK & (ADC_ETC->TRIG[0U].TRIGn_RESULT_3_2)) << 3);

}
