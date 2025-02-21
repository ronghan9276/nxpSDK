/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __FSL_DEVICE_REGISTERS_H__
#define __FSL_DEVICE_REGISTERS_H__

/*
 * Include the cpu specific register header files.
 *
 * The CPU macro should be declared in the project or makefile.
 */
#if (defined(CPU_MKL17Z128VFM4) || defined(CPU_MKL17Z128VFT4) || defined(CPU_MKL17Z128VLH4) || \
    defined(CPU_MKL17Z128VMP4) || defined(CPU_MKL17Z256CAL4R) || defined(CPU_MKL17Z256VFM4) || \
    defined(CPU_MKL17Z256VFT4) || defined(CPU_MKL17Z256VLH4) || defined(CPU_MKL17Z256VMP4))

#define KL17Z4_SERIES

/* CMSIS-style register definitions */
#include "MKL17Z4.h"
/* CPU specific feature definitions */
#include "MKL17Z4_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
