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

#define SOPT5_LPUART0RXSRC_LPUART_RX 0x00u /*!<@brief LPUART0 Receive Data Source Select: LPUART_RX pin */
#define SOPT5_LPUART0TXSRC_LPUART_TX 0x00u /*!<@brief LPUART0 Transmit Data Source Select: LPUART0_TX pin */

/*! @name PORTE31 (number 19), LED2
  @{ */
#define BOARD_LED2_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_LED2_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_LED2_PIN 31U    /*!<@brief PORTE pin index: 31 */
                              /* @} */

/*! @name PORTD5 (number 62), J2[12]/D13/SPI1_SCK/LED1/LCD_P45
  @{ */
#define BOARD_LED1_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_LED1_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_LED1_PIN 5U     /*!<@brief PORTD pin index: 5 */
                              /* @} */

/*! @name PORTA1 (number 23), J1[2]/D0/UART0_RX
  @{ */
#define BOARD_DEBUG_UART0_RX_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_DEBUG_UART0_RX_PIN 1U     /*!<@brief PORTA pin index: 1 */
                                        /* @} */

/*! @name PORTA2 (number 24), J1[4]/D1/UART0_TX
  @{ */
#define BOARD_DEBUG_UART0_TX_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_DEBUG_UART0_TX_PIN 2U     /*!<@brief PORTA pin index: 2 */
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
