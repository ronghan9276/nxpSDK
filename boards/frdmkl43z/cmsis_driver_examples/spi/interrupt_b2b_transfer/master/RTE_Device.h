/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __RTE_DEVICE_H
#define __RTE_DEVICE_H

/*Driver name mapping.*/
#define RTE_SPI0        1
#define RTE_SPI0_DMA_EN 0

/* SPI configuration. */
#define RTE_SPI0_DMA_TX_CH          0
#define RTE_SPI0_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0SPI0Tx
#define RTE_SPI0_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_SPI0_DMA_TX_DMA_BASE    DMA0
#define RTE_SPI0_DMA_RX_CH          1
#define RTE_SPI0_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0SPI0Rx
#define RTE_SPI0_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_SPI0_DMA_RX_DMA_BASE    DMA0

#endif /* __RTE_DEVICE_H */
