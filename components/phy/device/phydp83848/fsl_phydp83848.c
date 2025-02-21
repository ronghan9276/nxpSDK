/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_phydp83848.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines the timeout macro. */
#define PHY_TIMEOUT_COUNT 0x3FFFFFFU

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
const phy_operations_t phydp83848_ops = {.phyInit            = PHY_DP83848_Init,
                                         .phyWrite           = PHY_DP83848_Write,
                                         .phyRead            = PHY_DP83848_Read,
                                         .getLinkStatus      = PHY_DP83848_GetLinkStatus,
                                         .getLinkSpeedDuplex = PHY_DP83848_GetLinkSpeedDuplex,
                                         .enableLoopback     = PHY_DP83848_EnableLoopback};

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t PHY_DP83848_Init(phy_handle_t *handle, const phy_config_t *config)
{
    uint32_t bssReg;
    uint32_t counter = PHY_TIMEOUT_COUNT;
    uint32_t idReg   = 0;
    status_t result  = kStatus_Success;
    uint32_t timeDelay;
    uint32_t ctlReg = 0;

    /* Init MDIO interface. */
    MDIO_Init(handle->mdioHandle);

    /* assign phy address. */
    handle->phyAddr = config->phyAddr;

    /* Initialization after PHY stars to work. */
    while ((idReg != PHY_CONTROL_ID1) && (counter != 0))
    {
        MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_ID1_REG, &idReg);
        counter--;
    }

    if (!counter)
    {
        return kStatus_Fail;
    }

    /* Reset PHY. */
    counter = PHY_TIMEOUT_COUNT;
    result  = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (result == kStatus_Success)
    {

        /* Set the negotiation. */
        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_AUTONEG_ADVERTISE_REG,
                            (PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK |
                             PHY_10BASETX_FULLDUPLEX_MASK | PHY_10BASETX_HALFDUPLEX_MASK | 0x1U));
        if (result == kStatus_Success)
        {
            result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG,
                                (PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
            if (result == kStatus_Success)
            {
                /* Check auto negotiation complete. */
                while (counter--)
                {
                    result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_BASICSTATUS_REG, &bssReg);
                    if (result == kStatus_Success)
                    {
                        MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_STATUS_REG, &ctlReg);
                        if (((bssReg & PHY_BSTATUS_AUTONEGCOMP_MASK) != 0) && (ctlReg & PHY_LINK_READY_MASK))
                        {
                            /* Wait a moment for Phy status stable. */
                            for (timeDelay = 0; timeDelay < PHY_TIMEOUT_COUNT; timeDelay++)
                            {
                                __ASM("nop");
                            }
                            break;
                        }
                    }

                    if (!counter)
                    {
                        return kStatus_PHY_AutoNegotiateFail;
                    }
                }
            }
        }
    }

    return result;
}

status_t PHY_DP83848_Write(phy_handle_t *handle, uint32_t phyReg, uint32_t data)
{
    return MDIO_Write(handle->mdioHandle, handle->phyAddr, phyReg, data);
}

status_t PHY_DP83848_Read(phy_handle_t *handle, uint32_t phyReg, uint32_t *dataPtr)
{
    return MDIO_Read(handle->mdioHandle, handle->phyAddr, phyReg, dataPtr);
}

status_t PHY_DP83848_EnableLoopback(phy_handle_t *handle, phy_loop_t mode, phy_speed_t speed, bool enable)
{
    status_t result;
    uint32_t data = 0;

    /* Set the loop mode. */
    if (enable)
    {
        if (mode == kPHY_LocalLoop)
        {
            if (speed == kPHY_Speed100M)
            {
                data = PHY_BCTL_SPEED_100M_MASK | PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
            }
            else
            {
                data = PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
            }
            return MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, data);
        }
        else
        {
            /* DP83848 PHY doesn't support remote loopback. */
            return kStatus_InvalidArgument;
        }
    }
    else
    {
        /* Disable the loop mode. */
        if (mode == kPHY_LocalLoop)
        {
            /* First read the current status in control register. */
            result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, &data);
            if (result == kStatus_Success)
            {
                data &= ~PHY_BCTL_LOOP_MASK;
                return MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG,
                                  (data | PHY_BCTL_RESTART_AUTONEG_MASK));
            }
        }
        else
        {
            /* DP83848 PHY doesn't support remote loopback. */
            return kStatus_InvalidArgument;
        }
    }
    return result;
}

status_t PHY_DP83848_GetLinkStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    status_t result = kStatus_Success;
    uint32_t data;

    /* Read the basic status register. */
    result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_BASICSTATUS_REG, &data);
    if (result == kStatus_Success)
    {
        if (!(PHY_BSTATUS_LINKSTATUS_MASK & data))
        {
            /* link down. */
            *status = false;
        }
        else
        {
            /* link up. */
            *status = true;
        }
    }
    return result;
}

status_t PHY_DP83848_GetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(duplex);

    status_t result = kStatus_Success;
    uint32_t data, ctlReg;

    /* Read the control two register. */
    result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_STATUS_REG, &ctlReg);
    if (result == kStatus_Success)
    {
        data = ctlReg & PHY_STATUS_SPEED_MASK;
        if (data)
        {
            /* Full duplex. */
            *duplex = kPHY_FullDuplex;
        }
        else
        {
            /* Half duplex. */
            *duplex = kPHY_HalfDuplex;
        }

        data = ctlReg & PHY_STATUS_SPEED_MASK;
        if (data)
        {
            /* 10M speed. */
            *speed = kPHY_Speed10M;
        }
        else
        {   /* 100M speed. */
            *speed = kPHY_Speed100M;
        }
    }

    return result;
}
