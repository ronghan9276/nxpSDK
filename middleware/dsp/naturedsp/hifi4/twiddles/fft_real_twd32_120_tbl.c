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
#include "NatureDSP_Signal_fft.h"
#include "fft_twiddles32x32.h"
#include "common.h"

ALIGN(8) static const int32_t __fft_real_tw[] =
{
    (int32_t)0x7FFFFFFF, (int32_t)0x00000000,
    (int32_t)0x7FD317B4, (int32_t)0xF94D0E2E,
    (int32_t)0x7F4C7E54, (int32_t)0xF29ECFB2,
    (int32_t)0x7E6C9251, (int32_t)0xEBF9F498,
    (int32_t)0x7D33F0CA, (int32_t)0xE5632654,
    (int32_t)0x7BA3751D, (int32_t)0xDEDF047D,
    (int32_t)0x79BC384D, (int32_t)0xD8722192,
    (int32_t)0x777F903C, (int32_t)0xD220FFC0,
    (int32_t)0x74EF0EBC, (int32_t)0xCBF00DBE,
    (int32_t)0x720C8075, (int32_t)0xC5E3A3A9,
    (int32_t)0x6ED9EBA1, (int32_t)0xC0000000,
    (int32_t)0x6B598EA3, (int32_t)0xBA4944A2,
    (int32_t)0x678DDE6E, (int32_t)0xB4C373EE,
    (int32_t)0x637984D4, (int32_t)0xAF726DEF,
    (int32_t)0x5F1F5EA1, (int32_t)0xAA59EDA4,
    (int32_t)0x5A82799A, (int32_t)0xA57D8666,
    (int32_t)0x55A6125C, (int32_t)0xA0E0A15F,
    (int32_t)0x508D9211, (int32_t)0x9C867B2C,
    (int32_t)0x4B3C8C12, (int32_t)0x98722192,
    (int32_t)0x45B6BB5E, (int32_t)0x94A6715D,
    (int32_t)0x40000000, (int32_t)0x9126145F,
    (int32_t)0x3A1C5C57, (int32_t)0x8DF37F8B,
    (int32_t)0x340FF242, (int32_t)0x8B10F144,
    (int32_t)0x2DDF0040, (int32_t)0x88806FC4,
    (int32_t)0x278DDE6E, (int32_t)0x8643C7B3,
    (int32_t)0x2120FB83, (int32_t)0x845C8AE3,
    (int32_t)0x1A9CD9AC, (int32_t)0x82CC0F36,
    (int32_t)0x14060B68, (int32_t)0x81936DAF,
    (int32_t)0x0D61304E, (int32_t)0x80B381AC,
    (int32_t)0x06B2F1D2, (int32_t)0x802CE84C,
};

static const fft_real32x32_descr_t __rfft_descr =
{
    (const fft_handle_t)&__cfft_descr60_32x32,
    __fft_real_tw
};

static const fft_real32x32_descr_t __rifft_descr =
{
    (const fft_handle_t)&__cifft_descr60_32x32,
    __fft_real_tw
};

const fft_handle_t rnfft32_120 =  (const fft_handle_t)&__rfft_descr;
const fft_handle_t rinfft32_120 = (const fft_handle_t)&__rifft_descr;
