/*
 * Copyright 2018-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _SPECIFIC_H_
#define _SPECIFIC_H_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define FLEXSPI_INST                 FLEXSPI
#define HAS_WAKEUP_PIN               (1)
#define CCM_CLPCR_BYPASS_LPM_HS_BITS (CCM_CLPCR_BYPASS_LPM_HS0_MASK | CCM_CLPCR_BYPASS_LPM_HS1_MASK)

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

void ClockSetToOverDriveRun(void);
void ClockSetToFullSpeedRun(void);
void ClockSetToLowSpeedRun(void);
void ClockSetToLowPowerRun(void);
void ClockSetToSystemIdle(void);
void ClockSetToLowPowerIdle(void);

AT_QUICKACCESS_SECTION_CODE(void SetLowPowerClockGate(void));
void PowerDownUSBPHY(void);
void ConfigUartRxPinToGpio(void);
void ReConfigUartRxPin(void);
void PeripheralEnterDozeMode(void);
void PeripheralExitDozeMode(void);
void PeripheralEnterStopMode(void);
void APP_PrintRunFrequency(int32_t run_freq_only);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* _SPECIFIC_H_ */
