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
processor: MKL27Z64xxx4
package_id: MKL27Z64VLH4
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
  - {pin_num: '23', peripheral: LPUART0, signal: RX, pin_signal: PTA1/LPUART0_RX/TPM2_CH0}
  - {pin_num: '24', peripheral: LPUART0, signal: TX, pin_signal: PTA2/LPUART0_TX/TPM2_CH1}
  - {pin_num: '26', peripheral: GPIOA, signal: 'GPIO, 4', pin_signal: PTA4/I2C1_SDA/TPM0_CH1/NMI_b, slew_rate: slow, pull_select: up, pull_enable: enable, passive_filter: enable}
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
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);

    /* PORTA1 (pin 23) is configured as LPUART0_RX */
    PORT_SetPinMux(PORTA, 1U, kPORT_MuxAlt2);

    /* PORTA2 (pin 24) is configured as LPUART0_TX */
    PORT_SetPinMux(PORTA, 2U, kPORT_MuxAlt2);

    const port_pin_config_t porta4_pin26_config = {/* Internal pull-up resistor is enabled */
                                                   kPORT_PullUp,
                                                   /* Slow slew rate is configured */
                                                   kPORT_SlowSlewRate,
                                                   /* Passive filter is enabled */
                                                   kPORT_PassiveFilterEnable,
                                                   /* Low drive strength is configured */
                                                   kPORT_LowDriveStrength,
                                                   /* Pin is configured as PTA4 */
                                                   kPORT_MuxAsGpio};
    /* PORTA4 (pin 26) is configured as PTA4 */
    PORT_SetPinConfig(PORTA, 4U, &porta4_pin26_config);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_LPUART0TXSRC_MASK | SIM_SOPT5_LPUART0RXSRC_MASK)))

                  /* LPUART0 Transmit Data Source Select: LPUART0_TX pin. */
                  | SIM_SOPT5_LPUART0TXSRC(SOPT5_LPUART0TXSRC_LPUART_TX)

                  /* LPUART0 Receive Data Source Select: LPUART_RX pin. */
                  | SIM_SOPT5_LPUART0RXSRC(SOPT5_LPUART0RXSRC_LPUART_RX));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPUART0_InitPins:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '23', peripheral: LPUART0, signal: RX, pin_signal: PTA1/LPUART0_RX/TPM2_CH0}
  - {pin_num: '24', peripheral: LPUART0, signal: TX, pin_signal: PTA2/LPUART0_TX/TPM2_CH1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : LPUART0_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void LPUART0_InitPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);

    /* PORTA1 (pin 23) is configured as LPUART0_RX */
    PORT_SetPinMux(PORTA, 1U, kPORT_MuxAlt2);

    /* PORTA2 (pin 24) is configured as LPUART0_TX */
    PORT_SetPinMux(PORTA, 2U, kPORT_MuxAlt2);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_LPUART0TXSRC_MASK | SIM_SOPT5_LPUART0RXSRC_MASK)))

                  /* LPUART0 Transmit Data Source Select: LPUART0_TX pin. */
                  | SIM_SOPT5_LPUART0TXSRC(SOPT5_LPUART0TXSRC_LPUART_TX)

                  /* LPUART0 Receive Data Source Select: LPUART_RX pin. */
                  | SIM_SOPT5_LPUART0RXSRC(SOPT5_LPUART0RXSRC_LPUART_RX));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LPUART0_DeinitPins:
- options: {coreID: core0, enableClock: 'false'}
- pin_list:
  - {pin_num: '24', peripheral: n/a, signal: disabled, pin_signal: PTA2/LPUART0_TX/TPM2_CH1}
  - {pin_num: '23', peripheral: n/a, signal: disabled, pin_signal: PTA1/LPUART0_RX/TPM2_CH0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : LPUART0_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void LPUART0_DeinitPins(void)
{

    /* PORTA1 (pin 23) is disabled */
    PORT_SetPinMux(PORTA, 1U, kPORT_PinDisabledOrAnalog);

    /* PORTA2 (pin 24) is disabled */
    PORT_SetPinMux(PORTA, 2U, kPORT_PinDisabledOrAnalog);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
