/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _EMWIN_SUPPORT_H_
#define _EMWIN_SUPPORT_H_

#define BOARD_LCD_SPI          Driver_SPI5
#define BOARD_LCD_SPI_BAUDRATE 10000000U /*! Transfer baudrate */
#define BOARD_LCD_SPI_IRQ      FLEXCOMM5_IRQn

#define BOARD_LCD_DC_GPIO      GPIO /*! LCD data/command base */
#define BOARD_LCD_DC_GPIO_PORT 1U   /*! LCD data/command port */
#define BOARD_LCD_DC_GPIO_PIN  7U   /*! LCD data/command pin */

#define BOARD_LCD_READABLE 0

#define LCD_WIDTH  320
#define LCD_HEIGHT 240

#define BOARD_TOUCH_I2C     Driver_I2C2
#define BOARD_TOUCH_I2C_IRQ FLEXCOMM2_IRQn

#define GUI_NUMBYTES 0x8000 /*! Amount of memory assigned to the emWin library */

extern int BOARD_Touch_Poll(void);

#endif
