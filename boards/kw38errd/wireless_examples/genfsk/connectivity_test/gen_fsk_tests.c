/*

Copyright 2016-2019 NXP
All rights reserved.
SPDX-License-Identifier: BSD-3-Clause

*/


#include "MemManager.h"
#include "RNG_Interface.h"
#include "TimersManager.h"
#if ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable))
#include "PWR_Interface.h"
#endif /* ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable)) */
#include "Flash_Adapter.h"

#include "genfsk_interface.h"
#include "gen_fsk_tests_states.h"
#include "gen_fsk_tests.h"
#if !defined(RADIO_IS_GEN_3P5)
#include "xcvr_test_fsk.h"
#else
#include "nxp_xcvr_msk_config.h"
#include "nxp_xcvr_coding_config.h"
#include "genfsk_utils.h"
#endif
#include "menus.h"
#include "LED.h"
#include "clock_config.h"

#if defined(gBoard_ExtPaSupport_d) && (gBoard_ExtPaSupport_d > 0)
#include "board_extPA.h"
#endif

/*! *********************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */
/*serial interface id*/
uint8_t mAppSerId;
/*timers manager app timer id*/
uint8_t mAppTmrId;
/*GENFSK instance id*/
uint8_t mAppGenfskId;
/*configuration params*/
ct_config_params_t gaConfigParams[gConfParamIdxMax];

char* strDescr[gMaxRate_c+1]        = {"GENFSK 250Kbps", 
                                       "GENFSK 500Kbps", 
                                       "  GENFSK 1Mbps",
#ifdef RADIO_IS_GEN_3P0
                                       "  GENFSK 2Mbps",
#endif /* RADIO_IS_GEN_3P0 */
#ifdef RADIO_IS_GEN_3P5
                                       "BLE LR 125Kbps", 
                                       "BLE LR 500Kbps",
#endif /* RADIO_IS_GEN_3P5 */
                                       "     BLE 1Mbps",
#ifdef RADIO_IS_GEN_3P0
                                       "     BLE 2Mbps"
#endif /* RADIO_IS_GEN_3P0 */
                                         };

char* strWhitenDescr[gMaxWhitenMode_c+1]        = {"Fixed", 
                                                   " Chan"};

#ifdef RADIO_IS_GEN_3P0
uint8_t crtRate[gRateMaxNbr]                  = {gRateGenfsk1Mbps_c, gRateGenfsk500Kbps_c, gRateGenfsk250Kbps_c, gRateGenfsk2Mbps_c};
#else /* RADIO_IS_GEN_3P0 */
uint8_t crtRate[gRateMaxNbr]                  = {gRateGenfsk1Mbps_c, gRateGenfsk500Kbps_c, gRateGenfsk250Kbps_c};
#endif

#ifdef RADIO_IS_GEN_3P5
uint8_t targetRate[gMaxRate_c+1]    = {gGenfskDR250Kbps, gGenfskDR500Kbps, gGenfskDR1Mbps, gGenfskDR2Mbps,
                                       /* For BLE LR rates, no need to select alternate rate => use gGenfskDR1Mbps rate*/
                                       gGenfskDR1Mbps, gGenfskDR1Mbps, gGenfskDR1Mbps, gGenfskDR2Mbps};
#elif defined(RADIO_IS_GEN_3P0)
uint8_t targetRate[gMaxRate_c+1]    = {gGenfskDR250Kbps, gGenfskDR500Kbps, gGenfskDR1Mbps, gGenfskDR2Mbps,
                                       gGenfskDR1Mbps, gGenfskDR2Mbps};

#else
uint8_t targetRate[gMaxRate_c+1]    = {gGenfskDR250Kbps, gGenfskDR500Kbps, gGenfskDR1Mbps,
                                       gGenfskDR1Mbps};
#endif

#if defined(gBoard_ExtPaSupport_d) && (gBoard_ExtPaSupport_d > 0)
char* strExtPaModeDesc[]   = {"Gain", "Bypass"};
char* strExtPaAntDesc[]    = {"uFL", "Printed"};
#endif

/*! *********************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
********************************************************************************** */
#define gPerOpcode1 (0xCA)
#define gPerOpcode2 (0xFE)

#define gRangeOpcode1 (0xAB)
#define gRangeOpcode2 (0xCD)
/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
/* PER RX handler */
static bool_t CT_PacketErrorRateRx(ct_event_t evType, void* pAssociatedValue, bool_t bReInit);
/* PER TX handler */
static bool_t CT_PacketErrorRateTx(ct_event_t evType, void* pAssociatedValue, bool_t bReInit);
/* Range RX handler */
static bool_t CT_RangeRx(ct_event_t evType, void* pAssociatedValue, bool_t bReInit);
/* Range RX handler */
static bool_t CT_RangeTx(ct_event_t evType, void* pAssociatedValue, bool_t bReInit);
#if defined (RADIO_IS_GEN_3P5)
/* Handles the activation/deactivation of low/high power transmit levels */
static void CT_HandleHighLowPower(void);
/* Wrapper to convert types */
static void CT_WrapperRadioModeAndDataRate(xcvr_currConfig_t * pCurrConfig, 
                                           genfskRadioMode_t* pRadioModeIn, genfskDataRate_t*  pDataRate);
#endif

/* Shortcuts enable/disable depending on test state */
static void CT_EnableShortcuts(bool_t bEnable);
/* Handler that applies latest values for channel and tx power and prints shortcuts values */
static bool_t CT_ApplyPrintConfigParams(void);
/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
/* buffers for interaction with Generic FSK */
static uint8_t* gRxBuffer;
static uint8_t* gTxBuffer;

/* Generic FSK packets to get formatted data*/
static GENFSK_packet_t gRxPacket;
static GENFSK_packet_t gTxPacket;

/* control if shortcuts are enabled or disabled*/
static bool_t   bEnableShortcuts = FALSE;

/*hook to notify app thread*/
static pHookAppNotification pNotifyAppThread = NULL;
/*hook to notify app thread*/
static pTmrHookNotification pTmrCallback = NULL;

/*! @brief GENFSK default mode configuration. */
static GENFSK_mode_config_t mModeConfig = 
{
    .mode = gGenfskGllMode,
    .stayInRx = 0,
    .turnaroundTime = 150
};

/*packet configuration*/
static GENFSK_packet_config_t pktConfig = 
{
    .preambleSizeBytes = 0, /*1 byte of preamble*/
    .packetType = gGenfskFormattedPacket,
    .lengthSizeBits = gGenFskDefaultLengthFieldSize_c,
    .lengthBitOrder = gGenfskLengthBitLsbFirst,
    /*sync address bytes = size + 1*/
    .syncAddrSizeBytes = gGenFskDefaultSyncAddrSize_c,
    .lengthAdjBytes = gGenFskDefaultCrcSize_c, /*length field not including CRC so adjust by crc len*/
    .h0SizeBits = gGenFskDefaultH0FieldSize_c,
    .h1SizeBits = gGenFskDefaultH1FieldSize_c,
    .h0Match = gGenFskDefaultH0Value_c, /*match field containing zeros*/
    .h0Mask = gGenFskDefaultH0Mask_c,
    .h1Match = gGenFskDefaultH1Value_c,
    .h1Mask = gGenFskDefaultH1Mask_c,
#if defined (RADIO_IS_GEN_3P5)
    .preambleBytePattern = 0
#endif      
};

/*CRC configuration*/
static GENFSK_crc_config_t crcConfig =
{
    .crcEnable = gGenfskCrcEnable,
    .crcSize = gGenFskDefaultCrcSize_c,
    .crcStartByte = gGenFskDefaultSyncAddrSize_c+1,
    .crcRefIn = gGenfskCrcInputNoRef,
    .crcRefOut = gGenfskCrcOutputNoRef,
    .crcByteOrder = gGenfskCrcLSByteFirst,
    .crcSeed = gGenFskDefaultCrcSeed_c,
    .crcPoly = gGenFskDefaultCrccPoly_c,
    .crcXorOut = 0
};

/*whitener configuration*/
static GENFSK_whitener_config_t whitenConfig = 
{
#ifdef TEST_DTM_LIKE
    .whitenEnable = gGenfskWhitenDisable, //No whitening in DTM
#else
    .whitenEnable = gGenfskWhitenEnable,
#endif /* TEST_DTM_LIKE */    
    .whitenStart = gWhitenStartWhiteningAtH0,
    .whitenEnd = gWhitenEndAtEndOfCrc,
    .whitenB4Crc = gCrcB4Whiten,
    .whitenPolyType = gGaloisPolyType,
    .whitenRefIn = gGenfskWhitenInputNoRef,
    .whitenPayloadReinit = gGenfskWhitenNoPayloadReinit,
    .whitenSize = 7,
    .whitenInit = 0x53,
    .whitenPoly = 0x11, /*x^7 + x^4 + 1! x^7 is never set*/
    .whitenSizeThr = 0,
    .manchesterEn = gGenfskManchesterDisable,
    .manchesterStart = gGenfskManchesterStartAtPayload,
    .manchesterInv = gGenfskManchesterNoInv,
};

/*radio configuration*/
static GENFSK_radio_config_t radioConfig = 
{
    .radioMode = gGenfskGfskBt0p5h0p5,
    .dataRate = gGenfskDR1Mbps
};

/*bit processing configuration*/

/*network / sync address configuration*/
static GENFSK_nwk_addr_match_t ntwkAddr = 
{
    .nwkAddrSizeBytes = gGenFskDefaultSyncAddrSize_c,
    .nwkAddrThrBits = 0,
    .nwkAddr = gGenFskDefaultSyncAddress_c,
};

/* Xtal trim set to invalid value*/
static uint8_t xtalTrim = 0xFFU; /**/

#if defined(gBoard_ExtPaSupport_d) && (gBoard_ExtPaSupport_d > 0)
static uint8_t extPaMode = gDefaultExPaMode_c;
static uint8_t extPaAnt = gDefaultExPaAnt_c;
#endif

