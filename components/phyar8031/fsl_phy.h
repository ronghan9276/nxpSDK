/*
 * Copyright 2017-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_PHY_H_
#define _FSL_PHY_H_

#include "fsl_enet.h"

/*!
 * @addtogroup phy_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief PHY driver version */
/*
    -2.0.1
      - Default configure RMII I/O to 1.8v in PHY_Init
      - Enable RMII rx delay.
*/
#define FSL_PHY_DRIVER_VERSION (MAKE_VERSION(2, 0, 1)) /*!< Version 2.0.1. */

/*! @brief Defines the PHY registers. */
#define PHY_BASICCONTROL_REG 0x00U       /*!< The PHY basic control register. */
#define PHY_BASICSTATUS_REG 0x01U        /*!< The PHY basic status register. */
#define PHY_ID1_REG 0x02U                /*!< The PHY ID one register. */
#define PHY_ID2_REG 0x03U                /*!< The PHY ID two register. */
#define PHY_AUTONEG_ADVERTISE_REG 0x04U  /*!< The PHY auto-negotiate advertise register. */
#define PHY_1000BASET_CONTROL_REG 0x09U  /*!< The PHY 1000BASE-T control register. */
#define PHY_MMD_ACCESS_CONTROL_REG 0x0DU /*!< The PHY MMD access control register. */
#define PHY_MMD_ACCESS_DATA_REG 0x0EU    /*!< The PHY MMD access data register. */
#define PHY_SPECIFIC_STATUS_REG 0x11U    /*!< The PHY specific status register. */
#define PHY_COPPERFIBER_STATUS_REG 0x1BU /*!< The PHY copper/fiber status register. */
#define PHY_DEBUGPORT_ADDR_REG 0x1DU     /*!< The PHY Debug port address register.*/
#define PHY_DEBUGPORT_DATA_REG 0x1EU     /*!< The PHY Debug port data register.*/
#define PHY_CHIP_CFG_REG 0x1FU           /*!< The PHY chip configure register. */

/*! @brief Defines the Debug register offset. */
#define PHY_DEBUG_HIBECTL_REG_OFFSET 0x0BU /*!< The PHY Debug register offset 0xB.*/
#define PHY_DEBUG_EXTLOOP_REG_OFFSET 0x11U /*!< The PHY Debug register offset 0x11.*/

#define PHY_CONTROL_ID1 0x004DU /*!< The PHY ID1 is 0x004D. */

/*! @brief Defines the mask flag in basic control register. */
#define PHY_BCTL_DUPLEX_MASK 0x0100U          /*!< The PHY duplex bit mask. */
#define PHY_BCTL_RESTART_AUTONEG_MASK 0x0200U /*!< The PHY restart auto negotiation mask. */
#define PHY_BCTL_AUTONEG_MASK 0x1000U         /*!< The PHY auto negotiation bit mask. */
#define PHY_BCTL_SPEED_MASK 0x2000U           /*!< The PHY speed bit mask. */
#define PHY_BCTL_LOOP_MASK 0x4000U            /*!< The PHY loop bit mask. */
#define PHY_BCTL_RESET_MASK 0x8000U           /*!< The PHY reset bit mask. */
#define PHY_BCTL_SPEED_1000M_MASK 0x40U       /*!< The PHY 1000M speed mask.*/
#define PHY_BCTL_SPEED_100M_MASK 0x2000U      /*!< The PHY 100M speed mask. */

/*!@brief Defines the mask flag of operation mode in control two register*/
#define PHY_CTL2_REMOTELOOP_MASK 0x0004U    /*!< The PHY remote loopback mask. */
#define PHY_CTL2_REFCLK_SELECT_MASK 0x0080U /*!< The PHY RMII reference clock select. */
#define PHY_CTL1_10HALFDUPLEX_MASK 0x0001U  /*!< The PHY 10M half duplex mask. */
#define PHY_CTL1_100HALFDUPLEX_MASK 0x0002U /*!< The PHY 100M half duplex mask. */
#define PHY_CTL1_10FULLDUPLEX_MASK 0x0005U  /*!< The PHY 10M full duplex mask. */
#define PHY_CTL1_100FULLDUPLEX_MASK 0x0006U /*!< The PHY 100M full duplex mask. */

