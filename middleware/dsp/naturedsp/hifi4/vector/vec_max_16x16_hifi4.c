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

#include "common.h"
#include "NatureDSP_types.h"
/* Library API */
#include "NatureDSP_Signal_vector.h"

/*-------------------------------------------------------------------------
  Vector Min/Max
  These routines find maximum/minimum value in a vector.
  Two versions of functions available: regular version (vec_min32x32, 
  vec_max32x32, vec_min16x16, vec_max16x16, vec_minf, vec_maxf) with 
  arbitrary arguments and faster version (vec_min32x32_fast, vec_max32x32_fast, 
  vec_min16x16_fast, vec_max16x16_fast) that apply some restrictions
  NOTE: functions return zero if N is less or equal to zero

  Precision: 
  32x32 32-bit data, 32-bit output
  16x16 16-bit data, 16-bit output
  f     single precision floating point
  
  Input:
  x[N]  input data
  N     length of vector
  Returned value:
  Minimum or maximum value correspondingly

  Restriction:
  For regular routines:
  none
  For faster routines:
  x aligned on 8-byte boundary
  N   - multiple of 4
-------------------------------------------------------------------------*/
int16_t vec_max16x16 (const int16_t* restrict x, int N)
{
  int         n;
  const ae_int16x4 * restrict px = (const ae_int16x4 *)x;
  ae_valign      x_align;
  ae_int16x4  vxh, vmh, vzh;
  xtbool4     cprt;

  NASSERT(x);
  if (N <= 0) return 0;

  vzh = vmh = AE_MOVDA16(0x8000);
  x_align = AE_LA64_PP(px);

  for (n=0;n<N-7;n+=8)
  {
    AE_LA16X4_IP(vxh, x_align, px);
    cprt = AE_LT16(vmh, vxh);
    AE_MOVT16X4(vmh, vxh, cprt);

	// UNROLL

	AE_LA16X4_IP(vxh, x_align, px);
	cprt = AE_LT16(vmh, vxh);
	AE_MOVT16X4(vmh, vxh, cprt);
  }
  if (N & 4) {
	  AE_LA16X4_IP(vxh, x_align, px);
	  cprt = AE_LT16(vmh, vxh);
	  AE_MOVT16X4(vmh, vxh, cprt);
  }

  AE_LA16X4_IP(vxh, x_align, px);
  AE_MOVF16X4(vxh, vzh, (xtbool4)(240>>(N&3)));
  cprt = AE_LT16(vmh, vxh);
  AE_MOVT16X4(vmh, vxh, cprt);

  vxh = AE_SEL16_4321(vmh, vmh);
  cprt = AE_LT16(vmh, vxh);
  AE_MOVT16X4(vmh, vxh, cprt);
  vxh = AE_SEL16_5432(vmh, vmh);
  cprt = AE_LT16(vmh, vxh);
  AE_MOVT16X4(vmh, vxh, cprt);

  return (int16_t)AE_MOVAD16_0(vmh);
}
