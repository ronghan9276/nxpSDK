/*
 * The Clear BSD License
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_dspi.h"
#include "board.h"
#include "fsl_dspi_edma.h"
#include "fsl_edma.h"
#include "fsl_dmamux.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_DSPI_SLAVE_BASEADDR SPI0
#define EXAMPLE_DSPI_SLAVE_DMA_MUX_BASEADDR DMAMUX
#define EXAMPLE_DSPI_SLAVE_DMA_BASEADDR DMA0
#define EXAMPLE_DSPI_SLAVE_DMA_RX_REQUEST_SOURCE kDmaRequestMux0SPI0Rx
#define EXAMPLE_DSPI_SLAVE_DMA_TX_REQUEST_SOURCE kDmaRequestMux0SPI0Tx
#define TRANSFER_SIZE 64U /* Transfer dataSize */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* DSPI user callback */
void DSPI_SlaveUserCallback(SPI_Type *base, dspi_slave_edma_handle_t *handle, status_t status, void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t slaveRxData[TRANSFER_SIZE] = {0};

dspi_slave_edma_handle_t g_dspi_edma_s_handle;
edma_handle_t dspiEdmaSlaveRxRegToRxDataHandle;
edma_handle_t dspiEdmaSlaveTxDataToTxRegHandle;

volatile bool isTransferCompleted = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

void DSPI_SlaveUserCallback(SPI_Type *base, dspi_slave_edma_handle_t *handle, status_t status, void *userData)
{
    if (status == kStatus_Success)
    {
        PRINTF("This is DSPI slave edma transfer completed callback. \r\n\r\n");
    }

    isTransferCompleted = true;
}

/*!
 * @brief Main function
 */
int main(void)
{
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("DSPI board to board edma example.\r\n");

    /* DMA Mux setting and EDMA init */
    uint32_t slaveRxChannel, slaveTxChannel;
    edma_config_t userConfig;

    slaveRxChannel = 0U;
    slaveTxChannel = 1U;

    /* DMA MUX init */
    DMAMUX_Init(EXAMPLE_DSPI_SLAVE_DMA_MUX_BASEADDR);

    DMAMUX_SetSource(EXAMPLE_DSPI_SLAVE_DMA_MUX_BASEADDR, slaveRxChannel, (uint8_t)EXAMPLE_DSPI_SLAVE_DMA_RX_REQUEST_SOURCE);
    DMAMUX_EnableChannel(EXAMPLE_DSPI_SLAVE_DMA_MUX_BASEADDR, slaveRxChannel);

#if (defined EXAMPLE_DSPI_SLAVE_DMA_TX_REQUEST_SOURCE)
    DMAMUX_SetSource(EXAMPLE_DSPI_SLAVE_DMA_MUX_BASEADDR, slaveTxChannel, (uint8_t)EXAMPLE_DSPI_SLAVE_DMA_TX_REQUEST_SOURCE);
    DMAMUX_EnableChannel(EXAMPLE_DSPI_SLAVE_DMA_MUX_BASEADDR, slaveTxChannel);
#endif

    /* EDMA init */
    /*
     * userConfig.enableRoundRobinArbitration = false;
     * userConfig.enableHaltOnError = true;
     * userConfig.enableContinuousLinkMode = false;
     * userConfig.enableDebugMode = false;
     */
    EDMA_GetDefaultConfig(&userConfig);
    EDMA_Init(EXAMPLE_DSPI_SLAVE_DMA_BASEADDR, &userConfig);

    uint32_t i;
    dspi_slave_config_t slaveConfig;
    dspi_transfer_t slaveXfer;

    /* Slave config */
    slaveConfig.whichCtar = kDSPI_Ctar0;
    slaveConfig.ctarConfig.bitsPerFrame = 8U;
    slaveConfig.ctarConfig.cpol = kDSPI_ClockPolarityActiveHigh;
    slaveConfig.ctarConfig.cpha = kDSPI_ClockPhaseFirstEdge;
    slaveConfig.enableContinuousSCK = false;
    slaveConfig.enableRxFifoOverWrite = false;
    slaveConfig.enableModifiedTimingFormat = false;
    slaveConfig.samplePoint = kDSPI_SckToSin0Clock;

    DSPI_SlaveInit(EXAMPLE_DSPI_SLAVE_BASEADDR, &slaveConfig);

    /* Set up dspi slave first */
    memset(&(dspiEdmaSlaveRxRegToRxDataHandle), 0, sizeof(dspiEdmaSlaveRxRegToRxDataHandle));
    memset(&(dspiEdmaSlaveTxDataToTxRegHandle), 0, sizeof(dspiEdmaSlaveTxDataToTxRegHandle));
    EDMA_CreateHandle(&(dspiEdmaSlaveRxRegToRxDataHandle), EXAMPLE_DSPI_SLAVE_DMA_BASEADDR, slaveRxChannel);
    EDMA_CreateHandle(&(dspiEdmaSlaveTxDataToTxRegHandle), EXAMPLE_DSPI_SLAVE_DMA_BASEADDR, slaveTxChannel);
    DSPI_SlaveTransferCreateHandleEDMA(EXAMPLE_DSPI_SLAVE_BASEADDR, &g_dspi_edma_s_handle, DSPI_SlaveUserCallback, NULL,
                                       &dspiEdmaSlaveRxRegToRxDataHandle, &dspiEdmaSlaveTxDataToTxRegHandle);

    while (1)
    {
        PRINTF("\r\n Slave example is running...\r\n");

        /* Reset the receive buffer */
        for (i = 0U; i < TRANSFER_SIZE; i++)
        {
            slaveRxData[i] = 0U;
        }

        /* Set slave transfer ready to receive data */
        isTransferCompleted = false;
        slaveXfer.txData = NULL;
        slaveXfer.rxData = slaveRxData;
        slaveXfer.dataSize = TRANSFER_SIZE;
        slaveXfer.configFlags = kDSPI_SlaveCtar0;

        /* Slave start receive */
        if (kStatus_Success != DSPI_SlaveTransferEDMA(EXAMPLE_DSPI_SLAVE_BASEADDR, &g_dspi_edma_s_handle, &slaveXfer))
        {
            PRINTF("There is error when start DSPI_SlaveTransferEDMA \r\n");
        }

        while (!isTransferCompleted)
        {
        }

        /* Set slave transfer ready to send back data */
        isTransferCompleted = false;
        slaveXfer.txData = slaveRxData;
        slaveXfer.rxData = NULL;
        slaveXfer.dataSize = TRANSFER_SIZE;
        slaveXfer.configFlags = kDSPI_SlaveCtar0;

        /* Slave start send */
        if (kStatus_Success != DSPI_SlaveTransferEDMA(EXAMPLE_DSPI_SLAVE_BASEADDR, &g_dspi_edma_s_handle, &slaveXfer))
        {
            PRINTF("There is error when start DSPI_SlaveTransferEDMA \r\n");
        }

        while (!isTransferCompleted)
        {
        }

        /* Print out receive buffer */
        PRINTF("\r\n Slave receive:");
        for (i = 0; i < TRANSFER_SIZE; i++)
        {
            /* Print 16 numbers in a line */
            if ((i & 0x0FU) == 0U)
            {
                PRINTF("\r\n    ");
            }
            PRINTF(" %02X", slaveRxData[i]);
        }
        PRINTF("\r\n");
    }
}
