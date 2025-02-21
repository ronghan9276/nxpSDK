/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "fsl_common.h"
#include "fsl_gpio.h"

#include "clock_config.h"
#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_MCGOUTCLK_FREQ 120000000U
#define LED_INIT() LED_RED_INIT(LOGIC_LED_ON)
#define LED_TOGGLE() LED_RED_TOGGLE()
#define CORE_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
mcg_pll_config_t g_pllConfig; /* The Pll config. */
uint32_t g_frdivValue = 0U;   /* The FRDIV value.*/
                              /*******************************************************************************
                               * Code
                               ******************************************************************************/
#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
/*!
 * @brief Get the available FRDIV. The FLL reference clock after FRDIV must
 * be in the range of 31250Hz to 39062.5Hz.
 */
bool APP_GetAvailableFrdiv(void)
{
    const uint32_t allowedRefFreq[][2U] =
    {
        /*  Min          Max   */
        {1000000U, 1250000U},
        {2000000U, 2500000U},
        {4000000U, 5000000U},
        {8000000U, 10000000U},
        {16000000U, 20000000U},
        {32000000U, 40000000U},
#if (defined(FSL_FEATURE_MCG_FRDIV_SUPPORT_1280) && FSL_FEATURE_MCG_FRDIV_SUPPORT_1280)
        {40000000U, 50000000U},
#endif /* FSL_FEATURE_MCG_FRDIV_SUPPORT_1280 */
#if (defined(FSL_FEATURE_MCG_FRDIV_SUPPORT_1536) && FSL_FEATURE_MCG_FRDIV_SUPPORT_1536)
        {48000000U, 60000000U}
#endif /* FSL_FEATURE_MCG_FRDIV_SUPPORT_1536 */
    };
    uint32_t size = (sizeof(allowedRefFreq) / sizeof(allowedRefFreq[0U]));

    if (32768U == g_xtal0Freq)
    {
        g_frdivValue = 0U;
        return true;
    }
    for (g_frdivValue = 0U; g_frdivValue < size; g_frdivValue++)
    {
        if ((g_xtal0Freq >= allowedRefFreq[g_frdivValue][0U]) && (g_xtal0Freq <= allowedRefFreq[g_frdivValue][1U]))
        {
            return true;
        }
    }
    return false;
}
#endif /* FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE */

/*!
 * @brief Get the available PLL configuration.
 * If the PLL has dividers PRDIV and VDIV, here need to calculate the available
 * divider values.
 * If the PLL could share the FLL reference clock, here need to check whether
 * the FLL reference clock could be divided to the allowed range.
 */
bool APP_GetAvailablePllConfig(mcg_pll_config_t *pllConfig)
{
    pllConfig->enableMode = 0U;

#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
    pllConfig->refSrc = kMCG_PllRefFllRef;
#elif(defined(FSL_FEATURE_MCG_USE_PLLREFSEL) && FSL_FEATURE_MCG_USE_PLLREFSEL)
    pllConfig->refSrc = kMCG_PllRefOsc0;
#endif /* FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE || FSL_FEATURE_MCG_USE_PLLREFSEL */
#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
    pllConfig->frdiv = g_frdivValue;
#endif /* FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE */
#if ((defined(FSL_FEATURE_MCG_HAS_PLL_PRDIV) && FSL_FEATURE_MCG_HAS_PLL_PRDIV)) && \
    ((defined(FSL_FEATURE_MCG_HAS_PLL_VDIV) && FSL_FEATURE_MCG_HAS_PLL_VDIV))
    if (!CLOCK_CalcPllDiv(g_xtal0Freq, APP_MCGOUTCLK_FREQ, &pllConfig->prdiv, &pllConfig->vdiv))
    {
        return false;
    }
#endif /* FSL_FEATURE_MCG_HAS_PLL_PRDIV && FSL_FEATURE_MCG_HAS_PLL_VDIV */
    return true;
}

/*!
 * @brief Example function to show how to change from PEE to BLPI mode.
 * MCG transition: PEE ->FBE -> FBI -> BLPI
 */
