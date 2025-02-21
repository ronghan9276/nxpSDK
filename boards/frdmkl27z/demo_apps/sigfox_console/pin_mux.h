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

/*! @name PORTC5 (number 50), J2[12]/D13-SPI0_SCK
  @{ */
#define BOARD_SF_SCK_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SF_SCK_PIN 5U     /*!<@brief PORTC pin index: 5 */
                                /* @} */

/*! @name PORTC7 (number 52), J2[10]/D12-SPI0_MISO
  @{ */
#define BOARD_SF_MISO_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SF_MISO_PIN 7U     /*!<@brief PORTC pin index: 7 */
                                 /* @} */

/*! @name PORTC6 (number 51), J2[8]/D11-SPI0_MOSI
  @{ */
#define BOARD_SF_MOSI_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SF_MOSI_PIN 6U     /*!<@brief PORTC pin index: 6 */
                                 /* @} */

/*! @name PORTC4 (number 49), J2[6]/D10-SPI0_CS0
  @{ */
#define BOARD_SF_CS_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_SF_CS_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SF_CS_PIN 4U     /*!<@brief PORTC pin index: 4 */
                               /* @} */

/*! @name PORTA5 (number 27), J2[4]/D9-TPM0_CH2
  @{ */
#define BOARD_SF_ACK_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_SF_ACK_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_SF_ACK_PIN 5U     /*!<@brief PORTA pin index: 5 */
                                /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#define SOPT5_LPUART0RXSRC_LPUART_RX 0x00u /*!<@brief LPUART0 Receive Data Source Select: LPUART_RX pin */
#define SOPT5_LPUART0TXSRC_LPUART_TX 0x00u /*!<@brief LPUART0 Transmit Data Source Select: LPUART0_TX pin */

/*! @name PORTA1 (number 23), J1[2]/J25[1]/D0-UART0_RX
  @{ */
#define BOARD_DEBUG_UART0_RX_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_DEBUG_UART0_RX_PIN 1U     /*!<@brief PORTA pin index: 1 */
                                        /* @} */

/*! @name PORTA2 (number 24), J1[4]/J26[1]/D1-UART0_TX
  @{ */
#define BOARD_DEBUG_UART0_TX_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_DEBUG_UART0_TX_PIN 2U     /*!<@brief PORTA pin index: 2 */
                                        /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDEBUG_UARTPins(void);

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
