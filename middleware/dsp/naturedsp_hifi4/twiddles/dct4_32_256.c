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
    NatureDSP Signal Processing Library. FFT part
    DCT-IV twiddles
    Integrit, 2006-2018
*/

#include "NatureDSP_Signal_fft.h"
#include "common.h"
#include "dct4_twd.h"


static const complex_fract32 ALIGN(8) dct4_twd_256[]=
{
    {{(int32_t)0X7FFFD886UL,(int32_t)0xFF9B781DUL}},
    {{(int32_t)0X7FFE9CB2UL,(int32_t)0xFED2694FUL}},
    {{(int32_t)0X7FFC250FUL,(int32_t)0xFE095D69UL}},
    {{(int32_t)0X7FF871A2UL,(int32_t)0xFD40565CUL}},
    {{(int32_t)0X7FF38274UL,(int32_t)0xFC775616UL}},
    {{(int32_t)0X7FED5791UL,(int32_t)0xFBAE5E89UL}},
    {{(int32_t)0X7FE5F108UL,(int32_t)0xFAE571A4UL}},
    {{(int32_t)0X7FDD4EECUL,(int32_t)0xFA1C9157UL}},
    {{(int32_t)0X7FD37153UL,(int32_t)0xF953BF91UL}},
    {{(int32_t)0X7FC85854UL,(int32_t)0xF88AFE42UL}},
    {{(int32_t)0X7FBC040AUL,(int32_t)0xF7C24F59UL}},
    {{(int32_t)0X7FAE7495UL,(int32_t)0xF6F9B4C6UL}},
    {{(int32_t)0X7F9FAA15UL,(int32_t)0xF6313077UL}},
    {{(int32_t)0X7F8FA4B0UL,(int32_t)0xF568C45BUL}},
    {{(int32_t)0X7F7E648CUL,(int32_t)0xF4A07261UL}},
    {{(int32_t)0X7F6BE9D4UL,(int32_t)0xF3D83C77UL}},
    {{(int32_t)0X7F5834B7UL,(int32_t)0xF310248AUL}},
    {{(int32_t)0X7F434563UL,(int32_t)0xF2482C8AUL}},
    {{(int32_t)0X7F2D1C0EUL,(int32_t)0xF1805662UL}},
    {{(int32_t)0X7F15B8EEUL,(int32_t)0xF0B8A401UL}},
    {{(int32_t)0X7EFD1C3CUL,(int32_t)0xEFF11753UL}},
    {{(int32_t)0X7EE34636UL,(int32_t)0xEF29B243UL}},
    {{(int32_t)0X7EC8371AUL,(int32_t)0xEE6276BFUL}},
    {{(int32_t)0X7EABEF2CUL,(int32_t)0xED9B66B2UL}},
    {{(int32_t)0X7E8E6EB2UL,(int32_t)0xECD48407UL}},
    {{(int32_t)0X7E6FB5F4UL,(int32_t)0xEC0DD0A8UL}},
    {{(int32_t)0X7E4FC53EUL,(int32_t)0xEB474E81UL}},
    {{(int32_t)0X7E2E9CDFUL,(int32_t)0xEA80FF7AUL}},
    {{(int32_t)0X7E0C3D29UL,(int32_t)0xE9BAE57DUL}},
    {{(int32_t)0X7DE8A670UL,(int32_t)0xE8F50273UL}},
    {{(int32_t)0X7DC3D90DUL,(int32_t)0xE82F5844UL}},
    {{(int32_t)0X7D9DD55AUL,(int32_t)0xE769E8D8UL}},
    {{(int32_t)0X7D769BB5UL,(int32_t)0xE6A4B616UL}},
    {{(int32_t)0X7D4E2C7FUL,(int32_t)0xE5DFC1E5UL}},
    {{(int32_t)0X7D24881BUL,(int32_t)0xE51B0E2AUL}},
    {{(int32_t)0X7CF9AEF0UL,(int32_t)0xE4569CCBUL}},
    {{(int32_t)0X7CCDA169UL,(int32_t)0xE3926FADUL}},
    {{(int32_t)0X7CA05FF1UL,(int32_t)0xE2CE88B3UL}},
    {{(int32_t)0X7C71EAF9UL,(int32_t)0xE20AE9C1UL}},
    {{(int32_t)0X7C4242F2UL,(int32_t)0xE14794BAUL}},
    {{(int32_t)0X7C116853UL,(int32_t)0xE0848B7FUL}},
    {{(int32_t)0X7BDF5B94UL,(int32_t)0xDFC1CFF3UL}},
    {{(int32_t)0X7BAC1D31UL,(int32_t)0xDEFF63F4UL}},
    {{(int32_t)0X7B77ADA8UL,(int32_t)0xDE3D4964UL}},
    {{(int32_t)0X7B420D7AUL,(int32_t)0xDD7B8220UL}},
    {{(int32_t)0X7B0B3D2CUL,(int32_t)0xDCBA1008UL}},
    {{(int32_t)0X7AD33D45UL,(int32_t)0xDBF8F4F8UL}},
    {{(int32_t)0X7A9A0E50UL,(int32_t)0xDB3832CDUL}},
    {{(int32_t)0X7A5FB0D8UL,(int32_t)0xDA77CB63UL}},
    {{(int32_t)0X7A24256FUL,(int32_t)0xD9B7C094UL}},
    {{(int32_t)0X79E76CA7UL,(int32_t)0xD8F81439UL}},
    {{(int32_t)0X79A98715UL,(int32_t)0xD838C82DUL}},
    {{(int32_t)0X796A7554UL,(int32_t)0xD779DE47UL}},
    {{(int32_t)0X792A37FEUL,(int32_t)0xD6BB585EUL}},
    {{(int32_t)0X78E8CFB2UL,(int32_t)0xD5FD3848UL}},
    {{(int32_t)0X78A63D11UL,(int32_t)0xD53F7FDAUL}},
    {{(int32_t)0X786280BFUL,(int32_t)0xD48230E9UL}},
    {{(int32_t)0X781D9B65UL,(int32_t)0xD3C54D47UL}},
    {{(int32_t)0X77D78DAAUL,(int32_t)0xD308D6C7UL}},
    {{(int32_t)0X7790583EUL,(int32_t)0xD24CCF39UL}},
    {{(int32_t)0X7747FBCEUL,(int32_t)0xD191386EUL}},
    {{(int32_t)0X76FE790EUL,(int32_t)0xD0D61434UL}},
    {{(int32_t)0X76B3D0B4UL,(int32_t)0xD01B6459UL}},
    {{(int32_t)0X76680376UL,(int32_t)0xCF612AAAUL}},
    {{(int32_t)0X5A3B47ABUL,(int32_t)0xA5368C4BUL}},
    {{(int32_t)0X59AC3CFDUL,(int32_t)0xA4A94043UL}},
    {{(int32_t)0X591C550EUL,(int32_t)0xA41CD599UL}},
    {{(int32_t)0X588B9140UL,(int32_t)0xA3914DA8UL}},
    {{(int32_t)0X57F9F2F8UL,(int32_t)0xA306A9C8UL}},
    {{(int32_t)0X57677B9DUL,(int32_t)0xA27CEB4FUL}},
    {{(int32_t)0X56D42C99UL,(int32_t)0xA1F41392UL}},
    {{(int32_t)0X56400758UL,(int32_t)0xA16C23E1UL}},
    {{(int32_t)0X55AB0D46UL,(int32_t)0xA0E51D8CUL}},
    {{(int32_t)0X55153FD4UL,(int32_t)0xA05F01E1UL}},
    {{(int32_t)0X547EA073UL,(int32_t)0x9FD9D22AUL}},
    {{(int32_t)0X53E73097UL,(int32_t)0x9F558FB0UL}},
    {{(int32_t)0X534EF1B5UL,(int32_t)0x9ED23BB9UL}},
    {{(int32_t)0X52B5E546UL,(int32_t)0x9E4FD78AUL}},
    {{(int32_t)0X521C0CC2UL,(int32_t)0x9DCE6463UL}},
    {{(int32_t)0X518169A5UL,(int32_t)0x9D4DE385UL}},
    {{(int32_t)0X50E5FD6DUL,(int32_t)0x9CCE562CUL}},
    {{(int32_t)0X5049C999UL,(int32_t)0x9C4FBD93UL}},
    {{(int32_t)0X4FACCFABUL,(int32_t)0x9BD21AF3UL}},
    {{(int32_t)0X4F0F1126UL,(int32_t)0x9B556F81UL}},
    {{(int32_t)0X4E708F8FUL,(int32_t)0x9AD9BC71UL}},
    {{(int32_t)0X4DD14C6EUL,(int32_t)0x9A5F02F5UL}},
    {{(int32_t)0X4D31494BUL,(int32_t)0x99E5443BUL}},
    {{(int32_t)0X4C9087B1UL,(int32_t)0x996C816FUL}},
    {{(int32_t)0X4BEF092DUL,(int32_t)0x98F4BBBCUL}},
    {{(int32_t)0X4B4CCF4DUL,(int32_t)0x987DF449UL}},
    {{(int32_t)0X4AA9DBA2UL,(int32_t)0x98082C3BUL}},
    {{(int32_t)0X4A062FBDUL,(int32_t)0x979364B5UL}},
    {{(int32_t)0X4961CD33UL,(int32_t)0x971F9ED7UL}},
    {{(int32_t)0X48BCB599UL,(int32_t)0x96ACDBBEUL}},
    {{(int32_t)0X4816EA86UL,(int32_t)0x963B1C86UL}},
    {{(int32_t)0X47706D93UL,(int32_t)0x95CA6247UL}},
    {{(int32_t)0X46C9405CUL,(int32_t)0x955AAE17UL}},
    {{(int32_t)0X4621647DUL,(int32_t)0x94EC010BUL}},
    {{(int32_t)0X4578DB93UL,(int32_t)0x947E5C33UL}},
    {{(int32_t)0X44CFA740UL,(int32_t)0x9411C09EUL}},
    {{(int32_t)0X4425C923UL,(int32_t)0x93A62F57UL}},
    {{(int32_t)0X437B42E1UL,(int32_t)0x933BA968UL}},
    {{(int32_t)0X42D0161EUL,(int32_t)0x92D22FD9UL}},
    {{(int32_t)0X42244481UL,(int32_t)0x9269C3ACUL}},
    {{(int32_t)0X4177CFB1UL,(int32_t)0x920265E4UL}},
    {{(int32_t)0X40CAB958UL,(int32_t)0x919C1781UL}},
    {{(int32_t)0X401D0321UL,(int32_t)0x9136D97DUL}},
    {{(int32_t)0X3F6EAEB8UL,(int32_t)0x90D2ACD4UL}},
    {{(int32_t)0X3EBFBDCDUL,(int32_t)0x906F927CUL}},
    {{(int32_t)0X3E10320DUL,(int32_t)0x900D8B69UL}},
    {{(int32_t)0X3D600D2CUL,(int32_t)0x8FAC988FUL}},
    {{(int32_t)0X3CAF50DAUL,(int32_t)0x8F4CBADBUL}},
    {{(int32_t)0X3BFDFECDUL,(int32_t)0x8EEDF33BUL}},
    {{(int32_t)0X3B4C18BAUL,(int32_t)0x8E904298UL}},
    {{(int32_t)0X3A99A057UL,(int32_t)0x8E33A9DAUL}},
    {{(int32_t)0X39E6975EUL,(int32_t)0x8DD829E4UL}},
    {{(int32_t)0X3932FF87UL,(int32_t)0x8D7DC399UL}},
    {{(int32_t)0X387EDA8EUL,(int32_t)0x8D2477D8UL}},
    {{(int32_t)0X37CA2A30UL,(int32_t)0x8CCC477DUL}},
    {{(int32_t)0X3714F02AUL,(int32_t)0x8C753362UL}},
    {{(int32_t)0X365F2E3BUL,(int32_t)0x8C1F3C5DUL}},
    {{(int32_t)0X35A8E625UL,(int32_t)0x8BCA6343UL}},
    {{(int32_t)0X34F219A8UL,(int32_t)0x8B76A8E4UL}},
    {{(int32_t)0X343ACA87UL,(int32_t)0x8B240E11UL}},
    {{(int32_t)0X3382FA88UL,(int32_t)0x8AD29394UL}},
    {{(int32_t)0X32CAAB6FUL,(int32_t)0x8A823A36UL}},
    {{(int32_t)0X3211DF04UL,(int32_t)0x8A3302BEUL}},
    {{(int32_t)0X3158970EUL,(int32_t)0x89E4EDEFUL}},
};