/**********************************************************************************/
app_status_t CT_GenFskInit(pHookAppNotification pFunc, pTmrHookNotification pTmrFunc)
{
    bEnableShortcuts = TRUE;

    /*configure hook*/
    pNotifyAppThread = pFunc;
    
    /*configure timer callback*/
    pTmrCallback = pTmrFunc;
    
    /* populate shortcut array */
    gaConfigParams[gConfParamMode].paramType = gParamTypeString_c;
    FLib_MemCpy(gaConfigParams[gConfParamMode].paramName, "Mode", 5);
    FLib_MemCpy(gaConfigParams[gConfParamMode].paramValue.stringValue, "RX", 3);
    if(gDefaultMode_c == gModeTx_c)
    {
        gaConfigParams[gConfParamMode].paramValue.stringValue[0] = 'T';
    }
    
    gaConfigParams[gConfParamRateMode].paramType = gParamTypeMixed_c;
    FLib_MemCpy(gaConfigParams[gConfParamRateMode].paramName, "Rate", 5);
    gaConfigParams[gConfParamRateMode].id = gDefaultRate_c;
    gaConfigParams[gConfParamRateMode].ptr = strDescr;
    
    gaConfigParams[gConfParamWhitenMode].paramType = gParamTypeMixed_c;
    FLib_MemCpy(gaConfigParams[gConfParamWhitenMode].paramName, "Whiten", 7);
    gaConfigParams[gConfParamWhitenMode].id = gDefaultWhitenMode_c;
    gaConfigParams[gConfParamWhitenMode].ptr = strWhitenDescr;
    
    gaConfigParams[gConfParamChannel].paramType = gParamTypeNumber_c;
    FLib_MemCpy(gaConfigParams[gConfParamChannel].paramName, "Channel", 8);
    gaConfigParams[gConfParamChannel].paramValue.decValue = gGenFskDefaultChannel_c;
    
    gaConfigParams[gConfParamPower].paramType = gParamTypeNumber_c;
    FLib_MemCpy(gaConfigParams[gConfParamPower].paramName, "Lo Power", 9);
    gaConfigParams[gConfParamPower].paramValue.decValue = gGenFskDefaultTxPowerLevel_c;
    
    gaConfigParams[gConfParamPayload].paramType = gParamTypeNumber_c;
    FLib_MemCpy(gaConfigParams[gConfParamPayload].paramName, "Payload", 8);
    gaConfigParams[gConfParamPayload].paramValue.decValue = gGenFskDefaultPayloadLen_c;
    
    gaConfigParams[gConfParamXtalTrim].paramType = gParamTypeNumber_c;
    FLib_MemCpy(gaConfigParams[gConfParamXtalTrim].paramName, "XtalTrim", 9);
    
    /* Get trim value */
    xtalTrim = GENFSK_GetSavedXtalTrim();
    gaConfigParams[gConfParamXtalTrim].paramValue.decValue = xtalTrim;
    
#if defined(gBoard_ExtPaSupport_d) && (gBoard_ExtPaSupport_d > 0)
    gaConfigParams[gConfParamExPaGain].paramType = gParamTypeMixed_c;
    FLib_MemCpy(gaConfigParams[gConfParamExPaGain].paramName, "PaMode", 7);
    gaConfigParams[gConfParamExPaGain].id = gDefaultExPaMode_c;
    gaConfigParams[gConfParamExPaGain].ptr = strExtPaModeDesc;
    
    gaConfigParams[gConfParamExPaAnt].paramType = gParamTypeMixed_c;
    FLib_MemCpy(gaConfigParams[gConfParamExPaAnt].paramName, "PaAnt", 6);
    gaConfigParams[gConfParamExPaAnt].id = gDefaultExPaAnt_c;
    gaConfigParams[gConfParamExPaAnt].ptr = strExtPaAntDesc;
#endif

    gaConfigParams[gConfParamTypeMax].paramType = gParamTypeMaxType_c;
    /* allocate once to use for the entire application */
    gRxBuffer  = MEM_BufferAlloc(gGenFskDefaultMaxBufferSize_c + 
                                 crcConfig.crcSize);
    if(gRxBuffer==0)
        return gAppStatusMemoryAllocFailure;
                                 
    gTxBuffer  = MEM_BufferAlloc(gGenFskDefaultMaxBufferSize_c);
    while(gTxBuffer==0)
    {
        MEM_BufferFree(gRxBuffer);
        return gAppStatusMemoryAllocFailure;
    }
    
    gRxPacket.payload = (uint8_t*)MEM_BufferAlloc(gGenFskMaxPayloadLen_c  + 
                                                  crcConfig.crcSize);
    while(gRxPacket.payload==0)
    {
        MEM_BufferFree(gRxBuffer);
        MEM_BufferFree(gTxBuffer);
        return gAppStatusMemoryAllocFailure;
    }
    
    gTxPacket.payload = (uint8_t*)MEM_BufferAlloc(gGenFskMaxPayloadLen_c);
    while(gTxPacket.payload==0)
    {
        MEM_BufferFree(gRxBuffer);
        MEM_BufferFree(gTxBuffer);
        MEM_BufferFree(gRxPacket.payload);
        return gAppStatusMemoryAllocFailure;
    }

    /*prepare the part of the tx packet that is common for all tests*/
    gTxPacket.addr = gGenFskDefaultSyncAddress_c;
    gTxPacket.header.h0Field = gGenFskDefaultH0Value_c;
    gTxPacket.header.h1Field = gGenFskDefaultH1Value_c;
    
    /*set bitrate*/
    GENFSK_RadioConfig(mAppGenfskId, &radioConfig);
    /*set packet config*/
    GENFSK_SetPacketConfig(mAppGenfskId, &pktConfig);
    /*set whitener config*/
    GENFSK_SetWhitenerConfig(mAppGenfskId, &whitenConfig);
    /*set crc config*/
    GENFSK_SetCrcConfig(mAppGenfskId, &crcConfig);
    
    /*set network address at location 0 and enable it*/
    GENFSK_SetNetworkAddress(mAppGenfskId, 0, &ntwkAddr);
    GENFSK_EnableNetworkAddress(mAppGenfskId, 0);
    
    /*set tx power level*/
    GENFSK_SetTxPowerLevel(mAppGenfskId, gGenFskDefaultTxPowerLevel_c);
    /*set channel: Freq = 2360MHz + ChannNumber*1MHz*/
    GENFSK_SetChannelNumber(mAppGenfskId, gGenFskDefaultChannel_c);
    
#ifdef RADIO_IS_GEN_3P5
    /* Whitening specific configuration (withen init depending on channel) only applies to BLE */
    {
        GENFSK_mode_config_t modeConfig;
        
        (void)GENFSK_GetModeConfig(mAppGenfskId, &modeConfig);
        
        if ((modeConfig.mode == gGenfskBleLrMode) || (modeConfig.mode == gGenfskBleUncodedMode))
        {
            GENFSK_SetBleWhitenInit(mAppGenfskId, gGenFskDefaultChannel_c);
        }
    }
#endif
    
#if ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable))
    PWR_ChangeDeepSleepMode(7);
#endif /* ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable)) */
    
    return gAppStatusSuccess;
}


/****************************************************************************
*****************************Packet error rate*******************************
****************************************************************************/
bool_t CT_PacketErrorRate(ct_event_t evType, void* pAssociatedValue)
{
    bool_t bReturnFromSM = FALSE;
    static uint8_t currentTest = 0;
    
    if(gaConfigParams[gConfParamMode].paramValue.stringValue[0] == 'R')
    {
        bReturnFromSM = CT_PacketErrorRateRx(evType, pAssociatedValue, (currentTest != 'R'));
        currentTest = bReturnFromSM? 0 : 'R';
    }
    else
    {
        bReturnFromSM = CT_PacketErrorRateTx(evType, pAssociatedValue, currentTest != 'T');
        currentTest = bReturnFromSM? 0 : 'T';
    }
    return bReturnFromSM;
}

/*! *********************************************************************************
* \brief  Handles the Packet error rate RX test
********************************************************************************** */
static bool_t CT_PacketErrorRateRx(ct_event_t evType, 
                                   void* pAssociatedValue, 
                                   bool_t bReInit)
{
    static ct_per_rx_states_t perRxState = gPerRxStateInit_c; 
    static int32_t  i32RssiSum;
    static uint16_t u16ReceivedPackets;
    static uint16_t u16PacketsIndex;  
    static uint16_t u16TotalPackets;
    
    int8_t   i8AverageRssi = 0;
    ct_rx_indication_t* pIndicationInfo = NULL;
#if ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable))
    uint32_t u32SleepDuration = 0;
#endif /* ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable)) */
    
    uint8_t u8UartData = 0xFF;

    uint8_t* pRxBuffer = NULL;
    bool_t bRestartRx = FALSE;
    bool_t bReturnFromSM = FALSE;
     
    (void)CT_ApplyPrintConfigParams();
    
    if(bReInit) /* Reset the state machine */
    {
        perRxState = gPerRxStateInit_c;
    }
    if(gCtEvtUart_c == evType) /* if UART event extract the character */
    {
        u8UartData = *((uint8_t*)pAssociatedValue);
    }
    switch(perRxState)
    {
    case gPerRxStateInit_c:
        CT_EnableShortcuts(TRUE);
        /*print per rx menu and shortcut keys*/
        PrintMenu(cu8ShortCutsBar, mAppSerId);
        PrintMenu(cu8PerRxTestMenu, mAppSerId);
        PrintTestParams(gaConfigParams, FALSE, mAppSerId);
        
        u16TotalPackets = 0;
        u16ReceivedPackets = 0;
        u16PacketsIndex = 0;
        i32RssiSum = 0;
        perRxState = gPerRxStateWaitStartTest_c;
        break;
    case gPerRxStateWaitStartTest_c:
        if(gCtEvtUart_c == evType)
        {
            if(' ' == u8UartData)
            {
                Serial_Print(mAppSerId, cu8PerRxMessages[0], gAllowToBlock_d);
                
                if(gGenfskSuccess_c != 
                   GENFSK_StartRx(mAppGenfskId,
                                  gRxBuffer, 
                                  gGenFskDefaultMaxBufferSize_c + crcConfig.crcSize,
                                  0,
                                  0)
                   )
                {
                    GENFSK_AbortAll();
                    Serial_Print(mAppSerId, cu8PerRxMessages[1], gAllowToBlock_d);
                    perRxState = gPerRxStateIdle_c; 
                }
                else
                {
                    CT_EnableShortcuts(FALSE);  
                    perRxState = gPerRxStateStartTest_c;
                }
            }
            else if('p' == u8UartData)
            { 
                perRxState = gPerRxStateInit_c;
                bReturnFromSM = TRUE;
            }
        }
        break;
    case gPerRxStateStartTest_c:
        if(gCtEvtRxDone_c == evType || 
           gCtEvtRxFailed_c == evType ||
               gCtEvtSeqTimeout_c == evType) /*check if RX related events are fired */
        {
            if (gCtEvtRxDone_c == evType) /*if rx succesfull, get packet information */
            {
                pIndicationInfo = (ct_rx_indication_t*)pAssociatedValue;
                pRxBuffer = pIndicationInfo->pBuffer; /*same as gRxBuffer*/
                
                /*map rx buffer to generic fsk packet*/
                GENFSK_ByteArrayToPacket(mAppGenfskId, pRxBuffer, &gRxPacket);
                if(gRxPacket.payload[4] == gPerOpcode1 && 
                   gRxPacket.payload[5] == gPerOpcode2) /* check if packet payload is PER type */
                {
                    u16TotalPackets = ((uint16_t)gRxPacket.payload[0] <<8) + gRxPacket.payload[1];
                    u16PacketsIndex = ((uint16_t)gRxPacket.payload[2] <<8) + gRxPacket.payload[3];
#if ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable))                    
                    u32SleepDuration = ((uint16_t)gRxPacket.payload[6] <<24) + ((uint16_t)gRxPacket.payload[7] <<16) +
                                        ((uint16_t)gRxPacket.payload[8] <<8) + gRxPacket.payload[9];
#endif /* ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable)) */
                    u16ReceivedPackets++;
                    i32RssiSum += (int8_t)(pIndicationInfo->rssi);
                    
                    /* print statistics */
                    PrintPerRxInfo(u16PacketsIndex, u16ReceivedPackets, pIndicationInfo, mAppSerId);
                    
                    if(u16PacketsIndex == u16TotalPackets) /* received last packet */
                    { 
                        Serial_Print(mAppSerId, cu8PerRxMessages[3], gAllowToBlock_d);
                        perRxState = gPerRxStateIdle_c;
                        pNotifyAppThread(); 
                    }
                    else
                    {
#if ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable))
                        /*RX will be restarted on WakeUp event.*/
                        PWR_GENFSK_EnterDSM(u32SleepDuration - 10); /*wake-up ~10ms earlier*/
                        PWR_AllowDeviceToSleep();
#else
                        bRestartRx = TRUE;
#endif /* ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable)) */
                    }
                } 
                else
                {
                    bRestartRx = TRUE;
                }
            }
            else
            {
                bRestartRx = TRUE;
            }
            if(bRestartRx) /*restart RX immediately with no timeout*/
            {
                if(gGenfskSuccess_c != 
                   GENFSK_StartRx(mAppGenfskId,
                                  gRxBuffer, 
                                  gGenFskDefaultMaxBufferSize_c + crcConfig.crcSize,
                                  0,
                                  0)
                   )
                {
                    GENFSK_AbortAll();
                    Serial_Print(mAppSerId, cu8PerRxMessages[1], gAllowToBlock_d);
                    perRxState = gPerRxStateIdle_c; 
                }
            }  
        }
        if(gCtEvtUart_c == evType)
        {
            if(' ' == u8UartData)
            {
                GENFSK_AbortAll();
                Serial_Print(mAppSerId, cu8PerRxMessages[2], gAllowToBlock_d);
                pNotifyAppThread(); /* send gCtEvtSelfEvent_c event */
                perRxState = gPerRxStateIdle_c;
            } 
        }
        if(gCtEvtKBD_c == evType)
        {
            GENFSK_AbortAll();
            Serial_Print(mAppSerId, cu8PerRxMessages[2], gAllowToBlock_d);
            pNotifyAppThread(); /* send gCtEvtSelfEvent_c event */
            perRxState = gPerRxStateIdle_c;
        }
#if ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable))         
        if(gCtEvtWakeUp_c == evType)
        {
            if(gGenfskSuccess_c != 
               GENFSK_StartRx(mAppGenfskId,
                              gRxBuffer, 
                              gGenFskDefaultMaxBufferSize_c + crcConfig.crcSize,
                              0,
                              0)
                   )
            {
                GENFSK_AbortAll();
                Serial_Print(mAppSerId, cu8PerRxMessages[1], gAllowToBlock_d);
                perRxState = gPerRxStateIdle_c; 
            }
        }
#endif /* ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable)) */
        break;
    case gPerRxStateIdle_c:
        if((gCtEvtUart_c == evType) && 
           ('\r' == u8UartData)) /* reinit state machine (for error cases)*/
        {
            perRxState = gPerRxStateInit_c;
            pNotifyAppThread();
        }
        if(gCtEvtSelfEvent_c == evType) /* print statistics for PER test */
        {
                                
            i8AverageRssi = u16ReceivedPackets > 0 ? 
                i32RssiSum/u16ReceivedPackets: 0;
                
            PrintPerRxFinal(u16ReceivedPackets, 
                            u16TotalPackets, 
                            i8AverageRssi, 
                            mAppSerId);
            Serial_Print(mAppSerId, 
                         cu8PerRxMessages[4], 
                         gAllowToBlock_d);
        }
        break;
    default:
        break;
    }
    return bReturnFromSM;      
}

