/*
 * Copyright 2018-2019 NXP.
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

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

/*! @name PORTD5 (coord A2), J16[3]/J24[A79]/LED_J_PTD5
  @{ */
#define BOARD_LED_YELLOW_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_LED_YELLOW_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_LED_YELLOW_PIN 5U     /*!<@brief PORTD pin index: 5 */
                                    /* @} */

/*! @name PORTD6 (coord B2), J16[5]/J24[A80]/J24[B38]/LED_J_PTD6
  @{ */
#define BOARD_LED_ORANGE_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_LED_ORANGE_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_LED_ORANGE_PIN 6U     /*!<@brief PORTD pin index: 6 */
                                    /* @} */

/*! @name PORTD4 (coord A3), J16[1]/J24[B47]/J24[A78]/LED_J_PTD4
  @{ */
#define BOARD_LED_GREEN_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_LED_GREEN_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_LED_GREEN_PIN 4U     /*!<@brief PORTD pin index: 4 */
                                   /* @} */

/*! @name PORTD7 (coord A1), J16[7]/J24[A56]/J32[4]/J34[1]/USB_K22_ID/LED_J_PTD7
  @{ */
#define BOARD_LED_BLUE_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_LED_BLUE_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_LED_BLUE_PIN 7U     /*!<@brief PORTD pin index: 7 */
                                  /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLEDsPins(void);

/*! @name PORTC6 (coord C7), J24[A58]/J24[A71]/J24[B61]
  @{ */
#define BOARD_SW1_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_SW1_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SW1_PIN 6U     /*!<@brief PORTC pin index: 6 */
                             /* @} */

/*! @name PORTC7 (coord B7), J24[A59]/J24[A72]
  @{ */
#define BOARD_SW2_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_SW2_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SW2_PIN 7U     /*!<@brief PORTC pin index: 7 */
                             /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitButtonsPins(void);

#define SOPT5_UART1TXSRC_UART_TX 0x00u /*!<@brief UART 1 transmit data source select: UART1_TX pin */

/*! @name PORTE1 (coord E3), UART1_RX_PKYK
  @{ */
#define BOARD_DEBUG_UART_RX_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_DEBUG_UART_RX_PIN 1U     /*!<@brief PORTE pin index: 1 */
                                       /* @} */

/*! @name PORTE0 (coord E4), UART1_TX_PKYK
  @{ */
#define BOARD_DEBUG_UART_TX_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_DEBUG_UART_TX_PIN 0U     /*!<@brief PORTE pin index: 0 */
                                       /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDEBUG_UARTPins(void);

/*! @name PORTC11 (coord C5), J5[4]/J7[1]/J24[A60]/J24[B51]/J24[B71]/U1[6]/I2C1_SDA
  @{ */
#define BOARD_ACCEL_SDA_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_ACCEL_SDA_PIN 11U    /*!<@brief PORTC pin index: 11 */
                                   /* @} */

/*! @name PORTC10 (coord C6), J5[3]/J24[A75]/J24[B50]/J24[B52/J9[1]/U1[4]/I2C1_SCL
  @{ */
#define BOARD_ACCEL_SCL_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_ACCEL_SCL_PIN 10U    /*!<@brief PORTC pin index: 10 */
                                   /* @} */

/*! @name PORTB0 (coord G11), J6[8]/J24[B27]/U1[11]/INT1
  @{ */
#define BOARD_ACCEL_INT1_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_ACCEL_INT1_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_ACCEL_INT1_PIN 0U     /*!<@brief PORTB pin index: 0 */
                                    /* @} */

/*! @name PORTB1 (coord G10), J6[9]/J24[B28]/U1[9]/INT2
  @{ */
#define BOARD_ACCEL_INT2_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_ACCEL_INT2_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_ACCEL_INT2_PIN 1U     /*!<@brief PORTB pin index: 1 */
                                    /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitAccelPins(void);

/*! @name PORTA18 (coord L11), X51[1]/8MHz_EXTAL
  @{ */
#define BOARD_EXTAL0_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_EXTAL0_PIN 18U    /*!<@brief PORTA pin index: 18 */
                                /* @} */

/*! @name PORTA19 (coord K11), X51[3]/8MHz_XTAL
  @{ */
#define BOARD_XTAL0_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_XTAL0_PIN 19U    /*!<@brief PORTA pin index: 19 */
                               /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitOSC0Pins(void);

/*! @name USB0_DP (coord F1), J32[2]/U8[3]/USB0_R_DP
  @{ */
/* @} */

/*! @name USB0_DM (coord F2), J32[3]/U8[5]/USB0_R_DN
  @{ */
/* @} */

/*! @name PORTC9 (coord D6), J26[2]/J24[A74]/U61[1]/K22_USB_ENA
  @{ */
#define BOARD_K22_USB_ENA_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_K22_USB_ENA_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_K22_USB_ENA_PIN 9U     /*!<@brief PORTC pin index: 9 */
                                     /* @} */

/*! @name PORTD7 (coord A1), J16[7]/J24[A56]/J32[4]/J34[1]/USB_K22_ID/LED_J_PTD7
  @{ */
#define BOARD_USB_K22_ID_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_USB_K22_ID_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_USB_K22_ID_PIN 7U     /*!<@brief PORTD pin index: 7 */
                                    /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitUSBHostPins(void);

/*! @name PORTB2 (coord G9), J18[1]/J24[B29]/POT_5K
  @{ */
#define BOARD_POT_5K_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_POT_5K_PIN 2U     /*!<@brief PORTB pin index: 2 */
                                /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPOTPins(void);

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