static const complex_fract32 dct3_256[]=
{
    {{(int32_t)0X7FFFFFFFUL,(int32_t)0x00000000UL}},
    {{(int32_t)0X7FFD885AUL,(int32_t)0x01921D20UL}},
    {{(int32_t)0X7FF62182UL,(int32_t)0x03242ABFUL}},
    {{(int32_t)0X7FE9CBC0UL,(int32_t)0x04B6195DUL}},
    {{(int32_t)0X7FD8878EUL,(int32_t)0x0647D97CUL}},
    {{(int32_t)0X7FC25596UL,(int32_t)0x07D95B9EUL}},
    {{(int32_t)0X7FA736B4UL,(int32_t)0x096A9049UL}},
    {{(int32_t)0X7F872BF3UL,(int32_t)0x0AFB6805UL}},
    {{(int32_t)0X7F62368FUL,(int32_t)0x0C8BD35EUL}},
    {{(int32_t)0X7F3857F6UL,(int32_t)0x0E1BC2E4UL}},
    {{(int32_t)0X7F0991C4UL,(int32_t)0x0FAB272BUL}},
    {{(int32_t)0X7ED5E5C6UL,(int32_t)0x1139F0CFUL}},
    {{(int32_t)0X7E9D55FCUL,(int32_t)0x12C8106FUL}},
    {{(int32_t)0X7E5FE493UL,(int32_t)0x145576B1UL}},
    {{(int32_t)0X7E1D93EAUL,(int32_t)0x15E21445UL}},
    {{(int32_t)0X7DD6668FUL,(int32_t)0x176DD9DEUL}},
    {{(int32_t)0X7D8A5F40UL,(int32_t)0x18F8B83CUL}},
    {{(int32_t)0X7D3980ECUL,(int32_t)0x1A82A026UL}},
    {{(int32_t)0X7CE3CEB2UL,(int32_t)0x1C0B826AUL}},
    {{(int32_t)0X7C894BDEUL,(int32_t)0x1D934FE5UL}},
    {{(int32_t)0X7C29FBEEUL,(int32_t)0x1F19F97BUL}},
    {{(int32_t)0X7BC5E290UL,(int32_t)0x209F701CUL}},
    {{(int32_t)0X7B5D039EUL,(int32_t)0x2223A4C5UL}},
    {{(int32_t)0X7AEF6323UL,(int32_t)0x23A6887FUL}},
    {{(int32_t)0X7A7D055BUL,(int32_t)0x25280C5EUL}},
    {{(int32_t)0X7A05EEADUL,(int32_t)0x26A82186UL}},
    {{(int32_t)0X798A23B1UL,(int32_t)0x2826B928UL}},
    {{(int32_t)0X7909A92DUL,(int32_t)0x29A3C485UL}},
    {{(int32_t)0X78848414UL,(int32_t)0x2B1F34EBUL}},
    {{(int32_t)0X77FAB989UL,(int32_t)0x2C98FBBAUL}},
    {{(int32_t)0X776C4EDBUL,(int32_t)0x2E110A62UL}},
    {{(int32_t)0X76D94989UL,(int32_t)0x2F875262UL}},
    {{(int32_t)0X7641AF3DUL,(int32_t)0x30FBC54DUL}},
    {{(int32_t)0X75A585CFUL,(int32_t)0x326E54C7UL}},
    {{(int32_t)0X7504D345UL,(int32_t)0x33DEF287UL}},
    {{(int32_t)0X745F9DD1UL,(int32_t)0x354D9057UL}},
    {{(int32_t)0X73B5EBD1UL,(int32_t)0x36BA2014UL}},
    {{(int32_t)0X7307C3D0UL,(int32_t)0x382493B0UL}},
    {{(int32_t)0X72552C85UL,(int32_t)0x398CDD32UL}},
    {{(int32_t)0X719E2CD2UL,(int32_t)0x3AF2EEB7UL}},
    {{(int32_t)0X70E2CBC6UL,(int32_t)0x3C56BA70UL}},
    {{(int32_t)0X7023109AUL,(int32_t)0x3DB832A6UL}},
    {{(int32_t)0X6F5F02B2UL,(int32_t)0x3F1749B8UL}},
    {{(int32_t)0X6E96A99DUL,(int32_t)0x4073F21DUL}},
    {{(int32_t)0X6DCA0D14UL,(int32_t)0x41CE1E65UL}},
    {{(int32_t)0X6CF934FCUL,(int32_t)0x4325C135UL}},
    {{(int32_t)0X6C242960UL,(int32_t)0x447ACD50UL}},
    {{(int32_t)0X6B4AF279UL,(int32_t)0x45CD358FUL}},
    {{(int32_t)0X6A6D98A4UL,(int32_t)0x471CECE7UL}},
    {{(int32_t)0X698C246CUL,(int32_t)0x4869E665UL}},
    {{(int32_t)0X68A69E81UL,(int32_t)0x49B41533UL}},
    {{(int32_t)0X67BD0FBDUL,(int32_t)0x4AFB6C98UL}},
    {{(int32_t)0X66CF8120UL,(int32_t)0x4C3FDFF4UL}},
    {{(int32_t)0X65DDFBD3UL,(int32_t)0x4D8162C4UL}},
    {{(int32_t)0X64E88926UL,(int32_t)0x4EBFE8A5UL}},
    {{(int32_t)0X63EF3290UL,(int32_t)0x4FFB654DUL}},
    {{(int32_t)0X62F201ACUL,(int32_t)0x5133CC94UL}},
    {{(int32_t)0X61F1003FUL,(int32_t)0x5269126EUL}},
    {{(int32_t)0X60EC3830UL,(int32_t)0x539B2AF0UL}},
    {{(int32_t)0X5FE3B38DUL,(int32_t)0x54CA0A4BUL}},
    {{(int32_t)0X5ED77C8AUL,(int32_t)0x55F5A4D2UL}},
    {{(int32_t)0X5DC79D7CUL,(int32_t)0x571DEEFAUL}},
    {{(int32_t)0X5CB420E0UL,(int32_t)0x5842DD54UL}},
    {{(int32_t)0X5B9D1154UL,(int32_t)0x59646498UL}},
};

