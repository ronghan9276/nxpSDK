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

/* DSP Library API */
#include "NatureDSP_Signal_math.h"
/* Common helper macros. */
#include "common_fpu.h"
/* Tables */
#include "log2f_tbl.h"
#include "sqrt2f_tbl.h"
/* +/-Infinity, single precision */
#include "inff_tbl.h"
/* sNaN/qNaN, single precision. */
#include "nanf_tbl.h"

#if !HAVE_VFPU && !HAVE_FPU
DISCARD_FUN(void,vec_log2f,( float32_t * restrict y, const float32_t * restrict x, int N ))
#elif HAVE_VFPU
#define sz_i32  (int)sizeof(int32_t)
#define sz_f32  (int)sizeof(float32_t)

/*===========================================================================
  Vector matematics:
  vec_log              Logarithm
  ===========================================================================*/

/*-------------------------------------------------------------------------
  Logarithm:
  Different kinds of logarithm (base 2, natural, base 10). Fixed point 
  functions represent results in Q25 format or return 0x80000000 on negative 
  of zero input.

  Precision:
  32x32  32-bit inputs, 32-bit outputs
  f      floating point

  Accuracy :
  vec_log2_32x32,scl_log2_32x32              730 (2.2e-5)
  vec_logn_32x32,scl_logn_32x32              510 (1.5e-5)
  vec_log10_32x32,scl_log10_32x32            230 (6.9e-6)
  floating point                             2 ULP

  NOTES:
  1.  Although 32 and 24 bit functions provide the same accuracy, 32-bit 
      functions have better input/output resolution (dynamic range)
  2.  Scalar Floating point functions are compatible with standard ANSI C routines 
      and set errno and exception flags accordingly.
  3.  Floating point functions limit the range of allowable input values:
      A) If x<0, the result is set to NaN. In addition, scalar floating point
         functions assign the value EDOM to errno and raise the "invalid" 
         floating-point exception.
      B) If x==0, the result is set to minus infinity. Scalar floating  point
         functions assign the value ERANGE to errno and raise the "divide-by-zero"
         floating-point exception.

  Input:
  x[N]  input data, Q16.15 or floating point 
  N     length of vectors
  Output:
  y[N]  result, Q25 or floating point 

  Restriction:
  x,y should not overlap

  Scalar versions:
  ----------------
  return result in Q25 or floating point
-------------------------------------------------------------------------*/