/*! *********************************************************************************
* \brief  Handles the Packet error rate TX test
********************************************************************************** */
static bool_t CT_PacketErrorRateTx(ct_event_t evType, 
                                   void* pAssociatedValue, 
                                   bool_t bReInit)
{
    const uint16_t u16TotalPacketsOptions[] = {1,25,100,500,1000,2000,5000,10000,65535};
    
    static ct_per_tx_states_t perTxState = gPerTxStateInit_c;
    static uint32_t miliSecDelay;

    static uint16_t u16TotalPackets;
    static uint16_t u16SentPackets;
    
    uint16_t buffLen = 0;
    bool_t bReturnFromSM = FALSE;

    uint8_t u8Index;
    uint8_t u8UartData = 0xFF;
    
    (void)CT_ApplyPrintConfigParams();
    
    if(bReInit)
    {
        perTxState = gPerTxStateInit_c;
    }
    
    if(gCtEvtUart_c == evType)
    {
        u8UartData = *((uint8_t*)pAssociatedValue);
    }
    switch(perTxState)
    {
    case gPerTxStateInit_c:
        PrintMenu(cu8ShortCutsBar, mAppSerId);
        PrintMenu(cu8PerTxTestMenu, mAppSerId);
        PrintTestParams(gaConfigParams, FALSE, mAppSerId);
        
        CT_EnableShortcuts(TRUE);          
        
        perTxState = gPerTxStateSelectPacketNum_c;
        miliSecDelay = 0;
        break;
    case gPerTxStateSelectPacketNum_c:
        if(gCtEvtUart_c == evType) /*select number of packets to send*/
        {    
            if((u8UartData >= '0') && (u8UartData <= '8'))
            {
                u16TotalPackets = u16TotalPacketsOptions[u8UartData - '0'];
                CT_EnableShortcuts(FALSE);  
                Serial_Print(mAppSerId, cu8PerTxMessages[0], gAllowToBlock_d);
                perTxState = gPerTxStateInputPacketDelay_c;
            }
            else if('p' == u8UartData) /*go back to previous menu*/
            { 
                perTxState = gPerTxStateInit_c;
                CT_EnableShortcuts(TRUE);
                bReturnFromSM = TRUE;
            }
        }
        break;
    case gPerTxStateInputPacketDelay_c:
        if(gCtEvtUart_c == evType) /*select delay*/
        {
            if(u8UartData == '\r')
            {
                /*approximate limitation due to printing data on the Serial Interface*/
                if(miliSecDelay < 7) 
                {
                    Serial_Print(mAppSerId, cu8PerTxMessages[1], gAllowToBlock_d);
                    perTxState = gPerTxStateInit_c;
                    pNotifyAppThread(); /*notify application thread*/
                }
                else
                {
                    perTxState = gPerTxStateStartTest_c;
                    pNotifyAppThread();
                }
            }
            else if((u8UartData >= '0') && (u8UartData <='9'))
            {
                miliSecDelay = miliSecDelay*10 + (u8UartData - '0');
                Serial_PrintDec(mAppSerId, (uint32_t)(u8UartData - '0'));
            }
            else if('p' == u8UartData)
            { 
                perTxState = gPerTxStateInit_c;
                CT_EnableShortcuts(TRUE);
                bReturnFromSM = TRUE;
            }
        }
        break;
    case gPerTxStateStartTest_c:
        miliSecDelay *= 1000; /*convert into microseconds*/
        u16SentPackets = 0;
        gTxPacket.header.lengthField = 
            (uint16_t)gaConfigParams[gConfParamPayload].paramValue.decValue;
        
        gTxPacket.payload[0] = (u16TotalPackets >> 8);
        gTxPacket.payload[1] = (uint8_t)u16TotalPackets;
        gTxPacket.payload[2] = ((u16SentPackets+1) >> 8);
        gTxPacket.payload[3] = (uint8_t)(u16SentPackets+1);
        gTxPacket.payload[4] = gPerOpcode1;
        gTxPacket.payload[5] = gPerOpcode2;
#if ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable))
        miliSecDelay /= 1000; /*for low power use miliseconds resolution*/
        gTxPacket.payload[6] = (miliSecDelay >> 24);
        gTxPacket.payload[7] = (miliSecDelay >> 16);
        gTxPacket.payload[8] = (miliSecDelay >> 8);
        gTxPacket.payload[9] = (uint8_t)miliSecDelay;
#endif /* ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable)) */
        
        if(gGenFskMinPayloadLen_c < gaConfigParams[gConfParamPayload].paramValue.decValue)
        {
            for(u8Index = gGenFskMinPayloadLen_c ;
                u8Index < gaConfigParams[gConfParamPayload].paramValue.decValue;
                u8Index++)
            {     
                gTxPacket.payload[u8Index] = (u8Index%10)+'0';  /*add some padding*/          
            }
        }
        /*pack everything into a buffer*/
        GENFSK_PacketToByteArray(mAppGenfskId, &gTxPacket, gTxBuffer);
        /*calculate buffer length*/
        buffLen = gTxPacket.header.lengthField+
                    (gGenFskDefaultHeaderSizeBytes_c)+
                        (gGenFskDefaultSyncAddrSize_c + 1);
                
        if(gGenfskSuccess_c != /*start tx at current time + input delay*/
           GENFSK_StartTx(mAppGenfskId, gTxBuffer, buffLen, 0))
        {
            GENFSK_AbortAll();
            Serial_Print(mAppSerId, cu8PerTxMessages[2], gAllowToBlock_d);
            perTxState = gPerTxStateIdle_c;
        }
        
        u16SentPackets++;
        Serial_Print(mAppSerId, cu8PerTxMessages[3], gAllowToBlock_d);
        Serial_PrintDec(mAppSerId, (uint32_t)u16TotalPackets);
        
        perTxState = gPerTxStateRunningTest_c;
        break;
    case gPerTxStateRunningTest_c:
        if(gCtEvtTxDone_c == evType)
        {    
            PrintPerTxPackets(u16SentPackets, 
                              (gGenfskSuccess == *((genfskEventStatus_t*)pAssociatedValue)),
                              mAppSerId);
            
            if(u16SentPackets == u16TotalPackets)
            {    
                Serial_Print(mAppSerId, cu8PerTxMessages[4], gAllowToBlock_d);
                perTxState = gPerTxStateIdle_c;
            }
            else
            {
#if ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable))
                /*next packet is sent on wakeup event*/
                PWR_GENFSK_EnterDSM(miliSecDelay);
                PWR_AllowDeviceToSleep();
#else
                gTxPacket.payload[2] = ((u16SentPackets+1) >> 8);
                gTxPacket.payload[3] = (uint8_t)(u16SentPackets+1);
                /*pack everything into a buffer*/
                GENFSK_PacketToByteArray(mAppGenfskId, &gTxPacket, gTxBuffer);
                /*calculate buffer length*/
                buffLen = gTxPacket.header.lengthField+
                    (gGenFskDefaultHeaderSizeBytes_c)+
                        (gGenFskDefaultSyncAddrSize_c + 1);
                
                if(gGenfskSuccess_c != 
                   GENFSK_StartTx(mAppGenfskId, gTxBuffer, buffLen, GENFSK_GetTimestamp() + miliSecDelay))
                {
                    GENFSK_AbortAll();
                    Serial_Print(mAppSerId, cu8PerTxMessages[5], gAllowToBlock_d);
                    perTxState = gPerTxStateIdle_c;
                }
                
                u16SentPackets++;
#endif /* ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable)) */
            }
        }
#if ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable))
        if(gCtEvtWakeUp_c == evType)
        {
            gTxPacket.payload[2] = ((u16SentPackets+1) >> 8);
            gTxPacket.payload[3] = (uint8_t)(u16SentPackets+1);
            /*pack everything into a buffer*/
            GENFSK_PacketToByteArray(mAppGenfskId, &gTxPacket, gTxBuffer);
            /*calculate buffer length*/
            buffLen = gTxPacket.header.lengthField+
                (gGenFskDefaultHeaderSizeBytes_c)+
                    (gGenFskDefaultSyncAddrSize_c + 1);
            
            if(gGenfskSuccess_c != 
               GENFSK_StartTx(mAppGenfskId, gTxBuffer, buffLen, 0))
            {
                GENFSK_AbortAll();
                Serial_Print(mAppSerId, cu8PerTxMessages[5], gAllowToBlock_d);
                perTxState = gPerTxStateIdle_c;
            }
            
            u16SentPackets++;
        }
#endif /* ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable)) */
        if(gCtEvtUart_c == evType && u8UartData == ' ')
        {
            GENFSK_AbortAll();
            
            Serial_Print(mAppSerId, cu8PerTxMessages[6],gAllowToBlock_d);
            perTxState = gPerTxStateIdle_c;
        }
        if(gCtEvtKBD_c == evType)
        {
            GENFSK_AbortAll();
            
            Serial_Print(mAppSerId, cu8PerTxMessages[6],gAllowToBlock_d);
            perTxState = gPerTxStateIdle_c;
        }
        break;	
    case gPerTxStateIdle_c:
        if((gCtEvtUart_c == evType) && ('\r' == u8UartData))
        {
            perTxState = gPerTxStateInit_c;
            pNotifyAppThread();
        }
        break;
    default:
        break;
    }
    
    return bReturnFromSM;      
}

/****************************************************************************
*********************************Range test**********************************
****************************************************************************/
bool_t CT_RangeTest(ct_event_t evType, void* pAssociatedValue)
{
        
    static uint8_t currentTest = 0;
    bool_t bReturnFromSM = FALSE;
    
    if(gaConfigParams[gConfParamMode].paramValue.stringValue[0] == 'R')
    {
        bReturnFromSM = CT_RangeRx(evType, pAssociatedValue, (currentTest != 'R'));
        currentTest = bReturnFromSM? 0 : 'R';
    }
    else
    {
        bReturnFromSM = CT_RangeTx(evType, pAssociatedValue, currentTest != 'T');
        currentTest = bReturnFromSM? 0 : 'T';
    }
    return bReturnFromSM;   
}

