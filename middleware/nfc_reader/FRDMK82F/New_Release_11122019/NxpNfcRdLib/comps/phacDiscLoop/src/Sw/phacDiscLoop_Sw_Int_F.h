/*
 *                    Copyright (c), NXP Semiconductors
 *
 *                       (C) NXP Semiconductors 2014
 *
 *         All rights are reserved. Reproduction in whole or in part is
 *        prohibited without the written consent of the copyright owner.
 *    NXP reserves the right to make changes without notice at any time.
 *   NXP makes no warranty, expressed, implied or statutory, including but
 *   not limited to any implied warranty of merchantability or fitness for any
 *  particular purpose, or that the use will not infringe any third party patent,
 *   copyright or trademark. NXP must not be liable for any loss or damage
 *                            arising from its use.
 */

/** \file
* Discovery Loop Activities for Type F polling.
* $Author$
* $Revision$ (v06.01.00)
* $Date$
*
* History:
*  PC: Generated 23. Aug 2012
*
*/

#ifndef PHACDISCLOOP_SW_INT_F_H
#define PHACDISCLOOP_SW_INT_F_H

#include <ph_Status.h>


#ifdef NXPBUILD__PHAC_DISCLOOP_SW
/* *****************************************************************************************************************
 * Includes
 * ***************************************************************************************************************** */
#include "phacDiscLoop_Sw.h"

/* *****************************************************************************************************************
 * Function Prototypes
 * ***************************************************************************************************************** */
phStatus_t phacDiscLoop_Sw_DetTechTypeF(
    phacDiscLoop_Sw_DataParams_t *pDataParams
    );

phStatus_t phacDiscLoop_Sw_Int_CollisionResolutionF(
    phacDiscLoop_Sw_DataParams_t *pDataParams
    );

phStatus_t phacDiscLoop_Sw_Int_ActivateF(
    phacDiscLoop_Sw_DataParams_t * pDataParams,
    uint8_t  bTypeFTagIdx
    );

#ifdef NXPBUILD__PHAC_DISCLOOP_TYPEF_TAGS
phStatus_t phacDiscLoop_Sw_Int_Config_GTF(
    phacDiscLoop_Sw_DataParams_t *pDataParams,
    uint8_t bTechIndex
    );
#endif /* NXPBUILD__PHAC_DISCLOOP_TYPEF_TAGS */

#endif /* NXPBUILD__PHAC_DISCLOOP_SW */
#endif /* PHACDISCLOOP_SW_INT_F_H */
