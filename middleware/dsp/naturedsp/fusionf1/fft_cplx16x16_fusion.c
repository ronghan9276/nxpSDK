/* ------------------------------------------------------------------------ */
/* Copyright (c) 2016 by Cadence Design Systems, Inc. ALL RIGHTS RESERVED.  */
/* These coded instructions, statements, and computer programs (�Cadence    */
/* Libraries�) are the copyrighted works of Cadence Design Systems Inc.	    */
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
/*          Copyright (C) 2015-2016 IntegrIT, Limited.                      */
/*                      All Rights Reserved.                                */
/* ------------------------------------------------------------------------ */
/*
	NatureDSP Signal Processing Library. FFT part
    C code optimized for Fusion
*/
/*===========================================================================
Fast Fourier Transforms:
fft_cplx             FFT on Complex Data
fft_real             FFT on Real Data
ifft_cplx            IFFT on Complex Data
ifft_real            Inverse FFT Forming Real Data
fft_cplx<prec>_ie    FFT on Complex Data with optimized memory usage
fft_real<prec>_ie    FFT on Real Data with optimized memory usage
ifft_cplx<prec>_ie   IFFT on Complex Data with optimized memory usage
ifft_real<prec>_ie   Inverse FFT Forming Real Data with optimized memory usage
dct                  Discrete Cosine Transform

There are limited combinations of precision and scaling options available:
----------------+---------------------------------------------------------------
FFT/IFFT        | Scaling options                        | Restrictions on the
                |                                        | input dynamic range
----------------+---------------------------------------------------------------
cplx24x24       | 0 � no scaling                         | input signal < 2^23/(2*N),
                |                                        | N-fft-size
real24x24       | 1 � 24-bit scaling                     |        none
                | 2 � 32-bit scaling on the first stage  |        none
                | and 24-bit scaling later               |        none
                | 3 � fixed scaling before each stage    |        none
------------------------------------------------------------------------------------
cplx32x16       | 3 � fixed scaling before each stage    |        none
cplx16x16       | 3 � fixed scaling before each stage    |        none
cplx32x16_ie    | 3 � fixed scaling before each stage    |        none
cplx24x24_ie    | 3 � fixed scaling before each stage    |        none
real32x16       | 3 � fixed scaling before each stage    |        none
real16x16       | 3 � fixed scaling before each stage    |        none
real32x16_ie    | 3 � fixed scaling before each stage    |        none
real24x24_ie    | 3 � fixed scaling before each stage    |        none
real32x16_ie_24p| 3 � fixed scaling before each stage    |        none
----------------+---------------------------------------------------------------
real24x24_ie_24p| 1 � 24-bit scaling                     |        none
----------------+---------------------------------------------------------------
DCT:            |
----------------+---------------------------------------------------------------
24x24	          | 0 � no scaling                         |        none
32x16	          | 0 � no scaling                         |        none
----------------+---------------------------------------------------------------

===========================================================================*/
#include "NatureDSP_Signal.h"
#include "common.h"
#include "fft_cplx_twiddles.h"

#define FIRST_STAGE_SCALE 3

#if !(XCHAL_HAVE_FUSION_16BIT_BASEBAND)

#define FFT_BUTTERFLY_R2(idx)              \
{                                          \
    vA1l = AE_L32X2_I(p_x0, 8);            \
    AE_L32X2_IP(vA0l,p_x0, 16);            \
    vB0l = AE_SEL32_HH(vA0l, vA1l);        \
    vB1l = AE_SEL32_LL(vA0l, vA1l);        \
    vA2s = AE_MOVINT16X4_FROMF32X2(vB0l);  \
    vA3s = AE_MOVINT16X4_FROMF32X2(vB1l);  \
    vA0s = AE_ADD16S(vA2s, vA3s);          \
    vA1s = AE_SUB16S(vA2s, vA3s);          \
    vA0l = AE_MOVINT32X2_FROMINT16X4(vA0s);\
    vA1l = AE_MOVINT32X2_FROMINT16X4(vA1s);\
    AE_S32_L_X(vA0l, p_y1, (idx));         \
    vA0l = AE_SEL32_LH(vA0l, vA0l);        \
    AE_S32_L_X(vA1l, p_y3, (idx));         \
    AE_S32_L_X(vA0l, p_y0, (idx));         \
    vA1l = AE_SEL32_LH(vA1l, vA1l);        \
    AE_S32_L_X(vA1l, p_y2, (idx));         \
}

#define FFT_BUTTERFLY_R4(idx)              \
{                                          \
    vA1l = AE_L32X2_I(p_x0, 8);            \
    AE_L32X2_IP(vA0l,p_x0, 16);            \
    vA2s = AE_MOVINT16X4_FROMF32X2(vA0l);  \
    vA3s = AE_MOVINT16X4_FROMF32X2(vA1l);  \
    vA0s = AE_ADD16S(vA2s, vA3s);          \
    vA1s = AE_SUB16S(vA2s, vA3s);          \
    vA2l=AE_MULC32X16_L(vA3l,vA1s);        \
    vB1s=AE_CVT16X4(vA2l,vA2l);            \
    vA2l=AE_MOVINT32X2_FROMINT16X4(vB1s);  \
    vA0l = AE_MOVINT32X2_FROMINT16X4(vA0s);\
    vA1l = AE_MOVINT32X2_FROMINT16X4(vA1s);\
    vA1l = AE_SEL32_HH(vA0l,vA1l);         \
    vA0l = AE_SEL32_LL(vA0l,vA2l);         \
    vA2s = AE_MOVINT16X4_FROMF32X2(vA1l);  \
    vA3s = AE_MOVINT16X4_FROMF32X2(vA0l);  \
    vA0s = AE_ADD16S(vA2s, vA3s);          \
    vA1s = AE_SUB16S(vA2s, vA3s);          \
    vA0l = AE_MOVINT32X2_FROMINT16X4(vA0s);\
    vA1l = AE_MOVINT32X2_FROMINT16X4(vA1s);\
    AE_S32_L_X(vA0l, p_y3, (idx));         \
    AE_S32_L_X(vA1l, p_y1, (idx));         \
    vA0l = AE_SEL32_LH(vA0l, vA0l);        \
    AE_S32_L_X(vA0l, p_y0, (idx));         \
    vA1l = AE_SEL32_LH(vA1l, vA1l);        \
    AE_S32_L_X(vA1l, p_y2, (idx));         \
}