/*! *********************************************************************************
* \brief  Handles the Range RX test
********************************************************************************** */
static bool_t CT_RangeRx(ct_event_t evType, 
                         void* pAssociatedValue, 
                         bool_t bReInit)
{
    static ct_range_rx_states_t rangeRxState = gRangeRxStateInit_c;
    static int32_t i32RssiSum = 0;
    static uint16_t u16ReceivedPackets = 0;
#if ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable))
    static uint32_t miliSecDelay;
#endif /* ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable)) */

    ct_rx_indication_t* pIndicationInfo = NULL;
    uint8_t u8UartData = 0xFF;
    uint16_t buffLen = 0;
    int8_t i8AverageRssi = 0;
    int8_t i8TempValue = 0;
    bool_t bReturnFromSM = FALSE;
    bool_t bRestartRx = FALSE;
    
    if(bReInit)
    {
        rangeRxState = gRangeRxStateInit_c;
    }
    
    if(gCtEvtUart_c == evType)
    {
        u8UartData = *((uint8_t*)pAssociatedValue);
    }
    
    (void)CT_ApplyPrintConfigParams();
    
    switch(rangeRxState)
    {
    case gRangeRxStateInit_c:
        i32RssiSum = 0;
        u16ReceivedPackets = 0;
        
        PrintMenu(cu8ShortCutsBar, mAppSerId);
        PrintMenu(cu8RangeRxTestMenu, mAppSerId);
        PrintTestParams(gaConfigParams, FALSE,  mAppSerId);
        
        CT_EnableShortcuts(TRUE);           
        
        gTxPacket.payload[1] = gRangeOpcode1;
        gTxPacket.payload[2] = gRangeOpcode2;
        gTxPacket.payload[3] = gRangeOpcode1 ^ gRangeOpcode2;
        gTxPacket.payload[4] = 255 - gTxPacket.payload[3];
        gTxPacket.payload[5] = 0x00;
#if ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable))
        miliSecDelay = 100; /*100 ms between packets*/
        gTxPacket.payload[6] = (miliSecDelay >> 24);
        gTxPacket.payload[7] = (miliSecDelay >> 16);
        gTxPacket.payload[8] = (miliSecDelay >> 8);
        gTxPacket.payload[9] = (uint8_t)miliSecDelay;
#endif /* ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable)) */
        
        rangeRxState = gRangeRxStateStartTest_c;
        break;
    case gRangeRxStateStartTest_c:
        if(gCtEvtUart_c == evType)
        {
            if(' ' == u8UartData)
            {
                CT_EnableShortcuts(FALSE); 
                
                if(gGenfskSuccess_c == 
                   GENFSK_StartRx(mAppGenfskId,
                                  gRxBuffer, 
                                  gGenFskDefaultMaxBufferSize_c + crcConfig.crcSize, 
                                  0,
                                  0))
                {
                    Serial_Print(mAppSerId, cu8RangeRxMessages[0], gAllowToBlock_d);
                    rangeRxState = gRangeRxStateRunningTest_c;
                }
                else
                {
                    Serial_Print(mAppSerId, cu8RangeRxMessages[1], gAllowToBlock_d);
                    rangeRxState = gRangeRxStateIdle_c;
                }
            }
            else if('p' == u8UartData)
            { 
                rangeRxState = gRangeRxStateInit_c;
                CT_EnableShortcuts(TRUE);
                bReturnFromSM = TRUE;
            }
        }
        break;
    case gRangeRxStateRunningTest_c:
        if(gCtEvtUart_c == evType && 
           (' ' == u8UartData)) /*stop test in case [SPACE] is pressed*/
        {             
            GENFSK_AbortAll();
            Serial_Print(mAppSerId, cu8RangeRxMessages[2], gAllowToBlock_d);
            
            i8AverageRssi = u16ReceivedPackets > 0 ?
                (int8_t)(i32RssiSum/u16ReceivedPackets) : 0;
            
            PrintAvgRssi(i8AverageRssi, mAppSerId); /*Print average RSSI*/
            
            Serial_Print(mAppSerId, cu8RangeRxMessages[3], gAllowToBlock_d);
            rangeRxState = gRangeRxStateIdle_c;
        }
        if(gCtEvtKBD_c == evType)
        {
            GENFSK_AbortAll();
            Serial_Print(mAppSerId, cu8RangeRxMessages[2], gAllowToBlock_d);
            
            i8AverageRssi = u16ReceivedPackets > 0 ?
                (int8_t)(i32RssiSum/u16ReceivedPackets) : 0;
            
            PrintAvgRssi(i8AverageRssi, mAppSerId); /*Print average RSSI*/
            
            Serial_Print(mAppSerId, cu8RangeRxMessages[3], gAllowToBlock_d);
            rangeRxState = gRangeRxStateIdle_c;            
        }
        if(gCtEvtRxDone_c == evType || 
           gCtEvtSeqTimeout_c == evType || 
               gCtEvtRxFailed_c == evType)
        {
            if(gCtEvtRxDone_c == evType) /*if RX is succesfull*/
            {                   
                pIndicationInfo = (ct_rx_indication_t*)pAssociatedValue;
                GENFSK_ByteArrayToPacket(mAppGenfskId, pIndicationInfo->pBuffer, &gRxPacket);
                /*check if Range Test payload type*/
                if(gRxPacket.payload[1] == gRangeOpcode1 &&
                   gRxPacket.payload[2] == gRangeOpcode2 &&
                       gRxPacket.header.lengthField == gGenFskMinPayloadLen_c) 
                {
                    gTxPacket.header.lengthField = gGenFskMinPayloadLen_c;
                    /*extract RSSI for the received packet and send it back*/
                    gTxPacket.payload[0] = pIndicationInfo->rssi;
                    
                    /*prepare TX packet and calculate buffer length for the resulting buffer*/
                    GENFSK_PacketToByteArray(mAppGenfskId, &gTxPacket, gTxBuffer);
                    buffLen = gTxPacket.header.lengthField+
                        (gGenFskDefaultHeaderSizeBytes_c)+
                            (gGenFskDefaultSyncAddrSize_c + 1);
                    if(gGenfskSuccess_c != 
                       GENFSK_StartTx(mAppGenfskId,
                                      gTxBuffer, 
                                      buffLen, 
                                      GENFSK_GetTimestamp() + 1000))
                    {
                        Serial_Print(mAppSerId, cu8RangeRxMessages[1], gAllowToBlock_d);
                        rangeRxState = gRangeRxStateIdle_c;
                    }
                    else
                    {
                        rangeRxState = gRangeRxStatePrintTestResults_c;
                    }
                }
                else
                {
                    bRestartRx = TRUE;
                }
            }
            else
            {
                bRestartRx = TRUE;
            }
            if(bRestartRx)
            {
                if(gGenfskSuccess_c != 
                   GENFSK_StartRx(mAppGenfskId,
                                  gRxBuffer, 
                                  gGenFskDefaultMaxBufferSize_c + crcConfig.crcSize, 
                                  0,
                                  0))
                {
                    Serial_Print(mAppSerId, cu8RangeRxMessages[1], gAllowToBlock_d);
                    rangeRxState = gRangeRxStateIdle_c;
                } 
            }
        }
        break;
    case gRangeRxStatePrintTestResults_c:
        if(gCtEvtKBD_c == evType)
        {
            GENFSK_AbortAll();
            Serial_Print(mAppSerId, cu8RangeRxMessages[2], gAllowToBlock_d);
            
            i8AverageRssi = u16ReceivedPackets > 0 ?
                (int8_t)(i32RssiSum/u16ReceivedPackets) : 0;
            
            PrintAvgRssi(i8AverageRssi, mAppSerId); /*Print average RSSI*/
            
            Serial_Print(mAppSerId, cu8RangeRxMessages[3], gAllowToBlock_d);
            rangeRxState = gRangeRxStateIdle_c;            
        }
        if(gCtEvtTxDone_c == evType)
        {     
            i8TempValue = (int8_t)(gTxPacket.payload[0]);
            i32RssiSum += i8TempValue;
            u16ReceivedPackets++;
            /*after sending the RSSI to TX device succesfully, print it*/
            PrintCrtRssi(i8TempValue, mAppSerId);

#if ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable))
            /*next packet is sent on wakeup event*/
            PWR_GENFSK_EnterDSM(miliSecDelay - 10);
            PWR_AllowDeviceToSleep();
#else
            if(gGenfskSuccess_c != 
               GENFSK_StartRx(mAppGenfskId,
                              gRxBuffer, 
                              gGenFskDefaultMaxBufferSize_c + crcConfig.crcSize, 
                              0,
                              0))
            {
                Serial_Print(mAppSerId, cu8RangeRxMessages[1], gAllowToBlock_d);
                rangeRxState = gRangeRxStateIdle_c;
            }
            else
            {
                rangeRxState = gRangeRxStateRunningTest_c;
            }
#endif /* ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable)) */
        }
#if ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable))
        if(gCtEvtWakeUp_c == evType)
        {
            if(gGenfskSuccess_c != 
               GENFSK_StartRx(mAppGenfskId,
                              gRxBuffer, 
                              gGenFskDefaultMaxBufferSize_c + crcConfig.crcSize, 
                              0,
                              0))
            {
                Serial_Print(mAppSerId, cu8RangeRxMessages[1], gAllowToBlock_d);
                rangeRxState = gRangeRxStateIdle_c;
            }
            else
            {
                rangeRxState = gRangeRxStateRunningTest_c;
            }
        }
#endif /* ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable)) */
        break;
    case gRangeRxStateIdle_c:
        if((gCtEvtUart_c == evType) && 
           ('\r' == u8UartData))
        {
            rangeRxState = gRangeRxStateInit_c;
            pNotifyAppThread();
        }
        break;
    default:
        break;
    }
    
    return bReturnFromSM;      
}

