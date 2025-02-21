/*******************************************************************************
*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
* 
*
****************************************************************************//*!
*
* @brief  Multiply
* 
*******************************************************************************/
#ifndef _MLIB_MUL_F16_ASM_H_
#define _MLIB_MUL_F16_ASM_H_

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
#define MLIB_MulSat_F16_Asmi(f16Mult1, f16Mult2) MLIB_MulSat_F16_FAsmi(f16Mult1, f16Mult2)

/***************************************************************************//*!
*
* Output = f16Mult1 * f16Mult2
* With saturation
*******************************************************************************/
/* inline function without any optimization (compilation issue) */ 
RTCESL_INLINE_OPTIM_SAVE
RTCESL_INLINE_OPTIM_SET
static inline frac16_t MLIB_MulSat_F16_FAsmi(register frac16_t f16Mult1, register frac16_t f16Mult2)
{
    register frac32_t f32SatVal = 0x8000;
    #if defined(__CC_ARM)                                   /* For ARM Compiler */
        __asm volatile{ sxth f16Mult1, f16Mult1             /* Converts 16-bit input to 32-bit */
                        sxth f16Mult2, f16Mult2             /* Converts 16-bit input to 32-bit */
                        muls f16Mult1, f16Mult1, f16Mult2   /* f16Mult1 * f16Mult2 */
                        asrs f16Mult1, f16Mult1, #15        /* f16Mult1 >> 15  */
                        cmp f16Mult1, f32SatVal             /* Compares f16Mult1 with 0x8000*/
                        bne NotSat                          /* If f16Mult1 <> 0x8000, then jumps through next command */
                        subs f16Mult1, f16Mult1, #1         /* If f16Mult1 = 0x8000, then f16Mult1 = 0x7FFF */
                    NotSat: };
    #elif defined(__GNUC__) && ( __ARMCC_VERSION >= 6010050) 
        __asm volatile(
                        "sxth %0, %0 \n\t"                    /* Converts 16-bit input to 32-bit */
                        "sxth %1, %1 \n\t"                    /* Converts 16-bit input to 32-bit */
                        "muls %0, %0, %1 \n\t"                /* f16Mult1 * f16Mult2 */
                        "asrs %0, %0, #15 \n\t"               /* f16Mult1 >> 15  */
                        "cmp %0, %2 \n\t"                     /* Compares f16Mult1 with 0x8000*/
                        "bne MLIB_MulSat_F16_NotSat \n\t"     /* If f16Mult1 <> 0x8000, then jumps through next command */
                        "subs %0, %0, #1 \n\t"                /* If f16Mult1 = 0x8000, then f16Mult1 = 0x7FFF */
					"MLIB_MulSat_F16_NotSat: \n\t"
                        : "+l"(f16Mult1), "+l"(f16Mult2): "l"(f32SatVal));
    #endif

    return f16Mult1;
}
/* inline function without any optimization (compilation issue) */ 
RTCESL_INLINE_OPTIM_RESTORE 

#if defined(__cplusplus)
}
#endif

#endif /* _MLIB_MUL_F16_ASM_H_ */
