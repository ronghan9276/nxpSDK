/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "fsl_uart_freertos.h"
#include "fsl_uart.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_UART UART0
#define DEMO_UART_CLKSRC kCLOCK_CoreSysClk
#define DEMO_UART_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)
/* Task priorities. */
#define uart_task_PRIORITY (configMAX_PRIORITIES - 1)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void uart_task(void *pvParameters);

/*******************************************************************************
 * Variables
 ******************************************************************************/
const char *to_send               = "FreeRTOS UART driver example!\r\n";
const char *send_ring_overrun     = "\r\nRing buffer overrun!\r\n";
const char *send_hardware_overrun = "\r\nHardware buffer overrun!\r\n";
uint8_t background_buffer[32];
uint8_t recv_buffer[4];

uart_rtos_handle_t handle;
struct _uart_handle t_handle;

uart_rtos_config_t uart_config = {
    .baudrate    = 115200,
    .parity      = kUART_ParityDisabled,
    .stopbits    = kUART_OneStopBit,
    .buffer      = background_buffer,
    .buffer_size = sizeof(background_buffer),
};

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Application entry point.
 */
int main(void)
{
    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    if (xTaskCreate(uart_task, "Uart_task", configMINIMAL_STACK_SIZE + 100, NULL, uart_task_PRIORITY, NULL) != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1)
            ;
    }
    vTaskStartScheduler();
    for (;;)
        ;
}

/*!
 * @brief Task responsible for loopback.
 */
static void uart_task(void *pvParameters)
{
    int error;
    size_t n = 0;

    uart_config.srcclk = DEMO_UART_CLK_FREQ;
    uart_config.base   = DEMO_UART;

    if (0 > UART_RTOS_Init(&handle, &t_handle, &uart_config))
    {
        vTaskSuspend(NULL);
    }

    /* Send introduction message. */
    if (0 > UART_RTOS_Send(&handle, (uint8_t *)to_send, strlen(to_send)))
    {
        vTaskSuspend(NULL);
    }

    /* Receive user input and send it back to terminal. */
    do
    {
        error = UART_RTOS_Receive(&handle, recv_buffer, sizeof(recv_buffer), &n);
        if (error == kStatus_UART_RxHardwareOverrun)
        {
            /* Notify about hardware buffer overrun */
            if (kStatus_Success !=
                UART_RTOS_Send(&handle, (uint8_t *)send_hardware_overrun, strlen(send_hardware_overrun)))
            {
                vTaskSuspend(NULL);
            }
        }
        if (error == kStatus_UART_RxRingBufferOverrun)
        {
            /* Notify about ring buffer overrun */
            if (kStatus_Success != UART_RTOS_Send(&handle, (uint8_t *)send_ring_overrun, strlen(send_ring_overrun)))
            {
                vTaskSuspend(NULL);
            }
        }
        if (n > 0)
        {
            /* send back the received data */
            UART_RTOS_Send(&handle, (uint8_t *)recv_buffer, n);
        }
    } while (kStatus_Success == error);

    UART_RTOS_Deinit(&handle);
    vTaskSuspend(NULL);
}
