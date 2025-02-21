/*******************************************************************************
*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
* 
*
****************************************************************************//*!
*
* @brief  Algorithm of PMSM Back Electromotive Force observer in stationary 
*         reference frame
* 
*******************************************************************************/
#ifndef _AMCLIB_PMSM_BEMF_OBSRVHW_A32_AB_H_
#define _AMCLIB_PMSM_BEMF_OBSRVHW_A32_AB_H_

#if defined(__cplusplus) 
extern "C" { 
#endif 
/******************************************************************************
* Includes
******************************************************************************/
#include "gflib.h"
#include "gmclib.h"
#include "AMCLIB_PMSMBemfObsrvAB_A32.h"
    
/******************************************************************************
* Macros 
******************************************************************************/
#define AMCLIB_PMSMBemfObsrvABHw_F16_C(psIAlBe, psUAlBe, f16Speed, psCtrl)     \
        AMCLIB_PMSMBemfObsrvABHw_F16_FC(psIAlBe, psUAlBe, f16Speed, psCtrl)
/******************************************************************************
* Types
******************************************************************************/

   
/******************************************************************************
* Exported function prototypes
******************************************************************************/
extern void AMCLIB_PMSMBemfObsrvABHw_F16_FC(const GMCLIB_2COOR_ALBE_T_F16 *psIAlBe,
                                            const GMCLIB_2COOR_ALBE_T_F16 *psUAlBe,
                                            frac16_t f16Speed,
                                            AMCLIB_BEMF_OBSRV_AB_T_A32 *psCtrl);

/******************************************************************************
* Inline functions
******************************************************************************/

 
#if defined(__cplusplus) 
} 
#endif 

#endif /* _AMCLIB_PMSM_BEMF_OBSRVHW_A32_AB_H_ */    
