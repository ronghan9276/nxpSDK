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
processor: MK28FN2M0xxx15
package_id: MK28FN2M0VMI15
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
  - {pin_num: K13, peripheral: SPI0, signal: PCS0_SS, pin_signal: PTA14/SPI0_PCS0/LPUART0_TX/TRACE_D2/FXIO0_D20/I2S0_RX_BCLK/I2S0_TXD1}
  - {pin_num: K12, peripheral: SPI0, signal: SCK, pin_signal: PTA15/SPI0_SCK/LPUART0_RX/TRACE_D1/FXIO0_D21/I2S0_RXD0}
  - {pin_num: J13, peripheral: SPI0, signal: SOUT, pin_signal: PTA16/SPI0_SOUT/LPUART0_CTS_b/TRACE_D0/FXIO0_D22/I2S0_RX_FS/I2S0_RXD1}
  - {pin_num: J12, peripheral: SPI0, signal: SIN, pin_signal: PTA17/SPI0_SIN/LPUART0_RTS_b/FXIO0_D23/I2S0_MCLK/I2S1_MCLK}
  - {pin_num: C2, peripheral: SPI2, signal: PCS0_SS, pin_signal: PTD11/LLWU_P25/SPI2_PCS0/LPUART1_CTS_b/FB_A19/FXIO0_D27}
  - {pin_num: B2, peripheral: SPI2, signal: SCK, pin_signal: PTD12/SPI2_SCK/FTM3_FLT0/FB_A20/FXIO0_D28}
  - {pin_num: B3, peripheral: SPI2, signal: SOUT, pin_signal: PTD13/SPI2_SOUT/FB_A21/FXIO0_D29}
  - {pin_num: A2, peripheral: SPI2, signal: SIN, pin_signal: PTD14/SPI2_SIN/FB_A22/FXIO0_D30}
  - {pin_num: A7, peripheral: LPUART0, signal: RX, pin_signal: PTC25/LPUART0_RX/FB_A4/SDRAM_D4/QSPI0A_SCLK}
  - {pin_num: B7, peripheral: LPUART0, signal: TX, pin_signal: PTC24/LPUART0_TX/FB_A5/SDRAM_D5/QSPI0A_DATA3}
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
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    /* PORTA14 (pin K13) is configured as SPI0_PCS0 */
    PORT_SetPinMux(PORTA, 14U, kPORT_MuxAlt2);

    /* PORTA15 (pin K12) is configured as SPI0_SCK */
    PORT_SetPinMux(PORTA, 15U, kPORT_MuxAlt2);

    /* PORTA16 (pin J13) is configured as SPI0_SOUT */
    PORT_SetPinMux(PORTA, 16U, kPORT_MuxAlt2);

    /* PORTA17 (pin J12) is configured as SPI0_SIN */
    PORT_SetPinMux(PORTA, 17U, kPORT_MuxAlt2);

    /* PORTC24 (pin B7) is configured as LPUART0_TX */
    PORT_SetPinMux(PORTC, 24U, kPORT_MuxAlt3);

    /* PORTC25 (pin A7) is configured as LPUART0_RX */
    PORT_SetPinMux(PORTC, 25U, kPORT_MuxAlt3);

    /* PORTD11 (pin C2) is configured as SPI2_PCS0 */
    PORT_SetPinMux(PORTD, 11U, kPORT_MuxAlt2);

    /* PORTD12 (pin B2) is configured as SPI2_SCK */
    PORT_SetPinMux(PORTD, 12U, kPORT_MuxAlt2);

    /* PORTD13 (pin B3) is configured as SPI2_SOUT */
    PORT_SetPinMux(PORTD, 13U, kPORT_MuxAlt2);

    /* PORTD14 (pin A2) is configured as SPI2_SIN */
    PORT_SetPinMux(PORTD, 14U, kPORT_MuxAlt2);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_LPUART0TXSRC_MASK | SIM_SOPT5_LPUART0RXSRC_MASK)))

                  /* LPUART0 transmit data source select: LPUART0_TX pin. */
                  | SIM_SOPT5_LPUART0TXSRC(SOPT5_LPUART0TXSRC_LPUART_TX)

                  /* LPUART0 receive data source select: LPUART0_RX pin. */
                  | SIM_SOPT5_LPUART0RXSRC(SOPT5_LPUART0RXSRC_LPUART_RX));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
