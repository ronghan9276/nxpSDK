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

/*!
 * @brief FTM3 channel 4 output source: FTM3_CH4 pin is output of FTM3 channel 4 output */
#define SOPT8_FTM3OCH4SRC_FTM 0x00u
/*!
 * @brief FTM3 channel 5 output source: FTM3_CH5 pin is output of FTM3 channel 5 output */
#define SOPT8_FTM3OCH5SRC_FTM 0x00u

/*! @name PORTC14 (number 86), OpenSDA_UART
  @{ */
#define BOARD_DEBUG_UART_RX_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_DEBUG_UART_RX_PIN 14U    /*!<@brief PORTC pin index: 14 */
                                       /* @} */

/*! @name PORTC15 (number 87), OpenSDA_UART
  @{ */
#define BOARD_DEBUG_UART_TX_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_DEBUG_UART_TX_PIN 15U    /*!<@brief PORTC pin index: 15 */
                                       /* @} */

/*! @name PORTC8 (number 80), J1[14]/J12[17]/D6/LEDRGB_RED/Camera Reset
  @{ */
#define BOARD_LED_RED_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_LED_RED_PIN 8U     /*!<@brief PORTC pin index: 8 */
                                 /* @} */

/*! @name PORTC9 (number 81), J1[16]/D7/LEDRGB_GREEN
  @{ */
#define BOARD_LED_GREEN_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_LED_GREEN_PIN 9U     /*!<@brief PORTC pin index: 9 */
                                   /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_I2C_ConfigurePins(void);

/*! @name PORTA1 (number 37), J2[18]/J12[4]/U6[6]/D14/I2C SDA
  @{ */
#define BOARD_ACCEL_I2C_SDA_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_ACCEL_I2C_SDA_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_ACCEL_I2C_SDA_PIN 1U     /*!<@brief PORTA pin index: 1 */
                                       /* @} */

/*! @name PORTA2 (number 38), J2[20]J12[3]/J19[6]/U6[4]/I2C_SCL
  @{ */
#define BOARD_ACCEL_I2C_SCL_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_ACCEL_I2C_SCL_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_ACCEL_I2C_SCL_PIN 2U     /*!<@brief PORTA pin index: 2 */
                                       /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_Init_I2C_GPIO_pins(void);

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
