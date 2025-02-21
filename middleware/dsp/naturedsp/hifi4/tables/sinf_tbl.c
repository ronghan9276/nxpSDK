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
    tables for sin(pi/2*x) approximation
*/

#include "NatureDSP_types.h"
#include "sinf_tbl.h"
#include "common.h"

const union ufloat32uint32 sinf_maxval={0x47c90e00};

/* pi/4 represented as a sum of exacly represented numbers.
    derived from hex value of pi: 3.243F6A8885A308D313198A2E037073
*/
const union ufloat64uint64 pi4fc[]=
{
    {0x3fe9220000000000}, /*  3217/2^12                   */
    {0xbec2aeef4b9ee59e}  /*  -8.9089102067615373566e-6/4 */
};

/* 
   polynomial coefficients for sin(x)/x, [-pi/4...pi/4]
   derived by MATLAB code:
   s=pow2(1,-16); x=(s:s:pi/4); x=[-x(end:-1:1) x];
   y=sin(x)./x;
   p=polyfit(x,y,6); p=p(1:2:end); p(end)=[];
*/
const union ufloat32uint32 ALIGN(8) polysinf_tbl[]=
{ 
    {0xb94cbf8d}, /*-1.9526313755e-004*/
    {0x3c0883d8}, /* 8.3322152879e-003*/
    {0xbe2aaaa2}, /*-1.6666654143e-001*/
    {0x00000000}  /* Padding for vector loads */
};

/* 
   polynomial coefficients for cos(x), [-pi/4...pi/4]
   derived by MATLAB code:
   s=pow2(1,-16); x=(s:s:pi/4); x=[-x(end:-1:1) x];
   y=cos(x);
   p=polyfit(x,y,6); p=p(1:2:end); p(end)=[];
*/
const union ufloat32uint32 ALIGN(8) polycosf_tbl[]=
{
#if SINNCOSF_ALG==0
    {0xbab255cf}, /*-1.3605895053e-003*/
    {0x3d2aa023}, /* 4.1656626373e-002*/
    {0xbeffffda}, /*-4.9999887566e-001*/
    {0x00000000}  /* Padding for vector loads */
#elif SINNCOSF_ALG==1
    {0x37ccb2c7}, /* 2.4401944152886800e-005 */
    {0xbab60495}, /* -1.388686378733473e-003 */
    {0x3d2aaaa0}, /* 4.1666625080677780e-002 */
    {0xbf000000}  /* 4.9999999704259030e-001 */
#else
#error wrong SINNCOSF_ALG
#endif 
};