/*! *********************************************************************************
* \brief  Handles the Range TX test
********************************************************************************** */
static bool_t CT_RangeTx(ct_event_t evType, 
                         void* pAssociatedValue, 
                         bool_t bReInit)
{
    static ct_range_tx_states_t rangeTxState = gRangeTxStateInit_c;
    static int32_t i32RssiSum = 0;
    static uint16_t u16ReceivedPackets = 0;
    static uint16_t u16PacketsDropped = 0;
#if ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable))
    static uint32_t miliSecDelay;
#endif /* ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable)) */
    
    ct_rx_indication_t* pIndicationInfo;
    int8_t  i8AverageRssi;
    int8_t  i8TempValue;
    uint8_t u8UartData = 0xFF;
    uint16_t buffLen = 0;
    bool_t bRestartRx = FALSE;
    bool_t bReturnFromSM = FALSE;
    
    if(bReInit)
    {
        rangeTxState = gRangeTxStateInit_c;
    }
    
    if(gCtEvtUart_c == evType)
    {
        u8UartData = *((uint8_t*)pAssociatedValue);
    }
    
    (void)CT_ApplyPrintConfigParams();
    
    switch(rangeTxState)
    {
    case gRangeTxStateInit_c:
        i32RssiSum = 0;
        u16ReceivedPackets = 0;
        u16PacketsDropped = 0;
        
        PrintMenu(cu8ShortCutsBar, mAppSerId);
        PrintMenu(cu8RangeTxTestMenu, mAppSerId);
        PrintTestParams(gaConfigParams, FALSE, mAppSerId);
        
        gTxPacket.payload[1] = gRangeOpcode1;
        gTxPacket.payload[2] = gRangeOpcode2;
        gTxPacket.payload[3] = gRangeOpcode1 ^ gRangeOpcode2;
        gTxPacket.payload[4] = 255 - gTxPacket.payload[3];
        gTxPacket.payload[5] = 0x00;
#if ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable))
        miliSecDelay = 100; /*100 ms between packets*/
        gTxPacket.payload[6] = (miliSecDelay >> 24);
        gTxPacket.payload[7] = (miliSecDelay >> 16);
        gTxPacket.payload[8] = (miliSecDelay >> 8);
        gTxPacket.payload[9] = (uint8_t)miliSecDelay;
#endif /* ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable)) */
        
        CT_EnableShortcuts(TRUE);          
        rangeTxState = gRangeTxStateStartTest_c;
        break;
    case gRangeTxStateStartTest_c:
        if(gCtEvtUart_c == evType)
        {
            if(' ' == u8UartData)
            {
                CT_EnableShortcuts(FALSE); 
                /*set first byte of payload*/
                gTxPacket.payload[0] = 0x00;
                /*set payload length*/
                gTxPacket.header.lengthField = gGenFskMinPayloadLen_c;
                /*convert to a ready-to-send buffer*/
                GENFSK_PacketToByteArray(mAppGenfskId, &gTxPacket, gTxBuffer);
                /*calculate gTxBuffer length*/
                buffLen = gTxPacket.header.lengthField + 
                         (gGenFskDefaultHeaderSizeBytes_c) + 
                         (gGenFskDefaultSyncAddrSize_c + 1);

                if(gGenfskSuccess_c == GENFSK_StartTx(mAppGenfskId,
                                                      gTxBuffer, 
                                                      buffLen,
                                                      0))
                {
                    Serial_Print(mAppSerId, cu8RangeTxMessages[0], gAllowToBlock_d);
                    rangeTxState = gRangeTxStateRunningTest_c;
                }
                else
                {
                    Serial_Print(mAppSerId, cu8RangeTxMessages[1], gAllowToBlock_d);
                    rangeTxState = gRangeTxStateIdle_c;
                }
            }
            else if('p' == u8UartData)
            { 
                rangeTxState = gRangeTxStateInit_c;
                CT_EnableShortcuts(TRUE);
                bReturnFromSM = TRUE;
            }
        }
        break;
    case gRangeTxStateRunningTest_c:
        if((gCtEvtUart_c == evType) && (' ' == u8UartData))
        {
            GENFSK_AbortAll();
            
            Serial_Print(mAppSerId, cu8RangeTxMessages[3], gAllowToBlock_d);

            i8AverageRssi = u16ReceivedPackets > 0 ? 
                (int8_t)(i32RssiSum/u16ReceivedPackets) : 0;
            /*print average RSSI for the Range test*/
            PrintAvgRssi(i8AverageRssi, mAppSerId);
            /*print number of dropped packets*/
            PrintRangeTxDroppedPackets(u16PacketsDropped, mAppSerId);
            
            Serial_Print(mAppSerId, cu8RangeTxMessages[4], gAllowToBlock_d);
            
            rangeTxState = gRangeTxStateIdle_c;
        }
        
        if(gCtEvtKBD_c == evType)
        {
            GENFSK_AbortAll();
            
            Serial_Print(mAppSerId, cu8RangeTxMessages[3], gAllowToBlock_d);

            i8AverageRssi = u16ReceivedPackets > 0 ? 
                (int8_t)(i32RssiSum/u16ReceivedPackets) : 0;
            /*print average RSSI for the Range test*/
            PrintAvgRssi(i8AverageRssi, mAppSerId);
            /*print number of dropped packets*/
            PrintRangeTxDroppedPackets(u16PacketsDropped, mAppSerId);
            
            Serial_Print(mAppSerId, cu8RangeTxMessages[4], gAllowToBlock_d);
            
            rangeTxState = gRangeTxStateIdle_c;            
        }
        
        if(gCtEvtTxDone_c == evType)
        {                                         
            if(gGenfskSuccess_c != 
               GENFSK_StartRx(mAppGenfskId,
                              gRxBuffer, 
                              gGenFskDefaultMaxBufferSize_c, 
                              0, 
                              10000)) /*wait 10 ms for the response*/
            {
                Serial_Print(mAppSerId, cu8RangeTxMessages[1], gAllowToBlock_d);
                rangeTxState = gRangeTxStateIdle_c;  
            }
            else
            {
                rangeTxState = gRangeTxStatePrintTestResults_c;
            }
        }
        break;
    case gRangeTxStatePrintTestResults_c:
        if(gCtEvtKBD_c == evType)
        {
            GENFSK_AbortAll();
            
            Serial_Print(mAppSerId, cu8RangeTxMessages[3], gAllowToBlock_d);

            i8AverageRssi = u16ReceivedPackets > 0 ? 
                (int8_t)(i32RssiSum/u16ReceivedPackets) : 0;
            /*print average RSSI for the Range test*/
            PrintAvgRssi(i8AverageRssi, mAppSerId);
            /*print number of dropped packets*/
            PrintRangeTxDroppedPackets(u16PacketsDropped, mAppSerId);
            
            Serial_Print(mAppSerId, cu8RangeTxMessages[4], gAllowToBlock_d);
            
            rangeTxState = gRangeTxStateIdle_c;            
        }
        if(gCtEvtRxDone_c == evType ||
           gCtEvtRxFailed_c == evType ||
               gCtEvtSeqTimeout_c == evType)
        {                                                       
            if(gCtEvtRxDone_c == evType)
            { 
                pIndicationInfo = (ct_rx_indication_t*)pAssociatedValue;
                GENFSK_ByteArrayToPacket(mAppGenfskId, pIndicationInfo->pBuffer, &gRxPacket);
                
                if(gRxPacket.payload[1] == gRangeOpcode1 &&
                   gRxPacket.payload[2] == gRangeOpcode2 &&
                       gRxPacket.header.lengthField == gGenFskMinPayloadLen_c)
                {
                    i8TempValue = (int8_t)(gRxPacket.payload[0]); 
                    i32RssiSum += i8TempValue;  
                    u16ReceivedPackets++;
                    
                    PrintCrtRssi(i8TempValue, mAppSerId);
                }
                else
                {                                   
                    bRestartRx = TRUE;                        
                }
            }
            else if(gCtEvtSeqTimeout_c == evType)
            {
                u16PacketsDropped++;
                Serial_Print(mAppSerId, cu8RangeTxMessages[2], gAllowToBlock_d);
            }
            else
            {
                bRestartRx = TRUE;
            }
            if(bRestartRx)
            {
                if(gGenfskSuccess_c != 
                   GENFSK_StartRx(mAppGenfskId, 
                                  gRxBuffer, 
                                  gGenFskDefaultMaxBufferSize_c, 
                                  0, 
                                  10000))
                {
                    Serial_Print(mAppSerId, cu8RangeTxMessages[1], gAllowToBlock_d);
                    rangeTxState = gRangeTxStateIdle_c;  
                }
            }
            else
            {
#if ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable))
                /*next packet is sent on wakeup event*/
                PWR_GENFSK_EnterDSM(miliSecDelay);
                PWR_AllowDeviceToSleep();
#else
                gTxPacket.payload[0] = 0x00;
                gTxPacket.header.lengthField = gGenFskMinPayloadLen_c;
                GENFSK_PacketToByteArray(mAppGenfskId, &gTxPacket, gTxBuffer);
                
                buffLen = gTxPacket.header.lengthField + 
                    (gGenFskDefaultHeaderSizeBytes_c) + 
                        (gGenFskDefaultSyncAddrSize_c + 1);
                
                if(gGenfskSuccess_c != GENFSK_StartTx(mAppGenfskId,
                                                      gTxBuffer, 
                                                      buffLen, 
                                                      GENFSK_GetTimestamp() + 100000))
                {
                    Serial_Print(mAppSerId, cu8RangeTxMessages[1], gAllowToBlock_d);
                    rangeTxState = gRangeTxStateIdle_c;
                }
                else
                {
                    rangeTxState = gRangeTxStateRunningTest_c;
                }
#endif /* ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable)) */
            }
        }  
#if ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable))
        if(gCtEvtWakeUp_c == evType)
        {
            gTxPacket.payload[0] = 0x00;
            gTxPacket.header.lengthField = gGenFskMinPayloadLen_c;
            GENFSK_PacketToByteArray(mAppGenfskId, &gTxPacket, gTxBuffer);
            
            buffLen = gTxPacket.header.lengthField + 
                (gGenFskDefaultHeaderSizeBytes_c) + 
                    (gGenFskDefaultSyncAddrSize_c + 1);
            
            if(gGenfskSuccess_c != GENFSK_StartTx(mAppGenfskId,
                                                  gTxBuffer, 
                                                  buffLen, 
                                                  0))
            {
                Serial_Print(mAppSerId, cu8RangeTxMessages[1], gAllowToBlock_d);
                rangeTxState = gRangeTxStateIdle_c;
            }
            else
            {
                rangeTxState = gRangeTxStateRunningTest_c;
            }
        }
#endif /* ((cPWR_UsePowerDownMode) && (cPWR_GENFSK_LL_Enable)) */
        break;
    case gRangeTxStateIdle_c:
        if((gCtEvtUart_c == evType) && 
           ('\r' == u8UartData))
        {
            rangeTxState = gRangeTxStateInit_c;
            pNotifyAppThread();
        }
        break;
    default:
        break;
    }
    return bReturnFromSM;      
}


