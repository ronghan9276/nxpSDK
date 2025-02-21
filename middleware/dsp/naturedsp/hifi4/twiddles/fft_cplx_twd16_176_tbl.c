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
#include "common.h"
#include "fft_x16_common.h"

/* Twiddles tables for fft_cplx32x16, ifft_cplx32x16, fft_cplx16x16, ifft_cplx16x16, N=176 */
#define N 176

/********** Twiddles table N=176 stage 1 radix 4 ******************/
ALIGN(8) static const int16_t _fft176_tw1_[] =
{
    (int16_t)0x7FFF, (int16_t)0x0000, (int16_t)0x7FFF, (int16_t)0x0000, (int16_t)0x7FFF, (int16_t)0x0000, (int16_t)0x7FEB, (int16_t)0xFB6E,
    (int16_t)0x7FAD, (int16_t)0xF6DE, (int16_t)0x7F44, (int16_t)0xF251, (int16_t)0x7FAD, (int16_t)0xF6DE, (int16_t)0x7EB2, (int16_t)0xEDC9,
    (int16_t)0x7D13, (int16_t)0xE4CB, (int16_t)0x7F44, (int16_t)0xF251, (int16_t)0x7D13, (int16_t)0xE4CB, (int16_t)0x7973, (int16_t)0xD794,
    (int16_t)0x7EB2, (int16_t)0xEDC9, (int16_t)0x7AD1, (int16_t)0xDBF0, (int16_t)0x746F, (int16_t)0xCAD4, (int16_t)0x7DF7, (int16_t)0xE946,
    (int16_t)0x77EE, (int16_t)0xD345, (int16_t)0x6E15, (int16_t)0xBEAF, (int16_t)0x7D13, (int16_t)0xE4CB, (int16_t)0x746F, (int16_t)0xCAD4,
    (int16_t)0x6678, (int16_t)0xB34B, (int16_t)0x7C06, (int16_t)0xE058, (int16_t)0x7058, (int16_t)0xC2A8, (int16_t)0x5DAF, (int16_t)0xA8C7,
    (int16_t)0x7AD1, (int16_t)0xDBF0, (int16_t)0x6BAE, (int16_t)0xBACC, (int16_t)0x53D2, (int16_t)0x9F44, (int16_t)0x7973, (int16_t)0xD794,
    (int16_t)0x6678, (int16_t)0xB34B, (int16_t)0x4900, (int16_t)0x96DC, (int16_t)0x77EE, (int16_t)0xD345, (int16_t)0x60BC, (int16_t)0xAC2E,
    (int16_t)0x3D58, (int16_t)0x8FA8, (int16_t)0x7642, (int16_t)0xCF04, (int16_t)0x5A82, (int16_t)0xA57E, (int16_t)0x30FC, (int16_t)0x89BE,
    (int16_t)0x746F, (int16_t)0xCAD4, (int16_t)0x53D2, (int16_t)0x9F44, (int16_t)0x2410, (int16_t)0x852F, (int16_t)0x7276, (int16_t)0xC6B4,
    (int16_t)0x4CB5, (int16_t)0x9988, (int16_t)0x16BA, (int16_t)0x8209, (int16_t)0x7058, (int16_t)0xC2A8, (int16_t)0x4534, (int16_t)0x9452,
    (int16_t)0x0922, (int16_t)0x8053, (int16_t)0x6E15, (int16_t)0xBEAF, (int16_t)0x3D58, (int16_t)0x8FA8, (int16_t)0xFB6E, (int16_t)0x8015,
    (int16_t)0x6BAE, (int16_t)0xBACC, (int16_t)0x352C, (int16_t)0x8B91, (int16_t)0xEDC9, (int16_t)0x814E, (int16_t)0x6924, (int16_t)0xB700,
    (int16_t)0x2CBB, (int16_t)0x8812, (int16_t)0xE058, (int16_t)0x83FA, (int16_t)0x6678, (int16_t)0xB34B, (int16_t)0x2410, (int16_t)0x852F,
    (int16_t)0xD345, (int16_t)0x8812, (int16_t)0x63AB, (int16_t)0xAFAF, (int16_t)0x1B35, (int16_t)0x82ED, (int16_t)0xC6B4, (int16_t)0x8D8A,
    (int16_t)0x60BC, (int16_t)0xAC2E, (int16_t)0x1237, (int16_t)0x814E, (int16_t)0xBACC, (int16_t)0x9452, (int16_t)0x5DAF, (int16_t)0xA8C7,
    (int16_t)0x0922, (int16_t)0x8053, (int16_t)0xAFAF, (int16_t)0x9C55, (int16_t)0x5A82, (int16_t)0xA57E, (int16_t)0x0000, (int16_t)0x8000,
    (int16_t)0xA57E, (int16_t)0xA57E, (int16_t)0x5739, (int16_t)0xA251, (int16_t)0xF6DE, (int16_t)0x8053, (int16_t)0x9C55, (int16_t)0xAFAF,
    (int16_t)0x53D2, (int16_t)0x9F44, (int16_t)0xEDC9, (int16_t)0x814E, (int16_t)0x9452, (int16_t)0xBACC, (int16_t)0x5051, (int16_t)0x9C55,
    (int16_t)0xE4CB, (int16_t)0x82ED, (int16_t)0x8D8A, (int16_t)0xC6B4, (int16_t)0x4CB5, (int16_t)0x9988, (int16_t)0xDBF0, (int16_t)0x852F,
    (int16_t)0x8812, (int16_t)0xD345, (int16_t)0x4900, (int16_t)0x96DC, (int16_t)0xD345, (int16_t)0x8812, (int16_t)0x83FA, (int16_t)0xE058,
    (int16_t)0x4534, (int16_t)0x9452, (int16_t)0xCAD4, (int16_t)0x8B91, (int16_t)0x814E, (int16_t)0xEDC9, (int16_t)0x4151, (int16_t)0x91EB,
    (int16_t)0xC2A8, (int16_t)0x8FA8, (int16_t)0x8015, (int16_t)0xFB6E, (int16_t)0x3D58, (int16_t)0x8FA8, (int16_t)0xBACC, (int16_t)0x9452,
    (int16_t)0x8053, (int16_t)0x0922, (int16_t)0x394C, (int16_t)0x8D8A, (int16_t)0xB34B, (int16_t)0x9988, (int16_t)0x8209, (int16_t)0x16BA,
    (int16_t)0x352C, (int16_t)0x8B91, (int16_t)0xAC2E, (int16_t)0x9F44, (int16_t)0x852F, (int16_t)0x2410, (int16_t)0x30FC, (int16_t)0x89BE,
    (int16_t)0xA57E, (int16_t)0xA57E, (int16_t)0x89BE, (int16_t)0x30FC, (int16_t)0x2CBB, (int16_t)0x8812, (int16_t)0x9F44, (int16_t)0xAC2E,
    (int16_t)0x8FA8, (int16_t)0x3D58, (int16_t)0x286C, (int16_t)0x868D, (int16_t)0x9988, (int16_t)0xB34B, (int16_t)0x96DC, (int16_t)0x4900,
    (int16_t)0x2410, (int16_t)0x852F, (int16_t)0x9452, (int16_t)0xBACC, (int16_t)0x9F44, (int16_t)0x53D2, (int16_t)0x1FA8, (int16_t)0x83FA,
    (int16_t)0x8FA8, (int16_t)0xC2A8, (int16_t)0xA8C7, (int16_t)0x5DAF, (int16_t)0x1B35, (int16_t)0x82ED, (int16_t)0x8B91, (int16_t)0xCAD4,
    (int16_t)0xB34B, (int16_t)0x6678, (int16_t)0x16BA, (int16_t)0x8209, (int16_t)0x8812, (int16_t)0xD345, (int16_t)0xBEAF, (int16_t)0x6E15,
    (int16_t)0x1237, (int16_t)0x814E, (int16_t)0x852F, (int16_t)0xDBF0, (int16_t)0xCAD4, (int16_t)0x746F, (int16_t)0x0DAF, (int16_t)0x80BC,
    (int16_t)0x82ED, (int16_t)0xE4CB, (int16_t)0xD794, (int16_t)0x7973, (int16_t)0x0922, (int16_t)0x8053, (int16_t)0x814E, (int16_t)0xEDC9,
    (int16_t)0xE4CB, (int16_t)0x7D13, (int16_t)0x0492, (int16_t)0x8015, (int16_t)0x8053, (int16_t)0xF6DE, (int16_t)0xF251, (int16_t)0x7F44,
};

