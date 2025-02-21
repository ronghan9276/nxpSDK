/*
 * Copyright 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
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
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

/*! @name PORTD0 (number 93), MB_J11[A14]/MB_U12[18]/MB_PWM_AT/J4[A14]/PWM0
  @{ */
#define MB_PWM_AT_PORT PORTD /*!<@brief PORT device name: PORTD */
#define MB_PWM_AT_PIN 0U     /*!<@brief PORTD pin index: 0 */
                             /* @} */

/*! @name PORTD1 (number 94), MB_J11[A15]/MB_U12[12]/MB_PWM_AB/J4[A15]/PWM1
  @{ */
#define MB_PWM_AB_PORT PORTD /*!<@brief PORT device name: PORTD */
#define MB_PWM_AB_PIN 1U     /*!<@brief PORTD pin index: 1 */
                             /* @} */

/*! @name PORTD2 (number 95), MB_J11[A16]/MB_U12[19]/MB_PWM_BT/J4[A16]/PWM2
  @{ */
#define MB_PWM_BT_PORT PORTD /*!<@brief PORT device name: PORTD */
#define MB_PWM_BT_PIN 2U     /*!<@brief PORTD pin index: 2 */
                             /* @} */

/*! @name PORTD3 (number 96), MB_J11[A17]/MB_U12[13]/MB_PWM_BB/J4[A17]/PWM3
  @{ */
#define MB_PWM_BB_PORT PORTD /*!<@brief PORT device name: PORTD */
#define MB_PWM_BB_PIN 3U     /*!<@brief PORTD pin index: 3 */
                             /* @} */

/*! @name PORTD4 (number 97), MB_J11[A18]/MB_U12[20]/MB_PWM_CT/J4[A18]/PWM4
  @{ */
#define MB_PWM_CT_PORT PORTD /*!<@brief PORT device name: PORTD */
#define MB_PWM_CT_PIN 4U     /*!<@brief PORTD pin index: 4 */
                             /* @} */

/*! @name PORTD5 (number 98), MB_J11[A19]/MB_U12[14]/MB_PWM_CB/J4[A19]/PWM5
  @{ */
#define MB_PWM_CB_PORT PORTD /*!<@brief PORT device name: PORTD */
#define MB_PWM_CB_PIN 5U     /*!<@brief PORTD pin index: 5 */
                             /* @} */

/*! @name PORTE1 (number 2), MB_J11[A25]/MB_U12[11]/MB_TP28/MB_FAULT/MB_FAULT_1/MB_PFC_overcurrent/J4[A25]/FAULT_1
  @{ */
#define MB_FAULT_1_PORT PORTE /*!<@brief PORT device name: PORTE */
#define MB_FAULT_1_PIN 1U     /*!<@brief PORTE pin index: 1 */
                              /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitMC_PWMPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitPFCPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitANA_SENSPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitBEMFPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitENCPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitUSB_UARTPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitBRAKEPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitEXT_UARTPins(void);

#define SOPT7_ADCAALTTRGEN_XBAR 0x00u /*!<@brief ADCA alternate trigger enable: XBARA output 12. */

/*! @name PORTB19 (number 65), MB_J11[B20]/MB_U9[4]/MB_USER_LED/J4[B20]/USER_LED
  @{ */
#define MB_LED_GREEN_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define MB_LED_GREEN_PORT PORTB /*!<@brief PORT device name: PORTB */
#define MB_LED_GREEN_PIN 19U    /*!<@brief PORTB pin index: 19 */
                                /* @} */

/*! @name PORTC16 (number 90), MB_J11[B25]/MB_U9[2]/MB_TP_35/MB_MCU_BRAKE/J4[B25]/MCU_BRAKE
  @{ */
#define MB_MCU_BRAKE_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define MB_MCU_BRAKE_PORT PORTC /*!<@brief PORT device name: PORTC */
#define MB_MCU_BRAKE_PIN 16U    /*!<@brief PORTC pin index: 16 */
                                /* @} */

/*! @name PORTC13 (number 85), MB_J11[B28]/MB_Q3[1]/MB_Relay/J4[B28]/Relay
  @{ */
#define MB_RELAY_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define MB_RELAY_PORT PORTC /*!<@brief PORT device name: PORTC */
#define MB_RELAY_PIN 13U    /*!<@brief PORTC pin index: 13 */
                            /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void MB_InitMISCPins(void);

#define SOPT5_UART1RXSRC_UART_RX 0x00u /*!<@brief UART 1 receive data source select: UART1_RX pin */
#define SOPT5_UART1TXSRC_UART_TX 0x00u /*!<@brief UART 1 transmit data source select: UART1_TX pin */

/*! @name PORTC3 (number 73), U2[25]/U6[14]/RxD_sda/UART_RX_TGTMCU
  @{ */
#define BOARD_UART_RX_TGTMCU_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_UART_RX_TGTMCU_PIN 3U     /*!<@brief PORTC pin index: 3 */
                                        /* @} */

/*! @name PORTC4 (number 76), U2[24]/U6[13]/TxD_sda/UART_TX_TGTMCU
  @{ */
#define BOARD_UART_TX_TGTMCU_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_UART_TX_TGTMCU_PIN 4U     /*!<@brief PORTC pin index: 4 */
                                        /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDEBUG_UARTPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLEDsPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitOSCPins(void);

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
