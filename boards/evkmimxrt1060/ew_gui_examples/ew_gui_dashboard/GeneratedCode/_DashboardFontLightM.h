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
* Version  : 10.0
* Date     : 17.02.2021  8:00:50
* Profile  : iMX_RT
* Platform : NXP.iMX_RT.RGB565
*
*******************************************************************************/

/* Font resource used per default by 'Text' and 'Attributed Text' views to ensure 
   that new views don't remain empty on the screen. */
EW_DEFINE_FONT_RES( DashboardFontLightM, 19, 5, 0, 16, 0x0001, 0x0060 )
  EW_GLYPH( 0x0001, 1, -11, 8, 11, 10, 0x00000000 ),
  EW_GLYPH( 0x0020, 0, 0, 0, 0, 4, 0x000000BA ),                /* ' ' */
  EW_GLYPH( 0x0021, 1, -12, 2, 12, 4, 0x000000BA ),             /* '!' */
  EW_GLYPH( 0x0022, 1, -11, 4, 4, 6, 0x00000105 ),              /* '"' */
  EW_GLYPH( 0x0023, 0, -11, 11, 11, 11, 0x00000140 ),           /* '#' */
  EW_GLYPH( 0x0024, 0, -13, 9, 15, 9, 0x000002FD ),             /* '$' */
  EW_GLYPH( 0x0025, 0, -12, 14, 13, 15, 0x000004AD ),           /* '%' */
  EW_GLYPH( 0x0026, 1, -12, 11, 13, 13, 0x000006EF ),           /* '&' */
  EW_GLYPH( 0x0027, 1, -11, 2, 4, 3, 0x000008FD ),              /* ''' */
  EW_GLYPH( 0x0028, 0, -13, 6, 16, 6, 0x0000091B ),             /* '(' */
  EW_GLYPH( 0x0029, 0, -13, 5, 16, 6, 0x00000A08 ),             /* ')' */
  EW_GLYPH( 0x002A, 0, -12, 7, 7, 7, 0x00000AEA ),              /* '*' */
  EW_GLYPH( 0x002B, 0, -9, 8, 8, 9, 0x00000B84 ),               /* '+' */
  EW_GLYPH( 0x002C, 1, -2, 2, 5, 4, 0x00000C2F ),               /* ',' */
  EW_GLYPH( 0x002D, 1, -5, 5, 2, 7, 0x00000C65 ),               /* '-' */
  EW_GLYPH( 0x002E, 1, -2, 2, 2, 4, 0x00000C9A ),               /* '.' */
  EW_GLYPH( 0x002F, 0, -11, 8, 13, 8, 0x00000CB0 ),             /* '/' */
  EW_GLYPH( 0x0030, 1, -12, 8, 13, 10, 0x00000D98 ),            /* '0' */
  EW_GLYPH( 0x0031, 0, -11, 5, 11, 7, 0x00000EFA ),             /* '1' */
  EW_GLYPH( 0x0032, 0, -12, 9, 12, 9, 0x00000F63 ),             /* '2' */
  EW_GLYPH( 0x0033, 0, -12, 8, 13, 9, 0x000010C1 ),             /* '3' */
  EW_GLYPH( 0x0034, 0, -11, 10, 11, 10, 0x0000123A ),           /* '4' */
  EW_GLYPH( 0x0035, 0, -11, 8, 12, 9, 0x00001375 ),             /* '5' */
  EW_GLYPH( 0x0036, 1, -12, 8, 13, 9, 0x000014D4 ),             /* '6' */
  EW_GLYPH( 0x0037, 0, -11, 8, 11, 8, 0x00001643 ),             /* '7' */
  EW_GLYPH( 0x0038, 1, -12, 8, 13, 10, 0x0000173B ),            /* '8' */
  EW_GLYPH( 0x0039, 0, -12, 8, 13, 9, 0x000018EC ),             /* '9' */
  EW_GLYPH( 0x003A, 1, -7, 2, 7, 4, 0x00001A57 ),               /* ':' */
  EW_GLYPH( 0x003B, 1, -7, 2, 10, 4, 0x00001A90 ),              /* ';' */
  EW_GLYPH( 0x003C, 0, -9, 8, 8, 9, 0x00001AE9 ),               /* '<' */
  EW_GLYPH( 0x003D, 1, -7, 8, 5, 10, 0x00001BC3 ),              /* '=' */
  EW_GLYPH( 0x003E, 1, -9, 7, 8, 9, 0x00001C6E ),               /* '>' */
  EW_GLYPH( 0x003F, 0, -12, 8, 12, 8, 0x00001D3B ),             /* '?' */
  EW_GLYPH( 0x0040, 1, -10, 10, 11, 12, 0x00001E52 ),           /* '@' */
  EW_GLYPH( 0x0041, 0, -11, 10, 11, 10, 0x0000201E ),           /* 'A' */
  EW_GLYPH( 0x0042, 1, -12, 8, 13, 10, 0x00002184 ),            /* 'B' */
  EW_GLYPH( 0x0043, 1, -12, 8, 13, 9, 0x000022FE ),             /* 'C' */
  EW_GLYPH( 0x0044, 1, -12, 9, 13, 11, 0x0000243A ),            /* 'D' */
  EW_GLYPH( 0x0045, 1, -12, 8, 12, 9, 0x00002581 ),             /* 'E' */
  EW_GLYPH( 0x0046, 1, -12, 8, 12, 9, 0x000026C8 ),             /* 'F' */
  EW_GLYPH( 0x0047, 1, -12, 8, 13, 10, 0x000027C6 ),            /* 'G' */
  EW_GLYPH( 0x0048, 1, -11, 9, 11, 11, 0x0000290C ),            /* 'H' */
  EW_GLYPH( 0x0049, 1, -11, 2, 11, 4, 0x000029D8 ),             /* 'I' */
  EW_GLYPH( 0x004A, 0, -11, 5, 12, 6, 0x000029F9 ),             /* 'J' */
  EW_GLYPH( 0x004B, 1, -11, 9, 11, 10, 0x00002A71 ),            /* 'K' */
  EW_GLYPH( 0x004C, 1, -11, 7, 11, 8, 0x00002B7F ),             /* 'L' */
  EW_GLYPH( 0x004D, 1, -11, 12, 11, 14, 0x00002C0F ),           /* 'M' */
  EW_GLYPH( 0x004E, 1, -11, 9, 11, 12, 0x00002DA6 ),            /* 'N' */
  EW_GLYPH( 0x004F, 1, -12, 9, 13, 11, 0x00002E99 ),            /* 'O' */
  EW_GLYPH( 0x0050, 1, -12, 8, 12, 10, 0x00003022 ),            /* 'P' */
  EW_GLYPH( 0x0051, 1, -12, 9, 16, 11, 0x00003140 ),            /* 'Q' */
  EW_GLYPH( 0x0052, 1, -12, 9, 12, 10, 0x00003324 ),            /* 'R' */
  EW_GLYPH( 0x0053, 0, -12, 9, 13, 9, 0x00003461 ),             /* 'S' */
  EW_GLYPH( 0x0054, 0, -11, 9, 11, 9, 0x000035F0 ),             /* 'T' */
  EW_GLYPH( 0x0055, 1, -11, 9, 12, 11, 0x000036B9 ),            /* 'U' */
  EW_GLYPH( 0x0056, 0, -11, 10, 11, 10, 0x000037B3 ),           /* 'V' */
  EW_GLYPH( 0x0057, 0, -11, 15, 11, 15, 0x000038EE ),           /* 'W' */
  EW_GLYPH( 0x0058, 0, -11, 10, 11, 10, 0x00003B29 ),           /* 'X' */
  EW_GLYPH( 0x0059, 0, -11, 9, 11, 9, 0x00003C84 ),             /* 'Y' */
  EW_GLYPH( 0x005A, 0, -11, 9, 11, 9, 0x00003D88 ),             /* 'Z' */
  EW_GLYPH( 0x005B, 1, -13, 4, 16, 5, 0x00003ECF ),             /* '[' */
  EW_GLYPH( 0x005C, 0, -11, 8, 13, 8, 0x00003F55 ),             /* '\' */
  EW_GLYPH( 0x005D, 0, -13, 4, 16, 5, 0x00004041 ),             /* ']' */
  EW_GLYPH( 0x005E, 0, -10, 7, 5, 7, 0x000040C6 ),              /* '^' */
  EW_GLYPH( 0x005F, 0, 0, 7, 1, 7, 0x00004139 ),                /* '_' */
  EW_GLYPH( 0x0060, 0, -12, 5, 4, 5, 0x0000415C ),              /* '`' */
  EW_GLYPH( 0x0061, 0, -8, 8, 9, 9, 0x0000419E ),               /* 'a' */
  EW_GLYPH( 0x0062, 1, -12, 8, 13, 9, 0x000042DE ),             /* 'b' */
  EW_GLYPH( 0x0063, 0, -8, 8, 9, 8, 0x000043FE ),               /* 'c' */
  EW_GLYPH( 0x0064, 0, -12, 8, 13, 9, 0x000044E0 ),             /* 'd' */
  EW_GLYPH( 0x0065, 0, -8, 8, 9, 9, 0x0000460F ),               /* 'e' */
  EW_GLYPH( 0x0066, 0, -12, 7, 12, 6, 0x0000474A ),             /* 'f' */
  EW_GLYPH( 0x0067, 0, -8, 9, 12, 9, 0x00004822 ),              /* 'g' */
  EW_GLYPH( 0x0068, 1, -12, 8, 12, 9, 0x000049E5 ),             /* 'h' */
  EW_GLYPH( 0x0069, 1, -12, 2, 12, 4, 0x00004AA0 ),             /* 'i' */
  EW_GLYPH( 0x006A, 0, -12, 3, 16, 4, 0x00004AE9 ),             /* 'j' */
  EW_GLYPH( 0x006B, 1, -12, 7, 12, 8, 0x00004B6C ),             /* 'k' */
  EW_GLYPH( 0x006C, 1, -12, 4, 13, 5, 0x00004C48 ),             /* 'l' */
  EW_GLYPH( 0x006D, 1, -8, 12, 8, 14, 0x00004CB8 ),             /* 'm' */
  EW_GLYPH( 0x006E, 1, -8, 8, 8, 9, 0x00004DB0 ),               /* 'n' */
  EW_GLYPH( 0x006F, 0, -8, 9, 9, 9, 0x00004E44 ),               /* 'o' */
  EW_GLYPH( 0x0070, 1, -8, 8, 12, 9, 0x00004F5B ),              /* 'p' */
  EW_GLYPH( 0x0071, 0, -8, 8, 12, 9, 0x0000507D ),              /* 'q' */
  EW_GLYPH( 0x0072, 1, -8, 6, 8, 7, 0x0000519D ),               /* 'r' */
  EW_GLYPH( 0x0073, 0, -8, 8, 9, 8, 0x0000520A ),               /* 's' */
  EW_GLYPH( 0x0074, 0, -11, 6, 12, 6, 0x00005325 ),             /* 't' */
  EW_GLYPH( 0x0075, 1, -8, 7, 9, 9, 0x000053E6 ),               /* 'u' */
  EW_GLYPH( 0x0076, 0, -8, 9, 8, 9, 0x0000548C ),               /* 'v' */
  EW_GLYPH( 0x0077, 0, -8, 13, 8, 13, 0x00005573 ),             /* 'w' */
  EW_GLYPH( 0x0078, 0, -8, 9, 8, 9, 0x000056E8 ),               /* 'x' */
  EW_GLYPH( 0x0079, 0, -8, 9, 12, 9, 0x000057D9 ),              /* 'y' */
  EW_GLYPH( 0x007A, 0, -8, 8, 8, 8, 0x0000591D ),               /* 'z' */
  EW_GLYPH( 0x007B, 0, -13, 5, 16, 5, 0x00005A2C ),             /* '{' */
  EW_GLYPH( 0x007C, 1, -13, 2, 16, 4, 0x00005AEE ),             /* '|' */
  EW_GLYPH( 0x007D, 0, -13, 5, 16, 5, 0x00005B22 ),             /* '}' */
  EW_GLYPH( 0x007E, 1, -6, 7, 3, 9, 0x00005BDF ),               /* '~' */

  EW_FONT_PIXEL( DashboardFontLightM, 0x00005C39 )              /* ratio 76.31 % */
    0xF7DF7BEB, 0x7DF796FD, 0x0005F7DF, 0x00000000, 0x7DE00000, 0x897DF7DF, 0xAE4401B5,
    0x3F9AC7B9, 0x717A3FEB, 0x3CF1D245, 0x0FF27F18, 0xF02D62E6, 0xAC4FF3FF, 0xFFFEFCFF,
    0xFAD3FCF9, 0x8FFFFB8F, 0x24624FF3, 0x18D63039, 0xF948E663, 0x5F7DF17D, 0xF5BE537C,
    0xBDFADF7B, 0x03183185, 0x0267933C, 0x654601F2, 0xF6FD9E60, 0xF4EBD1F9, 0x1D889F3E,
    0x4E188844, 0xF8277542, 0x0DFDD566, 0x3ADFAEF4, 0x8899D3C0, 0x948884B4, 0xB3FF0C6F,
    0x7D9ABFE7, 0x22673EBE, 0x011C8064, 0x5DBE7BC0, 0xED621FC8, 0x46DE2FB7, 0xC7326B26,
    0xDFE20580, 0xFA730F90, 0x884F3C75, 0x3EF7EBF5, 0xBFFFFB19, 0x7EDFEDE1, 0x7BA7AEDE,
    0x5F88C62D, 0x5013973B, 0xCDD000A3, 0xBF44EC39, 0xF6DFCCC1, 0x7DF81FA0, 0x47221FFF,
    0xFCEFC406, 0x7CC0FFF7, 0x0BDEF77E, 0x040C1467, 0xA37C1FF0, 0x9E2318C7, 0xE73CD721,
    0xDE33BF1C, 0xFFFFFCE7, 0x4F1FF3BF, 0x30100801, 0xFCF9119F, 0xF3EDA13D, 0xCF7CEF7F,
    0xCE73FF1A, 0xEB39EF1E, 0x80EC883F, 0x065F8827, 0x733C5EDF, 0x7F503EE1, 0x00004C44,
    0x36A13110, 0x366782DC, 0x7E21637C, 0xBC606319, 0xBC2C6F8D, 0xF139906F, 0x042671FC,
    0xA899C080, 0xFA4C633F, 0xC658DF0D, 0x0F8020DB, 0x8C278466, 0xDCF07A37, 0x7FC4331D,
    0xD67C419D, 0x06C40100, 0x18CA3180, 0xE8CFBA23, 0xFBF7E2FE, 0x02F7EFC6, 0x5CDF83C0,
    0xBCF38BF1, 0x7DF7DFA3, 0xFCE739CF, 0x3740BAD6, 0xFD05E788, 0xF02D6405, 0x02D640FB,
    0x26B903FD, 0x3E6306E8, 0xD6305FA0, 0xC4037203, 0xDEEEB018, 0xEEFF54A7, 0x47A9CFA9,
    0x46E6A2FC, 0xEB01918C, 0x006200C4, 0xDCCEB019, 0x4D4E3188, 0xEEAA8BF1, 0x759FD67B,
    0x783FFFF6, 0x77EDF77E, 0x0057BD0F, 0x00000000, 0x3848C620, 0x7FFFEF67, 0x7FBDCFB0,
    0x0CE4192F, 0x8F40DCC0, 0x0BF59E09, 0x207EBF18, 0xDC4173FF, 0x9F77F06A, 0xC8C479E7,
    0x2FBEFBEF, 0xFF1231C8, 0x5FFFDEFF, 0xFDDEF7D8, 0x0231812C, 0x7CF3D410, 0xD4E7D931,
    0x3BF7FA0C, 0x80AA05F3, 0x59E22320, 0x39CFFC4F, 0xCF71D3DF, 0xE05F9F7F, 0x04EF0039,
    0x179EBE54, 0x627F857A, 0x5E808FE4, 0x00FA8C09, 0xBFFFFF9C, 0x7D8C7F9E, 0x279539CE,
    0x18C6318C, 0xBAC0006B, 0xB8FBDEF7, 0x3CE739CF, 0xE0444462, 0xDEFDF900, 0x8FFDBC19,
    0x667C876F, 0x03302F6F, 0x5988C8C0, 0x73FFFE3B, 0xCE713D7A, 0x31869FF9, 0xFDECEB12,
    0xDEFBAA5F, 0x826BFCBB, 0x8881C867, 0xF167DFFD, 0xCBE77BDC, 0x00C5F06F, 0xD8307983,
    0xB18BF06B, 0x1F5BDF6A, 0x7F9FF9DF, 0xF7BDEE79, 0x39CE7EDE, 0x117F1FE7, 0xF3815311,
    0x1E03A804, 0xA205B80F, 0x380F282E, 0x2039E205, 0x677E2246, 0xF39B4FFF, 0xC6B7EF7F,
    0xC672A4A9, 0x5ABF1180, 0xD6547AA3, 0xE9F9DE7B, 0x7DFFFF38, 0x9E23679F, 0x7EB1007F,
    0x6E79E223, 0xAFCE7DAF, 0x39CEFE66, 0x891C83E7, 0xFFEFFFF1, 0x3DCF3D4E, 0xF886EA7E,
    0x0CC85855, 0x78CBA80B, 0x2DEF79E9, 0x7D9CFFC6, 0x03EE1102, 0xDF5FD731, 0x7D4E7A7B,
    0xDFB4E7FE, 0xFC37775A, 0xB5BFBAD6, 0xCDF86EEE, 0xCF38BF15, 0xFD40003B, 0x3DFFCC1E,
    0xFEF73E8F, 0x2FD7311E, 0x5FDCF711, 0xDEFFD621, 0xDDFA80FF, 0xFFFFFDF8, 0xBE3FFFFF,
    0x7BDEF7BD, 0x84444444, 0x6B5AD6B9, 0xB7E00005, 0xDFBBDE02, 0xDEFFF641, 0x73BE615F,
    0xD3DFFECB, 0x1BFBBDEF, 0x3015FFFE, 0xD419E79E, 0xB7FCE739, 0xBF7EFFFA, 0x0128146F,
    0xBCF03E56, 0x0DF7F207, 0x39C0AAF8, 0x5DE02CC0, 0xEA305E40, 0xFE229E79, 0xBCE73EFF,
    0x7FB3AF7F, 0x2B3FDFBF, 0xF3CF3C4B, 0xC9F63888, 0xB5EC884C, 0xEA278416, 0x7BEEAE0B,
    0xAC3915DE, 0xD6F1BE73, 0x18C635AE, 0x7DDE7863, 0x24E739CE, 0x70077B9E, 0xFA80FCE7,
    0x7A8F02EF, 0x3C5B80C6, 0x14E5D41F, 0x7BEFB89E, 0x7FE3B8B3, 0xA9FC7FCE, 0xBEB5AD77,
    0x8A8289E5, 0xE39015BA, 0xEF02222F, 0x5FDCE739, 0x7EEF7BA8, 0x01CF1826, 0x58C63584,
    0x739E4FCF, 0xFF3C35DE, 0x0BE4FFFF, 0x220805EC, 0x3A86FC62, 0x3DF76CE7, 0x07B39CE7,
    0x9D608C72, 0x5467DEFF, 0x19EF73CF, 0x56107467, 0x00017901, 0x2AC0BC80, 0x88CE8CE0,
    0xFF9F7A88, 0xFF996739, 0x8A773FF3, 0xE7BC0C88, 0x83D9FF9C, 0x076EF7BA, 0x180B3718,
    0x00E30031, 0x07180000, 0x88883118, 0x9CEA59BA, 0x7BD75BF3, 0x97F739CE, 0x3FF18088,
    0x9F1BDEE7, 0x44E739FF, 0x00888CCE, 0xF3CF3D60, 0x39CE7924, 0xFBF7E78B, 0x00001EFD,
    0xC2223339, 0x9CE7FE2F, 0xEFB9001B, 0xE2FAF7BD, 0x6239CE7F, 0x00044466, 0x82318C6B,
    0x879CE73C, 0xFFFFFFE7, 0x0000000B, 0x648C7200, 0xFFDEFF9D, 0x7B9E7AB7, 0x07467BEF,
    0x03C807AC, 0x03EB00F9, 0x02AC0BC8, 0xB66258EE, 0xFCF7BD67, 0xF3EEFA5F, 0x20FEFBAB,
    0x000000EE, 0x5AD6B980, 0x7BDEC62F, 0xDFBF3C0F, 0x0001F7EF, 0xEF000000, 0x7800000F,
    0x0000006E, 0x7F880000, 0x35EB3CC4, 0x1FDE59CF, 0x2FC0DFE2, 0x203ACC1A, 0x39EB13BB,
    0x3CEC84CF, 0xBFBFF9E0, 0x02F3D604, 0xD90267DE, 0x8E7CC09D, 0x000007F7, 0x00000000,
    0x18D66200, 0xDBF1BC63, 0xDEE7DF7B, 0x9F7B9E07, 0x9DC2F311, 0x05FE3199, 0x945287F5,
    0xF3FA86E2, 0x72C4F32F, 0xE540BA8B, 0x44185918, 0x6442AAFD, 0x9B7EBB24, 0x135AE601,
    0x20BF7E20, 0xAC3FDF66, 0x58130C7F, 0xC6B00FDF, 0xE02F9803, 0x5E6202CD, 0x200CF7C0,
    0xB57E0357, 0x302A7C81, 0x7B3AC246, 0xE9E5FFFF, 0x5F9EEE79, 0xBC61D1DC, 0xE64156B1,
    0x02660BC9, 0x05E64004, 0xE6415633, 0x18CE8CFF, 0xF3D53C6F, 0xB3FAF67F, 0x3D9F7FCE,
    0xDE0C8888, 0xFCFFCE73, 0x7F7BDD42, 0xFCF504CF, 0x34AC0101, 0xF1BF5AD7, 0xBF9DECE7,
    0xEFDFDF32, 0x0000002D, 0x9D612318, 0xF2FFFFBD, 0x3FF73CF4, 0x43A3B8BF, 0x03D6B1BE,
    0x980F3799, 0x22002003, 0x0AB9980F, 0x37C9CF32, 0xAAB1BC63, 0xF5ECFFD7, 0xDFECEB0F,
    0xEF9E03D9, 0x3DCC0737, 0xE7BE41BA, 0xF0322223, 0xE7FE739E, 0x77BDD417, 0x6A302F3F,
    0x6D620000, 0xBFFFFF9E, 0x3FDD916B, 0xB33CF581, 0x144F0057, 0x5D80B9E0, 0xAC08C630,
    0x1F3EF7B3, 0x9EF73AEF, 0x107F889F, 0xE9E02421, 0xE7CDF02E, 0xFE897E77, 0x203ADF9F,
    0x40011E9E, 0x23FE4444, 0xFF39CFFC, 0xFE73ECD5, 0xBDEF4CE7, 0xFF7BDEF7, 0xBD3FBDBF,
    0x4A31C9F7, 0x0000318E, 0x00000000, 0x7E000000, 0x00FB883F, 0x00000000, 0x80180080,
    0xAB1E1338, 0x8F4633B2, 0x3FF9DE31, 0xFF9E65DB, 0x3FE87B3E, 0x1CBF5BC8, 0x0B235150,
    0x786D45FE, 0x1E0AFF2E, 0x7EC5150F, 0x87F52EA0, 0x782E465B, 0xCF00AA8C, 0xB381B7EF,
    0x0373C1F2, 0x7F87FBBF, 0xCE9E0F2F, 0x319FF320, 0x30F198C8, 0x959FCF2D, 0xA4766CF1,
    0x632FF8B1, 0x619D8A30, 0xE787EDFC, 0x0CF1E3CF, 0x20C6644F, 0x44788C72, 0xFAC1E9AE,
    0xFFAC193F, 0xDD7FC0CE, 0x0B18FF85, 0x5546E72A, 0x784CE26D, 0xE43F98B7, 0xBA2C7A6C,
    0x3C6BEF0A, 0xFDBC6B0D, 0xD9EB500C, 0x7F37D720, 0xB1EA9FA0, 0x7DE69E30, 0xA35835D1,
    0x9BF0BD55, 0xDFB07FD9, 0xF93C4C77, 0x7787F78B, 0xCAA635A5, 0x9E9FDE1F, 0x7CDE3589,
    0x6019CF41, 0x000001F9, 0xBDEF7100, 0xE711DEF7, 0x1C9E739C, 0x79F22222, 0xBC0AB381,
    0x203CD41A, 0x2FC035DE, 0x41753C1A, 0x6318CAFC, 0xDEF678C8, 0xE4630F7B, 0xDF32DF3A,
    0x00000007, 0x91AC0000, 0x36AB7CF5, 0xFA01EB50, 0xC09AC605, 0x4D7203FB, 0xD6407FA0,
    0x901F7E02, 0x037E80B5, 0x7E817CC4, 0xEFC88C63, 0x01FDE37E, 0x00000000, 0x7E471880,
    0x9C06F90E, 0xFEDFA1F8, 0xED63C34F, 0xEF2F8D1C, 0xABDEF7BD, 0xDE4BDF90, 0x97BE23F1,
    0x3E7BFFDE, 0xABE73DF6, 0x7A88C6A9, 0xFBF7E7AE, 0x1BF11EFD, 0x7E329DDD, 0x3D258C63,
    0xF588F7C6, 0xFA5FB3DE, 0x6F5CFF9C, 0x00FEF026, 0xF7310000, 0xDD9E0DFD, 0x55F5973F,
    0xA60611DD, 0x18530004, 0xEA391DC4, 0x3EAF33DE, 0x03FE7FE7, 0x1F9EFFEF, 0x6EFFEADF,
    0x87327DEA, 0x42000188, 0x7825F502, 0x293DEFFD, 0x939FF9F7, 0x1E600C40, 0x3BF10000,
    0xADF877E7, 0xFA927FEF, 0x445B3C6A, 0x78881602, 0x9E1FE780, 0xBDCE7E8F, 0xF3FF38CD,
    0xFEF17F3D, 0x57E5FFEF, 0x56ADFFEF, 0x11AACABF, 0x278C6311, 0xECF775F8, 0xBF7EFDF0,
    0xE097D52F, 0xEF7BFF5D, 0x3FF3BF92, 0xCD731177, 0x773BFFE0, 0x6FBEF188, 0xDCF9E162,
    0xEBE3AB5F, 0x2467944F, 0x00000000, 0xFF73BF18, 0xE4E3DFBF, 0x47EE673E, 0x0EA3197E,
    0x7518CBE3, 0xA9CFB5E8, 0xFEE79EC5, 0xDFB99C5F, 0xF7CFF855, 0xAAA7F79C, 0x0A9EF59F,
    0xCF511E06, 0xCDDBFF3E, 0x9F67FE77, 0x7F781325, 0xE3000000, 0xF752673B, 0xFDACD5EE,
    0x006117E4, 0x00000000, 0xFFFDFBE1, 0x071AF673, 0xF3F7E000, 0x6AD39BFF, 0x60000067,
    0x989F75A4, 0xDE0996CF, 0x6000001F, 0xECF206FC, 0xF58B5381, 0x8CEB178F, 0x02FF4607,
    0xEF81F3E6, 0x3FBC9959, 0x00000000, 0xFF2749E2, 0x5D59CEAB, 0xC73BBBF5, 0x78C7FCEF,
    0xEF71DDEF, 0xBF5AF1DD, 0xF2BB151A, 0x10580D37, 0x00000000, 0xE35D0000, 0xEF1A673B,
    0x73357BDD, 0x2422FCCF, 0x00000000, 0xFFBFFBC0, 0xFFAB782F, 0xDF58FCEF, 0x8896F593,
    0x22012981, 0x5F549624, 0xEBC23B88, 0xB92EB3DC, 0xE87B3ECF, 0x97F9DFAA, 0x5FFBDEF1,
    0xA357EB1F, 0x13481863, 0x83908400, 0xDEEB1E37, 0xFB3C3B3B, 0x4884CFFC, 0x803FBC00,
    0xBFFF7FF7, 0x7FF7ADE5, 0x957EB3E2, 0x01222FE3, 0x8C09840B, 0x9F71F3C3, 0x38C3EF7B,
    0x46177CFB, 0xA7980000, 0x718EFD47, 0xF731FFFB, 0x0000062C, 0xBDFFE800, 0x7EB91DFF,
    0x506E73FF, 0xB1C86319, 0xBFB039BF, 0xAA37FFFC, 0x4814777F, 0xAEEF7BDC, 0xE739CF72,
    0x03388087, 0xAFEE7D60, 0x2FEBE39F, 0x001233CB, 0xCC413C00, 0x73DE2CF7, 0xEF3C2F56,
    0x0002C838, 0xD6290000, 0x9EF73CEB, 0x79F773CF, 0xA83F3FEB, 0xB819E79F, 0xF11F8C61,
    0x3587BE1C, 0xFF86358A, 0xEB2FA887, 0x254F5381, 0x3E783E94, 0x5E85BF3C, 0xBE4E49F3,
    0xE1F23998, 0xCA2349F9, 0x94F90DB3, 0xA3DF855F, 0x336ABECA, 0x151B7FD4, 0xF5DAC1E3,
    0x624731A8, 0xDE7831CF, 0x781BF91F, 0xB3CBCC97, 0xF8AC6F26, 0xBF7DE075, 0xA2004267,
    0x7E2737FB, 0x554EEA73, 0xE6BD4F2F, 0x79E7CF07, 0xFC630E06, 0x0F7C3A88, 0x86358B33,
    0x2FA887DF, 0x7D6703C7, 0xFD635095, 0x88263781, 0x6B7505F7, 0x20BF6781, 0xEFDFBF7E,
    0xE738ABF7, 0xE7A6789C, 0xC4BEA279, 0x3C857EF8, 0x33CE20FD, 0x88DEBFE1, 0x739D4630,
    0xFC1183CE, 0x86FE553B, 0x30460000, 0x1D723F7E, 0x00002DE2, 0xF10AC640, 0x5518CF3F,
    0x64000000, 0x4DF6411A, 0x01051BF9, 0x57EE0200, 0x4EA1F37C, 0xCC400000, 0x86FEF29C,
    0xDA230F5C, 0x59C77FFD, 0x0027BEDF

  EW_FONT_KERNING_CODES( DashboardFontLightM )
  EW_FONT_KERNING_VALUES( DashboardFontLightM )
EW_END_OF_FONT_RES( DashboardFontLightM )

/* Embedded Wizard */
