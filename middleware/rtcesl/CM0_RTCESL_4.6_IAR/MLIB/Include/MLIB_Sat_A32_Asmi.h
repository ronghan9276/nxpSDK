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
* @brief  Saturation
* 
*******************************************************************************/
#ifndef _MLIB_SAT_A32_ASM_H_
#define _MLIB_SAT_A32_ASM_H_

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
#define MLIB_Sat_F16a_Asmi(a32Accum) MLIB_Sat_F16a_FAsmi(a32Accum)

/***************************************************************************//*!
*
* Takes the fractional part from number in accumulator format and saturate if the original number is greater than 1. 
* 
*******************************************************************************/ 
/* inline function without any optimization (compilation issue) */ 
RTCESL_INLINE_OPTIM_SAVE
RTCESL_INLINE_OPTIM_SET
static inline frac16_t MLIB_Sat_F16a_FAsmi(register acc32_t a32Accum)
{
    register frac16_t f16Val=0;

    #if defined(__CC_ARM)                               /* For ARM Compiler */
        __asm volatile{ sxth f16Val, a32Accum           /* Takes fractional part */
                        cmp f16Val, a32Accum            /* Compares a32Accum and f16Val */
                        beq SatEnd                      /* If a32Accum != f16Val, then saturates output */
                        movs f16Val, #0x80              /* f16Val = 0x80 */
                        lsls f16Val, f16Val, #8         /* f16Val = 0x8000 */
                        subs f16Val, #1                 /* f16Val = 0x7FFF */
                        asrs a32Accum, a32Accum, #31    /* a32Accum >> 31 */
                        subs f16Val, f16Val, a32Accum   /* f16Val = 0x7FFF - a32Accum */
                    SatEnd: };
    #elif defined(__GNUC__) && ( __ARMCC_VERSION >= 6010050) 
        __asm volatile(
                        "sxth %0, %1 \n\t"              /* Takes fractional part */
                        "cmp %0, %1 \n\t"               /* Compares a32Accum and f16Val */
                        "beq MLIB_Sat_F16a_SatEnd%= \n\t" /* If a32Accum != f16Val, then saturates output */
                        "movs %0, #0x80 \n\t"           /* f16Val = 0x80 */
                        "lsls %0, %0, #8 \n\t"          /* f16Val = 0x8000 */
                        "subs %0, #1 \n\t"              /* f16Val = 0x7FFF */
                        "asrs %1, %1, #31 \n\t"         /* a32Accum >> 31 */
                        "subs %0, %0, %1 \n\t"          /* f16Val = 0x7FFF - a32Accum */
                    "MLIB_Sat_F16a_SatEnd%=:"
                        :"=&l"(f16Val), "+l"(a32Accum):);
    #elif defined(__GNUC__)
        __asm volatile(
                        #if defined(__GNUC__)           /* For GCC compiler */
                            ".syntax unified \n"        /* Using unified asm syntax */
                        #endif
                        "sxth %0, %1 \n"                /* Takes fractional part */
                        "cmp %0, %1 \n"                 /* Compares a32Accum and f16Val */
                        "beq SatEnd%= \n"               /* If a32Accum != f16Val, then saturates output */
                        "movs %0, #0x80 \n"             /* f16Val = 0x80 */
                        "lsls %0, %0, #8 \n"            /* f16Val = 0x8000 */
                        "subs %0, #1 \n"                /* f16Val = 0x7FFF */
                        "asrs %1, %1, #31 \n"           /* a32Accum >> 31 */
                        "subs %0, %0, %1 \n"            /* f16Val = 0x7FFF - a32Accum */
                    "SatEnd%=:"
                        #if defined(__GNUC__)           /* For GCC compiler */
                            ".syntax divided \n"
                        #endif
                        :"=&l"(f16Val), "+l"(a32Accum):);
    #else
        __asm volatile(
                        #if defined(__GNUC__)           /* For GCC compiler */
                            ".syntax unified \n"        /* Using unified asm syntax */
                        #endif
                        "sxth %0, %1 \n"                /* Takes fractional part */
                        "cmp %0, %1 \n"                 /* Compares a32Accum and f16Val */
                        "beq SatEnd \n"                 /* If a32Accum != f16Val, then saturates output */
                        "movs %0, #0x80 \n"             /* f16Val = 0x80 */
                        "lsls %0, %0, #8 \n"            /* f16Val = 0x8000 */
                        "subs %0, #1 \n"                /* f16Val = 0x7FFF */
                        "asrs %1, %1, #31 \n"           /* a32Accum >> 31 */
                        "subs %0, %0, %1 \n"            /* f16Val = 0x7FFF - a32Accum */
                    "SatEnd:"
                        #if defined(__GNUC__)           /* For GCC compiler */
                            ".syntax divided \n"
                        #endif
                        :"=&l"(f16Val), "+l"(a32Accum):);
    #endif

    return (frac16_t)f16Val;
}
/* inline function without any optimization (compilation issue) */ 
RTCESL_INLINE_OPTIM_RESTORE 

#if defined(__cplusplus)
}
#endif

#endif /* _MLIB_SAT_A32_ASM_H_ */
