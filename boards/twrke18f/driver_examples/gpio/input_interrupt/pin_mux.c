/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v3.0
processor: MKE18F512xxx16
package_id: MKE18F512VLL16
mcu_data: ksdk2_0
processor_version: 0.0.8
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"



/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '54', peripheral: LPUART0, signal: RX, pin_signal: ADC0_SE4/PTB0/LPUART0_RX/LPSPI0_PCS0/LPTMR0_ALT3/PWT_IN3}
  - {pin_num: '53', peripheral: LPUART0, signal: TX, pin_signal: ADC0_SE5/PTB1/LPUART0_TX/LPSPI0_SOUT/TCLK0}
  - {pin_num: '52', peripheral: GPIOC, signal: 'GPIO, 10', pin_signal: PTC10/FTM3_CH4}
  - {pin_num: '32', peripheral: GPIOD, signal: 'GPIO, 6', pin_signal: PTD6/LPUART2_RX/FTM2_FLT2}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Clock Control: 0x01u */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Clock Control: 0x01u */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Clock Control: 0x01u */
    CLOCK_EnableClock(kCLOCK_PortD);

    /* PORTB0 (pin 54) is configured as LPUART0_RX */
    PORT_SetPinMux(PORTB, 0U, kPORT_MuxAlt2);

    /* PORTB1 (pin 53) is configured as LPUART0_TX */
    PORT_SetPinMux(PORTB, 1U, kPORT_MuxAlt2);

    /* PORTC10 (pin 52) is configured as PTC10 */
    PORT_SetPinMux(PORTC, 10U, kPORT_MuxAsGpio);

    /* PORTD6 (pin 32) is configured as PTD6 */
    PORT_SetPinMux(PORTD, 6U, kPORT_MuxAsGpio);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
