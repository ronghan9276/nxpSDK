/*
 * Copyright 2018-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fsl_debug_console.h"
#include "fsl_sd.h"
#include "ff.h"
#include "diskio.h"
#include "fsl_sd_disk.h"


#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "main_cm33.h"
#include "dsp_support.h"
#include "dsp_ipc.h"
#include "cmd.h"
#include "sdmmc_config.h"
#include "dsp_config.h"
#include "fsl_wm8904.h"
#include "fsl_codec_common.h"
#include "fsl_codec_adapter.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SDCARD_SWITCH_VOLTAGE_FUNCTION_EXIST
#define APP_TASK_STACK_SIZE (6 * 1024)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
int BOARD_CODEC_Init(void);
int BOARD_CODEC_Init(void);
static void APP_SDCARD_DetectCallBack(bool isInserted, void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
codec_handle_t g_codecHandle;
wm8904_config_t g_wm8904Config = {
    .i2cConfig          = {.codecI2CInstance = BOARD_CODEC_I2C_INSTANCE},
    .recordSource       = kWM8904_RecordSourceLineInput,
    .recordChannelLeft  = kWM8904_RecordChannelLeft2,
    .recordChannelRight = kWM8904_RecordChannelRight2,
    .playSource         = kWM8904_PlaySourceDAC,
    .slaveAddress       = WM8904_I2C_ADDRESS,
    .protocol           = kWM8904_ProtocolI2S,
    .format             = {.sampleRate = kWM8904_SampleRate48kHz, .bitWidth = kWM8904_BitWidth16},
    .mclk_HZ            = 24576000U,
    .master             = false,
};
codec_config_t g_boardCodecConfig = {.codecDevType = kCODEC_WM8904, .codecDevConfig = &g_wm8904Config};
static app_handle_t app;
/*******************************************************************************
 * Code
 ******************************************************************************/

int BOARD_CODEC_Init(void)
{
    PRINTF("Configure WM8904 codec\r\n");

    if (CODEC_Init(&g_codecHandle, &g_boardCodecConfig) != kStatus_Success)
    {
        PRINTF("WM8904_Init failed!\r\n");
        return -1;
    }

    /* Invert the DAC data in order to output signal with correct polarity - set DACL_DATINV and DACR_DATINV = 1 */
    if (WM8904_WriteRegister((wm8904_handle_t *)g_codecHandle.codecDevHandle, WM8904_AUDIO_IF_0, 0x1850) !=
        kStatus_WM8904_Success)
    {
        PRINTF("WM8904 configuration failed!\r\n");
        return -1;
    }

    /* Initial volume kept at 75% for hearing safety. */
    /* Adjust it to your needs between 0 - 100*/
    if (CODEC_SetVolume(&g_codecHandle, kCODEC_PlayChannelHeadphoneLeft | kCODEC_PlayChannelHeadphoneRight, 75) !=
        kStatus_Success)
    {
        return -1;
    }

    return 0;
}
static void APP_SDCARD_DetectCallBack(bool isInserted, void *userData)
{
    app_handle_t *app = (app_handle_t *)userData;

    app->sdcardInserted = isInserted;
    xSemaphoreGiveFromISR(app->sdcardSem, NULL);
}

void APP_SDCARD_Task(void *param)
{
    const TCHAR driverNumberBuffer[3U] = {SDDISK + '0', ':', '/'};
    FRESULT error;
    app_handle_t *app = (app_handle_t *)param;

    app->sdcardSem = xSemaphoreCreateBinary();

    PRINTF("[APP_SDCARD_Task] start\r\n");

    /* SD host init function */
    if (SD_HostInit(&g_sd) != kStatus_Success)
    {
        PRINTF("[APP_SDCARD_Task] SD host init failed.\r\n");
        vTaskSuspend(NULL);
    }

    /* Small delay for SD card detection logic to process */
    vTaskDelay(100 / portTICK_PERIOD_MS);

    while (1)
    {
        /* Block waiting for SDcard detect interrupt */
        if (xSemaphoreTake(app->sdcardSem, portMAX_DELAY) != pdTRUE)
        {
            PRINTF("Failed to take semaphore.\r\n");
        }

        if (app->sdcardInserted != app->sdcardInsertedPrev)
        {
            app->sdcardInsertedPrev = app->sdcardInserted;

            SD_SetCardPower(&g_sd, false);

            if (app->sdcardInserted)
            {
                /* power on the card */
                SD_SetCardPower(&g_sd, true);
                /* Init card. */
                if (SD_CardInit(&g_sd))
                {
                    PRINTF("[APP_SDCARD_Task] card init failed.\r\n");
                    continue;
                }

                if (f_mount(&app->fileSystem, driverNumberBuffer, 0U))
                {
                    PRINTF("[APP_SDCARD_Task] Mount volume failed.\r\n");
                    continue;
                }

#if (FF_FS_RPATH >= 2U)
                error = f_chdrive((char const *)&driverNumberBuffer[0U]);
                if (error)
                {
                    PRINTF("[APP_SDCARD_Task] Change drive failed.\r\n");
                    continue;
                }
#endif

                PRINTF("[APP_SDCARD_Task] SD card drive mounted\r\n");

                xSemaphoreGive(app->sdcardSem);
            }
        }
    }
}

