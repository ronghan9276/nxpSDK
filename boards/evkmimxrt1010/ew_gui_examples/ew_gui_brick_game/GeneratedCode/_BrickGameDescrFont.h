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

/* Font resource : 'BrickGame::DescrFont' */
EW_DEFINE_FONT_RES( BrickGameDescrFont, 9, 3, 0, 16, 0x0001, 0x00C0 )
  EW_GLYPH( 0x0001, 0, -7, 6, 7, 6, 0x00000000 ),
  EW_GLYPH( 0x0020, 0, 0, 0, 0, 6, 0x00000090 ),                /* ' ' */
  EW_GLYPH( 0x0021, 2, -7, 2, 8, 6, 0x00000090 ),               /* '!' */
  EW_GLYPH( 0x0022, 1, -7, 4, 3, 6, 0x000000C9 ),               /* '"' */
  EW_GLYPH( 0x0023, 0, -7, 6, 7, 6, 0x000000FF ),               /* '#' */
  EW_GLYPH( 0x0024, 0, -8, 5, 10, 6, 0x000001A7 ),              /* '$' */
  EW_GLYPH( 0x0025, 0, -7, 6, 8, 6, 0x0000026F ),               /* '%' */
  EW_GLYPH( 0x0026, 0, -7, 6, 8, 6, 0x0000034F ),               /* '&' */
  EW_GLYPH( 0x0027, 2, -7, 2, 3, 6, 0x0000041F ),               /* ''' */
  EW_GLYPH( 0x0028, 1, -8, 4, 10, 6, 0x00000438 ),              /* '(' */
  EW_GLYPH( 0x0029, 1, -8, 3, 10, 6, 0x000004AC ),              /* ')' */
  EW_GLYPH( 0x002A, 0, -7, 5, 5, 6, 0x0000050F ),               /* '*' */
  EW_GLYPH( 0x002B, 0, -5, 6, 5, 6, 0x0000056F ),               /* '+' */
  EW_GLYPH( 0x002C, 1, -2, 3, 4, 6, 0x000005CF ),               /* ',' */
  EW_GLYPH( 0x002D, 1, -4, 4, 2, 6, 0x000005FF ),               /* '-' */
  EW_GLYPH( 0x002E, 1, -2, 3, 3, 6, 0x00000622 ),               /* '.' */
  EW_GLYPH( 0x002F, 0, -7, 5, 8, 6, 0x00000640 ),               /* '/' */
  EW_GLYPH( 0x0030, 0, -7, 6, 8, 6, 0x000006A9 ),               /* '0' */
  EW_GLYPH( 0x0031, 0, -7, 5, 7, 6, 0x00000764 ),               /* '1' */
  EW_GLYPH( 0x0032, 0, -7, 5, 7, 6, 0x000007C7 ),               /* '2' */
  EW_GLYPH( 0x0033, 0, -7, 5, 8, 6, 0x0000084F ),               /* '3' */
  EW_GLYPH( 0x0034, 0, -7, 6, 7, 6, 0x000008FA ),               /* '4' */
  EW_GLYPH( 0x0035, 0, -7, 5, 8, 6, 0x00000986 ),               /* '5' */
  EW_GLYPH( 0x0036, 0, -7, 5, 8, 6, 0x00000A2A ),               /* '6' */
  EW_GLYPH( 0x0037, 0, -7, 5, 7, 6, 0x00000ADB ),               /* '7' */
  EW_GLYPH( 0x0038, 0, -7, 5, 8, 6, 0x00000B55 ),               /* '8' */
  EW_GLYPH( 0x0039, 0, -7, 5, 7, 6, 0x00000C17 ),               /* '9' */
  EW_GLYPH( 0x003A, 2, -5, 2, 6, 6, 0x00000CB7 ),               /* ':' */
  EW_GLYPH( 0x003B, 1, -5, 3, 7, 6, 0x00000CF4 ),               /* ';' */
  EW_GLYPH( 0x003C, 0, -6, 5, 7, 6, 0x00000D49 ),               /* '<' */
  EW_GLYPH( 0x003D, 0, -4, 5, 3, 6, 0x00000DC2 ),               /* '=' */
  EW_GLYPH( 0x003E, 1, -6, 4, 7, 6, 0x00000E13 ),               /* '>' */
  EW_GLYPH( 0x003F, 1, -7, 4, 8, 6, 0x00000E7D ),               /* '?' */
  EW_GLYPH( 0x0040, 0, -7, 6, 9, 6, 0x00000EF3 ),               /* '@' */
  EW_GLYPH( 0x0041, 0, -7, 6, 7, 6, 0x00000FDB ),               /* 'A' */
  EW_GLYPH( 0x0042, 0, -7, 5, 7, 6, 0x00001075 ),               /* 'B' */
  EW_GLYPH( 0x0043, 0, -7, 5, 8, 6, 0x0000110C ),               /* 'C' */
  EW_GLYPH( 0x0044, 0, -7, 6, 7, 6, 0x000011A3 ),               /* 'D' */
  EW_GLYPH( 0x0045, 1, -7, 4, 7, 6, 0x0000122F ),               /* 'E' */
  EW_GLYPH( 0x0046, 1, -7, 4, 7, 6, 0x000012A7 ),               /* 'F' */
  EW_GLYPH( 0x0047, 0, -7, 5, 8, 6, 0x0000130B ),               /* 'G' */
  EW_GLYPH( 0x0048, 0, -7, 5, 7, 6, 0x000013BA ),               /* 'H' */
  EW_GLYPH( 0x0049, 0, -7, 5, 7, 6, 0x00001426 ),               /* 'I' */
  EW_GLYPH( 0x004A, 0, -7, 5, 8, 6, 0x0000148A ),               /* 'J' */
  EW_GLYPH( 0x004B, 0, -7, 6, 7, 6, 0x00001503 ),               /* 'K' */
  EW_GLYPH( 0x004C, 1, -7, 4, 7, 6, 0x00001580 ),               /* 'L' */
  EW_GLYPH( 0x004D, 0, -7, 6, 7, 6, 0x000015B5 ),               /* 'M' */
  EW_GLYPH( 0x004E, 0, -7, 5, 7, 6, 0x00001645 ),               /* 'N' */
  EW_GLYPH( 0x004F, 0, -7, 6, 8, 6, 0x000016B0 ),               /* 'O' */
  EW_GLYPH( 0x0050, 0, -7, 5, 7, 6, 0x00001767 ),               /* 'P' */
  EW_GLYPH( 0x0051, 0, -7, 6, 9, 6, 0x000017E0 ),               /* 'Q' */
  EW_GLYPH( 0x0052, 0, -7, 6, 7, 6, 0x000018AC ),               /* 'R' */
  EW_GLYPH( 0x0053, 0, -7, 5, 8, 6, 0x0000193A ),               /* 'S' */
  EW_GLYPH( 0x0054, 0, -7, 6, 7, 6, 0x000019F1 ),               /* 'T' */
  EW_GLYPH( 0x0055, 0, -7, 5, 8, 6, 0x00001A50 ),               /* 'U' */
  EW_GLYPH( 0x0056, 0, -7, 6, 7, 6, 0x00001AC3 ),               /* 'V' */
  EW_GLYPH( 0x0057, 0, -7, 6, 7, 6, 0x00001B56 ),               /* 'W' */
  EW_GLYPH( 0x0058, 0, -7, 6, 7, 6, 0x00001BEC ),               /* 'X' */
  EW_GLYPH( 0x0059, 0, -7, 6, 7, 6, 0x00001C85 ),               /* 'Y' */
  EW_GLYPH( 0x005A, 0, -7, 5, 7, 6, 0x00001D02 ),               /* 'Z' */
  EW_GLYPH( 0x005B, 1, -8, 4, 10, 6, 0x00001D91 ),              /* '[' */
  EW_GLYPH( 0x005C, 0, -7, 5, 8, 6, 0x00001DEC ),               /* '\' */
  EW_GLYPH( 0x005D, 1, -8, 3, 10, 6, 0x00001E50 ),              /* ']' */
  EW_GLYPH( 0x005E, 0, -7, 5, 4, 6, 0x00001E95 ),               /* '^' */
  EW_GLYPH( 0x005F, 0, 1, 6, 1, 6, 0x00001EDB ),                /* '_' */
  EW_GLYPH( 0x0060, 0, -7, 4, 2, 6, 0x00001F04 ),               /* '`' */
  EW_GLYPH( 0x0061, 0, -5, 5, 6, 6, 0x00001F1D ),               /* 'a' */
  EW_GLYPH( 0x0062, 0, -7, 5, 8, 6, 0x00001FAB ),               /* 'b' */
  EW_GLYPH( 0x0063, 0, -5, 5, 6, 6, 0x0000203A ),               /* 'c' */
  EW_GLYPH( 0x0064, 0, -7, 5, 8, 6, 0x000020BC ),               /* 'd' */
  EW_GLYPH( 0x0065, 0, -5, 5, 6, 6, 0x0000214A ),               /* 'e' */
  EW_GLYPH( 0x0066, 0, -7, 6, 7, 6, 0x000021E2 ),               /* 'f' */
  EW_GLYPH( 0x0067, 0, -5, 6, 7, 6, 0x00002265 ),               /* 'g' */
  EW_GLYPH( 0x0068, 0, -7, 5, 7, 6, 0x00002325 ),               /* 'h' */
  EW_GLYPH( 0x0069, 0, -7, 5, 7, 6, 0x0000237E ),               /* 'i' */
  EW_GLYPH( 0x006A, 0, -7, 5, 9, 6, 0x000023E1 ),               /* 'j' */
  EW_GLYPH( 0x006B, 0, -7, 6, 7, 6, 0x0000245F ),               /* 'k' */
  EW_GLYPH( 0x006C, 0, -7, 5, 7, 6, 0x000024D2 ),               /* 'l' */
  EW_GLYPH( 0x006D, 0, -5, 6, 5, 6, 0x00002525 ),               /* 'm' */
  EW_GLYPH( 0x006E, 0, -5, 5, 5, 6, 0x00002575 ),               /* 'n' */
  EW_GLYPH( 0x006F, 0, -5, 5, 6, 6, 0x000025C1 ),               /* 'o' */
  EW_GLYPH( 0x0070, 0, -5, 5, 7, 6, 0x00002644 ),               /* 'p' */
  EW_GLYPH( 0x0071, 0, -5, 5, 7, 6, 0x000026C2 ),               /* 'q' */
  EW_GLYPH( 0x0072, 1, -5, 4, 5, 6, 0x00002744 ),               /* 'r' */
  EW_GLYPH( 0x0073, 0, -5, 5, 6, 6, 0x00002789 ),               /* 's' */
  EW_GLYPH( 0x0074, 0, -7, 5, 8, 6, 0x0000281C ),               /* 't' */
  EW_GLYPH( 0x0075, 0, -5, 5, 6, 6, 0x0000289E ),               /* 'u' */
  EW_GLYPH( 0x0076, 0, -5, 6, 5, 6, 0x000028FB ),               /* 'v' */
  EW_GLYPH( 0x0077, 0, -5, 6, 5, 6, 0x0000296B ),               /* 'w' */
  EW_GLYPH( 0x0078, 0, -5, 6, 5, 6, 0x000029E3 ),               /* 'x' */
  EW_GLYPH( 0x0079, 0, -5, 6, 7, 6, 0x00002A5C ),               /* 'y' */
  EW_GLYPH( 0x007A, 0, -5, 5, 5, 6, 0x00002AEE ),               /* 'z' */
  EW_GLYPH( 0x007B, 0, -8, 5, 10, 6, 0x00002B5E ),              /* '{' */
  EW_GLYPH( 0x007C, 2, -8, 2, 10, 6, 0x00002BE3 ),              /* '|' */
  EW_GLYPH( 0x007D, 1, -8, 4, 10, 6, 0x00002BFF ),              /* '}' */
  EW_GLYPH( 0x007E, 0, -4, 6, 3, 6, 0x00002C72 ),               /* '~' */
  EW_GLYPH( 0x00A0, 0, 0, 0, 0, 6, 0x00002CC3 ),
  EW_GLYPH( 0x00A1, 2, -5, 2, 7, 6, 0x00002CC3 ),
  EW_GLYPH( 0x00A2, 0, -8, 5, 10, 6, 0x00002CF5 ),
  EW_GLYPH( 0x00A3, 0, -7, 5, 7, 6, 0x00002D9F ),
  EW_GLYPH( 0x00A4, 0, -7, 6, 7, 6, 0x00002E34 ),
  EW_GLYPH( 0x00A5, 0, -7, 6, 7, 6, 0x00002ED5 ),
  EW_GLYPH( 0x00A6, 2, -8, 2, 10, 6, 0x00002F5C ),
  EW_GLYPH( 0x00A7, 0, -7, 5, 9, 6, 0x00002F89 ),
  EW_GLYPH( 0x00A8, 1, -7, 4, 2, 6, 0x0000304E ),
  EW_GLYPH( 0x00A9, 0, -7, 6, 8, 6, 0x00003077 ),
  EW_GLYPH( 0x00AA, 1, -7, 4, 6, 6, 0x00003143 ),
  EW_GLYPH( 0x00AB, 0, -5, 5, 5, 6, 0x000031A1 ),
  EW_GLYPH( 0x00AC, 0, -3, 5, 3, 6, 0x0000320A ),
  EW_GLYPH( 0x00AD, 1, -4, 4, 2, 6, 0x00003250 ),
  EW_GLYPH( 0x00AE, 0, -7, 5, 5, 6, 0x00003273 ),
  EW_GLYPH( 0x00AF, 1, -7, 3, 1, 6, 0x000032E9 ),
  EW_GLYPH( 0x00B0, 1, -7, 4, 4, 6, 0x000032F9 ),
  EW_GLYPH( 0x00B1, 0, -6, 5, 6, 6, 0x00003353 ),
  EW_GLYPH( 0x00B2, 1, -7, 4, 4, 6, 0x000033CB ),
  EW_GLYPH( 0x00B3, 1, -7, 4, 5, 6, 0x00003413 ),
  EW_GLYPH( 0x00B4, 2, -7, 3, 2, 6, 0x00003460 ),
  EW_GLYPH( 0x00B5, 0, -5, 6, 7, 6, 0x0000347E ),
  EW_GLYPH( 0x00B6, 0, -7, 5, 9, 6, 0x000034EA ),
  EW_GLYPH( 0x00B7, 1, -4, 3, 2, 6, 0x0000358A ),
  EW_GLYPH( 0x00B8, 2, 0, 2, 2, 6, 0x000035A2 ),
  EW_GLYPH( 0x00B9, 1, -7, 4, 4, 6, 0x000035B5 ),
  EW_GLYPH( 0x00BA, 1, -7, 4, 6, 6, 0x000035F7 ),
  EW_GLYPH( 0x00BB, 0, -5, 5, 5, 6, 0x00003668 ),
  EW_GLYPH( 0x00BC, 0, -7, 6, 7, 6, 0x000036C9 ),
  EW_GLYPH( 0x00BD, 0, -7, 6, 7, 6, 0x00003767 ),
  EW_GLYPH( 0x00BE, 0, -7, 6, 7, 6, 0x000037FF ),
  EW_GLYPH( 0x00BF, 1, -5, 3, 7, 6, 0x000038A9 ),
  EW_GLYPH( 0x00C0, 0, -9, 6, 9, 6, 0x00003904 ),
  EW_GLYPH( 0x00C1, 0, -9, 6, 9, 6, 0x000039BB ),
  EW_GLYPH( 0x00C2, 0, -9, 6, 9, 6, 0x00003A6A ),
  EW_GLYPH( 0x00C3, 0, -9, 6, 9, 6, 0x00003B25 ),
  EW_GLYPH( 0x00C4, 0, -9, 6, 9, 6, 0x00003BE7 ),
  EW_GLYPH( 0x00C5, 0, -9, 6, 9, 6, 0x00003CA9 ),
  EW_GLYPH( 0x00C6, -1, -7, 7, 7, 6, 0x00003D69 ),
  EW_GLYPH( 0x00C7, 0, -7, 5, 9, 6, 0x00003E1A ),
  EW_GLYPH( 0x00C8, 1, -9, 4, 9, 6, 0x00003EBD ),
  EW_GLYPH( 0x00C9, 1, -9, 4, 9, 6, 0x00003F47 ),
  EW_GLYPH( 0x00CA, 1, -9, 4, 9, 6, 0x00003FCD ),
  EW_GLYPH( 0x00CB, 1, -9, 4, 9, 6, 0x0000405A ),
  EW_GLYPH( 0x00CC, 0, -9, 5, 9, 6, 0x000040E3 ),
  EW_GLYPH( 0x00CD, 0, -9, 5, 9, 6, 0x0000415B ),
  EW_GLYPH( 0x00CE, 0, -9, 5, 9, 6, 0x000041CF ),
  EW_GLYPH( 0x00CF, 0, -9, 5, 9, 6, 0x0000424A ),
  EW_GLYPH( 0x00D0, 0, -7, 6, 7, 6, 0x000042C1 ),
  EW_GLYPH( 0x00D1, 0, -9, 5, 9, 6, 0x00004373 ),
  EW_GLYPH( 0x00D2, 0, -9, 6, 10, 6, 0x00004406 ),
  EW_GLYPH( 0x00D3, 0, -9, 6, 10, 6, 0x000044D8 ),
  EW_GLYPH( 0x00D4, 0, -9, 6, 10, 6, 0x000045A2 ),
  EW_GLYPH( 0x00D5, 0, -9, 6, 10, 6, 0x00004677 ),
  EW_GLYPH( 0x00D6, 0, -9, 6, 10, 6, 0x00004751 ),
  EW_GLYPH( 0x00D7, 0, -5, 5, 5, 6, 0x0000482B ),
  EW_GLYPH( 0x00D8, 0, -8, 6, 9, 6, 0x0000489E ),
  EW_GLYPH( 0x00D9, 0, -9, 5, 10, 6, 0x00004978 ),
  EW_GLYPH( 0x00DA, 0, -9, 5, 10, 6, 0x00004A08 ),
  EW_GLYPH( 0x00DB, 0, -9, 5, 10, 6, 0x00004A96 ),
  EW_GLYPH( 0x00DC, 0, -9, 5, 10, 6, 0x00004B2F ),
  EW_GLYPH( 0x00DD, 0, -9, 6, 9, 6, 0x00004BC2 ),
  EW_GLYPH( 0x00DE, 0, -7, 5, 7, 6, 0x00004C5C ),
  EW_GLYPH( 0x00DF, 0, -7, 5, 8, 6, 0x00004CDE ),
  EW_GLYPH( 0x00E0, 0, -7, 5, 8, 6, 0x00004D85 ),
  EW_GLYPH( 0x00E1, 0, -7, 5, 8, 6, 0x00004E2B ),
  EW_GLYPH( 0x00E2, 0, -7, 5, 8, 6, 0x00004EDC ),
  EW_GLYPH( 0x00E3, 0, -7, 5, 8, 6, 0x00004F8A ),
  EW_GLYPH( 0x00E4, 0, -7, 5, 8, 6, 0x00005045 ),
  EW_GLYPH( 0x00E5, 0, -8, 5, 9, 6, 0x000050FF ),
  EW_GLYPH( 0x00E6, 0, -5, 6, 6, 6, 0x000051B8 ),
  EW_GLYPH( 0x00E7, 0, -5, 5, 7, 6, 0x0000527C ),
  EW_GLYPH( 0x00E8, 0, -7, 5, 8, 6, 0x00005308 ),
  EW_GLYPH( 0x00E9, 0, -7, 5, 8, 6, 0x000053B8 ),
  EW_GLYPH( 0x00EA, 0, -7, 5, 8, 6, 0x00005470 ),
  EW_GLYPH( 0x00EB, 0, -7, 5, 8, 6, 0x00005529 ),
  EW_GLYPH( 0x00EC, 0, -7, 5, 7, 6, 0x000055EC ),
  EW_GLYPH( 0x00ED, 0, -7, 5, 7, 6, 0x0000564D ),
  EW_GLYPH( 0x00EE, 0, -7, 5, 7, 6, 0x000056B9 ),
  EW_GLYPH( 0x00EF, 0, -7, 5, 7, 6, 0x00005725 ),
  EW_GLYPH( 0x00F0, 0, -7, 5, 8, 6, 0x0000579C ),
  EW_GLYPH( 0x00F1, 0, -7, 5, 7, 6, 0x0000584D ),
  EW_GLYPH( 0x00F2, 0, -7, 5, 8, 6, 0x000058C6 ),
  EW_GLYPH( 0x00F3, 0, -7, 5, 8, 6, 0x00005961 ),
  EW_GLYPH( 0x00F4, 0, -7, 5, 8, 6, 0x00005A04 ),
  EW_GLYPH( 0x00F5, 0, -7, 5, 8, 6, 0x00005AA9 ),
  EW_GLYPH( 0x00F6, 0, -7, 5, 8, 6, 0x00005B56 ),
  EW_GLYPH( 0x00F7, 0, -6, 6, 6, 6, 0x00005C05 ),
  EW_GLYPH( 0x00F8, 0, -6, 5, 7, 6, 0x00005C7E ),
  EW_GLYPH( 0x00F9, 0, -7, 5, 8, 6, 0x00005D17 ),
  EW_GLYPH( 0x00FA, 0, -7, 5, 8, 6, 0x00005D93 ),
  EW_GLYPH( 0x00FB, 0, -7, 5, 8, 6, 0x00005E12 ),
  EW_GLYPH( 0x00FC, 0, -7, 5, 8, 6, 0x00005E93 ),
  EW_GLYPH( 0x00FD, 0, -7, 6, 9, 6, 0x00005F1A ),
  EW_GLYPH( 0x00FE, 0, -7, 5, 9, 6, 0x00005FD6 ),
  EW_GLYPH( 0x00FF, 0, -7, 6, 9, 6, 0x00006061 ),

  EW_FONT_PIXEL( BrickGameDescrFont, 0x00006122 )               /* ratio 91.21 % */
    0x479E79E3, 0x611CFFCD, 0x0540DFBC, 0x5DC0868C, 0x48EF5D77, 0x538BF264, 0x86FADEBB,
    0x0DE5F915, 0xAAD49991, 0x4EFDCEA9, 0xBF3DF8D6, 0x329EB1AC, 0x234A6B3D, 0x7EB12406,
    0x2B91DF91, 0xF19E37CF, 0x5E757C3E, 0xEAFCF3F4, 0x7F3BCFD7, 0x2DF99B25, 0x5FEFEC6F,
    0xFFDFFE27, 0x2F3BEB2C, 0xB38FBE2A, 0x9F7EAEEF, 0xC47A7EFF, 0xB7F30BEF, 0x0BF7EF88,
    0xF3056311, 0x5A9F4AFC, 0x7BFBE72D, 0x27CDFB9C, 0xCEDF7F6B, 0x041EA477, 0x8CB5F1F1,
    0x883136A1, 0x3C626D64, 0xCCB985F4, 0xC6BEF0FF, 0x7DCAA102, 0xDE160DD7, 0x8CEE3F7F,
    0x1875F9E5, 0x00DE0C4F, 0x7EFABF58, 0xFDF57EB1, 0xFD2B0382, 0xA9F4731E, 0x5F7EF088,
    0x99CBA99A, 0x22EF1318, 0x1760F304, 0x32671FCF, 0xF07CC406, 0x5F9B7FCF, 0x9D7229ED,
    0x3C63E3A4, 0xDF1A9633, 0xDFBF7CD7, 0xF5F8A540, 0x021FBE23, 0xFBEFC400, 0xFC4AB95E,
    0xADE27DC6, 0x74DDC7F3, 0x7AC6D696, 0x2ACF3FFE, 0xE33C7DD4, 0x5BF78C3F, 0xD44D7F46,
    0x3B7BEFC8, 0xE25FBF7F, 0x8A83B781, 0x7FE8DB89, 0x7CF6F748, 0xFCEFBD73, 0xD279E7A5,
    0xD279EB0B, 0xFF697DFA, 0xEF89634E, 0xBF7C5FEB, 0x5A4F905F, 0x27BFFE4D, 0x8F7F7CD7,
    0x79EBFBDF, 0x5FBE3188, 0xCABF7EFB, 0xA30A79E7, 0xC5E279F3, 0xFC7F587E, 0xAE43EB26,
    0xDE35BC47, 0xC7233C61, 0x9C62FCFF, 0xAE8F6BA7, 0x5FBFBDFA, 0xB94DFEEC, 0x9FF5BE4A,
    0x37EF19CF, 0x7DD4566E, 0xBF2B3C22, 0xFFCCFDF8, 0x8AC9EBD3, 0xFFE99D6F, 0x2B49E5E8,
    0xD7FE4FED, 0x5F18107E, 0xA32FDE7A, 0x8B7EC43B, 0x6F819DF8, 0x7BF7EFD4, 0xCEBEFBEB,
    0x3C4AE739, 0xE17F6B2F, 0xD67BD319, 0xE2BE5FF7, 0xDF9E3DF9, 0xEDF0F629, 0xC9A17E29,
    0xDE30793F, 0x7DF78A77, 0x99F7CE6F, 0xFFD7FD77, 0x221FEC9F, 0xDFBE2B18, 0xB9E88E5F,
    0xA06FBF74, 0xB0FEF112, 0xAAFF857E, 0x5BFECB12, 0x7FF977AB, 0x9E235BEF, 0x6FF1E4A7,
    0x79E97CF9, 0x7BF66BCF, 0xBF50A88D, 0xE1AD4BDF, 0x7279F237, 0x0C37333D, 0xEF631FD4,
    0xEFED67DF, 0x9E49E7CB, 0xE7EC9DED, 0x603303F7, 0xFDE158C1, 0x79E79FBD, 0x8CF3C346,
    0xBA35BEF1, 0xFBF1844B, 0x4679E7AD, 0xF18CF3C3, 0x4BBA35BE, 0x6559E004, 0xADFCE667,
    0xF7CADE67, 0xFF6BB2B5, 0x5F7E2785, 0x676FDFE8, 0x05E2CF52, 0xF86FDFDE, 0x11186FBE,
    0x0679E780, 0x1AACF26F, 0x3DF88000, 0x279E7977, 0x24F3D270, 0xEFC43000, 0xF7EFC467,
    0xCFC94189, 0xF5176B07, 0x1891589F, 0x3F7C81EF, 0x00001785, 0x0737BF7E, 0x3F9AE78F,
    0xE71FB19E, 0xF190BFEB, 0x194BE1A4, 0x5F5A8B20, 0xADC3EABA, 0xFCF13BC0, 0x3E629BE0,
    0x9FFF3FE4, 0x919EADEF, 0xFE209993, 0xFDAE6625, 0x6FDF9BFD, 0x219E7897, 0xCF95EF8F,
    0xBEA550BB, 0x016FA9F1, 0x3FC43E62, 0xADF79FFF, 0x9993919E, 0x6625FE20, 0x9BFDFDAE,
    0xFF42E8DF, 0x0679E1BF, 0xEB277AF1, 0xF7D99739, 0x8C0CFE63, 0xC8FDE131, 0x664F3339,
    0x9E3559AC, 0xBF787BF1, 0xCCFD12FD, 0xFCF5FBDF, 0xF3C6AFF5, 0x64DE0F3C, 0x001EAB3C,
    0xD4990000, 0x000178B3, 0xEFDAC491, 0xBFD7E3AF, 0x0779907A, 0x9589FBAF, 0x6B1FA94F,
    0x45FB87DC, 0x214DACF2, 0xA64F06E3, 0xE29E5274, 0x88CFF9CC, 0x8E6326F3, 0x879234FF,
    0xAB51AEA3, 0x05F7F47F, 0x2FE8FF35, 0xFF45FEA7, 0x5CC8C1E2, 0xAC5F5CDC, 0x793DEE8F,
    0x026B039E, 0x853CF3E4, 0x9E79F27D, 0x3185FD1F, 0xE663F726, 0x7845FFFE, 0x6F7E1DFE,
    0xF8000000, 0x8905E17E, 0x7018C3EF, 0xEC3F9E26, 0x51113CC2, 0x00179FBD, 0x1187EB00,
    0x7EFCDBE4, 0xFAE8DE46, 0xDFBF7EFD, 0xC3D64D63, 0xDF87B7EF, 0xB7DEBCEF, 0x3D7DE2A3,
    0xF762BEF5, 0x010D1BF7, 0xFAC7EDF9, 0x1021EBF6, 0xEBF79E33, 0xA86FEFDC, 0xEFE96FDF,
    0xE413C6B7, 0xDEFDF883, 0x85DEFD65, 0xDFAD2178, 0xA7DF9C67, 0xE7953236, 0xEFF66DF7,
    0xDFBF59FD, 0xF5F7E718, 0xEA27DFAC, 0xF8D5FBF7, 0x7AFBE9DE, 0xF05F7F32, 0xC3917DFB,
    0x2A8D6618, 0x005AC6B5, 0x2FEDFBC0, 0x233AF8C6, 0x9F2D9D67, 0xE9D44B78, 0xDFBF7EA5,
    0xDFBFF9E7, 0xE4043467, 0xCEFACBB7, 0x000118F1, 0xBC3F42BF, 0x00EEF0FD, 0xB7BEFC40,
    0x19BC4FF1, 0xEF11DBEF, 0xB00000BB, 0x9FBF7EA2, 0x66024178, 0xFD66EE63, 0x07EF587E,
    0x7F78FFF5, 0x0003BBC5, 0x7BEFC400, 0x7EBDDFBB, 0x98433F62, 0xBC60001E, 0x77CF2EDF,
    0x0008C78E, 0x8F57EFF4, 0x17F9D7DF, 0xFDCC4911, 0x7FAFDAFE, 0x3F6FDE35, 0x1EBF6F9E,
    0xFBD53102, 0x037F7AB5, 0x37DFBF58, 0xDA8BEFCE, 0xDF9E54C8, 0x46BFD9B7, 0xEBAFF5F0,
    0xFD233DFB, 0x57EFF401, 0xF4AFDF9E, 0xF7B3D37E, 0xF9EF7E2F, 0x257FAFC7, 0xF7E8AA06,
    0xDFBF75FB, 0xA8B881AF, 0xF6FD9B7A, 0x120AF168, 0x6F9E31E0, 0x9BFD7FB3, 0xA9F59F93,
    0x1F9E5621, 0xF3C18BE7, 0x86B179FC, 0x33CFF15C, 0x9C62337F, 0x2B59876F, 0xE4F8CFC9,
    0xF58FF57F, 0xBF3D60ED, 0x33FBBB50, 0x53EB3F27, 0x7FF8E629, 0x5419EF9C, 0xE8B110FD,
    0x7EFC45FF, 0x33EFC57B, 0xFEB0DDF9, 0x35FEF643, 0xDF06FE60, 0x9318106F, 0x16F106F8,
    0xBFBC0404, 0x8000037A, 0xDFE9BBC0, 0x2B0EE403, 0x201E73CB, 0xFBE4BBBC, 0x7EFFBE18,
    0xFBF7AEAF, 0xBF5BD5FB, 0x09006460, 0x711AF64D, 0x2FD64FFE, 0x47C9C44E, 0xBF2BEFE5,
    0x1A0445D9, 0x47B5A56A, 0x31CD6FD9, 0xFE6315DF, 0x79E19066, 0xD40BDFBE, 0x3D4FC63B,
    0xEAC47BBF, 0x1C698BFE, 0xF21DBF11, 0x24617EFE, 0x235C6BC5, 0xDEE97E9F, 0x197FDB29,
    0xF003FE3B, 0xE846F006, 0xA5F7D400, 0xCA725FDB, 0xACACFB18, 0xFA717EFC, 0x232FCAF7,
    0xE89F37DE, 0x3D9BC5FE, 0x390EF97E, 0x9F15D18B, 0x3FE37FB7, 0xA639FF3C, 0x3278C918,
    0xDFBBF54E, 0xF7F5F11B, 0x1BA839C8, 0xF65887DF, 0x39CD633E, 0x67794564, 0xE47234AF,
    0x3F53FE78, 0xF7EFD573, 0xF7EFD5FB, 0xE1117C41, 0x56B4BEFD, 0xFCFFC567, 0xF3C313C6,
    0x1BF93CDD, 0xE77DEAB9, 0x77EF8BEF, 0xF9F79CD7, 0x0DE0DF9E, 0xCF546462, 0x7E7DEBB7,
    0x9DFA9B2F, 0xD7BF9DEF, 0xCFEF15FC, 0xBF9AFF57, 0x4787ECD7, 0x6F54573C, 0xE5F8E5F1,
    0x0209A368, 0xFDF58980, 0xDEBEB49F, 0xFBFB5809, 0x39DE3D3D, 0xFEC40D60, 0xDE10240F,
    0xFB7AF7F7, 0xF7C358F7, 0xFC73B9BC, 0xB9E11CCA, 0xB349DFAC, 0x511FF97C, 0x7EDFEE77,
    0xE6B9B9C6, 0xE4E4CA1C, 0x7DF7CE1D, 0x8BEDDBEE, 0x379FE637, 0x222754D6, 0xBEFBC59D,
    0xCE5E78A8, 0xCEBF5377, 0x8DE7F98C, 0x4889D535, 0x2FBEF167, 0xF4E3EA2A, 0xC9FAFD0A,
    0xD637A5FA, 0xA7313A8A, 0xF7DF3CB3, 0x3979E2A2, 0x3AFD4DDF, 0xFAD7CC33, 0xE8E9E7C9,
    0xFA748CDF, 0x41F3C027, 0x3FBC449D, 0xBFE15FAC, 0xFFB2C4AA, 0xFE5DEAD6, 0x40D6FBDF,
    0x21F83540, 0xAFD61FDE, 0x62555FF0, 0xF56B7FD9, 0x7DEFFF2E, 0xBF50106B, 0xF11A750F,
    0x857EB0FE, 0xCB12AAFF, 0x77AB5BFE, 0x5BEF7FF9, 0x6FEE8083, 0xC41EFFD0, 0x15FAC3FB,
    0x2C4AABFE, 0xDEAD6FFB, 0x6FBDFFE5, 0x3D17C00D, 0x106F9EF8, 0x57EB0FEF, 0xB12AAFF8,
    0x7AB5BFEC, 0xBEF7FF97, 0x23039835, 0x47F38C3E, 0x57EB1FD4, 0xB12AAFF8, 0x7AB5BFEC,
    0xBEF7FF97, 0x279E3035, 0xBF3C0F70, 0x3CF3827C, 0xE788C86F, 0xC6179F0D, 0x525FABF7,
    0x7C8DF86B, 0xCCCF5C9E, 0xC7F5030D, 0x59F7FBD8, 0x21EC7F4F, 0x7DC47CF0, 0x8CF3C346,
    0xBA35BEF1, 0xFBF1844B, 0x4F6A822D, 0x3CF0D1EC, 0x8D6FBC63, 0xFC6112EE, 0xBF504B7E,
    0x1A3BDC4F, 0xF78C679E, 0x225DD1AD, 0xC16FDF8C, 0xFD6E3D17, 0x18CF3C35, 0xBBA35BEF,
    0xDFBF1844, 0x887CF012, 0xE4DE0CFB, 0x00003559, 0x42EE7BF1, 0xF6279AA0, 0x559E4DE0,
    0xBF100003, 0xF5022EE7, 0x077B88FB, 0x1AACF26F, 0x3DF88000, 0xF45F0177, 0x378FEB70,
    0x000D5679, 0xBB9EFC40, 0x759279F2, 0xF3FF8BBD, 0x63DF9CFB, 0x32CABFC6, 0xBE158C6E,
    0xD022FBDF, 0xEFDC8DFD, 0xAE97D6B7, 0xF02B70FA, 0xF83F3C4E, 0x07CF00A6, 0x7FC87ECF,
    0x5BDF3FFE, 0x3327233D, 0xCC4BFC41, 0x37FBFB5C, 0x082EDFBF, 0x26E446A8, 0x7CFFF9FF,
    0x9C8CF56F, 0x2FF104CC, 0xEFED7331, 0xBB7EFCDF, 0x0FBF5010, 0x3FE4BECF, 0xADEF9FFF,
    0x9993919E, 0x6625FE20, 0x9BFDFDAE, 0x02176FDF, 0x7BC1BFBA, 0xFCFF90EF, 0x7AB7BE7F,
    0x82664E46, 0xB99897F8, 0x7E6FF7F6, 0x5F005DBF, 0xFEB7E0F4, 0xFFF3FE43, 0x19EADEF9,
    0xE2099939, 0xDAE6625F, 0xFDF9BFDF, 0x3C478976, 0xFCB7D771, 0xFDBE9DDE, 0x16FCBE9F,
    0x87B31246, 0xF9FCE7FC, 0xC8CDF5DE, 0xFF933559, 0xC46FFF10, 0xBFE4F5CC, 0x022EDF99,
    0x9F9C8F9E, 0x002F167A, 0xFB589220, 0xFAFC75FD, 0xCB540857, 0xC59EB7AC, 0x2488000B,
    0x1D7F7ED6, 0x8115FEBF, 0x7E727DFA, 0x178B3D5F, 0xAC491000, 0x7E3AFEFD, 0x8BE02BFD,
    0xEBD1D91E, 0x8000BC59, 0xF7ED6248, 0x5FEBF1D7, 0x479AA021, 0x717323BD, 0x3EB17D73,
    0x79E4F7BA, 0x1009AC0E, 0x31677903, 0xA31AFD9F, 0xBF51EA17, 0x875FA9FD, 0xE4637EFE,
    0x6718CA77, 0x7BC13BF2, 0xCCD7E21E, 0xFCEF19EF, 0x0F589ADA, 0xDF87BD7E, 0xB7DEBCEF,
    0x3D7DE2A3, 0xF762BEF5, 0x64BE23F7, 0xFDEFD2FC, 0x79DFBF0F, 0xC5476FBD, 0x7DEA7AFB,
    0x27EFEEC5, 0xC7DF8D7F, 0xEFC33BFB, 0xDBEF5E77, 0x9EBEF151, 0xFBB15F7A, 0x59BF79FB,
    0xBF29EFDE, 0xBF7E1DDF, 0x8EDF7AF3, 0xD4F5F78A, 0xDFDD8AFB, 0xFC3D9BCF, 0xDFDE1DF2,
    0xCEFDF87F, 0x2A3B7DEB, 0xEF53D7DE, 0x3F7F762B, 0x65E3182A, 0xEFDBF3F8, 0xD79DFBF0,
    0xBC5476FB, 0x57DEA7AF, 0xF37EFEEC, 0xCCFDFBF7, 0xCF1EF65F, 0x78FFBCF7, 0xF97EF9BF,
    0xBC6FD97C, 0xA1BDFEBF, 0xBFA5BF7E, 0x904F1ADF, 0x7BF7E20F, 0xC5BF9597, 0x7AC4D64E,
    0xC637FAB0, 0xEB3D7DF9, 0xFDFA89F7, 0x77BE357E, 0xC49EBEFA, 0x5A5F8C97, 0xF9C637EF,
    0xF7EB3D7D, 0x7EFDFA89, 0xFA77BE35, 0xD7F29EBE, 0xBF3C7DF8, 0xFBF38C77, 0x13EFD67A,
    0x6AFDFBF5, 0x7DF4EF7C, 0xC3D9BD3D, 0xF9E1DF2F, 0xDF9C637D, 0x9F7EB3D7, 0x57EFDFA8,
    0xEFA77BE3, 0xAC4D69EB, 0xEF176F07, 0xEFC4000E, 0x92F89B7B, 0xFBEF4BF1, 0x4000EEF0,
    0xE5B7BEFC, 0xF8FBF1AF, 0x0EEF26FD, 0x7BEFC400, 0xFC3D9BDB, 0xBF7E1DF2, 0x00077787,
    0x2DBDF7E2, 0xB97CAB7F, 0xEA39CDCB, 0xB63BCEFC, 0x9CC522B1, 0xAFDAFDFB, 0xCDFBC37F,
    0x8D4F7EF2, 0xF9E5BBF7, 0x0118F1CE, 0x1EB13580, 0xF1EAFF74, 0x22FF3AFB, 0xDFB98922,
    0xAFF5FB5F, 0xBF192F88, 0x8F57EFD4, 0x17F9D7DF, 0xFDCC4911, 0x7FAFDAFE, 0xDF8D7F25,
    0xEB7BF7C7, 0xFF3AFBF1, 0xB9892222, 0xF5FB5FDF, 0x2CDFBCAF, 0xFE94F7EF, 0x5F7E3D75,
    0x24445FE7, 0x6BFBF731, 0x3795FEBF, 0x3BE5F87B, 0x1EAFBF7C, 0x2FF3AFBF, 0xFB989222,
    0xFF5FB5FD, 0x82FF008A, 0xEFDFAC5D, 0xBBF58BF7, 0x09382FDF, 0x3E6FF43A, 0x39D9EDCF,
    0xC8C56FBE, 0x5FAF735C, 0x6B2BFBCB, 0x1E8C3D62, 0xE0120AF1, 0xB36F9E31, 0xBE23FD7F,
    0x7472FC64, 0xF009057A, 0xD9B7CF18, 0x5FC9FEBF, 0x9F19F7E3, 0xE0120AF1, 0xB36F9E31,
    0x66F3FD7F, 0xC77CBF0F, 0x090578F8, 0xB7CF18F0, 0x11FEBFD9, 0xD2FC625F, 0xEB3F199C,
    0xF8E62953, 0x19EF9C7F, 0xB110FD54, 0x68C5FFE8, 0x3F6FC808, 0x0F5FB7D6, 0xFDEA9881,
    0x01BFBD5A, 0x5F83D9BC, 0xF12CC3BE, 0x62953EB3, 0xF9C7FF8E, 0x0FD5419E, 0x5FFE8B11,
    0x00000000

  EW_FONT_KERNING_CODES( BrickGameDescrFont )
  EW_FONT_KERNING_VALUES( BrickGameDescrFont )
EW_END_OF_FONT_RES( BrickGameDescrFont )

/* Embedded Wizard */
