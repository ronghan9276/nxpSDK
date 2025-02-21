/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if !defined(__TARGET_CONFIG_H__)
#define __TARGET_CONFIG_H__

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

typedef enum _clock_soruce_enum
{
    kClockSource_SystemOSC = 1u,
    kClockSource_SlowIRC = 2u,
    kClockSource_FastIRC = 3u,
    kClockSource_LPFLL = 6u,
} clock_source_type_t;

enum
{
    kFIRC48M = 48000000ul,
    kIRC8M = 8000000ul,
    kIRC2M = 2000000ul,

};

//! @brief Constants for clock frequencies.
enum _target_clocks
{

    //! The core clock cannot go above 48MHz.
    kMaxCoreClock = 480000000u,
    //! The bus clock cannot go above 24MHz.
    kMaxBusClock = 24000000u,
    //! The flash clock cannot go above 24MHz
    kMaxFlashClock = 24000000u,

    kDivider_Min = 1,
    kDivider_Max = 16,
};

//! @brief Memory Map index constants
enum
{
    kIndexFlashArray = 0,
    kIndexSRAM = 1,
    kSRAMSeparatrix = (uint32_t)0x20000000 //!< This value is the start address of SRAM_U
};

//! @brief Constants for sram partition
enum
{
    kSram_LowerPart = 1,
    kSram_UpperPart = 3,
};

//! @brief Version constants for the target.
enum _target_version_constants
{
    kTarget_Version_Name = 'T',
    kTarget_Version_Major = 1,
    kTarget_Version_Minor = 0,
    kTarget_Version_Bugfix = 0
};

#define kSIM_SDID_RAMSIZE_32KB 0x6
#define kSIM_SDID_RAMSIZE_48KB 0x7
#define kRAM_SIZE_32KB   (0x8000U)
#define kRAM_SIZE_48KB   (0xC000U)

#define kSIM_FCFG1_PFSIZE_128KB 0x7
#define kSIM_FCFG1_PFSIZE_256KB 0x9

#define kFLASH_SIZE_256KB   (0x40000U)
#define kFLASH_SIZE_128KB   (0x20000U)

//! CRC check pinmux configurations
// Note: This default muxing slot of selected crc check failure pin must be ALT0
#define CRC_CHECK_FAILURE_PIN_NUMBER 1
#define CRC_CHECK_FAILURE_PIN_PORT PORTD
#define CRC_CHECK_FAILURE_PIN_GPIO GPIOD
#define CRC_CHECK_FAILURE_PIN_DEFAULT_MODE 0
#define CRC_CHECK_FAILURE_PIN_GPIO_MODE 1

#define SIM_SDID_SRAMSIZE_MASK SIM_SDID_RAMSIZE_MASK
#define SIM_SDID_SRAMSIZE_SHIFT SIM_SDID_RAMSIZE_SHIFT

#endif // __TARGET_CONFIG_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
