/*
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*!=================================================================================================
\file       app_event_handler.c
\brief      ZLO Demo: Handles all the different type of Application events
==================================================================================================*/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "jendefs.h"
#include "dbg.h"
#include "app_events.h"
#include "app_zlo_sensor_node.h"
#include "app_light_sensor_state_machine.h"
#include "ZTimer.h"
#include "app_main.h"
#include "app_buttons.h"
#include "App_LightSensor.h"
#include "app_sleep_handler.h"
#include "app_event_handler.h"
#include "app_reporting.h"
#include "app_blink_led.h"
#include "app_zcl_tick_handler.h"

#include "bdb_api.h"
#include "bdb_fb_api.h"
#include "app_nwk_event_handler.h"
#include "app_zcl_cfg.h"
#ifdef APP_NTAG_ICODE
#include "app_ntag_icode.h"
#include "nfc_nwk.h"
#endif
#ifdef APP_NTAG_AES
#include "app_ntag_aes.h"
#include "nfc_nwk.h"
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#ifdef DEBUG_EVENT_HANDLER
    #define TRACE_EVENT_HANDLER   TRUE
#else
    #define TRACE_EVENT_HANDLER   FALSE
#endif
/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
PRIVATE void vDioEventHandler(APP_teButtons eTransitionCode);
PRIVATE void vEventStartFindAndBind(void);
PRIVATE void vStartPersistantPolling(void);
PRIVATE void vStopPersistantPolling(void);
PRIVATE void vHandlePeriodicReportEvent(void);
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
extern const uint8 u8MyEndpoint;
/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/****************************************************************************
 *
 * NAME: vDioEventHandler
 *
 * DESCRIPTION:
 * Processes the Dio events like binding and occupancy. Any other events that
 * come through we immediately attempt to go to sleep as we have no process for
 * them.
 *
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void vDioEventHandler(APP_teButtons eTransitionCode )
{
    static uint8_t poll_flag = 0;
    
    DBG_vPrintf(TRACE_EVENT_HANDLER,"\nAPP Process Buttons: In vSensorStateMachine TransitionCode = %02x -> ",eTransitionCode);
    switch(eTransitionCode)
    {
    /* Fall through for the button presses as there will be a delayed action*/
    case APP_E_BUTTONS_BUTTON_SW5:
        break;

    case APP_E_BUTTONS_BUTTON_SW4:  /* Start/Stop Persistant Polling */
        poll_flag ^= 1;
        poll_flag == 1 ? vStartPersistantPolling() : vStopPersistantPolling();
        break;

    case APP_E_BUTTONS_BUTTON_SW3:  /* Steering */
        DBG_vPrintf(TRUE, "APP: Switch-1(Steering)\r\n");
        BDB_eNsStartNwkSteering();
        sBDB.sAttrib.bTLStealNotAllowed = FALSE;
        break;

    case APP_E_BUTTONS_BUTTON_SW2: /* Find and Bind */
        vEventStartFindAndBind();
        break;

#if (defined APP_NTAG_ICODE) || (defined APP_NTAG_AES)
    case FD_PRESSED:
    case FD_RELEASED:
        #if APP_NTAG_ICODE
            APP_vNtagStart(LIGHTSENSOR_SENSOR_ENDPOINT);
        #endif
        #if APP_NTAG_AES
            APP_vNtagStart(NFC_NWK_NSC_DEVICE_CLIMATE_SENSOR_DEVICE);
        #endif
        break;
#endif

    default:
        break;
    }
}

