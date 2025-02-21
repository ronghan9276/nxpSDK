/*******************************************************************************
*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
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
* @brief  Absolute Value
* 
*******************************************************************************/
#ifndef _MLIB_ABS_F32_H_
#define _MLIB_ABS_F32_H_

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
#define MLIB_Abs_F32_Ci(f32Val)    MLIB_Abs_F32_FCi(f32Val)
#define MLIB_AbsSat_F32_Ci(f32Val) MLIB_AbsSat_F32_FCi(f32Val)
  
/***************************************************************************//*!
*  Absolute value      
*  f32Out = |f32In|
*  not saturated
*******************************************************************************/
static inline frac32_t MLIB_Abs_F32_FCi(register frac32_t f32Val)
{
    return((f32Val < (frac32_t)0) ? (-f32Val) : (f32Val));
}
/***************************************************************************//*!
*  Absolute value saturated        
*  f32Out = |f32In|
*******************************************************************************/  
static inline frac32_t MLIB_AbsSat_F32_FCi(register frac32_t f32Val)
{
    register int32_t i32Temp;
    
    i32Temp = (int32_t)(MLIB_Abs_F32_Ci(f32Val));
    i32Temp = (i32Temp == INT32_MIN) ? INT32_MAX : i32Temp; /* Correction for -1.0 * (-1.0) */
    return((frac32_t)(i32Temp));
}
#if defined(__cplusplus)
}
#endif

#endif  /* _MLIB_ABS_F32_H_*/
