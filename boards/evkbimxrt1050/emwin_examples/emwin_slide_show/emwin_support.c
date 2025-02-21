/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "GUI.h"
#include "WM.h"
#include "emwin_support.h"
#include "GUIDRV_Lin.h"

#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_video_common.h"
#include "fsl_elcdif.h"
#include "fsl_lpi2c.h"
#include "fsl_gpio.h"
#if (DEMO_PANEL == DEMO_PANEL_RK043FN66HS)
#include "fsl_gt911.h"
#else
#include "fsl_ft5406_rt.h"
#endif
#include "fsl_gpt.h"

uint32_t s_gui_memory[GUI_NUMBYTES];
uint32_t s_vram_buffer[VRAM_SIZE * GUI_BUFFERS];

/* Memory address definitions */
#define GUI_MEMORY_ADDR ((uint32_t)s_gui_memory)
#define VRAM_ADDR       (SDK_SIZEALIGN(s_vram_buffer, FRAME_BUFFER_ALIGN))

static volatile int32_t s_LCDpendingBuffer = -1;

#if (DEMO_PANEL == DEMO_PANEL_RK043FN66HS)
static void BOARD_PullTouchResetPin(bool pullUp);
static void BOARD_ConfigTouchIntPin(gt911_int_pin_mode_t mode);
#endif

/*******************************************************************************
 * Implementation of PortAPI for emWin LCD driver
 ******************************************************************************/

/* Enable interrupt. */
void BOARD_EnableLcdInterrupt(void)
{
    EnableIRQ(LCDIF_IRQn);
}

void APP_LCDIF_IRQHandler(void)
{
    uint32_t intStatus;

    intStatus = ELCDIF_GetInterruptStatus(APP_ELCDIF);

    ELCDIF_ClearInterruptStatus(APP_ELCDIF, intStatus);

    if (intStatus & kELCDIF_CurFrameDone)
    {
        if (s_LCDpendingBuffer >= 0)
        {
            /* Send a confirmation that the given buffer is visible */
            GUI_MULTIBUF_Confirm(s_LCDpendingBuffer);
            s_LCDpendingBuffer = -1;
        }
    }
    SDK_ISR_EXIT_BARRIER;
}

void LCDIF_IRQHandler(void)
{
    APP_LCDIF_IRQHandler();
}

void APP_ELCDIF_Init(void)
{
    const elcdif_rgb_mode_config_t config = {
        .panelWidth    = APP_IMG_WIDTH,
        .panelHeight   = APP_IMG_HEIGHT,
        .hsw           = APP_HSW,
        .hfp           = APP_HFP,
        .hbp           = APP_HBP,
        .vsw           = APP_VSW,
        .vfp           = APP_VFP,
        .vbp           = APP_VBP,
        .polarityFlags = APP_POL_FLAGS,
        .bufferAddr    = VRAM_ADDR,
        .pixelFormat   = ELCDIF_PIXEL_FORMAT,
        .dataBus       = APP_LCDIF_DATA_BUS,
    };
    ELCDIF_RgbModeInit(APP_ELCDIF, &config);

    BOARD_EnableLcdInterrupt();
    ELCDIF_EnableInterrupts(APP_ELCDIF, kELCDIF_CurFrameDoneInterruptEnable);
    NVIC_EnableIRQ(LCDIF_IRQn);
    ELCDIF_RgbModeStart(APP_ELCDIF);
}

/*******************************************************************************
 * Implementation of communication with the touch controller
 ******************************************************************************/

/* Touch driver handle. */
#if (DEMO_PANEL == DEMO_PANEL_RK043FN66HS)
static gt911_handle_t s_touchHandle;
static const gt911_config_t s_touchConfig = {
    .I2C_SendFunc     = BOARD_Touch_I2C_Send,
    .I2C_ReceiveFunc  = BOARD_Touch_I2C_Receive,
    .pullResetPinFunc = BOARD_PullTouchResetPin,
    .intPinFunc       = BOARD_ConfigTouchIntPin,
    .timeDelayMsFunc  = VIDEO_DelayMs,
    .touchPointNum    = 1,
    .i2cAddrMode      = kGT911_I2cAddrMode0,
    .intTrigMode      = kGT911_IntRisingEdge,
};