void handleShellMessage(srtm_message *msg, void *arg)
{
    /* Send message to the DSP */
    dsp_ipc_send_sync(msg);

    /* Wait for response message to be processed before returning to shell. */
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
}

void APP_Shell_Task(void *param)
{
    PRINTF("[APP_Shell_Task] start\r\n");

    /* Handle shell commands.  Return when 'exit' command entered. */
    shellCmd(handleShellMessage, param);

    PRINTF("\r\n[APP_Shell_Task] audio demo end\r\n");
    while (1)
        ;
}

void APP_DSP_IPC_Task(void *param)
{
    srtm_message msg;
    app_handle_t *app = (app_handle_t *)param;

    PRINTF("[APP_DSP_IPC_Task] start\r\n");

    while (1)
    {
        /* Block for IPC message from DSP */
        dsp_ipc_recv_sync(&msg);
        /* Process message */
        handleDSPMessage(app, &msg);
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    int ret;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    CLOCK_EnableClock(kCLOCK_InputMux);

    /* Clear MUA reset before run DSP core */
    RESET_PeripheralReset(kMU_RST_SHIFT_RSTn);

    /* Attach main clock to I3C */
    CLOCK_AttachClk(kMAIN_CLK_to_I3C_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivI3cClk, 4);

    /* attach AUDIO PLL clock to MCLK */
    CLOCK_AttachClk(kAUDIO_PLL_to_MCLK_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivMclkClk, 1);
    SYSCTL1->MCLKPINDIR = SYSCTL1_MCLKPINDIR_MCLKPINDIR_MASK;

    g_wm8904Config.i2cConfig.codecI2CSourceClock = CLOCK_GetI3cClkFreq();
    g_wm8904Config.mclk_HZ                       = CLOCK_GetMclkClkFreq();

    PRINTF("\r\n");
    PRINTF("******************************\r\n");
    PRINTF("DSP audio framework demo start\r\n");
    PRINTF("******************************\r\n");
    PRINTF("\r\n");

    BOARD_SD_Config(&g_sd, APP_SDCARD_DetectCallBack, BOARD_SDMMC_SD_HOST_IRQ_PRIORITY, &app);

    ret = BOARD_CODEC_Init();
    if (ret)
    {
        PRINTF("CODEC_Init failed!\r\n");
        return -1;
    }

    /* Initialize RPMsg IPC interface between ARM and DSP cores. */
    BOARD_DSP_IPC_Init();

    /* Copy DSP image to RAM and start DSP core. */
    BOARD_DSP_Init();

#if DSP_IMAGE_COPY_TO_RAM
    PRINTF("DSP image copied to 0x%x\r\n", DSP_BOOT_ADDRESS);
#endif

    if (xTaskCreate(APP_SDCARD_Task, "SDCard Task", APP_TASK_STACK_SIZE, &app, tskIDLE_PRIORITY + 2, NULL) != pdPASS)
    {
        PRINTF("\r\nFailed to create application task\r\n");
        while (1)
            ;
    }

    /* Set IPC processing task priority = 2 */
    if (xTaskCreate(APP_DSP_IPC_Task, "DSP Msg Task", APP_TASK_STACK_SIZE, &app, tskIDLE_PRIORITY + 2,
                    &app.ipc_task_handle) != pdPASS)
    {
        PRINTF("\r\nFailed to create application task\r\n");
        while (1)
            ;
    }

    /* Set shell command task priority = 1 */
    if (xTaskCreate(APP_Shell_Task, "Shell Task", APP_TASK_STACK_SIZE, &app, tskIDLE_PRIORITY + 1,
                    &app.shell_task_handle) != pdPASS)
    {
        PRINTF("\r\nFailed to create application task\r\n");
        while (1)
            ;
    }

    vTaskStartScheduler();

    /* Shoud not reach this statement. */
    return 0;
}
