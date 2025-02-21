/*
 * Copyright 2019 NXP.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _VECTORS_MDK_H_
#define _VECTORS_MDK_H_

#include "safety_config.h"  /* for device definition */

/*******************************************************************************
* API
******************************************************************************/
void DefaultISR(void); /* function prototype for DefaultISR in vectors.c */
extern void start(void);
void NMI_isr(void); /* included in vector.c */
void hard_fault_handler_c(uint32_t * hardfault_args);
typedef void pointer(void); /* Interrupt Vector Table Function Pointers */
extern void __startup(void);
extern uint32_t __BOOT_STACK_ADDRESS[];
extern void start(void);

/*******************************************************************************
* Definitions
******************************************************************************/
//				Address     Vector IRQ   Source module   Source description
#define VECTOR_000       (vector_entry)&Image$$ARM_LIB_STACK$$ZI$$Limit          /* Initial SP           */
#define VECTOR_001       (vector_entry)&start                                    /* Initial PC           */
#ifndef VECTOR_002
  #define VECTOR_002      NMI_isr         // 0x0000_0008 2 -          ARM core        Non-maskable Interrupt (NMI)
#endif
#ifndef VECTOR_003
  #define VECTOR_003      DefaultISR     // 0x0000_000C 3 -          ARM core        Hard Fault
#endif
#ifndef VECTOR_004
  #define VECTOR_004      DefaultISR     // 0x0000_0010 4 -          ARM core        Memory Manage
#endif
#ifndef VECTOR_005
  #define VECTOR_005      DefaultISR     // 0x0000_0014 5 -          ARM core        Bus Fault
#endif
#ifndef VECTOR_006
  #define VECTOR_006      DefaultISR     // 0x0000_0018 6 -          ARM core        Usage Fault
#endif
#ifndef VECTOR_007
  #define VECTOR_007      DefaultISR     // 0x0000_001C 7 -          ARM core        Reserved
#endif
/*****************************************************************************************************/
/********************* SEE USER MANUAL FOR LPC55S6x, chapter BOOT ROM (table 170) ********************/
/*****************************************************************************************************/
#ifndef VECTOR_008
  #define VECTOR_008      0               // 0x0000_0020 8 -          ARM core        Image length
#endif
#ifndef VECTOR_009
  #define VECTOR_009      0               // 0x0000_0024 9 -          ARM core        Image type
#endif
#ifndef VECTOR_010
  #define VECTOR_010      0               // 0x0000_0028 10 -         ARM core        Offset to certificate block in bytes
#endif
/*****************************************************************************************************/
/*****************************************************************************************************/
#ifndef VECTOR_011
  #define VECTOR_011      DefaultISR     // 0x0000_002C 11 -         ARM core        Offset to certificate block in bytes
#endif
#ifndef VECTOR_0012
  #define VECTOR_012      DefaultISR     // 0x0000_0030 12 -         ARM core        Supervisor call (SVCall)
#endif
#ifndef VECTOR_013
  #define VECTOR_013      DefaultISR     // 0x0000_0034 13 -         ARM core        Debug Monitor
#endif
#ifndef VECTOR_014
  #define VECTOR_014      DefaultISR     // 0x0000_0038 14 -         ARM core        Reserved
#endif
#ifndef VECTOR_015
  #define VECTOR_015      DefaultISR     // 0x0000_003C 15 -         ARM core        System tick timer (SysTick)
#endif
#ifndef VECTOR_016  
  #define VECTOR_016      DefaultISR     // 0x0000_0040
#endif
#ifndef VECTOR_017
  #define VECTOR_017      DefaultISR     // 0x0000_0044
#endif
#ifndef VECTOR_018
  #define VECTOR_018      DefaultISR     // 0x0000_0048
#endif
#ifndef VECTOR_019
  #define VECTOR_019      DefaultISR     // 0x0000_004C 
#endif
#ifndef VECTOR_020
  #define VECTOR_020      DefaultISR     // 0x0000_0050 
#endif
#ifndef VECTOR_021
  #define VECTOR_021      DefaultISR     // 0x0000_0054 
#endif
#ifndef VECTOR_022
  #define VECTOR_022      DefaultISR     // 0x0000_0058 
#endif
#ifndef VECTOR_023
  #define VECTOR_023      DefaultISR     // 0x0000_005C 
#endif
#ifndef VECTOR_024
  #define VECTOR_024      DefaultISR     // 0x0000_0060 
#endif
#ifndef VECTOR_025
  #define VECTOR_025      DefaultISR     // 0x0000_0064 
#endif
#ifndef VECTOR_026
  #define VECTOR_026      DefaultISR     // 0x0000_0068 
#endif
#ifndef VECTOR_027
  #define VECTOR_027      DefaultISR     // 0x0000_006C 
#endif
#ifndef VECTOR_028
  #define VECTOR_028      DefaultISR     // 0x0000_0070
#endif
#ifndef VECTOR_029
  #define VECTOR_029      DefaultISR     // 0x0000_0074 
#endif
#ifndef VECTOR_030
  #define VECTOR_030      DefaultISR     // 0x0000_0078 
#endif
#ifndef VECTOR_031
  #define VECTOR_031      DefaultISR     // 0x0000_007C 