#else
static ft5406_rt_handle_t touchHandle;
#endif

#if (DEMO_PANEL == DEMO_PANEL_RK043FN66HS)
static void BOARD_PullTouchResetPin(bool pullUp)
{
    if (pullUp)
    {
        GPIO_PinWrite(BOARD_TOUCH_RST_GPIO, BOARD_TOUCH_RST_PIN, 1);
    }
    else
    {
        GPIO_PinWrite(BOARD_TOUCH_RST_GPIO, BOARD_TOUCH_RST_PIN, 0);
    }
}

static void BOARD_ConfigTouchIntPin(gt911_int_pin_mode_t mode)
{
    if (mode == kGT911_IntPinInput)
    {
        BOARD_TOUCH_INT_GPIO->GDIR &= ~(1UL << BOARD_TOUCH_INT_PIN);
    }
    else
    {
        if (mode == kGT911_IntPinPullDown)
        {
            GPIO_PinWrite(BOARD_TOUCH_INT_GPIO, BOARD_TOUCH_INT_PIN, 0);
        }
        else
        {
            GPIO_PinWrite(BOARD_TOUCH_INT_GPIO, BOARD_TOUCH_INT_PIN, 1);
        }

        BOARD_TOUCH_INT_GPIO->GDIR |= (1UL << BOARD_TOUCH_INT_PIN);
    }
}
#endif

static void BOARD_Touch_Init(void)
{
    lpi2c_master_config_t masterConfig = {0};
    /*
     * masterConfig.debugEnable = false;
     * masterConfig.ignoreAck = false;
     * masterConfig.pinConfig = kLPI2C_2PinOpenDrain;
     * masterConfig.baudRate_Hz = 100000U;
     * masterConfig.busIdleTimeout_ns = 0;
     * masterConfig.pinLowTimeout_ns = 0;
     * masterConfig.sdaGlitchFilterWidth_ns = 0;
     * masterConfig.sclGlitchFilterWidth_ns = 0;
     */
    LPI2C_MasterGetDefaultConfig(&masterConfig);

    /* Change the default baudrate configuration */
    masterConfig.baudRate_Hz = BOARD_TOUCH_I2C_BAUDRATE;

    /* Initialize the LPI2C master peripheral */
    LPI2C_MasterInit(BOARD_TOUCH_I2C, &masterConfig, BOARD_TOUCH_I2C_CLOCK_FREQ);

    /* Initialize the touch handle. */
#if (DEMO_PANEL == DEMO_PANEL_RK043FN66HS)
    GT911_Init(&s_touchHandle, &s_touchConfig);
#else
    FT5406_RT_Init(&touchHandle, BOARD_TOUCH_I2C);
#endif
}

void BOARD_Touch_Deinit(void)
{
    LPI2C_MasterDeinit(BOARD_TOUCH_I2C);
}

int BOARD_Touch_Poll(void)
{
#if (DEMO_PANEL == DEMO_PANEL_RK043FN02H)
    touch_event_t touch_event;
#endif
    int touch_x;
    int touch_y;
    static GUI_PID_STATE pid_state;
    pid_state.Layer = 0;

#if (DEMO_PANEL == DEMO_PANEL_RK043FN66HS)
    status_t st = GT911_GetSingleTouch(&s_touchHandle, &touch_x, &touch_y);
    if ((st == kStatus_Success) || (st == kStatus_TOUCHPANEL_NotTouched))
    {
        if (st == kStatus_Success)
        {
            pid_state.x = touch_x;
            pid_state.y = touch_y;
        }
        pid_state.Pressed = (st == kStatus_Success);
        GUI_TOUCH_StoreStateEx(&pid_state);
    }
#else
    if (kStatus_Success == FT5406_RT_GetSingleTouch(&touchHandle, &touch_event, &touch_x, &touch_y))
    {
        if ((touch_event == kTouch_Contact) || (touch_event == kTouch_Up))
        {
            if (touch_event == kTouch_Contact)
            {
                pid_state.x = touch_y;
                pid_state.y = touch_x;
            }
            pid_state.Pressed = (touch_event == kTouch_Contact);
            GUI_TOUCH_StoreStateEx(&pid_state);
        }
    }
#endif
    return 1;
}

