/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
    kPIN_MUX_DirectionInput = 0U,        /* Input direction */
    kPIN_MUX_DirectionOutput = 1U,       /* Output direction */
    kPIN_MUX_DirectionInputOrOutput = 2U /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif


#define SOPT5_LPUART0RXSRC_LPUART_RX 0x00u /*!<@brief LPUART 0 receive data source select: LPUART0_RX pin */
#define SOPT5_LPUART0TXSRC_LPUART_TX 0x00u /*!<@brief LPUART0 transmit data source select: LPUART0_TX pin */

/*! @name PORTB16 (number 51), J1[2]/Arduino_D0_UART0_RX/UART1_RX_TGTMCU
  @{ */
/*!
 * @brief Device name: LPUART0 */
#define BOARD_INITPINS_DEBUG_UART_RX_PERIPHERAL LPUART0
/*!
 * @brief LPUART0 signal: RX */
#define BOARD_INITPINS_DEBUG_UART_RX_SIGNAL RX
/*!
 * @brief PORT device name: PORTB */
#define BOARD_INITPINS_DEBUG_UART_RX_PORT PORTB
/*!
 * @brief PORTB pin index: 16 */
#define BOARD_INITPINS_DEBUG_UART_RX_PIN 16U
/*!
 * @brief Pin name */
#define BOARD_INITPINS_DEBUG_UART_RX_PIN_NAME LPUART0_RX
/*!
 * @brief Label */
#define BOARD_INITPINS_DEBUG_UART_RX_LABEL "J1[2]/Arduino_D0_UART0_RX/UART1_RX_TGTMCU"
/*!
 * @brief Identifier name */
#define BOARD_INITPINS_DEBUG_UART_RX_NAME "DEBUG_UART_RX"
/* @} */

/*! @name PORTB17 (number 52), J1[4]/Arduino_D1_UART0_TX/UART1_TX_TGTMCU
  @{ */
/*!
 * @brief Device name: LPUART0 */
#define BOARD_INITPINS_DEBUG_UART_TX_PERIPHERAL LPUART0
/*!
 * @brief LPUART0 signal: TX */
#define BOARD_INITPINS_DEBUG_UART_TX_SIGNAL TX
/*!
 * @brief PORT device name: PORTB */
#define BOARD_INITPINS_DEBUG_UART_TX_PORT PORTB
/*!
 * @brief PORTB pin index: 17 */
#define BOARD_INITPINS_DEBUG_UART_TX_PIN 17U
/*!
 * @brief Pin name */
#define BOARD_INITPINS_DEBUG_UART_TX_PIN_NAME LPUART0_TX
/*!
 * @brief Label */
#define BOARD_INITPINS_DEBUG_UART_TX_LABEL "J1[4]/Arduino_D1_UART0_TX/UART1_TX_TGTMCU"
/*!
 * @brief Identifier name */
#define BOARD_INITPINS_DEBUG_UART_TX_NAME "DEBUG_UART_TX"
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
