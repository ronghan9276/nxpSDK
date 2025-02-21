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
EW_DEFINE_FONT_RES( WasherListFontXL, 44, 12, 0, 16, 0x0001, 0x000C )
  EW_GLYPH( 0x0001, 4, -30, 22, 30, 29, 0x00000000 ),
  EW_GLYPH( 0x0030, 2, -29, 19, 29, 22, 0x0000055F ),           /* '0' */
  EW_GLYPH( 0x0031, 3, -29, 17, 29, 22, 0x000009FB ),           /* '1' */
  EW_GLYPH( 0x0032, 1, -29, 20, 29, 22, 0x00000C82 ),           /* '2' */
  EW_GLYPH( 0x0033, 1, -29, 20, 29, 22, 0x00001120 ),           /* '3' */
  EW_GLYPH( 0x0034, 0, -29, 22, 29, 22, 0x0000166C ),           /* '4' */
  EW_GLYPH( 0x0035, 1, -29, 20, 29, 22, 0x00001A6E ),           /* '5' */
  EW_GLYPH( 0x0036, 2, -29, 19, 29, 22, 0x00001F5F ),           /* '6' */
  EW_GLYPH( 0x0037, 2, -29, 19, 29, 22, 0x000024B5 ),           /* '7' */
  EW_GLYPH( 0x0038, 1, -29, 20, 29, 22, 0x00002867 ),           /* '8' */
  EW_GLYPH( 0x0039, 1, -29, 20, 29, 22, 0x00002E3A ),           /* '9' */
  EW_GLYPH( 0x003A, 2, -22, 7, 22, 11, 0x000033B3 ),            /* ':' */

  EW_FONT_PIXEL( WasherListFontXL, 0x000034F4 )                 /* ratio 52.20 % */
    0xEF7BDEF7, 0x7BDEF7BD, 0xDEF7BDEF, 0x00001F7B, 0x00000000, 0xDEF7BDCF, 0x01FDEF7B,
    0x6800CF28, 0x80D34051, 0x8C095867, 0x8B403D47, 0x82F0E806, 0xC800DE95, 0x2BC44C65,
    0x1A1D0016, 0xC400686F, 0x394E4B14, 0x1BC3A001, 0xC000D0BF, 0x78CB7E2B, 0x9E958000,
    0x1F0000D0, 0xFC000146, 0x60000630, 0x0003490E, 0x0F52DC7E, 0x66695800, 0xBC4002F3,
    0x319467E2, 0x2661D001, 0x5C800FCD, 0xE478C5E2, 0x03A1D002, 0x1801BC3A, 0x4E41318F,
    0x069A02F1, 0x94099A74, 0xA27E00A7, 0xE600D100, 0x7BFF1000, 0xDEF7BDEF, 0x0000077B,
    0x00000000, 0xFDCFBD90, 0xBD000F7F, 0x7CF908D7, 0x2B7C04BF, 0xCC137500, 0xBBDDFC87,
    0x3440F21F, 0x5BE31763, 0xB837898C, 0xC3F07A01, 0x4BC00D43, 0x801C9196, 0x507BF827,
    0x971E1E00, 0x21830008, 0xC8380079, 0x10300049, 0x626000C9, 0x00000002, 0x08000000,
    0x03060000, 0x09398980, 0x79220600, 0x5E443800, 0xA9140122, 0x506200B0, 0x0B003932,
    0x00AA3E3F, 0x0560C63F, 0x7937826F, 0x30FBC9A1, 0x303D49BE, 0xBBDDF927, 0xDE03F21F,
    0x00ED400E, 0xC846BDAC, 0x000BF7E7, 0x01FEF7BC, 0x8009FF50, 0x0097FB5C, 0x000F7F88,
    0x00000000, 0xEF7BDC40, 0x0000004D, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xF7580000, 0x926F7BDE,
    0x7F7BDEF7, 0x00000000, 0xBDF77A80, 0x18027767, 0x310737FB, 0xF301BFD6, 0x1FAC003F,
    0xFF4437E8, 0x5077FDEF, 0x5DD49C8D, 0xCC1DAE49, 0xFCF1FF20, 0x2626C802, 0xCC00FEC6,
    0x80090FE0, 0x00000587, 0x00080000, 0x00098780, 0x0002E0A8, 0x0000F12E, 0xC0004C55,
    0x4000BC4B, 0xE0001D27, 0x0004D459, 0x003F23F9, 0x09C43710, 0x7A4FF000, 0x60DF8000,
    0x2BF0004D, 0xBF00069E, 0xF0003EA2, 0x0003F515, 0x01F8C3DF, 0xFC61EF80, 0xC0F7C001,
    0xBDEF7FFF, 0xEF7BDEF7, 0x23181E33, 0x00000001, 0xDCFBBC60, 0x4007DFB3, 0x211CF6FE,
    0x05FEFCC6, 0xF2005DAC, 0x88756137, 0xBF3DEFB5, 0x54CC0F42, 0xBF5107BB, 0x3B88BC49,
    0x8378097F, 0x78017C82, 0x40000088, 0x09260000, 0x07927800, 0x647E7800, 0xF6B51003,
    0xF005C617, 0x43D7E7BF, 0x80009DAC, 0x100006E8, 0xFC0059EF, 0x13EFD9EF, 0x88007FA2,
    0x50FDBF31, 0xBF20003F, 0xC0002A87, 0x1000170F, 0x900003C5, 0x02400004, 0xC90F0001,
    0x198013BB, 0x4F733994, 0x67E26A80, 0x4CF77884, 0xDE0BF7D4, 0x78C97CF4, 0xDFDEF7FF,
    0x7B50B983, 0x5EFC8005, 0x67BF7D10, 0xFBF31884, 0x7500003F, 0x0003BDEF, 0x800005E0,
    0x30000137, 0x1C000026, 0x4E800016, 0x180003F9, 0x7000068B, 0xA00007A8, 0x0000BC53,
    0x0169D163, 0x049A8700, 0x1F14E800, 0x7458C000, 0x6A5C0000, 0x10F40002, 0x98C0001F,
    0xE00002FC, 0x0001E786, 0x007E21E8, 0x73893900, 0xDEF7BDEF, 0x1BDEFB0F, 0x00000011,
    0x7B8C0000, 0xDEF7BDEF, 0xB0FDEF7B, 0x0001BDEF, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x7BDE0000, 0xDEF7BDEF, 0x3FBDEF7B, 0x10000030, 0xCC580000, 0xF7BDEF7B,
    0x207F7BDE, 0x49000038, 0x01200000, 0x00058100, 0x40004818, 0x8B000020, 0x3DCFB5C8,
    0xC08095BF, 0xFAA211EE, 0x044902FF, 0x8460DCC0, 0xF3DEFB58, 0xA83E307B, 0xA20F76BD,
    0x80CF17BE, 0x85CC04EC, 0x41D00017, 0x11140001, 0x00C48000, 0x00045C00, 0x000120E0,
    0xC000110F, 0x07EF1418, 0xE731C680, 0x5F001FF3, 0xFDC82551, 0xFFCE493D, 0x2FACBC43,
    0xBDFFBE78, 0x7FC937FF, 0x0033B9E2, 0x78807B3C, 0x108CFBEF, 0x00BFFD63, 0x7BEDF3C0,
    0xA009BFFF, 0xC833DFFE, 0xAC05FF7A, 0xAFE4025F, 0xF6B13661, 0x8137FFBD, 0x83DB8CD1,
    0xA366BB9C, 0x8803FE43, 0x74518BDF, 0x7C8F8000, 0x07C58000, 0x00A08C00, 0x00188780,
    0xF9E061C0, 0x95BF3DCE, 0x7F634C90, 0xBDEA884F, 0x00FFA810, 0xD64CBF44, 0x7BFFD117,
    0x03E60AF7, 0x64AEEA23, 0xE05787F4, 0x935005F9, 0x00FC8B91, 0x0041587C, 0x02499030,
    0x00313600, 0x00282780, 0x03E28881, 0x721C7850, 0x50E4BC01, 0x0F405BC5, 0x7C43787E,
    0x62DF183D, 0xC43FE44C, 0x87EEF7DA, 0x176307F1, 0x200FF3C0, 0xE499BF7F, 0xDEE05FDC,
    0xF7BDEF7B, 0xBDEF7BDE, 0x0005DEF7, 0xF1000000, 0xBDEF7BDC, 0xEF7BDEF7, 0x0027413D,
    0x026785F8, 0x3F11E780, 0x00E9A000, 0x04C69D00, 0x00B93900, 0x00D42FC0, 0x00B8B900,
    0x00B217C0, 0x0007C980, 0x0004C13C, 0x4000152E, 0x0A8001B1, 0xC418000A, 0x09360000,
    0x00787800, 0x000E0C80, 0xC0009130, 0x0E0004C0, 0x48180002, 0x00026000, 0x60002410,
    0x04100000, 0x9F7B2000, 0x004AF67B, 0x211AFFDE, 0xD806EF46, 0x07D62013, 0xDDFA837C,
    0x99E4BE7B, 0x5F9E1E30, 0xFC1ECF11, 0x407C47E0, 0xF060725C, 0x01E48C00, 0x1024C012,
    0x36040024, 0x0A1E0035, 0x3C013933, 0xC84E12A1, 0x78B440FD, 0x7E42F8C1, 0x9D4FF27B,
    0xF183FD40, 0x13D0FF9E, 0x6A9103E0, 0xEA7FC601, 0x3FEA277F, 0x7C67F8C0, 0x37FFD72B,
    0x09C17FC8, 0x5FDA82BF, 0xD2B06F88, 0x1D9E00F3, 0x0171F2E2, 0x24463364, 0x0785800B,
    0x40408002, 0x31103001, 0x0FC002F8, 0x07FC8F8F, 0x618C59E0, 0x41AEE316, 0x1711F7D4,
    0xEFBD115F, 0xF887BF3D, 0x03AFC40D, 0xC03FF8C0, 0xC493EFBA, 0x800F7B58, 0xFFDCFB58,
    0xDD60026F, 0x3DEB211E, 0x00EDE013, 0x9CC0DBC4, 0xFFEF77E4, 0x6884D64D, 0xE721FFC6,
    0x0DE2741E, 0x87F88071, 0x12A1E1F8, 0x442B2F10, 0x443C01B2, 0xE4007819, 0xE0000B60,
    0x009891E1, 0x1FC0861C, 0x78308B80, 0xFC0B3C00, 0x7EB017C8, 0xAFE64AC0, 0x0C776788,
    0x77EA0DE0, 0xF586F9EF, 0x404FF502, 0xF1810DBC, 0xA3149F7F, 0x302494EF, 0x7B3DFFBF,
    0x00098705, 0x000030F0, 0x8000D839, 0x20002887, 0x0008265E, 0x3C2F10BF, 0xE1FA0077,
    0xEC5F8C0D, 0x2F739077, 0xDCC2C16A, 0x41DFFEF7, 0x02ED40FD, 0xF201FE88, 0xAC839BF7,
    0xBF100BBE, 0x195F07BB, 0x800E4287, 0x195F0E42, 0x3DDDF887, 0x00000000, 0x00000000,
    0xC1EEEFC4, 0x90A1C657, 0xC390A003, 0x0001C657

  EW_FONT_KERNING_CODES( WasherListFontXL )
  EW_FONT_KERNING_VALUES( WasherListFontXL )
EW_END_OF_FONT_RES( WasherListFontXL )

/* Embedded Wizard */
