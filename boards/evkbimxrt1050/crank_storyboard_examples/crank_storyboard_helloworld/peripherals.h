/*
 * Copyright 2019 NXP.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "fsl_common.h"
#include "fsl_lpuart.h"
#include "fsl_clock.h"
#include "fsl_lpi2c.h"
#include "fsl_elcdif.h"
#include "fsl_gpio.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/* Definitions for BOARD_InitPeripherals functional group */
/* Definition of peripheral ID */
#define LPUART_1_PERIPHERAL LPUART1
/* Definition of the clock source frequency */
#define LPUART_1_CLOCK_SOURCE 80000000UL
/* BOARD_InitPeripherals defines for LPI2C1 */
/* Definition of peripheral ID */
#define LPI2C_1_PERIPHERAL LPI2C1
/* Definition of clock source */
#define LPI2C_1_CLOCK_FREQ 60000000UL
/* Transfer buffer size */
#define LPI2C_1_MASTER_BUFFER_SIZE 32
/* Definition of peripheral ID */
#define ELCDIF_PERIPHERAL LCDIF
/* Definition of the expected display clock frequency */
#define ELCDIF_EXPECTED_DCLK_FREQ 9210240UL
/* Definition of the panel width */
#define ELCDIF_PANEL_WIDTH 480
/* Definition of the panel height */
#define ELCDIF_PANEL_HEIGHT 272
/* Definition of the RGB buffer alignment */
#define ELCDIF_RGB_BUFFER_ALIGN 64

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern const lpuart_config_t LPUART_1_config;
extern const lpi2c_master_config_t LPI2C_1_masterConfig;
extern lpi2c_master_transfer_t LPI2C_1_masterTransfer;
extern uint8_t LPI2C_1_masterBuffer[LPI2C_1_MASTER_BUFFER_SIZE];
/* RGB mode configuration */
extern const elcdif_rgb_mode_config_t eLCDIF_rgbConfig;
/* RGB buffer */
extern uint16_t eLCDIF_Buffer[2][ELCDIF_PANEL_HEIGHT][ELCDIF_PANEL_WIDTH];

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void);

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void);

#if defined(__cplusplus)
}
#endif

#endif /* _PERIPHERALS_H_ */
