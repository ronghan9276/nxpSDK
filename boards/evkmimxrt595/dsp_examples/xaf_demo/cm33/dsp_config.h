/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _DSP_CONFIG_H_
#define _DSP_CONFIG_H_

#define DSP_EPT_ADDR (30)
#define MCU_EPT_ADDR (40)

/* Address of RAM, where the image for DSP should be copied */
/* These addresses are accessed by the ARM core and aliased to M33 code memory */
#define DSP_BOOT_ADDRESS (uint32_t *)0x00400000
#define DSP_SRAM_ADDRESS (uint32_t *)0x00300000

/* Inter processor communication common RAM */
/* This address is accessed by both cores, and aliased to M33 data memory */
#define RPMSG_LITE_LINK_ID    (RL_PLATFORM_IMXRT500_LINK_ID)
#define RPMSG_LITE_SHMEM_BASE (void *)0x20070000
#define RPMSG_LITE_SHMEM_SIZE (64 * 1024)

/* DSP-private uncached audio memory buffers */
/* Each buffer is 32k in size in a separate SRAM partition */
/* These addresses are accessed by the DSP core and aliased to DSP data memory */
#define DSP_AUDIO_BUFFER_1_PING (0x00800000)
#define DSP_AUDIO_BUFFER_1_PONG (0x00808000)
#define DSP_AUDIO_BUFFER_2_PING (0x00810000)
#define DSP_AUDIO_BUFFER_2_PONG (0x00818000)

/* Audio ping/pong buffers for streaming DSP handling.
 * Assign each buffer to distinct shared RAM partition to maximize performance. */
/* These addresses are accessed by the M33 core and aliased to M33 data memory */
#define AUDIO_SHARED_BUFFER_1      0x20020000
#define AUDIO_SHARED_BUFFER_1_SIZE (128 * 1024)
#define AUDIO_SHARED_BUFFER_2      0x20040000
#define AUDIO_SHARED_BUFFER_2_SIZE (128 * 1024)

#define AUDIO_I2S_CAPTURER_DEVICE 5
#define AUDIO_I2S_RENDERER_DEVICE 1

#endif
