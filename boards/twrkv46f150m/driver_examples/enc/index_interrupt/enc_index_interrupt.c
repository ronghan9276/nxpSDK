/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_enc.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_xbara.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_ENC_BASEADDR     ENC
#define DEMO_ENC_INDEX_IRQ_ID ENC_INDEX_IRQn

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_EncIndexCounter = 0U;

/*******************************************************************************
 * Code
 ******************************************************************************/

void NVIC_Configuration(void)
{
    EnableIRQ(DEMO_ENC_INDEX_IRQ_ID); /* Enable the interrupt for ENC_INDEX. */
}

/*!
 * @brief ISR for INDEX event
 */
void ENC_INDEX_IRQHandler(void)
{
    g_EncIndexCounter++;
    ENC_ClearStatusFlags(DEMO_ENC_BASEADDR, kENC_INDEXPulseFlag);
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    enc_config_t mEncConfigStruct;
    uint32_t mCurPosValue;

    XBARA_Init(XBARA);
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nENC INDEX Interrupt Example.\r\n");

    /* Initialize the ENC module. */
    ENC_GetDefaultConfig(&mEncConfigStruct);
    /* Configure the INDEX action. */
    mEncConfigStruct.INDEXTriggerMode = kENC_INDEXTriggerOnRisingEdge;
    /* Setup the hardware. */
    ENC_Init(DEMO_ENC_BASEADDR, &mEncConfigStruct);
    /* Update position counter from initial position register. */
    ENC_DoSoftwareLoadInitialPositionValue(DEMO_ENC_BASEADDR);

    PRINTF("Press any key to get the encoder values ...\r\n");

    /* Interrupts. */
    NVIC_Configuration();
    ENC_ClearStatusFlags(DEMO_ENC_BASEADDR, kENC_INDEXPulseFlag);
    ENC_EnableInterrupts(DEMO_ENC_BASEADDR, kENC_INDEXPulseInterruptEnable);

    while (1)
    {
        GETCHAR();
        PRINTF("\r\n");

        /* This read operation would capture all the positon counter to responding hold registers. */
        mCurPosValue = ENC_GetPositionValue(DEMO_ENC_BASEADDR);

        PRINTF("Current position value: %ld\r\n", mCurPosValue);
        PRINTF("Current position differential value: %d\r\n",
               (int16_t)ENC_GetHoldPositionDifferenceValue(DEMO_ENC_BASEADDR));
        PRINTF("Current position revolution value: %d\r\n", ENC_GetHoldRevolutionValue(DEMO_ENC_BASEADDR));
        PRINTF("g_EncIndexCounter: %d\r\n", g_EncIndexCounter);
    }
}
