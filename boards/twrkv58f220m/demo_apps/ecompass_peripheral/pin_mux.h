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

#define SOPT5_UART0RXSRC_UART_RX 0x00u /*!<@brief UART 0 receive data source select: UART0_RX pin */
#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */

/*! @name PORTB0 (number 81), J15[A43]/J31[7]/UART0_RX
  @{ */
#define BOARD_DEBUG_UART_RX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_DEBUG_UART_RX_PIN 0U     /*!<@brief PORTB pin index: 0 */
                                       /* @} */

/*! @name PORTB1 (number 82), J15[A44]/J31[5]/UART0_TX
  @{ */
#define BOARD_DEBUG_UART_TX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_DEBUG_UART_TX_PIN 1U     /*!<@brief PORTB pin index: 1 */
                                       /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#define PORT_DFER_DFE_8_MASK 0x0100u /*!<@brief Digital Filter Enable Mask for item 8. */
#define PORT_DFER_DFE_9_MASK 0x0200u /*!<@brief Digital Filter Enable Mask for item 9. */

/*! @name PORTD8 (number 137), J15[A7]/U1[4]/I2C1_SCL
  @{ */
#define BOARD_I2C_CONFIGUREPINS_I2C_SCL_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_I2C_CONFIGUREPINS_I2C_SCL_PIN 8U     /*!<@brief PORTD pin index: 8 */
                                                   /* @} */

/*! @name PORTD9 (number 138), J15[A8]/U1[6]/I2C1_SDA
  @{ */
#define BOARD_I2C_CONFIGUREPINS_I2C_SDA_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_I2C_CONFIGUREPINS_I2C_SDA_PIN 9U     /*!<@brief PORTD pin index: 9 */
                                                   /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_I2C_ConfigurePins(void);

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