/****************************************************************************
 *
 * NAME: vAppHandleAppEvent
 *
 * DESCRIPTION:
 * interprets the button press and calls the state machine.
 *
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void vAppHandleAppEvent(APP_tsEvent sButton)
{
    te_TransitionCode eTransitionCode=NUMBER_OF_TRANSITION_CODE;
    
    ZPS_eAplZdoPoll();

    switch(sButton.eType)
    {
    case APP_E_EVENT_BUTTON_DOWN:
        DBG_vPrintf(TRACE_EVENT_HANDLER, "\nAPP Process Buttons: Button Number= %d",sButton.uEvent.sButton.u8Button);
        DBG_vPrintf(TRACE_EVENT_HANDLER, "\nAPP Process Buttons: DIO State    = %08x",sButton.uEvent.sButton.u32DIOState);
        
        eTransitionCode=sButton.uEvent.sButton.u8Button;
        
        DBG_vPrintf(TRACE_EVENT_HANDLER, "\nAPP Process Buttons: Transition Code = %d",eTransitionCode);
        vDioEventHandler(eTransitionCode);
        break;

    case APP_E_EVENT_BUTTON_UP:
        DBG_vPrintf(TRACE_EVENT_HANDLER, "\nAPP Process Buttons: Button Number= %d",sButton.uEvent.sButton.u8Button);
        DBG_vPrintf(TRACE_EVENT_HANDLER, "\nAPP Process Buttons: DIO State    = %08x",sButton.uEvent.sButton.u32DIOState);

        eTransitionCode = BUTTON_RELEASED_OFFSET | sButton.uEvent.sButton.u8Button;

        DBG_vPrintf(TRACE_EVENT_HANDLER, "\nAPP Process Buttons: Transition Code = %d",eTransitionCode);
        vDioEventHandler(eTransitionCode);
        break;

    case APP_E_EVENT_PERIODIC_REPORT:
        vHandlePeriodicReportEvent();
        break;

    case APP_E_EVENT_KEEPALIVE_START:
        vStartPersistantPolling();
        break;

    case APP_E_EVENT_KEEPALIVE_STOP:
        vStopPersistantPolling();
        break;

    case APP_E_EVENT_SEND_REPORT:
    case APP_E_EVENT_WAKE_TIMER:
    case APP_E_EVENT_NONE:
        break;

    default :
        break;

    }

}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/
/****************************************************************************
 *
 * NAME: vEventStartFindAndBind
 *
 * DESCRIPTION:
 * Initiates the find and bind procedure, Starts a poll timer and the blink
 * timer.
 *
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PRIVATE void vEventStartFindAndBind(void)
{
    DBG_vPrintf(TRACE_EVENT_HANDLER,"\nAPP Process Buttons: eEZ_FindAndBind");
    sBDB.sAttrib.u16bdbCommissioningGroupID = 0xFFFF;
    vAPP_ZCL_DeviceSpecific_SetIdentifyTime(0xFF);
    BDB_eFbTriggerAsInitiator(u8MyEndpoint);
    vStartPollTimer(POLL_TIME);
    vStartBlinkTimer(APP_FIND_AND_BIND_BLINK_TIME);
}

/****************************************************************************
 *
 * NAME: vEventStopFindAndBind
 *
 * DESCRIPTION:
 * Stops the find and bind procedure and attempts to sleep.
 *
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void vEventStopFindAndBind(void)
{
    DBG_vPrintf(TRACE_EVENT_HANDLER,"\nAPP Process Buttons: Exit Easy Mode");
    vAPP_ZCL_DeviceSpecific_IdentifyOff();
    BDB_vFbExitAsInitiator();
    vStopBlinkTimer();
    ZTIMER_eStop(u8TimerPoll);
}

/****************************************************************************
 *
 * NAME: vStartPersistantPolling
 *
 * DESCRIPTION:
 * Starts the Poll timer which will in turn keep the device awake so it can
 * receive data from it's parent.
 *
 ****************************************************************************/
PRIVATE void vStartPersistantPolling(void)
{
    DBG_vPrintf(TRACE_EVENT_HANDLER,"\nAPP Process Buttons: Start PersistantPolling");
    APP_bPersistantPolling |= TRUE;
    ZTIMER_eStart(u8TimerLightSensorSample, POLL_TIME);
    vStartPollTimer(POLL_TIME);
    vStartBlinkTimer(APP_KEEP_AWAKE_TIME);
}

/****************************************************************************
 *
 * NAME: vStopPersistantPolling
 *
 * DESCRIPTION:
 * Stops the poll timer which will allow the device to go back to sleep.
 *
 ****************************************************************************/
PRIVATE void vStopPersistantPolling(void)
{
    DBG_vPrintf(TRACE_EVENT_HANDLER,"\nAPP Process Buttons: Stop PersistantPolling");
    APP_bPersistantPolling &= FALSE;
    ZTIMER_eStop(u8TimerLightSensorSample);
    ZTIMER_eStop(u8TimerPoll);
    vStopBlinkTimer();
}


PRIVATE void vHandlePeriodicReportEvent(void)
{
    vAPP_LightSensorSample();
    vUpdateZCLTickSinceSleep();
}
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
