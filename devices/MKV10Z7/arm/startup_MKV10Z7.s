/* ------------------------------------------------------------------------- */
/*  @file:    startup_MKV10Z7.s                                              */
/*  @purpose: CMSIS Cortex-M0P Core Device Startup File                      */
/*            MKV10Z7                                                        */
/*  @version: 1.2                                                            */
/*  @date:    2014-8-28                                                      */
/*  @build:   b190918                                                        */
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Copyright 1997-2016 Freescale Semiconductor, Inc.                         */
/* Copyright 2016-2019 NXP                                                   */
/* All rights reserved.                                                      */
/*                                                                           */
/* SPDX-License-Identifier: BSD-3-Clause                                     */
/*****************************************************************************/
/* Version: GCC for ARM Embedded Processors                                  */
/*****************************************************************************/
    .syntax unified
    .arch armv6-m
    .eabi_attribute Tag_ABI_align_preserved, 1 /*8-byte alignment */

    .section .isr_vector, "a"
    .align 2
    .globl __Vectors
__Vectors:
    .long   Image$$ARM_LIB_STACK$$ZI$$Limit                 /* Top of Stack */
    .long   Reset_Handler                                   /* Reset Handler */
    .long   NMI_Handler                                     /* NMI Handler*/
    .long   HardFault_Handler                               /* Hard Fault Handler*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   SVC_Handler                                     /* SVCall Handler*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   PendSV_Handler                                  /* PendSV Handler*/
    .long   SysTick_Handler                                 /* SysTick Handler*/

                                                            /* External Interrupts*/
    .long   DMA0_IRQHandler                                 /* DMA channel 0 transfer complete*/
    .long   DMA1_IRQHandler                                 /* DMA channel 1 transfer complete*/
    .long   DMA2_IRQHandler                                 /* DMA channel 2 transfer complete*/
    .long   DMA3_IRQHandler                                 /* DMA channel 3 transfer complete*/
    .long   DMA_Error_IRQHandler                            /* DMA channel 0 1 2 3 error*/
    .long   FTFA_IRQHandler                                 /* Command complete and read collision*/
    .long   PMC_IRQHandler                                  /* Low-voltage detect, low-voltage warning*/
    .long   LLWU_IRQHandler                                 /* Low Leakage Wakeup*/
    .long   I2C0_IRQHandler                                 /* I2C0 interrupt*/
    .long   Reserved25_IRQHandler                           /* Reserved interrupt*/
    .long   SPI0_IRQHandler                                 /* SPI0 single interrupt vector for all sources*/
    .long   Reserved27_IRQHandler                           /* Reserved interrupt*/
    .long   UART0_IRQHandler                                /* UART0 status and error*/
    .long   UART1_IRQHandler                                /* UART1 status and error*/
    .long   Reserved30_IRQHandler                           /* Reserved interrupt*/
    .long   ADC0_IRQHandler                                 /* ADC0 interrupt*/
    .long   ADC1_IRQHandler                                 /* ADC1 interrupt*/
    .long   FTM0_IRQHandler                                 /* FTM0 single interrupt vector for all sources*/
    .long   FTM1_IRQHandler                                 /* FTM1 single interrupt vector for all sources*/
    .long   FTM2_IRQHandler                                 /* FTM2 single interrupt vector for all sources*/
    .long   CMP0_IRQHandler                                 /* CMP0 interrupt*/
    .long   CMP1_IRQHandler                                 /* CMP1 interrupt*/
    .long   Reserved38_IRQHandler                           /* Reserved interrupt*/
    .long   WDOG_EWM_IRQHandler                             /* Single interrupt vector for  WDOG and EWM*/
    .long   Reserved40_IRQHandler                           /* Reserved interrupt*/
    .long   DAC0_IRQHandler                                 /* DAC0 interrupt*/
    .long   Reserved42_IRQHandler                           /* Reserved interrupt*/
    .long   MCG_IRQHandler                                  /* MCG interrupt*/
    .long   LPTMR0_IRQHandler                               /* LPTMR0 interrupt*/
    .long   PDB0_IRQHandler                                 /* PDB0 interrupt*/
    .long   PORTA_IRQHandler                                /* GPIOA Pin detect*/
    .long   PORTB_PORTC_PORTD_PORTE_IRQHandler              /* Single interrupt vector for GPIOB; GPIOC; GPIOD; GPIOE Pin detect*/

    .size    __Vectors, . - __Vectors

/* Flash Configuration */
    .section .FlashConfig, "a"
    .long 0xFFFFFFFF
    .long 0xFFFFFFFF
    .long 0xFFFFFFFF
    .long 0xFFFFFFFE

    .text
    .thumb

/* Reset Handler */

    .thumb_func
    .align 2
    .globl   Reset_Handler
    .weak    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
    cpsid   i               /* Mask interrupts */
    .equ    VTOR, 0xE000ED08
    ldr     r0, =VTOR
    ldr     r1, =__Vectors
    str     r1, [r0]
    ldr     r2, [r1]
    msr     msp, r2
    ldr   r0,=SystemInit
    blx   r0
    cpsie   i               /* Unmask interrupts */
    ldr   r0,=__main
    bx    r0

    .pool
    .size Reset_Handler, . - Reset_Handler

    .align  1
    .thumb_func
    .weak DefaultISR
    .type DefaultISR, %function
DefaultISR:
    ldr r0, =DefaultISR
    bx r0
    .size DefaultISR, . - DefaultISR

    .align 1
    .thumb_func
    .weak NMI_Handler
    .type NMI_Handler, %function
