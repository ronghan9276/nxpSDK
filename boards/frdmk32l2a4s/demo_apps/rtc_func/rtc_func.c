/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "fsl_rtc.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "fsl_intmux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Set the alarm which will be trigerred x secs later. The alarm trigger
 *        will print a notification on the console.
 *
 * @param offsetSec  Offset seconds is set for alarm.
 */
static void CommandAlarm(uint8_t offsetSec);

/*!
 * @brief Run the digital clock in 20s and show the digital clock on console.
 *
 */
static void CommandSeconds(void);

/*!
 * @brief Get the current date time.
 *
 */
static void CommandGetDatetime(void);

/*!
 * @brief Receive the console input and echo.
 *
 * @param buf  Pointer of buffer.
 * @param size Size of buffer.
 */
static void ReceiveFromConsole(char *buf, uint32_t size);

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint8_t g_AlarmPending = 0U;
volatile bool g_SecsFlag        = false;

static char g_StrMenu[] =
    "\r\n"
    "Please choose the sub demo to run:\r\n"
    "1) Get current date time.\r\n"
    "2) Set current date time.\r\n"
    "3) Alarm trigger show.\r\n"
    "4) Second interrupt show (demo for 20s).\r\n";

static char g_StrNewline[] = "\r\n";
static char g_StrInvalid[] = "Invalid input format\r\n";

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Override the RTC IRQ handler.
 */
void RTC_IRQHandler(void)
{
    uint32_t status = RTC_GetStatusFlags(RTC);

    if (status & kRTC_AlarmFlag)
    {
        g_AlarmPending = 1U;

        /* Clear alarm flag */
        RTC_ClearStatusFlags(RTC, kRTC_AlarmInterruptEnable);
    }
    else if (status & kRTC_TimeInvalidFlag)
    {
        /* Clear timer invalid flag */
        RTC_ClearStatusFlags(RTC, kRTC_TimeInvalidFlag);
    }
    else
    {
    }
}

/*!
 * @brief Override the RTC Second IRQ handler.
 */
void RTC_Seconds_IRQHandler(void)
{
    g_SecsFlag = true;
}


static void CommandAlarm(uint8_t offsetSec)
{
    rtc_datetime_t date;

    RTC_EnableInterrupts(RTC, kRTC_AlarmInterruptEnable);
    if ((offsetSec < 1U) || (offsetSec > 9U))
    {
        PRINTF("Invalid input format\r\n");
        return;
    }
    /* Get date time and add offset*/
    RTC_GetDatetime(RTC, &date);
    date.second += offsetSec;
    if (date.second > 59U)
    {
        date.second -= 60U;
        date.minute += 1U;
        if (date.minute > 59U)
        {
            date.minute -= 60U;
            date.hour += 1U;
            if (date.hour > 23U)
            {
                date.hour -= 24U;
                date.day += 1U;
            }
        }
    }

    /* Set the datetime for alarm */
    if (RTC_SetAlarm(RTC, &date) == kStatus_Success)
    {
        /* Alarm was successfully set, wait for alarm interrupt */
        while (g_AlarmPending == 0U)
        {
        }
    }
    else
    {
        PRINTF("Failed to set alarm. Alarm time is not in the future\r\n");
        return;
    }
    /* Interrupt done */
    RTC_GetDatetime(RTC, &date);
    PRINTF("Triggered Alarm: %02d:%02d:%02d\r\n", date.hour, date.minute, date.second);

    g_AlarmPending = 0U;
    RTC_DisableInterrupts(RTC, kRTC_AlarmInterruptEnable);
}

static void CommandGetDatetime(void)
{
    rtc_datetime_t date;

    RTC_GetDatetime(RTC, &date);
    PRINTF("Current datetime: %04d-%02d-%02d %02d:%02d:%02d\r\n", date.year, date.month, date.day, date.hour,
           date.minute, date.second);
}

static void CommandSeconds(void)
{
    uint32_t count = 0U;
    rtc_datetime_t date;
    char sourceBuff[] = "\r10:10:00";

    g_SecsFlag = false;
    while (count < 20U)
    {
        /* If seconds interrupt ocurred, print new time */
        if (g_SecsFlag)
        {
            /* Build up the word */
            g_SecsFlag = false;
            count++;
            RTC_GetDatetime(RTC, &date);

            sourceBuff[1] = ((date.hour / 10) + 0x30);
            sourceBuff[2] = ((date.hour % 10) + 0x30);
            sourceBuff[3] = ':';
            sourceBuff[4] = ((date.minute / 10) + 0x30);
            sourceBuff[5] = ((date.minute % 10) + 0x30);
            sourceBuff[6] = ':';
            sourceBuff[7] = ((date.second / 10) + 0x30);
            sourceBuff[8] = ((date.second % 10) + 0x30);
            /* Print the time */
            PRINTF(sourceBuff);
        }
    }
    /* Disable Sec interrupt */
    RTC_DisableInterrupts(RTC, kRTC_SecondsInterruptEnable);
    PRINTF(g_StrNewline);
}