#ifdef COMPILER_MSVC
#define MSC_ALIGNED ALIGN(8)
#define GCC_ALIGNED
#else
#define MSC_ALIGNED
#define GCC_ALIGNED ALIGN(8)
#endif

static const int16_t MSC_ALIGNED fft_twd_r8[12] GCC_ALIGNED = {
    (int16_t)0x7fff,(int16_t)0x0000,(int16_t)0x7fff,(int16_t)0x0000,
    (int16_t)0x7fff,(int16_t)0x0000,(int16_t)0x5a82,(int16_t)0xA57E,
    (int16_t)0x0000,(int16_t)0x8000,(int16_t)0xa57e,(int16_t)0xA57E
};

static int fft_core_s3(int16_t *y, int16_t *x, const tFftDescr *pDescr)
{
  int N;
  ae_int16x4  * restrict p4_x0, * restrict p4_x1,
              * restrict p4_x2, * restrict p4_x3;
  const ae_int16x4 * restrict p_twd;
  const ae_int16 * restrict p_inc;

  ae_int32 * restrict p_y0;
  ae_int32 * restrict p_y1;
  ae_int32 * restrict p_y2;
  ae_int32 * restrict p_y3;
  ae_int32x2 * restrict p_x0;

  ae_int16x4  vS;
  ae_int16x4  vA0s, vA1s, vA2s, vA3s, vB1s, vB2s, vB3s,
              vC1s, vC2s, vC3s, vT0s, vT1s, vT2s;
  ae_int32x2  vA0l, vA1l, vA2l, vA3l, vB0l, vB1l, vB2l, vB3l, vC0l, vC1l, vC2l, vC3l;
  const cint32_ptr * restrict seq;
  int step_circ;
  int stride,scale=0;

  {
    N=pDescr->N;
    p_inc = (const ae_int16 *)(pDescr->inc);
    seq=(const cint32_ptr * )pDescr->twd;
    p_twd = (const ae_int16x4 *)*seq++;
  }
  stride     =   N; // The stride is quartered with every iteration of the outer loop.

  if (stride > 4)
  { // first iteration for pre-scaling
    int lc = (N>>3)-1;

    p4_x0 = (ae_int16x4 *)x;
    p4_x1 = p4_x0 + (stride>>3);
    p4_x2 = p4_x1 + (stride>>3);
    p4_x3 = p4_x2 + (stride>>3);

    //-----------------------------------------------------------------
    // Set up offsets to access "N/4", "N/2", "3N/4" complex point or  
    // "N/2", "N", "3N/2" half word                                    
    //-----------------------------------------------------------------

    vA0s = AE_L16X4_I(p4_x0, 0);
    vA1s = AE_L16X4_I(p4_x1, 0);
    vA2s = AE_L16X4_I(p4_x2, 0);
    vA3s = AE_L16X4_I(p4_x3, 0);

    vA0s = AE_SRAI16(vA0s, FIRST_STAGE_SCALE);
    vA1s = AE_SRAI16(vA1s, FIRST_STAGE_SCALE);
    vA2s = AE_SRAI16(vA2s, FIRST_STAGE_SCALE);
    vA3s = AE_SRAI16(vA3s, FIRST_STAGE_SCALE);

    vB2s = AE_SUB16S(vA0s, vA2s);
    vB3s = AE_SUB16S(vA1s, vA3s);
    vA0s = AE_ADD16S(vA0s, vA2s);
    vA1s = AE_ADD16S(vA1s, vA3s);

    do
    {
      vT2s = AE_L16X4_I(p_twd, 16);
      vB1s = AE_SUB16S(vA0s, vA1s);
      vC3s = AE_ADD16S(vA0s, vA1s);
      vT1s = AE_L16X4_I(p_twd, 8);
      AE_L16X4_IP(vT0s, p_twd, 24);
      vC0l = AE_CVT32X2F16_32(vB1s);
      vC1l = AE_CVT32X2F16_10(vB1s);
      vC3s = AE_SRAI16(vC3s, 2);
      vC0l = AE_SRAI32(vC0l, 2);
      AE_S16X4_IP(vC3s, p4_x0, 8);
      vC0l = AE_MULFC32X16RAS_L(vC0l, vT0s);
      vC1l = AE_SRAI32(vC1l, 2);
      vA0s = AE_L16X4_I(p4_x0, 0);
      vB1l = AE_CVT32X2F16_32(vB3s);
      vC1l = AE_MULFC32X16RAS_H(vC1l, vT2s);
      vA2s = AE_L16X4_I(p4_x2, 8);
      vB0l = AE_CVT32X2F16_32(vB2s);
      vB1l = AE_SEL32_LH(vB1l, vB1l);
      vC1s = AE_ROUND16X4F32SASYM(vC0l, vC1l);
      vB3l = AE_CVT32X2F16_10(vB3s);
      vC0l = AE_SUBADD32S(vB0l, vB1l);
      vB3l = AE_SEL32_LH(vB3l, vB3l);
      vB2l = AE_CVT32X2F16_10(vB2s);
      vC1l = AE_ADDSUB32S(vB0l, vB1l);
      vA0s = AE_SRAI16(vA0s, FIRST_STAGE_SCALE);
      vC2l = AE_SUBADD32S(vB2l, vB3l);
      vA2s = AE_SRAI16(vA2s, FIRST_STAGE_SCALE);
      vC3l = AE_ADDSUB32S(vB2l, vB3l);
      vC0l = AE_SRAI32(vC0l, 2);
      vC0l = AE_MULFC32X16RAS_H(vC0l, vT1s);
      vC2l = AE_SRAI32(vC2l, 2);
      vA1s = AE_L16X4_I(p4_x1, 8);
      vC2l = AE_MULFC32X16RAS_L(vC2l, vT2s);
      vC1l = AE_SRAI32(vC1l, 2);
      vC1l = AE_MULFC32X16RAS_H(vC1l, vT0s);
      vC3l = AE_SRAI32(vC3l, 2);
      vC3l = AE_MULFC32X16RAS_L(vC3l, vT1s);
      vA1s = AE_SRAI16(vA1s, FIRST_STAGE_SCALE);
      vA3s = AE_L16X4_I(p4_x3, 8);
      vC2s = AE_ROUND16X4F32SASYM(vC0l, vC2l);
      vB2s = AE_SUB16S(vA0s, vA2s);
      vC3s = AE_ROUND16X4F32SASYM(vC1l, vC3l);
      AE_S16X4_IP(vC2s, p4_x3, 8);
      vA0s = AE_ADD16S(vA0s, vA2s);
      vA3s = AE_SRAI16(vA3s, FIRST_STAGE_SCALE);
      AE_S16X4_IP(vC1s, p4_x1, 8);
      AE_S16X4_IP(vC3s, p4_x2, 8);
      vB3s = AE_SUB16S(vA1s, vA3s);
      vA1s = AE_ADD16S(vA1s, vA3s);
    } while(--lc);
    // last iteration
    vT2s = AE_L16X4_I(p_twd, 16);
    vB1s = AE_SUB16S(vA0s, vA1s);
    vC3s = AE_ADD16S(vA0s, vA1s);
    vT1s = AE_L16X4_I(p_twd, 8);
    AE_L16X4_IP(vT0s, p_twd, 24);
    vC0l = AE_CVT32X2F16_32(vB1s);
    vC1l = AE_CVT32X2F16_10(vB1s);
    vC3s = AE_SRAI16(vC3s, 2);
    vC0l = AE_SRAI32(vC0l, 2);
    AE_S16X4_IP(vC3s, p4_x0, 8);
    vC0l = AE_MULFC32X16RAS_L(vC0l, vT0s);
    vC1l = AE_SRAI32(vC1l, 2);
    vB1l = AE_CVT32X2F16_32(vB3s);
    vC1l = AE_MULFC32X16RAS_H(vC1l, vT2s);
    vB0l = AE_CVT32X2F16_32(vB2s);
    vB1l = AE_SEL32_LH(vB1l, vB1l);
    vC1s = AE_ROUND16X4F32SASYM(vC0l, vC1l);
    vB3l = AE_CVT32X2F16_10(vB3s);
    vC0l = AE_SUBADD32S(vB0l, vB1l);
    vB3l = AE_SEL32_LH(vB3l, vB3l);
    vB2l = AE_CVT32X2F16_10(vB2s);
    vC1l = AE_ADDSUB32S(vB0l, vB1l);
    vA0s = AE_SRAI16(vA0s, FIRST_STAGE_SCALE);
    vC2l = AE_SUBADD32S(vB2l, vB3l);
    vA2s = AE_SRAI16(vA2s, FIRST_STAGE_SCALE);
    vC3l = AE_ADDSUB32S(vB2l, vB3l);
    vC0l = AE_SRAI32(vC0l, 2);
    vC0l = AE_MULFC32X16RAS_H(vC0l, vT1s);
    vC2l = AE_SRAI32(vC2l, 2);
    vC2l = AE_MULFC32X16RAS_L(vC2l, vT2s);
    vC1l = AE_SRAI32(vC1l, 2);
    vC1l = AE_MULFC32X16RAS_H(vC1l, vT0s);
    vC3l = AE_SRAI32(vC3l, 2);
    vC3l = AE_MULFC32X16RAS_L(vC3l, vT1s);
    vA1s = AE_SRAI16(vA1s, FIRST_STAGE_SCALE);
    vC2s = AE_ROUND16X4F32SASYM(vC0l, vC2l);
    vC3s = AE_ROUND16X4F32SASYM(vC1l, vC3l);
    AE_S16X4_IP(vC2s, p4_x3, 8);
    vA3s = AE_SRAI16(vA3s, FIRST_STAGE_SCALE);
    AE_S16X4_IP(vC1s, p4_x1, 8);
    AE_S16X4_IP(vC3s, p4_x2, 8);

    scale += 2;
    stride  >>= 2;
  }

  while (stride > 8) 
  {
    int lc = N>>4;
    int step;

    p4_x0 = (ae_int16x4 *)x;
    p4_x1 = p4_x0 + (stride>>3);
    p4_x2 = p4_x1 + (stride>>3);
    p4_x3 = p4_x2 + (stride>>3);

    //-----------------------------------------------------------------
    // Set up offsets to access "N/4", "N/2", "3N/4" complex point or  
    // "N/2", "N", "3N/2" half word                                    
    //-----------------------------------------------------------------
    vA0s = AE_L16X4_I(p4_x0, 0);
    vA1s = AE_L16X4_I(p4_x1, 0);
    vA2s = AE_L16X4_I(p4_x2, 0);
    vA3s = AE_L16X4_I(p4_x3, 0);

    vB2s = AE_SUB16S(vA0s, vA2s);
    vB3s = AE_SUB16S(vA1s, vA3s);
    vA0s = AE_ADD16S(vA0s, vA2s);
    vA1s = AE_ADD16S(vA1s, vA3s);

    p_twd=(const ae_int16x4 *)(*seq++);
    WUR_AE_CBEGIN0( (uintptr_t)p_twd );
    WUR_AE_CEND0  ( (uintptr_t)(p_twd)+stride*3 );
    step_circ=24;

    do
    {
      AE_L16_IP(vS, p_inc, 2);
      vS = AE_SLAI16S(vS, 1);
      step = AE_MOVAD16_0(vS)+4;
      vT2s = AE_L16X4_I(p_twd, 16);
      vB1s = AE_SUB16S(vA0s, vA1s);
      vC3s = AE_ADD16S(vA0s, vA1s);
      vT1s = AE_L16X4_I(p_twd, 8);
      AE_L16X4_XC(vT0s, p_twd, step_circ);
      vC0l = AE_CVT32X2F16_32(vB1s);
      vC1l = AE_CVT32X2F16_10(vB1s);
      vC3s = AE_SRAI16(vC3s, 2);
      vC0l = AE_SRAI32(vC0l, 2);
      AE_S16X4_IP(vC3s, p4_x0, 8);
      vC0l = AE_MULFC32X16RAS_L(vC0l, vT0s);
      vC1l = AE_SRAI32(vC1l, 2);
      vA0s = AE_L16X4_I(p4_x0, 0);
      vB1l = AE_CVT32X2F16_32(vB3s);
      vC1l = AE_MULFC32X16RAS_H(vC1l, vT2s);
      vA2s = AE_L16X4_I(p4_x2, 8);
      vB0l = AE_CVT32X2F16_32(vB2s);
      vB1l = AE_SEL32_LH(vB1l, vB1l);
      vC1s = AE_ROUND16X4F32SASYM(vC0l, vC1l);
      vB3l = AE_CVT32X2F16_10(vB3s);
      vC0l = AE_SUBADD32S(vB0l, vB1l);
      vB3l = AE_SEL32_LH(vB3l, vB3l);
      vB2l = AE_CVT32X2F16_10(vB2s);
      vC1l = AE_ADDSUB32S(vB0l, vB1l);
      vC2l = AE_SUBADD32S(vB2l, vB3l);
      vC3l = AE_ADDSUB32S(vB2l, vB3l);
      vC0l = AE_SRAI32(vC0l, 2);
      vC0l = AE_MULFC32X16RAS_H(vC0l, vT1s);
      vC2l = AE_SRAI32(vC2l, 2);
      vA1s = AE_L16X4_I(p4_x1, 8);
      vC2l = AE_MULFC32X16RAS_L(vC2l, vT2s);
      vC1l = AE_SRAI32(vC1l, 2);
      vC1l = AE_MULFC32X16RAS_H(vC1l, vT0s);
      vC3l = AE_SRAI32(vC3l, 2);
      vC3l = AE_MULFC32X16RAS_L(vC3l, vT1s);
      vA3s = AE_L16X4_I(p4_x3, 8);
      vC2s = AE_ROUND16X4F32SASYM(vC0l, vC2l);
      vB2s = AE_SUB16S(vA0s, vA2s);
      vC3s = AE_ROUND16X4F32SASYM(vC1l, vC3l);
      AE_S16X4_IP(vC2s, p4_x3, 8);
      vA0s = AE_ADD16S(vA0s, vA2s);
      AE_S16X4_IP(vC1s, p4_x1, 8);
      AE_S16X4_IP(vC3s, p4_x2, 8);
      vB3s = AE_SUB16S(vA1s, vA3s);
      vA1s = AE_ADD16S(vA1s, vA3s);

      vT2s = AE_L16X4_I(p_twd, 16);
      vB1s = AE_SUB16S(vA0s, vA1s);
      vC3s = AE_ADD16S(vA0s, vA1s);
      vT1s = AE_L16X4_I(p_twd, 8);
      AE_L16X4_XC(vT0s, p_twd, step_circ);
      vC0l = AE_CVT32X2F16_32(vB1s);
      vC1l = AE_CVT32X2F16_10(vB1s);
      vC3s = AE_SRAI16(vC3s, 2);
      vC0l = AE_SRAI32(vC0l, 2);
      AE_S16X4_XP(vC3s, p4_x0, step);
      vC0l = AE_MULFC32X16RAS_L(vC0l, vT0s);
      vC1l = AE_SRAI32(vC1l, 2);
      vA0s = AE_L16X4_I(p4_x0, 0);
      vB1l = AE_CVT32X2F16_32(vB3s);
      vC1l = AE_MULFC32X16RAS_H(vC1l, vT2s);
      vA2s = AE_L16X4_X(p4_x2, step);
      vB0l = AE_CVT32X2F16_32(vB2s);
      vB1l = AE_SEL32_LH(vB1l, vB1l);
      vC1s = AE_ROUND16X4F32SASYM(vC0l, vC1l);
      vB3l = AE_CVT32X2F16_10(vB3s);
      vC0l = AE_SUBADD32S(vB0l, vB1l);
      vB3l = AE_SEL32_LH(vB3l, vB3l);
      vB2l = AE_CVT32X2F16_10(vB2s);
      vC1l = AE_ADDSUB32S(vB0l, vB1l);
      vC2l = AE_SUBADD32S(vB2l, vB3l);
      vC3l = AE_ADDSUB32S(vB2l, vB3l);
      vC0l = AE_SRAI32(vC0l, 2);
      vC0l = AE_MULFC32X16RAS_H(vC0l, vT1s);
      vC2l = AE_SRAI32(vC2l, 2);
      vA1s = AE_L16X4_X(p4_x1, step);
      vC2l = AE_MULFC32X16RAS_L(vC2l, vT2s);
      vC1l = AE_SRAI32(vC1l, 2);
      vC1l = AE_MULFC32X16RAS_H(vC1l, vT0s);
      vC3l = AE_SRAI32(vC3l, 2);
      vC3l = AE_MULFC32X16RAS_L(vC3l, vT1s);
      vA3s = AE_L16X4_X(p4_x3, step);
      vC2s = AE_ROUND16X4F32SASYM(vC0l, vC2l);
      vB2s = AE_SUB16S(vA0s, vA2s);
      vC3s = AE_ROUND16X4F32SASYM(vC1l, vC3l);
      AE_S16X4_XP(vC2s, p4_x3, step);
      vA0s = AE_ADD16S(vA0s, vA2s);
      AE_S16X4_XP(vC1s, p4_x1, step);
      AE_S16X4_XP(vC3s, p4_x2, step);
      vB3s = AE_SUB16S(vA1s, vA3s);
      vA1s = AE_ADD16S(vA1s, vA3s);
    } while(--lc);

    scale += 2;
    stride >>= 2;
  }

  if (stride==8) 
  {
    int lc = (N>>3)-1;

    p4_x0 = (ae_int16x4 *)x;
    p4_x1 = p4_x0 + (stride>>3);
    p4_x2 = p4_x1 + (stride>>3);
    p4_x3 = p4_x2 + (stride>>3);

    //-----------------------------------------------------------------
    // Set up offsets to access "N/4", "N/2", "3N/4" complex point or  
    // "N/2", "N", "3N/2" half word                                    
    //-----------------------------------------------------------------
    vA0s = AE_L16X4_I(p4_x0, 0);
    vA1s = AE_L16X4_I(p4_x1, 0);
    vA2s = AE_L16X4_I(p4_x2, 0);
    vA3s = AE_L16X4_I(p4_x3, 0);

    vB2s = AE_SUB16S(vA0s, vA2s);
    vB3s = AE_SUB16S(vA1s, vA3s);
    vA0s = AE_ADD16S(vA0s, vA2s);
    vA1s = AE_ADD16S(vA1s, vA3s);

    vT0s = AE_L16X4_I(((const ae_int16x4*)fft_twd_r8), 0);
    vT1s = AE_L16X4_I(((const ae_int16x4*)fft_twd_r8), 8);
    vT2s = AE_L16X4_I(((const ae_int16x4*)fft_twd_r8), 16);

    do
    {
      vB1s = AE_SUB16S(vA0s, vA1s);
      vC3s = AE_ADD16S(vA0s, vA1s);
      vC0l = AE_CVT32X2F16_32(vB1s);
      vC1l = AE_CVT32X2F16_10(vB1s);
      vC3s = AE_SRAI16(vC3s, 1);
      vC0l = AE_SRAI32(vC0l, 1);
      AE_S16X4_IP(vC3s, p4_x0, 32);
      vC0l = AE_MULFC32X16RAS_L(vC0l, vT0s);
      vC1l = AE_SRAI32(vC1l, 1);
      vA0s = AE_L16X4_I(p4_x0, 0);
      vB1l = AE_CVT32X2F16_32(vB3s);
      vC1l = AE_MULFC32X16RAS_H(vC1l, vT2s);
      vA2s = AE_L16X4_I(p4_x2, 32);
      vB0l = AE_CVT32X2F16_32(vB2s);
      vB1l = AE_SEL32_LH(vB1l, vB1l);
      vC1s = AE_ROUND16X4F32SASYM(vC0l, vC1l);
      vB3l = AE_CVT32X2F16_10(vB3s);
      vC0l = AE_SUBADD32S(vB0l, vB1l);
      vB3l = AE_SEL32_LH(vB3l, vB3l);
      vB2l = AE_CVT32X2F16_10(vB2s);
      vC1l = AE_ADDSUB32S(vB0l, vB1l);
      vC2l = AE_SUBADD32S(vB2l, vB3l);
      vC3l = AE_ADDSUB32S(vB2l, vB3l);
      vC0l = AE_SRAI32(vC0l, 1);
      vC0l = AE_MULFC32X16RAS_H(vC0l, vT1s);
      vC2l = AE_SRAI32(vC2l, 1);
      vA1s = AE_L16X4_I(p4_x1, 32);
      vC2l = AE_MULFC32X16RAS_L(vC2l, vT2s);
      vC1l = AE_SRAI32(vC1l, 1);
      vC1l = AE_MULFC32X16RAS_H(vC1l, vT0s);
      vC3l = AE_SRAI32(vC3l, 1);
      vC3l = AE_MULFC32X16RAS_L(vC3l, vT1s);
      vA3s = AE_L16X4_I(p4_x3, 32);
      vC2s = AE_ROUND16X4F32SASYM(vC0l, vC2l);
      vB2s = AE_SUB16S(vA0s, vA2s);
      vC3s = AE_ROUND16X4F32SASYM(vC1l, vC3l);
      AE_S16X4_XP(vC2s, p4_x3, 32);
      vA0s = AE_ADD16S(vA0s, vA2s);
      AE_S16X4_IP(vC1s, p4_x1, 32);
      AE_S16X4_IP(vC3s, p4_x2, 32);
      vB3s = AE_SUB16S(vA1s, vA3s);
      vA1s = AE_ADD16S(vA1s, vA3s);
    } while(--lc);
    vB1s = AE_SUB16S(vA0s, vA1s);
    vC3s = AE_ADD16S(vA0s, vA1s);
    vC0l = AE_CVT32X2F16_32(vB1s);
    vC1l = AE_CVT32X2F16_10(vB1s);
    vC3s = AE_SRAI16(vC3s, 1);
    vC0l = AE_SRAI32(vC0l, 1);
    AE_S16X4_IP(vC3s, p4_x0, 32);
    vC0l = AE_MULFC32X16RAS_L(vC0l, vT0s);
    vC1l = AE_SRAI32(vC1l, 1);
    vB1l = AE_CVT32X2F16_32(vB3s);
    vC1l = AE_MULFC32X16RAS_H(vC1l, vT2s);
    vB0l = AE_CVT32X2F16_32(vB2s);
    vB1l = AE_SEL32_LH(vB1l, vB1l);
    vC1s = AE_ROUND16X4F32SASYM(vC0l, vC1l);
    vB3l = AE_CVT32X2F16_10(vB3s);
    vC0l = AE_SUBADD32S(vB0l, vB1l);
    vB3l = AE_SEL32_LH(vB3l, vB3l);
    vB2l = AE_CVT32X2F16_10(vB2s);
    vC1l = AE_ADDSUB32S(vB0l, vB1l);
    vC2l = AE_SUBADD32S(vB2l, vB3l);
    vC3l = AE_ADDSUB32S(vB2l, vB3l);
    vC0l = AE_SRAI32(vC0l, 1);
    vC0l = AE_MULFC32X16RAS_H(vC0l, vT1s);
    vC2l = AE_SRAI32(vC2l, 1);
    vC2l = AE_MULFC32X16RAS_L(vC2l, vT2s);
    vC1l = AE_SRAI32(vC1l, 1);
    vC1l = AE_MULFC32X16RAS_H(vC1l, vT0s);
    vC3l = AE_SRAI32(vC3l, 1);
    vC3l = AE_MULFC32X16RAS_L(vC3l, vT1s);
    vC2s = AE_ROUND16X4F32SASYM(vC0l, vC2l);
    vC3s = AE_ROUND16X4F32SASYM(vC1l, vC3l);
    AE_S16X4_XP(vC2s, p4_x3, 32);
    AE_S16X4_IP(vC1s, p4_x1, 32);
    AE_S16X4_IP(vC3s, p4_x2, 32);
    scale += 1;
    stride >>= 2;
  }

    {
        p_y0=(ae_int32 *)(y);
        p_y1=(ae_int32 *)(p_y0 + (N >> 2));
        p_y2=(ae_int32 *)(p_y1 + (N >> 2));
        p_y3=(ae_int32 *)(p_y2 + (N >> 2));         
        p_x0=(ae_int32x2 *)(x);
        int i;
        int32_t i0,i1,i2,i3,ai;
        i = AE_NSAZ32_L(N)+2;
        ai=((int32_t)0x1)<<i;
        i0=0;
        if (stride==2) 
        {
            //--------------------------------------------------------------------------
            // last stage is RADIX2 !!!
            //--------------------------------------------------------------------------
            for (i = 0; i < (N>>4); i++) 
            {
                i1 = AE_ADDBRBA32(i0, ai);
                i2 = AE_ADDBRBA32(i1, ai);
                i3 = AE_ADDBRBA32(i2, ai);
                FFT_BUTTERFLY_R2(i0);
                FFT_BUTTERFLY_R2(i1);
                FFT_BUTTERFLY_R2(i2);
                FFT_BUTTERFLY_R2(i3);
                i0 = AE_ADDBRBA32(i3, ai);
            }
        } 
        else 
        {
            vA3l=AE_MOVDA32X2(0,0xFFFFFFFF);
            //--------------------------------------------------------------------------
            // last stage is RADIX4 !!!
            //--------------------------------------------------------------------------
           for (i = 0; i < (N>>4); i++) 
           {
                NASSERT_ALIGN8(p_y0);
                NASSERT_ALIGN8(p_y1);
                NASSERT_ALIGN8(p_y2);
                NASSERT_ALIGN8(p_y3);
                i1 = AE_ADDBRBA32(i0, ai);
                i2 = AE_ADDBRBA32(i1, ai);
                i3 = AE_ADDBRBA32(i2, ai);
                NASSERT_ALIGN8(p_x0);
                FFT_BUTTERFLY_R4(i0);
                FFT_BUTTERFLY_R4(i1);
                FFT_BUTTERFLY_R4(i2);
                FFT_BUTTERFLY_R4(i3);
                i0 = AE_ADDBRBA32(i3, ai);
            }
        }
    }

  return scale;
}
#endif

