/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
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

/*******************************************************************************
*
* @brief  Main GFLIB header file for devices without FPU.
* 
*******************************************************************************/
#ifndef _GFLIB_H_
#define _GFLIB_H_

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
* Includes
*******************************************************************************/ 
#include "mlib.h"
#include "GFLIB_Atan_A32.h"
#include "GFLIB_AtanYX_A32.h"
#include "GFLIB_CtrlPIp_A32.h"
#include "GFLIB_FlexRamp_A32.h"      
#include "GFLIB_DFlexRamp_A32.h"    
#include "GFLIB_DRamp_F16.h" 
#include "GFLIB_DRamp_F32.h"     
#include "GFLIB_Hyst_F16_Asmi.h"
#include "GFLIB_Integrator_A32.h" 
#include "GFLIB_Limit_F16.h" 
#include "GFLIB_Limit_F32.h" 
#include "GFLIB_LowerLimit_F16.h" 
#include "GFLIB_LowerLimit_F32.h"
#include "GFLIB_Lut_F32.h"
#include "GFLIB_Lut_F16_Asmi.h"
#include "GFLIB_LutPer_F32.h"
#include "GFLIB_LutPer_F16_Asmi.h"
#include "GFLIB_Ramp_F16.h"
#include "GFLIB_Ramp_F16_Asmi.h"
#include "GFLIB_Ramp_F32.h"    
#include "GFLIB_Ramp_F32_Asmi.h"
#include "GFLIB_SinCos_A32.h"  
#include "GFLIB_Sqrt_F16.h"
#include "GFLIB_Sqrt_F32.h"  
#include "GFLIB_UpperLimit_F16.h" 
#include "GFLIB_UpperLimit_F32.h"   
#include "GFLIB_VectorLimit1_F16.h"
#include "GFLIB_AtanYXHw_A32.h"
#include "GFLIB_FlexRampHw_A32.h"      
#include "GFLIB_DFlexRampHw_A32.h"    
#include "GFLIB_SqrtHw_F16.h"
#include "GFLIB_SqrtHw_F16_Asmi.h"
#include "GFLIB_SqrtHw_F32.h"
#include "GFLIB_SqrtHw_F32_Asmi.h"
#include "GFLIB_VectorLimit1Hw_F16.h"  

