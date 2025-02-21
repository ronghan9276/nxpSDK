; * -------------------------------------------------------------------------
; *  @file:    startup_MK27F15.s
; *  @purpose: CMSIS Cortex-M4 Core Device Startup File
; *            MK27F15
; *  @version: 1.3
; *  @date:    2018-1-9
; *  @build:   b180801
; * -------------------------------------------------------------------------
; *
; * Copyright 1997-2016 Freescale Semiconductor, Inc.
; * Copyright 2016-2018 NXP
; *
; * SPDX-License-Identifier: BSD-3-Clause
; *
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; *****************************************************************************/


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size
                IMPORT  |Image$$ARM_LIB_STACK$$ZI$$Limit|

__Vectors       DCD     |Image$$ARM_LIB_STACK$$ZI$$Limit| ; Top of Stack
                DCD     Reset_Handler  ; Reset Handler
                DCD     NMI_Handler                         ;NMI Handler
                DCD     HardFault_Handler                   ;Hard Fault Handler
                DCD     MemManage_Handler                   ;MPU Fault Handler
                DCD     BusFault_Handler                    ;Bus Fault Handler
                DCD     UsageFault_Handler                  ;Usage Fault Handler
                DCD     0                                   ;Reserved
                DCD     0                                   ;Reserved
                DCD     0                                   ;Reserved
                DCD     0                                   ;Reserved
                DCD     SVC_Handler                         ;SVCall Handler
                DCD     DebugMon_Handler                    ;Debug Monitor Handler
                DCD     0                                   ;Reserved
                DCD     PendSV_Handler                      ;PendSV Handler
                DCD     SysTick_Handler                     ;SysTick Handler

                                                            ;External Interrupts
                DCD     DMA0_DMA16_IRQHandler               ;DMA channel 0,16 transfer complete
                DCD     DMA1_DMA17_IRQHandler               ;DMA channel 1,17 transfer complete
                DCD     DMA2_DMA18_IRQHandler               ;DMA channel 2,18 transfer complete
                DCD     DMA3_DMA19_IRQHandler               ;DMA channel 3,19 transfer complete
                DCD     DMA4_DMA20_IRQHandler               ;DMA channel 4,20 transfer complete
                DCD     DMA5_DMA21_IRQHandler               ;DMA channel 5,21 transfer complete
                DCD     DMA6_DMA22_IRQHandler               ;DMA channel 6,22 transfer complete
                DCD     DMA7_DMA23_IRQHandler               ;DMA channel 7,23 transfer complete
                DCD     DMA8_DMA24_IRQHandler               ;DMA channel 8,24 transfer complete
                DCD     DMA9_DMA25_IRQHandler               ;DMA channel 9,25 transfer complete
                DCD     DMA10_DMA26_IRQHandler              ;DMA channel 10,26 transfer complete
                DCD     DMA11_DMA27_IRQHandler              ;DMA channel 11,27 transfer complete
                DCD     DMA12_DMA28_IRQHandler              ;DMA channel 12,28 transfer complete
                DCD     DMA13_DMA29_IRQHandler              ;DMA channel 13,29 transfer complete
                DCD     DMA14_DMA30_IRQHandler              ;DMA channel 14,30 transfer complete
                DCD     DMA15_DMA31_IRQHandler              ;DMA channel 15,31 transfer complete
                DCD     DMA_Error_IRQHandler                ;DMA channel 0 - 31 error
                DCD     MCM_IRQHandler                      ;MCM normal interrupt
                DCD     FTFE_IRQHandler                     ;FTFE command complete
                DCD     Read_Collision_IRQHandler           ;FTFE read collision
                DCD     LVD_LVW_IRQHandler                  ;PMC controller low-voltage detect, low-voltage warning
                DCD     LLWU_IRQHandler                     ;Low leakage wakeup unit
                DCD     WDOG_EWM_IRQHandler                 ;Single interrupt vector for  WDOG and EWM
                DCD     TRNG0_IRQHandler                    ;True randon number generator
                DCD     I2C0_IRQHandler                     ;Inter-integrated circuit 0
                DCD     I2C1_IRQHandler                     ;Inter-integrated circuit 1
                DCD     SPI0_IRQHandler                     ;Serial peripheral Interface 0
                DCD     SPI1_IRQHandler                     ;Serial peripheral Interface 1
                DCD     I2S0_Tx_IRQHandler                  ;Integrated interchip sound 0 transmit interrupt
                DCD     I2S0_Rx_IRQHandler                  ;Integrated interchip sound 0 receive interrupt
                DCD     LPUART0_IRQHandler                  ;LPUART0 receive/transmit/error interrupt
                DCD     LPUART1_IRQHandler                  ;LPUART1 receive/transmit/error interrupt
                DCD     LPUART2_IRQHandler                  ;LPUART2 receive/transmit/error interrupt
                DCD     LPUART3_IRQHandler                  ;LPUART3 receive/transmit/error interrupt
                DCD     LPUART4_IRQHandler                  ;LPUART4 receive/transmit/error interrupt
                DCD     Reserved51_IRQHandler               ;Reserved interrupt
                DCD     Reserved52_IRQHandler               ;Reserved interrupt
                DCD     Reserved53_IRQHandler               ;Reserved interrupt
                DCD     Reserved54_IRQHandler               ;Reserved interrupt
                DCD     ADC0_IRQHandler                     ;Analog-to-digital converter 0
                DCD     CMP0_IRQHandler                     ;Comparator 0
                DCD     CMP1_IRQHandler                     ;Comparator 1
                DCD     FTM0_IRQHandler                     ;FlexTimer module 0 fault, overflow and channels interrupt
                DCD     FTM1_IRQHandler                     ;FlexTimer module 1 fault, overflow and channels interrupt
                DCD     FTM2_IRQHandler                     ;FlexTimer module 2 fault, overflow and channels interrupt
                DCD     CMT_IRQHandler                      ;Carrier modulator transmitter
                DCD     RTC_IRQHandler                      ;Real time clock
                DCD     RTC_Seconds_IRQHandler              ;Real time clock seconds
                DCD     PIT0CH0_IRQHandler                  ;Periodic interrupt timer 0 channel 0
                DCD     PIT0CH1_IRQHandler                  ;Periodic interrupt timer 0 channel 1
                DCD     PIT0CH2_IRQHandler                  ;Periodic interrupt timer 0 channel 2
                DCD     PIT0CH3_IRQHandler                  ;Periodic interrupt timer 0 channel 3
                DCD     PDB0_IRQHandler                     ;Programmable delay block
                DCD     USB0_IRQHandler                     ;USB OTG interrupt
                DCD     USBDCD_IRQHandler                   ;USB charger detect
                DCD     Reserved71_IRQHandler               ;Reserved interrupt
                DCD     DAC0_IRQHandler                     ;Digital-to-analog converter 0
                DCD     MCG_IRQHandler                      ;Multipurpose clock generator
                DCD     LPTMR0_LPTMR1_IRQHandler            ;Single interrupt vector for  Low Power Timer 0 and 1
                DCD     PORTA_IRQHandler                    ;Port A pin detect interrupt
                DCD     PORTB_IRQHandler                    ;Port B pin detect interrupt
                DCD     PORTC_IRQHandler                    ;Port C pin detect interrupt
                DCD     PORTD_IRQHandler                    ;Port D pin detect interrupt
                DCD     PORTE_IRQHandler                    ;Port E pin detect interrupt
                DCD     SWI_IRQHandler                      ;Software interrupt
                DCD     SPI2_IRQHandler                     ;Serial peripheral Interface 2
                DCD     SPI3_IRQHandler                     ;Serial peripheral Interface 3
                DCD     Reserved83_IRQHandler               ;Reserved interrupt
                DCD     I2S1_Tx_IRQHandler                  ;Integrated interchip sound 1 transmit interrupt
                DCD     I2S1_Rx_IRQHandler                  ;Integrated interchip sound 1 receive interrupt
                DCD     FLEXIO0_IRQHandler                  ;FLEXIO0
                DCD     FTM3_IRQHandler                     ;FlexTimer module 3 fault, overflow and channels interrupt
                DCD     Reserved88_IRQHandler               ;Reserved interrupt
                DCD     Reserved89_IRQHandler               ;Reserved interrupt
                DCD     I2C2_IRQHandler                     ;Inter-integrated circuit 2
                DCD     Reserved91_IRQHandler               ;Reserved interrupt
                DCD     Reserved92_IRQHandler               ;Reserved interrupt
                DCD     Reserved93_IRQHandler               ;Reserved interrupt
                DCD     Reserved94_IRQHandler               ;Reserved interrupt
                DCD     Reserved95_IRQHandler               ;Reserved interrupt
                DCD     Reserved96_IRQHandler               ;Reserved interrupt
                DCD     SDHC_IRQHandler                     ;Secured digital host controller
                DCD     Reserved98_IRQHandler               ;Reserved interrupt
                DCD     Reserved99_IRQHandler               ;Reserved interrupt
                DCD     Reserved100_IRQHandler              ;Reserved interrupt
                DCD     Reserved101_IRQHandler              ;Reserved interrupt
                DCD     Reserved102_IRQHandler              ;Reserved interrupt
                DCD     Reserved103_IRQHandler              ;Reserved interrupt
                DCD     TPM1_IRQHandler                     ;TPM1 single interrupt vector for all sources
                DCD     TPM2_IRQHandler                     ;TPM2 single interrupt vector for all sources
                DCD     USBHSDCD_IRQHandler                 ;HS USB charger detect
                DCD     I2C3_IRQHandler                     ;Inter-integrated circuit 3
                DCD     Reserved108_IRQHandler              ;Reserved interrupt
                DCD     USBHS_IRQHandler                    ;USB HS interrupt
                DCD     Reserved110_IRQHandler              ;Reserved interrupt
                DCD     Reserved111_IRQHandler              ;Reserved interrupt
                DCD     Reserved112_IRQHandler              ;Reserved interrupt
                DCD     Reserved113_IRQHandler              ;Reserved interrupt
                DCD     Reserved114_IRQHandler              ;Reserved interrupt
                DCD     Reserved115_IRQHandler              ;Reserved interrupt
                DCD     QuadSPI0_IRQHandler                 ;qspi
                DCD     Reserved117_IRQHandler              ;Reserved interrupt
                DCD     Reserved118_IRQHandler              ;Reserved interrupt
                DCD     Reserved119_IRQHandler              ;Reserved interrupt
                DCD     Reserved120_IRQHandler              ;Reserved interrupt
                DCD     Reserved121_IRQHandler              ;Reserved interrupt
                DCD     Reserved122_IRQHandler              ;Reserved interrupt
                DCD     DefaultISR                          ;123
                DCD     DefaultISR                          ;124
                DCD     DefaultISR                          ;125
                DCD     DefaultISR                          ;126
                DCD     DefaultISR                          ;127
                DCD     DefaultISR                          ;128
                DCD     DefaultISR                          ;129
                DCD     DefaultISR                          ;130
                DCD     DefaultISR                          ;131
                DCD     DefaultISR                          ;132
                DCD     DefaultISR                          ;133
                DCD     DefaultISR                          ;134
                DCD     DefaultISR                          ;135
                DCD     DefaultISR                          ;136
                DCD     DefaultISR                          ;137
                DCD     DefaultISR                          ;138
                DCD     DefaultISR                          ;139
                DCD     DefaultISR                          ;140
                DCD     DefaultISR                          ;141
                DCD     DefaultISR                          ;142
                DCD     DefaultISR                          ;143
                DCD     DefaultISR                          ;144
                DCD     DefaultISR                          ;145
                DCD     DefaultISR                          ;146
                DCD     DefaultISR                          ;147
                DCD     DefaultISR                          ;148
                DCD     DefaultISR                          ;149
                DCD     DefaultISR                          ;150
                DCD     DefaultISR                          ;151
                DCD     DefaultISR                          ;152
                DCD     DefaultISR                          ;153
                DCD     DefaultISR                          ;154
                DCD     DefaultISR                          ;155
                DCD     DefaultISR                          ;156
                DCD     DefaultISR                          ;157
                DCD     DefaultISR                          ;158
                DCD     DefaultISR                          ;159
                DCD     DefaultISR                          ;160
                DCD     DefaultISR                          ;161
                DCD     DefaultISR                          ;162
                DCD     DefaultISR                          ;163
                DCD     DefaultISR                          ;164
                DCD     DefaultISR                          ;165
                DCD     DefaultISR                          ;166
                DCD     DefaultISR                          ;167
                DCD     DefaultISR                          ;168
                DCD     DefaultISR                          ;169
                DCD     DefaultISR                          ;170
                DCD     DefaultISR                          ;171
                DCD     DefaultISR                          ;172
                DCD     DefaultISR                          ;173
                DCD     DefaultISR                          ;174
                DCD     DefaultISR                          ;175
                DCD     DefaultISR                          ;176
                DCD     DefaultISR                          ;177
                DCD     DefaultISR                          ;178
                DCD     DefaultISR                          ;179
                DCD     DefaultISR                          ;180
                DCD     DefaultISR                          ;181
                DCD     DefaultISR                          ;182
                DCD     DefaultISR                          ;183
                DCD     DefaultISR                          ;184
                DCD     DefaultISR                          ;185
                DCD     DefaultISR                          ;186
                DCD     DefaultISR                          ;187
                DCD     DefaultISR                          ;188
                DCD     DefaultISR                          ;189
                DCD     DefaultISR                          ;190
                DCD     DefaultISR                          ;191
                DCD     DefaultISR                          ;192
                DCD     DefaultISR                          ;193
                DCD     DefaultISR                          ;194
                DCD     DefaultISR                          ;195
                DCD     DefaultISR                          ;196
                DCD     DefaultISR                          ;197
                DCD     DefaultISR                          ;198
                DCD     DefaultISR                          ;199
                DCD     DefaultISR                          ;200
                DCD     DefaultISR                          ;201
                DCD     DefaultISR                          ;202
                DCD     DefaultISR                          ;203
                DCD     DefaultISR                          ;204
                DCD     DefaultISR                          ;205
                DCD     DefaultISR                          ;206
                DCD     DefaultISR                          ;207
                DCD     DefaultISR                          ;208
                DCD     DefaultISR                          ;209
                DCD     DefaultISR                          ;210
                DCD     DefaultISR                          ;211
                DCD     DefaultISR                          ;212
                DCD     DefaultISR                          ;213
                DCD     DefaultISR                          ;214
                DCD     DefaultISR                          ;215
                DCD     DefaultISR                          ;216
                DCD     DefaultISR                          ;217
                DCD     DefaultISR                          ;218
                DCD     DefaultISR                          ;219
                DCD     DefaultISR                          ;220
                DCD     DefaultISR                          ;221
                DCD     DefaultISR                          ;222
                DCD     DefaultISR                          ;223
                DCD     DefaultISR                          ;224
                DCD     DefaultISR                          ;225
                DCD     DefaultISR                          ;226
                DCD     DefaultISR                          ;227
                DCD     DefaultISR                          ;228
                DCD     DefaultISR                          ;229
                DCD     DefaultISR                          ;230
                DCD     DefaultISR                          ;231
                DCD     DefaultISR                          ;232
                DCD     DefaultISR                          ;233
                DCD     DefaultISR                          ;234
                DCD     DefaultISR                          ;235
                DCD     DefaultISR                          ;236
                DCD     DefaultISR                          ;237
                DCD     DefaultISR                          ;238
                DCD     DefaultISR                          ;239
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