#if (XCHAL_HAVE_FUSION_16BIT_BASEBAND)

inline_ void DFT4x2(
    ae_int16x4 *x0,
    ae_int16x4 *x1,
    ae_int16x4 *x2,
    ae_int16x4 *x3)
{

    ae_int16x4 s0, s1, d0, d1;

    s0 = AE_ADD16S(*x0, *x2);
    s1 = AE_ADD16S(*x1, *x3);
    d0 = AE_SUB16S(*x0, *x2);
    d1 = AE_SUB16S(*x1, *x3);

    d1 = AE_MOVINT16X4_FROMF16X4(AE_MUL16JS(AE_MOVF16X4_FROMINT16X4(d1))); 

    *x0 = AE_ADD16S(s0, s1);
    *x1 = AE_SUB16S(d0, d1); 
    *x2 = AE_SUB16S(s0, s1);
    *x3 = AE_ADD16S(d0, d1);
}



inline_ void MULCx2(ae_int16x4 *x, const ae_int16x4 *t)
{
    ae_f16x4 f;
    f = AE_MULFC16RAS_L(AE_MOVF16X4_FROMINT16X4(*x), AE_MOVF16X4_FROMINT16X4(*t));
    AE_MULFC16RAS_H(f, AE_MOVF16X4_FROMINT16X4(*x), AE_MOVF16X4_FROMINT16X4(*t));
    *x = AE_MOVINT16X4_FROMF16X4(f);
}


 static void stage_first_DFT4xI2ss(int16_t *x, int16_t *y, int16_t *twd, int N)
 {
     ae_int16x4 * restrict px = (ae_int16x4 *)x;
     ae_int16x4 * restrict py = (ae_int16x4 *)y;
     ae_int32x2 * restrict ptw32x2 = (ae_int32x2 *)twd;
     ae_int32x2 r1, r2, r3;
     int stride = N / 4 * sizeof(int16_t) * 2;
     int i = N >> 3;
     ae_int16x4 y0, y1, y2, y3;
     ae_int16x4 x0, x1, x2, x3;
     ae_int16x4 w1, w2, w3;
     /*20 cycles per pipeline stage in steady state with unroll=1 */
     do
     {
         x1 = AE_L16X4_X(px, stride);
         x3 = AE_L16X4_X(px, stride * 3);
         x2 = AE_L16X4_X(px, stride * 2);
         AE_L16X4_XP(x0, px, 8);

         x1 = AE_SRAI16(x1, FIRST_STAGE_SCALE);
         x3 = AE_SRAI16(x3, FIRST_STAGE_SCALE);
         x2 = AE_SRAI16(x2, FIRST_STAGE_SCALE);
         x0 = AE_SRAI16(x0, FIRST_STAGE_SCALE);

         DFT4x2(&x0, &x1, &x2, &x3);

         /* Use AE_L32X2_XP for reading twiddles ! */
         AE_L32X2_XP(r1, ptw32x2, 8); 
         AE_L32X2_XP(r2, ptw32x2, 8);
         AE_L32X2_XP(r3, ptw32x2, 8);

         w1 = AE_MOVINT16X4_FROMF32X2(r1);
         w2 = AE_MOVINT16X4_FROMF32X2(r2);
         w3 = AE_MOVINT16X4_FROMF32X2(r3);

         MULCx2(&x1, &w1);
         MULCx2(&x2, &w2); 
         MULCx2(&x3, &w3);

         x1 = AE_SRAA16RS(x1, 2);
         x3 = AE_SRAA16RS(x3, 2);
         x2 = AE_SRAA16RS(x2, 2);
         x0 = AE_SRAA16RS(x0, 2);

         y0 = AE_SEL16_7632(x0, x1);
         y1 = AE_SEL16_7632(x2, x3);
         y2 = AE_SEL16_5410(x0, x1);
         y3 = AE_SEL16_5410(x2, x3);

         AE_S16X4_IP(y0, py, 8);
         AE_S16X4_IP(y1, py, 8);
         AE_S16X4_IP(y2, py, 8);
         AE_S16X4_IP(y3, py, 8);

     } while (--i);
 }



 static void stage_last_DFT4xI2ss(int16_t *x, int16_t *y, int N)
 {
     ae_int16x4 * restrict px = (ae_int16x4 *)x;
     ae_int16x4 * restrict py = (ae_int16x4 *)y;

     int stride = N / 4 * sizeof(int16_t) * 2;
     int i = N >> 3;


     ae_int16x4 x0, x1, x2, x3;

     /* 9 cycles per pipeline stage in steady state with unroll=1*/
     do
     {


         x1 = AE_L16X4_X(px, stride);
         x3 = AE_L16X4_X(px, stride * 3);
         x2 = AE_L16X4_X(px, stride * 2);
         AE_L16X4_XP(x0, px, 8);

         DFT4x2(&x0, &x1, &x2, &x3);

         AE_S16X4_X(x1, py, stride);
         AE_S16X4_X(x3, py, stride * 3);
         AE_S16X4_X(x2, py, stride * 2);
         AE_S16X4_XP(x0, py, 8);

     } while (--i);
 }


 static void stage_last_DFT2xI2ss(int16_t *x, int16_t *y, int N)
 {
     ae_int16x4 * restrict px = (ae_int16x4 *)x;
     ae_int16x4 * restrict py = (ae_int16x4 *)y;
     int stride = N / 2 * sizeof(int16_t) * 2;
     int i = N >> 2;
     ae_int16x4 x0, x1, x2, x3;

     do
     {

         x1 = AE_L16X4_X(px, stride);
         AE_L16X4_XP(x0, px, 8);

         x2 = AE_ADD16S(x0, x1); 
         x3 = AE_SUB16S(x0, x1); 


         AE_S16X4_X(x3, py, stride);
         AE_S16X4_XP(x2, py, 8);

     } while (--i);
 }

 static void stage_inner_DFT4xI2ss(int16_t *x, int16_t *y, const int16_t *twd, int N, int stride, int shift)
 {
     ae_int16x4 * restrict px = (ae_int16x4 *)x;
     ae_int16x4 * restrict py = (ae_int16x4 *)y;
     ae_int32x2 * restrict ptw32x2 = (ae_int32x2 *)twd;
     
     int M = 1<<(XT_NSA(stride) - XT_NSA(N)); // (N / stride);
     int twstep = 6 * M * sizeof(int16_t);
     int i;
     int j;

     ae_int16x4 x0, x1, x2, x3;
     ae_int32x2 t1, t2, t3;
     ae_int16x4 w1, w2, w3;

     if (M / 2 > stride / 4)
     {
         // Good for large M
         __Pragma("loop_count min=2");
         for (i = 0; i < stride / 4; i++)
         {

             AE_L32_IP(t1, castxcc(const ae_int32,ptw32x2), 8);
             AE_L32_IP(t2, castxcc(const ae_int32,ptw32x2), 8);
             AE_L32_XP(t3, castxcc(const ae_int32,ptw32x2), twstep - 2 * 8);

             w1 = AE_MOVINT16X4_FROMINT32X2(t1);
             w2 = AE_MOVINT16X4_FROMINT32X2(t2);
             w3 = AE_MOVINT16X4_FROMINT32X2(t3);
             /* 15 cycles per pipeline stage in steady state with unroll=1 */
             __Pragma("loop_count min=2");
             for (j = 0; j < M / 2; j++)
             {

                 x1 = AE_L16X4_X(px, N * 1);
                 x2 = AE_L16X4_X(px, N * 2);
                 x3 = AE_L16X4_X(px, N * 3);
                 AE_L16X4_IP(x0, px, sizeof(x0));


                 DFT4x2(&x0, &x1, &x2, &x3);

                 MULCx2(&x1, &w1);
                 MULCx2(&x2, &w2);
                 MULCx2(&x3, &w3);

                 x1 = AE_SRAA16RS(x1, shift);
                 x3 = AE_SRAA16RS(x3, shift);
                 x2 = AE_SRAA16RS(x2, shift);
                 x0 = AE_SRAA16RS(x0, shift);

                 AE_S16X4_XP(x0, py, M * 4);
                 AE_S16X4_XP(x1, py, M * 4);
                 AE_S16X4_XP(x2, py, M * 4);
                 AE_S16X4_XP(x3, py, 8 - 3 * M * 4);
             }
             py = (ae_int16x4 *)(M * 16 - 8*M/2 + (uintptr_t)py);
         }
     }
     else //if (M / 2 > stride / 4)
     {
         WUR_AE_CBEGIN0((unsigned)ptw32x2); 
         WUR_AE_CEND0( N/4*3*2*sizeof(int16_t) + (uintptr_t)ptw32x2);
//VVVVVVVVVVVVVVVV Best for small M VVVVVVVVVVVVVVVVVVVVVVVvv
         __Pragma("loop_count min=2");
         for (j = 0; j < M / 2; j++)
         {
             /* 15 cycles per pipeline stage in steady state with unroll=1 */
             __Pragma("loop_count min=2");
             for (i = 0; i < stride / 4; i++)
             {
                 AE_L32_IP(t1, castxcc(const ae_int32,ptw32x2), 8);
                 AE_L32_IP(t2, castxcc(const ae_int32,ptw32x2), 8);
                 AE_L32_XC(t3, castxcc(const ae_int32,ptw32x2), twstep - 2 * 8);

                 w1 = AE_MOVINT16X4_FROMINT32X2(t1);
                 w2 = AE_MOVINT16X4_FROMINT32X2(t2);
                 w3 = AE_MOVINT16X4_FROMINT32X2(t3);
#if 0
                 x1 = AE_L16X4_X(px, (j + i*M/2)*sizeof(*px)     + N * 1);
                 x2 = AE_L16X4_X(px, (j + i*M/2)*sizeof(*px) + N * 2);
                 x3 = AE_L16X4_X(px, (j + i*M/2)*sizeof(*px) + N * 3);
                 x0 = AE_L16X4_X(px, (j + i*M / 2)*sizeof(*px) + N * 0);
#else
                 x1 = AE_L16X4_X(px, N * 1);
                 x2 = AE_L16X4_X(px, N * 2);
                 x3 = AE_L16X4_X(px, N * 3);
                 AE_L16X4_XP(x0, px, (M / 2)*sizeof(*px));
#endif

                 DFT4x2(&x0, &x1, &x2, &x3);

                 MULCx2(&x1, &w1);
                 MULCx2(&x2, &w2);
                 MULCx2(&x3, &w3);

                 x1 = AE_SRAA16RS(x1, shift);
                 x3 = AE_SRAA16RS(x3, shift);
                 x2 = AE_SRAA16RS(x2, shift);
                 x0 = AE_SRAA16RS(x0, shift);
#if 1
                 AE_S16X4_X(x1, py, 1 * M * 4);
                 AE_S16X4_X(x2, py, 2 * M * 4);
                 AE_S16X4_X(x3, py, 3 * M * 4);
                 AE_S16X4_XP(x0, py, M * 16);
#else
                 AE_S16X4_X(x0, py, M * 16 * i + j * 8 + 0 * M * 4);
                 AE_S16X4_X(x1, py, M * 16 * i + j * 8 + 1 * M * 4);
                 AE_S16X4_X(x2, py, M * 16 * i + j * 8 + 2 * M * 4);
                 AE_S16X4_X(x3, py, M * 16 * i + j * 8 + 3 * M * 4);
#endif
             }
             px += 1 - stride / 4 * (M / 2);
             py += 1 - stride / 4 * (M * 2);
         }

     } //if if (M / 2 > stride / 4) else..
 }