/****************************************************************************
*****************************Continuous Tests********************************
****************************************************************************/
/*! ************************************************************************
* \brief  Restores RBME configuration for continuous tests
*************************************************************************** */
#if defined (RADIO_IS_GEN_3P5)
static void CT_RestoreRbmeConfiguration(bool_t *rbme_rec_required)
{
    if(*rbme_rec_required)
    {
        /*Restore whitener and crc config (RBME parameter) due to XCVR_ChangeMode() API called inside XCVR_DftTxPatternReg() or
        the XCVR_DftTxLfsrReg() APIs*/
        /*set whitener config*/
        GENFSK_SetWhitenerConfig(mAppGenfskId, &whitenConfig);
        /*set crc config*/
        GENFSK_SetCrcConfig(mAppGenfskId, &crcConfig);
        *rbme_rec_required = FALSE;
    }
}
#endif
/*! ************************************************************************
* \brief  Handles continuous tests
*************************************************************************** */
bool_t CT_ContinuousTests(ct_event_t evType, void* pAssociatedValue)
{
    static ct_cont_tests_states_t contTestState = gContStateInit_c;
    static ct_cont_tests_states_t prevState = gContStateInvalid_c;
#if defined (RADIO_IS_GEN_3P5)
    const xcvr_coding_config_t *rbme_config = &xcvr_ble_uncoded_config;
#endif
    ct_rx_indication_t* pIndicationInfo = NULL;
    uint32_t u32RandomValue = 0;
    uint16_t buffLen = 0;
    uint16_t u16Idx = 0;
    uint8_t u8ByteCount = 0;
    uint8_t u8UartData = 0xFF;
    
    bool_t bRestartRx = FALSE;
    bool_t bReturnFromSM = FALSE;
    
#if defined (RADIO_IS_GEN_3P5)
    xcvr_config_t xcvr_config;
    const xcvr_config_t *p_xcvr_config = &xcvr_config;
    xcvr_currConfig_t currConfig;
    xcvr_currConfig_t * p_currConfig = &currConfig;
    uint8_t chanNum;
    genfskRadioMode_t radioModeIn;
    genfskDataRate_t  dataRate;
    
    static bool_t is_rbme_recovery_required = FALSE;
#endif
    
    if(gCtEvtUart_c == evType)
    {
        u8UartData = *((uint8_t*)pAssociatedValue);
    }
    /*if continuous tx test go through idle so that channel and tx power can
      be changed during test*/
    if((gContStateRunModTxOne_c <= prevState &&
       gContStateRunUnmodTx_c >= prevState) || 
       gContStateRunIdle_c == prevState)
    {
#if defined (RADIO_IS_GEN_3P5)
        XCVR_DftTxOff();
        /* Remember continuous mode has been used (XCVR_ChangeMode() API called) */
        is_rbme_recovery_required = TRUE;
#else
        XcvrFskIdle();
#endif

        if('1' <= u8UartData &&
               '8' >= u8UartData)
        {
            /* Do not print out RF params yet but postpone print
            when sub-menu state is reached (gContStateRunModTxOne_c, ...) */
        }
        else
        {
            if(CT_ApplyPrintConfigParams())
            {
                contTestState = prevState;
            }
        }
    }
    else
    {
        if('1' <= u8UartData &&
               '8' >= u8UartData)
        {
            /* Do not print out RF params yet but postpone print
            when sub-menu state is reached (gContStateRunModTxOne_c, ...) */
        }
        else
        {
            (void)CT_ApplyPrintConfigParams();          
        }
    }
    
#if defined (RADIO_IS_GEN_3P5)
    chanNum  = GENFSK_GetChannelNumber(mAppGenfskId);
    
    /* If packet mode is used and continuous mode was used previously, restore whitener and crc config 
        (RBME parameter) due to XCVR_ChangeMode() API called inside XCVR_DftTxPatternReg() or the XCVR_DftTxLfsrReg() APIs*/
    if ((contTestState == gContStateRunPRBS_c) || (contTestState == gContStateRunRx_c) ||
        (contTestState == gContStateRunEd_c))
    {
        CT_RestoreRbmeConfiguration(&is_rbme_recovery_required);
    }
#endif

    
    switch(contTestState)
    {
    case gContStateInit_c:
        PrintMenu(cu8ShortCutsBar, mAppSerId);
        PrintMenu(cu8ContinuousTestMenu, mAppSerId); 
        PrintTestParams(gaConfigParams, FALSE, mAppSerId);
        CT_EnableShortcuts(TRUE);
        contTestState = gContStateSelectTest_c;
        break;
    case gContStateSelectTest_c:
        if(gCtEvtUart_c == evType)
        {
            if('1' <= u8UartData &&
               '8' >= u8UartData)
            {
                contTestState = (ct_cont_tests_states_t)((u8UartData - '1') + 
                                                         gContStateRunIdle_c);
                prevState = contTestState;
                pNotifyAppThread();
            }
            else if('p' == u8UartData)
            {
#if defined (RADIO_IS_GEN_3P5)              
                /* When leaving continuous mode, restore whitener and crc config (RBME parameter)
                to be used for next tests (continous packet tests, PER tests or Range tests. */
                CT_RestoreRbmeConfiguration(&is_rbme_recovery_required);
#endif                

                CT_EnableShortcuts(TRUE);
                bReturnFromSM = TRUE;
                prevState     = gContStateInvalid_c;
                contTestState = gContStateInit_c;
            }
        }
        break;
    case gContStateRunIdle_c:
        Serial_Print(mAppSerId, cu8ContMessages[7], gAllowToBlock_d);
        contTestState = gContStateSelectTest_c;
        break;
    case gContStateRunPRBS_c:
        if(gCtEvtTxDone_c == evType ||   /* if packet is sent */
           gCtEvtSelfEvent_c == evType) /* if first run */
        {
            if(gCtEvtSelfEvent_c == evType)
            {
                CT_EnableShortcuts(FALSE);
                Serial_Print(mAppSerId, cu8ContMessages[0], gAllowToBlock_d);
            }
            /*set payload length with user set value*/
            gTxPacket.header.lengthField = gaConfigParams[gConfParamPayload].paramValue.decValue;
            /*calculate buffer length*/
            buffLen = gTxPacket.header.lengthField+
                (gGenFskDefaultHeaderSizeBytes_c)+
                    (gGenFskDefaultSyncAddrSize_c + 1);
            /*fill the payload*/
            for(u16Idx = 0; u16Idx < gTxPacket.header.lengthField; u16Idx++)
            {
               if(u8ByteCount == 0)
               {
                   RNG_GetRandomNo(&u32RandomValue); /*get 4 bytes from RNG*/
                   u8ByteCount = 4;
               }
               --u8ByteCount;
               gTxPacket.payload[u16Idx] = 
                   (uint8_t)(u32RandomValue >> (u8ByteCount << 3));
            }
            /*convert the packet to generic fsk formatted byte array*/
            GENFSK_PacketToByteArray(mAppGenfskId, &gTxPacket, gTxBuffer);
            if(gGenfskSuccess_c != GENFSK_StartTx(mAppGenfskId, gTxBuffer, buffLen, 0))
            {
                Serial_Print(mAppSerId, cu8ContMessages[1], gAllowToBlock_d);
                contTestState = gContStateIdle_c;
            }
        }
        if(gCtEvtUart_c == evType && 
           ' ' == u8UartData)
        {
            GENFSK_AbortAll();
            Serial_Print(mAppSerId, cu8ContMessages[2], gAllowToBlock_d);
            contTestState = gContStateIdle_c; 
        }
        break;
    case gContStateRunModTxOne_c:
#if defined (RADIO_IS_GEN_3P5)        
        XCVR_GetCurrentConfig(p_currConfig);
        CT_WrapperRadioModeAndDataRate(p_currConfig, &radioModeIn, &dataRate);
        GENFSK_GetXcvrConfig(radioModeIn, dataRate, &p_xcvr_config);
        XCVR_DftTxPatternReg(chanNum, &p_xcvr_config, &rbme_config,0xFFFFFFFFU);
#if defined(gBoard_ExtPaSupport_d) && (gBoard_ExtPaSupport_d > 0)
        (void) BOARD_ExtPaXcvrInit(FALSE);
#endif
#else
        XcvrFskLoadPattern(0xFFFFFFFFU);
        XcvrFskModTx();
#endif
        Serial_Print(mAppSerId, cu8ContMessages[8], gAllowToBlock_d);
        contTestState = gContStateSelectTest_c;
        break;
    case gContStateRunModTxZero_c:
#if defined (RADIO_IS_GEN_3P5)
        XCVR_GetCurrentConfig(p_currConfig);
        CT_WrapperRadioModeAndDataRate(p_currConfig, &radioModeIn, &dataRate);
        GENFSK_GetXcvrConfig(radioModeIn, dataRate, &p_xcvr_config);
        XCVR_DftTxPatternReg(chanNum, &p_xcvr_config, &rbme_config, 0x00000000);
#if defined(gBoard_ExtPaSupport_d) && (gBoard_ExtPaSupport_d > 0)
        (void) BOARD_ExtPaXcvrInit(FALSE);
#endif
#else
        XcvrFskLoadPattern(0x00000000);
        XcvrFskModTx();
#endif
        Serial_Print(mAppSerId, cu8ContMessages[9], gAllowToBlock_d);
        contTestState = gContStateSelectTest_c;
        break;
    case gContStateRunModTxPN_c:
#if defined (RADIO_IS_GEN_3P5)
        XCVR_GetCurrentConfig(p_currConfig);
        CT_WrapperRadioModeAndDataRate(p_currConfig, &radioModeIn, &dataRate);
        GENFSK_GetXcvrConfig(radioModeIn, dataRate, &p_xcvr_config);
        XCVR_DftTxLfsrReg(chanNum, &p_xcvr_config, &rbme_config, 3U /* arbitrary choice */);
#if defined(gBoard_ExtPaSupport_d) && (gBoard_ExtPaSupport_d > 0)
        (void) BOARD_ExtPaXcvrInit(FALSE);
#endif
#else
        XcvrFskTxRand();
#endif
        Serial_Print(mAppSerId, cu8ContMessages[10], gAllowToBlock_d);
        contTestState = gContStateSelectTest_c;
        break;
    case gContStateRunUnmodTx_c:
    {
#if defined (RADIO_IS_GEN_3P5)
        uint32_t rf_freq = (2360U + chanNum)*1000000U; /* In Hertz */
        XCVR_DftTxCW(rf_freq);
#if defined(gBoard_ExtPaSupport_d) && (gBoard_ExtPaSupport_d > 0)
        (void) BOARD_ExtPaXcvrInit(FALSE);
#endif
#else
        XcvrFskNoModTx();
#endif
        Serial_Print(mAppSerId, cu8ContMessages[11], gAllowToBlock_d);
        contTestState = gContStateSelectTest_c;
        break;
    }
    case gContStateRunRx_c:
        if(gCtEvtUart_c == evType &&
           (' ' == u8UartData))
        {
            GENFSK_AbortAll();
            Serial_Print(mAppSerId, cu8ContMessages[5], gAllowToBlock_d);
            contTestState = gContStateIdle_c;  
        }
        if(gCtEvtRxDone_c == evType)
        {
            pIndicationInfo = (ct_rx_indication_t*)pAssociatedValue;
            Serial_Print(mAppSerId, cu8ContMessages[6], gAllowToBlock_d);

            Serial_PrintDec(mAppSerId, pIndicationInfo->bufferLength);
            Serial_Print(mAppSerId, " bytes: ", gAllowToBlock_d);

            if( pIndicationInfo->bufferLength <= 50 )
            {
                Serial_PrintHex(mAppSerId, 
                                pIndicationInfo->pBuffer, 
                                pIndicationInfo->bufferLength, 
                                gPrtHexBigEndian_c);
            }
            else
            {
                Serial_PrintHex(mAppSerId, 
                                pIndicationInfo->pBuffer, 
                                25, 
                                gPrtHexBigEndian_c);
                Serial_Print(mAppSerId, "...", gAllowToBlock_d);
                Serial_PrintHex(mAppSerId, 
                                pIndicationInfo->pBuffer+pIndicationInfo->bufferLength-25, 
                                25,
                                gPrtHexBigEndian_c);
            }
            bRestartRx = TRUE;
            
        }
        else if(gCtEvtRxFailed_c == evType ||
                gCtEvtSeqTimeout_c == evType)
        {
            GENFSK_AbortAll();
            bRestartRx = TRUE;
        }
        if(gCtEvtSelfEvent_c == evType)
        {
            CT_EnableShortcuts(FALSE);
            Serial_Print(mAppSerId, cu8ContMessages[3], gAllowToBlock_d);
            bRestartRx = TRUE;
        }
        if(bRestartRx)
        {
            if(gGenfskSuccess_c != 
               GENFSK_StartRx(mAppGenfskId,
                              gRxBuffer, 
                              gGenFskDefaultMaxBufferSize_c + crcConfig.crcSize, 
                              0, 
                              0))
            {
                Serial_Print(mAppSerId, cu8ContMessages[4], gAllowToBlock_d);
                contTestState = gContStateIdle_c;
            }
        }
        break;
    case gContStateRunEd_c:
        if(gCtEvtSelfEvent_c == evType)
        {
            CT_EnableShortcuts(FALSE);
            TMR_StartIntervalTimer(mAppTmrId, 50, pTmrCallback, NULL);
        }
        if(gCtEvtUart_c == evType &&
           (' ' == u8UartData))
        {
            TMR_StopTimer(mAppTmrId);
            Serial_Print(mAppSerId, cu8ContMessages[12], gAllowToBlock_d);
            contTestState = gContStateIdle_c;  
        }
        if(gCtEvtTimerExpired_c == evType)
        {
#if defined (RADIO_IS_GEN_3P5)
            PrintCrtRssi((int8_t)XCVR_GetInstantRssi(), mAppSerId);
#else
            PrintCrtRssi((int8_t)XcvrFskGetInstantRssi(), mAppSerId);
#endif
        }
        break;
    case gContStateIdle_c:
        if(gCtEvtUart_c == evType &&
           ('\r' == u8UartData))
        {
            contTestState = gContStateInit_c;
            pNotifyAppThread();
        }
    default:
        break;
    }
    
    return bReturnFromSM;    
}