static const complex_fract32 rfft_128[]=
{
    {{(int32_t)0X7FD8878EUL,(int32_t)0x0647D97CUL}},
    {{(int32_t)0X7F62368FUL,(int32_t)0x0C8BD35EUL}},
    {{(int32_t)0X7E9D55FCUL,(int32_t)0x12C8106FUL}},
    {{(int32_t)0X7D8A5F40UL,(int32_t)0x18F8B83CUL}},
    {{(int32_t)0X7C29FBEEUL,(int32_t)0x1F19F97BUL}},
    {{(int32_t)0X7A7D055BUL,(int32_t)0x25280C5EUL}},
    {{(int32_t)0X78848414UL,(int32_t)0x2B1F34EBUL}},
    {{(int32_t)0X7641AF3DUL,(int32_t)0x30FBC54DUL}},
    {{(int32_t)0X73B5EBD1UL,(int32_t)0x36BA2014UL}},
    {{(int32_t)0X70E2CBC6UL,(int32_t)0x3C56BA70UL}},
    {{(int32_t)0X6DCA0D14UL,(int32_t)0x41CE1E65UL}},
    {{(int32_t)0X6A6D98A4UL,(int32_t)0x471CECE7UL}},
    {{(int32_t)0X66CF8120UL,(int32_t)0x4C3FDFF4UL}},
    {{(int32_t)0X62F201ACUL,(int32_t)0x5133CC94UL}},
    {{(int32_t)0X5ED77C8AUL,(int32_t)0x55F5A4D2UL}},
    {{(int32_t)0X5A82799AUL,(int32_t)0x5A82799AUL}},
    {{(int32_t)0X55F5A4D2UL,(int32_t)0x5ED77C8AUL}},
    {{(int32_t)0X5133CC94UL,(int32_t)0x62F201ACUL}},
    {{(int32_t)0X4C3FDFF4UL,(int32_t)0x66CF8120UL}},
    {{(int32_t)0X471CECE7UL,(int32_t)0x6A6D98A4UL}},
    {{(int32_t)0X41CE1E65UL,(int32_t)0x6DCA0D14UL}},
    {{(int32_t)0X3C56BA70UL,(int32_t)0x70E2CBC6UL}},
    {{(int32_t)0X36BA2014UL,(int32_t)0x73B5EBD1UL}},
    {{(int32_t)0X30FBC54DUL,(int32_t)0x7641AF3DUL}},
    {{(int32_t)0X2B1F34EBUL,(int32_t)0x78848414UL}},
    {{(int32_t)0X25280C5EUL,(int32_t)0x7A7D055BUL}},
    {{(int32_t)0X1F19F97BUL,(int32_t)0x7C29FBEEUL}},
    {{(int32_t)0X18F8B83CUL,(int32_t)0x7D8A5F40UL}},
    {{(int32_t)0X12C8106FUL,(int32_t)0x7E9D55FCUL}},
    {{(int32_t)0X0C8BD35EUL,(int32_t)0x7F62368FUL}},
    {{(int32_t)0X0647D97CUL,(int32_t)0x7FD8878EUL}},
};

