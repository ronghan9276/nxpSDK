/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "milliseconds_delay.h"
#include "pin_mux.h"

#if TOWER
#define LED1_OFFSET 7
#define LED2_OFFSET 19
#define LED3_OFFSET 0
#define LED4_OFFSET 1

#define DELAY_1MS (1000)
#define LED_COUNT 4

static uint8_t led_offset[LED_COUNT] = { LED1_OFFSET, LED2_OFFSET, LED3_OFFSET, LED4_OFFSET };
static PORT_Type *led_port[LED_COUNT] = { PORTD, PORTB, PORTE, PORTE };
static GPIO_Type *led_gpio[LED_COUNT] = { GPIOD, GPIOB, GPIOE, GPIOE };
#endif // TOWER

#if FREEDOM
#define LED1_OFFSET 1
#define LED2_OFFSET 7
#define LED3_OFFSET 25

#define DELAY_1MS (1000)
#define LED_COUNT 3

static uint8_t led_offset[LED_COUNT] = { LED1_OFFSET, LED2_OFFSET, LED3_OFFSET };
static PORT_Type *led_port[LED_COUNT] = { PORTD, PORTD, PORTE };
static GPIO_Type *led_gpio[LED_COUNT] = { GPIOD, GPIOD, GPIOE };
#endif // FREEDOM

static void led_toggle(uint32_t leds)
{
    uint8_t i = 0;
    // led OFF
    for (i = 0; i < LED_COUNT; i++)
    {
        led_gpio[i]->PDOR |= (uint32_t)(1 << led_offset[i]);
    }
    // led ON
    led_gpio[leds]->PDOR &= (uint32_t) ~(1 << led_offset[leds]);
}

void delay(void)
{
    volatile uint32_t delayTicks = 2000000;

    while (delayTicks--)
    {
        __ASM("nop");
    }
}

int main(void)
{
    BOARD_InitBootPins();
    // Note: for ROM development, use this version of delay function,
    // Which is in order to test if the VTCOR is correct.
    milliseconds_delay_init();
    uint32_t leds = 0;
    while (1)
    {
        led_toggle(leds);
        milliseconds_delay(DELAY_1MS);

        ++leds;
        if (leds == LED_COUNT)
        {
            leds = 0;
        }
    }
}
