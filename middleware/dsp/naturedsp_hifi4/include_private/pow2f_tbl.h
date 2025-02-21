/* ------------------------------------------------------------------------ */
/* Copyright (c) 2018 by Cadence Design Systems, Inc. ALL RIGHTS RESERVED.  */
/* These coded instructions, statements, and computer programs ("Cadence    */
/* Libraries") are the copyrighted works of Cadence Design Systems Inc.	    */
/* Cadence IP is licensed for use with Cadence processor cores only and     */
/* must not be used for any other processors and platforms. Your use of the */
/* Cadence Libraries is subject to the terms of the license agreement you   */
/* have entered into with Cadence Design Systems, or a sublicense granted   */
/* to you by a direct Cadence licensee.                                     */
/* ------------------------------------------------------------------------ */
/*  IntegrIT, Ltd.   www.integrIT.com, info@integrIT.com                    */
/*                                                                          */
/* DSP Library                                                              */
/*                                                                          */
/* This library contains copyrighted materials, trade secrets and other     */
/* proprietary information of IntegrIT, Ltd. This software is licensed for  */
/* use with Cadence processor cores only and must not be used for any other */
/* processors and platforms. The license to use these sources was given to  */
/* Cadence, Inc. under Terms and Condition of a Software License Agreement  */
/* between Cadence, Inc. and IntegrIT, Ltd.                                 */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2015-2018 IntegrIT, Limited.                      */
/*                      All Rights Reserved.                                */
/* ------------------------------------------------------------------------ */

/*
    tables for 2^x approximation
*/
#ifndef POW2F_TBL_H__
#define POW2F_TBL_H__
#include "NatureDSP_types.h"
#include "common.h"

/*
        polynomial coefficients for 2.^x, x=[-1...0)
        x=(-1:pow2(1,-16):0); y=2.^x; p=polyfit(x,y,6);
*/
externC const union ufloat32uint32 ALIGN(32) polypow2f_tbl[];
externC const union ufloat32uint32 ALIGN(32) log2f_coef[];

/* polynomial coefficients for 2^x, x=-0.5...0.5 */
externC const union ufloat32uint32 ALIGN(32) pow2f_coef[];
#endif