void vec_log2f(float32_t * restrict y,const float32_t * restrict x,int N)
{
  /*
   * Reference C code for a scalar variant:
   *
   * float32_t y;
   * int e;
   *
   * if ( x<0           ) return ( qNaNf.f     );
   * if ( x==0          ) return ( minusInff.f );
   * if ( x==plusInff.f ) return ( x           );
   *
   * x=frexpf(x,&e);
   * if(x<sqrt0_5f.f) { x=x*2; e--; }
   *
   * x=1.0f-x;
   * y=log2f_tbl[0].f;
   * y=log2f_tbl[1].f+x*y;
   * y=log2f_tbl[2].f+x*y;
   * y=log2f_tbl[3].f+x*y;
   * y=log2f_tbl[4].f+x*y;
   * y=log2f_tbl[5].f+x*y;
   * y=log2f_tbl[6].f+x*y;
   * y=log2f_tbl[7].f+x*y;
   * y=log2f_tbl[8].f+x*y;
   * y=log2f_tbl[9].f+x*y;
   * y=x*y;
   * y=y+(float32_t)e;
   * return y;
   */

  const xtfloatx2  *          X_rd;
  const xtfloatx2  *          Y_rd;
        xtfloatx2  * restrict Y_wr;
  const ae_int32x2 *          SCR_rd;
        ae_int32x2 * restrict SCR_wr;

  ae_valign X_rd_va, Y_rd_va, Y_wr_va;

  /* Current block index; overall number of blocks; number of values in the current block */
  int blkIx,blkNum,blkLen;
  /* Block size, blkLen <= blkSize */
  const int blkSize = (MAX_ALLOCA_SZ/(sz_i32*2));
  /* Allocate a fixed-size scratch area on the stack. */
  int32_t ALIGN(8) scr0[blkSize];
  float32_t ALIGN(8) scr1[blkSize];
  /* Table of floating-point constants:        0.0     +Inf         qNaN      -Inf  */
  static const uint32_t ALIGN(8) const_tbl[] = {0  , 0x7f800000, 0x7fc00000, 0xff800000};
  const xtfloat *pconst_tbl = (const xtfloat *)const_tbl;

  int n;

  if ( N<=0 ) return;

  NASSERT_ALIGN8( scr0 );
  NASSERT_ALIGN8( scr1 );

  /*
   * Data are processed in blocks of scratch area size. Further, the algorithm
   * implementation is splitted in order to feed the optimizing compiler with a
   * few loops of managable size.
   */

  blkNum = (N + blkSize-1)/blkSize;

  for (blkIx=0; blkIx<blkNum; blkIx++)
  {
    blkLen = XT_MIN(N-blkIx*blkSize,blkSize);

    /*
     * Part I, reference C code:
     *
     *   {
     *     float32_t fr;
     *     int ex;
     *
     *     for ( n=0; n<blkLen; n++ )
     *     {
     *       fr = frexpf( x[blkIx*blkSize+n], &ex );
     *       if ( fr < sqrt0_5f.f ) { fr *= 2.f; ex--; };
     *       y[blkIx*blkSize+n] = 1.f - fr;
     *       scr[n] = ex;
     *     }
     *   }
     */

    {
      /* Input value; fractional part */
      xtfloatx2 x0, x1, fr0, fr1;
      /* Significand; exponential part */
      ae_int32x2 xn0, xn1, ex0, ex1;
      /* Is a subnormal; is less than 2^0.5  */
      xtbool2 b_subn, b_ltsqr;

      SCR_wr = (ae_int32x2*)scr0;

      X_rd = (xtfloatx2*)( (uintptr_t)x + blkIx*blkSize*sz_f32 );
      Y_wr = (xtfloatx2*)scr1;

      X_rd_va = AE_LA64_PP( X_rd );
      Y_wr_va = AE_ZALIGN64();

      for ( n=0; n<(blkLen>>1); n++ )
      {
        XT_LASX2IP( x0, X_rd_va, X_rd );

        /* Compare with smallest positive normal number 2^-126 */
        b_subn = XT_OLT_SX2( x0, XT_AE_MOVXTFLOATX2_FROMINT32X2(0x00800000) );
        /* Multiply subnormals by 2^23 */
        x1 = XT_MUL_SX2( x0, XT_AE_MOVXTFLOATX2_FROMINT32X2(0x4b000000) );

        xn0 = XT_AE_MOVINT32X2_FROMXTFLOATX2( x0 );
        xn1 = XT_AE_MOVINT32X2_FROMXTFLOATX2( x1 );

        ex0 = AE_SRLI32( xn0, 23 );
        ex1 = AE_SRLI32( xn1, 23 );

        ex0 = AE_SUB32( ex0, 127-1 );
        ex1 = AE_SUB32( ex1, 127-1+23 );

        AE_MOVT32X2( xn0, xn1, b_subn );
        AE_MOVT32X2( ex0, ex1, b_subn );

        xn0 = AE_AND32( xn0, (1<<23)-1 );
        xn0 = AE_OR32( xn0, 126<<23 );

        fr0 = XT_AE_MOVXTFLOATX2_FROMINT32X2(xn0);

        fr1 = XT_MUL_SX2( fr0, (xtfloatx2)2.0f );
        ex1 = AE_SUB32( ex0, AE_MOVI(1) );

        b_ltsqr = XT_OLT_SX2( fr0, sqrt0_5f.f );
        XT_MOVT_SX2( fr0, fr1, b_ltsqr );
        AE_MOVT32X2( ex0, ex1, b_ltsqr );

        fr0 = XT_SUB_SX2( (xtfloatx2)1.0f, fr0 );

        XT_SASX2IP( fr0, Y_wr_va, Y_wr );

        AE_S32X2_IP( ex0, SCR_wr, +2*sz_i32 );
      }

      XT_SASX2POSFP(Y_wr_va,Y_wr);

      /* Deliberately process the last input value if it's even-numbered. */
      if ( blkLen & 1 )
      {
        x0 = XT_LSI( (xtfloat*)X_rd, 0 );

        /* Compare with smallest positive normal number 2^-126 */
        b_subn = XT_OLT_SX2( x0, XT_AE_MOVXTFLOATX2_FROMINT32X2(0x00800000) );
        /* Multiply subnormals by 2^23 */
        x1 = XT_MUL_SX2( x0, XT_AE_MOVXTFLOATX2_FROMINT32X2(0x4b000000) );

        xn0 = XT_AE_MOVINT32X2_FROMXTFLOATX2( x0 );
        xn1 = XT_AE_MOVINT32X2_FROMXTFLOATX2( x1 );

        ex0 = AE_SRLI32( xn0, 23 );
        ex1 = AE_SRLI32( xn1, 23 );

        ex0 = AE_SUB32( ex0, 127-1 );
        ex1 = AE_SUB32( ex1, 127-1+23 );

        AE_MOVT32X2( xn0, xn1, b_subn );
        AE_MOVT32X2( ex0, ex1, b_subn );

        xn0 = AE_AND32( xn0, (1<<23)-1 );
        xn0 = AE_OR32( xn0, 126<<23 );

        fr0 = XT_AE_MOVXTFLOATX2_FROMINT32X2( xn0 );

        fr1 = XT_MUL_SX2( fr0, (xtfloatx2)2.0f );
        ex1 = AE_SUB32( ex0, AE_MOVI(1) );

        b_ltsqr = XT_OLT_SX2( fr0, sqrt0_5f.f );
        XT_MOVT_SX2( fr0, fr1, b_ltsqr );
        AE_MOVT32X2( ex0, ex1, b_ltsqr );

        fr0 = XT_SUB_SX2( (xtfloatx2)1.0f, fr0 );

        XT_SSI( (xtfloat)fr0, (xtfloat*)Y_wr, 0 );

        AE_S32_L_I( ex0, (ae_int32*)SCR_wr, 0 );
      }
    }

    __Pragma("no_reorder");

    /*
     * Part II, reference C code:
     *
     *   {
     *     float32_t xn, yn, fr, fr2;
     *     float32_t gn, cf0, cf1, cf2, cf3, cf4;
     *   
     *     for (n=0; n<blkLen; n++)
     *     {
     *       xn = x[blkIx*blkSize+n];
     *   
     *            if ( isnan(xn)      ) yn = xn;
     *       else if ( xn<0.f         ) yn = qNaNf.f;
     *       else if ( xn==0.f        ) yn = minusInff.f;
     *       else if ( xn==plusInff.f ) yn = plusInff.f;
     *       else
     *       {
     *         fr = y[blkIx*blkSize+n];
     *   
     *         //                                                              
     *         // Use a combination of Estrin's method and Horner's scheme to  
     *         // evaluate the polynomial.                                     
     *         //                                                              
     *   
     *         cf0 = log2f_tbl[0].f*fr + log2f_tbl[1].f;
     *         cf1 = log2f_tbl[2].f*fr + log2f_tbl[3].f;
     *         cf2 = log2f_tbl[4].f*fr + log2f_tbl[5].f;
     *         cf3 = log2f_tbl[6].f*fr + log2f_tbl[7].f;
     *         cf4 = log2f_tbl[8].f*fr + log2f_tbl[9].f;
     *   
     *         fr2 = fr*fr;
     *   
     *         gn = cf0;
     *         gn = cf1 + fr2*gn;
     *         gn = cf2 + fr2*gn;
     *         gn = cf3 + fr2*gn;
     *         gn = cf4 + fr2*gn;
     *   
     *         yn = fr*gn + scr[n];
     *       }
     *   
     *       y[blkIx*blkSize+n] = yn;
     *     }
     *   }
     */

    {
      const xtfloat *LOG_TBL_Rd;
      xtfloat temp;
      xtfloatx2 zero, qnan, mInf, pInf;
      /* Input value; output value; fractional part; squared fractional part */
      xtfloatx2 x0, y0, fr, fr2;
      /* Exponential part */
      ae_int32x2 ex0;
      /* Polynomial value; polynomial coefficients */
      xtfloatx2 g, cf0, cf1, cf2, cf3, cf4, cf5, cf6, cf7, cf8, cf9;
      /* Is a NaN or is less than zero; is equal to zero; is positive infinity */
      xtbool2 b_ultz, b_eqz, b_inf;

      SCR_rd = (ae_int32x2*)scr0;
      LOG_TBL_Rd = (const xtfloat *)(log2f_tbl);

      X_rd = (xtfloatx2*)( (uintptr_t)x + blkIx*blkSize*sz_f32 );
      Y_rd = (xtfloatx2*)scr1;
      Y_wr = (xtfloatx2*)( (uintptr_t)y + blkIx*blkSize*sz_f32 );

      X_rd_va = AE_LA64_PP( X_rd );
      Y_rd_va = AE_LA64_PP( Y_rd );
      Y_wr_va = AE_ZALIGN64();

      for ( n=0; n<(blkLen>>1); n++ )
      {
        XT_LASX2IP( fr, Y_rd_va, Y_rd );

        AE_L32X2_IP( ex0, SCR_rd, +2*sz_i32 );

        y0 = XT_FLOAT_SX2( ex0, 0 );

         /*
         * Reload input value and check it for special cases.
         */
        XT_LASX2IP( x0, X_rd_va, X_rd );

        /* Reload constants. */
        XT_LSIP(temp, pconst_tbl, sizeof(float32_t)); zero = (xtfloatx2)temp;
        XT_LSIP(temp, pconst_tbl, sizeof(float32_t)); pInf = (xtfloatx2)temp;
        XT_LSIP(temp, pconst_tbl, sizeof(float32_t)); qnan = (xtfloatx2)temp;
        XT_LSIP(temp, pconst_tbl, -3*(int)sizeof(float32_t)); mInf = (xtfloatx2)temp;

        b_ultz = XT_ULT_SX2( x0, zero );
        b_eqz  = XT_OEQ_SX2( x0, zero );
        b_inf  = XT_OEQ_SX2( x0, pInf );

        XT_MOVT_SX2( y0, qnan, b_ultz );
        XT_MOVT_SX2( y0, mInf, b_eqz );
        XT_MOVT_SX2( y0, pInf, b_inf );

        /* Reload coefficients on each iteration. */
        XT_LSIP(temp, LOG_TBL_Rd, sizeof(float32_t)); cf0 = (xtfloatx2)temp;
        XT_LSIP(temp, LOG_TBL_Rd, sizeof(float32_t)); cf1 = (xtfloatx2)temp;
        XT_LSIP(temp, LOG_TBL_Rd, sizeof(float32_t)); cf2 = (xtfloatx2)temp;
        XT_LSIP(temp, LOG_TBL_Rd, sizeof(float32_t)); cf3 = (xtfloatx2)temp;
        XT_LSIP(temp, LOG_TBL_Rd, sizeof(float32_t)); cf4 = (xtfloatx2)temp;
        XT_LSIP(temp, LOG_TBL_Rd, sizeof(float32_t)); cf5 = (xtfloatx2)temp;
        XT_LSIP(temp, LOG_TBL_Rd, sizeof(float32_t)); cf6 = (xtfloatx2)temp;
        XT_LSIP(temp, LOG_TBL_Rd, sizeof(float32_t)); cf7 = (xtfloatx2)temp;
        XT_LSIP(temp, LOG_TBL_Rd, sizeof(float32_t)); cf8 = (xtfloatx2)temp;
        XT_LSXP(temp, LOG_TBL_Rd, -9*(int)sizeof(float32_t)); cf9 = (xtfloatx2)temp;

        /*                                                              
         * Use a combination of Estrin's method and Horner's scheme to evaluate
         * the polynomial.                                     
         */

        XT_MADD_SX2( cf1, cf0, fr );
        XT_MADD_SX2( cf3, cf2, fr );
        XT_MADD_SX2( cf5, cf4, fr );
        XT_MADD_SX2( cf7, cf6, fr );
        XT_MADD_SX2( cf9, cf8, fr );

        fr2 = XT_MUL_SX2( fr, fr );

                                    g = cf1;
        XT_MADD_SX2( cf3, g, fr2 ); g = cf3;
        XT_MADD_SX2( cf5, g, fr2 ); g = cf5;
        XT_MADD_SX2( cf7, g, fr2 ); g = cf7;
        XT_MADD_SX2( cf9, g, fr2 ); g = cf9;
        XT_MADD_SX2( y0, g, fr );

        XT_SASX2IP( y0, Y_wr_va, Y_wr ); 
      }

      XT_SASX2POSFP( Y_wr_va, Y_wr );

      /* Deliberately process the last input value if it's even-numbered. */
      if ( blkLen & 1 )
      {
        fr = XT_LSI( (xtfloat*)Y_rd, 0 );

        ex0 = AE_L32_I( (ae_int32*)SCR_rd, 0 );

        y0 = XT_FLOAT_SX2( ex0, 0 );

        cf0 = (xtfloatx2)log2f_tbl[0].f;
        cf1 = (xtfloatx2)log2f_tbl[1].f;
        cf2 = (xtfloatx2)log2f_tbl[2].f;
        cf3 = (xtfloatx2)log2f_tbl[3].f;
        cf4 = (xtfloatx2)log2f_tbl[4].f;
        cf5 = (xtfloatx2)log2f_tbl[5].f;
        cf6 = (xtfloatx2)log2f_tbl[6].f;
        cf7 = (xtfloatx2)log2f_tbl[7].f;
        cf8 = (xtfloatx2)log2f_tbl[8].f;
        cf9 = (xtfloatx2)log2f_tbl[9].f;

        /*                                                              
         * Use a combination of Estrin's method and Horner's scheme to evaluate
         * the polynomial.                                     
         */

        XT_MADD_SX2( cf1, cf0, fr );
        XT_MADD_SX2( cf3, cf2, fr );
        XT_MADD_SX2( cf5, cf4, fr );
        XT_MADD_SX2( cf7, cf6, fr );
        XT_MADD_SX2( cf9, cf8, fr );

        fr2 = XT_MUL_SX2( fr, fr );

                                    g = cf1;
        XT_MADD_SX2( cf3, g, fr2 ); g = cf3;
        XT_MADD_SX2( cf5, g, fr2 ); g = cf5;
        XT_MADD_SX2( cf7, g, fr2 ); g = cf7;
        XT_MADD_SX2( cf9, g, fr2 ); g = cf9;

        XT_MADD_SX2( y0, g, fr );

        /*
         * Reload input value and check it for special cases.
         */

        x0 = XT_LSI( (xtfloat*)X_rd, 0 );

        b_ultz = XT_ULT_SX2( x0, (xtfloatx2)(0.0f) );
        b_eqz  = XT_OEQ_SX2( x0, (xtfloatx2)(0.0f) );
        b_inf  = XT_OEQ_SX2( x0, plusInff.f );

        XT_MOVT_SX2( y0, qNaNf.f, b_ultz );
        XT_MOVT_SX2( y0, minusInff.f, b_eqz );
        XT_MOVT_SX2( y0, plusInff.f, b_inf );

        XT_SSI( (xtfloat)y0, (xtfloat*)Y_wr, 0 );
      }
    }

  } /* for ( blkIx=0; blkIx<blkNum; blkIx++ ) */

} /* vec_log2f() */
#elif HAVE_FPU
#define sz_i32 (int)sizeof(int32_t)
#define sz_f32 (int)sizeof(float32_t)

