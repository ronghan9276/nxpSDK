/*
 * The Clear BSD License
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 * that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************

!!GlobalInfo

product: Pins v3.0

processor: MKS22FN256xxx12

package_id: MKS22FN256VLL12

mcu_data: ksdk2_0

processor_version: 0.0.11

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

  - {pin_num: '38', peripheral: n/a, signal: disabled, pin_signal: PTA4/LLWU_P3/TPM0_CH1/I2S0_MCLK/NMI_b}

  - {pin_num: '1', peripheral: UART1, signal: TX, pin_signal: ADC0_SE4a/PTE0/CLKOUT32K/SPI1_PCS1/UART1_TX/LPI2C1_SDA/RTC_CLKOUT}

  - {pin_num: '2', peripheral: UART1, signal: RX, pin_signal: ADC0_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/LPI2C1_SCL/SPI1_SIN}

  - {pin_num: '39', peripheral: I2S0, signal: TX_BCLK, pin_signal: PTA5/USB_CLKIN/TPM0_CH2/I2S0_TX_BCLK/JTAG_TRST_b}

  - {pin_num: '42', peripheral: I2S0, signal: TXD0, pin_signal: PTA12/CAN0_TX/TPM1_CH0/I2S0_TXD0}

  - {pin_num: '43', peripheral: I2S0, signal: TX_FS, pin_signal: PTA13/LLWU_P4/CAN0_RX/TPM1_CH1/I2S0_TX_FS}

  - {pin_num: '47', peripheral: I2S0, signal: MCLK, pin_signal: PTA17/SPI0_SIN/UART0_RTS_b/I2S0_MCLK}

  - {pin_num: '45', peripheral: I2S0, signal: RXD0, pin_signal: PTA15/SPI0_SCK/UART0_RX/I2S0_RXD0, slew_rate: fast, pull_enable: enable}

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

    /* PORTA12 (pin 42) is configured as I2S0_TXD0 */
    PORT_SetPinMux(PORTA, 12U, kPORT_MuxAlt6);
    
    PORTA->PCR[12] = ((PORTA->PCR[12] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK)))

                      /* Pull Select: Internal pulldown resistor is enabled on the corresponding pin, if the
                       * corresponding PE field is set. */
                      | (uint32_t)(kPORT_PullDown)

                      /* Slew Rate Enable: Fast slew rate is configured on the corresponding pin, if the pin is
                       * configured as a digital output. */
                      | PORT_PCR_SRE(kPORT_FastSlewRate));

    /* PORTA13 (pin 43) is configured as I2S0_TX_FS */
    PORT_SetPinMux(PORTA, 13U, kPORT_MuxAlt6);

    /* PORTA17 (pin 47) is configured as I2S0_MCLK */
    PORT_SetPinMux(PORTA, 17U, kPORT_MuxAlt6);

    /* PORTA4 (pin 38) is disabled */
    PORT_SetPinMux(PORTA, 4U, kPORT_PinDisabledOrAnalog);

    /* PORTA5 (pin 39) is configured as I2S0_TX_BCLK */
    PORT_SetPinMux(PORTA, 5U, kPORT_MuxAlt6);

    /* PORTE0 (pin 1) is configured as UART1_TX */
    PORT_SetPinMux(PORTE, 0U, kPORT_MuxAlt3);

    /* PORTE1 (pin 2) is configured as UART1_RX */
    PORT_SetPinMux(PORTE, 1U, kPORT_MuxAlt3);
    
    /* PORTA15 (pin 45) is configured as I2S0_RXD0 */
    PORT_SetPinMux(PORTA, 15U, kPORT_MuxAlt6);

    PORTA->PCR[15] = ((PORTA->PCR[15] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK)))

                      /* Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin. */
                      | (uint32_t)(PORT_PCR_PE_MASK)

                      /* Slew Rate Enable: Fast slew rate is configured on the corresponding pin, if the pin is
                       * configured as a digital output. */
                      | PORT_PCR_SRE(kPORT_FastSlewRate));

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_UART1TXSRC_MASK)))

                  /* UART 1 transmit data source select: UART1_TX pin. */
                  | SIM_SOPT5_UART1TXSRC(SOPT5_UART1TXSRC_UART_TX));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************

BOARD_I2C_ConfigurePins:

- options: {coreID: core0, enableClock: 'true'}

- pin_list:

  - {pin_num: '53', peripheral: LPI2C0, signal: SCL, pin_signal: ADC0_SE8/PTB0/LLWU_P5/LPI2C0_SCL/TPM1_CH0/FXIO0_D4/UART0_RX, slew_rate: fast, open_drain: enable,

    drive_strength: low, pull_select: up, pull_enable: enable}

  - {pin_num: '54', peripheral: LPI2C0, signal: SDA, pin_signal: ADC0_SE9/PTB1/LPI2C0_SDA/TPM1_CH1/EWM_IN/FXIO0_D5/UART0_TX, slew_rate: fast, open_drain: enable,

    drive_strength: low, pull_select: up, pull_enable: enable}

 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_I2C_ConfigurePins
 *
 * END ****************************************************************************************************************/
void BOARD_I2C_ConfigurePins(void)
{
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);

    const port_pin_config_t portb0_pin53_config = {/* Internal pull-up resistor is enabled */
                                                   kPORT_PullUp,
                                                   /* Fast slew rate is configured */
                                                   kPORT_FastSlewRate,
                                                   /* Passive filter is disabled */
                                                   kPORT_PassiveFilterDisable,
                                                   /* Open drain is enabled */
                                                   kPORT_OpenDrainEnable,
                                                   /* Low drive strength is configured */
                                                   kPORT_LowDriveStrength,
                                                   /* Pin is configured as LPI2C0_SCL */
                                                   kPORT_MuxAlt2,
                                                   /* Pin Control Register fields [15:0] are not locked */
                                                   kPORT_UnlockRegister};
    /* PORTB0 (pin 53) is configured as LPI2C0_SCL */
    PORT_SetPinConfig(PORTB, 0U, &portb0_pin53_config);

    const port_pin_config_t portb1_pin54_config = {/* Internal pull-up resistor is enabled */
                                                   kPORT_PullUp,
                                                   /* Fast slew rate is configured */
                                                   kPORT_FastSlewRate,
                                                   /* Passive filter is disabled */
                                                   kPORT_PassiveFilterDisable,
                                                   /* Open drain is enabled */
                                                   kPORT_OpenDrainEnable,
                                                   /* Low drive strength is configured */
                                                   kPORT_LowDriveStrength,
                                                   /* Pin is configured as LPI2C0_SDA */
                                                   kPORT_MuxAlt2,
                                                   /* Pin Control Register fields [15:0] are not locked */
                                                   kPORT_UnlockRegister};
    /* PORTB1 (pin 54) is configured as LPI2C0_SDA */
    PORT_SetPinConfig(PORTB, 1U, &portb1_pin54_config);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
