/*
 * Copyright 2018-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dsp_config.h"
#include "dsp_xaf.h"
#include "message.h"
#include "rpmsg_lite.h"
#include "rtp.h"

#include "fsl_common.h"
#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
#include "fsl_memory.h"
#endif

#include <xtensa/xos.h>

#include <xtensa/config/core.h>
#include "board_hifi4.h"
#include "fsl_gpio.h"
#include "fsl_inputmux.h"
#include "fsl_dma.h"
#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define INIT_DEBUG_CONSOLE 0
#define BOARD_XTAL_SYS_CLK_HZ 24000000U /*!< Board xtal_sys frequency in Hz */
#define BOARD_XTAL32K_CLK_HZ  32768U    /*!< Board xtal32K frequency in Hz */

#define DSP_THREAD_STACK_SIZE (8 * 1024)
#define DSP_THREAD_PRIORITY   (XOS_MAX_PRIORITY - 3)

/* Must be same size as number of RTP buffers on CM33 side so buffers are not lost */
#define RPMSG_QUEUE_SIZE SHARED_BUFFER_COUNT

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
extern int NonCacheable_start, NonCacheable_end;
extern int NonCacheable_init_start, NonCacheable_init_end;

/*! @brief Main application handle */
static dsp_handle_t dsp;

/*! @brief Main thread stack area */
static uint8_t dsp_thread_stack[DSP_THREAD_STACK_SIZE];

/*******************************************************************************
 * Code
 ******************************************************************************/
static void BOARD_InitClock(void)
{
    CLOCK_SetXtalFreq(BOARD_XTAL_SYS_CLK_HZ); /* sets external XTAL OSC freq */

    CLOCK_EnableClock(kCLOCK_InputMux);

    /* DSP_INT0_SEL18 = DMA1 */
    INPUTMUX_AttachSignal(INPUTMUX, 18U, kINPUTMUX_Dmac1ToDspInterrupt);
    /* MUB interrupt signal is selected for DSP interrupt input 1 */
    INPUTMUX_AttachSignal(INPUTMUX, 1U, kINPUTMUX_MuBToDspInterrupt);

    /* I2S clocks */
    CLOCK_AttachClk(kAUDIO_PLL_to_FLEXCOMM1);
    CLOCK_AttachClk(kAUDIO_PLL_to_FLEXCOMM4);
    /* reset FLEXCOMM for I2S */
    RESET_PeripheralReset(kFC1_RST_SHIFT_RSTn);

    /* DMIC uses 24.576MHz AUDIO_PLL clock */
    CLOCK_AttachClk(kAUDIO_PLL_to_DMIC_CLK);

    /* 24.576MHz divided by 12 = 2048 KHz PDM clock --> gives 16kHz sample rate */
    CLOCK_SetClkDiv(kCLOCK_DivDmicClk, 12);
}

static void XOS_Init(void)
{
    xos_set_clock_freq(XOS_CLOCK_FREQ);

    xos_start_system_timer(-1, 0);
}



/*!
 * @brief Invoked when message is received from RPMsg-Lite
 */
static int rpmsg_callback(void *payload, uint32_t payload_len, uint32_t src, void *priv)
{
    XosMsgQueue *queue = (XosMsgQueue *)priv;
    int status;

    if (payload_len == sizeof(message_t))
    {
        status = xos_msgq_put(queue, payload);
        if (status != XOS_OK)
        {
            xos_fatal_error(status, "Failed to put RPMsg message into queue.\r\n");
        }
    }
    else
    {
        /* Error / invalid message received. */
        xos_fatal_error(XOS_ERR_INVALID_PARAMETER,
                        "RPMsg message with invalid length received from the other core.\r\n");
    }

    return RL_RELEASE;
}

/*!
 * @brief Initializes RPMsg-Lite communication and wait until link with another core is up
 */
static void rpmsg_lite_init(dsp_handle_t *dsp)
{
    static struct rpmsg_lite_ept_static_context ept_ctx;
    static struct rpmsg_lite_instance rpmsg_ctx;
    void *rpmsg_shmem_base;
    int status;

    dsp->rpmsg_queue = malloc(XOS_MSGQ_SIZE(RPMSG_QUEUE_SIZE, sizeof(message_t)));
    if (dsp->rpmsg_queue == NULL)
    {
        xos_fatal_error(status, "Failed to allocate RPMsg queue memory.\r\n");
    }

    status = xos_msgq_create(dsp->rpmsg_queue, RPMSG_QUEUE_SIZE, sizeof(message_t), XOS_MSGQ_WAIT_PRIORITY);
    if (status != XOS_OK)
    {
        xos_fatal_error(status, "Failed to create RPMsg queue.\r\n");
    }

#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
    rpmsg_shmem_base = (void *)MEMORY_ConvertMemoryMapAddress((uint32_t)RPMSG_LITE_SHMEM_BASE, kMEMORY_Local2DMA);
#else
    rpmsg_shmem_base = RPMSG_LITE_SHMEM_BASE;
#endif

    dsp->rpmsg = rpmsg_lite_remote_init(rpmsg_shmem_base, RPMSG_LITE_LINK_ID, RL_NO_FLAGS, &rpmsg_ctx);

    while (RL_TRUE != rpmsg_lite_is_link_up(dsp->rpmsg))
    {
    }

    DSP_PRINTF("[main_dsp] established RPMsg link\r\n");

    dsp->ept = rpmsg_lite_create_ept(dsp->rpmsg, DSP_EPT_ADDR, (rl_ept_rx_cb_t)rpmsg_callback, (void *)dsp->rpmsg_queue,
                                     &ept_ctx);
}

