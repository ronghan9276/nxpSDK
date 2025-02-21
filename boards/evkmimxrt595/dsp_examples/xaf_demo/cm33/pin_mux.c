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

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v9.0
processor: MIMXRT595S
package_id: MIMXRT595SFFOC
mcu_data: ksdk2_0
processor_version: 0.9.0
pin_labels:
- {pin_num: B11, pin_signal: PIO0_29/FC4_TXD_SCL_MISO_WS/CTIMER4_MAT1/I2S_BRIDGE_WS_OUT/SEC_PIO0_29, label: UART_TX, identifier: UART_TX}
- {pin_num: D14, pin_signal: PIO0_30/FC4_RXD_SDA_MOSI_DATA/CTIMER4_MAT2/I2S_BRIDGE_DATA_OUT/SEC_PIO0_30, label: UART_RX, identifier: UART_RX}
- {pin_num: J15, pin_signal: PIO0_7/FC1_SCK/SCT0_GPI4/SCT0_OUT4/CTIMER1_MAT0/I2S_BRIDGE_CLK_OUT/SEC_PIO0_7, label: I2S_CLK, identifier: I2S_CLK;I3S_CLK}
- {pin_num: H12, pin_signal: PIO0_8/FC1_TXD_SCL_MISO_WS/SCT0_GPI5/SCT0_OUT5/CTIMER1_MAT1/I2S_BRIDGE_WS_OUT/SEC_PIO0_8, label: I2S_TX, identifier: I3S_TX;I2S_TX}
- {pin_num: H17, pin_signal: PIO0_9/FC1_RXD_SDA_MOSI_DATA/SCT0_GPI6/SCT0_OUT6/CTIMER1_MAT2/I2S_BRIDGE_DATA_OUT/SEC_PIO0_9, label: I2S_RX, identifier: I3S_RX;I2S_RX}
- {pin_num: P2, pin_signal: PIO5_4/LCD_D9/DBI_D9/PDM_CLK01, label: DMIC_CLK, identifier: DMIC_CLK}
- {pin_num: P3, pin_signal: PIO5_8/LCD_D13/DBI_D13/PDM_DATA01, label: DMIC_DATA01, identifier: DMIC_DATA01}
- {pin_num: D16, pin_signal: PIO3_1/PDM_CLK23/PDM_DATA23/FC0_TXD_SCL_MISO_WS/I3C1_SCL, label: DMIC_DATA23, identifier: DMIC_DATA23}
- {pin_num: C16, pin_signal: PIO3_2/PDM_CLK45/PDM_DATA45/FC0_RXD_SDA_MOSI_DATA/I3C1_SDA, label: DMIC_DATA45, identifier: DMIC_DATA45}
- {pin_num: D15, pin_signal: PIO3_3/PDM_CLK67/PDM_DATA67/LCD_D23/FC0_CTS_SDA_SSEL0/I3C1_PUR/CMP0_OUT, label: DMIC_DATA67, identifier: DMIC_DATA67}
- {pin_num: C13, pin_signal: PIO0_23/FC3_RXD_SDA_MOSI_DATA/SCT0_GPI7/SCT0_OUT8/CTIMER3_MAT2/CTIMER0_MAT3/TRACEDATA_1/SEC_PIO0_23, label: I2S3, identifier: I2S3}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_iopctl.h"
#include "fsl_inputmux.h"
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
- options: {callFromInitBoot: 'true', coreID: cm33, enableClock: 'true'}
- pin_list:
  - {pin_num: B10, peripheral: I3C0, signal: SCL, pin_signal: PIO2_29/I3C0_SCL/SCT0_OUT0/CLKOUT/SMARTDMA_PIO29, pupdena: enabled, pupdsel: pullUp, ibena: enabled}
  - {pin_num: C14, peripheral: I3C0, signal: PUR, pin_signal: PIO2_31/I3C0_PUR/SCT0_OUT7/UTICK_CAP3/CTIMER_INP15/SWO/SMARTDMA_PIO31/CMP0_B}
  - {pin_num: D10, peripheral: I3C0, signal: SDA, pin_signal: PIO2_30/I3C0_SDA/SCT0_OUT3/CLKIN/CMP0_OUT/SMARTDMA_PIO30, pupdena: enabled, pupdsel: pullUp, ibena: enabled}
  - {pin_num: G16, peripheral: FLEXCOMM0, signal: TXD_SCL_MISO_WS, pin_signal: PIO0_1/FC0_TXD_SCL_MISO_WS/CTIMER0_MAT1/I2S_BRIDGE_WS_IN/SEC_PIO0_1}
  - {pin_num: H16, peripheral: FLEXCOMM0, signal: RXD_SDA_MOSI_DATA, pin_signal: PIO0_2/FC0_RXD_SDA_MOSI_DATA/CTIMER0_MAT2/I2S_BRIDGE_DATA_IN/SEC_PIO0_2, ibena: enabled}
  - {pin_num: K6, peripheral: FLEXCOMM15, signal: SDA, pin_signal: PMIC_I2C_SDA, ibena: enabled, odena: enabled}
  - {pin_num: K4, peripheral: FLEXCOMM15, signal: SCL, pin_signal: PMIC_I2C_SCL, ibena: enabled, odena: enabled}
  - {pin_num: M5, peripheral: CLKCTL, signal: MCLK, pin_signal: PIO1_10/MCLK/FREQME_GPIO_CLK/CTIMER_INP10/CLKOUT, drive: full}
  - {peripheral: FUSIONF1, signal: 'DSP_INTERRUPT, 1', pin_signal: MU_B}
  - {pin_num: R5, peripheral: USDHC0, signal: USDHC_CLK, pin_signal: PIO1_30/SD0_CLK/SCT0_GPI0, ibena: enabled}
  - {pin_num: R6, peripheral: USDHC0, signal: USDHC_CMD, pin_signal: PIO1_31/SD0_CMD/SCT0_GPI1, pupdena: enabled, pupdsel: pullUp, ibena: enabled}
  - {pin_num: U4, peripheral: USDHC0, signal: 'USDHC_DATA, 0', pin_signal: PIO2_0/SD0_D0/SCT0_GPI2/SMARTDMA_PIO0, pupdena: enabled, pupdsel: pullUp, ibena: enabled}
  - {pin_num: T4, peripheral: USDHC0, signal: 'USDHC_DATA, 1', pin_signal: PIO2_1/SD0_D1/SCT0_GPI3/SMARTDMA_PIO1, pupdena: enabled, pupdsel: pullUp, ibena: enabled}
  - {pin_num: T7, peripheral: USDHC0, signal: 'USDHC_DATA, 2', pin_signal: PIO2_2/SD0_D2/SCT0_OUT0/SMARTDMA_PIO2, pupdena: enabled, pupdsel: pullUp, ibena: enabled}
  - {pin_num: U6, peripheral: USDHC0, signal: 'USDHC_DATA, 3', pin_signal: PIO2_3/SD0_D3/SCT0_OUT1/SMARTDMA_PIO3, pupdena: enabled, pupdsel: pullUp, ibena: enabled}
  - {pin_num: P6, peripheral: GPIO, signal: 'PIO2, 4', pin_signal: PIO2_4/SD0_WR_PRT/SCT0_OUT2/SD0_DS/SMARTDMA_PIO4}
  - {pin_num: N5, peripheral: GPIO, signal: 'PIO2, 10', pin_signal: PIO2_10/SD0_RESET_N/SCT0_GPI6/CTIMER2_MAT0/FC8_SSEL2/SMARTDMA_PIO10}
  - {pin_num: T3, peripheral: USDHC0, signal: USDHC_CARD_DET, pin_signal: PIO2_9/SD0_CARD_DET_N/SCT0_OUT5/CTIMER1_MAT3/FC8_CTS_SDA_SSEL1/SMARTDMA_PIO9, pupdena: enabled,
    pupdsel: pullUp, ibena: enabled}
  - {pin_num: N15, peripheral: GPIO, signal: 'PIO4, 0', pin_signal: PIO4_0/FC7_SCK/FREQME_GPIO_CLK/CLKOUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M33 */
void BOARD_InitPins(void)
{
    /* Enables the clock for the Input Mux */
    CLOCK_EnableClock(kCLOCK_InputMux);
    /* MUB interrupt signal is selected for DSP interrupt input 1 */
    INPUTMUX_AttachSignal(INPUTMUX, 1U, kINPUTMUX_MuBToDspInterrupt);

    const uint32_t fc15_i2c_scl_config = (/* Pin is configured as I2C_SCL */
                                          IOPCTL_PIO_FUNC0 |
                                          /* Disable pull-up / pull-down function */
                                          IOPCTL_PIO_PUPD_DI |
                                          /* Enable pull-down function */
                                          IOPCTL_PIO_PULLDOWN_EN |
                                          /* Enables input buffer function */
                                          IOPCTL_PIO_INBUF_EN |
                                          /* Normal mode */
                                          IOPCTL_PIO_SLEW_RATE_NORMAL |
                                          /* Normal drive */
                                          IOPCTL_PIO_FULLDRIVE_DI |
                                          /* Analog mux is disabled */
                                          IOPCTL_PIO_ANAMUX_DI |
                                          /* Pseudo Output Drain is enabled */
                                          IOPCTL_PIO_PSEDRAIN_EN |
                                          /* Input function is not inverted */
                                          IOPCTL_PIO_INV_DI);
    /* FC15_SCL PIN (coords: K4) is configured as I2C SCL */
    IOPCTL->FC15_I2C_SCL = fc15_i2c_scl_config;

    const uint32_t fc15_i2c_sda_config = (/* Pin is configured as I2C_SDA */
                                          IOPCTL_PIO_FUNC0 |
                                          /* Disable pull-up / pull-down function */
                                          IOPCTL_PIO_PUPD_DI |
                                          /* Enable pull-down function */
                                          IOPCTL_PIO_PULLDOWN_EN |
                                          /* Enables input buffer function */
                                          IOPCTL_PIO_INBUF_EN |
                                          /* Normal mode */
                                          IOPCTL_PIO_SLEW_RATE_NORMAL |
                                          /* Normal drive */
                                          IOPCTL_PIO_FULLDRIVE_DI |
                                          /* Analog mux is disabled */
                                          IOPCTL_PIO_ANAMUX_DI |
                                          /* Pseudo Output Drain is enabled */
                                          IOPCTL_PIO_PSEDRAIN_EN |
                                          /* Input function is not inverted */
                                          IOPCTL_PIO_INV_DI);
    /* FC15_SDA PIN (coords: K6) is configured as I2C SDA */
    IOPCTL->FC15_I2C_SDA = fc15_i2c_sda_config;

    const uint32_t port0_pin1_config = (/* Pin is configured as FC0_TXD_SCL_MISO_WS */
                                        IOPCTL_PIO_FUNC1 |
                                        /* Disable pull-up / pull-down function */
                                        IOPCTL_PIO_PUPD_DI |
                                        /* Enable pull-down function */
                                        IOPCTL_PIO_PULLDOWN_EN |
                                        /* Disable input buffer function */
                                        IOPCTL_PIO_INBUF_DI |
                                        /* Normal mode */
                                        IOPCTL_PIO_SLEW_RATE_NORMAL |
                                        /* Normal drive */
                                        IOPCTL_PIO_FULLDRIVE_DI |
                                        /* Analog mux is disabled */
                                        IOPCTL_PIO_ANAMUX_DI |
                                        /* Pseudo Output Drain is disabled */
                                        IOPCTL_PIO_PSEDRAIN_DI |
                                        /* Input function is not inverted */
                                        IOPCTL_PIO_INV_DI);
    /* PORT0 PIN1 (coords: G16) is configured as FC0_TXD_SCL_MISO_WS */
    IOPCTL_PinMuxSet(IOPCTL, 0U, 1U, port0_pin1_config);

    const uint32_t port0_pin2_config = (/* Pin is configured as FC0_RXD_SDA_MOSI_DATA */
                                        IOPCTL_PIO_FUNC1 |
                                        /* Disable pull-up / pull-down function */
                                        IOPCTL_PIO_PUPD_DI |
                                        /* Enable pull-down function */
                                        IOPCTL_PIO_PULLDOWN_EN |
                                        /* Enables input buffer function */
                                        IOPCTL_PIO_INBUF_EN |
                                        /* Normal mode */
                                        IOPCTL_PIO_SLEW_RATE_NORMAL |
                                        /* Normal drive */
                                        IOPCTL_PIO_FULLDRIVE_DI |
                                        /* Analog mux is disabled */
                                        IOPCTL_PIO_ANAMUX_DI |
                                        /* Pseudo Output Drain is disabled */
                                        IOPCTL_PIO_PSEDRAIN_DI |
                                        /* Input function is not inverted */
                                        IOPCTL_PIO_INV_DI);
    /* PORT0 PIN2 (coords: H16) is configured as FC0_RXD_SDA_MOSI_DATA */
    IOPCTL_PinMuxSet(IOPCTL, 0U, 2U, port0_pin2_config);

    const uint32_t port1_pin10_config = (/* Pin is configured as MCLK */
                                         IOPCTL_PIO_FUNC1 |
                                         /* Disable pull-up / pull-down function */
                                         IOPCTL_PIO_PUPD_DI |
                                         /* Enable pull-down function */
                                         IOPCTL_PIO_PULLDOWN_EN |
                                         /* Disable input buffer function */
                                         IOPCTL_PIO_INBUF_DI |
                                         /* Normal mode */
                                         IOPCTL_PIO_SLEW_RATE_NORMAL |
                                         /* Full drive enable */
                                         IOPCTL_PIO_FULLDRIVE_EN |
                                         /* Analog mux is disabled */
                                         IOPCTL_PIO_ANAMUX_DI |
                                         /* Pseudo Output Drain is disabled */
                                         IOPCTL_PIO_PSEDRAIN_DI |
                                         /* Input function is not inverted */
                                         IOPCTL_PIO_INV_DI);
    /* PORT1 PIN10 (coords: M5) is configured as MCLK */
    IOPCTL_PinMuxSet(IOPCTL, 1U, 10U, port1_pin10_config);

    const uint32_t port1_pin30_config = (/* Pin is configured as SD0_CLK */
                                         IOPCTL_PIO_FUNC1 |
                                         /* Disable pull-up / pull-down function */
                                         IOPCTL_PIO_PUPD_DI |
                                         /* Enable pull-down function */
                                         IOPCTL_PIO_PULLDOWN_EN |
                                         /* Enables input buffer function */
                                         IOPCTL_PIO_INBUF_EN |
                                         /* Normal mode */
                                         IOPCTL_PIO_SLEW_RATE_NORMAL |
                                         /* Normal drive */
                                         IOPCTL_PIO_FULLDRIVE_DI |
                                         /* Analog mux is disabled */
                                         IOPCTL_PIO_ANAMUX_DI |
                                         /* Pseudo Output Drain is disabled */
                                         IOPCTL_PIO_PSEDRAIN_DI |
                                         /* Input function is not inverted */
                                         IOPCTL_PIO_INV_DI);
    /* PORT1 PIN30 (coords: R5) is configured as SD0_CLK */
    IOPCTL_PinMuxSet(IOPCTL, 1U, 30U, port1_pin30_config);

    const uint32_t port1_pin31_config = (/* Pin is configured as SD0_CMD */
                                         IOPCTL_PIO_FUNC1 |
                                         /* Enable pull-up / pull-down function */
                                         IOPCTL_PIO_PUPD_EN |
                                         /* Enable pull-up function */
                                         IOPCTL_PIO_PULLUP_EN |
                                         /* Enables input buffer function */
                                         IOPCTL_PIO_INBUF_EN |
                                         /* Normal mode */
                                         IOPCTL_PIO_SLEW_RATE_NORMAL |
                                         /* Normal drive */
                                         IOPCTL_PIO_FULLDRIVE_DI |
                                         /* Analog mux is disabled */
                                         IOPCTL_PIO_ANAMUX_DI |
                                         /* Pseudo Output Drain is disabled */
                                         IOPCTL_PIO_PSEDRAIN_DI |
                                         /* Input function is not inverted */
                                         IOPCTL_PIO_INV_DI);
    /* PORT1 PIN31 (coords: R6) is configured as SD0_CMD */
    IOPCTL_PinMuxSet(IOPCTL, 1U, 31U, port1_pin31_config);

    const uint32_t port2_pin0_config = (/* Pin is configured as SD0_D0 */
                                        IOPCTL_PIO_FUNC1 |
                                        /* Enable pull-up / pull-down function */
                                        IOPCTL_PIO_PUPD_EN |
                                        /* Enable pull-up function */
                                        IOPCTL_PIO_PULLUP_EN |
                                        /* Enables input buffer function */
                                        IOPCTL_PIO_INBUF_EN |
                                        /* Normal mode */
                                        IOPCTL_PIO_SLEW_RATE_NORMAL |
                                        /* Normal drive */
                                        IOPCTL_PIO_FULLDRIVE_DI |
                                        /* Analog mux is disabled */
                                        IOPCTL_PIO_ANAMUX_DI |
                                        /* Pseudo Output Drain is disabled */
                                        IOPCTL_PIO_PSEDRAIN_DI |
                                        /* Input function is not inverted */
                                        IOPCTL_PIO_INV_DI);
    /* PORT2 PIN0 (coords: U4) is configured as SD0_D0 */
    IOPCTL_PinMuxSet(IOPCTL, 2U, 0U, port2_pin0_config);

    const uint32_t port2_pin1_config = (/* Pin is configured as SD0_D1 */
                                        IOPCTL_PIO_FUNC1 |
                                        /* Enable pull-up / pull-down function */
                                        IOPCTL_PIO_PUPD_EN |
                                        /* Enable pull-up function */
                                        IOPCTL_PIO_PULLUP_EN |
                                        /* Enables input buffer function */
                                        IOPCTL_PIO_INBUF_EN |
                                        /* Normal mode */
                                        IOPCTL_PIO_SLEW_RATE_NORMAL |
                                        /* Normal drive */
                                        IOPCTL_PIO_FULLDRIVE_DI |
                                        /* Analog mux is disabled */
                                        IOPCTL_PIO_ANAMUX_DI |
                                        /* Pseudo Output Drain is disabled */
                                        IOPCTL_PIO_PSEDRAIN_DI |
                                        /* Input function is not inverted */
                                        IOPCTL_PIO_INV_DI);
    /* PORT2 PIN1 (coords: T4) is configured as SD0_D1 */
    IOPCTL_PinMuxSet(IOPCTL, 2U, 1U, port2_pin1_config);

    const uint32_t port2_pin10_config = (/* Pin is configured as PIO2_10 */
                                         IOPCTL_PIO_FUNC0 |
                                         /* Disable pull-up / pull-down function */
                                         IOPCTL_PIO_PUPD_DI |
                                         /* Enable pull-down function */
                                         IOPCTL_PIO_PULLDOWN_EN |
                                         /* Disable input buffer function */
                                         IOPCTL_PIO_INBUF_DI |
                                         /* Normal mode */
                                         IOPCTL_PIO_SLEW_RATE_NORMAL |
                                         /* Normal drive */
                                         IOPCTL_PIO_FULLDRIVE_DI |
                                         /* Analog mux is disabled */
                                         IOPCTL_PIO_ANAMUX_DI |
                                         /* Pseudo Output Drain is disabled */
                                         IOPCTL_PIO_PSEDRAIN_DI |
                                         /* Input function is not inverted */
                                         IOPCTL_PIO_INV_DI);
    /* PORT2 PIN10 (coords: N5) is configured as PIO2_10 */
    IOPCTL_PinMuxSet(IOPCTL, 2U, 10U, port2_pin10_config);

    const uint32_t port2_pin2_config = (/* Pin is configured as SD0_D2 */
                                        IOPCTL_PIO_FUNC1 |
                                        /* Enable pull-up / pull-down function */
                                        IOPCTL_PIO_PUPD_EN |
                                        /* Enable pull-up function */
                                        IOPCTL_PIO_PULLUP_EN |
                                        /* Enables input buffer function */
                                        IOPCTL_PIO_INBUF_EN |
                                        /* Normal mode */
                                        IOPCTL_PIO_SLEW_RATE_NORMAL |
                                        /* Normal drive */
                                        IOPCTL_PIO_FULLDRIVE_DI |
                                        /* Analog mux is disabled */
                                        IOPCTL_PIO_ANAMUX_DI |
                                        /* Pseudo Output Drain is disabled */
                                        IOPCTL_PIO_PSEDRAIN_DI |
                                        /* Input function is not inverted */
                                        IOPCTL_PIO_INV_DI);
    /* PORT2 PIN2 (coords: T7) is configured as SD0_D2 */
    IOPCTL_PinMuxSet(IOPCTL, 2U, 2U, port2_pin2_config);

    const uint32_t port2_pin29_config = (/* Pin is configured as I3C0_SCL */
                                         IOPCTL_PIO_FUNC1 |
                                         /* Enable pull-up / pull-down function */
                                         IOPCTL_PIO_PUPD_EN |
                                         /* Enable pull-up function */
                                         IOPCTL_PIO_PULLUP_EN |
                                         /* Enables input buffer function */
                                         IOPCTL_PIO_INBUF_EN |
                                         /* Normal mode */
                                         IOPCTL_PIO_SLEW_RATE_NORMAL |
                                         /* Normal drive */
                                         IOPCTL_PIO_FULLDRIVE_DI |
                                         /* Analog mux is disabled */
                                         IOPCTL_PIO_ANAMUX_DI |
                                         /* Pseudo Output Drain is disabled */
                                         IOPCTL_PIO_PSEDRAIN_DI |
                                         /* Input function is not inverted */
                                         IOPCTL_PIO_INV_DI);
    /* PORT2 PIN29 (coords: B10) is configured as I3C0_SCL */
    IOPCTL_PinMuxSet(IOPCTL, 2U, 29U, port2_pin29_config);

    const uint32_t port2_pin3_config = (/* Pin is configured as SD0_D3 */
                                        IOPCTL_PIO_FUNC1 |
                                        /* Enable pull-up / pull-down function */
                                        IOPCTL_PIO_PUPD_EN |
                                        /* Enable pull-up function */
                                        IOPCTL_PIO_PULLUP_EN |
                                        /* Enables input buffer function */
                                        IOPCTL_PIO_INBUF_EN |
                                        /* Normal mode */
                                        IOPCTL_PIO_SLEW_RATE_NORMAL |
                                        /* Normal drive */
                                        IOPCTL_PIO_FULLDRIVE_DI |
                                        /* Analog mux is disabled */
                                        IOPCTL_PIO_ANAMUX_DI |
                                        /* Pseudo Output Drain is disabled */
                                        IOPCTL_PIO_PSEDRAIN_DI |
                                        /* Input function is not inverted */
                                        IOPCTL_PIO_INV_DI);
    /* PORT2 PIN3 (coords: U6) is configured as SD0_D3 */
    IOPCTL_PinMuxSet(IOPCTL, 2U, 3U, port2_pin3_config);

    const uint32_t port2_pin30_config = (/* Pin is configured as I3C0_SDA */
                                         IOPCTL_PIO_FUNC1 |
                                         /* Enable pull-up / pull-down function */
                                         IOPCTL_PIO_PUPD_EN |
                                         /* Enable pull-up function */
                                         IOPCTL_PIO_PULLUP_EN |
                                         /* Enables input buffer function */
                                         IOPCTL_PIO_INBUF_EN |
                                         /* Normal mode */
                                         IOPCTL_PIO_SLEW_RATE_NORMAL |
                                         /* Normal drive */
                                         IOPCTL_PIO_FULLDRIVE_DI |
                                         /* Analog mux is disabled */
                                         IOPCTL_PIO_ANAMUX_DI |
                                         /* Pseudo Output Drain is disabled */
                                         IOPCTL_PIO_PSEDRAIN_DI |
                                         /* Input function is not inverted */
                                         IOPCTL_PIO_INV_DI);
    /* PORT2 PIN30 (coords: D10) is configured as I3C0_SDA */
    IOPCTL_PinMuxSet(IOPCTL, 2U, 30U, port2_pin30_config);

    const uint32_t port2_pin31_config = (/* Pin is configured as I3C0_PUR */
                                         IOPCTL_PIO_FUNC1 |
                                         /* Disable pull-up / pull-down function */
                                         IOPCTL_PIO_PUPD_DI |
                                         /* Enable pull-down function */
                                         IOPCTL_PIO_PULLDOWN_EN |
                                         /* Disable input buffer function */
                                         IOPCTL_PIO_INBUF_DI |
                                         /* Normal mode */
                                         IOPCTL_PIO_SLEW_RATE_NORMAL |
                                         /* Normal drive */
                                         IOPCTL_PIO_FULLDRIVE_DI |
                                         /* Analog mux is disabled */
                                         IOPCTL_PIO_ANAMUX_DI |
                                         /* Pseudo Output Drain is disabled */
                                         IOPCTL_PIO_PSEDRAIN_DI |
                                         /* Input function is not inverted */
                                         IOPCTL_PIO_INV_DI);
    /* PORT2 PIN31 (coords: C14) is configured as I3C0_PUR */
    IOPCTL_PinMuxSet(IOPCTL, 2U, 31U, port2_pin31_config);

    const uint32_t port2_pin4_config = (/* Pin is configured as PIO2_4 */
                                        IOPCTL_PIO_FUNC0 |
                                        /* Disable pull-up / pull-down function */
                                        IOPCTL_PIO_PUPD_DI |
                                        /* Enable pull-down function */
                                        IOPCTL_PIO_PULLDOWN_EN |
                                        /* Disable input buffer function */
                                        IOPCTL_PIO_INBUF_DI |
                                        /* Normal mode */
                                        IOPCTL_PIO_SLEW_RATE_NORMAL |
                                        /* Normal drive */
                                        IOPCTL_PIO_FULLDRIVE_DI |
                                        /* Analog mux is disabled */
                                        IOPCTL_PIO_ANAMUX_DI |
                                        /* Pseudo Output Drain is disabled */
                                        IOPCTL_PIO_PSEDRAIN_DI |
                                        /* Input function is not inverted */
                                        IOPCTL_PIO_INV_DI);
    /* PORT2 PIN4 (coords: P6) is configured as PIO2_4 */
    IOPCTL_PinMuxSet(IOPCTL, 2U, 4U, port2_pin4_config);

    const uint32_t port2_pin9_config = (/* Pin is configured as SD0_CARD_DET_N */
                                        IOPCTL_PIO_FUNC1 |
                                        /* Enable pull-up / pull-down function */
                                        IOPCTL_PIO_PUPD_EN |
                                        /* Enable pull-up function */
                                        IOPCTL_PIO_PULLUP_EN |
                                        /* Enables input buffer function */
                                        IOPCTL_PIO_INBUF_EN |
                                        /* Normal mode */
                                        IOPCTL_PIO_SLEW_RATE_NORMAL |
                                        /* Normal drive */
                                        IOPCTL_PIO_FULLDRIVE_DI |
                                        /* Analog mux is disabled */
                                        IOPCTL_PIO_ANAMUX_DI |
                                        /* Pseudo Output Drain is disabled */
                                        IOPCTL_PIO_PSEDRAIN_DI |
                                        /* Input function is not inverted */
                                        IOPCTL_PIO_INV_DI);
    /* PORT2 PIN9 (coords: T3) is configured as SD0_CARD_DET_N */
    IOPCTL_PinMuxSet(IOPCTL, 2U, 9U, port2_pin9_config);

    const uint32_t port4_pin0_config = (/* Pin is configured as PIO4_0 */
                                        IOPCTL_PIO_FUNC0 |
                                        /* Disable pull-up / pull-down function */
                                        IOPCTL_PIO_PUPD_DI |
                                        /* Enable pull-down function */
                                        IOPCTL_PIO_PULLDOWN_EN |
                                        /* Disable input buffer function */
                                        IOPCTL_PIO_INBUF_DI |
                                        /* Normal mode */
                                        IOPCTL_PIO_SLEW_RATE_NORMAL |
                                        /* Normal drive */
                                        IOPCTL_PIO_FULLDRIVE_DI |
                                        /* Analog mux is disabled */
                                        IOPCTL_PIO_ANAMUX_DI |
                                        /* Pseudo Output Drain is disabled */
                                        IOPCTL_PIO_PSEDRAIN_DI |
                                        /* Input function is not inverted */
                                        IOPCTL_PIO_INV_DI);
    /* PORT4 PIN0 (coords: N15) is configured as PIO4_0 */
    IOPCTL_PinMuxSet(IOPCTL, 4U, 0U, port4_pin0_config);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
