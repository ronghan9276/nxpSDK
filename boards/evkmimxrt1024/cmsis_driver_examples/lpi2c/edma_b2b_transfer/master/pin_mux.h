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

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/* Define the flexspi macro. Note that it can't be modified here */
#define IOMUXC_GPIO_AD_B1_00_FLEXSPI_A_DATA03 0x401F80FCU, 0x1U, 0x401F8374U, 0x1U, 0x401F8270U
#define IOMUXC_GPIO_AD_B1_01_FLEXSPI_A_SCLK 0x401F8100U, 0x1U, 0x401F8378U, 0x1U, 0x401F8274U
#define IOMUXC_GPIO_AD_B1_02_FLEXSPI_A_DATA00 0x401F8104U, 0x1U, 0x401F8368U, 0x1U, 0x401F8278U
#define IOMUXC_GPIO_AD_B1_03_FLEXSPI_A_DATA02 0x401F8108U, 0x1U, 0x401F8370U, 0x1U, 0x401F827CU
#define IOMUXC_GPIO_AD_B1_04_FLEXSPI_A_DATA01 0x401F810CU, 0x1U, 0x401F836CU, 0x1U, 0x401F8280U
#define IOMUXC_GPIO_AD_B1_05_FLEXSPI_A_SS0_B 0x401F8110U, 0x1U, 0, 0, 0x401F8284U

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
  kPIN_MUX_DirectionInput = 0U,         /* Input direction */
  kPIN_MUX_DirectionOutput = 1U,        /* Output direction */
  kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;

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


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void LPI2C1_InitPins(void);


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void LPI2C1_DeinitPins(void);

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
