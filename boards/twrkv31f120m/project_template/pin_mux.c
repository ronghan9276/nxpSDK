/*
 * Copyright 2018-2019 NXP.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v5.0
processor: MKV31F512xxx12
package_id: MKV31F512VLL12
mcu_data: ksdk2_0
processor_version: 0.0.18
board: TWR-KV31F120M
pin_labels:
- {pin_num: '9', pin_signal: VSS9, label: GND}
- {pin_num: '25', pin_signal: VSSA, label: GND}
- {pin_num: '29', pin_signal: VSS29, label: GND}
- {pin_num: '41', pin_signal: VSS41, label: GND}
- {pin_num: '49', pin_signal: VSS49, label: GND}
- {pin_num: '60', pin_signal: VSS60, label: GND}
- {pin_num: '74', pin_signal: VSS74, label: GND}
- {pin_num: '88', pin_signal: VSS88, label: GND}
- {pin_num: '8', pin_signal: VDD8, label: 'J13[2]/MCU_VDD'}
- {pin_num: '22', pin_signal: VDDA, label: 'J14[2]/VDDA'}
- {pin_num: '30', pin_signal: VDD30, label: 'J13[2]/MCU_VDD'}
- {pin_num: '40', pin_signal: VDD40, label: 'J13[2]/MCU_VDD'}
- {pin_num: '48', pin_signal: VDD48, label: 'J13[2]/MCU_VDD'}
- {pin_num: '61', pin_signal: VDD61, label: 'J13[2]/MCU_VDD'}
- {pin_num: '75', pin_signal: VDD75, label: 'J13[2]/MCU_VDD'}
- {pin_num: '89', pin_signal: VDD89, label: 'J13[2]/MCU_VDD'}
- {pin_num: '24', pin_signal: VREFL, label: GND}
- {pin_num: '23', pin_signal: VREFH, label: 'J14[2]/VREFH'}
- {pin_num: '1', pin_signal: ADC1_SE4a/PTE0/CLKOUT32K/SPI1_PCS1/UART1_TX/I2C1_SDA, label: 'J6[18]/J17[3]/D4/LED2/UART1_TX', identifier: LED_RED}
- {pin_num: '2', pin_signal: ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/I2C1_SCL/SPI1_SIN, label: 'J6[17]/J17[1]/J16[B10]/D3/LED1/UART1_RX/SPI1_SOUT', identifier: LED_YELLOW}
- {pin_num: '3', pin_signal: ADC1_SE6a/PTE2/LLWU_P1/SPI1_SCK/UART1_CTS_b, label: 'J16[B27]/ADC1_SE6a', identifier: ADC1_SE6a}
- {pin_num: '4', pin_signal: ADC1_SE7a/PTE3/SPI1_SIN/UART1_RTS_b/SPI1_SOUT, label: 'J16[B11]/SPI1_SIN', identifier: SPI1_SIN}
- {pin_num: '5', pin_signal: PTE4/LLWU_P2/SPI1_PCS0/LPUART0_TX, label: 'J16[A42]/J500[40]/LPUART0_TX', identifier: LPUART0_TX}
- {pin_num: '6', pin_signal: PTE5/SPI1_PCS2/LPUART0_RX/FTM3_CH0, label: 'J16[A41]/J500[17]/LPUART0_RX/FTM3_CH0', identifier: LPUART0_RX}
- {pin_num: '7', pin_signal: PTE6/SPI1_PCS3/LPUART0_CTS_b/FTM3_CH1, label: 'J16[B33]/J500[19]/FTM3_CH1', identifier: FTM3_CH1}
- {pin_num: '10', pin_signal: ADC0_SE4a/PTE16/SPI0_PCS0/UART2_TX/FTM_CLKIN0/FTM0_FLT3, label: 'J16[B46]/J500[6]/J500[33]/SPI0_PCS0'}
- {pin_num: '11', pin_signal: ADC0_SE5a/PTE17/SPI0_SCK/UART2_RX/FTM_CLKIN1/LPTMR0_ALT3, label: 'J6[12]/J16[B48]/SPI0_SCK', identifier: TWRPI_SPI0_SCK}
- {pin_num: '12', pin_signal: ADC0_SE6a/PTE18/SPI0_SOUT/UART2_CTS_b/I2C0_SDA, label: 'J6[10]/J16[B45]/SPI0_SOUT', identifier: TWRPI_SPI0_SOUT}
- {pin_num: '13', pin_signal: ADC0_SE7a/PTE19/SPI0_SIN/UART2_RTS_b/I2C0_SCL, label: 'J6[9]/J16[B44]/SPI0_SIN', identifier: TWRPI_SPI0_SIN}
- {pin_num: '14', pin_signal: ADC0_DP1, label: 'J16[A27]'}
- {pin_num: '15', pin_signal: ADC0_DM1, label: NC}
- {pin_num: '16', pin_signal: ADC1_DP1/ADC0_DP2, label: NC}
- {pin_num: '17', pin_signal: ADC1_DM1/ADC0_DM2, label: NC}
- {pin_num: '18', pin_signal: ADC0_DP0/ADC1_DP3, label: 'J500[22]/ADC0_DP0/ADC1_DP3'}
- {pin_num: '19', pin_signal: ADC0_DM0/ADC1_DM3, label: 'J7[8]/J500[26]/ADC0_DM0/ADC1_DM3', identifier: TWRPI_ADC0}
- {pin_num: '20', pin_signal: ADC1_DP0/ADC0_DP3, label: 'J500[20]/J16[A29]/ADC1_DP0/ADC0_DP3'}
- {pin_num: '21', pin_signal: ADC1_DM0/ADC0_DM3, label: 'J7[17]/J500[35]/ADC1_DM0/ADC0_DM3', identifier: TWRPI_ID0}
- {pin_num: '26', pin_signal: VREF_OUT/CMP1_IN5/CMP0_IN5/ADC1_SE18, label: 'J7[12]/J500[39]/ADC1_SE18', identifier: ADC1_SE18}
- {pin_num: '27', pin_signal: DAC0_OUT/CMP1_IN3/ADC0_SE23, label: 'J16[A32]/DAC0_OUT/ADC0_SE23/POT_5K', identifier: POT_5K}
- {pin_num: '28', pin_signal: DAC1_OUT/CMP0_IN4/ADC1_SE23, label: 'J16[B32]/J7[9]/J500[28]/DAC1_OUT/ADC1_SE23', identifier: TWRPI_ADC1}
- {pin_num: '31', pin_signal: ADC0_SE17/PTE24/FTM0_CH0/I2C0_SCL/EWM_OUT_b, label: 'J10[2]/U1[9]/INT2', identifier: ACCEL_INT2}
- {pin_num: '32', pin_signal: ADC0_SE18/PTE25/FTM0_CH1/I2C0_SDA/EWM_IN, label: SW4, identifier: SW4}
- {pin_num: '33', pin_signal: PTE26/CLKOUT32K, label: 'J16[B25]/RTC_CLKOUT', identifier: RTC_CLKOUT}
- {pin_num: '34', pin_signal: PTA0/UART0_CTS_b/FTM0_CH5/EWM_IN/JTAG_TCLK/SWD_CLK/EZP_CLK, label: 'J19[4]/J500[29]/JTAG_TCLK/EZP_CLK', identifier: SWD_CLK_KV3x}
- {pin_num: '35', pin_signal: PTA1/UART0_RX/FTM0_CH6/CMP0_OUT/FTM2_QD_PHA/FTM1_CH1/JTAG_TDI/EZP_DI, label: 'J19[8]/J500[25]/JTAG_TDI/EZP_DI'}
- {pin_num: '36', pin_signal: PTA2/UART0_TX/FTM0_CH7/CMP1_OUT/FTM2_QD_PHB/FTM1_CH0/JTAG_TDO/TRACE_SWO/EZP_DO, label: 'J19[6]/J500[27]/JTAG_TDO/EZP_DO'}
- {pin_num: '37', pin_signal: PTA3/UART0_RTS_b/FTM0_CH0/FTM2_FLT0/EWM_OUT_b/JTAG_TMS/SWD_DIO, label: 'J19[2]/J500[31]/JTAG_TMS/EZP_DI', identifier: SWD_DIO_TGTMCU}
- {pin_num: '38', pin_signal: PTA4/LLWU_P3/FTM0_CH1/FTM0_FLT3/NMI_b/EZP_CS_b, label: 'J500[14]/SW3/NMI', identifier: SW3}
- {pin_num: '39', pin_signal: PTA5/FTM0_CH2/JTAG_TRST_b, label: 'J16[B52]'}
- {pin_num: '42', pin_signal: PTA12/FTM1_CH0/FTM1_QD_PHA, label: 'J16[A34]/J500[15]/FTM1_CH0/FTM1_QD_PHA'}
- {pin_num: '43', pin_signal: PTA13/LLWU_P4/FTM1_CH1/FTM1_QD_PHB, label: 'J16[A33]/J500[13]/FTM1_CH1/FTM1_QD_PHB'}
- {pin_num: '44', pin_signal: PTA14/SPI0_PCS0/UART0_TX, label: 'J16[A51]'}
- {pin_num: '45', pin_signal: PTA15/SPI0_SCK/UART0_RX, label: NC}
- {pin_num: '46', pin_signal: PTA16/SPI0_SOUT/UART0_CTS_b, label: 'J16[A9]'}
- {pin_num: '47', pin_signal: ADC1_SE17/PTA17/SPI0_SIN/UART0_RTS_b, label: NC}
- {pin_num: '51', pin_signal: XTAL0/PTA19/FTM0_FLT0/FTM1_FLT0/FTM_CLKIN1/LPTMR0_ALT1, label: 'X501[3]/XTAL0', identifier: XTAL0}
- {pin_num: '50', pin_signal: EXTAL0/PTA18/FTM0_FLT2/FTM_CLKIN0, label: 'X501[1]/EXTAL0/CLKIN0', identifier: EXTAL0}
- {pin_num: '52', pin_signal: RESET_b, label: 'J7[20]J19[10]/J500[4]/J16[A62]/U511[4]/RESET'}
- {pin_num: '53', pin_signal: ADC0_SE8/ADC1_SE8/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/FTM1_QD_PHA/UART0_RX, label: 'J500[18]/ADC0_SE8/ADC1_SE8'}
- {pin_num: '54', pin_signal: ADC0_SE9/ADC1_SE9/PTB1/I2C0_SDA/FTM1_CH1/FTM0_FLT2/EWM_IN/FTM1_QD_PHB/UART0_TX, label: 'J16[B28]/J500[12]/ADC0_SE9/ADC1_SE9'}
- {pin_num: '55', pin_signal: ADC0_SE12/PTB2/I2C0_SCL/UART0_RTS_b/FTM0_FLT1/FTM0_FLT3, label: 'J16[B21]/J500[38]/UART0_RTS'}
- {pin_num: '56', pin_signal: ADC0_SE13/PTB3/I2C0_SDA/UART0_CTS_b/FTM0_FLT0, label: 'J16[B30]/J500[10]/ADC0_SE13', identifier: ADC0_SE13}
- {pin_num: '57', pin_signal: PTB9/SPI1_PCS1/LPUART0_CTS_b/FB_AD20, label: 'J16[B8]/SPI1_PCS1', identifier: SPI1_PCS1}
- {pin_num: '58', pin_signal: ADC1_SE14/PTB10/SPI1_PCS0/LPUART0_RX/FB_AD19/FTM0_FLT1, label: 'J16[B9]/SPI1_PCS0', identifier: SPI1_PCS0}
- {pin_num: '59', pin_signal: ADC1_SE15/PTB11/SPI1_SCK/LPUART0_TX/FB_AD18/FTM0_FLT2, label: 'J16[B7]/SPI1_SCK', identifier: SPI1_SCK}
- {pin_num: '62', pin_signal: PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/EWM_IN, label: 'J500[7]/J22[2]/UART0_RX_TGTMCU', identifier: DEBUG_UART_RX}
- {pin_num: '63', pin_signal: PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/EWM_OUT_b, label: 'J500[5]/J23[2]/UART0_TX_TGTMCU', identifier: DEBUG_UART_TX}
- {pin_num: '64', pin_signal: PTB18/FTM2_CH0/FB_AD15/FTM2_QD_PHA, label: 'J16[B61]/J500[37]'}
- {pin_num: '65', pin_signal: PTB19/FTM2_CH1/FB_OE_b/FTM2_QD_PHB, label: 'J17[5]/D6/LED3', identifier: LED_ORANGE}
- {pin_num: '66', pin_signal: PTB20/FB_AD31/CMP0_OUT, label: 'J16[A50]'}
- {pin_num: '67', pin_signal: PTB21/FB_AD30/CMP1_OUT, label: 'J16[A10]'}
- {pin_num: '68', pin_signal: PTB22/FB_AD29, label: 'J16[A11]'}
- {pin_num: '69', pin_signal: PTB23/SPI0_PCS5/FB_AD28, label: 'J16[B56]'}
- {pin_num: '70', pin_signal: ADC0_SE14/PTC0/SPI0_PCS4/PDB0_EXTRG/FB_AD14/FTM0_FLT1/SPI0_PCS0, label: 'J16[B22]'}
- {pin_num: '71', pin_signal: ADC0_SE15/PTC1/LLWU_P6/SPI0_PCS3/UART1_RTS_b/FTM0_CH0/FB_AD13/LPUART0_RTS_b, label: 'J16[A40]/J500[9]/FTM0_CH0', identifier: FTM0_CH0}
- {pin_num: '72', pin_signal: ADC0_SE4b/CMP1_IN0/PTC2/SPI0_PCS2/UART1_CTS_b/FTM0_CH1/FB_AD12/LPUART0_CTS_b, label: 'J16[A39]/J500[11]/FTM0_CH1', identifier: FTM0_CH1}
- {pin_num: '73', pin_signal: CMP1_IN1/PTC3/LLWU_P7/SPI0_PCS1/UART1_RX/FTM0_CH2/CLKOUT/LPUART0_RX, label: 'J6[11]/J16[B47]/SPI0_PCS1', identifier: TWRPI_SPI0_PCS0}
- {pin_num: '76', pin_signal: PTC4/LLWU_P8/SPI0_PCS0/UART1_TX/FTM0_CH3/FB_AD11/CMP1_OUT/LPUART0_TX, label: 'J16[A37]/J500[32]/FTM0_CH3', identifier: FTM0_CH3}
- {pin_num: '77', pin_signal: PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/FB_AD10/CMP0_OUT/FTM0_CH2, label: 'J16[A38]/J500[30]/FTM0_CH2', identifier: FTM0_CH2}
- {pin_num: '78', pin_signal: CMP0_IN0/PTC6/LLWU_P10/SPI0_SOUT/PDB0_EXTRG/FB_AD9/I2C0_SCL, label: SW1/LLWU_P10, identifier: SW1}
- {pin_num: '79', pin_signal: CMP0_IN1/PTC7/SPI0_SIN/FB_AD8/I2C0_SDA, label: 'J6[19]/J16[A63]', identifier: TWRPI_GPIO4}
- {pin_num: '80', pin_signal: ADC1_SE4b/CMP0_IN2/PTC8/FTM3_CH4/FB_AD7, label: 'J7[18]/ADC1_SE4b', identifier: TWRPI_ID1}
- {pin_num: '81', pin_signal: ADC1_SE5b/CMP0_IN3/PTC9/FTM3_CH5/FB_AD6/FTM2_FLT0, label: 'J16[B62]'}
- {pin_num: '82', pin_signal: ADC1_SE6b/PTC10/I2C1_SCL/FTM3_CH6/FB_AD5, label: 'J16[B29]/J500[2]/ADC1_SE6b'}
- {pin_num: '83', pin_signal: ADC1_SE7b/PTC11/LLWU_P11/I2C1_SDA/FTM3_CH7/FB_RW_b, label: SW2/LLWU_P11, identifier: SW2}
- {pin_num: '84', pin_signal: PTC12/FB_AD27/FTM3_FLT0, label: 'J16[B59]'}
- {pin_num: '85', pin_signal: PTC13/FB_AD26, label: 'J16[B57]'}
- {pin_num: '86', pin_signal: PTC14/FB_AD25, label: 'J16[B55]'}
- {pin_num: '87', pin_signal: PTC15/FB_AD24, label: 'J16[B23]'}
- {pin_num: '90', pin_signal: PTC16/LPUART0_RX/FB_CS5_b/FB_TSIZ1/FB_BE23_16_BLS15_8_b, label: 'J16[B58]'}
- {pin_num: '91', pin_signal: PTC17/LPUART0_TX/FB_CS4_b/FB_TSIZ0/FB_BE31_24_BLS7_0_b, label: 'J16[B60]'}
- {pin_num: '92', pin_signal: PTC18/LPUART0_RTS_b/FB_TBST_b/FB_CS2_b/FB_BE15_8_BLS23_16_b, label: 'J16[B35]'}
- {pin_num: '93', pin_signal: PTD0/LLWU_P12/SPI0_PCS0/UART2_RTS_b/FTM3_CH0/FB_ALE/FB_CS1_b/FB_TS_b/LPUART0_RTS_b, label: 'J6[15]/J11[2]/U1[11]/INT1', identifier: ACCEL_INT1}
- {pin_num: '94', pin_signal: ADC0_SE5b/PTD1/SPI0_SCK/UART2_CTS_b/FTM3_CH1/FB_CS0_b/LPUART0_CTS_b, label: 'J6[16]', identifier: TWRPI_GPIO1}
- {pin_num: '95', pin_signal: PTD2/LLWU_P13/SPI0_SOUT/UART2_RX/FTM3_CH2/FB_AD4/LPUART0_RX/I2C0_SCL, label: 'J6[3]/J9[2]/J16[A7]/J500[23]/I2C0_SCL', identifier: ACCEL_SCL}
- {pin_num: '96', pin_signal: PTD3/SPI0_SIN/UART2_TX/FTM3_CH3/FB_AD3/LPUART0_TX/I2C0_SDA, label: 'J6[4]/J12[2]/J16[A8]/J500[21]/I2C0_SDA', identifier: ACCEL_SDA}
- {pin_num: '97', pin_signal: PTD4/LLWU_P14/SPI0_PCS1/UART0_RTS_b/FTM0_CH4/FB_AD2/EWM_IN/SPI1_PCS0, label: 'J16[B40]/J500[34]/FTM0_CH4', identifier: FTM0_CH4}
- {pin_num: '98', pin_signal: ADC0_SE6b/PTD5/SPI0_PCS2/UART0_CTS_b/FTM0_CH5/FB_AD1/EWM_OUT_b/SPI1_SCK, label: 'J16[B39]/J500[36]/FTM0_CH5', identifier: FTM0_CH5}
- {pin_num: '99', pin_signal: ADC0_SE7b/PTD6/LLWU_P15/SPI0_PCS3/UART0_RX/FTM0_CH6/FB_AD0/FTM0_FLT0/SPI1_SOUT, label: 'J16[B34]/FTM0_CH6', identifier: FTM0_CH6}
- {pin_num: '100', pin_signal: PTD7/UART0_TX/FTM0_CH7/FTM0_FLT1/SPI1_SIN, label: 'J6[20]/J17[7]/D7/LED4', identifier: LED_GREEN}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
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
    BOARD_InitDEBUG_UARTPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '36', peripheral: TPIU, signal: SWO, pin_signal: PTA2/UART0_TX/FTM0_CH7/CMP1_OUT/FTM2_QD_PHB/FTM1_CH0/JTAG_TDO/TRACE_SWO/EZP_DO, pull_select: down,
    pull_enable: disable}
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

    /* PORTA2 (pin 36) is configured as TRACE_SWO */
    PORT_SetPinMux(PORTA, 2U, kPORT_MuxAlt7);

    PORTA->PCR[2] = ((PORTA->PCR[2] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                     /* Pull Select: Internal pulldown resistor is enabled on the corresponding pin, if the
                      * corresponding PE field is set. */
                     | PORT_PCR_PS(kPORT_PullDown)

                     /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
                     | PORT_PCR_PE(kPORT_PullDisable));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitBUTTONsPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '78', peripheral: GPIOC, signal: 'GPIO, 6', pin_signal: CMP0_IN0/PTC6/LLWU_P10/SPI0_SOUT/PDB0_EXTRG/FB_AD9/I2C0_SCL, direction: INPUT, slew_rate: fast,
    open_drain: disable, pull_select: up, pull_enable: enable}
  - {pin_num: '83', peripheral: GPIOC, signal: 'GPIO, 11', pin_signal: ADC1_SE7b/PTC11/LLWU_P11/I2C1_SDA/FTM3_CH7/FB_RW_b, direction: INPUT, slew_rate: fast, open_drain: disable,
    pull_select: up, pull_enable: enable}
  - {pin_num: '38', peripheral: GPIOA, signal: 'GPIO, 4', pin_signal: PTA4/LLWU_P3/FTM0_CH1/FTM0_FLT3/NMI_b/EZP_CS_b, direction: INPUT, slew_rate: fast, open_drain: disable,
    pull_select: up, pull_enable: enable, passive_filter: disable}
  - {pin_num: '32', peripheral: GPIOE, signal: 'GPIO, 25', pin_signal: ADC0_SE18/PTE25/FTM0_CH1/I2C0_SDA/EWM_IN, direction: INPUT, slew_rate: fast, open_drain: disable,
    pull_select: up, pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBUTTONsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBUTTONsPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    gpio_pin_config_t SW3_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTA4 (pin 38)  */
    GPIO_PinInit(BOARD_SW3_GPIO, BOARD_SW3_PIN, &SW3_config);

    gpio_pin_config_t SW1_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC6 (pin 78)  */
    GPIO_PinInit(BOARD_SW1_GPIO, BOARD_SW1_PIN, &SW1_config);

    gpio_pin_config_t SW2_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC11 (pin 83)  */
    GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_PIN, &SW2_config);

    gpio_pin_config_t SW4_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTE25 (pin 32)  */
    GPIO_PinInit(BOARD_SW4_GPIO, BOARD_SW4_PIN, &SW4_config);

    const port_pin_config_t SW3 = {/* Internal pull-up resistor is enabled */
                                   kPORT_PullUp,
                                   /* Fast slew rate is configured */
                                   kPORT_FastSlewRate,
                                   /* Passive filter is disabled */
                                   kPORT_PassiveFilterDisable,
                                   /* Open drain is disabled */
                                   kPORT_OpenDrainDisable,
                                   /* Low drive strength is configured */
                                   kPORT_LowDriveStrength,
                                   /* Pin is configured as PTA4 */
                                   kPORT_MuxAsGpio,
                                   /* Pin Control Register fields [15:0] are not locked */
                                   kPORT_UnlockRegister};
    /* PORTA4 (pin 38) is configured as PTA4 */
    PORT_SetPinConfig(BOARD_SW3_PORT, BOARD_SW3_PIN, &SW3);

    const port_pin_config_t SW2 = {/* Internal pull-up resistor is enabled */
                                   kPORT_PullUp,
                                   /* Fast slew rate is configured */
                                   kPORT_FastSlewRate,
                                   /* Passive filter is disabled */
                                   kPORT_PassiveFilterDisable,
                                   /* Open drain is disabled */
                                   kPORT_OpenDrainDisable,
                                   /* Low drive strength is configured */
                                   kPORT_LowDriveStrength,
                                   /* Pin is configured as PTC11 */
                                   kPORT_MuxAsGpio,
                                   /* Pin Control Register fields [15:0] are not locked */
                                   kPORT_UnlockRegister};
    /* PORTC11 (pin 83) is configured as PTC11 */
    PORT_SetPinConfig(BOARD_SW2_PORT, BOARD_SW2_PIN, &SW2);

    const port_pin_config_t SW1 = {/* Internal pull-up resistor is enabled */
                                   kPORT_PullUp,
                                   /* Fast slew rate is configured */
                                   kPORT_FastSlewRate,
                                   /* Passive filter is disabled */
                                   kPORT_PassiveFilterDisable,
                                   /* Open drain is disabled */
                                   kPORT_OpenDrainDisable,
                                   /* Low drive strength is configured */
                                   kPORT_LowDriveStrength,
                                   /* Pin is configured as PTC6 */
                                   kPORT_MuxAsGpio,
                                   /* Pin Control Register fields [15:0] are not locked */
                                   kPORT_UnlockRegister};
    /* PORTC6 (pin 78) is configured as PTC6 */
    PORT_SetPinConfig(BOARD_SW1_PORT, BOARD_SW1_PIN, &SW1);

    const port_pin_config_t SW4 = {/* Internal pull-up resistor is enabled */
                                   kPORT_PullUp,
                                   /* Fast slew rate is configured */
                                   kPORT_FastSlewRate,
                                   /* Passive filter is disabled */
                                   kPORT_PassiveFilterDisable,
                                   /* Open drain is disabled */
                                   kPORT_OpenDrainDisable,
                                   /* Low drive strength is configured */
                                   kPORT_LowDriveStrength,
                                   /* Pin is configured as PTE25 */
                                   kPORT_MuxAsGpio,
                                   /* Pin Control Register fields [15:0] are not locked */
                                   kPORT_UnlockRegister};
    /* PORTE25 (pin 32) is configured as PTE25 */
    PORT_SetPinConfig(BOARD_SW4_PORT, BOARD_SW4_PIN, &SW4);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLEDsPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '1', peripheral: GPIOE, signal: 'GPIO, 0', pin_signal: ADC1_SE4a/PTE0/CLKOUT32K/SPI1_PCS1/UART1_TX/I2C1_SDA, direction: OUTPUT, gpio_init_state: 'true',
    slew_rate: slow, open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: '2', peripheral: GPIOE, signal: 'GPIO, 1', pin_signal: ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/I2C1_SCL/SPI1_SIN, direction: OUTPUT, gpio_init_state: 'true',
    slew_rate: slow, open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: '100', peripheral: GPIOD, signal: 'GPIO, 7', pin_signal: PTD7/UART0_TX/FTM0_CH7/FTM0_FLT1/SPI1_SIN, direction: OUTPUT, gpio_init_state: 'true', slew_rate: slow,
    open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable, digital_filter: disable}
  - {pin_num: '65', peripheral: GPIOB, signal: 'GPIO, 19', pin_signal: PTB19/FTM2_CH1/FB_OE_b/FTM2_QD_PHB, direction: OUTPUT, gpio_init_state: 'true', slew_rate: slow,
    open_drain: disable, pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitLEDsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitLEDsPins(void)
{
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    gpio_pin_config_t LED_ORANGE_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTB19 (pin 65)  */
    GPIO_PinInit(BOARD_LED_ORANGE_GPIO, BOARD_LED_ORANGE_PIN, &LED_ORANGE_config);

    gpio_pin_config_t LED_GREEN_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTD7 (pin 100)  */
    GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_PIN, &LED_GREEN_config);

    gpio_pin_config_t LED_RED_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTE0 (pin 1)  */
    GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_PIN, &LED_RED_config);

    gpio_pin_config_t LED_YELLOW_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTE1 (pin 2)  */
    GPIO_PinInit(BOARD_LED_YELLOW_GPIO, BOARD_LED_YELLOW_PIN, &LED_YELLOW_config);

    const port_pin_config_t LED_ORANGE = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Slow slew rate is configured */
                                          kPORT_SlowSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as PTB19 */
                                          kPORT_MuxAsGpio,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTB19 (pin 65) is configured as PTB19 */
    PORT_SetPinConfig(BOARD_LED_ORANGE_PORT, BOARD_LED_ORANGE_PIN, &LED_ORANGE);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port D */
        PORTD,
        /* Digital filter is configured for PORTD0 */
        PORT_DFER_DFE_7_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t LED_GREEN = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Slow slew rate is configured */
                                         kPORT_SlowSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as PTD7 */
                                         kPORT_MuxAsGpio,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTD7 (pin 100) is configured as PTD7 */
    PORT_SetPinConfig(BOARD_LED_GREEN_PORT, BOARD_LED_GREEN_PIN, &LED_GREEN);

    const port_pin_config_t LED_RED = {/* Internal pull-up/down resistor is disabled */
                                       kPORT_PullDisable,
                                       /* Slow slew rate is configured */
                                       kPORT_SlowSlewRate,
                                       /* Passive filter is disabled */
                                       kPORT_PassiveFilterDisable,
                                       /* Open drain is disabled */
                                       kPORT_OpenDrainDisable,
                                       /* Low drive strength is configured */
                                       kPORT_LowDriveStrength,
                                       /* Pin is configured as PTE0 */
                                       kPORT_MuxAsGpio,
                                       /* Pin Control Register fields [15:0] are not locked */
                                       kPORT_UnlockRegister};
    /* PORTE0 (pin 1) is configured as PTE0 */
    PORT_SetPinConfig(BOARD_LED_RED_PORT, BOARD_LED_RED_PIN, &LED_RED);

    const port_pin_config_t LED_YELLOW = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Slow slew rate is configured */
                                          kPORT_SlowSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as PTE1 */
                                          kPORT_MuxAsGpio,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTE1 (pin 2) is configured as PTE1 */
    PORT_SetPinConfig(BOARD_LED_YELLOW_PORT, BOARD_LED_YELLOW_PIN, &LED_YELLOW);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitDEBUG_UARTPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '62', peripheral: UART0, signal: RX, pin_signal: PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/EWM_IN, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
  - {pin_num: '63', peripheral: UART0, signal: TX, pin_signal: PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/EWM_OUT_b, direction: OUTPUT, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitDEBUG_UARTPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitDEBUG_UARTPins(void)
{
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);

    const port_pin_config_t DEBUG_UART_RX = {/* Internal pull-up/down resistor is disabled */
                                             kPORT_PullDisable,
                                             /* Fast slew rate is configured */
                                             kPORT_FastSlewRate,
                                             /* Passive filter is disabled */
                                             kPORT_PassiveFilterDisable,
                                             /* Open drain is disabled */
                                             kPORT_OpenDrainDisable,
                                             /* Low drive strength is configured */
                                             kPORT_LowDriveStrength,
                                             /* Pin is configured as UART0_RX */
                                             kPORT_MuxAlt3,
                                             /* Pin Control Register fields [15:0] are not locked */
                                             kPORT_UnlockRegister};
    /* PORTB16 (pin 62) is configured as UART0_RX */
    PORT_SetPinConfig(BOARD_DEBUG_UART_RX_PORT, BOARD_DEBUG_UART_RX_PIN, &DEBUG_UART_RX);

    const port_pin_config_t DEBUG_UART_TX = {/* Internal pull-up/down resistor is disabled */
                                             kPORT_PullDisable,
                                             /* Fast slew rate is configured */
                                             kPORT_FastSlewRate,
                                             /* Passive filter is disabled */
                                             kPORT_PassiveFilterDisable,
                                             /* Open drain is disabled */
                                             kPORT_OpenDrainDisable,
                                             /* Low drive strength is configured */
                                             kPORT_LowDriveStrength,
                                             /* Pin is configured as UART0_TX */
                                             kPORT_MuxAlt3,
                                             /* Pin Control Register fields [15:0] are not locked */
                                             kPORT_UnlockRegister};
    /* PORTB17 (pin 63) is configured as UART0_TX */
    PORT_SetPinConfig(BOARD_DEBUG_UART_TX_PORT, BOARD_DEBUG_UART_TX_PIN, &DEBUG_UART_TX);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_UART0TXSRC_MASK)))

                  /* UART 0 transmit data source select: UART0_TX pin. */
                  | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitACCEL_MAGPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '95', peripheral: I2C0, signal: SCL, pin_signal: PTD2/LLWU_P13/SPI0_SOUT/UART2_RX/FTM3_CH2/FB_AD4/LPUART0_RX/I2C0_SCL, slew_rate: fast, open_drain: enable,
    pull_select: up, pull_enable: enable, digital_filter: disable}
  - {pin_num: '96', peripheral: I2C0, signal: SDA, pin_signal: PTD3/SPI0_SIN/UART2_TX/FTM3_CH3/FB_AD3/LPUART0_TX/I2C0_SDA, slew_rate: fast, open_drain: enable, pull_select: up,
    pull_enable: enable, digital_filter: disable}
  - {pin_num: '93', peripheral: GPIOD, signal: 'GPIO, 0', pin_signal: PTD0/LLWU_P12/SPI0_PCS0/UART2_RTS_b/FTM3_CH0/FB_ALE/FB_CS1_b/FB_TS_b/LPUART0_RTS_b, direction: INPUT,
    slew_rate: fast, open_drain: enable, pull_select: up, pull_enable: enable, digital_filter: disable}
  - {pin_num: '31', peripheral: GPIOE, signal: 'GPIO, 24', pin_signal: ADC0_SE17/PTE24/FTM0_CH0/I2C0_SCL/EWM_OUT_b, direction: INPUT, slew_rate: fast, open_drain: enable,
    pull_select: up, pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitACCEL_MAGPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitACCEL_MAGPins(void)
{
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    gpio_pin_config_t ACCEL_INT1_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTD0 (pin 93)  */
    GPIO_PinInit(BOARD_ACCEL_INT1_GPIO, BOARD_ACCEL_INT1_PIN, &ACCEL_INT1_config);

    gpio_pin_config_t ACCEL_INT2_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTE24 (pin 31)  */
    GPIO_PinInit(BOARD_ACCEL_INT2_GPIO, BOARD_ACCEL_INT2_PIN, &ACCEL_INT2_config);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port D */
        PORTD,
        /* Digital filter is configured for PORTD0 */
          PORT_DFER_DFE_0_MASK
            /* Digital filter is configured for PORTD1 */
            | PORT_DFER_DFE_2_MASK
            /* Digital filter is configured for PORTD2 */
            | PORT_DFER_DFE_3_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t ACCEL_INT1 = {/* Internal pull-up resistor is enabled */
                                          kPORT_PullUp,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is enabled */
                                          kPORT_OpenDrainEnable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as PTD0 */
                                          kPORT_MuxAsGpio,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTD0 (pin 93) is configured as PTD0 */
    PORT_SetPinConfig(BOARD_ACCEL_INT1_PORT, BOARD_ACCEL_INT1_PIN, &ACCEL_INT1);

    const port_pin_config_t ACCEL_SCL = {/* Internal pull-up resistor is enabled */
                                         kPORT_PullUp,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is enabled */
                                         kPORT_OpenDrainEnable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as I2C0_SCL */
                                         kPORT_MuxAlt7,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTD2 (pin 95) is configured as I2C0_SCL */
    PORT_SetPinConfig(BOARD_ACCEL_SCL_PORT, BOARD_ACCEL_SCL_PIN, &ACCEL_SCL);

    const port_pin_config_t ACCEL_SDA = {/* Internal pull-up resistor is enabled */
                                         kPORT_PullUp,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is enabled */
                                         kPORT_OpenDrainEnable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as I2C0_SDA */
                                         kPORT_MuxAlt7,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTD3 (pin 96) is configured as I2C0_SDA */
    PORT_SetPinConfig(BOARD_ACCEL_SDA_PORT, BOARD_ACCEL_SDA_PIN, &ACCEL_SDA);

    const port_pin_config_t ACCEL_INT2 = {/* Internal pull-up resistor is enabled */
                                          kPORT_PullUp,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is enabled */
                                          kPORT_OpenDrainEnable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as PTE24 */
                                          kPORT_MuxAsGpio,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTE24 (pin 31) is configured as PTE24 */
    PORT_SetPinConfig(BOARD_ACCEL_INT2_PORT, BOARD_ACCEL_INT2_PIN, &ACCEL_INT2);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPOTPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'false'}
- pin_list:
  - {pin_num: '27', peripheral: ADC0, signal: 'SE, 23', pin_signal: DAC0_OUT/CMP1_IN3/ADC0_SE23}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPOTPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPOTPins(void)
{
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitOSCPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '50', peripheral: OSC, signal: EXTAL0, pin_signal: EXTAL0/PTA18/FTM0_FLT2/FTM_CLKIN0, slew_rate: no_init, open_drain: no_init, pull_select: no_init,
    pull_enable: no_init}
  - {pin_num: '51', peripheral: OSC, signal: XTAL0, pin_signal: XTAL0/PTA19/FTM0_FLT0/FTM1_FLT0/FTM_CLKIN1/LPTMR0_ALT1, slew_rate: no_init, open_drain: no_init, pull_select: no_init,
    pull_enable: no_init}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitOSCPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitOSCPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);

    /* PORTA18 (pin 50) is configured as EXTAL0 */
    PORT_SetPinMux(BOARD_EXTAL0_PORT, BOARD_EXTAL0_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTA19 (pin 51) is configured as XTAL0 */
    PORT_SetPinMux(BOARD_XTAL0_PORT, BOARD_XTAL0_PIN, kPORT_PinDisabledOrAnalog);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
