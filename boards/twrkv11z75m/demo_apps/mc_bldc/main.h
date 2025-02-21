/*
 * Copyright 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _MAIN_H_
#define _MAIN_H_

#include "board.h"
#include "mcdrv.h"
#include "freemaster.h"
#include "pin_mux.h"
#include "m1_sm_ref_sol.h"
#include "fsl_uart.h"

#include "freemaster_serial_uart.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief The UART to use for FreeMASTER communication */
#define BOARD_FMSTR_UART_PORT UART0
#define BOARD_FMSTR_UART_BAUDRATE 19200

/* Macro for correct Cortex CM0 / CM4 end of interrupt */
#define M1_END_OF_ISR \
    {                 \
        __DSB(); \
        __ISB(); \
    }

/* CPU load measurement SysTick START / STOP macros */
#define SYSTICK_START_COUNT() (SysTick->VAL = SysTick->LOAD)
#define SYSTICK_STOP_COUNT(par1) uint32_t val = SysTick->VAL; uint32_t load = SysTick->LOAD; par1 = load - val

/* RED TWR-LV3PH LED control */
#define LED_LV3PH_RED_TOGGLE() (GPIOA->PTOR = (1U << 5U))
#define LED_LV3PH_RED_ON() (GPIOA->PSOR = (1U << 5U))
#define LED_LV3PH_RED_OFF() (GPIOA->PCOR = (1U << 5U))

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
  
/*******************************************************************************
 * API
 ******************************************************************************/

void DemoSpeedStimulator(void);

/* Init HW */
void BOARD_Init(void);
void BOARD_InitUART(uint32_t, uint32_t);
void BOARD_InitSysTick(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _MAIN_H_ */
