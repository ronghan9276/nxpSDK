/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __RTE_DEVICE_H
#define __RTE_DEVICE_H

/* Driver name mapping. */
#define RTE_USART4        1
#define RTE_USART4_DMA_EN 0

/* UART configuration. */
#define RTE_USART4_DMA_TX_CH          0
#define RTE_USART4_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART4Tx
#define RTE_USART4_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART4_DMA_TX_DMA_BASE    DMA0
#define RTE_USART4_DMA_RX_CH          1
#define RTE_USART4_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART4Rx
#define RTE_USART4_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_USART4_DMA_RX_DMA_BASE    DMA0

/* UART RX buffer configuration. */
#define USART_RX_BUFFER_LEN     128
#define USART4_RX_BUFFER_ENABLE 1

#endif /* __RTE_DEVICE_H */
