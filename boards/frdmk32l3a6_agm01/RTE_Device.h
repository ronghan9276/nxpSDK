/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTE_DEVICE_H
#define _RTE_DEVICE_H

extern void LPUART0_InitPins();
extern void LPUART0_DeinitPins();
extern void LPUART1_InitPins();
extern void LPUART1_DeinitPins();
extern void LPI2C0_InitPins();
extern void LPI2C0_DeinitPins();
extern void LPI2C3_InitPins();
extern void LPI2C3_DeinitPins();
extern void LPSPI0_InitPins();
extern void LPSPI0_DeinitPins();

/* Driver name mapping. */
/* User needs to provide the implementation of LPI2CX_GetFreq/LPI2CX_InitPins/LPI2CX_DeinitPins for the enabled LPI2C
 * instance. */
//#define RTE_I2C0 1
//#define RTE_I2C0_DMA_EN 0
#define RTE_I2C3        1
#define RTE_I2C3_DMA_EN 0
/* User needs to provide the implementation of LPSPIX_GetFreq/LPSPIX_InitPins/LPSPIX_DeinitPins for the enabled LPSPI
 * instance. */
#define RTE_SPI0        1
#define RTE_SPI0_DMA_EN 0
/* User needs to provide the implementation of LPUARTX_GetFreq/LPUARTX_InitPins/LPUARTX_DeinitPins for the enabled
 * LPUART instance. */
#define RTE_USART0        1
#define RTE_USART0_DMA_EN 0
#define RTE_USART1        1
#define RTE_USART1_DMA_EN 0

/* UART configuration. */
#define USART_RX_BUFFER_LEN     64
#define USART0_RX_BUFFER_ENABLE 1
#define USART1_RX_BUFFER_ENABLE 1

#define RTE_USART0_PIN_INIT           LPUART0_InitPins
#define RTE_USART0_PIN_DEINIT         LPUART0_DeinitPins
#define RTE_USART0_DMA_TX_CH          0
#define RTE_USART0_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART0Tx
#define RTE_USART0_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART0_DMA_TX_DMA_BASE    DMA0
#define RTE_USART0_DMA_RX_CH          1
#define RTE_USART0_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART0Rx
#define RTE_USART0_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_USART0_DMA_RX_DMA_BASE    DMA0

#define RTE_USART1_PIN_INIT           LPUART1_InitPins
#define RTE_USART1_PIN_DEINIT         LPUART1_DeinitPins
#define RTE_USART1_DMA_TX_CH          0
#define RTE_USART1_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART1Tx
#define RTE_USART1_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART1_DMA_TX_DMA_BASE    DMA0
#define RTE_USART1_DMA_RX_CH          1
#define RTE_USART1_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART1Rx
#define RTE_USART1_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_USART1_DMA_RX_DMA_BASE    DMA0

/* I2C configuration. */
#define RTE_I2C0_PIN_INIT           LPI2C0_InitPins
#define RTE_I2C0_PIN_DEINIT         LPI2C0_DeinitPins
#define RTE_I2C0_DMA_TX_CH          0
#define RTE_I2C0_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0LPI2C0Tx
#define RTE_I2C0_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_I2C0_DMA_TX_DMA_BASE    DMA0
#define RTE_I2C0_DMA_RX_CH          1
#define RTE_I2C0_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0LPI2C0Rx
#define RTE_I2C0_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_I2C0_DMA_RX_DMA_BASE    DMA0

#define RTE_I2C3_PIN_INIT           LPI2C3_InitPins
#define RTE_I2C3_PIN_DEINIT         LPI2C3_DeinitPins
#define RTE_I2C3_DMA_TX_CH          0
#define RTE_I2C3_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux1LPI2C3Tx
#define RTE_I2C3_DMA_TX_DMAMUX_BASE DMAMUX1
#define RTE_I2C3_DMA_TX_DMA_BASE    DMA1
#define RTE_I2C3_DMA_RX_CH          1
#define RTE_I2C3_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux1LPI2C3Rx
#define RTE_I2C3_DMA_RX_DMAMUX_BASE DMAMUX1
#define RTE_I2C3_DMA_RX_DMA_BASE    DMA1

/* SPI configuration. */
#define RTE_SPI0_PCS_TO_SCK_DELAY       1000
#define RTE_SPI0_SCK_TO_PSC_DELAY       1000
#define RTE_SPI0_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI0_MASTER_PCS_PIN_SEL     (kLPSPI_MasterPcs2)
#define RTE_SPI0_SLAVE_PCS_PIN_SEL      (kLPSPI_SlavePcs2)
#define RTE_SPI0_PIN_INIT               LPSPI0_InitPins
#define RTE_SPI0_PIN_DEINIT             LPSPI0_DeinitPins
#define RTE_SPI0_DMA_TX_CH              0
#define RTE_SPI0_DMA_TX_PERI_SEL        (uint8_t) kDmaRequestMux0LPSPI0Tx
#define RTE_SPI0_DMA_TX_DMAMUX_BASE     DMAMUX0
#define RTE_SPI0_DMA_TX_DMA_BASE        DMA0
#define RTE_SPI0_DMA_RX_CH              1
#define RTE_SPI0_DMA_RX_PERI_SEL        (uint8_t) kDmaRequestMux0LPSPI0Rx
#define RTE_SPI0_DMA_RX_DMAMUX_BASE     DMAMUX0
#define RTE_SPI0_DMA_RX_DMA_BASE        DMA0

#endif /* _RTE_DEVICE_H */
