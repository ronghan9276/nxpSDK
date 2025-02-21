/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "erpc_client_setup.h"
#include "erpc_error_handler.h"
#include "erpc_matrix_multiply.h"
#include "fsl_debug_console.h"
#include <stdlib.h>

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BUTTON_INIT()       GPIO_PinInit(BOARD_SW1_GPIO, BOARD_SW1_GPIO_PIN, &button_config)
#define IS_BUTTON_PRESSED() !GPIO_PinRead(BOARD_SW1_GPIO, BOARD_SW1_GPIO_PIN)

#define MATRIX_ITEM_MAX_VALUE 50

/*******************************************************************************
 * Variables
 ******************************************************************************/

extern bool g_erpc_error_occurred;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Fill matrices by random values
 */
static void fill_matrices(Matrix matrix1_ptr, Matrix matrix2_ptr)
{
    int32_t a, b;

    /* Fill both matrices by random values */
    for (a = 0; a < matrix_size; ++a)
    {
        for (b = 0; b < matrix_size; ++b)
        {
            matrix1_ptr[a][b] = rand() % MATRIX_ITEM_MAX_VALUE;
            matrix2_ptr[a][b] = rand() % MATRIX_ITEM_MAX_VALUE;
        }
    }
}

/*!
 * @brief Printing a matrix to the console
 */
static void print_matrix(Matrix matrix_ptr)
{
    int32_t a, b;

    for (a = 0; a < matrix_size; ++a)
    {
        for (b = 0; b < matrix_size; ++b)
        {
            PRINTF("%4i ", (int)(matrix_ptr[a][b]));
        }
        PRINTF("\r\n");
    }
}

/*!
 * @brief Main function
 */
int main()
{
    Matrix matrix1 = {0}, matrix2 = {0}, result_matrix = {0};

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

#if defined(BOARD_SW1_GPIO) || defined(BOARD_SW2_GPIO) || defined(BOARD_SW3_GPIO)
    /* Define the init structure for the input switch pin */
    gpio_pin_config_t button_config = {
        kGPIO_DigitalInput,
        0,
    };
    /* Configure BUTTON */
    BUTTON_INIT();
#endif

    /* SPI transport layer initialization */
    erpc_transport_t transport;
#if defined(ERPC_BOARD_SPI_BASEADDR)
    transport = erpc_transport_spi_master_init((void *)ERPC_BOARD_SPI_BASEADDR, ERPC_BOARD_SPI_BAUDRATE,
                                               ERPC_BOARD_SPI_CLK_FREQ);
#elif defined(ERPC_BOARD_DSPI_BASEADDR)
    transport = erpc_transport_dspi_master_init((void *)ERPC_BOARD_DSPI_BASEADDR, ERPC_BOARD_DSPI_BAUDRATE,
                                                ERPC_BOARD_DSPI_CLK_FREQ);
#endif

    /* MessageBufferFactory initialization */
    erpc_mbf_t message_buffer_factory;
    message_buffer_factory = erpc_mbf_dynamic_init();

    /* eRPC client side initialization */
    erpc_client_init(transport, message_buffer_factory);

    /* Set default error handler */
    erpc_client_set_error_handler(erpc_error_handler);

    /* Fill both matrices by random values */
    fill_matrices(matrix1, matrix2);

    /* Print both matrices on the console */
    PRINTF("\r\nMatrix #1");
    PRINTF("\r\n=========\r\n");
    print_matrix(matrix1);

    PRINTF("\r\nMatrix #2");
    PRINTF("\r\n=========\r\n");
    print_matrix(matrix2);

    while (1)
    {
        PRINTF("\r\neRPC request is sent to the server\r\n");

        erpcMatrixMultiply(matrix1, matrix2, result_matrix);

        /* Check if some error occurred in eRPC */
        if (g_erpc_error_occurred)
        {
            /* Exit program loop */
            break;
        }

        PRINTF("\r\nResult matrix");
        PRINTF("\r\n=============\r\n");
        print_matrix(result_matrix);

#if defined(BOARD_SW1_GPIO) || defined(BOARD_SW2_GPIO) || defined(BOARD_SW3_GPIO)
        PRINTF("\r\nPress the button to initiate the next matrix multiplication\r\n");
        /* Check for button push. Pin is grounded when button is pushed. */
        while (1 != IS_BUTTON_PRESSED())
        {
        }

        /* Wait for a moment to eliminate the button glitch */
        int32_t i;
        for (i = 0; i < 2500000; ++i)
        {
            __NOP();
        }

        /* Fill both matrices by random values */
        fill_matrices(matrix1, matrix2);

        /* Print both matrices on the console */
        PRINTF("\r\nMatrix #1");
        PRINTF("\r\n=========\r\n");
        print_matrix(matrix1);

        PRINTF("\r\nMatrix #2");
        PRINTF("\r\n=========\r\n");
        print_matrix(matrix2);
#else
        PRINTF("\r\nEnd of example.\r\n");
        while (1)
        {
        }
#endif
    }
    while (1)
    {
    }
}