#define SWAP_PTR(_x, _y)\
{ \
    int16_t *tmp = _x; \
    _x = _y; _y = tmp; \
}
#endif
/*-------------------------------------------------------------------------
  These functions make FFT on complex data.
  NOTES:
  1. Bit-reversing permutation is done here. 
  2. FFT runs in-place algorithm so INPUT DATA WILL APPEAR DAMAGED after 
     the call

  Precision: 
  32x32  32-bit input/outputs, 32-bit twiddles
  24x24  24-bit input/outputs, 24-bit twiddles
  32x16  32-bit input/outputs, 16-bit twiddles
  16x16  16-bit input/outputs, 16-bit twiddles
 
  Input:
  x[2*N]     complex input signal. Real and imaginary data are interleaved 
             and real data goes first
  N          FFT size
  scalingOpt scaling option
  Output:
  y[2*N]     output spectrum. Real and imaginary data are interleaved and 
             real data goes first

  Returned value: total number of right shifts occurred during scaling 
                  procedure

  Restrictions:
  x,y should not overlap
  x,y - aligned on a 8-bytes boundary
  N   - 2^m, 16...4096

-------------------------------------------------------------------------*/
int fft_cplx16x16( int16_t* y,int16_t* x,fft_handle_t h,int scalingOption)
#if !(XCHAL_HAVE_FUSION_16BIT_BASEBAND)
{
    /* no Quad MAC option */
  int scale=0;

  NASSERT_ALIGN8(x);
  NASSERT_ALIGN8(y);
  NASSERT(scalingOption==3);

  scale=FIRST_STAGE_SCALE;
  scale+=fft_core_s3 (y, x, (const tFftDescr*)h);

  return scale;
}
#else
{
    /* with Quad MAC option */
    int N;
    const tFftDescr *pDescr = (const tFftDescr*)h;
    const ae_int16x4 * restrict p_twd;
    int stride, scale = 3;

    NASSERT_ALIGN8(x);
    NASSERT_ALIGN8(y);
    NASSERT(scalingOption == 3);

    N = pDescr->N;
    p_twd = (const ae_int16x4 *)pDescr->twd;
    stride = N; // The stride is quartered with every iteration of the outer loop.

    int16_t *ptr_in = x; 
    int16_t *ptr_out = y; 

    stage_first_DFT4xI2ss(ptr_in, ptr_out, (int16_t*)p_twd, N);
    scale += 2;
    stride >>= 2;

    SWAP_PTR(ptr_in, ptr_out); 
      
    while (stride > 8)
    {
        stage_inner_DFT4xI2ss(ptr_in, ptr_out, (const int16_t*)p_twd, N, stride, 2);
        SWAP_PTR(ptr_in, ptr_out); 
        scale += 2;
        stride >>= 2;
    }

    if (stride > 4)
    {        
        stage_inner_DFT4xI2ss(ptr_in, ptr_out, (const int16_t*)p_twd, N, stride, 1);
        SWAP_PTR(ptr_in, ptr_out);
        scale += 1;
        stride >>= 2;
    }

    if (ptr_in == y)
    {
        ptr_out = ptr_in; 
    }

    if (stride == 4)
    {
        stage_last_DFT4xI2ss(ptr_in, ptr_out, N);
    }
    else
    {
        stage_last_DFT2xI2ss(ptr_in, ptr_out, N);
    }
    return scale;
}
#endif
