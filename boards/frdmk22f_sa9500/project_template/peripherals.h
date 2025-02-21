/*
 * Copyright 2018 NXP.
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

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void SHIELD_InitPeripherals(void);
void SHIELD_InitBUTTONsPeripheral(void);
void SHIELD_InitLEDsPeripheral(void);
void SHIELD_InitDEBUG_UARTPeripheral(void);
void SHIELD_InitACCELPeripheral(void);
void SHIELD_InitS1_I2CPeripheral(void);
void SHIELD_InitSPIPeripheral(void);
void SHIELD_InitSDHCPeripheral(void);

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void);

#if defined(__cplusplus)
}
#endif

#endif /* _PERIPHERALS_H_ */
