/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
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

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
PinsProfile:
- !!product 'Pins v2.0'
- !!processor 'MKW24D512xxx5'
- !!package 'MKW24D512VHA5'
- !!mcu_data 'ksdk2_0'
- !!processor_version '1.1.0'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */
#define SOPT5_UART1RXSRC_UART_RX      0x00u   /*!< UART 1 receive data source select: UART1_RX pin */
#define SOPT5_UART1TXSRC_UART_TX      0x00u   /*!< UART 1 transmit data source select: UART1_TX pin */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '15', peripheral: UART1, signal: TX, pin_signal: ADC0_SE10/PTE0/SPI1_PCS1/UART1_TX/TRACE_CLKOUT/I2C1_SDA/RTC_CLKOUT}
  - {pin_num: '16', peripheral: UART1, signal: RX, pin_signal: ADC0_SE11/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/TRACE_D3/I2C1_SCL/SPI1_SIN}
  - {pin_num: '13', peripheral: FTM0, signal: 'CH, 6', pin_signal: ADC0_SE7b/PTD6/LLWU_P15/SPI0_PCS3/UART0_RX/FTM0_CH6/FTM0_FLT0}
  - {pin_num: '14', peripheral: FTM0, signal: 'CH, 7', pin_signal: ADC0_SE22/PTD7/CMT_IRO/UART0_TX/FTM0_CH7/FTM0_FLT1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortD);                           /* Port D Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Port E Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTD, PIN6_IDX, kPORT_MuxAlt4);            /* PORTD6 (pin 13) is configured as FTM0_CH6 */
  PORT_SetPinMux(PORTD, PIN7_IDX, kPORT_MuxAlt4);            /* PORTD7 (pin 14) is configured as FTM0_CH7 */
  PORT_SetPinMux(PORTE, PIN0_IDX, kPORT_MuxAlt3);            /* PORTE0 (pin 15) is configured as UART1_TX */
  PORT_SetPinMux(PORTE, PIN1_IDX, kPORT_MuxAlt3);            /* PORTE1 (pin 16) is configured as UART1_RX */
  SIM->SOPT5 = ((SIM->SOPT5 &
    (~(SIM_SOPT5_UART1TXSRC_MASK | SIM_SOPT5_UART1RXSRC_MASK))) /* Mask bits to zero which are setting */
      | SIM_SOPT5_UART1TXSRC(SOPT5_UART1TXSRC_UART_TX)       /* UART 1 transmit data source select: UART1_TX pin */
      | SIM_SOPT5_UART1RXSRC(SOPT5_UART1RXSRC_UART_RX)       /* UART 1 receive data source select: UART1_RX pin */
    );
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