NMI_Handler:
    ldr   r0,=NMI_Handler
    bx    r0
    .size NMI_Handler, . - NMI_Handler

    .align 1
    .thumb_func
    .weak HardFault_Handler
    .type HardFault_Handler, %function
HardFault_Handler:
    ldr   r0,=HardFault_Handler
    bx    r0
    .size HardFault_Handler, . - HardFault_Handler

    .align 1
    .thumb_func
    .weak SVC_Handler
    .type SVC_Handler, %function
SVC_Handler:
    ldr   r0,=SVC_Handler
    bx    r0
    .size SVC_Handler, . - SVC_Handler

    .align 1
    .thumb_func
    .weak PendSV_Handler
    .type PendSV_Handler, %function
PendSV_Handler:
    ldr   r0,=PendSV_Handler
    bx    r0
    .size PendSV_Handler, . - PendSV_Handler

    .align 1
    .thumb_func
    .weak SysTick_Handler
    .type SysTick_Handler, %function
SysTick_Handler:
    ldr   r0,=SysTick_Handler
    bx    r0
    .size SysTick_Handler, . - SysTick_Handler

    .align 1
    .thumb_func
    .weak DMA0_IRQHandler
    .type DMA0_IRQHandler, %function
DMA0_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_IRQHandler, . - DMA0_IRQHandler

    .align 1
    .thumb_func
    .weak DMA1_IRQHandler
    .type DMA1_IRQHandler, %function
DMA1_IRQHandler:
    ldr   r0,=DMA1_DriverIRQHandler
    bx    r0
    .size DMA1_IRQHandler, . - DMA1_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_IRQHandler
    .type DMA2_IRQHandler, %function
DMA2_IRQHandler:
    ldr   r0,=DMA2_DriverIRQHandler
    bx    r0
    .size DMA2_IRQHandler, . - DMA2_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_IRQHandler
    .type DMA3_IRQHandler, %function
DMA3_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_IRQHandler, . - DMA3_IRQHandler

    .align 1
    .thumb_func
    .weak DMA_Error_IRQHandler
    .type DMA_Error_IRQHandler, %function
DMA_Error_IRQHandler:
    ldr   r0,=DMA_Error_DriverIRQHandler
    bx    r0
    .size DMA_Error_IRQHandler, . - DMA_Error_IRQHandler

    .align 1
    .thumb_func
    .weak I2C0_IRQHandler
    .type I2C0_IRQHandler, %function
I2C0_IRQHandler:
    ldr   r0,=I2C0_DriverIRQHandler
    bx    r0
    .size I2C0_IRQHandler, . - I2C0_IRQHandler

    .align 1
    .thumb_func
    .weak SPI0_IRQHandler
    .type SPI0_IRQHandler, %function
SPI0_IRQHandler:
    ldr   r0,=SPI0_DriverIRQHandler
    bx    r0
    .size SPI0_IRQHandler, . - SPI0_IRQHandler

    .align 1
    .thumb_func
    .weak UART0_IRQHandler
    .type UART0_IRQHandler, %function
UART0_IRQHandler:
    ldr   r0,=UART0_DriverIRQHandler
    bx    r0
    .size UART0_IRQHandler, . - UART0_IRQHandler

    .align 1
    .thumb_func
    .weak UART1_IRQHandler
    .type UART1_IRQHandler, %function
UART1_IRQHandler:
    ldr   r0,=UART1_DriverIRQHandler
    bx    r0
    .size UART1_IRQHandler, . - UART1_IRQHandler


/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro def_irq_handler  handler_name
    .weak \handler_name
    .set  \handler_name, DefaultISR
    .endm

/* Exception Handlers */
    def_irq_handler    DMA0_DriverIRQHandler
    def_irq_handler    DMA1_DriverIRQHandler
    def_irq_handler    DMA2_DriverIRQHandler
    def_irq_handler    DMA3_DriverIRQHandler
    def_irq_handler    DMA_Error_DriverIRQHandler
    def_irq_handler    FTFA_IRQHandler
    def_irq_handler    PMC_IRQHandler
    def_irq_handler    LLWU_IRQHandler
    def_irq_handler    I2C0_DriverIRQHandler
    def_irq_handler    Reserved25_IRQHandler
    def_irq_handler    SPI0_DriverIRQHandler
    def_irq_handler    Reserved27_IRQHandler
    def_irq_handler    UART0_DriverIRQHandler
    def_irq_handler    UART1_DriverIRQHandler
    def_irq_handler    Reserved30_IRQHandler
    def_irq_handler    ADC0_IRQHandler
    def_irq_handler    ADC1_IRQHandler
    def_irq_handler    FTM0_IRQHandler
    def_irq_handler    FTM1_IRQHandler
    def_irq_handler    FTM2_IRQHandler
    def_irq_handler    CMP0_IRQHandler
    def_irq_handler    CMP1_IRQHandler
    def_irq_handler    Reserved38_IRQHandler
    def_irq_handler    WDOG_EWM_IRQHandler
    def_irq_handler    Reserved40_IRQHandler
    def_irq_handler    DAC0_IRQHandler
    def_irq_handler    Reserved42_IRQHandler
    def_irq_handler    MCG_IRQHandler
    def_irq_handler    LPTMR0_IRQHandler
    def_irq_handler    PDB0_IRQHandler
    def_irq_handler    PORTA_IRQHandler
    def_irq_handler    PORTB_PORTC_PORTD_PORTE_IRQHandler

    .end