/*******************************************************************************
* Macros
*******************************************************************************/
#define GFLIB_Atan_F16(f16Val)                                                 GFLIB_Atan_F16_Asm(f16Val)
#define GFLIB_Cos_F16(f16Angle)                                                GFLIB_Cos_F16_Asmi(f16Angle)
#define GFLIB_CtrlPIpAWInit_F16(f16InitVal, psParam)                           GFLIB_CtrlPIpAWInit_F16_Ci(f16InitVal, psParam)
#define GFLIB_CtrlPIpAW_F16(f16InErr, pbStopIntegFlag, psParam)                GFLIB_CtrlPIpAW_F16_Asm(f16InErr, pbStopIntegFlag, psParam)
#define GFLIB_DFlexRampInit_F16(f16InitVal, psParam)                           GFLIB_DFlexRampInit_F16_C(f16InitVal, psParam)
#define GFLIB_DFlexRamp_F16(f16Instant, pbStopFlagMot, pbStopFlagGen, psParam) GFLIB_DFlexRamp_F16_C(f16Instant, pbStopFlagMot, pbStopFlagGen, psParam)
#define GFLIB_FlexRampInit_F16(f16InitVal, psParam)                            GFLIB_FlexRampInit_F16_C(f16InitVal, psParam)
#define GFLIB_FlexRamp_F16(psParam)                                            GFLIB_FlexRamp_F16_C(psParam)
#define GFLIB_DRampInit_F16(f16InitVal, psParam)                               GFLIB_DRampInit_F16_Ci(f16InitVal, psParam)
#define GFLIB_DRampInit_F32(f32InitVal, psParam)                               GFLIB_DRampInit_F32_Ci(f32InitVal, psParam)
#define GFLIB_DRamp_F16(f16Target, f16Instant, pbStopFlag, psParam)            GFLIB_DRamp_F16_Asm(f16Target, f16Instant, pbStopFlag, psParam)
#define GFLIB_DRamp_F32(f32Target, f32Instant, pbStopFlag, psParam)            GFLIB_DRamp_F32_Asm(f32Target, f32Instant, pbStopFlag, psParam)
#define GFLIB_Hyst_F16(f16Val, psParam)                                        GFLIB_Hyst_F16_Asmi(f16Val, psParam)
#define GFLIB_IntegratorInit_F16(f16InitVal, psParam)                          GFLIB_IntegratorInit_F16_Ci(f16InitVal, psParam)
#define GFLIB_Integrator_F16(f16InVal, psParam)                                GFLIB_Integrator_F16_Ci(f16InVal, psParam)
#define GFLIB_Limit_F16(f16Val, f16LLim, f16ULim)                              GFLIB_Limit_F16_Ci(f16Val, f16LLim, f16ULim)  
#define GFLIB_Limit_F32(f32Val, f32LLim, f32ULim)                              GFLIB_Limit_F32_Ci(f32Val, f32LLim, f32ULim)
#define GFLIB_LowerLimit_F16(f16Val, f16LLim)                                  GFLIB_LowerLimit_F16_Ci(f16Val, f16LLim)  
#define GFLIB_LowerLimit_F32(f32Val, f32LLim)                                  GFLIB_LowerLimit_F32_Ci(f32Val, f32LLim)
#define GFLIB_Lut1D_F16(f16X, pf16Table, u16TableSize)                         GFLIB_Lut1D_F16_Asmi(f16X, pf16Table, u16TableSize)
#define GFLIB_LutPer1D_F16(f16X, pf16Table, u16TableSize)                      GFLIB_LutPer1D_F16_Asmi( f16X, pf16Table, u16TableSize)
#define GFLIB_RampInit_F16(f16InitVal, psParam)                                GFLIB_RampInit_F16_Ci(f16InitVal, psParam)
#define GFLIB_RampInit_F32(f32InitVal, psParam)                                GFLIB_RampInit_F32_Ci(f32InitVal, psParam)
#define GFLIB_Ramp_F16(f16Target, psParam)                                     GFLIB_Ramp_F16_Asmi(f16Target, psParam)
#define GFLIB_Ramp_F32(f32Target, psParam)                                     GFLIB_Ramp_F32_Asmi(f32Target, psParam)
#define GFLIB_Sin_F16(f16Angle)                                                GFLIB_Sin_F16_Asm(f16Angle)
#define GFLIB_UpperLimit_F16(f16Val, f16ULim)                                  GFLIB_UpperLimit_F16_Ci(f16Val, f16ULim)     
#define GFLIB_UpperLimit_F32(f32Val, f32ULim)                                  GFLIB_UpperLimit_F32_Ci(f32Val, f32ULim)     
#if (RTCESL_MMDVSQ)                                                            
    #define GFLIB_AtanYX_F16(f16Y, f16X, pbErrFlag)                            GFLIB_AtanYXHw_F16_Asm(f16Y, f16X, pbErrFlag)
    #define GFLIB_Sqrt_F16(f16Val)                                             GFLIB_SqrtHw_F16_Asmi(f16Val)
    #define GFLIB_Sqrt_F16l(f32Val)                                            GFLIB_SqrtHw_F16l_Asmi(f32Val)
    #define GFLIB_VectorLimit1_F16(psVectorIn, f16Lim, psVectorOut)            GFLIB_VectorLimit1Hw_F16_C(psVectorIn, f16Lim, psVectorOut)
    #define GFLIB_DFlexRampCalcIncr_F16(f16Target, a32Duration, f32IncrSatMot, f32IncrSatGen, psParam)             \
            GFLIB_DFlexRampCalcIncrHw_F16_C(f16Target, a32Duration, f32IncrSatMot, f32IncrSatGen, psParam)
    #define GFLIB_FlexRampCalcIncr_F16(f16Target, a32Duration, psParam)                                            \
            GFLIB_FlexRampCalcIncrHw_F16_C(f16Target, a32Duration, psParam)                                  
#else                                                                  
    #define GFLIB_AtanYX_F16(f16Y, f16X, pbErrFlag)                             GFLIB_AtanYX_F16_Asm(f16Y, f16X, pbErrFlag)
    #define GFLIB_Sqrt_F16(f16Val)                                              GFLIB_Sqrt_F16_C(f16Val)
    #define GFLIB_Sqrt_F16l(f32Val)                                             GFLIB_Sqrt_F16l_C(f32Val)
    #define GFLIB_VectorLimit1_F16(psVectorIn, f16Lim, psVectorOut)             GFLIB_VectorLimit1_F16_C(psVectorIn, f16Lim, psVectorOut)
    #define GFLIB_DFlexRampCalcIncr_F16(f16Target, a32Duration, f32IncrSatMot, f32IncrSatGen, psParam)             \
            GFLIB_DFlexRampCalcIncr_F16_C(f16Target, a32Duration, f32IncrSatMot, f32IncrSatGen, psParam)
    #define GFLIB_FlexRampCalcIncr_F16(f16Target, a32Duration, psParam)                                            \
            GFLIB_FlexRampCalcIncr_F16_C(f16Target, a32Duration, psParam)                     
#endif              
  
#if defined(__cplusplus)
}
#endif

#endif /* _GFLIB_H_ */  
