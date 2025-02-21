/*
 * Copyright 2019 NXP
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

#define SOPT5_UART1RXSRC_UART_RX 0x00u /*!<@brief UART 1 receive data source select: UART1_RX pin */
#define SOPT5_UART1TXSRC_UART_TX 0x00u /*!<@brief UART 1 transmit data source select: UART1_TX pin */

/*! @name PORTE0 (number 1), J500[A44]/J501[5]/J505[4]/GPIOE0/TXD1
  @{ */
#define BOARD_DEBUG_UART_TX_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_DEBUG_UART_TX_PIN 0U     /*!<@brief PORTE pin index: 0 */
                                       /* @} */

/*! @name PORTE1 (number 2), J500[A43]/J501[7]/J506[4]/GPIOE1/RXD1
  @{ */
#define BOARD_DEBUG_UART_RX_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_DEBUG_UART_RX_PIN 1U     /*!<@brief PORTE pin index: 1 */
                                       /* @} */

/*! @name PORTC7 (number 79), J4[1]/J500[B62]/GC7/SW1
  @{ */
#define BOARD_SW1_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SW1_PIN 7U     /*!<@brief PORTC pin index: 7 */
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
