/*
** ###################################################################
**     Processors:          MK21FN1M0VLQ12
**                          MK21FN1M0VMC12
**                          MK21FN1M0VMD12
**                          MK21FX512VLQ12
**                          MK21FX512VMC12
**                          MK21FX512VMD12
**
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          MCUXpresso Compiler
**
**     Reference manuals:   K21P121M120SF5V2RM, Rev.3, Apr 2014
**                          K21P144M120SF5V2RM, Rev.3, Apr 2014
**
**     Version:             rev. 1.9, 2015-07-29
**     Build:               b170713
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     The Clear BSD License
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2017 NXP
**     All rights reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted (subject to the limitations in the disclaimer below) provided
**      that the following conditions are met:
**
**     1. Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     2. Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     3. Neither the name of the copyright holder nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2012-11-12)
**         Initial version.
**     - rev. 1.1 (2012-12-04)
**         Update according to reference manual rev.1
**     - rev. 1.2 (2013-01-21)
**         Registers related to security features removed.
**     - rev. 1.3 (2013-03-11)
**         System initialization updated to add 120MHz clock option.
**     - rev. 1.4 (2013-04-05)
**         Changed start of doxygen comment.
**     - rev. 1.5 (2013-05-16)
**         Update according to reference manual rev.2
**     - rev. 1.6 (2013-10-29)
**         Definition of BITBAND macros updated to support peripherals with 32-bit acces disabled.
**         Access restriction of some registers fixed.
**     - rev. 1.7 (2014-02-18)
**         UART0 module - LON registers removed.
**     - rev. 1.8 (2015-02-19)
**         update of SystemInit() imlementation
**         Module access macro module_BASES replaced by module_BASE_PTRS.
**         Register accessor macros added to the memory map.
**         Renamed interrupt vector Watchdog to WDOG_EWM, LPTimer to LPTMR0 and LLW to LLWU
**     - rev. 1.9 (2015-07-29)
**         Correction of backward compatibility.
**
** ###################################################################
*/

/*!
 * @file MK21F12
 * @version 1.9
 * @date 2015-07-29
 * @brief Device specific configuration file for MK21F12 (header file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#ifndef _SYSTEM_MK21F12_H_
#define _SYSTEM_MK21F12_H_                       /**< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


#ifndef DISABLE_WDOG
  #define DISABLE_WDOG                 1
#endif


/* Define clock source values */

#define CPU_XTAL_CLK_HZ                8000000U            /* Value of the external crystal or oscillator clock frequency of the system oscillator (OSC) in Hz */
#define CPU_XTAL32k_CLK_HZ             32768U              /* Value of the external 32k crystal or oscillator clock frequency of the RTC in Hz */
#define CPU_INT_SLOW_CLK_HZ            32768U              /* Value of the slow internal oscillator clock frequency in Hz */
#define CPU_INT_FAST_CLK_HZ            4000000U            /* Value of the fast internal oscillator clock frequency in Hz */

/* RTC oscillator setting */
/* #undef SYSTEM_RTC_CR_VALUE */                           /* RTC oscillator not enabled. Commented out for MISRA compliance. */

/* Low power mode enable */
/* SMC_PMPROT: AVLP=1,ALLS=1,AVLLS=1 */
#define SYSTEM_SMC_PMPROT_VALUE        0x2AU               /* SMC_PMPROT */

#define DEFAULT_SYSTEM_CLOCK           20971520u           /* Default System clock value */


/**
 * @brief System clock frequency (core clock)
 *
 * The system clock frequency supplied to the SysTick timer and the processor
 * core clock. This variable can be used by the user application to setup the
 * SysTick timer or configure other parameters. It may also be used by debugger to
 * query the frequency of the debug timer or configure the trace clock speed
 * SystemCoreClock is initialized with a correct predefined value.
 */
extern uint32_t SystemCoreClock;

/**
 * @brief Setup the microcontroller system.
 *
 * Typically this function configures the oscillator (PLL) that is part of the
 * microcontroller device. For systems with variable clock speed it also updates
 * the variable SystemCoreClock. SystemInit is called from startup_device file.
 */
void SystemInit (void);

/**
 * @brief Updates the SystemCoreClock variable.
 *
 * It must be called whenever the core clock is changed during program
 * execution. SystemCoreClockUpdate() evaluates the clock register settings and calculates
 * the current core clock.
 */
void SystemCoreClockUpdate (void);

#ifdef __cplusplus
}
#endif

#endif  /* _SYSTEM_MK21F12_H_ */
