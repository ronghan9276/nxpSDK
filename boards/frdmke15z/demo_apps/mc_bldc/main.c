/*
 * Copyright 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "main.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* CPU load measurement using Systick*/
uint32_t g_ui32NumberOfCycles    = 0;
uint32_t g_ui32MaxNumberOfCycles = 0;

/* Demo mode enabled/disabled */
bool_t bDemoMode = FALSE;

/* Used for demo mode */
static uint32_t ui32SpeedStimulatorCnt = 0;

/* Counter for button pressing */
static uint32_t ui32ButtonFilter = 0;

/* Application and board ID  */
app_ver_t g_sAppId = {
    "frdm-ke15z", /* board id */
    "bldc",       /* motor type */
    MCRSP_VER,    /* sw version */
};

/* Structure used in FM to get required ID's */
app_ver_t g_sAppIdFM;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief   Application main function processing peripheral function calling and
 *          infinite loop
 *
 * @param   void
 *
 * @return  none
 */
int main(void)
{
    uint32_t ui32PrimaskReg;

    /* disable all interrupts before peripherals are initialized */
    ui32PrimaskReg = DisableGlobalIRQ();

    /* disable demo mode after reset */
    bDemoMode              = FALSE;
    ui32SpeedStimulatorCnt = 0;

    /* Pass actual demo id and board info to FM */
    g_sAppIdFM = g_sAppId;

    /* Init board hardware. */
    BOARD_Init();

    /* initialize peripheral motor control driver for motor M1*/
    MCDRV_Init_M1();

    /* SysTick initialization for CPU load measurement */
    BOARD_InitSysTick();

    /* Enable interrupts */
    EnableGlobalIRQ(ui32PrimaskReg);

    /* infinite loop */
    while (1)
    {
        FMSTR_Poll();
    }
}

/*!
 * @brief   ADC conversion complete ISR called with 100us period processes
 *           - motor M1 fast application machine function
 *
 * @param   void
 *
 * @return  none
 */
void ADC0_IRQHandler(void)
{
    /* Start CPU tick number couting */
    SYSTICK_START_COUNT();

    /* State machine */
    SM_StateMachineFast(&g_sM1Ctrl);

    /* stop CPU tick number couting and store actual and maximum ticks */
    SYSTICK_STOP_COUNT(g_ui32NumberOfCycles);
    g_ui32MaxNumberOfCycles =
        g_ui32NumberOfCycles > g_ui32MaxNumberOfCycles ? g_ui32NumberOfCycles : g_ui32MaxNumberOfCycles;

    /* Call FreeMASTER recorder */
    FMSTR_Recorder(0);

    /* Add empty instructions for correct interrupt flag clearing */
    M1_END_OF_ISR;
}

/*!
 * @brief   FTM1 interrupt service routine
 *          - Forced commutation control
 *
 * @param   void
 *
 * @return  none
 */
void FTM1_IRQHandler(void)
{
    /* asynchronous time event processing */
    M1_TimeEvent();

    /* clear flag */
    FTM1->CONTROLS[0].CnSC &= ~(FTM_CnSC_CHF_MASK);

    /* add empty instructions for correct interrupt flag clearing */
    M1_END_OF_ISR;
}

/*!
 * @brief   FTM2 reload ISR called with 1ms period and processes following functions:
 *           - motor M1 slow application machine function
 *
 * @param   void
 *
 * @return  none
 */
void FTM2_IRQHandler(void)
{
    static int16_t i = 0;

    /* Slow StateMachine call */
    SM_StateMachineSlow(&g_sM1Ctrl);

    /* If in STOP state turn on red */
    if (M1_GetAppState() == 2)
    {
        LED_RED1_ON();
        LED_GREEN1_OFF();
    }

    /* If in FAULT state red blinking*/
    else if (M1_GetAppState() == 0)
    {
        if (i-- < 0)
        {
            LED_RED1_TOGGLE();
            i = 125;
        }
        LED_GREEN1_OFF();
    }

    /* If in RUN or INIT state turn on green */
    else
    {
        LED_RED1_OFF();
        LED_GREEN1_ON();
    }

    /* Demo Speed Simulator */
    DemoSpeedStimulator();

    /* Clear the TOF flag */
    FTM2->SC &= ~(FTM_SC_TOF_MASK);

    /* add empty instructions for correct interrupt flag clearing */
    M1_END_OF_ISR;
}

