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
* @brief  Negation
* 
*******************************************************************************/
#ifndef _MLIB_NEG_F32_ASM_H_
#define _MLIB_NEG_F32_ASM_H_

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
#define MLIB_NegSat_F32_Asmi(f32Val) MLIB_NegSat_F32_FAsmi(f32Val)
  
/***************************************************************************//*!
*
* Output = -f32Val
* With saturation
*******************************************************************************/  
#if defined(__IAR_SYSTEMS_ICC__)           /* IAR compiler */
#pragma diag_suppress=Pe549                /* Suppresses the Pe549 warning for IAR compiler*/
#endif
/* inline function without any optimization (compilation issue) */ 
RTCESL_INLINE_OPTIM_SAVE
RTCESL_INLINE_OPTIM_SET
static inline frac32_t MLIB_NegSat_F32_FAsmi(register frac32_t f32Val)
{
    register frac32_t f32SatVal=0;
    #if defined(__CC_ARM)                                 /* For ARM Compiler */
        __asm volatile{ rev f32SatVal, f32Val             /* f32SatVal = byte-reverse of f32Val*/
                        rsbs f32Val, f32Val, #0           /* f32Val = - f32Val */
                        cmp f32SatVal, #128               /* Compares f32SatVal with 0x80 */
                        bne SatEnd                        /* If f32SatVal != 0x80, then goes to SatEnd */
                        subs f32Val, f32Val, #1           /* If f32SatVal = 0x80, then f32Val = f32Val - 1 */
                    SatEnd: };
    #elif defined(__GNUC__) && ( __ARMCC_VERSION >= 6010050) 
        __asm volatile(
                        "rev %1, %0 \n\t"                 /* f32SatVal = byte-reverse of f32Val*/
                        "rsbs %0, %0, #0 \n\t"            /* f32Val = - f32Val */
                        "cmp %1, #128 \n\t"               /* Compares f32SatVal with 0x80 */
                        "bne MLIB_NegSat_F32_SatEnd%= \n\t" /* If f32SatVal != 0x80, then jumps through next command */
                        "subs %0, %0, #1 \n\t"            /* If f32SatVal = 0x80, then f32Val = f32Val - 1 */
					"MLIB_NegSat_F32_SatEnd%=: \n\t"
                        : "+l"(f32Val), "+l"(f32SatVal):);
    #else
        __asm volatile(
                        #if defined(__GNUC__)             /* For GCC compiler */
                            ".syntax unified \n"          /* Using unified asm syntax */
                        #endif  
                        "rev %1, %0 \n"                   /* f32SatVal = byte-reverse of f32Val*/
                        "rsbs %0, %0, #0 \n"              /* f32Val = - f32Val */
                        "cmp %1, #128 \n"                 /* Compares f32SatVal with 0x80 */
                        "bne .+4 \n"                      /* If f32SatVal != 0x80, then jumps through next command */
                        "subs %0, %0, #1 \n"              /* If f32SatVal = 0x80, then f32Val = f32Val - 1 */
                        #if defined(__GNUC__)             /* For GCC compiler */
                            ".syntax divided \n"
                        #endif
                        : "+l"(f32Val), "+l"(f32SatVal):);
    #endif

    return f32Val;
}
/* inline function without any optimization (compilation issue) */ 
RTCESL_INLINE_OPTIM_RESTORE 

#if defined(__IAR_SYSTEMS_ICC__)           /* IAR compiler */
#pragma diag_default=Pe549
#endif

#if defined(__cplusplus)
}
#endif

#endif /* _MLIB_NEG_F32_ASM_H_ */
