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

#define IOPCTL_PIO_ANAMUX_DI 0x00u        /*!<@brief Analog mux is disabled */
#define IOPCTL_PIO_FULLDRIVE_DI 0x00u     /*!<@brief Normal drive */
#define IOPCTL_PIO_FUNC0 0x00u            /*!<@brief Selects pin function 0 */
#define IOPCTL_PIO_FUNC1 0x01u            /*!<@brief Selects pin function 1 */
#define IOPCTL_PIO_INBUF_DI 0x00u         /*!<@brief Disable input buffer function */
#define IOPCTL_PIO_INBUF_EN 0x40u         /*!<@brief Enables input buffer function */
#define IOPCTL_PIO_INV_DI 0x00u           /*!<@brief Input function is not inverted */
#define IOPCTL_PIO_PSEDRAIN_DI 0x00u      /*!<@brief Pseudo Output Drain is disabled */
#define IOPCTL_PIO_PULLDOWN_EN 0x00u      /*!<@brief Enable pull-down function */
#define IOPCTL_PIO_PULLUP_EN 0x20u        /*!<@brief Enable pull-up function */
#define IOPCTL_PIO_PUPD_DI 0x00u          /*!<@brief Disable pull-up / pull-down function */
#define IOPCTL_PIO_PUPD_EN 0x10u          /*!<@brief Enable pull-up / pull-down function */
#define IOPCTL_PIO_SLEW_RATE_NORMAL 0x00u /*!<@brief Normal mode */

/*! @name PIO2_4 (coord P6), U111A[H5]/SD0_WR_PRT_DS
  @{ */
/* Routed pin properties */
#define BOARD_INITPINS_SD0_WR_PRT_DS_PERIPHERAL GPIO                 /*!<@brief Peripheral name */
#define BOARD_INITPINS_SD0_WR_PRT_DS_SIGNAL PIO2                     /*!<@brief Signal name */
#define BOARD_INITPINS_SD0_WR_PRT_DS_CHANNEL 4                       /*!<@brief Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_SD0_WR_PRT_DS_GPIO GPIO                       /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_SD0_WR_PRT_DS_GPIO_PIN_MASK (1U << 4U)        /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_SD0_WR_PRT_DS_PORT 2U                         /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_SD0_WR_PRT_DS_PIN 4U                          /*!<@brief PORT pin number */
#define BOARD_INITPINS_SD0_WR_PRT_DS_PIN_MASK (1U << 4U)             /*!<@brief PORT pin mask */
                                                                     /* @} */

/*! @name PIO2_10 (coord N5), SD0_RESET_N
  @{ */
/* Routed pin properties */
#define BOARD_INITPINS_SD0_RESET_N_PERIPHERAL GPIO           /*!<@brief Peripheral name */
#define BOARD_INITPINS_SD0_RESET_N_SIGNAL PIO2               /*!<@brief Signal name */
#define BOARD_INITPINS_SD0_RESET_N_CHANNEL 10                /*!<@brief Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_SD0_RESET_N_GPIO GPIO                 /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_SD0_RESET_N_GPIO_PIN_MASK (1U << 10U) /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_SD0_RESET_N_PORT 2U                   /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_SD0_RESET_N_PIN 10U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_SD0_RESET_N_PIN_MASK (1U << 10U)      /*!<@brief PORT pin mask */
                                                             /* @} */

/*! @name PIO0_31 (coord D12), WL_REG_ON
  @{ */
/* Routed pin properties */
#define BOARD_INITPINS_WL_REG_ON_PERIPHERAL GPIO                    /*!<@brief Peripheral name */
#define BOARD_INITPINS_WL_REG_ON_SIGNAL PIO0                        /*!<@brief Signal name */
#define BOARD_INITPINS_WL_REG_ON_CHANNEL 31                         /*!<@brief Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_WL_REG_ON_GPIO GPIO                          /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_WL_REG_ON_GPIO_PIN_MASK (1U << 31U)          /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_WL_REG_ON_PORT 0U                            /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_WL_REG_ON_PIN 31U                            /*!<@brief PORT pin number */
#define BOARD_INITPINS_WL_REG_ON_PIN_MASK (1U << 31U)               /*!<@brief PORT pin mask */
                                                                    /* @} */

/*! @name PIO4_5 (coord P16), U24[13]
  @{ */
/* Routed pin properties */
#define BOARD_INITPINS_OSPI_RESET_PERIPHERAL GPIO                    /*!<@brief Peripheral name */
#define BOARD_INITPINS_OSPI_RESET_SIGNAL PIO4                        /*!<@brief Signal name */
#define BOARD_INITPINS_OSPI_RESET_CHANNEL 5                          /*!<@brief Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_OSPI_RESET_GPIO GPIO                          /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_OSPI_RESET_GPIO_PIN_MASK (1U << 5U)           /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_OSPI_RESET_PORT 4U                            /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_OSPI_RESET_PIN 5U                             /*!<@brief PORT pin number */
#define BOARD_INITPINS_OSPI_RESET_PIN_MASK (1U << 5U)                /*!<@brief PORT pin mask */
                                                                     /* @} */

/*! @name PIO0_14 (coord B12), Q3[2]/PWM_RED_LED
  @{ */
/* Routed pin properties */
#define BOARD_INITPINS_LED_RED_PERIPHERAL GPIO                    /*!<@brief Peripheral name */
#define BOARD_INITPINS_LED_RED_SIGNAL PIO0                        /*!<@brief Signal name */
#define BOARD_INITPINS_LED_RED_CHANNEL 14                         /*!<@brief Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_LED_RED_GPIO GPIO                          /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_LED_RED_GPIO_PIN_MASK (1U << 14U)          /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_LED_RED_PORT 0U                            /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_LED_RED_PIN 14U                            /*!<@brief PORT pin number */
#define BOARD_INITPINS_LED_RED_PIN_MASK (1U << 14U)               /*!<@brief PORT pin mask */
                                                                  /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void); /* Function assigned for the Cortex-M33 */

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