/*===========================================================================
  Vector matematics:
  vec_log              Logarithm 
===========================================================================*/
/*-------------------------------------------------------------------------
  Logarithm:
  Different kinds of logarithm (base 2, natural, base 10). 32 and 24-bit 
  fixed point functions interpret input as Q16.15 and represent results in 
  Q25 format or return 0x80000000 on negative of zero input. 16-bit fixed-
  point functions interpret input as Q8.7 and represent result in Q3.12 or
  return 0x8000 on negative of zero input

  Precision:
  16x16  16-bit inputs, 16-bit outputs
  24x24  24-bit inputs, 24-bit outputs
  32x32  32-bit inputs, 32-bit outputs
  f      floating point

  Accuracy :
  16x16 functions                                                    2 LSB
  vec_log2_32x32,scl_log2_32x32  , vec_log2_24x24,scl_log2_24x24     730 (2.2e-5)
  vec_logn_32x32,scl_logn_32x32  , vec_logn_24x24,scl_logn_24x24     510 (1.5e-5)
  vec_log10_32x32,scl_log10_32x32, vec_log10_24x24,scl_log10_24x24   230 (6.9e-6)
  floating point                                                     2 ULP

  NOTES:
  1.  Although 32 and 24 bit functions provide the same accuracy, 32-bit 
      functions have better input/output resolution (dynamic range)
  2.  Scalar Floating point functions are compatible with standard ANSI C routines 
      and set errno and exception flags accordingly.
  3.  Floating point functions limit the range of allowable input values:
      A) If x<0, the result is set to NaN. In addition, scalar floating point
         functions assign the value EDOM to errno and raise the "invalid" 
         floating-point exception.
      B) If x==0, the result is set to minus infinity. Scalar floating  point
         functions assign the value ERANGE to errno and raise the "divide-by-zero"
         floating-point exception.

  Input:
  x[N]  input data, Q16.15 (32 or 24-bit functions), Q8.7 (16-bit functions) or 
        floating point 
  N     length of vectors
  Output:
  y[N]  result, Q6.25 (32 or 24-bit functions), Q3.12 (16-bit functions) or 
        floating point 

  Restriction:
  x,y should not overlap

  Scalar versions:
  ----------------
  return result result, Q6.25 (32 or 24-bit functions), Q3.12 (16-bit 
  functions) or floating point
-------------------------------------------------------------------------*/

