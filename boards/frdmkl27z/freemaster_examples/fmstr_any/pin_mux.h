/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

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

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define SOPT5_LPUART0RXSRC_LPUART_RX 0x00u /*!<@brief LPUART0 Receive Data Source Select: LPUART_RX pin */
#define SOPT5_LPUART0TXSRC_LPUART_TX 0x00u /*!<@brief LPUART0 Transmit Data Source Select: LPUART0_TX pin */

/*! @name PORTA1 (number 23), J1[2]/J25[1]/D0-UART0_RX
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_DEBUG_UART0_RX_PORT PORTA               /*!<@brief PORT peripheral base pointer */
#define BOARD_DEBUG_UART0_RX_PIN 1U                   /*!<@brief PORT pin number */
#define BOARD_DEBUG_UART0_RX_PIN_MASK (1U << 1U)      /*!<@brief PORT pin mask */
                                                      /* @} */

/*! @name PORTA2 (number 24), J1[4]/J26[1]/D1-UART0_TX
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_DEBUG_UART0_TX_PORT PORTA               /*!<@brief PORT peripheral base pointer */
#define BOARD_DEBUG_UART0_TX_PIN 2U                   /*!<@brief PORT pin number */
#define BOARD_DEBUG_UART0_TX_PIN_MASK (1U << 2U)      /*!<@brief PORT pin mask */
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
