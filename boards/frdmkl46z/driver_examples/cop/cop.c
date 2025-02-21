/*
 * The Clear BSD License
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_cop.h"
#include "fsl_rcm.h"

#include "clock_config.h"
#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
* Variables
******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    cop_config_t configCop;

    /* Init hardware */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    RCM->RPFC = (1 << 2) | 1;
    RCM->RPFW = 0x1F;

    /*
     * configCop.enableWindowMode = false;
     * configCop.timeoutMode = kCOP_LongTimeoutMode;
     * configCop.enableStop = false;
     * configCop.enableDebug = false;
     * configCop.clockSource = kCOP_LpoClock;
     * configCop.timeoutCycles = kCOP_2Power10CyclesOr2Power18Cycles;
     */
    COP_GetDefaultConfig(&configCop);
#if FSL_FEATURE_COP_HAS_LONGTIME_MODE
    configCop.timeoutMode = kCOP_ShortTimeoutMode;
#endif

    /* Check if WDOG reset occurred */
    if (RCM_GetPreviousResetSources(RCM) & kRCM_SourceWdog)
    {
        PRINTF("Reset due to COP timeout\r\n");
        COP_Disable(SIM);
        PRINTF("COP example ends!\r\n");
    }
    else
    {
        /* If WDOG reset is not occurred, enables COP */
        PRINTF("\r\nCOP example start!\r\n");
        COP_Init(SIM, &configCop);
        /* Refresh COP 10 times and then wait for timeout reset */
        for (uint32_t loopCount = 0U; loopCount < 10U; loopCount++)
        {
            COP_Refresh(SIM);
            PRINTF("COP refresh %d time\r\n", loopCount + 1U);
        }

        PRINTF("COP will timeout and chip will be reset\r\n");
    }
    while (1)
    {
    }
}