// Taken from HiFi3 FP (Fusion F1 conflict: two scratches needed)
void vec_log2f(float32_t * restrict y, const float32_t * restrict x, int N)
{
  /*
   * Reference C code for a scalar variant:
   *
   * float32_t y;
   * int e;
   *
   * if ( x<0           ) return ( qNaNf.f     );
   * if ( x==0          ) return ( minusInff.f );
   * if ( x==plusInff.f ) return ( x           );
   *
   * x=frexpf(x,&e);
   * if(x<sqrt0_5f.f) { x=x*2; e--; }
   *
   * x=1.0f-x;
   * y=log2f_tbl[0].f;
   * y=log2f_tbl[1].f+x*y;
   * y=log2f_tbl[2].f+x*y;
   * y=log2f_tbl[3].f+x*y;
   * y=log2f_tbl[4].f+x*y;
   * y=log2f_tbl[5].f+x*y;
   * y=log2f_tbl[6].f+x*y;
   * y=log2f_tbl[7].f+x*y;
   * y=log2f_tbl[8].f+x*y;
   * y=log2f_tbl[9].f+x*y;
   * y=x*y;
   * y=y+(float32_t)e;
   * return y;
   */

  const xtfloat  *          X_rd;
  const xtfloat  *          Y_rd;
        xtfloat  * restrict Y_wr;
  const ae_int32 *          SCR_rd;
        ae_int32 * restrict SCR_wr;
  const xtfloat  *          POLY_TBL;

  /* Current block index; overall number of blocks; number of values in the current block */
  int blkIx,blkNum,blkLen;
  /* Block size, blkLen <= blkSize */
  const int blkSize = (MAX_ALLOCA_SZ/sz_i32);
  /* Allocate a fixed-size scratch area on the stack. */
  int32_t ALIGN(8) scr0[blkSize];
  float32_t ALIGN(8) scr1[blkSize];

  int n;

  if ( N<=0 ) return;

  NASSERT_ALIGN8( scr0 );
  NASSERT_ALIGN8( scr1 );

  /*
   * Data are processed in blocks of scratch area size. Further, the algorithm
   * implementation is splitted in order to feed the optimizing compiler with a
   * few loops of managable size.
   */

  POLY_TBL = (xtfloat*)log2f_tbl;

  blkNum = (N + blkSize-1)/blkSize;

  for (blkIx=0; blkIx<blkNum; blkIx++)
  {
    blkLen = XT_MIN(N-blkIx*blkSize,blkSize);

    /*
     * Part I, reference C code:
     *
     *   {
     *     float32_t fr;
     *     int ex;
     *
     *     for ( n=0; n<blkLen; n++ )
     *     {
     *       fr = frexpf( x[blkIx*blkSize+n], &ex );
     *       if ( fr < sqrt0_5f.f ) { fr *= 2.f; ex--; };
     *       y[blkIx*blkSize+n] = 1.f - fr;
     *       scr[n] = ex;
     *     }
     *   }
     */

    {
      /* Input value; fractional part */
      xtfloat x0, x1, fr0, fr1;
      /* Significand; exponential part */
      int32_t xn0, xn1, ex0, ex1;
      /* Is a subnormal; is less than 2^0.5  */
      xtbool b_subn, b_ltsqr;

      SCR_wr = (ae_int32*)scr0;

      X_rd = (xtfloat*)( (uintptr_t)x + blkIx*blkSize*sz_f32 );
      Y_wr = (xtfloat*)scr1;

      for ( n=0; n<blkLen; n++ )
      {
		XT_LSIP(x0, X_rd, sz_f32);

        /* Compare with smallest positive normal number 2^-126 */
        b_subn = XT_OLT_S( x0, XT_WFR(0x00800000) );

		/* Multiply subnormals by 2^23 */
        x1 = XT_WFR(0x4b000000);
		x1 = XT_MUL_S( x0, x1 );

        xn0 = XT_RFR( x0 );
        xn1 = XT_RFR( x1 );

        ex0 = xn0 >> 23;
        ex1 = xn1 >> 23;

        ex0 = XT_SUB( ex0, 127-1 );
        ex1 = XT_SUB( ex1, 127-1+23 );

        XT_MOVT( xn0, xn1, b_subn );
        XT_MOVT( ex0, ex1, b_subn );

        xn0 = XT_AND( xn0, (1<<23)-1 );
        xn0 = XT_OR( xn0, 126<<23 );

        fr0 = XT_WFR(xn0);

        fr1 = XT_MUL_S( fr0, 2.0f );
        ex1 = XT_SUB( ex0, XT_MOVI(1) );

        b_ltsqr = XT_OLT_S( fr0, sqrt0_5f.f );
        XT_MOVT_S( fr0, fr1, b_ltsqr );
        XT_MOVT( ex0, ex1, b_ltsqr );

        fr0 = XT_SUB_S( 1.0f, fr0 );

		XT_SSIP(fr0, Y_wr, sz_f32);

		*SCR_wr++ = ex0;
      }
    }

    __Pragma("no_reorder");

    /*
     * Part II, reference C code:
     *
     *   {
     *     float32_t xn, yn, fr, fr2;
     *     float32_t gn, cf0, cf1, cf2, cf3, cf4;
     *   
     *     for (n=0; n<blkLen; n++)
     *     {
     *       xn = x[blkIx*blkSize+n];
     *   
     *            if ( isnan(xn)      ) yn = xn;
     *       else if ( xn<0.f         ) yn = qNaNf.f;
     *       else if ( xn==0.f        ) yn = minusInff.f;
     *       else if ( xn==plusInff.f ) yn = plusInff.f;
     *       else
     *       {
     *         fr = y[blkIx*blkSize+n];
     *   
     *         //                                                              
     *         // Use a combination of Estrin's method and Horner's scheme to  
     *         // evaluate the polynomial.                                     
     *         //                                                              
     *   
     *         cf0 = log2f_tbl[0].f*fr + log2f_tbl[1].f;
     *         cf1 = log2f_tbl[2].f*fr + log2f_tbl[3].f;
     *         cf2 = log2f_tbl[4].f*fr + log2f_tbl[5].f;
     *         cf3 = log2f_tbl[6].f*fr + log2f_tbl[7].f;
     *         cf4 = log2f_tbl[8].f*fr + log2f_tbl[9].f;
     *   
     *         fr2 = fr*fr;
     *   
     *         gn = cf0;
     *         gn = cf1 + fr2*gn;
     *         gn = cf2 + fr2*gn;
     *         gn = cf3 + fr2*gn;
     *         gn = cf4 + fr2*gn;
     *   
     *         yn = fr*gn + scr[n];
     *       }
     *   
     *       y[blkIx*blkSize+n] = yn;
     *     }
     *   }
     */

    {
      /* Input value; output value; fractional part; squared fractional part */
      xtfloat x0, y0, fr, fr2;
      /* Exponential part */
      int32_t ex0;
      /* Polynomial value; polynomial coefficients */
      xtfloat g, cf0, cf1, cf2, cf3, cf4, cf5, cf6, cf7, cf8, cf9;
      /* Is a NaN or is less than zero; is equal to zero; is positive infinity */
      xtbool b_ultz, b_eqz, b_inf;

      SCR_rd = (ae_int32*)scr0;

      X_rd = (xtfloat*)( (uintptr_t)x + blkIx*blkSize*sz_f32 );
      Y_rd = (xtfloat*)scr1;
      Y_wr = (xtfloat*)( (uintptr_t)y + blkIx*blkSize*sz_f32 );

      /* Preload even-numbered coefficients. */
      cf0 = XT_LSI( POLY_TBL, 0*sz_f32 );
      cf2 = XT_LSI( POLY_TBL, 2*sz_f32 );
      cf4 = XT_LSI( POLY_TBL, 4*sz_f32 );
      cf6 = XT_LSI( POLY_TBL, 6*sz_f32 );
      cf8 = XT_LSX( POLY_TBL, 8*sz_f32 );

      for ( n=0; n<blkLen; n++ )
      {
		XT_LSIP(fr, Y_rd, sz_f32);

		ex0 = ae_int32_rtor_int32(*SCR_rd++);

		y0 = XT_FLOAT_S( ex0, 0 );

        /* Reload odd-numbered coefficients on each iteration. */
        cf1 = XT_LSI( POLY_TBL, 1*sz_f32 ); 
        cf3 = XT_LSI( POLY_TBL, 3*sz_f32 ); 
        cf5 = XT_LSI( POLY_TBL, 5*sz_f32 ); 
        cf7 = XT_LSI( POLY_TBL, 7*sz_f32 ); 
        cf9 = XT_LSX( POLY_TBL, 9*sz_f32 ); 

        /*                                                              
         * Use a combination of Estrin's method and Horner's scheme to evaluate
         * the polynomial.                                     
         */

        XT_MADD_S( cf1, cf0, fr );
        XT_MADD_S( cf3, cf2, fr );
        XT_MADD_S( cf5, cf4, fr );
        XT_MADD_S( cf7, cf6, fr );
        XT_MADD_S( cf9, cf8, fr );

        fr2 = XT_MUL_S( fr, fr );

                                  g = cf1;
        XT_MADD_S( cf3, g, fr2 ); g = cf3;
        XT_MADD_S( cf5, g, fr2 ); g = cf5;
        XT_MADD_S( cf7, g, fr2 ); g = cf7;
        XT_MADD_S( cf9, g, fr2 ); g = cf9;

        XT_MADD_S( y0, g, fr );

        /*
         * Reload input value and check it for special cases.
         */

		XT_LSIP(x0, X_rd, sz_f32);

        b_ultz = XT_ULT_S( x0, 0.0f );
        b_eqz  = XT_OEQ_S( x0, 0.0f );
        b_inf  = XT_OEQ_S( x0, plusInff.f );

        XT_MOVT_S( y0, qNaNf.f, b_ultz );
        XT_MOVT_S( y0, minusInff.f, b_eqz );
        XT_MOVT_S( y0, plusInff.f, b_inf );

		XT_SSIP(y0, Y_wr, sz_f32);
      }
    }
  } /* for ( blkIx=0; blkIx<blkNum; blkIx++ ) */
} /* vec_log2f() */
#endif