/*! @brief Defines the mask flag in basic status register. */
#define PHY_BSTATUS_AUTONEGABLE_MASK 0x0008U /*!< The PHY auto-negotiation ability mask. */
#define PHY_BSTATUS_AUTONEGCOMP_MASK 0x0020U /*!< The PHY auto-negotiation complete mask. */

/*! @brief Defines the mask flag in specific status register. */
#define PHY_SSTATUS_LINKSTATUS_MASK 0x0400U /*!< The PHY link status mask. */
#define PHY_SSTATUS_LINKSPEED_MASK 0xC000U  /*!< The PHY link speed mask. */
#define PHY_SSTATUS_LINKDUPLEX_MASK 0x2000U /*!< The PHY link duplex mask. */
#define PHY_SSTATUS_LINKSPEED_SHIFT 14      /*!< The link speed shift */

/*! @brief Defines the mask flag in PHY auto-negotiation advertise register. */
#define PHY_100BaseT4_ABILITY_MASK 0x200U    /*!< The PHY have the T4 ability. */
#define PHY_100BASETX_FULLDUPLEX_MASK 0x100U /*!< The PHY has the 100M full duplex ability.*/
#define PHY_100BASETX_HALFDUPLEX_MASK 0x080U /*!< The PHY has the 100M full duplex ability.*/
#define PHY_10BASETX_FULLDUPLEX_MASK 0x040U  /*!< The PHY has the 10M full duplex ability.*/
#define PHY_10BASETX_HALFDUPLEX_MASK 0x020U  /*!< The PHY has the 10M full duplex ability.*/

/*! @brief Defines the mask flag in the 1000BASE-T control register. */
#define PHY_1000BASET_FULLDUPLEX_MASK 0x200U /*!< The PHY has the 1000M full duplex ability.*/
#define PHY_1000BASET_HALFDUPLEX_MASK 0x100U /*!< The PHY has the 1000M full duplex ability.*/
/*! @brief Defines the mask flag in PHY debug register- hibernate control register. */
#define PHY_DEBUG_HIBERNATECTL_REG 0x8000U /*!< The power hibernate control mask. */

/*! @brief Defines the PHY MMD access. */
#define PHY_MMD_DEVICEID3 3U                 /*!< The PHY device id 3. */
#define PHY_MMD_REMOTEPHY_LOOP_OFFSET 0x805A /*!< The PHY MMD phy register */
#define PHY_MMD_SMARTEEE_CTL_OFFSET 0x805D   /*!< The PHY MMD smartEEE register */
#define PHY_MMD_SMARTEEE_LPI_EN_SHIFT 8      /*!< The SmartEEE enable/disable bit shift */
/*! @brief Defines the chip configure register. */
#define PHY_MODE_CFG_MASK 0xFU /*!< The PHY mode configure mask. */

/*! @brief Defines the PHY status. */
enum _phy_status
{
    kStatus_PHY_SMIVisitTimeout   = MAKE_STATUS(kStatusGroup_PHY, 1), /*!< ENET PHY SMI visit timeout. */
    kStatus_PHY_AutoNegotiateFail = MAKE_STATUS(kStatusGroup_PHY, 2)  /*!< ENET PHY AutoNegotiate Fail. */
};

/*! @brief Defines the PHY link speed. This is align with the speed for ENET MAC. */
typedef enum _phy_speed
{
    kPHY_Speed10M = 0U, /*!< ENET PHY 10M speed. */
    kPHY_Speed100M,     /*!< ENET PHY 100M speed. */
    kPHY_Speed1000M     /*!< ENET PHY 1000M speed. */
} phy_speed_t;

/*! @brief Defines the PHY link duplex. */
typedef enum _phy_duplex
{
    kPHY_HalfDuplex = 0U, /*!< ENET PHY half duplex. */
    kPHY_FullDuplex       /*!< ENET PHY full duplex. */
} phy_duplex_t;