/********** Twiddles table N=176 stage 2 radix 4 ******************/
ALIGN(8) static const int16_t _fft176_tw2_[] =
{
    (int16_t)0x7FFF, (int16_t)0x0000, (int16_t)0x7FFF, (int16_t)0x0000, (int16_t)0x7FFF, (int16_t)0x0000,
    (int16_t)0x7EB2, (int16_t)0xEDC9, (int16_t)0x7AD1, (int16_t)0xDBF0, (int16_t)0x746F, (int16_t)0xCAD4,
    (int16_t)0x7AD1, (int16_t)0xDBF0, (int16_t)0x6BAE, (int16_t)0xBACC, (int16_t)0x53D2, (int16_t)0x9F44,
    (int16_t)0x746F, (int16_t)0xCAD4, (int16_t)0x53D2, (int16_t)0x9F44, (int16_t)0x2410, (int16_t)0x852F,
    (int16_t)0x6BAE, (int16_t)0xBACC, (int16_t)0x352C, (int16_t)0x8B91, (int16_t)0xEDC9, (int16_t)0x814E,
    (int16_t)0x60BC, (int16_t)0xAC2E, (int16_t)0x1237, (int16_t)0x814E, (int16_t)0xBACC, (int16_t)0x9452,
    (int16_t)0x53D2, (int16_t)0x9F44, (int16_t)0xEDC9, (int16_t)0x814E, (int16_t)0x9452, (int16_t)0xBACC,
    (int16_t)0x4534, (int16_t)0x9452, (int16_t)0xCAD4, (int16_t)0x8B91, (int16_t)0x814E, (int16_t)0xEDC9,
    (int16_t)0x352C, (int16_t)0x8B91, (int16_t)0xAC2E, (int16_t)0x9F44, (int16_t)0x852F, (int16_t)0x2410,
    (int16_t)0x2410, (int16_t)0x852F, (int16_t)0x9452, (int16_t)0xBACC, (int16_t)0x9F44, (int16_t)0x53D2,
    (int16_t)0x1237, (int16_t)0x814E, (int16_t)0x852F, (int16_t)0xDBF0, (int16_t)0xCAD4, (int16_t)0x746F,
};

