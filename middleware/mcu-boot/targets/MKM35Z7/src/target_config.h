/*
 * Copyright 2020-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if !defined(__TARGET_CONFIG_H__)
#define __TARGET_CONFIG_H__

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
#define SIM_UIDH_UID SIM_UIDH_UID127_96
#define SIM_UIDMH_UID SIM_UIDMH_UID95_64
#define SIM_UIDML_UID SIM_UIDML_UID63_32
#define SIM_UIDL_UID SIM_UIDL_UID31_0

//! @brief Constants for clock frequencies.
enum _target_clocks
{
    kDefaultClock = 20971520u,
    kHIRC = 4000000u,
    kMinCoreClockWithUsbSupport = 20000000u,
    kMaxCoreClock = 75000000u,
    kMaxBusClock = 25000000u,
    kMaxFlashClock = 25000000u,

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
enum _sram_partition
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

#endif // __TARGET_CONFIG_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
