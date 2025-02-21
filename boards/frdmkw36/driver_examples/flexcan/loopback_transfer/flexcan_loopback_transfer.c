/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "fsl_flexcan.h"
#include "board.h"

#include "fsl_device_registers.h"
#include "fsl_common.h"
#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_CAN CAN0
#define DEMO_FORCE_CAN_SRC_OSC (1)
#define EXAMPLE_CAN_CLK_FREQ CLOCK_GetFreq(kCLOCK_Osc0ErClk)/2
#define USE_CANFD (1)
#define USE_IMPROVED_TIMING_CONFIG (1)
/*
 *    DWORD_IN_MB    DLC    BYTES_IN_MB             Maximum MBs
 *    2              8      kFLEXCAN_8BperMB        32
 *    4              10     kFLEXCAN_16BperMB       21
 *    8              13     kFLEXCAN_32BperMB       12
 *    16             15     kFLEXCAN_64BperMB       7
 *
 * Dword in each message buffer, Length of data in bytes, Payload size must align,
 * and the Message Buffers are limited corresponding to each payload configuration:
 */
#define DWORD_IN_MB (8)
#define DLC (13)
#define BYTES_IN_MB kFLEXCAN_32BperMB
#define RX_MESSAGE_BUFFER_NUM (8)
#define TX_MESSAGE_BUFFER_NUM (9)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool txComplete = false;
volatile bool rxComplete = false;
flexcan_handle_t flexcanHandle;
flexcan_mb_transfer_t txXfer, rxXfer;
#if (defined(USE_CANFD) && USE_CANFD)
flexcan_fd_frame_t txFrame, rxFrame;
#else
flexcan_frame_t txFrame, rxFrame;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief FlexCAN Call Back function
 */
static void flexcan_callback(CAN_Type *base, flexcan_handle_t *handle, status_t status, uint32_t result, void *userData)
{
    switch (status)
    {
        /* Process FlexCAN Rx event. */
        case kStatus_FLEXCAN_RxIdle:
            if (RX_MESSAGE_BUFFER_NUM == result)
            {
                rxComplete = true;
            }
            break;

        /* Process FlexCAN Tx event. */
        case kStatus_FLEXCAN_TxIdle:
            if (TX_MESSAGE_BUFFER_NUM == result)
            {
                txComplete = true;
            }
            break;

        default:
            break;
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    flexcan_config_t flexcanConfig;
    flexcan_rx_mb_config_t mbConfig;

    /* Initialize board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();

    BOARD_InitDebugConsole();

    PRINTF("\r\n==FlexCAN loopback example -- Start.==\r\n\r\n");

    /* Init FlexCAN module. */
    /*
     * flexcanConfig.clkSrc = kFLEXCAN_ClkSrcOsc;
     * flexcanConfig.baudRate = 1000000U;
     * flexcanConfig.baudRateFD = 1000000U;      
     * flexcanConfig.maxMbNum = 16;
     * flexcanConfig.enableLoopBack = false;
     * flexcanConfig.enableSelfWakeup = false;
     * flexcanConfig.enableIndividMask = false;
     * flexcanConfig.enableDoze = false;
     */
    FLEXCAN_GetDefaultConfig(&flexcanConfig);
#if (!defined(FSL_FEATURE_FLEXCAN_SUPPORT_ENGINE_CLK_SEL_REMOVE)) || !FSL_FEATURE_FLEXCAN_SUPPORT_ENGINE_CLK_SEL_REMOVE
#if (!defined(DEMO_FORCE_CAN_SRC_OSC)) || !DEMO_FORCE_CAN_SRC_OSC
    flexcanConfig.clkSrc = kFLEXCAN_ClkSrcPeri;
#endif /* DEMO_FORCE_CAN_SRC_OSC */
#endif /* FSL_FEATURE_FLEXCAN_SUPPORT_ENGINE_CLK_SEL_REMOVE */
    flexcanConfig.enableLoopBack = true;

#if (defined(USE_IMPROVED_TIMING_CONFIG) && USE_IMPROVED_TIMING_CONFIG)
    flexcan_timing_config_t timing_config;
    memset(&timing_config, 0, sizeof(flexcan_timing_config_t));
#if (defined(USE_CANFD) && USE_CANFD)
    if (FLEXCAN_FDCalculateImprovedTimingValues(flexcanConfig.baudRate, flexcanConfig.baudRateFD, EXAMPLE_CAN_CLK_FREQ,
                                                &timing_config))
    {
        /* Update the improved timing configuration*/
        memcpy(&(flexcanConfig.timingConfig), &timing_config, sizeof(flexcan_timing_config_t));
    }
    else
    {
        PRINTF("No found Improved Timing Configuration. Just used default configuration\r\n\r\n");
    }
#else
    if (FLEXCAN_CalculateImprovedTimingValues(flexcanConfig.baudRate, EXAMPLE_CAN_CLK_FREQ, &timing_config))
    {
        /* Update the improved timing configuration*/
        memcpy(&(flexcanConfig.timingConfig), &timing_config, sizeof(flexcan_timing_config_t));
    }
    else
    {
        PRINTF("No found Improved Timing Configuration. Just used default configuration\r\n\r\n");
    }
#endif
#endif

#if (defined(USE_CANFD) && USE_CANFD)
    FLEXCAN_FDInit(EXAMPLE_CAN, &flexcanConfig, EXAMPLE_CAN_CLK_FREQ, BYTES_IN_MB, true);
#else
    FLEXCAN_Init(EXAMPLE_CAN, &flexcanConfig, EXAMPLE_CAN_CLK_FREQ);
#endif

    /* Setup Rx Message Buffer. */
    mbConfig.format = kFLEXCAN_FrameFormatStandard;
    mbConfig.type = kFLEXCAN_FrameTypeData;
    mbConfig.id = FLEXCAN_ID_STD(0x123);
#if (defined(USE_CANFD) && USE_CANFD)
    FLEXCAN_SetFDRxMbConfig(EXAMPLE_CAN, RX_MESSAGE_BUFFER_NUM, &mbConfig, true);
#else
    FLEXCAN_SetRxMbConfig(EXAMPLE_CAN, RX_MESSAGE_BUFFER_NUM, &mbConfig, true);
#endif

    /* Setup Tx Message Buffer. */
#if (defined(USE_CANFD) && USE_CANFD)
    FLEXCAN_SetFDTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_NUM, true);
#else
    FLEXCAN_SetTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_NUM, true);
