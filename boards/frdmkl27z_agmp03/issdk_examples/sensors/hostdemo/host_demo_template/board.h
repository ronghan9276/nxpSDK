/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* The board name */
#define BOARD_NAME "FRDM-KL27Z"

/* The LPUART to use for debug messages. */
#define BOARD_DEBUG_UART_TYPE     kSerialPort_Uart
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) LPUART0
#define BOARD_DEBUG_UART_INSTANCE 0U
#define BOARD_DEBUG_UART_CLKSRC   kCLOCK_McgIrc48MClk
#define BOARD_DEBUG_UART_CLK_FREQ CLOCK_GetPeriphClkFreq()
#define BOARD_UART_IRQ            LPUART0_IRQn
#define BOARD_UART_IRQ_HANDLER    LPUART0_IRQHandler

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE 115200
#endif /* BOARD_DEBUG_UART_BAUDRATE */

/* Define the port macros for the board switches */
#define BOARD_SW1_GPIO        GPIOA
#define BOARD_SW1_PORT        PORTA
#define BOARD_SW1_GPIO_PIN    4U
#define BOARD_SW1_IRQ         PORTA_IRQn
#define BOARD_SW1_IRQ_HANDLER PORTA_IRQHandler
#define BOARD_SW1_NAME        "SW1"

#define BOARD_SW3_GPIO        GPIOC
#define BOARD_SW3_PORT        PORTC
#define BOARD_SW3_GPIO_PIN    1U
#define BOARD_SW3_IRQ         PORTB_PORTC_PORTD_PORTE_IRQn
#define BOARD_SW3_IRQ_HANDLER PORTB_PORTC_PORTD_PORTE_IRQHandler
#define BOARD_SW3_NAME        "SW3"

#define LLWU_SW_GPIO        BOARD_SW3_GPIO
#define LLWU_SW_PORT        BOARD_SW3_PORT
#define LLWU_SW_GPIO_PIN    BOARD_SW3_GPIO_PIN
#define LLWU_SW_IRQ         BOARD_SW3_IRQ
#define LLWU_SW_IRQ_HANDLER BOARD_SW3_IRQ_HANDLER
#define LLWU_SW_NAME        BOARD_SW3_NAME

/* Board led color mapping */
#define LOGIC_LED_ON              0U
#define LOGIC_LED_OFF             1U
#define BOARD_LED_RED_GPIO        GPIOB
#define BOARD_LED_RED_GPIO_PORT   PORTB
#define BOARD_LED_RED_GPIO_PIN    18U
#define BOARD_LED_GREEN_GPIO      GPIOB
#define BOARD_LED_GREEN_GPIO_PORT PORTB
#define BOARD_LED_GREEN_GPIO_PIN  19U
#define BOARD_LED_BLUE_GPIO       GPIOA
#define BOARD_LED_BLUE_GPIO_PORT  PORTA
#define BOARD_LED_BLUE_GPIO_PIN   13U

#define LED_RED_INIT(output)                                                 \
    GPIO_WritePinOutput(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, output); \
    BOARD_LED_RED_GPIO->PDDR |= (1U << BOARD_LED_RED_GPIO_PIN) /*!< Enable target LED_RED */
#define LED_RED_ON() \
    GPIO_ClearPinsOutput(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN) /*!< Turn on target LED_RED */
#define LED_RED_OFF() \
    GPIO_SetPinsOutput(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN) /*!< Turn off target LED_RED */
#define LED_RED_TOGGLE() \
    GPIO_TogglePinsOutput(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN) /*!< Toggle on target LED_RED */

#define LED_GREEN_INIT(output)                                                   \
    GPIO_WritePinOutput(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, output); \
    BOARD_LED_GREEN_GPIO->PDDR |= (1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Enable target LED_GREEN */
#define LED_GREEN_ON() \
    GPIO_ClearPinsOutput(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Turn on target LED_GREEN */
#define LED_GREEN_OFF() \
    GPIO_SetPinsOutput(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Turn off target LED_GREEN */
#define LED_GREEN_TOGGLE() \
    GPIO_TogglePinsOutput(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Toggle on target LED_GREEN */

#define LED_BLUE_INIT(output)                                                  \
    GPIO_WritePinOutput(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, output); \
    BOARD_LED_BLUE_GPIO->PDDR |= (1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Enable target LED_BLUE */
#define LED_BLUE_ON() \
    GPIO_ClearPinsOutput(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Turn on target LED_BLUE */
#define LED_BLUE_OFF() \
    GPIO_SetPinsOutput(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Turn off target LED_BLUE */
#define LED_BLUE_TOGGLE() \
    GPIO_TogglePinsOutput(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Toggle on target LED_BLUE */

#define BOARD_ACCEL_I2C_BASEADDR I2C1

/* ERPC SPI configuration */
#define ERPC_BOARD_SPI_BASEADDR            SPI0
#define ERPC_BOARD_SPI_BAUDRATE            500000U
#define ERPC_BOARD_SPI_CLKSRC              SPI0_CLK_SRC
#define ERPC_BOARD_SPI_CLK_FREQ            CLOCK_GetFreq(SPI0_CLK_SRC)
#define ERPC_BOARD_SPI_INT_GPIO            GPIOB
#define ERPC_BOARD_SPI_INT_PORT            PORTB
#define ERPC_BOARD_SPI_INT_PIN             0U
#define ERPC_BOARD_SPI_INT_PIN_IRQ         PORTB_PORTC_PORTD_PORTE_IRQn
#define ERPC_BOARD_SPI_INT_PIN_IRQ_HANDLER PORTB_PORTC_PORTD_PORTE_IRQHandler

/* Board accelerometer driver */
#define BOARD_ACCEL_MMA

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

void BOARD_InitDebugConsole(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
