/*
* Copyright (c) 2014-2015 Freescale Semiconductor, Inc.
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

//! @name Peripheral configuration macros
//@{

#if !defined(BL_CONFIG_SCUART)
#define BL_CONFIG_SCUART (1)
#endif
#if !defined(BL_CONFIG_I2C)
#define BL_CONFIG_I2C (1)
#endif
#if !defined(BL_CONFIG_DSPI)
#define BL_CONFIG_DSPI (1)
#endif

/* Either FS USB or HS USB to be enabled, not both are enabled at the same time.
 * HS USB is not supported in flashloader build, due to extral dependence.     */
#if !defined(BL_CONFIG_USB_HID)
#define BL_CONFIG_USB_HID (1)
#endif
#if !defined(BL_CONFIG_USB_MSC)
#define BL_CONFIG_USB_MSC (0)
#endif

#if !defined(BL_CONFIG_HS_USB_HID)
#define BL_CONFIG_HS_USB_HID (0) // For TOWER and FRDM boards
#endif
#if !defined(BL_CONFIG_HS_USB_MSC)
#define BL_CONFIG_HS_USB_MSC (0) // For TOWER and FRDM boards
#endif
//@}

#if !defined(BL_TARGET_FLASH) && !defined(BL_TARGET_RAM)
#define BL_TARGET_FLASH (1)
#endif

#if defined(BL_TARGET_RAM)
#define BL_FEATURE_FLASH_SECURITY (0)
#else
#define BL_FEATURE_FLASH_SECURITY (1)
#endif

#if !defined(BL_TARGET_RAM)
#define BL_FEATURE_CRC_CHECK (1)
#endif

#define BL_FEATURE_QSPI_MODULE (0)

#define BL_FEATURE_ENCRYPTION_MMCAU (1)
#define BL_FEATURE_ENCRYPTION (BL_FEATURE_ENCRYPTION_MMCAU)
#define BL_FEATURE_ENCRYPTION_KEY_ADDRESS 0xb000 // NOTE: this address must be 4-byte aligned.

#define BL_FEATURE_UART_AUTOBAUD_IRQ (1)

// Bootloader peripheral detection default timeout in milliseconds
// After coming out of reset the bootloader will spin in a peripheral detection
// loop for this amount of time. A zero value means no time out.
#if DEBUG
#define BL_DEFAULT_PERIPHERAL_DETECT_TIMEOUT 0
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

/* Backup application Info */
#if !defined(BL_TARGET_RAM)
#define BL_FEATURE_RELIABLE_UPDATE (1)
#define BL_FEATURE_HARDWARE_SWAP_UPDATE (1)
// Note the BAKCUP APP START address must be sector-aligned.
#define BL_BACKUP_APP_START (0x105000)
#endif // BL_TARGET_RAM

#define BL_FEATURE_ENABLE_FLASH_PROGRAM_SECTION (1)

#endif // __BOOTLOADER_CONFIG_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