; <h> Flash Configuration
;   <i> 16-byte flash configuration field that stores default protection settings (loaded on reset)
;   <i> and security information that allows the MCU to restrict access to the FTFL module.
;   <h> Backdoor Comparison Key
;     <o0>  Backdoor Comparison Key 0.  <0x0-0xFF:2>
;     <o1>  Backdoor Comparison Key 1.  <0x0-0xFF:2>
;     <o2>  Backdoor Comparison Key 2.  <0x0-0xFF:2>
;     <o3>  Backdoor Comparison Key 3.  <0x0-0xFF:2>
;     <o4>  Backdoor Comparison Key 4.  <0x0-0xFF:2>
;     <o5>  Backdoor Comparison Key 5.  <0x0-0xFF:2>
;     <o6>  Backdoor Comparison Key 6.  <0x0-0xFF:2>
;     <o7>  Backdoor Comparison Key 7.  <0x0-0xFF:2>
BackDoorK0      EQU     0xFF
BackDoorK1      EQU     0xFF
BackDoorK2      EQU     0xFF
BackDoorK3      EQU     0xFF
BackDoorK4      EQU     0xFF
BackDoorK5      EQU     0xFF
BackDoorK6      EQU     0xFF
BackDoorK7      EQU     0xFF
;   </h>
;   <h> Program flash protection bytes (FPROT)
;     <i> Each program flash region can be protected from program and erase operation by setting the associated PROT bit.
;     <i> Each bit protects a 1/32 region of the program flash memory.
;     <h> FPROT0
;       <i> Program Flash Region Protect Register 0
;       <i> 1/32 - 8/32 region
;       <o.0>   FPROT0.0
;       <o.1>   FPROT0.1
;       <o.2>   FPROT0.2
;       <o.3>   FPROT0.3
;       <o.4>   FPROT0.4
;       <o.5>   FPROT0.5
;       <o.6>   FPROT0.6
;       <o.7>   FPROT0.7
nFPROT0         EQU     0x00
FPROT0          EQU     nFPROT0:EOR:0xFF
;     </h>
;     <h> FPROT1
;       <i> Program Flash Region Protect Register 1
;       <i> 9/32 - 16/32 region
;       <o.0>   FPROT1.0
;       <o.1>   FPROT1.1
;       <o.2>   FPROT1.2
;       <o.3>   FPROT1.3
;       <o.4>   FPROT1.4
;       <o.5>   FPROT1.5
;       <o.6>   FPROT1.6
;       <o.7>   FPROT1.7
nFPROT1         EQU     0x00
FPROT1          EQU     nFPROT1:EOR:0xFF
;     </h>
;     <h> FPROT2
;       <i> Program Flash Region Protect Register 2
;       <i> 17/32 - 24/32 region
;       <o.0>   FPROT2.0
;       <o.1>   FPROT2.1
;       <o.2>   FPROT2.2
;       <o.3>   FPROT2.3
;       <o.4>   FPROT2.4
;       <o.5>   FPROT2.5
;       <o.6>   FPROT2.6
;       <o.7>   FPROT2.7
nFPROT2         EQU     0x00
FPROT2          EQU     nFPROT2:EOR:0xFF
;     </h>
;     <h> FPROT3
;       <i> Program Flash Region Protect Register 3
;       <i> 25/32 - 32/32 region
;       <o.0>   FPROT3.0
;       <o.1>   FPROT3.1
;       <o.2>   FPROT3.2
;       <o.3>   FPROT3.3
;       <o.4>   FPROT3.4
;       <o.5>   FPROT3.5
;       <o.6>   FPROT3.6
;       <o.7>   FPROT3.7
nFPROT3         EQU     0x00
FPROT3          EQU     nFPROT3:EOR:0xFF
;     </h>
;   </h>
;   <h> Flash nonvolatile option byte (FOPT)
;     <i> Allows the user to customize the operation of the MCU at boot time.
;     <o.0> LPBOOT
;       <0=> Low-power boot
;       <1=> Normal boot
;     <o.1> EZPORT_DIS
;       <0=> EzPort operation is disabled
;       <1=> EzPort operation is enabled
;     <o.2> NMI_DIS
;       <0=> NMI interrupts are always blocked
;       <1=> NMI_b pin/interrupts reset default to enabled
FOPT          EQU     0x3D
;   </h>
;   <h> Flash security byte (FSEC)
;     <i> WARNING: If SEC field is configured as "MCU security status is secure" and MEEN field is configured as "Mass erase is disabled",
;     <i> MCU's security status cannot be set back to unsecure state since Mass erase via the debugger is blocked !!!
;     <o.0..1> SEC
;       <2=> MCU security status is unsecure
;       <3=> MCU security status is secure
;         <i> Flash Security
;     <o.2..3> FSLACC
;       <2=> Freescale factory access denied
;       <3=> Freescale factory access granted
;         <i> Freescale Failure Analysis Access Code
;     <o.4..5> MEEN
;       <2=> Mass erase is disabled
;       <3=> Mass erase is enabled
;     <o.6..7> KEYEN
;       <2=> Backdoor key access enabled
;       <3=> Backdoor key access disabled
;         <i> Backdoor Key Security Enable
FSEC          EQU     0xFE
;   </h>
; </h>
                IF      :LNOT::DEF:RAM_TARGET
                AREA    FlashConfig, DATA, READONLY