void APP_ChangePeeToBlpiExample(void)
{
    /* Quick change PEE ->FBE */
    CLOCK_ExternalModeToFbeModeQuick();
    assert(kMCG_ModeFBE == CLOCK_GetMode());

    /* Change FBE -> FBI
    * It's transitional mode, don't need to wait for FLL stable
    * so NULL is passed as variable here.
    */
    CLOCK_SetFbiMode(kMCG_Dmx32Default, kMCG_DrsLow, NULL);
    assert(kMCG_ModeFBI == CLOCK_GetMode());

    /* Change FBI -> BLPI */
    CLOCK_SetLowPowerEnable(true);
    assert(kMCG_ModeBLPI == CLOCK_GetMode());
}

/*!
 * @brief Example function to show how to change from PEE to BLPI mode.
 * MCG transition: BLPI -> FBI -> FBE -> PBE -> PEE
 */
void APP_ChangeBlpiToPeeExample(void)
{
    /* Change BLPI -> FBI */
    CLOCK_SetLowPowerEnable(false);
    assert(kMCG_ModeFBI == CLOCK_GetMode());

    /* Change FBI -> FBE
    * It's transitional mode, don't need to wait for FLL stable
    * so NULL is passed as variable here.
    */
    CLOCK_SetFbeMode(g_frdivValue, kMCG_Dmx32Default, kMCG_DrsLow, NULL);
    assert(kMCG_ModeFBE == CLOCK_GetMode());

    /* Change FBE -> PBE */
    CLOCK_SetPbeMode(kMCG_PllClkSelPll0, &g_pllConfig);
    assert(kMCG_ModePBE == CLOCK_GetMode());

    /* Change PBE -> PEE */
    CLOCK_SetPeeMode();
    assert(kMCG_ModePEE == CLOCK_GetMode());
}

void APP_BootToPeeExample(void)
{
#if (!defined (BOARD_XTAL0_CLK_HZ))
    /* alternative clock's source */
#if defined BOARD_IRC48M_CLK_HZ
    CLOCK_BootToPeeMode(kMCG_OscselIrc, kMCG_PllClkSelPll0, &g_pllConfig);
#endif
#else
    CLOCK_BootToPeeMode(kMCG_OscselOsc, kMCG_PllClkSelPll0, &g_pllConfig);
#endif
    assert(kMCG_ModePEE == CLOCK_GetMode());
}

/*!
 * @brief Main function
 */
int main(void)
{
    volatile uint32_t i;
    uint32_t sysFreq;

    /* Structure for OSC configuration */
    osc_config_t oscConfig;
    oscConfig.freq = BOARD_XTAL0_CLK_HZ;
    oscConfig.capLoad = 0U;
    oscConfig.workMode = kOSC_ModeOscLowPower;
    oscConfig.oscerConfig.enableMode = kOSC_ErClkEnable;

    BOARD_InitPins();
    CLOCK_InitOsc0(&oscConfig);

    CLOCK_SetXtal0Freq(BOARD_XTAL0_CLK_HZ);

    /* Set clock divider to safe value to switch mode */
    CLOCK_SetSimSafeDivs();

#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
    /* Calculate frdiv */
    if (!APP_GetAvailableFrdiv())
    {
        while (1)
        {
        }
    }
#endif /* FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE || FSL_FEATURE_MCG_USE_PLLREFSEL */

    /* Configure pll */
    if (!APP_GetAvailablePllConfig(&g_pllConfig))
    {
        while (1)
        {
        }
    }

    /* Boot to Pee Mode */
    APP_BootToPeeExample();
    /* Change clock PEE -> PBE ->FBE -> FBI -> BLPI */
    APP_ChangePeeToBlpiExample();
    /* Change clock BLPI -> FBI -> FBE -> PBE -> PEE */
    APP_ChangeBlpiToPeeExample();
    /* Get System clock to blink a LED */
    sysFreq = CORE_CLK_FREQ / 20U;
    /* Enable a LED */
    LED_INIT();
    /* Blink a LED */
    while (1)
    {
        for (i = 0; i < sysFreq; i++)
        {
            __NOP();
        }
        LED_TOGGLE();
    }
}
