/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
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

/* Kernel includes. */
#include "ucos_ii.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define STACK_SIZE 512
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void hello_task(void *p_arg);

/*******************************************************************************
 * Globals
 ******************************************************************************/
OS_STK stack_hello[STACK_SIZE];

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    OSInit();
    OSTaskCreate(hello_task,                   /* Task function */
                 NULL,                         /* Creation parameter */
                 &stack_hello[STACK_SIZE - 1], /* Stack address */
                 5);                           /* Task priority */

    OSStart();

    return 0;
}

/*!
 * @brief Task responsible for printing of "Hello world." message.
 */
void hello_task(void *p_arg)
{
    INT8U err;
    uint32_t i = 0;

    OS_CPU_SysTickInit(CLOCK_GetFreq(kCLOCK_CoreSysClk) / OS_TICKS_PER_SEC);

    for (;;)
    {
        for (i = 0; i < 10; i++)
        {
            PRINTF("Hello world.\r\n");
            OSTimeDlyHMSM(0, 0, 1, 0);
        }
        err = OSTaskSuspend(OS_PRIO_SELF);
        if (err != OS_ERR_NONE)
        {
            PRINTF("Error.");
        }
    }
}
