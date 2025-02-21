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
* @brief  Shift
* 
*******************************************************************************/
#ifndef _MLIB_SHIFT_F32_H_
#define _MLIB_SHIFT_F32_H_

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
* Includes
*******************************************************************************/
#include "mlib_types.h"

/*******************************************************************************
* Macros
*******************************************************************************/  
#define MLIB_Sh1L_F32_Ci(f32Val)          MLIB_Sh1L_F32_FCi(f32Val) 
#define MLIB_Sh1R_F32_Ci(f32Val)          MLIB_Sh1R_F32_FCi(f32Val)   
#define MLIB_ShL_F32_Ci(f32Val, u16Sh)    MLIB_ShL_F32_FCi(f32Val, u16Sh)
#define MLIB_ShR_F32_Ci(f32Val, u16Sh)    MLIB_ShR_F32_FCi(f32Val, u16Sh)  
#define MLIB_ShLSat_F32_Ci(f32Val, u16Sh) MLIB_ShLSat_F32_FCi(f32Val, u16Sh)  

/***************************************************************************//*!
*
* This function returns the f32Val input shifted by 1 to the left. 
* The function does not saturate the output.
*              
*******************************************************************************/  
static inline frac32_t MLIB_Sh1L_F32_FCi(register frac32_t f32Val)
{
    return((frac32_t)(f32Val << 1));
}
/***************************************************************************//*!
*
* This function returns the f32Val input shifted by 1 to the right. 
*              
*******************************************************************************/
static inline frac32_t MLIB_Sh1R_F32_FCi(register frac32_t f32Val)
{
    return((frac32_t)(f32Val >> 1));
}
/***************************************************************************//*!
*
* This function returns the f32Val input shifted by the number of u16Sh to the left. 
* The function does not saturate the output. 
*             
*******************************************************************************/
static inline frac32_t MLIB_ShL_F32_FCi(register frac32_t f32Val, register uint16_t u16Sh)
{
    return((frac32_t)(f32Val << u16Sh));
}
/***************************************************************************//*!
*
* This function returns the f32Val input shifted by the number of u16Sh to the right.  
*             
*******************************************************************************/ 
static inline frac32_t MLIB_ShR_F32_FCi(register frac32_t f32Val, register uint16_t u16Sh)
{
  return((frac32_t)(f32Val >> u16Sh));
}
/***************************************************************************//*!
*
* This function returns the f32Val input shifted by the number of u16Sh to the left. 
* The function saturates the output. 
*             
*******************************************************************************/  
static inline frac32_t MLIB_ShLSat_F32_FCi(register frac32_t f32Val, register uint16_t u16Sh)
{
    register frac32_t f32Temp, f32Out;
    
    f32Out = (frac32_t)(f32Val << u16Sh);
    f32Temp = (frac32_t)((frac32_t)(INT32_MAX) >> u16Sh);
    if(f32Val > f32Temp)
    {
        f32Out = (frac32_t)(INT32_MAX);
    }
    else
    {
        f32Temp = (frac32_t)((frac32_t)(INT32_MIN) >> u16Sh);
        if(f32Val <= f32Temp)
        {
            f32Out = (frac32_t)(INT32_MIN);
        }
    }
    return(f32Out);
}
#if defined(__cplusplus)
}
#endif

#endif /* _MLIB_SHIFT_F32_H_ */