/*! *********************************************************************************
* \brief  Updates the corresponding parameter depending on key pressed
********************************************************************************** */
bool_t CT_UpdateShortcutKeyParam(uint8_t u8PressedKey)
{
    ct_config_params_t* pConfig;
    bool_t bReturnFlag = TRUE;

    switch(u8PressedKey)
    {
    case 't':
        pConfig = &gaConfigParams[gConfParamMode];
        pConfig->paramValue.stringValue[0] = 'T';
        break;
    case 'r':
        pConfig = &gaConfigParams[gConfParamMode];
        pConfig->paramValue.stringValue[0] = 'R';
        break;
    case 'q': 
        pConfig = &gaConfigParams[gConfParamChannel];
        if(pConfig->paramValue.decValue == gGenFskMaxChannel_c)
        {
            pConfig->paramValue.decValue = gGenFskMinChannel_c;
        }
        else
        {
            pConfig->paramValue.decValue++;
        }
        break;
    case 'w':
        pConfig = &gaConfigParams[gConfParamChannel];
        if(pConfig->paramValue.decValue == gGenFskMinChannel_c)
        {
            pConfig->paramValue.decValue = gGenFskMaxChannel_c;
        }
        else
        {
            pConfig->paramValue.decValue--;
        }
        break;
    case 'a':
        pConfig = &gaConfigParams[gConfParamPower];
        pConfig->paramValue.decValue++;
        if(gGenFskMaxTxPowerLevel_c < pConfig->paramValue.decValue)
        {
            pConfig->paramValue.decValue = gGenFskMinTxPowerLevel_c;
        }
#ifdef RADIO_IS_GEN_3P5
        CT_HandleHighLowPower();
#endif /* RADIO_IS_GEN_3P5 */
        break;
    case 's':
        pConfig = &gaConfigParams[gConfParamPower];
        if( pConfig->paramValue.decValue == gGenFskMinTxPowerLevel_c)
        {
             pConfig->paramValue.decValue = gGenFskMaxTxPowerLevel_c;
        }
        else
        {
             pConfig->paramValue.decValue--;	
        }
#ifdef RADIO_IS_GEN_3P5
        CT_HandleHighLowPower();
#endif /* RADIO_IS_GEN_3P5 */
        break;
    case 'n':
        pConfig = &gaConfigParams[gConfParamPayload];
        pConfig->paramValue.decValue++;
        if(gGenFskMaxPayloadLen_c < pConfig->paramValue.decValue)
        {
            pConfig->paramValue.decValue = gGenFskMinPayloadLen_c;
        }    
        break;
    case 'm':
        pConfig = &gaConfigParams[gConfParamPayload];
        pConfig->paramValue.decValue--;
        if(gGenFskMinPayloadLen_c > pConfig->paramValue.decValue)
        {
            pConfig->paramValue.decValue = gGenFskMaxPayloadLen_c;
        }    
        break;
    case 'd':
        pConfig = &gaConfigParams[gConfParamXtalTrim];
        if(pConfig->paramValue.decValue == gMaxTrimValue_c)
        {
            pConfig->paramValue.decValue = gMinTrimValue_c;
        }
        else
        {
            pConfig->paramValue.decValue++;
        }
        break;
    case 'f':
        pConfig = &gaConfigParams[gConfParamXtalTrim];
        if( pConfig->paramValue.decValue == gMinTrimValue_c)
        {
             pConfig->paramValue.decValue = gMaxTrimValue_c;
        }
        else
        {
             pConfig->paramValue.decValue--;	
        }
        break;
    case 'z':
        pConfig = &gaConfigParams[gConfParamRateMode];
        if(pConfig->id == gMaxRate_c)
        {
            pConfig->id = gMinRate_c;
        }
        else
        {
            pConfig->id++;
        }
        break;
    case 'x':
        pConfig = &gaConfigParams[gConfParamRateMode];
        if( pConfig->id == gMinRate_c)
        {
             pConfig->id = gMaxRate_c;
        }
        else
        {
             pConfig->id--;	
        }
        break;
    case 'c':
        pConfig = &gaConfigParams[gConfParamWhitenMode];
        pConfig->id++;
        pConfig->id = pConfig->id%gMaxWhitenMode_c;
        break;
    case '\r':
        /* Print configuration parameters. */
        break;
        
#if defined(gBoard_ExtPaSupport_d) && (gBoard_ExtPaSupport_d > 0)
    case 'g':
        pConfig = &gaConfigParams[gConfParamExPaGain];
        pConfig->id ^=1;
        break;

    case 'i':
        pConfig = &gaConfigParams[gConfParamExPaAnt];
        pConfig->id ^=1;
        break;
#endif

    default:
        bReturnFlag = FALSE;
        break;
    };
    
    return bReturnFlag;
}

/*! *********************************************************************************
* \brief  Checks if shortcuts can be used
********************************************************************************** */
bool_t CT_IsShortcutMenuEnabled(void)
{
    return bEnableShortcuts;
}

#ifdef RADIO_IS_GEN_3P5
/*! *********************************************************************************
* \brief  Handles the activation/deactivation of low/high power trasnmit levels
********************************************************************************** */
static void CT_HandleHighLowPower(void)
{
    genfskStatus_t status;
        
    if (GENFSK_IsHighPowerConfigured() == 0x1U)
    {
        if (gaConfigParams[gConfParamPower].paramValue.decValue > gGenFskLastLowPowerIdx_c)
        {
            gaConfigParams[gConfParamPower].paramValue.decValue -= gGenFskLastLowPowerIdx_c + 1U;
        }
        else
        {
            gaConfigParams[gConfParamPower].paramValue.decValue += gGenFskLastLowPowerIdx_c + 1U;
        }
    }
    /* Enable high power TX */
    if (gaConfigParams[gConfParamPower].paramValue.decValue > gGenFskLastLowPowerIdx_c)
    {
        gaConfigParams[gConfParamPower].paramValue.decValue -= gGenFskLastLowPowerIdx_c + 1U;
        status = GENFSK_ConfigurePower(1U);
        if (status == gGenfskSuccess_c)
        {
            FLib_MemCpy(gaConfigParams[gConfParamPower].paramName, "Hi Power", 9);
        }
    }
    else /* Enable low power TX */
    {
        status = GENFSK_ConfigurePower(0U);
        if (status == gGenfskSuccess_c)
        {
           FLib_MemCpy(gaConfigParams[gConfParamPower].paramName, "Lo Power", 9);
        }
    }
}
#endif /* RADIO_IS_GEN_3P5 */

/*! *********************************************************************************
* \brief  Enables / Disables the shortcut keys
********************************************************************************** */
static void CT_EnableShortcuts(bool_t bEnable)
{
    bEnableShortcuts = bEnable;
}

/*! *********************************************************************************
* \brief  Calls Generic FSK api to set mode and rate and prints
*         the shortcuts values
********************************************************************************** */
static bool_t CT_ApplyPrintRateParams(void)
{
    bool_t bParamsUpdated = FALSE;
    
#ifdef RADIO_IS_GEN_3P5
    static const xcvr_coding_config_t *old_rbmeConfig = &xcvr_ble_uncoded_config;
    const xcvr_coding_config_t *rbmeConfig = &xcvr_ble_uncoded_config;
    uint8_t preamble_pattern    = 0U;
#endif
    GENFSK_mode_config_t modeConfig;
    GENFSK_packet_config_t packetConfig;
    uint8_t crtMode             = 0U;
    uint16_t preamble_size      = 0U;
    uint8_t lengthSizeBits      = gGenFskDefaultLengthFieldSize_c;
    uint8_t h1SizeBits          = gGenFskDefaultH1FieldSize_c;
    uint16_t h1Mask             = gGenFskDefaultH1Mask_c;
    
    (void)GENFSK_GetModeConfig(mAppGenfskId, &modeConfig);
    (void)GENFSK_GetPacketConfig(mAppGenfskId, &packetConfig);
        
#ifdef RADIO_IS_GEN_3P5
    if (old_rbmeConfig == &xcvr_ble_coded_s2_config)
    {
        crtMode = gRateBle500Kbps_c;
    }
    else if (old_rbmeConfig == &xcvr_ble_coded_s8_config)
    {
        crtMode = gRateBle125Kbps_c;
    }
    else
    {
        crtMode = crtRate[radioConfig.dataRate];
        if ((modeConfig.mode == gGenfskBleLrMode) || (modeConfig.mode == gGenfskBleUncodedMode))
        {
            crtMode += gRateBle125Kbps_c;
        }
    }
#else
    crtMode = crtRate[radioConfig.dataRate];
    if (modeConfig.mode == gGenfskBleUncodedMode)
    {
        crtMode += gRateBle1Mbps_c - 2;
    }
#endif /* RADIO_IS_GEN_3P5 */

    if(gaConfigParams[gConfParamRateMode].id != crtMode)
    {
        /* Determine mode */
        genfskMode_t        mode = gGenfskGllMode; 
        
        if (gaConfigParams[gConfParamRateMode].id <= gMaxRateGenfsk_c)
        {
            mode = gGenfskGllMode;
        }
#ifdef RADIO_IS_GEN_3P5
        else if (gaConfigParams[gConfParamRateMode].id <= gRateBle500Kbps_c)
        {
            mode = gGenfskBleLrMode;
            preamble_size = 9U;
            preamble_pattern = 0x3C;
            lengthSizeBits = 8U;
            h1SizeBits     = 0U;
            h1Mask         = 0U;
            if (gaConfigParams[gConfParamRateMode].id == gRateBle500Kbps_c)
            {
                rbmeConfig = &xcvr_ble_coded_s2_config;
            }
            else
            {
                rbmeConfig = &xcvr_ble_coded_s8_config;
            }
        }
#endif /* RADIO_IS_GEN_3P5 */
        else
        {
            mode = gGenfskBleUncodedMode;

            if (gaConfigParams[gConfParamRateMode].id == gRateBle1Mbps_c)
            {
                preamble_size = 0U;
            }
#ifdef RADIO_IS_GEN_3P5
            else
            {
                preamble_size = 1U;
            }
            preamble_pattern = 0U;
#endif
            lengthSizeBits = 8U;
            h1SizeBits     = 0U;
            h1Mask         = 0U;
        }
          
        /* Determine rate */
        genfskDataRate_t    rate = (genfskDataRate_t)targetRate[gaConfigParams[gConfParamRateMode].id];

        /* Mode change detected */
        if (mode != modeConfig.mode)
        {
            genfskMode_t old_mode = mModeConfig.mode;
            mModeConfig.mode = mode;
            if(gGenfskSuccess_c != GENFSK_SetModeConfig(mAppGenfskId, &mModeConfig))
            {
                gaConfigParams[gConfParamRateMode].id = crtMode;
                mModeConfig.mode = old_mode;
            }
            else
            {
                bParamsUpdated = TRUE;
            }
#ifdef RADIO_IS_GEN_3P5
            {
                /* Whitening specific configuration (withen init depending on channel) only applies to BLE */
                if ((mModeConfig.mode == gGenfskBleLrMode) || (mModeConfig.mode == gGenfskBleUncodedMode))
                {
                    GENFSK_SetBleWhitenInit(mAppGenfskId, GENFSK_GetChannelNumber(mAppGenfskId));
                }
                else
                {
                    /* Restore GENFSK whitening configuration */
                    GENFSK_SetWhitenerConfig(mAppGenfskId, &whitenConfig);
                }
            }
#endif
        }
        
#ifdef RADIO_IS_GEN_3P5
        /* Rate change detected or rbme configuration changed*/
        if ((rate != radioConfig.dataRate) || (old_rbmeConfig != rbmeConfig))
#else
        if (rate != radioConfig.dataRate)
#endif
        {
            genfskDataRate_t old_rate = radioConfig.dataRate;
            radioConfig.dataRate = rate;
#ifdef RADIO_IS_GEN_3P5
            if(gGenfskSuccess_c != GENFSK_RadioConfigWithRbme(mAppGenfskId, &radioConfig, &rbmeConfig))
#else
            if(gGenfskSuccess_c != GENFSK_RadioConfig(mAppGenfskId, &radioConfig))
#endif /* RADIO_IS_GEN_3P5 */
            {
                gaConfigParams[gConfParamRateMode].id = crtMode;
                radioConfig.dataRate = old_rate;
            }
            else
            {
                GENFSK_whitener_config_t whitenerUpdatedConfig;
                
                /* Reads the current whitening configuration (as the whitening init may have been updated previously due to a channel update) */
                GENFSK_GetWhitenerConfig(mAppGenfskId, &whitenerUpdatedConfig);
                /*Restore whitener and crc config (RBME parameter) due to XCVR_ChangeMode()*/
                /*set whitener config*/
                GENFSK_SetWhitenerConfig(mAppGenfskId, &whitenerUpdatedConfig);
                /*set crc config*/
                GENFSK_SetCrcConfig(mAppGenfskId, &crcConfig);
#ifdef RADIO_IS_GEN_3P5
                /* Workaround to set SPOV_EN=1 for S2 */
                if (rbmeConfig == &xcvr_ble_coded_s2_config)
                {
                    RBME->SPREAD_CFG |= RBME_SPREAD_CFG_SPOV_EN(1);
                }
#endif /* RADIO_IS_GEN_3P5 */
                bParamsUpdated = TRUE;
            }
        }
#ifdef RADIO_IS_GEN_3P5
        old_rbmeConfig = rbmeConfig;

        if ((packetConfig.preambleSizeBytes != preamble_size) || (packetConfig.preambleBytePattern != preamble_pattern) ||
            (packetConfig.lengthSizeBits != lengthSizeBits) || (packetConfig.h1SizeBits != h1SizeBits) ||
            (packetConfig.h1Mask != h1Mask))
#else
        if ((packetConfig.preambleSizeBytes != preamble_size) || (packetConfig.lengthSizeBits != lengthSizeBits) || 
            (packetConfig.h1SizeBits != h1SizeBits) || (packetConfig.h1Mask != h1Mask))           
#endif /* RADIO_IS_GEN_3P5 */
        {
            GENFSK_packet_config_t old_packetConfig = packetConfig;
            packetConfig.preambleSizeBytes      = preamble_size;
#if defined (RADIO_IS_GEN_3P5)
            packetConfig.preambleBytePattern    = preamble_pattern;
#endif /* RADIO_IS_GEN_3P5 */
            packetConfig.lengthSizeBits         = lengthSizeBits;
            packetConfig.h1SizeBits             = h1SizeBits;
            packetConfig.h1Mask                 = h1Mask;
              
            if(gGenfskSuccess_c != GENFSK_SetPacketConfig(mAppGenfskId, &packetConfig))
            {
                gaConfigParams[gConfParamRateMode].id = crtMode;
                packetConfig = old_packetConfig;
            }
            else
            {
                bParamsUpdated = TRUE;
            }
        }
    }
        
    return bParamsUpdated;
}
/*! *********************************************************************************
* \brief  Calls Generic FSK api to set channel and tx power level and prints
*         the shortcuts values
********************************************************************************** */
static bool_t CT_ApplyPrintConfigParams(void)
{
    bool_t bParamsUpdated = FALSE;
#ifdef RADIO_IS_GEN_3P5
    static genfskMode_t old_mode = gGenfskGllMode;
    static uint8_t old_whiten_mode = gDefaultWhitenMode_c;
    bool_t update_whitening = false;
#endif /* RADIO_IS_GEN_3P5 */
    if(CT_IsShortcutMenuEnabled())
    {
        uint8_t crtChannel = GENFSK_GetChannelNumber(mAppGenfskId);
        uint8_t crtPwr     = GENFSK_GetTxPowerLevel(mAppGenfskId);
        
        bParamsUpdated = CT_ApplyPrintRateParams();

        if(gaConfigParams[gConfParamChannel].paramValue.decValue != crtChannel)
        {
            if(gGenfskSuccess_c != 
               GENFSK_SetChannelNumber(mAppGenfskId, (uint8_t)gaConfigParams[gConfParamChannel].paramValue.decValue))
            {
                gaConfigParams[gConfParamChannel].paramValue.decValue = crtChannel;
            }
            else
            {
                bParamsUpdated = TRUE;
#ifdef RADIO_IS_GEN_3P5
                update_whitening = true;
#endif /* RADIO_IS_GEN_3P5 */
            }
        }
        
#ifdef RADIO_IS_GEN_3P5
        GENFSK_mode_config_t modeConfig;
            
        (void)GENFSK_GetModeConfig(mAppGenfskId, &modeConfig);
        /* Upon mode change (BLE/GENFSK) or whiten mode change */
        if ((old_mode != modeConfig.mode) || (old_whiten_mode != gaConfigParams[gConfParamWhitenMode].id))
        {
            update_whitening = true;
        }
        /* Whitening specific configuration (withen init depending on channel) only applies to BLE */
        if (update_whitening)
        {            
            if ((modeConfig.mode == gGenfskBleLrMode) || (modeConfig.mode == gGenfskBleUncodedMode))
            {
                uint8_t channelNum = gaConfigParams[gConfParamChannel].paramValue.decValue;
                if (gaConfigParams[gConfParamWhitenMode].id == gWhitenFixed_c)
                {
                    /* If fixed whitening is selected always use the whitening configuration for BLE channel 37 
                    (corresponds to 42 in genfsk). */
                    channelNum = 42U;
                }
                GENFSK_SetBleWhitenInit(mAppGenfskId, channelNum);
            }
            update_whitening = false;
        }
        old_mode = modeConfig.mode;
        old_whiten_mode = gaConfigParams[gConfParamWhitenMode].id;
#endif

        if(gaConfigParams[gConfParamPower].paramValue.decValue != crtPwr)
        {
            if(gGenfskSuccess_c !=
               GENFSK_SetTxPowerLevel(mAppGenfskId, gaConfigParams[gConfParamPower].paramValue.decValue))
            {
                gaConfigParams[gConfParamPower].paramValue.decValue = crtPwr;
            }
            else
            {
                bParamsUpdated = TRUE;
            }
        }

        if(gaConfigParams[gConfParamXtalTrim].paramValue.decValue != xtalTrim)
        {
            if( GENFSK_SetXtalTrim(gaConfigParams[gConfParamXtalTrim].paramValue.decValue) != gGenfskSuccess_c )
            {
                gaConfigParams[gConfParamXtalTrim].paramValue.decValue = xtalTrim;
            }
            else
            {
                xtalTrim = gaConfigParams[gConfParamXtalTrim].paramValue.decValue;
                bParamsUpdated = TRUE;
            }
        } 
        
#if defined(gBoard_ExtPaSupport_d) && (gBoard_ExtPaSupport_d > 0)
        if( gaConfigParams[gConfParamExPaGain].id != extPaMode )
        {
            if( gaConfigParams[gConfParamExPaGain].id == 0 )
            {
                BOARD_ExtPaBypassDisable();           
            }
            else
            {
                BOARD_ExtPaBypassEnable();
            }
            extPaMode = gaConfigParams[gConfParamExPaGain].id;
            bParamsUpdated = TRUE;
            Serial_Print(mAppSerId, " ggggggggg ", gAllowToBlock_d);
        }

        if( gaConfigParams[gConfParamExPaAnt].id != extPaAnt )
        {
            if( gaConfigParams[gConfParamExPaAnt].id == 0 )
            {
                BOARD_ExtPaSelAnt1();
            }
            else
            {
                BOARD_ExtPaSelAnt2();
            }
            extPaAnt = gaConfigParams[gConfParamExPaAnt].id;
            bParamsUpdated = TRUE;
            Serial_Print(mAppSerId, " iiiiiiiiii ", gAllowToBlock_d);
        }
#endif

        PrintTestParams(gaConfigParams, TRUE, mAppSerId);
    }
    return bParamsUpdated;
}
#if defined (RADIO_IS_GEN_3P5)
/*! *********************************************************************************
* \brief  Converts radio_mode_t to genfskRadioMode_t & data_rate_t to genfskDataRate_t
*         This is used to provide the right types to GENFSK_GetXcvrConfig() after a 
*         call to XCVR_GetCurrentConfig().
********************************************************************************** */
static void CT_WrapperRadioModeAndDataRate(xcvr_currConfig_t * pCurrConfig, genfskRadioMode_t* pRadioModeIn, genfskDataRate_t*  pDataRate)
{
    *pRadioModeIn = gGenfskGfskBt0p5h0p5;
    *pDataRate = gGenfskDR1Mbps;
    
    if ((pCurrConfig->radio_mode >= GFSK_BT_0p5_h_0p5) && (pCurrConfig->radio_mode <= RESERVED4_MODE))
    {
        *pRadioModeIn = (genfskRadioMode_t)((uint8_t)pCurrConfig->radio_mode - GFSK_BT_0p5_h_0p5);
    }
    else
    {
        /* Conversion cannot be done */
        assert(0U);
    }
    if (pCurrConfig->data_rate <= DR_2MBPS)
    {
        *pDataRate = (genfskDataRate_t)(pCurrConfig->data_rate);
    }
    else
    {
        /* Conversion cannot be done */
        assert(0U);
    }
}
#endif

