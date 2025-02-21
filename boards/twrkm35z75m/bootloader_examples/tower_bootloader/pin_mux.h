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

/*! @name PORTD1 (number 64), SW2
  @{ */
#define BOARD_INITBOOTPIN_SW2_FGPIO FGPIOD /*!<@brief FGPIO device name: FGPIOD */
#define BOARD_INITBOOTPIN_SW2_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_INITBOOTPIN_SW2_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITBOOTPIN_SW2_PIN 1U     /*!<@brief PORTD pin index: 1 */
                                         /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitBootPin(void);

/*! @name PORTI6 (number 6), UART2_RX
  @{ */
#define UART2_POLLFORACTIVITY_RX_GPIO_FGPIO FGPIOI /*!<@brief FGPIO device name: FGPIOI */
#define UART2_POLLFORACTIVITY_RX_GPIO_GPIO GPIOI /*!<@brief GPIO device name: GPIOI */
#define UART2_POLLFORACTIVITY_RX_GPIO_PORT PORTI /*!<@brief PORT device name: PORTI */
#define UART2_POLLFORACTIVITY_RX_GPIO_PIN 6U     /*!<@brief PORTI pin index: 6 */
                                                 /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void UART2_PollForActivity(void);

/*!
 * @brief
 * UART2 IrDA Select: Pad RX input PTI[6] or PTE[6] selected for RX input of UART2 and UART2 TX signal is not used
 * for modulation.
 */
#define MISC_CTL_UART2IRSEL_0b0 0x00u

/*! @name PORTI6 (number 6), UART2_RX
  @{ */
#define UART2_RX_PORT PORTI /*!<@brief PORT device name: PORTI */
#define UART2_RX_PIN 6U     /*!<@brief PORTI pin index: 6 */
                            /* @} */

/*! @name PORTI7 (number 7), UART2_TX
  @{ */
#define UART2_TX_PORT PORTI /*!<@brief PORT device name: PORTI */
#define UART2_TX_PIN 7U     /*!<@brief PORTI pin index: 7 */
                            /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void UART2_InitPins(void);

/*! @name PORTI6 (number 6), UART2_RX
  @{ */
#define UART2_RESTOREDEFAULT_RX_PORT PORTI /*!<@brief PORT device name: PORTI */
#define UART2_RESTOREDEFAULT_RX_PIN 6U     /*!<@brief PORTI pin index: 6 */
                                           /* @} */

/*! @name PORTI7 (number 7), UART2_TX
  @{ */
#define UART2_RESTOREDEFAULT_TX_PORT PORTI /*!<@brief PORT device name: PORTI */
#define UART2_RESTOREDEFAULT_TX_PIN 7U     /*!<@brief PORTI pin index: 7 */
                                           /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void UART2_RestoreDefault(void);

/*! @name PORTK7 (number 105), J25[12]/I2C0_SCL
  @{ */
#define I2C0_SCL_PORT PORTK /*!<@brief PORT device name: PORTK */
#define I2C0_SCL_PIN 7U     /*!<@brief PORTK pin index: 7 */
                            /* @} */

/*! @name PORTL0 (number 106), J25[11]/I2C0_SDA
  @{ */
#define I2C0_SDA_PORT PORTL /*!<@brief PORT device name: PORTL */
#define I2C0_SDA_PIN 0U     /*!<@brief PORTL pin index: 0 */
                            /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void I2C0_InitPins(void);

/*! @name PORTK7 (number 105), J25[12]/I2C0_SCL
  @{ */
#define I2C0_RESTOREDEFAULT_SCL_PORT PORTK /*!<@brief PORT device name: PORTK */
#define I2C0_RESTOREDEFAULT_SCL_PIN 7U     /*!<@brief PORTK pin index: 7 */
                                           /* @} */

/*! @name PORTL0 (number 106), J25[11]/I2C0_SDA
  @{ */
#define I2C0_RESTOREDEFAULT_SDA_PORT PORTL /*!<@brief PORT device name: PORTL */
#define I2C0_RESTOREDEFAULT_SDA_PIN 0U     /*!<@brief PORTL pin index: 0 */
                                           /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void I2C0_RestoreDefault(void);

/*! @name PORTF3 (number 100), J32[B46]/J23[11]/J25[16]/SPI1_PCS0
  @{ */
#define SPI1_PCS_PORT PORTF /*!<@brief PORT device name: PORTF */
#define SPI1_PCS_PIN 3U     /*!<@brief PORTF pin index: 3 */
                            /* @} */

/*! @name PORTF4 (number 101), J32[B48]/J23[12]/J25[15]/SPI1_SCK
  @{ */
#define SPI1_SCK_PORT PORTF /*!<@brief PORT device name: PORTF */
#define SPI1_SCK_PIN 4U     /*!<@brief PORTF pin index: 4 */
                            /* @} */

/*! @name PORTF5 (number 102), J32[B44]/J23[9]/J25[14]/SPI1_MISO
  @{ */
#define SPI1_MISO_PORT PORTF /*!<@brief PORT device name: PORTF */
#define SPI1_MISO_PIN 5U     /*!<@brief PORTF pin index: 5 */
                             /* @} */

/*! @name PORTF6 (number 103), J32[B45]/J23[10]/J25[13]/SPI1_MOSI
  @{ */
#define SPI1_MOSI_PORT PORTF /*!<@brief PORT device name: PORTF */
#define SPI1_MOSI_PIN 6U     /*!<@brief PORTF pin index: 6 */
                             /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void SPI1_InitPins(void);

/*! @name PORTF3 (number 100), J32[B46]/J23[11]/J25[16]/SPI1_PCS0
  @{ */
#define SPI1_RESTOREDEFAULT_PCS_PORT PORTF /*!<@brief PORT device name: PORTF */
#define SPI1_RESTOREDEFAULT_PCS_PIN 3U     /*!<@brief PORTF pin index: 3 */
                                           /* @} */

/*! @name PORTF4 (number 101), J32[B48]/J23[12]/J25[15]/SPI1_SCK
  @{ */
#define SPI1_RESTOREDEFAULT_SCK_PORT PORTF /*!<@brief PORT device name: PORTF */
#define SPI1_RESTOREDEFAULT_SCK_PIN 4U     /*!<@brief PORTF pin index: 4 */
                                           /* @} */

/*! @name PORTF5 (number 102), J32[B44]/J23[9]/J25[14]/SPI1_MISO
  @{ */
#define SPI1_RESTOREDEFAULT_MISO_PORT PORTF /*!<@brief PORT device name: PORTF */
#define SPI1_RESTOREDEFAULT_MISO_PIN 5U     /*!<@brief PORTF pin index: 5 */
                                            /* @} */

/*! @name PORTF6 (number 103), J32[B45]/J23[10]/J25[13]/SPI1_MOSI
  @{ */
#define SPI1_RESTOREDEFAULT_MOSI_PORT PORTF /*!<@brief PORT device name: PORTF */
#define SPI1_RESTOREDEFAULT_MOSI_PIN 6U     /*!<@brief PORTF pin index: 6 */
                                            /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void SPI1_RestoreDefault(void);

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