/*!
 * @brief   PDB_Error_ISR_Handler
 *           - handling the PDB error interrupt: reinitializes the PDB module
 *
 * @param   void
 *
 * @return  none
 */
void PDB0_IRQHandler(void)
{
    PDB0->SC &= (~PDB_SC_PDBEN_MASK);   /* Disable PDB */
    PDB0->CH[0].S &= (~PDB_S_CF_MASK);  /* Clear flag on channel 0 */
    PDB0->CH[0].S &= (~PDB_S_ERR_MASK); /* Clear error on channel 0 */
    PDB0->CH[1].S &= (~PDB_S_CF_MASK);  /* Clear flag on channel 1 */
    PDB0->CH[1].S &= (~PDB_S_ERR_MASK); /* Clear error on channel 1 */
    PDB0->SC |= PDB_SC_PDBEN_MASK;      /* Enable PDB */

    /* add instructions for correct interrupt flag clearing */
    M1_END_OF_ISR;
}

/*!
 * @brief   Port interrupt handler
 *
 * @param   void
 *
 * @return  none
 */
void PORTBCD_IRQHandler(void)
{
    if (PORTB->PCR[11] & PORT_PCR_ISF_MASK)
    {
        /* clear the flag */
        PORTB->PCR[11] |= PORT_PCR_ISF_MASK;

        /* proceed only if pressing longer than timeout */
        if (ui32ButtonFilter > 200)
        {
            ui32ButtonFilter = 0;
            if (bDemoMode)
            {
                /* Stop application */
                M1_SetSpeed(0);
                M1_SetAppSwitch(FALSE);
                bDemoMode = FALSE;
            }
            else
            {
                /* Start application */
                M1_SetAppSwitch(TRUE);
                bDemoMode              = TRUE;
                ui32SpeedStimulatorCnt = 0;
            }
        }
    }

    /* Add empty instructions for correct interrupt flag clearing */
    M1_END_OF_ISR;
}

/*!
 * @brief   DemoSpeedStimulator
 *           - When demo mode is enabled it changes the required speed according
 *             to predefined profile
 *
 * @param   void
 *
 * @return  none
 */
void DemoSpeedStimulator(void)
{
    /* increase push button pressing counter  */
    if (ui32ButtonFilter < 1000)
        ui32ButtonFilter++;

    if (bDemoMode)
    {
        ui32SpeedStimulatorCnt++;
        switch (ui32SpeedStimulatorCnt)
        {
            case 1:
                M1_SetSpeed(FRAC16(1000.0 / M1_N_MAX));
                break;
            case 2500:
                M1_SetSpeed(FRAC16(2000.0 / M1_N_MAX));
                break;
            case 5000:
                M1_SetSpeed(FRAC16(1500.0 / M1_N_MAX));
                break;
            case 7500:
                M1_SetSpeed(FRAC16(1000.0 / M1_N_MAX));
                break;
            case 10000:
                M1_SetSpeed(FRAC16(-2000.0 / M1_N_MAX));
                break;
            case 20000:
                ui32SpeedStimulatorCnt = 0;
                break;
            default:
                break;
        }
    }
}

/*!
 * @brief   void BOARD_Init(void)
 *           - Initialization of clocks, pins and GPIO
 *
 * @param   void
 *
 * @return  none
 */
void BOARD_Init(void)
{
    /* Initialize pins configuration */
    BOARD_InitBootPins();
    /* Initialize clock configuration */
    BOARD_BootClockRUN();
    /* Init peripherals set in peripherals file */
    BOARD_InitBootPeripherals();
    /* Enable & setup interrupts */
    EnableIRQ(PORTBCD_IRQn);
    NVIC_SetPriority(PORTBCD_IRQn, 4);
}


/*!
 *@brief      SysTick initialization for CPU cycle measurement
 *
 *@param      none
 *
 *@return     none
 */
void BOARD_InitSysTick(void)
{
    /* Initialize SysTick core timer to run free */
    /* Set period to maximum value 2^24*/
    SysTick->LOAD = 0xFFFFFF;

    /*Clock source - System Clock*/
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;

    /*Start Sys Timer*/
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}
