/*
 * The Clear BSD License
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
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

#include "fsl_common.h"
#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_DSPI_SLAVE_BASEADDR SPI0
#define EXAMPLE_DSPI_SLAVE_IRQ SPI0_IRQn
#define EXAMPLE_DSPI_SLAVE_IRQHandler SPI0_IRQHandler
#define TRANSFER_SIZE 64U /*! Transfer dataSize */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t slaveRxData[TRANSFER_SIZE] = {0U};
uint8_t slaveTxData[TRANSFER_SIZE] = {0U};

volatile uint32_t slaveTxCount;
volatile uint32_t slaveRxCount;

volatile bool isTransferCompleted = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

void EXAMPLE_DSPI_SLAVE_IRQHandler(void)
{
    if (slaveRxCount < TRANSFER_SIZE)
    {
        while (DSPI_GetStatusFlags(EXAMPLE_DSPI_SLAVE_BASEADDR) & kDSPI_RxFifoDrainRequestFlag)
        {
            slaveRxData[slaveRxCount] = DSPI_ReadData(EXAMPLE_DSPI_SLAVE_BASEADDR);
            slaveRxCount++;

            DSPI_ClearStatusFlags(EXAMPLE_DSPI_SLAVE_BASEADDR, kDSPI_RxFifoDrainRequestFlag);

            if (slaveTxCount < TRANSFER_SIZE)
            {
                DSPI_SlaveWriteData(EXAMPLE_DSPI_SLAVE_BASEADDR, slaveTxData[slaveTxCount]);
                slaveTxCount++;
            }

            /* Try to clear TFFF by writing a one to it; it will not clear if TX FIFO not full */
            DSPI_ClearStatusFlags(EXAMPLE_DSPI_SLAVE_BASEADDR, kDSPI_TxFifoFillRequestFlag);

            if (slaveRxCount == TRANSFER_SIZE)
            {
                break;
            }
        }
    }

    /* Check if remaining receive byte count matches user request */
    if ((slaveRxCount == TRANSFER_SIZE) && (slaveTxCount == TRANSFER_SIZE))
    {
        isTransferCompleted = true;
        /* Disable interrupt requests */
        DSPI_DisableInterrupts(EXAMPLE_DSPI_SLAVE_BASEADDR, kDSPI_RxFifoDrainRequestInterruptEnable);
    }
    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

/*!
 * @brief Main function
 */
int main(void)
{
    BOARD_InitPins();
    BOARD_BootClockHSRUN();
    BOARD_InitDebugConsole();

    PRINTF("DSPI board to board functional interrupt example.\r\n");

    uint32_t i;
    dspi_slave_config_t slaveConfig;

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

    EnableIRQ(EXAMPLE_DSPI_SLAVE_IRQ);

    while (1)
    {
        PRINTF("\r\n Slave example is running...\r\n");

        /* Reset the receive buffer */
        for (i = 0; i < TRANSFER_SIZE; i++)
        {
            slaveRxData[i] = 0U;
            slaveTxData[i] = 0U;
        }

        /* Set up slave to receive data */
        isTransferCompleted = false;
        slaveTxCount = 0;
        slaveRxCount = 0;

        DSPI_StopTransfer(EXAMPLE_DSPI_SLAVE_BASEADDR);
        DSPI_FlushFifo(EXAMPLE_DSPI_SLAVE_BASEADDR, true, true);
        DSPI_ClearStatusFlags(EXAMPLE_DSPI_SLAVE_BASEADDR, kDSPI_AllStatusFlag);

        /*Fill up the slave Tx data*/
        while (DSPI_GetStatusFlags(EXAMPLE_DSPI_SLAVE_BASEADDR) & kDSPI_TxFifoFillRequestFlag)
        {
            /* Transmit data */
            if (slaveTxCount < TRANSFER_SIZE)
            {
                /* Write the data to the DSPI data register */
                DSPI_SlaveWriteData(EXAMPLE_DSPI_SLAVE_BASEADDR, slaveTxData[slaveTxCount]);

                ++slaveTxCount;
            }
            else
            {
                break;
            }

            /* Try to clear TFFF by writing a one to it; it will not clear if TX FIFO not full */
            DSPI_ClearStatusFlags(EXAMPLE_DSPI_SLAVE_BASEADDR, kDSPI_TxFifoFillRequestFlag);
        }

        /*Enable slave RX interrupt*/
        DSPI_EnableInterrupts(EXAMPLE_DSPI_SLAVE_BASEADDR, kDSPI_RxFifoDrainRequestInterruptEnable);
        DSPI_StartTransfer(EXAMPLE_DSPI_SLAVE_BASEADDR);

        while (!isTransferCompleted)
        {
        }

        /* Reset the receive buffer */
        for (i = 0; i < TRANSFER_SIZE; i++)
        {
            slaveTxData[i] = slaveRxData[i];
            slaveRxData[i] = 0U;
        }

        /* Set up slave to receive data */
        isTransferCompleted = false;
        slaveTxCount = 0;
        slaveRxCount = 0;

        DSPI_StopTransfer(EXAMPLE_DSPI_SLAVE_BASEADDR);
        DSPI_FlushFifo(EXAMPLE_DSPI_SLAVE_BASEADDR, true, true);
        DSPI_ClearStatusFlags(EXAMPLE_DSPI_SLAVE_BASEADDR, kDSPI_AllStatusFlag);

        /*Fill up the slave Tx data*/
        while (DSPI_GetStatusFlags(EXAMPLE_DSPI_SLAVE_BASEADDR) & kDSPI_TxFifoFillRequestFlag)
        {
            /* Transmit data */
            if (slaveTxCount < TRANSFER_SIZE)
            {
                /* Write the data to the DSPI data register */
                DSPI_SlaveWriteData(EXAMPLE_DSPI_SLAVE_BASEADDR, slaveTxData[slaveTxCount]);

                ++slaveTxCount;
            }
            else
            {
                break;
            }

            /* Try to clear TFFF by writing a one to it; it will not clear if TX FIFO not full */
            DSPI_ClearStatusFlags(EXAMPLE_DSPI_SLAVE_BASEADDR, kDSPI_TxFifoFillRequestFlag);
        }

        /*Enable slave RX interrupt*/
        DSPI_EnableInterrupts(EXAMPLE_DSPI_SLAVE_BASEADDR, kDSPI_RxFifoDrainRequestInterruptEnable);
        DSPI_StartTransfer(EXAMPLE_DSPI_SLAVE_BASEADDR);

        while (!isTransferCompleted)
        {
        }

        /* Print out slave received data in 1st round transfer. Use the slaveTxData since already copy the
        slaveRxData to slaveTxData after 1st round transfer.*/
        PRINTF("\r\n Slave receive below data in 1st round transfer:");
        for (i = 0U; i < TRANSFER_SIZE; i++)
        {
            /* Print 16 numbers in a line */
            if ((i & 0x0FU) == 0U)
            {
                PRINTF("\r\n    ");
            }
            PRINTF(" %02X", slaveTxData[i]);
        }
        PRINTF("\r\n");
    }
}
