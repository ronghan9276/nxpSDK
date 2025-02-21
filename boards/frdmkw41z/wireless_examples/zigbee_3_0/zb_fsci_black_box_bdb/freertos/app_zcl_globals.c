/*
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*/
     
/*!=============================================================================
\file       app_zcl_globals.c
\brief      Aplication ZCL Globals
==============================================================================*/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include <app_pdum_cfg.h>
#include "ZQueue.h"
#include "app_zps_cfg.h"
#include "app_zcl_cfg.h"

#include "zps_apl.h"
#include "zps_apl_aib.h"
#include "zps_apl_af.h"


/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#define COMPILE_TIME_ASSERT(pred)    switch(0){case 0:case pred:;}

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
/*** AF Context ***************************************************/
typedef struct _zps_tsAplAfSimpleDescCont
{
    ZPS_tsAplAfSimpleDescriptor sSimpleDesc;
    const PDUM_thAPdu *phAPduInClusters;
    bool_t bEnabled;
} zps_tsAplAfSimpleDescCont;
/****************************************************************************/
/***        External Dependencies                                         ***/
/****************************************************************************/


PUBLIC uint8 u8MaxZpsConfigEp = 1 ;
PUBLIC uint8 au8EpMapPresent[1] = { 1  }; 



/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

/* Simple Descriptors */
PRIVATE uint16 s_au16Endpoint0InputClusterList[85] = { 0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002a, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x8000, 0x8001, 0x8002, 0x8003, 0x8004, 0x8005, 0x8006, 0x8010, 0x8011, 0x8012, 0x8014, 0x8015, 0x8016, 0x8017, 0x8018, 0x8019, 0x801a, 0x801b, 0x801c, 0x801d, 0x801e, 0x8020, 0x8021, 0x8022, 0x8023, 0x8024, 0x8025, 0x8026, 0x8027, 0x8028, 0x8029, 0x802a, 0x8030, 0x8031, 0x8032, 0x8033, 0x8034, 0x8035, 0x8036, 0x8037, 0x8038, 0x001f, 0x801f, };
PRIVATE const PDUM_thAPdu s_ahEndpoint0InputClusterAPdus[85] = { apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, };
PRIVATE uint8 s_au8Endpoint0InputClusterDiscFlags[11] = { 0xff, 0xff, 0xf3, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18 };

PRIVATE uint16 s_au16Endpoint0OutputClusterList[85] = { 0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002a, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x8000, 0x8001, 0x8002, 0x8003, 0x8004, 0x8005, 0x8006, 0x8010, 0x8011, 0x8012, 0x8014, 0x8015, 0x8016, 0x8017, 0x8018, 0x8019, 0x801a, 0x801b, 0x801c, 0x801d, 0x801e, 0x8020, 0x8021, 0x8022, 0x8023, 0x8024, 0x8025, 0x8026, 0x8027, 0x8028, 0x8029, 0x802a, 0x8030, 0x8031, 0x8032, 0x8033, 0x8034, 0x8035, 0x8036, 0x8037, 0x8038, 0x001f, 0x801f, };
PRIVATE uint8 s_au8Endpoint0OutputClusterDiscFlags[11] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x1f };

PRIVATE uint16 s_au16Endpoint1InputClusterList[27] = { ZLO_BASIC_CLUSTER_ID, ZLO_GROUPS_CLUSTER_ID, ZLO_IDENTIFY_CLUSTER_ID, ZLO_ON_OFF_CLUSTER_ID, ZLO_ZLL_COMMISSIONING_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, 0xFFFE};
PRIVATE const PDUM_thAPdu s_ahEndpoint1InputClusterAPdus[26] = { apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, };
PRIVATE uint8 s_au8Endpoint1InputClusterDiscFlags[4] = { 0x09, 0x00, 0x00, 0x00 };

PRIVATE uint16 s_au16Endpoint1OutputClusterList[23] = {ZLO_BASIC_CLUSTER_ID, ZLO_GROUPS_CLUSTER_ID, ZLO_IDENTIFY_CLUSTER_ID, ZLO_ON_OFF_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, ZLO_DEFAULT_CLUSTER_ID, 0xFFFE};
PRIVATE uint8 s_au8Endpoint1OutputClusterDiscFlags[3] = { 0x0f, 0x00, 0x00 };


PUBLIC zps_tsAplAfSimpleDescCont s_asSimpleDescConts[2] = {
    {
        {
            0x0000,
            0,
            0,
            0,
            85,
            85,
            s_au16Endpoint0InputClusterList,
            s_au16Endpoint0OutputClusterList,
            s_au8Endpoint0InputClusterDiscFlags,
            s_au8Endpoint0OutputClusterDiscFlags,
        },
        s_ahEndpoint0InputClusterAPdus,
        1
    },
    {
        {
            0x0104,
            2112,
            0,
            1,
            5,
            4,
            s_au16Endpoint1InputClusterList,
            s_au16Endpoint1OutputClusterList,
            s_au8Endpoint1InputClusterDiscFlags,
            s_au8Endpoint1OutputClusterDiscFlags,
        },
        s_ahEndpoint1InputClusterAPdus,
        1
    },
};

/* Node Descriptor */
PUBLIC ZPS_tsAplAfNodeDescriptor s_sNodeDescriptor = {
    0,
    FALSE,
    FALSE,
    0,
    8,
    0,
    0x8f,
    0x1147,
    0x7f,
    0x0000,
    0x2a41,
    0x0000,
    0x00};

/* Node Power Descriptor */
PUBLIC ZPS_tsAplAfNodePowerDescriptor s_sNodePowerDescriptor = {
    0xC,   
    0x1,
    0x1,
    0x0};

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/
PUBLIC uint8* ZPS_pu8MaxZpsConfigEp(void) 
{
    return &u8MaxZpsConfigEp;
}

PUBLIC uint8* ZPS_pau8EpMapPresent(void)
{
    return &au8EpMapPresent[0];
}
/****************************************************************************/
/***        Configuration erros checks                                    ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
