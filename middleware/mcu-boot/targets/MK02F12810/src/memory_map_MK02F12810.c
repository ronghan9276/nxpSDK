/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bootloader/bl_context.h"
#include "memory/memory.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Memory map for KV30F128L/K02F128
//!
//! This map is not const because it is updated at runtime with the actual sizes of
//! flash and RAM for the chip we're running on.
memory_map_entry_t g_memoryMap[] = {
    { 0x00000000, 0x0001ffff, kMemoryIsExecutable | kMemoryType_FLASH, &g_flashMemoryInterface },   // Flash array (128KB)
    { 0x1fffe000, 0x20001fff, kMemoryIsExecutable | kMemoryType_RAM, &g_normalMemoryInterface },  // SRAM (16KB)
    { 0x40000000, 0x4007ffff, kMemoryNotExecutable | kMemoryType_Device, &g_deviceMemoryInterface }, // AIPS peripherals
    { 0x400ff000, 0x400fffff, kMemoryNotExecutable | kMemoryType_Device, &g_deviceMemoryInterface }, // GPIO
    { 0xe0000000, 0xe00fffff, kMemoryNotExecutable | kMemoryType_Device, &g_deviceMemoryInterface }, // M4 private peripherals
    { 0 }                                                                       // Terminator
};

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
