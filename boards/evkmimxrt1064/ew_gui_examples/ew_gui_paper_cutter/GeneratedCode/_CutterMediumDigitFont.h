/*******************************************************************************
*
* E M B E D D E D   W I Z A R D   P R O J E C T
*
*                                                Copyright (c) TARA Systems GmbH
*                                    written by Paul Banach and Manfred Schweyer
*
********************************************************************************
*
* This software is delivered "as is" and shows the usage of other software 
* components. It is provided as an example software which is intended to be 
* modified and extended according to particular requirements.
* 
* TARA Systems hereby disclaims all warranties and conditions with regard to the
* software, including all implied warranties and conditions of merchantability 
* and non-infringement of any third party IPR or other rights which may result 
* from the use or the inability to use the software.
*
* This file was generated automatically by Embedded Wizard Studio.
*
* Please do not make any modifications of this file! The modifications are lost
* when the file is generated again by Embedded Wizard Studio!
*
* Version  : 9.30
* Date     : 14.02.2020  8:00:50
* Profile  : iMX_RT
* Platform : NXP.iMX_RT.RGB565
*
*******************************************************************************/

/* This is a font resource. */
EW_DEFINE_FONT_RES( CutterMediumDigitFont, 36, 10, 0, 16, 0x0001, 0x000E )
  EW_GLYPH( 0x0001, 1, -27, 15, 27, 17, 0x00000000 ),
  EW_GLYPH( 0x002C, 0, -5, 7, 11, 8, 0x000003D9 ),              /* ',' */
  EW_GLYPH( 0x002E, 2, -5, 6, 5, 11, 0x00000498 ),              /* '.' */
  EW_GLYPH( 0x0030, 2, -27, 18, 27, 22, 0x0000050A ),           /* '0' */
  EW_GLYPH( 0x0031, 3, -27, 12, 27, 22, 0x000008FE ),           /* '1' */
  EW_GLYPH( 0x0032, 1, -27, 20, 27, 22, 0x00000AE2 ),           /* '2' */
  EW_GLYPH( 0x0033, 1, -27, 19, 27, 22, 0x00000F45 ),           /* '3' */
  EW_GLYPH( 0x0034, 1, -27, 20, 27, 22, 0x00001411 ),           /* '4' */
  EW_GLYPH( 0x0035, 2, -27, 19, 27, 22, 0x00001784 ),           /* '5' */
  EW_GLYPH( 0x0036, 2, -27, 19, 27, 22, 0x00001C0C ),           /* '6' */
  EW_GLYPH( 0x0037, 1, -27, 19, 27, 22, 0x0000208E ),           /* '7' */
  EW_GLYPH( 0x0038, 2, -27, 18, 27, 22, 0x0000242E ),           /* '8' */
  EW_GLYPH( 0x0039, 1, -27, 19, 27, 22, 0x000028D1 ),           /* '9' */
  EW_GLYPH( 0x003A, 2, -21, 6, 21, 10, 0x00002D57 ),            /* ':' */

  EW_FONT_PIXEL( CutterMediumDigitFont, 0x00002E95 )            /* ratio 53.49 % */
    0xF7BDEF71, 0xBDEF7BDE, 0xDEF71837, 0x37BDEF7B, 0x16601561, 0x3EF8039C, 0x5A825678,
    0x381F7C03, 0xC40F9807, 0x89A8807A, 0x3EF803F7, 0xAC60133C, 0x38005732, 0xF002F7C7,
    0xC000C7AC, 0xE000FBF7, 0x4F000989, 0x7EF8004C, 0xF59E001F, 0xE39C0018, 0x558C017B,
    0xEF800AE6, 0x510133C3, 0x9807EF13, 0x807AC40F, 0x80E703EF, 0x0D6A095A, 0x7DF007B8,
    0x0B300AB0, 0xDEF7BDC6, 0xF84DEF7B, 0x00077BDD, 0x18216000, 0xF0F07A64, 0xF0679F12,
    0x1678F5A6, 0x9E0FEDF9, 0xFC65FDFF, 0x9819BD52, 0x4BF19819, 0xFBF982F5, 0x4DFFFBDF,
    0x95BCE780, 0x01E7BD64, 0xF10017CF, 0x001FC83D, 0xA05F92FC, 0x10BBBDF6, 0x37EA163F,
    0x52C2BF18, 0x445C0B81, 0x1501446D, 0x200789D8, 0x58008191, 0x90018988, 0x02000058,
    0x00000000, 0x00000000, 0x4C400000, 0x0AC4800C, 0xFE42C004, 0xCE2400F1, 0x81501440,
    0x1A068151, 0x6FC61651, 0x8B037E30, 0x77BED40E, 0x2F89A217, 0x502F8800, 0x57E4025F,
    0x93EFFEA0, 0x02FFBD64, 0x807FF640, 0x4AFFBF98, 0x05BEF7A8, 0x19BFFEB9, 0x0004EDC0,
    0x7BD40062, 0xFFFD982F, 0x2B7E00CD, 0x00000001, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0xFFBF5880, 0x0ADFFFBD, 0x2576F300, 0xE0277D59,
    0xDE20037B, 0xC000FD06, 0xD10B907A, 0x037F7BFF, 0x2B7C345E, 0x04627FA9, 0xFC40A785,
    0x05C08D20, 0x0098003C, 0xDEF7B8C0, 0x03107801, 0x00B0F800, 0x03F03980, 0x12B1A300,
    0xA304F200, 0x126E2001, 0x9FE20007, 0xE0013FC4, 0x006F883F, 0x5F106FC0, 0xC457C001,
    0x3DF00057, 0xD00057C4, 0x0015F10F, 0x02BE22F4, 0xAF88B980, 0x88BE6000, 0xDEF7BDDF,
    0xF7BDEF7B, 0x000007F1, 0x00000000, 0xE7DAE400, 0x003DFD9E, 0x3108F77A, 0x00FFEF9E,
    0xF90015BF, 0x000AF84D, 0xE20F507A, 0x42EEF73D, 0x7FC45CBC, 0x5037E306, 0xF803583C,
    0x554F1110, 0x460301FD, 0x5FBF7EFC, 0x00911201, 0x000A1F10, 0x0D127731, 0xE7BDEF78,
    0x009FE24D, 0x000F6780, 0x00005580, 0xDE00FDF2, 0x0AF9EF7B, 0x9E20034F, 0x001983DF,
    0x000B11A0, 0xF73CE064, 0x03009BDE, 0x12201426, 0x017E0477, 0xDC899434, 0x137E304F,
    0x7E44E863, 0xD05DDEE7, 0x6F0009B8, 0xC8017721, 0xDBF104DF, 0xF318846B, 0xF00017FB,
    0x00EF7BDD, 0x0003CF00, 0x80001A20, 0x3500004E, 0x01780001, 0x00A4E800, 0x0BC8B180,
    0x059C5C00, 0x06B07A00, 0x6C931800, 0x2F06E000, 0xB306B000, 0x64BE4000, 0xF06F0003,
    0xC5980006, 0x9A200053, 0xBF0001F8, 0xF7BDCE20, 0xDEFB0DDE, 0x000001F7, 0x00240000,
    0xDEF7FE00, 0xF7BDEF7B, 0xBEF7D86E, 0x00000000, 0x00000000, 0x00000000, 0xEF7BDE40,
    0x7BDEF7BD, 0x020FBDEF, 0x00098000, 0x70000240, 0xF7BDEEB1, 0x7DEF7BDE, 0x4000B890,
    0x89800120, 0x12240009, 0xF4620400, 0x4DFFF73E, 0x11AF6120, 0x03FF79F2, 0xF9002226,
    0x2000181F, 0xFA20C60E, 0x905EEF7F, 0x6F9F6793, 0x07F464AF, 0x8127887F, 0x000141E7,
    0x98000617, 0xF5000000, 0x007EFDFB, 0xAAAAAC13, 0x18C45C02, 0xC1EA0681, 0x45D8C4C3,
    0x6F0E0FAC, 0x3DEEFC62, 0x3887A81D, 0xC1F18001, 0xF9E005D8, 0x6FDFC807, 0xED63108E,
    0xEB90002F, 0x000EE7DB, 0xCFDFEFC6, 0x2EF40008, 0x00B7C000, 0xC607DE00, 0x401DEFBB,
    0xCF6FE44D, 0xB791A001, 0x27035000, 0x19E0E001, 0xAC70A000, 0xB7E7B9DF, 0xBFC408C0,
    0x7FF5442B, 0x025F81E0, 0x08083FF2, 0x60397100, 0x0E9EE77C, 0xFDA8078C, 0x383F5884,
    0x29E03E20, 0xE004603C, 0xF000088F, 0x00241E40, 0x26006030, 0xC03E0564, 0x1AC28445,
    0x1A2C1EA0, 0xD6215FF1, 0x21723F07, 0x81D3DCFA, 0x0007E899, 0x03AF82F5, 0x5807EB10,
    0xB18847BB, 0xDEEFC376, 0xF7BDEF7B, 0xBDEF7BDE, 0x00005EF7, 0x00100000, 0xDEEFD400,
    0xF7BDEF7B, 0xE06F7BDE, 0xA8330005, 0xB87E0001, 0xB249E000, 0x1F8BC000, 0x4C41A800,
    0x0098D000, 0x05E20C60, 0x000A8D00, 0x000BC2C8, 0x2000351A, 0xFC00170B, 0x10005182,
    0x78001F0B, 0x60009883, 0x15800262, 0x3E000BC4, 0x998000AC, 0x87C000F8, 0x0CF0001A,
    0x62F0005C, 0xC0D40014, 0xFAC40007, 0xFFFDEFFD, 0xEDE60056, 0x4EFAB24A, 0xC4006FD0,
    0x0005A8DB, 0xFB50B8AB, 0x45705DDE, 0xF1837EA1, 0x0709281B, 0x09806178, 0x8130904C,
    0x07031909, 0xA8D0A838, 0x0AFC60DF, 0xBED46A97, 0xC2DE1777, 0x7F2012FA, 0x1800E413,
    0x001D7E09, 0x0AF87EF1, 0x27BBDF73, 0xD078D79E, 0x8DBC60EF, 0x01721F99, 0x583DF12B,
    0x30230B00, 0x144E6000, 0xC81CC2C0, 0xF8C4CC05, 0xBB20F741, 0x581E37E1, 0x0AFFDEFB,
    0x006FC33C, 0x3D88F8C0, 0xBC1B9801, 0xAB24AEFF, 0xAC402FFF, 0x7767B9DF, 0x2BB79802,
    0x01BB58C4, 0x58801BEF, 0x0013981F, 0xAC3442CF, 0x781D3DFF, 0x4EE81993, 0xC7C43EB1,
    0x26A058C6, 0x00FC1E1E, 0x2046647F, 0x000B0501, 0x00480C80, 0x0403F120, 0xF80B1850,
    0x27743F80, 0x0AA02ECF, 0x6FDEFFD6, 0x004BE080, 0x01DC4901, 0xE44C3FC8, 0xF5149EFE,
    0xC12217FE, 0xF9EFFDF3, 0x00051B4D, 0x8002E262, 0x000F905F, 0x07E0F7E2, 0x16F79F20,
    0xEF71026A, 0xF1819BFF, 0x3FD40001, 0xFDF18000, 0xA7C88002, 0xCF007EF7, 0x7E32FEFF,
    0xCC0CDEA9, 0xA5F8CC0C, 0xFBFF3D7A, 0x0000004B, 0x00000000, 0x2FEFFCF0, 0xCDEA97E3,
    0x8CC0CCC0, 0x0017AA5F

  EW_FONT_KERNING_CODES( CutterMediumDigitFont )
  EW_FONT_KERNING_VALUES( CutterMediumDigitFont )
EW_END_OF_FONT_RES( CutterMediumDigitFont )

/* Embedded Wizard */
