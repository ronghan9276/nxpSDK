/*******************************************************************************
*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
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
* 
*
****************************************************************************//*!
*
* @brief  Hysteresis function 
* 
*******************************************************************************/
#ifndef _GFLIB_HYST_FLT_H_
#define _GFLIB_HYST_FLT_H_

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
* Includes
*******************************************************************************/
#include "mlib_FP.h"
#include "gflib_types.h"

/*******************************************************************************
* Macros 
*******************************************************************************/
#define GFLIB_Hyst_FLT_Ci(fltVal, psParam) GFLIB_Hyst_FLT_FCi(fltVal, psParam) 
  
/*******************************************************************************
* Types
*******************************************************************************/  
typedef struct
{
    float_t fltHystOn;    /* Value determining the upper threshold */
    float_t fltHystOff;   /* Value determining the lower threshold */
    float_t fltOutValOn;  /* Value of the output when input is higher than the upper threshold */
    float_t fltOutValOff; /* Value of output when input is lower than lower threshold */
    float_t fltOutState;  /* Actual state of the output */
}   GFLIB_HYST_T_FLT;

/***************************************************************************//*!
*
* @brief     Hysteresis function
*
* @param     ptr  GFLIB_HYST_T_FLT *psParam
*                  - fltHystOn: Upper threshold
*                  - fltHystOff: Lower threshold
*                  - fltOutValOn: Output when input is above f16HystOn
*                  - fltOutValOff: Output when input is below f16HystOff
*                  - fltOutState: Output of the function
*
* @param     in  float_t fltVal
*
* @return    N/A
*
* @remarks   The function represents a hysteresis (or relay) function. The
*            function switches output between the two predefined values. When
*            the input is higher than upper threshold fltHystOn, the output
*            is high; when the input is below another (lower) threshold
*            fltHystOff, the output is low; when the input is between the two,
*            the output retains its value.
*
****************************************************************************/
static inline float_t GFLIB_Hyst_FLT_FCi(float_t fltVal, GFLIB_HYST_T_FLT *psParam)
{   
    if(fltVal < psParam->fltHystOff) 
    {
        psParam->fltOutState = psParam->fltOutValOff;
    }
    else if(fltVal > psParam->fltHystOn)  
    {
        psParam->fltOutState = psParam->fltOutValOn;
    }
    
    return(psParam->fltOutState);
}
 
#if defined(__cplusplus)
}
#endif

#endif /* _GFLIB_HYST_FLT_H_ */