#endif

    /* Create FlexCAN handle structure and set call back function. */
    FLEXCAN_TransferCreateHandle(EXAMPLE_CAN, &flexcanHandle, flexcan_callback, NULL);

    /* Start receive data through Rx Message Buffer. */
    rxXfer.mbIdx = RX_MESSAGE_BUFFER_NUM;
#if (defined(USE_CANFD) && USE_CANFD)
    rxXfer.framefd = &rxFrame;
    FLEXCAN_TransferFDReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer);
#else
    rxXfer.frame = &rxFrame;
    FLEXCAN_TransferReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer);
#endif

    /* Prepare Tx Frame for sending. */
    txFrame.format = kFLEXCAN_FrameFormatStandard;
    txFrame.type = kFLEXCAN_FrameTypeData;
    txFrame.id = FLEXCAN_ID_STD(0x123);
#if (defined(USE_CANFD) && USE_CANFD)
    txFrame.brs = 1U;
    txFrame.length = DLC;
#else
    txFrame.length = 8;
#endif
#if (defined(USE_CANFD) && USE_CANFD)
    uint8_t i = 0;
    for (i=0; i < DWORD_IN_MB; i++)
    {
        txFrame.dataWord[i] = i;
    }
#else
    txFrame.dataWord0 = CAN_WORD0_DATA_BYTE_0(0x11) | CAN_WORD0_DATA_BYTE_1(0x22) | CAN_WORD0_DATA_BYTE_2(0x33) |
                        CAN_WORD0_DATA_BYTE_3(0x44);
    txFrame.dataWord1 = CAN_WORD1_DATA_BYTE_4(0x55) | CAN_WORD1_DATA_BYTE_5(0x66) | CAN_WORD1_DATA_BYTE_6(0x77) |
                        CAN_WORD1_DATA_BYTE_7(0x88);
#endif

    PRINTF("Send message from MB%d to MB%d\r\n", TX_MESSAGE_BUFFER_NUM, RX_MESSAGE_BUFFER_NUM);
#if (defined(USE_CANFD) && USE_CANFD)
    for (i=0; i < DWORD_IN_MB; i++)
    {
        PRINTF("tx word%d = 0x%x\r\n", i, txFrame.dataWord[i]);
    }
#else
    PRINTF("tx word0 = 0x%x\r\n", txFrame.dataWord0);
    PRINTF("tx word1 = 0x%x\r\n", txFrame.dataWord1);
#endif

    /* Send data through Tx Message Buffer. */
    txXfer.mbIdx = TX_MESSAGE_BUFFER_NUM;
#if (defined(USE_CANFD) && USE_CANFD)
    txXfer.framefd = &txFrame;
    FLEXCAN_TransferFDSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#else
    txXfer.frame = &txFrame;
    FLEXCAN_TransferSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#endif

    /* Waiting for Rx Message finish. */
    while ((!rxComplete) || (!txComplete))
    {
    };

    PRINTF("\r\nReceived message from MB%d\r\n", RX_MESSAGE_BUFFER_NUM);
#if (defined(USE_CANFD) && USE_CANFD)
    for (i=0; i < DWORD_IN_MB; i++)
    {
        PRINTF("rx word%d = 0x%x\r\n", i, rxFrame.dataWord[i]);
    }
#else
    PRINTF("rx word0 = 0x%x\r\n", rxFrame.dataWord0);
    PRINTF("rx word1 = 0x%x\r\n", rxFrame.dataWord1);
#endif

    PRINTF("\r\n==FlexCAN loopback example -- Finish.==\r\n");

    while (1)
    {
        __WFI();
    }
}