/*! @brief Defines the PHY loopback mode. */
typedef enum _phy_loop
{
    kPHY_LocalLoop = 0U, /*!< ENET PHY local/digital loopback. */
    kPHY_RemoteLoop,     /*!< ENET PHY remote loopback. */
    kPHY_ExternalLoop,   /*!< ENET PHY external loopback. */
} phy_loop_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name PHY Driver
 * @{
 */

/*!
 * @brief Initializes PHY.
 *
 *  This function initialize the SMI interface and initialize PHY.
 *  The SMI is the MII management interface between PHY and MAC, which should be
 *  firstly initialized before any other operation for PHY. The PHY initialize with auto-negotiation.
 *
 * @param base       ENET peripheral base address.
 * @param phyAddr    The PHY address.
 * @param srcClock_Hz  The module clock frequency - system clock for MII management interface - SMI.
 * @retval kStatus_Success  PHY initialize success
 * @retval kStatus_PHY_SMIVisitTimeout  PHY SMI visit time out
 * @retval kStatus_PHY_AutoNegotiateFail  PHY auto negotiate fail
 */
status_t PHY_Init(ENET_Type *base, uint32_t phyAddr, uint32_t srcClock_Hz);

/*!
 * @brief PHY Write function. This function write data over the SMI to
 * the specified PHY register. This function is called by all PHY interfaces.
 *
 * @param base    ENET peripheral base address.
 * @param phyAddr The PHY address.
 * @param phyReg  The PHY register.
 * @param data    The data written to the PHY register.
 * @retval kStatus_Success     PHY write success
 * @retval kStatus_PHY_SMIVisitTimeout  PHY SMI visit time out
 */
status_t PHY_Write(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t data);

/*!
 * @brief PHY Read function. This interface read data over the SMI from the
 * specified PHY register. This function is called by all PHY interfaces.
 *
 * @param base     ENET peripheral base address.
 * @param phyAddr  The PHY address.
 * @param phyReg   The PHY register.
 * @param dataPtr  The address to store the data read from the PHY register.
 * @retval kStatus_Success  PHY read success
 * @retval kStatus_PHY_SMIVisitTimeout  PHY SMI visit time out
 */
status_t PHY_Read(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t *dataPtr);

/*!
 * @brief Enables/disables PHY loopback.
 *
 * @param base     ENET peripheral base address.
 * @param phyAddr  The PHY address.
 * @param mode     The loopback mode to be enabled, please see "phy_loop_t".
 * the two loopback mode should not be both set. when one loopback mode is set
 * the other one should be disabled.
 * @param speed    PHY speed for loopback mode.
 * @param enable   True to enable, false to disable.
 * @retval kStatus_Success  PHY loopback success
 * @retval kStatus_PHY_SMIVisitTimeout  PHY SMI visit time out
 */
status_t PHY_EnableLoopback(ENET_Type *base, uint32_t phyAddr, phy_loop_t mode, phy_speed_t speed, bool enable);

/*!
 * @brief Gets the PHY link status.
 *
 * @param base     ENET peripheral base address.
 * @param phyAddr  The PHY address.
 * @param status   The link up or down status of the PHY.
 *         - true the link is up.
 *         - false the link is down.
 * @retval kStatus_Success   PHY get link status success
 * @retval kStatus_PHY_SMIVisitTimeout  PHY SMI visit time out
 */
status_t PHY_GetLinkStatus(ENET_Type *base, uint32_t phyAddr, bool *status);

/*!
 * @brief Gets the PHY link speed and duplex.
 *
 * @param base     ENET peripheral base address.
 * @param phyAddr  The PHY address.
 * @param speed    The address of PHY link speed.
 * @param duplex   The link duplex of PHY.
 * @retval kStatus_Success   PHY get link speed and duplex success
 * @retval kStatus_PHY_SMIVisitTimeout  PHY SMI visit time out
 */
status_t PHY_GetLinkSpeedDuplex(ENET_Type *base, uint32_t phyAddr, phy_speed_t *speed, phy_duplex_t *duplex);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_PHY_H_ */
