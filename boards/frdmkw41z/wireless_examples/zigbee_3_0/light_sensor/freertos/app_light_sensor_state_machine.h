/*
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*/


#ifndef APP_SENSOR_STATE_MACHINE_H_
#define APP_SENSOR_STATE_MACHINE_H_

/*!
\file       app_light_sensor_state_machine.h
\brief      ZLO Demo: Processes all stack events depending on it's state
*/

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/
#include <jendefs.h>
#include "zcl.h"
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC void vStartWakeTimer(uint16 u16Tick);
PUBLIC void vAPP_HandlePIRStateTransition(void);
PUBLIC void vAppHandleStartup(void);
PUBLIC void vAppHandleRunning(ZPS_tsAfEvent* psStackEvent);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#endif /* APP_SENSOR_STATE_MACHINE_H_ */
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
