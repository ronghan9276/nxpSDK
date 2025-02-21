/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_rdc.h"

/******************************************************************************
 * Definitions
 *****************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.rdc"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get instance number for RDC module.
 *
 * @param base RDC peripheral base address.
 */
uint32_t RDC_GetInstance(RDC_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Pointers to rdc bases for each instance. */
static RDC_Type *const s_rdcBases[] = RDC_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to rdc clocks for each instance. */
static const clock_ip_name_t s_rdcClocks[] = RDC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/******************************************************************************
 * CODE
 *****************************************************************************/

uint32_t RDC_GetInstance(RDC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_rdcBases); instance++)
    {
        if (s_rdcBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_rdcBases));

    return instance;
}

/*!
 * brief Initializes the RDC module.
 *
 * This function enables the RDC clock.
 *
 * param base RDC peripheral base address.
 */
void RDC_Init(RDC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(s_rdcClocks[RDC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief De-initializes the RDC module.
 *
 * This function disables the RDC clock.
 *
 * param base RDC peripheral base address.
 */
void RDC_Deinit(RDC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(s_rdcClocks[RDC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Set peripheral access policy.
 *
 * param base RDC peripheral base address.
 * param config Pointer to the policy configuration.
 */
void RDC_SetPeriphAccessConfig(RDC_Type *base, const rdc_periph_access_config_t *config)
{
    assert(config->periph < RDC_PDAP_COUNT);

    uint32_t periph  = config->periph;
    uint32_t regPDAP = config->policy;

    if (config->lock)
    {
        regPDAP |= RDC_PDAP_LCK_MASK;
    }

    if (config->enableSema)
    {
        regPDAP |= RDC_PDAP_SREQ_MASK;
    }

    base->PDAP[periph] = regPDAP;
}

/*!
 * brief Get default peripheral access policy.
 *
 * The default configuration is:
 * code
    config->lock = false;
    config->enableSema = false;
    config->policy = RDC_ACCESS_POLICY(0, kRDC_ReadWrite) |
                     RDC_ACCESS_POLICY(1, kRDC_ReadWrite) |
                     RDC_ACCESS_POLICY(2, kRDC_ReadWrite) |
                     RDC_ACCESS_POLICY(3, kRDC_ReadWrite);
   endcode
 *
 * param config Pointer to the policy configuration.
 */
void RDC_GetDefaultPeriphAccessConfig(rdc_periph_access_config_t *config)
{
    assert(config);

    /* Initializes the configure structure to zero. */
    memset(config, 0, sizeof(*config));

    config->lock       = false;
    config->enableSema = false;
    config->policy     = RDC_ACCESS_POLICY(0, kRDC_ReadWrite) | RDC_ACCESS_POLICY(1, kRDC_ReadWrite) |
                     RDC_ACCESS_POLICY(2, kRDC_ReadWrite) | RDC_ACCESS_POLICY(3, kRDC_ReadWrite);
}

/*!
 * brief Set memory region access policy.
 *
 * Note that when setting the baseAddress and endAddress in p config,
 * should be aligned to the region resolution, see rdc_mem_t
 * definitions.
 *
 * param base RDC peripheral base address.
 * param config Pointer to the policy configuration.
 */
void RDC_SetMemAccessConfig(RDC_Type *base, const rdc_mem_access_config_t *config)
{
    assert(config->mem < RDC_MRC_COUNT);

    uint32_t mem = config->mem;
    /* The configuration is enabled by default. */
    uint32_t regMRC = config->policy | RDC_MRC_ENA_MASK;

    if (config->lock)
    {
        regMRC |= RDC_MRC_LCK_MASK;
    }

    base->MR[mem].MRSA = config->baseAddress;
    base->MR[mem].MREA = config->endAddress;
    base->MR[mem].MRC  = regMRC;
}

/*!
 * brief Get default memory region access policy.
 *
 * The default configuration is:
 * code
    config->lock = false;
    config->baseAddress = 0;
    config->endAddress = 0;
    config->policy = RDC_ACCESS_POLICY(0, kRDC_ReadWrite) |
                     RDC_ACCESS_POLICY(1, kRDC_ReadWrite) |
                     RDC_ACCESS_POLICY(2, kRDC_ReadWrite) |
                     RDC_ACCESS_POLICY(3, kRDC_ReadWrite);
   endcode
 *
 * param config Pointer to the policy configuration.
 */
void RDC_GetDefaultMemAccessConfig(rdc_mem_access_config_t *config)
{
    assert(config);

    /* Initializes the configure structure to zero. */
    memset(config, 0, sizeof(*config));

    config->lock        = false;
    config->baseAddress = 0;
    config->endAddress  = 0;
    config->policy      = RDC_ACCESS_POLICY(0, kRDC_ReadWrite) | RDC_ACCESS_POLICY(1, kRDC_ReadWrite) |
                     RDC_ACCESS_POLICY(2, kRDC_ReadWrite) | RDC_ACCESS_POLICY(3, kRDC_ReadWrite);
}

/*!
 * brief Get the memory region violation status.
 *
 * The first access violation is captured. Subsequent violations are ignored
 * until the status register is cleared. Contents are cleared upon reading the
 * register. Clearing of contents occurs only when the status is read by the
 * memory region's associated domain ID(s).
 *
 * param base RDC peripheral base address.
 * param mem Which memory region to get.
 * param status The returned status.
 */
void RDC_GetMemViolationStatus(RDC_Type *base, rdc_mem_t mem, rdc_mem_status_t *status)
{
    assert(mem < RDC_MRC_COUNT);

    uint32_t regMRVS = base->MR[mem].MRVS;

    status->hasViolation = (regMRVS & RDC_MRVS_AD_MASK);
    status->domainID     = (regMRVS & RDC_MRVS_VDID_MASK) >> RDC_MRVS_VDID_SHIFT;
    status->address      = (regMRVS & RDC_MRVS_VADR_MASK);
}