#endif
#ifndef VECTOR_032
  #define VECTOR_032      DefaultISR     // 0x0000_0080 
#endif
#ifndef VECTOR_033
  #define VECTOR_033      DefaultISR     // 0x0000_0084 
#endif
#ifndef VECTOR_034
  #define VECTOR_034      DefaultISR     // 0x0000_0088 
#endif
#ifndef VECTOR_035
  #define VECTOR_035      DefaultISR     // 0x0000_008C 
#endif
#ifndef VECTOR_036
  #define VECTOR_036      DefaultISR     // 0x0000_0090 
#endif
#ifndef VECTOR_037
  #define VECTOR_037      DefaultISR     // 0x0000_0094 
#endif
#ifndef VECTOR_038
  #define VECTOR_038      DefaultISR     // 0x0000_0098 
#endif
#ifndef VECTOR_039
  #define VECTOR_039      DefaultISR     // 0x0000_009C 
#endif
#ifndef VECTOR_040
  #define VECTOR_040      DefaultISR     // 0x0000_00A0 
#endif
#ifndef VECTOR_041
  #define VECTOR_041      DefaultISR     // 0x0000_00A4  
#endif
#ifndef VECTOR_042
  #define VECTOR_042      DefaultISR     // 0x0000_00A8 
#endif
#ifndef VECTOR_043
  #define VECTOR_043      DefaultISR     // 0x0000_00AC 
#endif
#ifndef VECTOR_044
  #define VECTOR_044      DefaultISR     // 0x0000_00B0 
#endif
#ifndef VECTOR_045
  #define VECTOR_045      DefaultISR     // 0x0000_00B4 
#endif
#ifndef VECTOR_046
  #define VECTOR_046      DefaultISR     // 0x0000_00B8 
#endif
#ifndef VECTOR_047
  #define VECTOR_047      DefaultISR     // 0x0000_00BC 
#endif
#ifndef VECTOR_048    
  #define VECTOR_048      DefaultISR     // 0x0000_00C0
#endif
#ifndef VECTOR_049
  #define VECTOR_049      DefaultISR     // 0x0000_00C4
#endif
#ifndef VECTOR_050
  #define VECTOR_050      DefaultISR     // 0x0000_00C8
#endif
#ifndef VECTOR_051
  #define VECTOR_051      DefaultISR     // 0x0000_00CC
#endif
#ifndef VECTOR_052
  #define VECTOR_052      DefaultISR     // 0x0000_00D0
#endif
#ifndef VECTOR_053
  #define VECTOR_053      DefaultISR     // 0x0000_00D4
#endif
#ifndef VECTOR_054
  #define VECTOR_054      DefaultISR     // 0x0000_00D8
#endif
#ifndef VECTOR_055
  #define VECTOR_055      DefaultISR     // 0x0000_00DC
#endif
#ifndef VECTOR_056
  #define VECTOR_056      DefaultISR     // 0x0000_00E0
#endif
#ifndef VECTOR_057
  #define VECTOR_057      DefaultISR     // 0x0000_00E4
#endif
#ifndef VECTOR_058
  #define VECTOR_058      DefaultISR     // 0x0000_00E8
#endif
#ifndef VECTOR_059
  #define VECTOR_059      DefaultISR     // 0x0000_00EC
#endif
#ifndef VECTOR_060
  #define VECTOR_060      DefaultISR     // 0x0000_00F0
#endif
#ifndef VECTOR_061
  #define VECTOR_061      DefaultISR     // 0x0000_00F4
#endif
#ifndef VECTOR_062
  #define VECTOR_062      DefaultISR     // 0x0000_00F8
#endif
#ifndef VECTOR_063
  #define VECTOR_063      DefaultISR     // 0x0000_00FC
#endif
#ifndef VECTOR_064
  #define VECTOR_064      DefaultISR     // 0x0000_0100
#endif
#ifndef VECTOR_065
  #define VECTOR_065      DefaultISR     // 0x0000_0104
#endif
#ifndef VECTOR_066
  #define VECTOR_066      DefaultISR     // 0x0000_0108
#endif
#ifndef VECTOR_067
  #define VECTOR_067      DefaultISR     // 0x0000_010C
#endif
#ifndef VECTOR_068
  #define VECTOR_068      DefaultISR     // 0x0000_0110
#endif
#ifndef VECTOR_069
  #define VECTOR_069      DefaultISR     // 0x0000_0114
#endif
#ifndef VECTOR_070
  #define VECTOR_070      DefaultISR     // 0x0000_0118
#endif
#ifndef VECTOR_071
  #define VECTOR_071      DefaultISR     // 0x0000_011C
#endif
#ifndef VECTOR_072
  #define VECTOR_072      DefaultISR     // 0x0000_0120
#endif
#ifndef VECTOR_073
  #define VECTOR_073      DefaultISR     // 0x0000_0124
#endif
#ifndef VECTOR_074
  #define VECTOR_074      DefaultISR     // 0x0000_0128
#endif
#ifndef VECTOR_075
  #define VECTOR_075      DefaultISR     // 0x0000_012C
#endif

#endif /* _VECTORS_MDK_H_ */