/*********************************************************************
 *
 *       _ClearCache
 */
static void _ClearCache(U32 v)
{
    GUI_USE_PARA(v);
    SCB_CleanInvalidateDCache();
}

/*******************************************************************************
 * Application implemented functions required by emWin library
 ******************************************************************************/
void LCD_X_Config(void)
{
    GUI_MULTIBUF_Config(GUI_BUFFERS);
    GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
    LCD_SetSizeEx(0, LCD_WIDTH, LCD_HEIGHT);
    LCD_SetVSizeEx(0, LCD_WIDTH, LCD_HEIGHT);
    LCD_SetVRAMAddrEx(0, (void *)VRAM_ADDR);
    BOARD_Touch_Init();
    GUI_DCACHE_SetClearCacheHook(_ClearCache);
}

int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void *p)
{
    GUI_USE_PARA(LayerIndex);

    uint32_t addr;
    int result = 0;
    LCD_X_SHOWBUFFER_INFO *pData;
    switch (Cmd)
    {
        case LCD_X_INITCONTROLLER:
        {
            APP_ELCDIF_Init();
            break;
        }
        case LCD_X_SHOWBUFFER:
        {
            pData = (LCD_X_SHOWBUFFER_INFO *)p;
            /* Calculate address of the given buffer */
            addr = VRAM_ADDR + VRAM_SIZE * pData->Index;
            /* Make the given buffer visible */
            ELCDIF_SetNextBufferAddr(APP_ELCDIF, addr);
            //
            // Remember buffer index to be used by ISR
            //
            s_LCDpendingBuffer = pData->Index;
            while (s_LCDpendingBuffer >= 0)
                ;
            return 0;
        }
        default:
            result = -1;
            break;
    }

    return result;
}

void GUI_X_Config(void)
{
    /* Assign work memory area to emWin */
    GUI_ALLOC_AssignMemory((void *)GUI_MEMORY_ADDR, GUI_NUMBYTES);

    /* Select default font */
    GUI_SetDefaultFont(GUI_FONT_6X8);
}

void GUI_X_Init(void)
{
}

/* Dummy RTOS stub required by emWin */
void GUI_X_InitOS(void)
{
}

/* Dummy RTOS stub required by emWin */
void GUI_X_Lock(void)
{
}

/* Dummy RTOS stub required by emWin */
void GUI_X_Unlock(void)
{
}

/* Dummy RTOS stub required by emWin */
U32 GUI_X_GetTaskId(void)
{
    return 0;
}

void GUI_X_ExecIdle(void)
{
    GUI_X_Delay(1);
}

GUI_TIMER_TIME GUI_X_GetTime(void)
{
    return GPT_GetCurrentTimerCount(EXAMPLE_GPT) / EXAMPLE_GPT_TICK_TO_MS;
}

void GUI_X_Delay(int Period)
{
    volatile uint32_t tNow = GPT_GetCurrentTimerCount(EXAMPLE_GPT);
    while ((GPT_GetCurrentTimerCount(EXAMPLE_GPT) - tNow) < Period * EXAMPLE_GPT_TICK_TO_MS)
        ;
}

void *emWin_memcpy(void *pDst, const void *pSrc, long size)
{
    return memcpy(pDst, pSrc, size);
}
