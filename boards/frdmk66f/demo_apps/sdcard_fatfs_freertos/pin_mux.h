/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

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

#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */

/*! @name PORTB16 (coord E10), U7[4]/UART0_RX
  @{ */
#define BOARD_DEBUG_UART_RX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_DEBUG_UART_RX_PIN 16U    /*!<@brief PORTB pin index: 16 */
                                       /* @} */

/*! @name PORTB17 (coord E9), U10[1]/UART0_TX
  @{ */
#define BOARD_DEBUG_UART_TX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_DEBUG_UART_TX_PIN 17U    /*!<@brief PORTB pin index: 17 */
                                       /* @} */

/*! @name PORTE3 (coord E4), SDHC0_CMD
  @{ */
#define BOARD_SDHC0_CMD_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_CMD_PIN 3U     /*!<@brief PORTE pin index: 3 */
                                   /* @} */

/*! @name PORTE1 (coord D2), SDHC0_D0
  @{ */
#define BOARD_SDHC0_D0_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_D0_PIN 1U     /*!<@brief PORTE pin index: 1 */
                                  /* @} */

/*! @name PORTE0 (coord D3), SDHC0_D1
  @{ */
#define BOARD_SDHC0_D1_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_D1_PIN 0U     /*!<@brief PORTE pin index: 0 */
                                  /* @} */

/*! @name PORTE5 (coord E2), SDHC0_D2
  @{ */
#define BOARD_SDHC0_D2_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_D2_PIN 5U     /*!<@brief PORTE pin index: 5 */
                                  /* @} */

/*! @name PORTE4 (coord E3), SDHC0_D3
  @{ */
#define BOARD_SDHC0_D3_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_D3_PIN 4U     /*!<@brief PORTE pin index: 4 */
                                  /* @} */

/*! @name PORTE2 (coord D1), SDHC0_DCLK
  @{ */
#define BOARD_SDHC0_DCLK_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_DCLK_PIN 2U     /*!<@brief PORTE pin index: 2 */
                                    /* @} */

/*! @name PORTD10 (coord B3), SD_CARD_DETECT
  @{ */
#define BOARD_SDCARD_CARD_DETECTION_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_SDCARD_CARD_DETECTION_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_SDCARD_CARD_DETECTION_PIN 10U    /*!<@brief PORTD pin index: 10 */
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