static void ReceiveFromConsole(char *buf, uint32_t size)
{
    uint32_t i;

    for (i = 0U; i < size; i++)
    {
        buf[i] = GETCHAR();
        PUTCHAR(buf[i]);
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint8_t index;
    uint8_t secs;
    char recvBuf[20];
    uint32_t result;
    uint16_t year;
    uint16_t month;
    uint16_t day;
    uint16_t hour;
    uint16_t minute;
    uint16_t second;
    rtc_config_t rtcConfig;
    rtc_datetime_t date;

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    INTMUX_Init(INTMUX0);
    INTMUX_EnableInterrupt(INTMUX0, 0, RTC_IRQn);

    /* Init RTC */
    /*
     * rtcConfig.wakeupSelect = false;
     * rtcConfig.updateMode = false;
     * rtcConfig.supervisorAccess = false;
     * rtcConfig.compensationInterval = 0;
     * rtcConfig.compensationTime = 0;
     */
    RTC_GetDefaultConfig(&rtcConfig);
    RTC_Init(RTC, &rtcConfig);
#if (defined(EXAMPLE_CAP_LOAD_VALUE) && EXAMPLE_CAP_LOAD_VALUE)
#if (defined(FSL_FEATURE_RTC_HAS_OSC_SCXP) && FSL_FEATURE_RTC_HAS_OSC_SCXP)
    /* Change the RTC oscillator capacity load value. */
    RTC_SetOscCapLoad(RTC, EXAMPLE_CAP_LOAD_VALUE);
#endif /* FSL_FEATURE_RTC_HAS_OSC_SCXP */
#endif /* EXAMPLE_CAP_LOAD_VALUE */
#if !(defined(FSL_FEATURE_RTC_HAS_NO_CR_OSCE) && FSL_FEATURE_RTC_HAS_NO_CR_OSCE)

    /* Select RTC clock source */
    RTC_SetClockSource(RTC);
#endif /* FSL_FEATURE_RTC_HAS_NO_CR_OSCE */

    /* Set a start date time and start RTC */
    date.year   = 2015U;
    date.month  = 11U;
    date.day    = 11U;
    date.hour   = 11U;
    date.minute = 11U;
    date.second = 11U;

    /* RTC time counter has to be stopped before setting the date & time in the TSR register */
    RTC_StopTimer(RTC);

    /* Enable at the NVIC */
    EnableIRQ(RTC_IRQn);
#ifdef RTC_SECONDS_IRQS
    EnableIRQ(RTC_Seconds_IRQn);
#endif /* RTC_SECONDS_IRQS */

    /* Start the RTC time counter */
    RTC_StartTimer(RTC);

    PRINTF("\r\nRTC Demo running...\r\n");

    /* Start loop */
    while (1)
    {
        /* Print the user information */
        PRINTF(g_StrMenu);
        PRINTF("\r\nSelect:");
        /* Get user input */
        index = GETCHAR();
        PUTCHAR(index);
        PRINTF(g_StrNewline);

        switch (index)
        {
            case '1':
                CommandGetDatetime();
                break;
            case '2':
                PRINTF("Input date time like: \"2010-01-31 17:00:11\"\r\n");
                ReceiveFromConsole(recvBuf, 19U);
                result = sscanf(recvBuf, "%04hd-%02hd-%02hd %02hd:%02hd:%02hd", &year, &month, &day, &hour, &minute,
                                &second);
                PRINTF("%s", g_StrNewline);
                /* Error message will appear when user enters the invalid date time */
                if (result != 6U)
                {
                    PRINTF(g_StrInvalid);
                    break;
                }
                date.year   = (uint16_t)year;
                date.month  = (uint8_t)month;
                date.day    = (uint8_t)day;
                date.hour   = (uint8_t)hour;
                date.minute = (uint8_t)minute;
                date.second = (uint8_t)second;

                /* RTC time counter has to be stopped before setting the date & time in the TSR register */
                RTC_StopTimer(RTC);

                if (kStatus_Success != RTC_SetDatetime(RTC, &date))
                {
                    PRINTF(g_StrInvalid);
                }
                RTC_StartTimer(RTC);

                CommandGetDatetime();
                break;
            case '3':
                PRINTF("Input the alarm seconds from now on (1s~9s):");
                secs = GETCHAR();
                PUTCHAR(secs);
                PRINTF(g_StrNewline);
                secs -= '0';
                CommandAlarm(secs);
                break;
            case '4':
                /* Enable seconds interrupt */
                RTC_EnableInterrupts(RTC, kRTC_SecondsInterruptEnable);
                CommandSeconds();
                break;
            default:
                break;
        }
    }
}