static const complex_fract32 fft_64[]=
{
    {{(int32_t)0X7FFFFFFFUL,(int32_t)0x00000000UL}},
    {{(int32_t)0X7FFFFFFFUL,(int32_t)0x00000000UL}},
    {{(int32_t)0X7FFFFFFFUL,(int32_t)0x00000000UL}},
    {{(int32_t)0X7F62368FUL,(int32_t)0xF3742CA2UL}},
    {{(int32_t)0X7D8A5F40UL,(int32_t)0xE70747C4UL}},
    {{(int32_t)0X7A7D055BUL,(int32_t)0xDAD7F3A2UL}},
    {{(int32_t)0X7D8A5F40UL,(int32_t)0xE70747C4UL}},
    {{(int32_t)0X7641AF3DUL,(int32_t)0xCF043AB3UL}},
    {{(int32_t)0X6A6D98A4UL,(int32_t)0xB8E31319UL}},
    {{(int32_t)0X7A7D055BUL,(int32_t)0xDAD7F3A2UL}},
    {{(int32_t)0X6A6D98A4UL,(int32_t)0xB8E31319UL}},
    {{(int32_t)0X5133CC94UL,(int32_t)0x9D0DFE54UL}},
    {{(int32_t)0X7641AF3DUL,(int32_t)0xCF043AB3UL}},
    {{(int32_t)0X5A82799AUL,(int32_t)0xA57D8666UL}},
    {{(int32_t)0X30FBC54DUL,(int32_t)0x89BE50C3UL}},
    {{(int32_t)0X70E2CBC6UL,(int32_t)0xC3A94590UL}},
    {{(int32_t)0X471CECE7UL,(int32_t)0x9592675CUL}},
    {{(int32_t)0X0C8BD35EUL,(int32_t)0x809DC971UL}},
    {{(int32_t)0X6A6D98A4UL,(int32_t)0xB8E31319UL}},
    {{(int32_t)0X30FBC54DUL,(int32_t)0x89BE50C3UL}},
    {{(int32_t)0XE70747C4UL,(int32_t)0x8275A0C0UL}},
    {{(int32_t)0X62F201ACUL,(int32_t)0xAECC336CUL}},
    {{(int32_t)0X18F8B83CUL,(int32_t)0x8275A0C0UL}},
    {{(int32_t)0XC3A94590UL,(int32_t)0x8F1D343AUL}},
    {{(int32_t)0X5A82799AUL,(int32_t)0xA57D8666UL}},
    {{(int32_t)0000000000UL,(int32_t)0x80000000UL}},
    {{(int32_t)0XA57D8666UL,(int32_t)0xA57D8666UL}},
    {{(int32_t)0X5133CC94UL,(int32_t)0x9D0DFE54UL}},
    {{(int32_t)0XE70747C4UL,(int32_t)0x8275A0C0UL}},
    {{(int32_t)0X8F1D343AUL,(int32_t)0xC3A94590UL}},
    {{(int32_t)0X471CECE7UL,(int32_t)0x9592675CUL}},
    {{(int32_t)0XCF043AB3UL,(int32_t)0x89BE50C3UL}},
    {{(int32_t)0X8275A0C0UL,(int32_t)0xE70747C4UL}},
    {{(int32_t)0X3C56BA70UL,(int32_t)0x8F1D343AUL}},
    {{(int32_t)0XB8E31319UL,(int32_t)0x9592675CUL}},
    {{(int32_t)0X809DC971UL,(int32_t)0x0C8BD35EUL}},
    {{(int32_t)0X30FBC54DUL,(int32_t)0x89BE50C3UL}},
    {{(int32_t)0XA57D8666UL,(int32_t)0xA57D8666UL}},
    {{(int32_t)0X89BE50C3UL,(int32_t)0x30FBC54DUL}},
    {{(int32_t)0X25280C5EUL,(int32_t)0x8582FAA5UL}},
    {{(int32_t)0X9592675CUL,(int32_t)0xB8E31319UL}},
    {{(int32_t)0X9D0DFE54UL,(int32_t)0x5133CC94UL}},
    {{(int32_t)0X18F8B83CUL,(int32_t)0x8275A0C0UL}},
    {{(int32_t)0X89BE50C3UL,(int32_t)0xCF043AB3UL}},
    {{(int32_t)0XB8E31319UL,(int32_t)0x6A6D98A4UL}},
    {{(int32_t)0X0C8BD35EUL,(int32_t)0x809DC971UL}},
    {{(int32_t)0X8275A0C0UL,(int32_t)0xE70747C4UL}},
    {{(int32_t)0XDAD7F3A2UL,(int32_t)0x7A7D055BUL}},
};

static const tdct4_twd_fr32 descr = { 256, dct4_twd_256, dct3_256, rfft_128, fft_64 };
const dct_handle_t dct4_32_256=(dct_handle_t)&descr;
const dct_handle_t mdct_32_256=(dct_handle_t)&descr;