__FlashConfig
                DCB     BackDoorK0, BackDoorK1, BackDoorK2, BackDoorK3
                DCB     BackDoorK4, BackDoorK5, BackDoorK6, BackDoorK7
                DCB     FPROT0    , FPROT1    , FPROT2    , FPROT3
                DCB     FSEC      , FOPT      , 0xFF      , 0xFF
                ENDIF


                AREA    |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main

                IF      :LNOT::DEF:RAM_TARGET
                REQUIRE FlashConfig
                ENDIF

                CPSID   I               ; Mask interrupts
                LDR     R0, =0xE000ED08
                LDR     R1, =__Vectors
                STR     R1, [R0]
                LDR     R2, [R1]
                MSR     MSP, R2
                LDR     R0, =SystemInit
                BLX     R0
                CPSIE   i               ; Unmask interrupts
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)
NMI_Handler\
                PROC
                EXPORT  NMI_Handler         [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler         [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler\
                PROC
                EXPORT  SVC_Handler         [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler         [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler         [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler         [WEAK]
                B       .
                ENDP
DMA0_DMA16_IRQHandler\
                PROC
                EXPORT  DMA0_DMA16_IRQHandler         [WEAK]
                LDR     R0, =DMA0_DMA16_DriverIRQHandler
                BX      R0
                ENDP

DMA1_DMA17_IRQHandler\
                PROC
                EXPORT  DMA1_DMA17_IRQHandler         [WEAK]
                LDR     R0, =DMA1_DMA17_DriverIRQHandler
                BX      R0
                ENDP

DMA2_DMA18_IRQHandler\
                PROC
                EXPORT  DMA2_DMA18_IRQHandler         [WEAK]
                LDR     R0, =DMA2_DMA18_DriverIRQHandler
                BX      R0
                ENDP

DMA3_DMA19_IRQHandler\
                PROC
                EXPORT  DMA3_DMA19_IRQHandler         [WEAK]
                LDR     R0, =DMA3_DMA19_DriverIRQHandler
                BX      R0
                ENDP

DMA4_DMA20_IRQHandler\
                PROC
                EXPORT  DMA4_DMA20_IRQHandler         [WEAK]
                LDR     R0, =DMA4_DMA20_DriverIRQHandler
                BX      R0
                ENDP

DMA5_DMA21_IRQHandler\
                PROC
                EXPORT  DMA5_DMA21_IRQHandler         [WEAK]
                LDR     R0, =DMA5_DMA21_DriverIRQHandler
                BX      R0
                ENDP

DMA6_DMA22_IRQHandler\
                PROC
                EXPORT  DMA6_DMA22_IRQHandler         [WEAK]
                LDR     R0, =DMA6_DMA22_DriverIRQHandler
                BX      R0
                ENDP

DMA7_DMA23_IRQHandler\
                PROC
                EXPORT  DMA7_DMA23_IRQHandler         [WEAK]
                LDR     R0, =DMA7_DMA23_DriverIRQHandler
                BX      R0
                ENDP

DMA8_DMA24_IRQHandler\
                PROC
                EXPORT  DMA8_DMA24_IRQHandler         [WEAK]
                LDR     R0, =DMA8_DMA24_DriverIRQHandler
                BX      R0
                ENDP

DMA9_DMA25_IRQHandler\
                PROC
                EXPORT  DMA9_DMA25_IRQHandler         [WEAK]
                LDR     R0, =DMA9_DMA25_DriverIRQHandler
                BX      R0
                ENDP

DMA10_DMA26_IRQHandler\
                PROC
                EXPORT  DMA10_DMA26_IRQHandler         [WEAK]
                LDR     R0, =DMA10_DMA26_DriverIRQHandler
                BX      R0
                ENDP

DMA11_DMA27_IRQHandler\
                PROC
                EXPORT  DMA11_DMA27_IRQHandler         [WEAK]
                LDR     R0, =DMA11_DMA27_DriverIRQHandler
                BX      R0
                ENDP

DMA12_DMA28_IRQHandler\
                PROC
                EXPORT  DMA12_DMA28_IRQHandler         [WEAK]
                LDR     R0, =DMA12_DMA28_DriverIRQHandler
                BX      R0
                ENDP

DMA13_DMA29_IRQHandler\
                PROC
                EXPORT  DMA13_DMA29_IRQHandler         [WEAK]
                LDR     R0, =DMA13_DMA29_DriverIRQHandler
                BX      R0
                ENDP

DMA14_DMA30_IRQHandler\
                PROC
                EXPORT  DMA14_DMA30_IRQHandler         [WEAK]
                LDR     R0, =DMA14_DMA30_DriverIRQHandler
                BX      R0
                ENDP

DMA15_DMA31_IRQHandler\
                PROC
                EXPORT  DMA15_DMA31_IRQHandler         [WEAK]
                LDR     R0, =DMA15_DMA31_DriverIRQHandler
                BX      R0
                ENDP

DMA_Error_IRQHandler\
                PROC
                EXPORT  DMA_Error_IRQHandler         [WEAK]
                LDR     R0, =DMA_Error_DriverIRQHandler
                BX      R0
                ENDP

I2C0_IRQHandler\
                PROC
                EXPORT  I2C0_IRQHandler         [WEAK]
                LDR     R0, =I2C0_DriverIRQHandler
                BX      R0
                ENDP

I2C1_IRQHandler\
                PROC
                EXPORT  I2C1_IRQHandler         [WEAK]
                LDR     R0, =I2C1_DriverIRQHandler
                BX      R0
                ENDP

SPI0_IRQHandler\
                PROC
                EXPORT  SPI0_IRQHandler         [WEAK]
                LDR     R0, =SPI0_DriverIRQHandler
                BX      R0
                ENDP

SPI1_IRQHandler\
                PROC
                EXPORT  SPI1_IRQHandler         [WEAK]
                LDR     R0, =SPI1_DriverIRQHandler
                BX      R0
                ENDP

I2S0_Tx_IRQHandler\
                PROC
                EXPORT  I2S0_Tx_IRQHandler         [WEAK]
                LDR     R0, =I2S0_Tx_DriverIRQHandler
                BX      R0
                ENDP

I2S0_Rx_IRQHandler\
                PROC
                EXPORT  I2S0_Rx_IRQHandler         [WEAK]
                LDR     R0, =I2S0_Rx_DriverIRQHandler
                BX      R0
                ENDP

LPUART0_IRQHandler\
                PROC
                EXPORT  LPUART0_IRQHandler         [WEAK]
                LDR     R0, =LPUART0_DriverIRQHandler
                BX      R0
                ENDP

LPUART1_IRQHandler\
                PROC
                EXPORT  LPUART1_IRQHandler         [WEAK]
                LDR     R0, =LPUART1_DriverIRQHandler
                BX      R0
                ENDP

LPUART2_IRQHandler\
                PROC
                EXPORT  LPUART2_IRQHandler         [WEAK]
                LDR     R0, =LPUART2_DriverIRQHandler
                BX      R0
                ENDP

LPUART3_IRQHandler\
                PROC
                EXPORT  LPUART3_IRQHandler         [WEAK]
                LDR     R0, =LPUART3_DriverIRQHandler
                BX      R0
                ENDP

LPUART4_IRQHandler\
                PROC
                EXPORT  LPUART4_IRQHandler         [WEAK]
                LDR     R0, =LPUART4_DriverIRQHandler
                BX      R0
                ENDP

SPI2_IRQHandler\
                PROC
                EXPORT  SPI2_IRQHandler         [WEAK]
                LDR     R0, =SPI2_DriverIRQHandler
                BX      R0
                ENDP

SPI3_IRQHandler\
                PROC
                EXPORT  SPI3_IRQHandler         [WEAK]
                LDR     R0, =SPI3_DriverIRQHandler
                BX      R0
                ENDP

I2S1_Tx_IRQHandler\
                PROC
                EXPORT  I2S1_Tx_IRQHandler         [WEAK]
                LDR     R0, =I2S1_Tx_DriverIRQHandler
                BX      R0
                ENDP

I2S1_Rx_IRQHandler\
                PROC
                EXPORT  I2S1_Rx_IRQHandler         [WEAK]
                LDR     R0, =I2S1_Rx_DriverIRQHandler
                BX      R0
                ENDP

FLEXIO0_IRQHandler\
                PROC
                EXPORT  FLEXIO0_IRQHandler         [WEAK]
                LDR     R0, =FLEXIO0_DriverIRQHandler
                BX      R0
                ENDP

I2C2_IRQHandler\
                PROC
                EXPORT  I2C2_IRQHandler         [WEAK]
                LDR     R0, =I2C2_DriverIRQHandler
                BX      R0
                ENDP

SDHC_IRQHandler\
                PROC
                EXPORT  SDHC_IRQHandler         [WEAK]
                LDR     R0, =SDHC_DriverIRQHandler
                BX      R0
                ENDP

I2C3_IRQHandler\
                PROC
                EXPORT  I2C3_IRQHandler         [WEAK]
                LDR     R0, =I2C3_DriverIRQHandler
                BX      R0
                ENDP

QuadSPI0_IRQHandler\
                PROC
                EXPORT  QuadSPI0_IRQHandler         [WEAK]
                LDR     R0, =QuadSPI0_DriverIRQHandler
                BX      R0
                ENDP

Default_Handler\
                PROC
                EXPORT  DMA0_DMA16_DriverIRQHandler         [WEAK]
                EXPORT  DMA1_DMA17_DriverIRQHandler         [WEAK]
                EXPORT  DMA2_DMA18_DriverIRQHandler         [WEAK]
                EXPORT  DMA3_DMA19_DriverIRQHandler         [WEAK]
                EXPORT  DMA4_DMA20_DriverIRQHandler         [WEAK]
                EXPORT  DMA5_DMA21_DriverIRQHandler         [WEAK]
                EXPORT  DMA6_DMA22_DriverIRQHandler         [WEAK]
                EXPORT  DMA7_DMA23_DriverIRQHandler         [WEAK]
                EXPORT  DMA8_DMA24_DriverIRQHandler         [WEAK]
                EXPORT  DMA9_DMA25_DriverIRQHandler         [WEAK]
                EXPORT  DMA10_DMA26_DriverIRQHandler         [WEAK]
                EXPORT  DMA11_DMA27_DriverIRQHandler         [WEAK]
                EXPORT  DMA12_DMA28_DriverIRQHandler         [WEAK]
                EXPORT  DMA13_DMA29_DriverIRQHandler         [WEAK]
                EXPORT  DMA14_DMA30_DriverIRQHandler         [WEAK]
                EXPORT  DMA15_DMA31_DriverIRQHandler         [WEAK]
                EXPORT  DMA_Error_DriverIRQHandler         [WEAK]
                EXPORT  MCM_IRQHandler         [WEAK]
                EXPORT  FTFE_IRQHandler         [WEAK]
                EXPORT  Read_Collision_IRQHandler         [WEAK]
                EXPORT  LVD_LVW_IRQHandler         [WEAK]
                EXPORT  LLWU_IRQHandler         [WEAK]
                EXPORT  WDOG_EWM_IRQHandler         [WEAK]
                EXPORT  TRNG0_IRQHandler         [WEAK]
                EXPORT  I2C0_DriverIRQHandler         [WEAK]
                EXPORT  I2C1_DriverIRQHandler         [WEAK]
                EXPORT  SPI0_DriverIRQHandler         [WEAK]
                EXPORT  SPI1_DriverIRQHandler         [WEAK]
                EXPORT  I2S0_Tx_DriverIRQHandler         [WEAK]
                EXPORT  I2S0_Rx_DriverIRQHandler         [WEAK]
                EXPORT  LPUART0_DriverIRQHandler         [WEAK]
                EXPORT  LPUART1_DriverIRQHandler         [WEAK]
                EXPORT  LPUART2_DriverIRQHandler         [WEAK]
                EXPORT  LPUART3_DriverIRQHandler         [WEAK]
                EXPORT  LPUART4_DriverIRQHandler         [WEAK]
                EXPORT  Reserved51_IRQHandler         [WEAK]
                EXPORT  Reserved52_IRQHandler         [WEAK]
                EXPORT  Reserved53_IRQHandler         [WEAK]
                EXPORT  Reserved54_IRQHandler         [WEAK]
                EXPORT  ADC0_IRQHandler         [WEAK]
                EXPORT  CMP0_IRQHandler         [WEAK]
                EXPORT  CMP1_IRQHandler         [WEAK]
                EXPORT  FTM0_IRQHandler         [WEAK]
                EXPORT  FTM1_IRQHandler         [WEAK]
                EXPORT  FTM2_IRQHandler         [WEAK]
                EXPORT  CMT_IRQHandler         [WEAK]
                EXPORT  RTC_IRQHandler         [WEAK]
                EXPORT  RTC_Seconds_IRQHandler         [WEAK]
                EXPORT  PIT0CH0_IRQHandler         [WEAK]
                EXPORT  PIT0CH1_IRQHandler         [WEAK]
                EXPORT  PIT0CH2_IRQHandler         [WEAK]
                EXPORT  PIT0CH3_IRQHandler         [WEAK]
                EXPORT  PDB0_IRQHandler         [WEAK]
                EXPORT  USB0_IRQHandler         [WEAK]
                EXPORT  USBDCD_IRQHandler         [WEAK]
                EXPORT  Reserved71_IRQHandler         [WEAK]
                EXPORT  DAC0_IRQHandler         [WEAK]
                EXPORT  MCG_IRQHandler         [WEAK]
                EXPORT  LPTMR0_LPTMR1_IRQHandler         [WEAK]
                EXPORT  PORTA_IRQHandler         [WEAK]
                EXPORT  PORTB_IRQHandler         [WEAK]
                EXPORT  PORTC_IRQHandler         [WEAK]
                EXPORT  PORTD_IRQHandler         [WEAK]
                EXPORT  PORTE_IRQHandler         [WEAK]
                EXPORT  SWI_IRQHandler         [WEAK]
                EXPORT  SPI2_DriverIRQHandler         [WEAK]
                EXPORT  SPI3_DriverIRQHandler         [WEAK]
                EXPORT  Reserved83_IRQHandler         [WEAK]
                EXPORT  I2S1_Tx_DriverIRQHandler         [WEAK]
                EXPORT  I2S1_Rx_DriverIRQHandler         [WEAK]
                EXPORT  FLEXIO0_DriverIRQHandler         [WEAK]
                EXPORT  FTM3_IRQHandler         [WEAK]
                EXPORT  Reserved88_IRQHandler         [WEAK]
                EXPORT  Reserved89_IRQHandler         [WEAK]
                EXPORT  I2C2_DriverIRQHandler         [WEAK]
                EXPORT  Reserved91_IRQHandler         [WEAK]
                EXPORT  Reserved92_IRQHandler         [WEAK]
                EXPORT  Reserved93_IRQHandler         [WEAK]
                EXPORT  Reserved94_IRQHandler         [WEAK]
                EXPORT  Reserved95_IRQHandler         [WEAK]
                EXPORT  Reserved96_IRQHandler         [WEAK]
                EXPORT  SDHC_DriverIRQHandler         [WEAK]
                EXPORT  Reserved98_IRQHandler         [WEAK]
                EXPORT  Reserved99_IRQHandler         [WEAK]
                EXPORT  Reserved100_IRQHandler         [WEAK]
                EXPORT  Reserved101_IRQHandler         [WEAK]
                EXPORT  Reserved102_IRQHandler         [WEAK]
                EXPORT  Reserved103_IRQHandler         [WEAK]
                EXPORT  TPM1_IRQHandler         [WEAK]
                EXPORT  TPM2_IRQHandler         [WEAK]
                EXPORT  USBHSDCD_IRQHandler         [WEAK]
                EXPORT  I2C3_DriverIRQHandler         [WEAK]
                EXPORT  Reserved108_IRQHandler         [WEAK]
                EXPORT  USBHS_IRQHandler         [WEAK]
                EXPORT  Reserved110_IRQHandler         [WEAK]
                EXPORT  Reserved111_IRQHandler         [WEAK]
                EXPORT  Reserved112_IRQHandler         [WEAK]
                EXPORT  Reserved113_IRQHandler         [WEAK]
                EXPORT  Reserved114_IRQHandler         [WEAK]
                EXPORT  Reserved115_IRQHandler         [WEAK]
                EXPORT  QuadSPI0_DriverIRQHandler         [WEAK]
                EXPORT  Reserved117_IRQHandler         [WEAK]
                EXPORT  Reserved118_IRQHandler         [WEAK]
                EXPORT  Reserved119_IRQHandler         [WEAK]
                EXPORT  Reserved120_IRQHandler         [WEAK]
                EXPORT  Reserved121_IRQHandler         [WEAK]
                EXPORT  Reserved122_IRQHandler         [WEAK]
                EXPORT  DefaultISR         [WEAK]
DMA0_DMA16_DriverIRQHandler
DMA1_DMA17_DriverIRQHandler
DMA2_DMA18_DriverIRQHandler
DMA3_DMA19_DriverIRQHandler
DMA4_DMA20_DriverIRQHandler
DMA5_DMA21_DriverIRQHandler
DMA6_DMA22_DriverIRQHandler
DMA7_DMA23_DriverIRQHandler
DMA8_DMA24_DriverIRQHandler
DMA9_DMA25_DriverIRQHandler
DMA10_DMA26_DriverIRQHandler
DMA11_DMA27_DriverIRQHandler
DMA12_DMA28_DriverIRQHandler
DMA13_DMA29_DriverIRQHandler
DMA14_DMA30_DriverIRQHandler
DMA15_DMA31_DriverIRQHandler
DMA_Error_DriverIRQHandler
MCM_IRQHandler
FTFE_IRQHandler
Read_Collision_IRQHandler
LVD_LVW_IRQHandler
LLWU_IRQHandler
WDOG_EWM_IRQHandler
TRNG0_IRQHandler
I2C0_DriverIRQHandler
I2C1_DriverIRQHandler
SPI0_DriverIRQHandler
SPI1_DriverIRQHandler
I2S0_Tx_DriverIRQHandler
I2S0_Rx_DriverIRQHandler
LPUART0_DriverIRQHandler
LPUART1_DriverIRQHandler
LPUART2_DriverIRQHandler
LPUART3_DriverIRQHandler
LPUART4_DriverIRQHandler
Reserved51_IRQHandler
Reserved52_IRQHandler
Reserved53_IRQHandler
Reserved54_IRQHandler
ADC0_IRQHandler
CMP0_IRQHandler
CMP1_IRQHandler
FTM0_IRQHandler
FTM1_IRQHandler
FTM2_IRQHandler
CMT_IRQHandler
RTC_IRQHandler
RTC_Seconds_IRQHandler
PIT0CH0_IRQHandler
PIT0CH1_IRQHandler
PIT0CH2_IRQHandler
PIT0CH3_IRQHandler
PDB0_IRQHandler
USB0_IRQHandler
USBDCD_IRQHandler
Reserved71_IRQHandler
DAC0_IRQHandler
MCG_IRQHandler
LPTMR0_LPTMR1_IRQHandler
PORTA_IRQHandler
PORTB_IRQHandler
PORTC_IRQHandler
PORTD_IRQHandler
PORTE_IRQHandler
SWI_IRQHandler
SPI2_DriverIRQHandler
SPI3_DriverIRQHandler
Reserved83_IRQHandler
I2S1_Tx_DriverIRQHandler
I2S1_Rx_DriverIRQHandler
FLEXIO0_DriverIRQHandler
FTM3_IRQHandler
Reserved88_IRQHandler
Reserved89_IRQHandler
I2C2_DriverIRQHandler
Reserved91_IRQHandler
Reserved92_IRQHandler
Reserved93_IRQHandler
Reserved94_IRQHandler
Reserved95_IRQHandler
Reserved96_IRQHandler
SDHC_DriverIRQHandler
Reserved98_IRQHandler
Reserved99_IRQHandler
Reserved100_IRQHandler
Reserved101_IRQHandler
Reserved102_IRQHandler
Reserved103_IRQHandler
TPM1_IRQHandler
TPM2_IRQHandler
USBHSDCD_IRQHandler
I2C3_DriverIRQHandler
Reserved108_IRQHandler
USBHS_IRQHandler
Reserved110_IRQHandler
Reserved111_IRQHandler
Reserved112_IRQHandler
Reserved113_IRQHandler
Reserved114_IRQHandler
Reserved115_IRQHandler
QuadSPI0_DriverIRQHandler
Reserved117_IRQHandler
Reserved118_IRQHandler
Reserved119_IRQHandler
Reserved120_IRQHandler
Reserved121_IRQHandler
Reserved122_IRQHandler
DefaultISR
                LDR    R0, =DefaultISR
                BX     R0
                ENDP
                  ALIGN


                END
