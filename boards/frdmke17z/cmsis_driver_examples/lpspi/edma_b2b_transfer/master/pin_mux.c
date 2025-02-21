/*
 * Copyright 2021 NXP
 *
 * All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v9.0
processor: MKE17Z256xxx7
package_id: MKE17Z256VLL7
mcu_data: ksdk2_0
processor_version: 0.0.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '54', peripheral: LPUART0, signal: RX, pin_signal: TSI1_CH15/PTB0/LPUART0_RX/LPSPI0_PCS0/LPTMR0_ALT3/PWT_IN3}
  - {pin_num: '53', peripheral: LPUART0, signal: TX, pin_signal: TSI1_CH16/PTB1/LPUART0_TX/LPSPI0_SOUT/TCLK0}
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
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);

    /* PORTB0 (pin 54) is configured as LPUART0_RX */
    PORT_SetPinMux(PORTB, 0U, kPORT_MuxAlt2);

    /* PORTB1 (pin 53) is configured as LPUART0_TX */
    PORT_SetPinMux(PORTB, 1U, kPORT_MuxAlt2);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPSPI0_InitPins:
- options: {callFromInitBoot: 'false', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '27', peripheral: LPSPI0, signal: PCS1_HREQ, pin_signal: ADC0_SE3/TSI0_CH23/PTB5/FTM0_CH5/LPSPI0_PCS1/TRGMUX_IN0}
  - {pin_num: '48', peripheral: LPSPI0, signal: SCK, pin_signal: TSI1_CH17/PTB2/FTM1_CH0/LPSPI0_SCK/TRGMUX_IN3}
  - {pin_num: '47', peripheral: LPSPI0, signal: SIN, pin_signal: TSI1_CH18/PTB3/FTM1_CH1/LPSPI0_SIN/TRGMUX_IN2}
  - {pin_num: '28', peripheral: LPSPI0, signal: SOUT, pin_signal: ADC0_SE5/TSI0_CH24/PTB4/FTM0_CH4/LPSPI0_SOUT/TRGMUX_IN1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : LPSPI0_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void LPSPI0_InitPins(void)
{
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);

    /* PORTB2 (pin 48) is configured as LPSPI0_SCK */
    PORT_SetPinMux(PORTB, 2U, kPORT_MuxAlt3);

    /* PORTB3 (pin 47) is configured as LPSPI0_SIN */
    PORT_SetPinMux(PORTB, 3U, kPORT_MuxAlt3);

    /* PORTB4 (pin 28) is configured as LPSPI0_SOUT */
    PORT_SetPinMux(PORTB, 4U, kPORT_MuxAlt3);

    /* PORTB5 (pin 27) is configured as LPSPI0_PCS1 */
    PORT_SetPinMux(PORTB, 5U, kPORT_MuxAlt3);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPSPI0_DeinitPins:
- options: {callFromInitBoot: 'false', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '27', peripheral: ADC0, signal: 'SE, 3', pin_signal: ADC0_SE3/TSI0_CH23/PTB5/FTM0_CH5/LPSPI0_PCS1/TRGMUX_IN0}
  - {pin_num: '48', peripheral: TSI1, signal: 'CH, 17', pin_signal: TSI1_CH17/PTB2/FTM1_CH0/LPSPI0_SCK/TRGMUX_IN3}
  - {pin_num: '47', peripheral: TSI1, signal: 'CH, 18', pin_signal: TSI1_CH18/PTB3/FTM1_CH1/LPSPI0_SIN/TRGMUX_IN2}
  - {pin_num: '28', peripheral: TSI0, signal: 'CH, 24', pin_signal: ADC0_SE5/TSI0_CH24/PTB4/FTM0_CH4/LPSPI0_SOUT/TRGMUX_IN1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : LPSPI0_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void LPSPI0_DeinitPins(void)
{
    /* Clock Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);

    /* PORTB2 (pin 48) is configured as TSI1_CH17 */
    PORT_SetPinMux(PORTB, 2U, kPORT_PinDisabledOrAnalog);

    /* PORTB3 (pin 47) is configured as TSI1_CH18 */
    PORT_SetPinMux(PORTB, 3U, kPORT_PinDisabledOrAnalog);

    /* PORTB4 (pin 28) is configured as TSI0_CH24 */
    PORT_SetPinMux(PORTB, 4U, kPORT_PinDisabledOrAnalog);

    /* PORTB5 (pin 27) is configured as ADC0_SE3 */
    PORT_SetPinMux(PORTB, 5U, kPORT_PinDisabledOrAnalog);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
