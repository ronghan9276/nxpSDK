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
* @brief  Subtraction
* 
*******************************************************************************/
#ifndef _MLIB_SUB_F16_H_
#define _MLIB_SUB_F16_H_

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
#define MLIB_Sub_F16_Ci(f16Min, f16Sub)    MLIB_Sub_F16_FCi(f16Min, f16Sub) 

/***************************************************************************//*!
*
* f16Out = f16Min - f16Sub
* Without saturation
*******************************************************************************/
static inline frac16_t MLIB_Sub_F16_FCi(register frac16_t f16Min, register frac16_t f16Sub)
{
    return(f16Min - f16Sub);
}
#if defined(__cplusplus)
}
#endif

#endif /* _MLIB_SUB_F16_H_ */