static const int tw_step_tab[] =
{
    1, 1, 0
}; 
static const cint16ptr_t tw_tab[] = 
{
    _fft176_tw1_, _fft176_tw2_, NULL
};

static const eFft_stage_type fft_stg_tab[] = 
{
    fft_stage_first_DFT4,
    fft_stage_inner_DFT4,
    fft_stage_last_DFT11
};
static const eFft_stage_type ifft_stg_tab[] =
{
    fft_stage_first_inv_DFT4,
    fft_stage_inner_DFT4,
    fft_stage_last_DFT11
};


const fft_cplx_x16_descr_t __cfft_x16_descr176 = 
{
    N, 
    fft_stg_tab, 
    fft_stg_tab, 
    fft_stg_tab, 
    fft_stg_tab, 
    tw_step_tab,
    tw_tab
};     
const fft_cplx_x16_descr_t __cifft_x16_descr176 =
{
    N, 
    ifft_stg_tab, 
    ifft_stg_tab, 
    ifft_stg_tab, 
    ifft_stg_tab, 
    tw_step_tab,
    tw_tab
};     
const fft_handle_t cnfft16_176  = (const fft_handle_t)&__cfft_x16_descr176;
const fft_handle_t cinfft16_176 = (const fft_handle_t)&__cifft_x16_descr176;
