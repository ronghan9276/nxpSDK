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
* @brief  Count of leading bits
* 
*******************************************************************************/
#ifndef _MLIB_CLB_F32_ASM_H_
#define _MLIB_CLB_F32_ASM_H_

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
#define MLIB_Clb_U16l_Asmi(f32Val) MLIB_Clb_U16l_FAsmi(f32Val)
  
/***************************************************************************//*!
* Count of leading bits
*  - first, if input < 0, the Bitwise NOT of the input is calculated
*  - then the amount of zero bits before the first non-zero bits is counted (sign bit is not included)
****************************************************************************/ 
/* inline function without any optimization (compilation issue) */ 
RTCESL_INLINE_OPTIM_SAVE
RTCESL_INLINE_OPTIM_SET
static inline uint16_t MLIB_Clb_U16l_FAsmi (register frac32_t f32Val)
{
    register frac32_t f32Clb = 0;                       /* Initialization of f32Clb */
    register frac32_t f32CompVal = 0xFFFF;              /* Initialization of f32CompVal */
  
    #if defined(__CC_ARM)                               /* For ARM Compiler */
        __asm volatile{ cmp f32Val,#0                   /* Compares f32Val with 0 */
                        bgt NotNeg                      /* If f32Val > 0, then go to NotNeg */
                        mvns f32Val, f32Val             /* If f32Val <= 0, then Bitwise NOT of f32Val */
                        bne NotNeg                      /* If f32Val <> 0, then go to NotNeg */
                        subs f32Val, f32Val, #1         /* f32Val = f32Val - 1 */
                    NotNeg:  
                        cmp f32Val, f32CompVal          /* Compares f32Val with 0xFFFF */
                        ble Cmp1                        /* If f32Val <= 0xFF, then goes to Cmp1 */
                        movs f32Clb, #16                /* f32Clb = 16 */
                        lsrs f32Val, f32Val, #16        /* f32Val >> 16 */
                    Cmp1:  
                        cmp f32Val, #0xFF               /* Compares f32Val with 0xFF */
                        ble Cmp2                        /* If f32Val <= 0xFF, then goes to Cmp2 */
                        adds f32Clb, #8                 /* f32Clb = f32Clb + 8 */
                        lsrs f32Val, f32Val, #8         /* f32Val >> 8 */
                    Cmp2:  
                        cmp f32Val, #0xF                /* Compares f32Val with 0xF */
                        ble Cmp3                        /* If f32Val <= 0xFF, then goes to Cmp3 */
                        adds f32Clb, #4                 /* f32Clb = f32Clb + 4 */
                        lsrs f32Val, f32Val, #4         /* f32Val >> 4 */
                    Cmp3:  
                        cmp f32Val, #0x3                /* Compares f32Val with 0x3 */
                        ble Cmp4                        /* If f32Val <= 0xFF, then goes to Cmp4 */
                        adds f32Clb, #2                 /* f32Clb = f32Clb + 2 */
                        lsrs f32Val, f32Val, #2         /* f32Val >> 2 */
                    Cmp4:  
                        lsrs f32Val, f32Val, #1         /* f32Val >> 1 */
                        orrs f32Clb, f32Clb, f32Val     /* f32Clb = f32Clb |= f32Val */
                        movs f32Val, #30                /* f32Val = 30 */
                        subs f32Val, f32Val, f32Clb};   /* f32Val = 30 - f32Clb */
    #elif defined(__GNUC__) && ( __ARMCC_VERSION >= 6010050) 
        __asm volatile(
                        "cmp %0,#0 \n\t"                /* Compares f32Val with 0 */
                        "bgt MLIB_Clb_U16l_NotNeg%= \n\t" /* If f32Val > 0, then jumps through three commands */
                        "mvns %0, %0 \n\t"              /* If f32Val <= 0, then Bitwise NOT of f32Val */
                        "bne MLIB_Clb_U16l_NotNeg%= \n\t" /* If f32Val <> 0, then jumps through the next command */
                        "subs %0, %0, #1 \n\t"          /* f32Val = f32Val - 1 */
					"MLIB_Clb_U16l_NotNeg%=: \n\t"
                        "cmp %0, %2 \n\t"               /* Compares f32Val with 0xFFFF */
                        "ble MLIB_Clb_U16l_Cmp1%= \n\t"   /* If f32Val <= 0xFFFF, then jumps through two commands */
                        "movs %1, #16 \n\t"             /* f32Clb = 16 */
                        "lsrs %0, %0, #16 \n\t"         /* f32Val >> 16 */
					"MLIB_Clb_U16l_Cmp1%=: \n\t"
                        "cmp %0, #0xFF \n\t"            /* Compares f32Val with 0xFF */
                        "ble MLIB_Clb_U16l_Cmp2%= \n\t"   /* If f32Val <= 0xFF, then jumps through two commands */
                        "adds %1, #8 \n\t"              /* f32Clb = f32Clb + 8 */
                        "lsrs %0, %0, #8 \n\t"          /* f32Val >> 8 */
					"MLIB_Clb_U16l_Cmp2%=: \n\t"
                        "cmp %0, #0xF \n\t"             /* Compares f32Val with 0xF */
                        "ble MLIB_Clb_U16l_Cmp3%= \n\t"   /* If f32Val <= 0xF, then jumps through two commands */
                        "adds %1, #4 \n\t"              /* f32Clb = f32Clb + 4 */
                        "lsrs %0, %0, #4 \n\t"          /* f32Val >> 4 */
					"MLIB_Clb_U16l_Cmp3%=: \n\t"
                        "cmp %0, #0x3 \n\t"             /* Compares f32Val with 0x3 */
                        "ble MLIB_Clb_U16l_Cmp4%= \n\t"   /* If f32Val <= 0x3, then jumps through two commands */
                        "adds %1, #2 \n\t"              /* f32Clb = f32Clb + 2 */
                        "lsrs %0, %0, #2 \n\t"          /* f32Val >> 2 */
					"MLIB_Clb_U16l_Cmp4%=: \n\t"
                        "lsrs %0, %0, #1 \n\t"          /* f32Val >> 1 */
                        "orrs %1, %1, %0 \n\t"          /* f32Clb = f32Clb |= f32Val */
                        "movs %0, #30 \n\t"             /* f32Val = 30 */
                        "subs %0, %0, %1 \n\t"          /* f32Val = 30 - f32Clb */

                        : "+l"(f32Val), "+l"(f32Clb): "l"(f32CompVal));
    #else
        __asm volatile(
                        #if defined(__GNUC__)           /* For GCC Compiler */
                            ".syntax unified \n"        /* Using unified asm syntax */
                        #endif
                        "cmp %0,#0 \n"                  /* Compares f32Val with 0 */
                        "bgt .+8 \n"                    /* If f32Val > 0, then jumps through three commands */
                        "mvns %0, %0 \n"                /* If f32Val <= 0, then Bitwise NOT of f32Val */
                        "bne .+4 \n"                    /* If f32Val <> 0, then jumps through the next command */
                        "subs %0, %0, #1 \n"            /* f32Val = f32Val - 1 */

                        "cmp %0, %2 \n"                 /* Compares f32Val with 0xFFFF */
                        "ble .+6 \n"                    /* If f32Val <= 0xFFFF, then jumps through two commands */
                        "movs %1, #16 \n"               /* f32Clb = 16 */
                        "lsrs %0, %0, #16 \n"           /* f32Val >> 16 */

                        "cmp %0, #0xFF \n"              /* Compares f32Val with 0xFF */
                        "ble .+6 \n"                    /* If f32Val <= 0xFF, then jumps through two commands */
                        "adds %1, #8 \n"                /* f32Clb = f32Clb + 8 */
                        "lsrs %0, %0, #8 \n"            /* f32Val >> 8 */

                        "cmp %0, #0xF \n"               /* Compares f32Val with 0xF */
                        "ble .+6 \n"                    /* If f32Val <= 0xF, then jumps through two commands */
                        "adds %1, #4 \n"                /* f32Clb = f32Clb + 4 */
                        "lsrs %0, %0, #4 \n"            /* f32Val >> 4 */

                        "cmp %0, #0x3 \n"               /* Compares f32Val with 0x3 */
                        "ble .+6 \n"                    /* If f32Val <= 0x3, then jumps through two commands */
                        "adds %1, #2 \n"                /* f32Clb = f32Clb + 2 */
                        "lsrs %0, %0, #2 \n"            /* f32Val >> 2 */

                        "lsrs %0, %0, #1 \n"            /* f32Val >> 1 */
                        "orrs %1, %1, %0 \n"            /* f32Clb = f32Clb |= f32Val */

                        "movs %0, #30 \n"               /* f32Val = 30 */
                        "subs %0, %0, %1 \n"            /* f32Val = 30 - f32Clb */
                        #if defined(__GNUC__)           /* For GCC Compiler */
                            ".syntax divided \n"
                        #endif
                        : "+l"(f32Val), "+l"(f32Clb): "l"(f32CompVal));
    #endif

    return f32Val;
}
/* inline function without any optimization (compilation issue) */ 
RTCESL_INLINE_OPTIM_RESTORE 

#if defined(__cplusplus)
}
#endif

#endif  /* _MLIB_CLB_F32_ASM_H_ */
