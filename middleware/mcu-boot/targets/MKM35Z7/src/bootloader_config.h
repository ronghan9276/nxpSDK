/*
 * Copyright (c) 2014-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __BOOTLOADER_CONFIG_H__
#define __BOOTLOADER_CONFIG_H__

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//
// Bootloader configuration options
//

#if (defined(__GNUC__) && defined(BL_TARGET_RAM))
#ifdef DEBUG
#undef DEBUG
#define NDEBUG
#endif
#endif

//! @name Peripheral configuration macros
//@{
#if !defined(BL_CONFIG_UART_2)
#define BL_CONFIG_UART_2 (1)
#endif

#if !defined(BL_CONFIG_I2C_0)
#define BL_CONFIG_I2C_0 (1)
#endif
#if !defined(BL_CONFIG_SPI_1)
#define BL_CONFIG_SPI_1 (1)
#endif

#define BL_CONFIG_UART (BL_CONFIG_UART_2)
#define BL_CONFIG_SPI (BL_CONFIG_SPI_1)
#define BL_CONFIG_I2C (BL_CONFIG_I2C_0)
//@}

#if !defined(BL_TARGET_FLASH) && !defined(BL_TARGET_RAM)
#define BL_TARGET_FLASH (1)
#endif

// Determines whether to support Kinetis C90TFS FTFx flash
#define BL_FLASH_TYPE_KINETIS_C90TFS_FLASH (1)
#define BL_FEATURE_FLASH_CHECK_CUMULATIVE_WRITE (1)

#if defined(BL_TARGET_RAM)
#define BL_FEATURE_FLASH_SECURITY (0)
#else
#define BL_FEATURE_FLASH_SECURITY (1)
#endif

#if !defined(BL_TARGET_RAM)
#define BL_FEATURE_CRC_CHECK (1)
#endif

#define BL_FEATURE_FILL_MEMORY (1)
#define BL_FEATURE_READ_MEMORY (1)

#define BL_FEATURE_QSPI_MODULE (0)
#define BL_FEATURE_ENCRYPTION (0)

#define BL_FEATURE_UART_AUTOBAUD_IRQ (1)

// Bootloader peripheral detection default timeout in milliseconds
// After coming out of reset the bootloader will spin in a peripheral detection
// loop for this amount of time. A zero value means no time out.
#if DEBUG
#define BL_DEFAULT_PERIPHERAL_DETECT_TIMEOUT 10000
#else
#define BL_DEFAULT_PERIPHERAL_DETECT_TIMEOUT 5000
#endif // DEBUG

#define BL_FEATURE_POWERDOWN (0)

// Bootloader powerdown timeout in milliseconds
// The bootloader enters a low power mode after waiting for this amount of time. A zero value means // no time out. Only
// applicable if BL_FEATURE_POWERDOWN is enabled.
#if DEBUG
#define BL_DEFAULT_POWERDOWN_TIMEOUT 10000
#else
#define BL_DEFAULT_POWERDOWN_TIMEOUT 600000
#endif // DEBUG

// The bootloader will check this address for the application vector table upon startup.
#if !defined(BL_APP_VECTOR_TABLE_ADDRESS)
#define BL_APP_VECTOR_TABLE_ADDRESS 0xa000
#endif

#endif // __BOOTLOADER_CONFIG_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
