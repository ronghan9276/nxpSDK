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
#include "fft_twiddles32x32.h"
#include "common.h"

/* Twiddles tables for fft_cplx32x32, ifft_cplx32x32 */

/****************** stage 1 radix 4 ******************/
ALIGN(8) static const int32_t __fft64_tw1[] = 
{
    (int32_t)0x7FFFFFFF, (int32_t)0x00000000, (int32_t)0x7FFFFFFF, (int32_t)0x00000000, (int32_t)0x7FFFFFFF, (int32_t)0x00000000, (int32_t)0x7F62368F, (int32_t)0xF3742CA2, 
    (int32_t)0x7D8A5F40, (int32_t)0xE70747C4, (int32_t)0x7A7D055B, (int32_t)0xDAD7F3A2, (int32_t)0x7D8A5F40, (int32_t)0xE70747C4, (int32_t)0x7641AF3D, (int32_t)0xCF043AB3, 
    (int32_t)0x6A6D98A4, (int32_t)0xB8E31319, (int32_t)0x7A7D055B, (int32_t)0xDAD7F3A2, (int32_t)0x6A6D98A4, (int32_t)0xB8E31319, (int32_t)0x5133CC94, (int32_t)0x9D0DFE54, 
    (int32_t)0x7641AF3D, (int32_t)0xCF043AB3, (int32_t)0x5A82799A, (int32_t)0xA57D8666, (int32_t)0x30FBC54D, (int32_t)0x89BE50C3, (int32_t)0x70E2CBC6, (int32_t)0xC3A94590, 
    (int32_t)0x471CECE7, (int32_t)0x9592675C, (int32_t)0x0C8BD35E, (int32_t)0x809DC971, (int32_t)0x6A6D98A4, (int32_t)0xB8E31319, (int32_t)0x30FBC54D, (int32_t)0x89BE50C3, 
    (int32_t)0xE70747C4, (int32_t)0x8275A0C0, (int32_t)0x62F201AC, (int32_t)0xAECC336C, (int32_t)0x18F8B83C, (int32_t)0x8275A0C0, (int32_t)0xC3A94590, (int32_t)0x8F1D343A, 
    (int32_t)0x5A82799A, (int32_t)0xA57D8666, (int32_t)0x00000000, (int32_t)0x80000000, (int32_t)0xA57D8666, (int32_t)0xA57D8666, (int32_t)0x5133CC94, (int32_t)0x9D0DFE54, 
    (int32_t)0xE70747C4, (int32_t)0x8275A0C0, (int32_t)0x8F1D343A, (int32_t)0xC3A94590, (int32_t)0x471CECE7, (int32_t)0x9592675C, (int32_t)0xCF043AB3, (int32_t)0x89BE50C3, 
    (int32_t)0x8275A0C0, (int32_t)0xE70747C4, (int32_t)0x3C56BA70, (int32_t)0x8F1D343A, (int32_t)0xB8E31319, (int32_t)0x9592675C, (int32_t)0x809DC971, (int32_t)0x0C8BD35E, 
    (int32_t)0x30FBC54D, (int32_t)0x89BE50C3, (int32_t)0xA57D8666, (int32_t)0xA57D8666, (int32_t)0x89BE50C3, (int32_t)0x30FBC54D, (int32_t)0x25280C5E, (int32_t)0x8582FAA5, 
    (int32_t)0x9592675C, (int32_t)0xB8E31319, (int32_t)0x9D0DFE54, (int32_t)0x5133CC94, (int32_t)0x18F8B83C, (int32_t)0x8275A0C0, (int32_t)0x89BE50C3, (int32_t)0xCF043AB3, 
    (int32_t)0xB8E31319, (int32_t)0x6A6D98A4, (int32_t)0x0C8BD35E, (int32_t)0x809DC971, (int32_t)0x8275A0C0, (int32_t)0xE70747C4, (int32_t)0xDAD7F3A2, (int32_t)0x7A7D055B, 
};
#define N 64
static const fft_cplx32x32_stage_t s2_tab[] = 
{
    fft_stageS2_DFT4_first_32x32,
    fft_stageS2_DFT4x4_penultimate_32x32,
    fft_stageS2_DFT4_last_32x32,
    NULL
};
static const fft_cplx32x32_stage_t s3_tab[] =
{
    fft_stageS3_DFT4_first_32x32,
    fft_stageS3_DFT4x4_penultimate_32x32,
    fft_stageS3_DFT4_last_32x32,
    NULL
};
static const fft_cplx32x32_stage_t is2_tab[] = 
{
    ifft_stageS2_DFT4_first_32x32,
    fft_stageS2_DFT4x4_penultimate_32x32,
    fft_stageS2_DFT4_last_32x32,
    NULL
};
static const fft_cplx32x32_stage_t is3_tab[] =
{
    ifft_stageS3_DFT4_first_32x32,
    fft_stageS3_DFT4x4_penultimate_32x32,
    fft_stageS3_DFT4_last_32x32,
    NULL
};
static const int tw_step_tab[] =
{
    1, 4, 16, 
}; 
static const cint32ptr_t tw_tab[] = 
{
    __fft64_tw1, __fft64_tw1, NULL
};
const fft_cplx32x32_descr_t __cfft_descr64_32x32 =
{
    N, 
    s2_tab, 
    s3_tab, 
    tw_step_tab,
    tw_tab
};     
const fft_cplx32x32_descr_t __cifft_descr64_32x32 =
{
    N, 
    is2_tab, 
    is3_tab, 
    tw_step_tab,
    tw_tab
};     
const fft_handle_t cfft32_64 = (const fft_handle_t)&__cfft_descr64_32x32;
const fft_handle_t cifft32_64 = (const fft_handle_t)&__cifft_descr64_32x32;