/********************************************************************************
*****************************Adjust RTC XTAL Menu********************************
********************************************************************************/
bool_t CT_TrimAdjust(ct_event_t evType, void* pAssociatedValue)
{
    static ct_trim_test_states_t trimStateTest = gTrimStateInit_c;
    bool_t bReturnFromSM = FALSE;
    uint8_t u8UartData = 0xFF;
    static uint8_t aTrimValue;
    uint8_t aWRTrimValue;

    switch (trimStateTest)
    {
        case gTrimStateInit_c:
        {
            /* Print Menu, Stop Flash All LEDs and configure PTB3 for frequency measurement */
            PrintMenu(cu8RTCTrimMenu, mAppSerId);
            LED_StopFlashingAllLeds();
            LED_UnInit();
            CLOCK_EnableClock(kCLOCK_Rtc0);                                             /*Enable RTC clock gating*/
            CLOCK_EnableClock(kCLOCK_PortB);                                            /*Enable PORTB clock gating*/
            PORTB->PCR[3] = (PORTB->PCR[3] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(7);     /*Mux the RTC_CLKOUT to PTB3*/
            SIM->SOPT1 |= SIM_SOPT1_OSC32KOUT(1);                                       /*Select the 32kHz reference for RTC_CLKOUT signal*/
            aTrimValue = RTC->CR;
            aTrimValue = (((aTrimValue & RTC_CR_SC2P_MASK)>>13U) |                         /*Get the RTC Trim Value*/
                         ((aTrimValue & RTC_CR_SC4P_MASK)>>11U)  |
                         ((aTrimValue & RTC_CR_SC8P_MASK)>>9U)   |
                         ((aTrimValue & RTC_CR_SC16P_MASK)>>7U));
            /* Print Trim Value */
            Serial_Print(mAppSerId, "\rTrim RTC Capacitance Value ", gAllowToBlock_d);
            Serial_PrintDec(mAppSerId, aTrimValue);
            Serial_Print(mAppSerId, " pF ", gAllowToBlock_d);
            /* Move to the next state */
            trimStateTest = gTrimStateRun_c;
        }
        break;

        case gTrimStateRun_c:
        {
            if(gCtEvtUart_c == evType)
            {
                u8UartData = *((uint8_t*)pAssociatedValue);

                /* Increment Trim Value */
                if('1' == u8UartData)
                {
                    if(aTrimValue<0xF)
                    {
                        aTrimValue++;

                        /* Reverse the trim value to fit in the register fields */
                        aWRTrimValue = (aTrimValue & 0x1)<<3;
                        aWRTrimValue |= (aTrimValue & 0x2)<<1;
                        aWRTrimValue |= (aTrimValue & 0x4)>>1;
                        aWRTrimValue |= (aTrimValue & 0x8)>>3;

                        RTC->CR &= ~RTC_CR_OSCE_MASK;
                        RTC->CR = (RTC->CR & ~(RTC_CR_SC2P_MASK | RTC_CR_SC4P_MASK | RTC_CR_SC8P_MASK | RTC_CR_SC16P_MASK)) | (aWRTrimValue<<10U);
                        RTC->CR |= RTC_CR_OSCE_MASK;
                    }
                }
                /* Decrement Trim Value */
                else if('2' == u8UartData)
                {
                    if(aTrimValue>0x0)
                    {
                        aTrimValue--;

                        /* Reverse the trim value to fit in the register fields */
                        aWRTrimValue = (aTrimValue & 0x1)<<3;
                        aWRTrimValue |= (aTrimValue & 0x2)<<1;
                        aWRTrimValue |= (aTrimValue & 0x4)>>1;
                        aWRTrimValue |= (aTrimValue & 0x8)>>3;

                        RTC->CR &= ~RTC_CR_OSCE_MASK;
                        RTC->CR = (RTC->CR & ~(RTC_CR_SC2P_MASK | RTC_CR_SC4P_MASK | RTC_CR_SC8P_MASK | RTC_CR_SC16P_MASK)) | (aWRTrimValue<<10U);
                        RTC->CR |= RTC_CR_OSCE_MASK;
                    }
                }
                /* Move MGC from FEI to FEE */
                else if('3' == u8UartData)
                {
                    BOARD_MoveClocktoFEE();
                    Serial_Print(mAppSerId, "\rThe MCG moved from FEI to FEE mode successfully! ", gAllowToBlock_d);
                    break;
                }
                /* Move MGC from FEE to FEI */
                else if('4' == u8UartData)
                {
                    BOARD_BootClockRUN();
                    Serial_Print(mAppSerId, "\rThe MCG moved from FEE to FEI mode successfully! ", gAllowToBlock_d);
                    break;
                }
                /* Exit from Trim RTC menu */
                else if('p' == u8UartData)
                {
                    /* Start Flash all LEDs, Stop PTB3 for frequency measurement */
                    SIM->SOPT1 &= ~SIM_SOPT1_OSC32KOUT(1);
                    CLOCK_DisableClock(kCLOCK_Rtc0); /*Enable RTC clock gating*/
                    LED_Init();
                    LED_StartSerialFlash(LED1);
                    trimStateTest = gTrimStateInit_c;
                    bReturnFromSM = TRUE;
                    break;
                }
                else
                {
                    break;
                }

                /* Print Trim Value */
                Serial_Print(mAppSerId, "\rTrim RTC Capacitance Value ", gAllowToBlock_d);
                Serial_PrintDec(mAppSerId, aTrimValue * 2U);
                Serial_Print(mAppSerId, " pF ", gAllowToBlock_d);
            }
        }
        break;

        default:
        break;
    }

    return bReturnFromSM;
}