/*!
 * @brief Starts playback thread
 */
static void playback_start(dsp_handle_t *dsp)
{
    int status;

    status = dsp_xaf_start_thread(dsp);
    if (status != 0)
    {
        xos_fatal_error(status, "dsp_xaf_start_thread() failed.\r\n");
    }
}

/*!
 * @brief Enqueues input data for playback
 */
static void command_write(dsp_handle_t *dsp, message_t *msg)
{
    uint32_t buffer_address = 0U;
    uint32_t buffer_size    = 0U;
    int i;

    for (i = 0; i < MESSAGE_PARAMS_MAX; i += 2)
    {
        if (msg->params[i] == MessageParam_NULL)
        {
            break;
        }
        else if (msg->params[i] == MessageParam_PacketAddress)
        {
            buffer_address = msg->params[i + 1];
        }
        else if (msg->params[i] == MessageParam_PacketSize)
        {
            buffer_size = msg->params[i + 1];
        }
    }

    if ((buffer_address != 0U) && (buffer_size != 0U))
    {
        dsp_xaf_add_packet(dsp, (rtp_header_t *)buffer_address, buffer_size);
    }
}

/*!
 * @brief Handles incoming message from ARM core
 */
static void handle_message(dsp_handle_t *dsp, message_t *msg)
{
    switch (msg->command)
    {
        case AudioCommand_PlayPacket:
        {
            command_write(dsp, msg);
            break;
        }

        /* Unknown / unimplemented message */
        default:
        {
            break;
        }
    }
}

/*!
 * @brief Main thread function
 */
static int dsp_main_thread(void *arg, int wake_value)
{
    dsp_handle_t *dsp = (dsp_handle_t *)arg;
    message_t msg;
    int status;

    DSP_PRINTF("[main_dsp] start\r\n");

    /* XAF related initializations */
    dsp_xaf_init(dsp);

    /* Initialize RPMsg-Lite */
    rpmsg_lite_init(dsp);

    /* Initialize audio playback processing chain */
    playback_start(dsp);

    /* Wait until audio processing is ready */
    while (dsp->state != DspState_Running)
    {
        xos_thread_sleep_msec(10);
    }

    /* Receive RPMsg-Lite messages */
    while (true)
    {
        /* Block until received message from ARM core */
        status = xos_msgq_get(dsp->rpmsg_queue, (uint32_t *)&msg);
        if (status != XOS_OK)
        {
            xos_fatal_error(status, "Failed to get item from RPMsg queue.\r\n");
        }

        /* Process request */
        handle_message(dsp, &msg);
    }

    /* Cleanup - will not get here anyway */
    rpmsg_lite_destroy_ept(dsp->rpmsg, dsp->ept);
    rpmsg_lite_deinit(dsp->rpmsg);

    return 0;
}

/*!
 * @brief Main function
 */
int main(void)
{
    XosThread thread_main;

    /* Disable DSP cache for RPMsg-Lite shared memory. */
    xthal_set_region_attribute((void *)RPMSG_LITE_SHMEM_BASE, RPMSG_LITE_SHMEM_SIZE, XCHAL_CA_BYPASS, 0);

    /* Disable DSP cache for shared memory containing RTP packets. */
    xthal_set_region_attribute((void *)AUDIO_SHARED_BUFFER_1, AUDIO_SHARED_BUFFER_1_SIZE, XCHAL_CA_BYPASS, 0);
    xthal_set_region_attribute((void *)AUDIO_SHARED_BUFFER_2, AUDIO_SHARED_BUFFER_2_SIZE, XCHAL_CA_BYPASS, 0);
    /* Disable DSP cache for noncacheable sections. */
    xthal_set_region_attribute((uint32_t *)&NonCacheable_start,
                               (uint32_t)&NonCacheable_end - (uint32_t)&NonCacheable_start, XCHAL_CA_BYPASS, 0);
    xthal_set_region_attribute((uint32_t *)&NonCacheable_init_start,
                               (uint32_t)&NonCacheable_init_end - (uint32_t)&NonCacheable_init_start, XCHAL_CA_BYPASS,
                               0);

    XOS_Init();
    BOARD_InitBootPins();
#if INIT_DEBUG_CONSOLE || APP_DSP_ONLY
    BOARD_InitDebugConsole();
#endif
    BOARD_InitClock();

    /* Iniitalize DMA1 which will be shared by capturer and renderer. */
    DMA_Init(DMA1);

    /* Map DMA IRQ handler to INPUTMUX selection DSP_INT0_SEL18
     * EXTINT19 = DSP INT 23 */
    xos_register_interrupt_handler(XCHAL_EXTINT19_NUM, (XosIntFunc *)DMA_IRQHandle, DMA1);
    xos_interrupt_enable(XCHAL_EXTINT19_NUM);

    /* Create main thread */
    xos_thread_create(&thread_main, NULL, dsp_main_thread, &dsp, "dsp_main", dsp_thread_stack, DSP_THREAD_STACK_SIZE,
                      DSP_THREAD_PRIORITY, 0, 0);

    /* Start XOS scheduler - does not return */
    xos_start(0);

    /* Should not reach this statement */
    return 0;
}
