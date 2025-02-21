/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v3.0
processor: MKV46F256xxx16
package_id: MKV46F256VLL16
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
  - {pin_num: '1', peripheral: UART1, signal: TX, pin_signal: ADCB_CH6f/PTE0/UART1_TX/XBAROUT10/XBARIN11}
  - {pin_num: '2', peripheral: UART1, signal: RX, pin_signal: ADCB_CH7f/PTE1/LLWU_P0/UART1_RX/XBAROUT11/XBARIN7}
  - {pin_num: '44', peripheral: SPI0, signal: PCS0_SS, pin_signal: CMP3_IN0/PTA14/SPI0_PCS0/UART0_TX}
  - {pin_num: '45', peripheral: SPI0, signal: SCK, pin_signal: CMP3_IN1/PTA15/SPI0_SCK/UART0_RX}
  - {pin_num: '46', peripheral: SPI0, signal: SOUT, pin_signal: CMP3_IN2/PTA16/SPI0_SOUT/UART0_CTS_b/UART0_COL_b}
  - {pin_num: '47', peripheral: SPI0, signal: SIN, pin_signal: ADCA_CH7e/PTA17/SPI0_SIN/UART0_RTS_b}
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
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    /* PORTA14 (pin 44) is configured as SPI0_PCS0 */
    PORT_SetPinMux(PORTA, 14U, kPORT_MuxAlt2);

    /* PORTA15 (pin 45) is configured as SPI0_SCK */
    PORT_SetPinMux(PORTA, 15U, kPORT_MuxAlt2);

    /* PORTA16 (pin 46) is configured as SPI0_SOUT */
    PORT_SetPinMux(PORTA, 16U, kPORT_MuxAlt2);

    /* PORTA17 (pin 47) is configured as SPI0_SIN */
    PORT_SetPinMux(PORTA, 17U, kPORT_MuxAlt2);

    /* PORTE0 (pin 1) is configured as UART1_TX */
    PORT_SetPinMux(PORTE, 0U, kPORT_MuxAlt3);

    /* PORTE1 (pin 2) is configured as UART1_RX */
    PORT_SetPinMux(PORTE, 1U, kPORT_MuxAlt3);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_UART1TXSRC_MASK | SIM_SOPT5_UART1RXSRC_MASK)))

                  /* UART 1 transmit data source select: UART1_TX pin. */
                  | SIM_SOPT5_UART1TXSRC(SOPT5_UART1TXSRC_UART_TX)

                  /* UART 1 receive data source select: UART1_RX pin. */
                  | SIM_SOPT5_UART1RXSRC(SOPT5_UART1RXSRC_UART_RX));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
