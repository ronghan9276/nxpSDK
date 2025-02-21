/*! *********************************************************************************
* \addtogroup FSCI_BLE
* @{
********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2019 NXP
* All rights reserved.
*
* \file
*
* This is a source file for FSCI BLE management.
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "EmbeddedTypes.h"
#include "fsci_ble_gap_types.h"


#if gFsciIncluded_c && gFsciBleGapLayerEnabled_d

/************************************************************************************
*************************************************************************************
* Private constants & macros
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

gapSmpKeys_t* fsciBleGapAllocSmpKeysForBuffer(uint8_t* pBuffer)
{
    bool_t          bLtkIncluded        = FALSE;
    uint8_t         ltkSize             = 0;
    bool_t          bIrkIncluded        = FALSE;
    uint8_t         irkSize             = 0;
    bool_t          bCsrkIncluded       = FALSE;
    uint8_t         csrkSize            = 0;
    uint8_t         randSize            = 0;
    bool_t          bAddressIncluded    = FALSE;
    uint8_t         addressSize         = 0;
    gapSmpKeys_t*   pSmpKeys;

    /* Verify if LTK is included or not */
    fsciBleGetBoolValueFromBuffer(bLtkIncluded, pBuffer);

    if(TRUE == bLtkIncluded)
    {
        /* Get LTK size from buffer */
        fsciBleGetUint8ValueFromBuffer(ltkSize, pBuffer);
    }

    /* Go to bIrkIncluded */
    pBuffer += ltkSize;

    /* Verify if IRK is included or not */
    fsciBleGetBoolValueFromBuffer(bIrkIncluded, pBuffer);

    if(TRUE == bIrkIncluded)
    {
        irkSize = gcSmpIrkSize_c;
    }

    /* Go to bIrkIncluded */
    pBuffer += irkSize;

    /* Verify if CSRK is included or not */
    fsciBleGetBoolValueFromBuffer(bCsrkIncluded, pBuffer);

    if(TRUE == bCsrkIncluded)
    {
        csrkSize = gcSmpCsrkSize_c;
    }

    /* Go to bRandIncluded */
    pBuffer += csrkSize;

    /* Random value is included only if LTK is included */
    if(TRUE == bLtkIncluded)
    {
        /* Get random value size from buffer */
        fsciBleGetUint8ValueFromBuffer(randSize, pBuffer);
    }

    /* Go to bAddressIncluded */
    pBuffer += randSize + ((TRUE == bLtkIncluded) ? sizeof(uint16_t) : 0U);

    /* Address is included only if IRK is included */
    if(TRUE == bIrkIncluded)
    {
        /* Verify if address is included or not */
        fsciBleGetBoolValueFromBuffer(bAddressIncluded, pBuffer);

        if(TRUE == bAddressIncluded)
        {
            addressSize =  gcBleDeviceAddressSize_c;
        }
    }

    /* Allocate buffer for SMP keys */
    pSmpKeys = (gapSmpKeys_t*)MEM_BufferAlloc(sizeof(gapSmpKeys_t) + (uint32_t)ltkSize + irkSize + csrkSize + randSize + addressSize);

    if(NULL == pSmpKeys)
    {
        /* No memory */
        return NULL;
    }

    /* Set pointers in gapSmpKeys_t structure */
    pSmpKeys->aLtk      = (uint8_t*)pSmpKeys + sizeof(gapSmpKeys_t);
    pSmpKeys->aIrk      = pSmpKeys->aLtk + ltkSize;
    pSmpKeys->aCsrk     = pSmpKeys->aIrk + irkSize;
    pSmpKeys->aRand     = pSmpKeys->aCsrk + csrkSize;
    pSmpKeys->aAddress  = pSmpKeys->aRand + randSize;

    if(FALSE == bLtkIncluded)
    {
        /* No LTK */
        pSmpKeys->aLtk  = NULL;
        /* No random value */
        pSmpKeys->aRand = NULL;
    }

    if(FALSE == bIrkIncluded)
    {
        /* No IRK */
        pSmpKeys->aIrk  = NULL;
    }

    if(FALSE == bCsrkIncluded)
    {
        /* No CSRK */
        pSmpKeys->aCsrk = NULL;
    }

    if(0U == randSize)
    {
        /* No random value */
        pSmpKeys->aRand = NULL;
    }

    if(FALSE == bAddressIncluded)
    {
        /* No address */
        pSmpKeys->aAddress = NULL;
    }

    /* Return the allocated buffer for SMP keys */
    return pSmpKeys;
}


gapSmpKeys_t *fsciBleGapAllocSmpKeys(void)
{
    gapSmpKeys_t   *pSmpKeys;

    /* Allocate buffer for SMP keys */
    pSmpKeys = (gapSmpKeys_t *)MEM_BufferAlloc(sizeof(gapSmpKeys_t) +
                                               gcSmpMaxLtkSize_c +
                                               gcSmpIrkSize_c +
                                               gcSmpCsrkSize_c +
                                               gcSmpMaxRandSize_c +
                                               gcBleDeviceAddressSize_c);

    if (NULL != pSmpKeys)
    {
        /* Set pointers in gapSmpKeys_t structure */
        pSmpKeys->aLtk      = (uint8_t *)pSmpKeys + sizeof(gapSmpKeys_t);
        pSmpKeys->aIrk      = pSmpKeys->aLtk + gcSmpMaxLtkSize_c;
        pSmpKeys->aCsrk     = pSmpKeys->aIrk + gcSmpIrkSize_c;
        pSmpKeys->aRand     = pSmpKeys->aCsrk + gcSmpCsrkSize_c;
        pSmpKeys->aAddress  = pSmpKeys->aRand + gcSmpMaxRandSize_c;
    }

    /* Return the allocated buffer for SMP keys or NULL if no memory is available */
    return pSmpKeys;
}


uint16_t fsciBleGapGetSmpKeysBufferSize(const gapSmpKeys_t* pSmpKeys)
{
    /* bLtkIncluded */
    uint16_t bufferSize = sizeof(bool_t);

    if(NULL != pSmpKeys->aLtk)
    {
        /* cLtkSIze and aLtk */
        bufferSize += sizeof(uint8_t) + (uint16_t)pSmpKeys->cLtkSize;
    }

    /* bIrkIncluded */
    bufferSize += sizeof(bool_t);

    if(NULL != pSmpKeys->aIrk)
    {
        /* aIrk */
        bufferSize += gcSmpIrkSize_c;
    }

    /* bCsrkIncluded */
    bufferSize += sizeof(bool_t);

    if(NULL != pSmpKeys->aCsrk)
    {
        /* aCsrk */
        bufferSize += gcSmpCsrkSize_c;
    }

    if(NULL != pSmpKeys->aLtk)
    {
        /* cRandSize, aRand and ediv */
        bufferSize += sizeof(uint8_t) + (uint16_t)pSmpKeys->cRandSize + sizeof(uint16_t);
    }

    if(NULL != pSmpKeys->aIrk)
    {
        /* bAddressIncluded */
        bufferSize += sizeof(bool_t);

        if(NULL != pSmpKeys->aAddress)
        {
            /* addressType and aAddress */
            bufferSize += sizeof(bleAddressType_t) + gcBleDeviceAddressSize_c;
        }
    }

    return bufferSize;
}


void fsciBleGapGetSmpKeysFromBuffer(gapSmpKeys_t* pSmpKeys, uint8_t** ppBuffer)
{
    bool_t  bLtkIncluded;
    bool_t  bIrkIncluded;
    bool_t  bCsrkIncluded;
    bool_t  bAddressIncluded;

    /* Read gapSmpKeys_t fields from buffer */

    /* Verify if LTK is included or not */
    fsciBleGetBoolValueFromBuffer(bLtkIncluded, *ppBuffer);

    if(TRUE == bLtkIncluded)
    {
        /* Get LTK size and LTK value from buffer */
        fsciBleGetUint8ValueFromBuffer(pSmpKeys->cLtkSize, *ppBuffer);
        fsciBleGetArrayFromBuffer(pSmpKeys->aLtk, *ppBuffer, pSmpKeys->cLtkSize);
    }

    /* Verify if IRK is included or not */
    fsciBleGetBoolValueFromBuffer(bIrkIncluded, *ppBuffer);

    if(TRUE == bIrkIncluded)
    {
        /* Get IRK value from buffer */
        fsciBleGetIrkFromBuffer(pSmpKeys->aIrk, *ppBuffer);
    }

    /* Verify if CSRK is included or not */
    fsciBleGetBoolValueFromBuffer(bCsrkIncluded, *ppBuffer);

    if(TRUE == bCsrkIncluded)
    {
        /* Get CSRK value from buffer */
        fsciBleGetCsrkFromBuffer(pSmpKeys->aCsrk, *ppBuffer);
    }

    if(TRUE == bLtkIncluded)
    {
        /* Rand size, rand value and ediv are present in the buffer only if LTK
        is included */
        fsciBleGetUint8ValueFromBuffer(pSmpKeys->cRandSize, *ppBuffer);
        fsciBleGetArrayFromBuffer(pSmpKeys->aRand, *ppBuffer, pSmpKeys->cRandSize);
        fsciBleGetUint16ValueFromBuffer(pSmpKeys->ediv, *ppBuffer);
    }

    if(TRUE == bIrkIncluded)
    {
        /* Verify if address is included or not */
        fsciBleGetBoolValueFromBuffer(bAddressIncluded, *ppBuffer);

        if(TRUE == bAddressIncluded)
        {
            /* Get address type from buffer */
            fsciBleGetEnumValueFromBuffer(pSmpKeys->addressType, *ppBuffer, bleAddressType_t);

            /* Get address from buffer */
            fsciBleGetAddressFromBuffer(pSmpKeys->aAddress, *ppBuffer);
        }
    }
}


void fsciBleGapGetBufferFromSmpKeys(const gapSmpKeys_t* pSmpKeys, uint8_t** ppBuffer)
{
    bool_t  bLtkIncluded        = (NULL == pSmpKeys->aLtk) ? FALSE : TRUE;
    bool_t  bIrkIncluded        = (NULL == pSmpKeys->aIrk) ? FALSE : TRUE;
    bool_t  bCsrkIncluded       = (NULL == pSmpKeys->aCsrk) ? FALSE : TRUE;
    bool_t  bAddressIncluded    = (NULL == pSmpKeys->aAddress) ? FALSE : TRUE;

    /* Write gapSmpKeys_t fields in buffer */

    /* Write boolean value which indicates if LTK is included or not */
    fsciBleGetBufferFromBoolValue(bLtkIncluded, *ppBuffer);

    if(TRUE == bLtkIncluded)
    {
        /* Write LTK size and LTK value in buffer */
        fsciBleGetBufferFromUint8Value(pSmpKeys->cLtkSize, *ppBuffer);
        fsciBleGetBufferFromArray(pSmpKeys->aLtk, *ppBuffer, pSmpKeys->cLtkSize);
    }

    /* Write boolean value which indicates if IRK is included or not */
    fsciBleGetBufferFromBoolValue(bIrkIncluded, *ppBuffer);

    if(TRUE == bIrkIncluded)
    {
        /* Write IRK value in buffer */
        fsciBleGetBufferFromIrk(pSmpKeys->aIrk, *ppBuffer);
    }

    /* Write boolean value which indicates if CSRK is included or not */
    fsciBleGetBufferFromBoolValue(bCsrkIncluded, *ppBuffer);

    if(TRUE == bCsrkIncluded)
    {
        /* Write CSRK value in buffer */
        fsciBleGetBufferFromCsrk(pSmpKeys->aCsrk, *ppBuffer);
    }

    if(TRUE == bLtkIncluded)
    {
        /* Write rand size, rand value and ediv in buffer only if LTK is included */
        fsciBleGetBufferFromUint8Value(pSmpKeys->cRandSize, *ppBuffer);
        fsciBleGetBufferFromArray(pSmpKeys->aRand, *ppBuffer, pSmpKeys->cRandSize);
        fsciBleGetBufferFromUint16Value(pSmpKeys->ediv, *ppBuffer);
    }

    if(TRUE == bIrkIncluded)
    {
        /* Write boolean value which indicates if address is included or not */
        fsciBleGetBufferFromBoolValue(bAddressIncluded, *ppBuffer);

        if(TRUE == bAddressIncluded)
        {
            /* Write address type in buffer */
            fsciBleGetBufferFromEnumValue(pSmpKeys->addressType, *ppBuffer, bleAddressType_t);

            /* Write address in buffer */
            fsciBleGetBufferFromAddress(pSmpKeys->aAddress, *ppBuffer);
        }
    }
}


void fsciBleGapGetSecurityRequirementsFromBuffer(gapSecurityRequirements_t* pSecurityRequirements, uint8_t** ppBuffer)
{
    /* Read gapSecurityRequirements_t fields from buffer */
    fsciBleGetEnumValueFromBuffer(pSecurityRequirements->securityModeLevel, *ppBuffer, gapSecurityModeAndLevel_t);
    fsciBleGetBoolValueFromBuffer(pSecurityRequirements->authorization, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pSecurityRequirements->minimumEncryptionKeySize, *ppBuffer);
}


void fsciBleGapGetBufferFromSecurityRequirements(gapSecurityRequirements_t* pSecurityRequirements, uint8_t** ppBuffer)
{
    /* Write gapSecurityRequirements_t fields in buffer */
    fsciBleGetBufferFromEnumValue(pSecurityRequirements->securityModeLevel, *ppBuffer, gapSecurityModeAndLevel_t);
    fsciBleGetBufferFromBoolValue(pSecurityRequirements->authorization, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pSecurityRequirements->minimumEncryptionKeySize, *ppBuffer);
}


void fsciBleGapGetServiceSecurityRequirementsFromBuffer(gapServiceSecurityRequirements_t* pServiceSecurityRequirements, uint8_t** ppBuffer)
{
    /* Read gapServiceSecurityRequirements_t fields from buffer */
    fsciBleGetUint16ValueFromBuffer(pServiceSecurityRequirements->serviceHandle, *ppBuffer);
    fsciBleGapGetSecurityRequirementsFromBuffer(&pServiceSecurityRequirements->requirements, ppBuffer);
}


void fsciBleGapGetBufferFromServiceSecurityRequirements(gapServiceSecurityRequirements_t* pServiceSecurityRequirements, uint8_t** ppBuffer)
{
    /* Write gapServiceSecurityRequirements_t fields in buffer */
    fsciBleGetBufferFromUint16Value(pServiceSecurityRequirements->serviceHandle, *ppBuffer);
    fsciBleGapGetBufferFromSecurityRequirements(&pServiceSecurityRequirements->requirements, ppBuffer);
}


gapDeviceSecurityRequirements_t* fsciBleGapAllocDeviceSecurityRequirementsForBuffer(uint8_t* pBuffer)
{
    union
    {
        uint8_t*                             pSecurityRequirementsTemp;
        gapServiceSecurityRequirements_t*    aServiceSecurityRequirementsTemp;
        gapSecurityRequirements_t*           pMasterSecurityRequirementsTemp;
    }securityRequirementsVars;

    uint8_t                             nbOfServices;
    gapDeviceSecurityRequirements_t*    pDeviceSecurityRequirements;

    /* Go in buffer to the number of services position */
    pBuffer += sizeof(gapSecurityModeAndLevel_t) + sizeof(bool_t) + sizeof(uint16_t);

    /* Get the number of services from buffer */
    fsciBleGetUint8ValueFromBuffer(nbOfServices, pBuffer);

    /* Allocate buffer for the device security requirements */
    pDeviceSecurityRequirements = (gapDeviceSecurityRequirements_t*)MEM_BufferAlloc(sizeof(gapDeviceSecurityRequirements_t) +
                                                                                    sizeof(uint8_t) +
                                                                                    sizeof(gapSecurityRequirements_t) +
                                                                                    (uint32_t)nbOfServices * sizeof(gapServiceSecurityRequirements_t));

    if(NULL == pDeviceSecurityRequirements)
    {
        /* No memory */
        return NULL;
    }

    /* Set pointers in gapDeviceSecurityRequirements_t structure */
    securityRequirementsVars.pSecurityRequirementsTemp = (uint8_t*)pDeviceSecurityRequirements + sizeof(gapDeviceSecurityRequirements_t);
    pDeviceSecurityRequirements->pMasterSecurityRequirements    = securityRequirementsVars.pMasterSecurityRequirementsTemp;
    securityRequirementsVars.pSecurityRequirementsTemp = (uint8_t*)pDeviceSecurityRequirements->pMasterSecurityRequirements + sizeof(gapSecurityRequirements_t);
    pDeviceSecurityRequirements->aServiceSecurityRequirements   = securityRequirementsVars.aServiceSecurityRequirementsTemp;

    /* Return the allocated buffer for the device security requirements */
    return pDeviceSecurityRequirements;
}


void fsciBleGapGetDeviceSecurityRequirementsFromBuffer(gapDeviceSecurityRequirements_t* pDeviceSecurityRequirements, uint8_t** ppBuffer)
{
    uint32_t iCount;

    /* Read gapDeviceSecurityRequirements_t fields from buffer */
    fsciBleGapGetSecurityRequirementsFromBuffer(pDeviceSecurityRequirements->pMasterSecurityRequirements, ppBuffer);
    fsciBleGetUint8ValueFromBuffer(pDeviceSecurityRequirements->cNumServices, *ppBuffer);

    /* Read all the service security requirements */
    for(iCount = 0; iCount < pDeviceSecurityRequirements->cNumServices; iCount++)
    {
        fsciBleGapGetServiceSecurityRequirementsFromBuffer(&pDeviceSecurityRequirements->aServiceSecurityRequirements[iCount], ppBuffer);
    }
}


void fsciBleGapGetBufferFromDeviceSecurityRequirements(const gapDeviceSecurityRequirements_t* pDeviceSecurityRequirements, uint8_t** ppBuffer)
{
    uint32_t iCount;

    /* Write gapDeviceSecurityRequirements_t fields in buffer */
    fsciBleGapGetBufferFromSecurityRequirements(pDeviceSecurityRequirements->pMasterSecurityRequirements, ppBuffer);
    fsciBleGetBufferFromUint8Value(pDeviceSecurityRequirements->cNumServices, *ppBuffer);

    /* Write all the service security requirements */
    for(iCount = 0; iCount < pDeviceSecurityRequirements->cNumServices; iCount++)
    {
        fsciBleGapGetBufferFromServiceSecurityRequirements(&pDeviceSecurityRequirements->aServiceSecurityRequirements[iCount], ppBuffer);
    }
}


void fsciBleGapGetHandleListFromBuffer(gapHandleList_t* pHandleList, uint8_t** ppBuffer)
{
    /* Read gapHandleList_t fields from buffer */
    fsciBleGetUint8ValueFromBuffer(pHandleList->cNumHandles, *ppBuffer);
    fsciBleGetArrayFromBuffer(pHandleList->aHandles, *ppBuffer, (uint32_t)pHandleList->cNumHandles * sizeof(uint16_t));
}


void fsciBleGapGetBufferFromHandleList(gapHandleList_t* pHandleList, uint8_t** ppBuffer)
{
    /* Write gapHandleList_t fields in buffer */
    fsciBleGetBufferFromUint8Value(pHandleList->cNumHandles, *ppBuffer);
    fsciBleGetBufferFromArray(pHandleList->aHandles, *ppBuffer, (uint32_t)pHandleList->cNumHandles * sizeof(uint16_t));
}


void fsciBleGapGetConnectionSecurityInformationFromBuffer(gapConnectionSecurityInformation_t* pConnectionSecurityInformation, uint8_t** ppBuffer)
{
    /* Read gapConnectionSecurityInformation_t fields from buffer */
    fsciBleGetBoolValueFromBuffer(pConnectionSecurityInformation->authenticated, *ppBuffer);
    fsciBleGapGetHandleListFromBuffer(&pConnectionSecurityInformation->authorizedToRead, ppBuffer);
    fsciBleGapGetHandleListFromBuffer(&pConnectionSecurityInformation->authorizedToWrite, ppBuffer);
}


void fsciBleGapGetBuffFromConnSecurityInformation(gapConnectionSecurityInformation_t* pConnectionSecurityInformation, uint8_t** ppBuffer)
{
    /* Write gapConnectionSecurityInformation_t fields in buffer */
    fsciBleGetBufferFromBoolValue(pConnectionSecurityInformation->authenticated, *ppBuffer);
    fsciBleGapGetBufferFromHandleList(&pConnectionSecurityInformation->authorizedToRead, ppBuffer);
    fsciBleGapGetBufferFromHandleList(&pConnectionSecurityInformation->authorizedToWrite, ppBuffer);
}


void fsciBleGapGetPairingParametersFromBuffer(gapPairingParameters_t* pPairingParameters, uint8_t** ppBuffer)
{
    /* Read gapPairingParameters_t fields from buffer */
    fsciBleGetBoolValueFromBuffer(pPairingParameters->withBonding, *ppBuffer);
    fsciBleGetEnumValueFromBuffer(pPairingParameters->securityModeAndLevel, *ppBuffer, gapSecurityModeAndLevel_t);
    fsciBleGetUint8ValueFromBuffer(pPairingParameters->maxEncryptionKeySize, *ppBuffer);
    fsciBleGetEnumValueFromBuffer(pPairingParameters->localIoCapabilities, *ppBuffer, gapIoCapabilities_t);
    fsciBleGetBoolValueFromBuffer(pPairingParameters->oobAvailable, *ppBuffer);
    fsciBleGetEnumValueFromBuffer(pPairingParameters->centralKeys, *ppBuffer, gapSmpKeyFlags_t);
    fsciBleGetEnumValueFromBuffer(pPairingParameters->peripheralKeys, *ppBuffer, gapSmpKeyFlags_t);
    fsciBleGetBoolValueFromBuffer(pPairingParameters->leSecureConnectionSupported, *ppBuffer);
    fsciBleGetBoolValueFromBuffer(pPairingParameters->useKeypressNotifications, *ppBuffer);
}


void fsciBleGapGetBufferFromPairingParameters(const gapPairingParameters_t* pPairingParameters, uint8_t** ppBuffer)
{
    /* Write gapPairingParameters_t fields in buffer */
    fsciBleGetBufferFromBoolValue(pPairingParameters->withBonding, *ppBuffer);
    fsciBleGetBufferFromEnumValue(pPairingParameters->securityModeAndLevel, *ppBuffer, gapSecurityModeAndLevel_t);
    fsciBleGetBufferFromUint8Value(pPairingParameters->maxEncryptionKeySize, *ppBuffer);
    fsciBleGetBufferFromEnumValue(pPairingParameters->localIoCapabilities, *ppBuffer, gapIoCapabilities_t);
    fsciBleGetBufferFromBoolValue(pPairingParameters->oobAvailable, *ppBuffer);
    fsciBleGetBufferFromEnumValue(pPairingParameters->centralKeys, *ppBuffer, gapSmpKeyFlags_t);
    fsciBleGetBufferFromEnumValue(pPairingParameters->peripheralKeys, *ppBuffer, gapSmpKeyFlags_t);
    fsciBleGetBufferFromBoolValue(pPairingParameters->leSecureConnectionSupported, *ppBuffer);
    fsciBleGetBufferFromBoolValue(pPairingParameters->useKeypressNotifications, *ppBuffer);
}


void fsciBleGapGetSlaveSecurityRequestParametersFromBuffer(gapSlaveSecurityRequestParameters_t* pSlaveSecurityRequestParameters, uint8_t** ppBuffer)
{
    /* Read gapSlaveSecurityRequestParameters_t fields from buffer */
    fsciBleGetBoolValueFromBuffer(pSlaveSecurityRequestParameters->bondAfterPairing, *ppBuffer);
    fsciBleGetBoolValueFromBuffer(pSlaveSecurityRequestParameters->authenticationRequired, *ppBuffer);
}


void fsciBleGapGetBufferFromSlaveSecurityRequestParameters(gapSlaveSecurityRequestParameters_t* pSlaveSecurityRequestParameters, uint8_t** ppBuffer)
{
    /* Write gapSlaveSecurityRequestParameters_t fields in buffer */
    fsciBleGetBufferFromBoolValue(pSlaveSecurityRequestParameters->bondAfterPairing, *ppBuffer);
    fsciBleGetBufferFromBoolValue(pSlaveSecurityRequestParameters->authenticationRequired, *ppBuffer);
}


void fsciBleGapGetAdvertisingParametersFromBuffer(gapAdvertisingParameters_t* pAdvertisingParameters, uint8_t** ppBuffer)
{
    /* Read gapAdvertisingParameters_t fields from buffer */
    fsciBleGetUint16ValueFromBuffer(pAdvertisingParameters->minInterval, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pAdvertisingParameters->maxInterval, *ppBuffer);
    fsciBleGetEnumValueFromBuffer(pAdvertisingParameters->advertisingType, *ppBuffer, bleAdvertisingType_t);
    fsciBleGetEnumValueFromBuffer(pAdvertisingParameters->ownAddressType, *ppBuffer, bleAddressType_t);
    fsciBleGetEnumValueFromBuffer(pAdvertisingParameters->peerAddressType, *ppBuffer, bleAddressType_t);
    fsciBleGetAddressFromBuffer(pAdvertisingParameters->peerAddress, *ppBuffer);
    fsciBleGetEnumValueFromBuffer(pAdvertisingParameters->channelMap, *ppBuffer, gapAdvertisingChannelMapFlags_t);
    fsciBleGetEnumValueFromBuffer(pAdvertisingParameters->filterPolicy, *ppBuffer, gapAdvertisingFilterPolicy_t);
}


#if defined(gBLE50_d) && (gBLE50_d == 1U)
void fsciBleGapGetExtAdvertisingParametersFromBuffer(gapExtAdvertisingParameters_t* pAdvertisingParameters, uint8_t** ppBuffer)
{
    /* Read gapExtAdvertisingParameters_t fields from buffer */
    fsciBleGetUint8ValueFromBuffer( pAdvertisingParameters->SID,                       *ppBuffer);
    fsciBleGetUint8ValueFromBuffer( pAdvertisingParameters->handle,                    *ppBuffer);
    fsciBleGetUint32ValueFromBuffer(pAdvertisingParameters->minInterval,               *ppBuffer);
    fsciBleGetUint32ValueFromBuffer(pAdvertisingParameters->maxInterval,               *ppBuffer);
    fsciBleGetEnumValueFromBuffer(  pAdvertisingParameters->ownAddressType,            *ppBuffer, bleAddressType_t);
    fsciBleGetAddressFromBuffer(    pAdvertisingParameters->ownRandomAddr,             *ppBuffer);
    fsciBleGetEnumValueFromBuffer(  pAdvertisingParameters->peerAddressType,           *ppBuffer, bleAddressType_t);
    fsciBleGetAddressFromBuffer(    pAdvertisingParameters->peerAddress,               *ppBuffer);
    fsciBleGetEnumValueFromBuffer(  pAdvertisingParameters->channelMap,                *ppBuffer, gapAdvertisingChannelMapFlags_t);
    fsciBleGetEnumValueFromBuffer(  pAdvertisingParameters->filterPolicy,              *ppBuffer, gapAdvertisingFilterPolicy_t);
    fsciBleGetEnumValueFromBuffer(  pAdvertisingParameters->extAdvProperties,          *ppBuffer, bleAdvRequestProperties_t);
    fsciBleGetUint8ValueFromBuffer( pAdvertisingParameters->txPower,                   *ppBuffer);
    fsciBleGetEnumValueFromBuffer(  pAdvertisingParameters->primaryPHY,                *ppBuffer, gapLePhyMode_t);
    fsciBleGetEnumValueFromBuffer(  pAdvertisingParameters->secondaryPHY,              *ppBuffer, gapLePhyMode_t);
    fsciBleGetUint8ValueFromBuffer( pAdvertisingParameters->secondaryAdvMaxSkip,       *ppBuffer);
    fsciBleGetBoolValueFromBuffer(  pAdvertisingParameters->enableScanReqNotification, *ppBuffer);
}

void fsciBleGapGetPeriodicAdvSyncReqFromBuffer(gapPeriodicAdvSyncReq_t* pReq, uint8_t** ppBuffer)
{
    fsciBleGetEnumValueFromBuffer(pReq->filterPolicy, *ppBuffer, gapCreateSyncReqFilterPolicy_t);
    fsciBleGetUint8ValueFromBuffer(pReq->SID, *ppBuffer);
    fsciBleGetEnumValueFromBuffer(pReq->peerAddressType, *ppBuffer, bleAddressType_t);
    fsciBleGetAddressFromBuffer(pReq->peerAddress, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pReq->skipCount, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pReq->timeout, *ppBuffer);
}

void fsciBleGapGetBufferFromPerAdvSyncReq(gapPeriodicAdvSyncReq_t* pReq, uint8_t** ppBuffer)
{
    fsciBleGetBufferFromEnumValue(pReq->filterPolicy, *ppBuffer, gapCreateSyncReqFilterPolicy_t);
    fsciBleGetBufferFromUint8Value(pReq->SID, *ppBuffer);
    fsciBleGetBufferFromEnumValue(pReq->peerAddressType, *ppBuffer, bleAddressType_t);
    fsciBleGetBufferFromAddress(pReq->peerAddress, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pReq->skipCount, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pReq->timeout, *ppBuffer);
}
#endif


void fsciBleGapGetBuffFromAdvParameters(const gapAdvertisingParameters_t* pAdvertisingParameters, uint8_t** ppBuffer)
{
    /* Write gapAdvertisingParameters_t fields in buffer */
    fsciBleGetBufferFromUint16Value(pAdvertisingParameters->minInterval, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pAdvertisingParameters->maxInterval, *ppBuffer);
    fsciBleGetBufferFromEnumValue(pAdvertisingParameters->advertisingType, *ppBuffer, bleAdvertisingType_t);
    fsciBleGetBufferFromEnumValue(pAdvertisingParameters->ownAddressType, *ppBuffer, bleAddressType_t);
    fsciBleGetBufferFromEnumValue(pAdvertisingParameters->peerAddressType, *ppBuffer, bleAddressType_t);
    fsciBleGetBufferFromAddress(pAdvertisingParameters->peerAddress, *ppBuffer);
    fsciBleGetBufferFromEnumValue(pAdvertisingParameters->channelMap, *ppBuffer, gapAdvertisingChannelMapFlags_t);
    fsciBleGetBufferFromEnumValue(pAdvertisingParameters->filterPolicy, *ppBuffer, gapAdvertisingFilterPolicy_t);
}


#if defined(gBLE50_d) && (gBLE50_d == 1U)
void fsciBleGapGetBufferFromExtAdvertisingParameters(gapExtAdvertisingParameters_t* pAdvertisingParameters, uint8_t** ppBuffer)
{
    /* Write gapExtAdvertisingParameters_t fields in buffer */
    fsciBleGetBufferFromUint8Value( pAdvertisingParameters->SID,                       *ppBuffer);
    fsciBleGetBufferFromUint8Value( pAdvertisingParameters->handle,                    *ppBuffer);
    fsciBleGetBufferFromUint32Value(pAdvertisingParameters->minInterval,               *ppBuffer);
    fsciBleGetBufferFromUint32Value(pAdvertisingParameters->maxInterval,               *ppBuffer);
    fsciBleGetBufferFromEnumValue(  pAdvertisingParameters->ownAddressType,            *ppBuffer, bleAddressType_t);
    fsciBleGetBufferFromAddress(    pAdvertisingParameters->ownRandomAddr,             *ppBuffer);
    fsciBleGetBufferFromEnumValue(  pAdvertisingParameters->peerAddressType,           *ppBuffer, bleAddressType_t);
    fsciBleGetBufferFromAddress(    pAdvertisingParameters->peerAddress,               *ppBuffer);
    fsciBleGetBufferFromEnumValue(  pAdvertisingParameters->channelMap,                *ppBuffer, gapAdvertisingChannelMapFlags_t);
    fsciBleGetBufferFromEnumValue(  pAdvertisingParameters->filterPolicy,              *ppBuffer, gapAdvertisingFilterPolicy_t);
    fsciBleGetBufferFromEnumValue(  pAdvertisingParameters->extAdvProperties,          *ppBuffer, bleAdvRequestProperties_t);
    fsciBleGetBufferFromUint8Value( pAdvertisingParameters->txPower,                   *ppBuffer);
    fsciBleGetBufferFromEnumValue(  pAdvertisingParameters->primaryPHY,                *ppBuffer, gapLePhyMode_t);
    fsciBleGetBufferFromEnumValue(  pAdvertisingParameters->secondaryPHY,              *ppBuffer, gapLePhyMode_t);
    fsciBleGetBufferFromUint8Value( pAdvertisingParameters->secondaryAdvMaxSkip,       *ppBuffer);
    fsciBleGetBufferFromBoolValue(  pAdvertisingParameters->enableScanReqNotification, *ppBuffer);
}
#endif


void fsciBleGapGetScanningParametersFromBuffer(gapScanningParameters_t* pScanningParameters, uint8_t** ppBuffer)
{
    /* Read gapScanningParameters_t fields from buffer */
    fsciBleGetEnumValueFromBuffer(pScanningParameters->type, *ppBuffer, bleScanType_t);
    fsciBleGetUint16ValueFromBuffer(pScanningParameters->interval, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pScanningParameters->window, *ppBuffer);
    fsciBleGetEnumValueFromBuffer(pScanningParameters->ownAddressType, *ppBuffer, bleAddressType_t);
    fsciBleGetEnumValueFromBuffer(pScanningParameters->filterPolicy, *ppBuffer, bleScanningFilterPolicy_t);
}


void fsciBleGapGetBuffFromScanParameters(const gapScanningParameters_t* pScanningParameters, uint8_t** ppBuffer)
{
    /* Write gapScanningParameters_t fields in buffer */
    fsciBleGetBufferFromEnumValue(pScanningParameters->type, *ppBuffer, bleScanType_t);
    fsciBleGetBufferFromUint16Value(pScanningParameters->interval, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pScanningParameters->window, *ppBuffer);
    fsciBleGetBufferFromEnumValue(pScanningParameters->ownAddressType, *ppBuffer, bleAddressType_t);
    fsciBleGetBufferFromEnumValue(pScanningParameters->filterPolicy, *ppBuffer, bleScanningFilterPolicy_t);
}


void fsciBleGapGetConnectionRequestParametersFromBuffer(gapConnectionRequestParameters_t* pConnectionRequestParameters, uint8_t** ppBuffer)
{
    /* Read gapConnectionRequestParameters_t fields from buffer */
    fsciBleGetUint16ValueFromBuffer(pConnectionRequestParameters->scanInterval, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pConnectionRequestParameters->scanWindow, *ppBuffer);
    fsciBleGetEnumValueFromBuffer(pConnectionRequestParameters->filterPolicy, *ppBuffer, bleInitiatorFilterPolicy_t);
    fsciBleGetEnumValueFromBuffer(pConnectionRequestParameters->ownAddressType, *ppBuffer, bleAddressType_t);
    fsciBleGetEnumValueFromBuffer(pConnectionRequestParameters->peerAddressType, *ppBuffer, bleAddressType_t);
    fsciBleGetAddressFromBuffer(pConnectionRequestParameters->peerAddress, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pConnectionRequestParameters->connIntervalMin, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pConnectionRequestParameters->connIntervalMax, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pConnectionRequestParameters->connLatency, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pConnectionRequestParameters->supervisionTimeout, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pConnectionRequestParameters->connEventLengthMin, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pConnectionRequestParameters->connEventLengthMax, *ppBuffer);
    fsciBleGetBoolValueFromBuffer(pConnectionRequestParameters->usePeerIdentityAddress, *ppBuffer);
    fsciBleGetEnumValueFromBuffer(pConnectionRequestParameters->initiatingPHYs, *ppBuffer, gapLePhyFlags_t);
}


void fsciBleGapGetBuffFromConnReqParameters(const gapConnectionRequestParameters_t* pConnectionRequestParameters, uint8_t** ppBuffer)
{
    /* Write gapConnectionRequestParameters_t fields in buffer */
    fsciBleGetBufferFromUint16Value(pConnectionRequestParameters->scanInterval, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pConnectionRequestParameters->scanWindow, *ppBuffer);
    fsciBleGetBufferFromEnumValue(pConnectionRequestParameters->filterPolicy, *ppBuffer, bleInitiatorFilterPolicy_t);
    fsciBleGetBufferFromEnumValue(pConnectionRequestParameters->ownAddressType, *ppBuffer, bleAddressType_t);
    fsciBleGetBufferFromEnumValue(pConnectionRequestParameters->peerAddressType, *ppBuffer, bleAddressType_t);
    fsciBleGetBufferFromAddress(pConnectionRequestParameters->peerAddress, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pConnectionRequestParameters->connIntervalMin, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pConnectionRequestParameters->connIntervalMax, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pConnectionRequestParameters->connLatency, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pConnectionRequestParameters->supervisionTimeout, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pConnectionRequestParameters->connEventLengthMin, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pConnectionRequestParameters->connEventLengthMax, *ppBuffer);
    fsciBleGetBufferFromBoolValue(pConnectionRequestParameters->usePeerIdentityAddress, *ppBuffer);
    fsciBleGetBufferFromEnumValue(pConnectionRequestParameters->initiatingPHYs, *ppBuffer, gapLePhyFlags_t);
}


void fsciBleGapGetConnectionParametersFromBuffer(gapConnectionParameters_t* pConnectionParameters, uint8_t** ppBuffer)
{
    /* Read gapConnectionParameters_t fields from buffer */
    fsciBleGetUint16ValueFromBuffer(pConnectionParameters->connInterval, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pConnectionParameters->connLatency, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pConnectionParameters->supervisionTimeout, *ppBuffer);
    fsciBleGetEnumValueFromBuffer(pConnectionParameters->masterClockAccuracy, *ppBuffer, bleMasterClockAccuracy_t);
}


void fsciBleGapGetBuffFromConnParameters(gapConnectionParameters_t* pConnectionParameters, uint8_t** ppBuffer)
{
    /* Write gapConnectionParameters_t fields in buffer */
    fsciBleGetBufferFromUint16Value(pConnectionParameters->connInterval, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pConnectionParameters->connLatency, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pConnectionParameters->supervisionTimeout, *ppBuffer);
    fsciBleGetBufferFromEnumValue(pConnectionParameters->masterClockAccuracy, *ppBuffer, bleMasterClockAccuracy_t);
}


gapAdStructure_t* fsciBleGapAllocAdStructureForBuffer(uint8_t* pBuffer)
{
    uint8_t             length;
    gapAdStructure_t*   pAdStructure;

    /* Get the data length from buffer */
    fsciBleGetUint8ValueFromBuffer(length, pBuffer);

    /* Allocate buffer for the gapAdStructure_t structure */
    pAdStructure = (gapAdStructure_t*)MEM_BufferAlloc(sizeof(gapAdStructure_t) + (uint32_t)length);

    if(NULL != pAdStructure)
    {
        /* Set data pointer in gapAdStructure_t structure */
        pAdStructure->aData = (uint8_t*)pAdStructure + sizeof(gapAdStructure_t);
    }

    /* Return the buffer allocated for gapAdStructure_t structure, or NULL */
    return pAdStructure;
}


void fsciBleGapGetAdStructureFromBuffer(gapAdStructure_t* pAdStructure, uint8_t** ppBuffer)
{
    /* Read gapAdStructure_t fields from buffer */
    fsciBleGetUint8ValueFromBuffer(pAdStructure->length, *ppBuffer);
    fsciBleGetEnumValueFromBuffer(pAdStructure->adType, *ppBuffer, gapAdType_t);
    fsciBleGetArrayFromBuffer(pAdStructure->aData, *ppBuffer, pAdStructure->length);

    /* The length value must contain also the type (uint8_t) */
    pAdStructure->length += sizeof(uint8_t);
}


void fsciBleGapGetBufferFromAdStructure(gapAdStructure_t* pAdStructure, uint8_t** ppBuffer)
{
    /* Write gapAdStructure_t fields in buffer */
    /* In TestTool, the length is only the data length */
    fsciBleGetBufferFromUint8Value((pAdStructure->length - sizeof(uint8_t)), *ppBuffer);
    fsciBleGetBufferFromEnumValue(pAdStructure->adType, *ppBuffer, gapAdType_t);
    fsciBleGetBufferFromArray(pAdStructure->aData, *ppBuffer, ((uint32_t)pAdStructure->length - sizeof(uint8_t)));
}


gapAdvertisingData_t* fsciBleGapAllocAdvertisingDataForBuffer(uint8_t* pBuffer)
{
    union
    {
        uint8_t*                    pAdvertisingDataTemp;
        gapAdStructure_t*           aAdStructuresTemp;
    }advertisingVars;

    uint16_t                advertisingDataSize = sizeof(gapAdvertisingData_t);
    uint8_t                 nbOfAdStructures = 0U;
    uint8_t*                aDataSizeArray = NULL;
    gapAdvertisingData_t*   pAdvertisingData = NULL;
    uint8_t*                pData = NULL;
    uint32_t                iCount = 0U;

    /* Get from buffer the number of AdStructures */
    fsciBleGetUint8ValueFromBuffer(nbOfAdStructures, pBuffer);

    if( nbOfAdStructures > 0U )
    {
        /* Allocate buffer to keep each AdStructure length */
        aDataSizeArray = MEM_BufferAlloc(nbOfAdStructures);

        if(NULL == aDataSizeArray)
        {
            /* No memory */
            return NULL;
        }

        /* Read from buffer each AdStructure length */
        for(iCount = 0; iCount < nbOfAdStructures; iCount++)
        {
            /* Get from buffer the AdStructure data length */
            fsciBleGetUint8ValueFromBuffer(aDataSizeArray[iCount], pBuffer);

            /* Go in buffer to the next AdStructure */
            pBuffer += sizeof(uint8_t) + aDataSizeArray[iCount];

            /* Add this AdStructure size to the total length needed for the allocated buffer */
            advertisingDataSize += (sizeof(gapAdStructure_t) + (uint16_t)aDataSizeArray[iCount]);
        }
    }

    /* Allocate buffer for the advertising data */
    pAdvertisingData = (gapAdvertisingData_t*)MEM_BufferAlloc(advertisingDataSize);

    if(NULL == pAdvertisingData)
    {
        /* No memory */
        /* Free the buffer used to keep the AdStructures lengths */
        (void)MEM_BufferFree(aDataSizeArray);
        return NULL;
    }

    /* Set pointers in gapAdvertisingData_t structure */
    advertisingVars.pAdvertisingDataTemp = (uint8_t*)pAdvertisingData + sizeof(gapAdvertisingData_t);
    pAdvertisingData->aAdStructures = advertisingVars.aAdStructuresTemp;
    pData                           = (uint8_t*)pAdvertisingData->aAdStructures + nbOfAdStructures * sizeof(gapAdStructure_t);

    if( nbOfAdStructures > 0U )
    {
        /* Set data pointer in each AdStructure */
        for(iCount = 0; iCount < nbOfAdStructures; iCount++)
        {
            pAdvertisingData->aAdStructures[iCount].aData = pData;

            pData += aDataSizeArray[iCount];
        }

        /* Free the buffer used to keep the AdStructures lengths */
        (void)MEM_BufferFree(aDataSizeArray);
    }

    /* Return the buffer allocated for gapAdvertisingData_t structure */
    return pAdvertisingData;
}


uint16_t fsciBleGapGetAdvertisingDataBufferSize(const gapAdvertisingData_t* pAdvertisingData)
{
    /* Get the constant size for the needed buffer */
    uint16_t    bufferSize = sizeof(uint8_t);
    uint32_t    iCount;

    /* Get the variable size for the needed buffer */
    for(iCount = 0; iCount < pAdvertisingData->cNumAdStructures; iCount++)
    {
        bufferSize += (uint16_t)fsciBleGapGetAdStructureBufferSize(&pAdvertisingData->aAdStructures[iCount]);
    }

    /* Return the size needed for the buffer */
    return bufferSize;
}


void fsciBleGapGetAdvertisingDataFromBuffer(gapAdvertisingData_t* pAdvertisingData, uint8_t** ppBuffer)
{
    uint32_t iCount;

    /* Read gapAdvertisingData_t fields from buffer */
    fsciBleGetUint8ValueFromBuffer(pAdvertisingData->cNumAdStructures, *ppBuffer);

    for(iCount = 0; iCount < pAdvertisingData->cNumAdStructures; iCount++)
    {
        fsciBleGapGetAdStructureFromBuffer(&pAdvertisingData->aAdStructures[iCount], ppBuffer);
    }
}


void fsciBleGapGetBufferFromAdvertisingData(const gapAdvertisingData_t* pAdvertisingData, uint8_t** ppBuffer)
{
    uint32_t iCount;

    /* Write gapAdvertisingData_t fields in buffer */
    fsciBleGetBufferFromUint8Value(pAdvertisingData->cNumAdStructures, *ppBuffer);

    for(iCount = 0; iCount < pAdvertisingData->cNumAdStructures; iCount++)
    {
        fsciBleGapGetBufferFromAdStructure(&pAdvertisingData->aAdStructures[iCount], ppBuffer);
    }
}


void fsciBleGapGetScannedDeviceFromBuffer(gapScannedDevice_t* pScannedDevice, uint8_t** ppBuffer)
{
    /* Read gapScannedDevice_t fields from buffer */
    fsciBleGetEnumValueFromBuffer(pScannedDevice->addressType, *ppBuffer, bleAddressType_t);
    fsciBleGetAddressFromBuffer(pScannedDevice->aAddress, *ppBuffer);
    fsciBleGetUint8ValueFromBufferSigned(pScannedDevice->rssi, *ppBuffer);
    fsciBleGetUint8ValueFromBuffer(pScannedDevice->dataLength, *ppBuffer);
    fsciBleGetArrayFromBuffer(pScannedDevice->data, *ppBuffer, pScannedDevice->dataLength);
    fsciBleGetEnumValueFromBuffer(pScannedDevice->advEventType, *ppBuffer, bleAdvertisingReportEventType_t);
    fsciBleGetBoolValueFromBuffer(pScannedDevice->directRpaUsed, *ppBuffer);
    if( pScannedDevice->directRpaUsed )
    {
        fsciBleGetAddressFromBuffer(pScannedDevice->directRpa, *ppBuffer);
    }
    fsciBleGetBoolValueFromBuffer(pScannedDevice->advertisingAddressResolved, *ppBuffer);
}


void fsciBleGapGetBufferFromScannedDevice(gapScannedDevice_t* pScannedDevice, uint8_t** ppBuffer)
{
    /* Write gapScannedDevice_t fields in buffer */
    fsciBleGetBufferFromEnumValue(pScannedDevice->addressType, *ppBuffer, bleAddressType_t);
    fsciBleGetBufferFromAddress(pScannedDevice->aAddress, *ppBuffer);
    fsciBleGetBufferFromUint8Value((uint8_t)pScannedDevice->rssi, *ppBuffer);
    fsciBleGetBufferFromUint8Value(pScannedDevice->dataLength, *ppBuffer);
    fsciBleGetBufferFromArray(pScannedDevice->data, *ppBuffer, pScannedDevice->dataLength);
    fsciBleGetBufferFromEnumValue(pScannedDevice->advEventType, *ppBuffer, bleAdvertisingReportEventType_t);
    fsciBleGetBufferFromBoolValue(pScannedDevice->directRpaUsed, *ppBuffer);
    if( pScannedDevice->directRpaUsed )
    {
        fsciBleGetBufferFromAddress(pScannedDevice->directRpa, *ppBuffer);
    }
    fsciBleGetBufferFromBoolValue(pScannedDevice->advertisingAddressResolved, *ppBuffer);
}

#if defined(gBLE50_d) && (gBLE50_d == 1U)

void fsciBleGapGetExtScannedDeviceFromBuffer(gapExtScannedDevice_t* pScannedDevice, uint8_t** ppBuffer)
{
    /* Read gapExtScannedDevice_t fields from buffer */
    fsciBleGetEnumValueFromBuffer(pScannedDevice->addressType, *ppBuffer, bleAddressType_t);
    fsciBleGetAddressFromBuffer(pScannedDevice->aAddress, *ppBuffer);
    fsciBleGetUint8ValueFromBuffer(pScannedDevice->SID, *ppBuffer);
    fsciBleGetBoolValueFromBuffer(pScannedDevice->advertisingAddressResolved, *ppBuffer);
    fsciBleGetEnumValueFromBuffer(pScannedDevice->advEventProperties, *ppBuffer, bleAdvReportEventProperties_t);
    fsciBleGetUint8ValueFromBuffer(pScannedDevice->rssi, *ppBuffer);
    fsciBleGetUint8ValueFromBuffer(pScannedDevice->txPower, *ppBuffer);
    fsciBleGetUint8ValueFromBuffer(pScannedDevice->primaryPHY, *ppBuffer);
    fsciBleGetUint8ValueFromBuffer(pScannedDevice->secondaryPHY, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pScannedDevice->periodicAdvInterval, *ppBuffer);
    fsciBleGetBoolValueFromBuffer(pScannedDevice->directRpaUsed, *ppBuffer);
    fsciBleGetEnumValueFromBuffer(pScannedDevice->directRpaType, *ppBuffer, bleAddressType_t);
    fsciBleGetAddressFromBuffer(pScannedDevice->directRpa, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pScannedDevice->dataLength, *ppBuffer);
    fsciBleGetArrayFromBuffer(pScannedDevice->pData, *ppBuffer, pScannedDevice->dataLength);
}

void fsciBleGapGetBufferFromExtScannedDevice(gapExtScannedDevice_t* pScannedDevice, uint8_t** ppBuffer)
{
    /* Write gapExtScannedDevice_t fields in buffer */
    fsciBleGetBufferFromEnumValue(pScannedDevice->addressType, *ppBuffer, bleAddressType_t);
    fsciBleGetBufferFromAddress(pScannedDevice->aAddress, *ppBuffer);
    fsciBleGetBufferFromUint8Value(pScannedDevice->SID, *ppBuffer);
    fsciBleGetBufferFromBoolValue(pScannedDevice->advertisingAddressResolved, *ppBuffer);
    fsciBleGetBufferFromEnumValue(pScannedDevice->advEventProperties, *ppBuffer, bleAdvReportEventProperties_t);
    fsciBleGetBufferFromUint8Value(pScannedDevice->rssi, *ppBuffer);
    fsciBleGetBufferFromUint8Value(pScannedDevice->txPower, *ppBuffer);
    fsciBleGetBufferFromUint8Value(pScannedDevice->primaryPHY, *ppBuffer);
    fsciBleGetBufferFromUint8Value(pScannedDevice->secondaryPHY, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pScannedDevice->periodicAdvInterval, *ppBuffer);
    fsciBleGetBufferFromBoolValue(pScannedDevice->directRpaUsed, *ppBuffer);
    fsciBleGetBufferFromEnumValue(pScannedDevice->directRpaType, *ppBuffer, bleAddressType_t);
    fsciBleGetBufferFromAddress(pScannedDevice->directRpa, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pScannedDevice->dataLength, *ppBuffer);
    fsciBleGetBufferFromArray(pScannedDevice->pData, *ppBuffer, pScannedDevice->dataLength);
}

void fsciBleGapGetPeriodicScannedDeviceFromBuffer(gapPeriodicScannedDevice_t* pScannedDevice, uint8_t** ppBuffer)
{
    /* Read gapExtScannedDevice_t fields from buffer */
    fsciBleGetUint16ValueFromBuffer(pScannedDevice->syncHandle, *ppBuffer);
    fsciBleGetUint8ValueFromBuffer(pScannedDevice->rssi, *ppBuffer);
    fsciBleGetUint8ValueFromBuffer(pScannedDevice->txPower, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pScannedDevice->dataLength, *ppBuffer);
    fsciBleGetArrayFromBuffer(pScannedDevice->pData, *ppBuffer, pScannedDevice->dataLength);
}

void fsciBleGapGetBufferFromPerScannedDevice(gapPeriodicScannedDevice_t* pScannedDevice, uint8_t** ppBuffer)
{
    /* Write gapExtScannedDevice_t fields in buffer */
    fsciBleGetBufferFromUint16Value(pScannedDevice->syncHandle, *ppBuffer);
    fsciBleGetBufferFromUint8Value(pScannedDevice->rssi, *ppBuffer);
    fsciBleGetBufferFromUint8Value(pScannedDevice->txPower, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pScannedDevice->dataLength, *ppBuffer);
    fsciBleGetBufferFromArray(pScannedDevice->pData, *ppBuffer, pScannedDevice->dataLength);
}

#endif  /* gBLE50_d */

void fsciBleGapGetConnectedEventFromBuffer(gapConnectedEvent_t* pConnectedEvent, uint8_t** ppBuffer)
{
    /* Read gapConnectedEvent_t fields from buffer */
    fsciBleGapGetConnectionParametersFromBuffer(&pConnectedEvent->connParameters, ppBuffer);
    fsciBleGetEnumValueFromBuffer(pConnectedEvent->peerAddressType, *ppBuffer, bleAddressType_t);
    fsciBleGetAddressFromBuffer(pConnectedEvent->peerAddress, *ppBuffer);
    fsciBleGetBoolValueFromBuffer(pConnectedEvent->peerRpaResolved, *ppBuffer);
    if( pConnectedEvent->peerRpaResolved )
    {
        fsciBleGetAddressFromBuffer(pConnectedEvent->peerRpa, *ppBuffer);
    }
    fsciBleGetBoolValueFromBuffer(pConnectedEvent->localRpaUsed, *ppBuffer);
    if( pConnectedEvent->localRpaUsed )
    {
        fsciBleGetAddressFromBuffer(pConnectedEvent->localRpa, *ppBuffer);
    }
    fsciBleGetEnumValueFromBuffer(pConnectedEvent->connectionRole, *ppBuffer, bleLlConnectionRole_t);
}


void fsciBleGapGetBufferFromConnectedEvent(gapConnectedEvent_t* pConnectedEvent, uint8_t** ppBuffer)
{
    /* Write gapConnectedEvent_t fields in buffer */
    fsciBleGapGetBuffFromConnParameters(&pConnectedEvent->connParameters, ppBuffer);
    fsciBleGetBufferFromEnumValue(pConnectedEvent->peerAddressType, *ppBuffer, bleAddressType_t);
    fsciBleGetBufferFromAddress(pConnectedEvent->peerAddress, *ppBuffer);
    fsciBleGetBufferFromBoolValue(pConnectedEvent->peerRpaResolved, *ppBuffer);
    if( pConnectedEvent->peerRpaResolved )
    {
        fsciBleGetBufferFromAddress(pConnectedEvent->peerRpa, *ppBuffer);
    }
    fsciBleGetBufferFromBoolValue(pConnectedEvent->localRpaUsed, *ppBuffer);
    if( pConnectedEvent->localRpaUsed )
    {
        fsciBleGetBufferFromAddress(pConnectedEvent->localRpa, *ppBuffer);
    }
    fsciBleGetBufferFromEnumValue(pConnectedEvent->connectionRole, *ppBuffer, bleLlConnectionRole_t);
}


void fsciBleGapGetKeyExchangeRequestEventFromBuffer(gapKeyExchangeRequestEvent_t* pKeyExchangeRequestEvent, uint8_t** ppBuffer)
{
    /* Read gapKeyExchangeRequestEvent_t fields from buffer */
    fsciBleGetEnumValueFromBuffer(pKeyExchangeRequestEvent->requestedKeys, *ppBuffer, gapSmpKeyFlags_t);
    fsciBleGetUint8ValueFromBuffer(pKeyExchangeRequestEvent->requestedLtkSize, *ppBuffer);
}


void fsciBleGapGetBufferFromKeyExchangeRequestEvent(gapKeyExchangeRequestEvent_t* pKeyExchangeRequestEvent, uint8_t** ppBuffer)
{
    /* Write gapKeyExchangeRequestEvent_t fields in buffer */
    fsciBleGetBufferFromEnumValue(pKeyExchangeRequestEvent->requestedKeys, *ppBuffer, gapSmpKeyFlags_t);
    fsciBleGetBufferFromUint8Value(pKeyExchangeRequestEvent->requestedLtkSize, *ppBuffer);
}


uint16_t fsciBleGapGetPairingCompleteEventBufferSize(gapPairingCompleteEvent_t* pPairingCompleteEvent)
{
    /* Return the size needed for the buffer */
    return (sizeof(bool_t) + ((TRUE == pPairingCompleteEvent->pairingSuccessful) ? (uint16_t)sizeof(bool_t) : (uint16_t)sizeof(bleResult_t)));
}


void fsciBleGapGetPairComplEventFromBuffer(gapPairingCompleteEvent_t* pPairingCompleteEvent, uint8_t** ppBuffer)
{
    /* Read gapPairingCompleteEvent_t fields from buffer */
    fsciBleGetBoolValueFromBuffer(pPairingCompleteEvent->pairingSuccessful, *ppBuffer);

    if(TRUE == pPairingCompleteEvent->pairingSuccessful)
    {
        fsciBleGetBoolValueFromBuffer(pPairingCompleteEvent->pairingCompleteData.withBonding, *ppBuffer);
    }
    else
    {
        fsciBleGetEnumValueFromBuffer(pPairingCompleteEvent->pairingCompleteData.failReason, *ppBuffer, bleResult_t);
    }
}


void fsciBleGapGetBufferFromPairingCompleteEvent(gapPairingCompleteEvent_t* pPairingCompleteEvent, uint8_t** ppBuffer)
{
    /* Write gapPairingCompleteEvent_t fields in buffer */
    fsciBleGetBufferFromBoolValue(pPairingCompleteEvent->pairingSuccessful, *ppBuffer);

    if(TRUE == pPairingCompleteEvent->pairingSuccessful)
    {
        fsciBleGetBufferFromBoolValue(pPairingCompleteEvent->pairingCompleteData.withBonding, *ppBuffer);
    }
    else
    {
        fsciBleGetBufferFromEnumValue(pPairingCompleteEvent->pairingCompleteData.failReason, *ppBuffer, bleResult_t);
    }
}


void fsciBleGapGetLongTermKeyRequestEventFromBuffer(gapLongTermKeyRequestEvent_t* pLongTermKeyRequestEvent, uint8_t** ppBuffer)
{
    /* Read gapLongTermKeyRequestEvent_t fields from buffer */
    fsciBleGetUint16ValueFromBuffer(pLongTermKeyRequestEvent->ediv, *ppBuffer);
    fsciBleGetUint8ValueFromBuffer(pLongTermKeyRequestEvent->randSize, *ppBuffer);
    fsciBleGetArrayFromBuffer(pLongTermKeyRequestEvent->aRand, *ppBuffer, pLongTermKeyRequestEvent->randSize);
}


void fsciBleGapGetBufferFromLongTermKeyRequestEvent(gapLongTermKeyRequestEvent_t* pLongTermKeyRequestEvent, uint8_t** ppBuffer)
{
    /* Write gapLongTermKeyRequestEvent_t fields in buffer */
    fsciBleGetBufferFromUint16Value(pLongTermKeyRequestEvent->ediv, *ppBuffer);
    fsciBleGetBufferFromUint8Value(pLongTermKeyRequestEvent->randSize, *ppBuffer);
    fsciBleGetBufferFromArray(pLongTermKeyRequestEvent->aRand, *ppBuffer, pLongTermKeyRequestEvent->randSize);
}


void fsciBleGapGetInternalErrorFromBuffer(gapInternalError_t* pInternalError, uint8_t** ppBuffer)
{
    /* Read gapInternalError_t fields from buffer */
    fsciBleGetEnumValueFromBuffer(pInternalError->errorCode, *ppBuffer, bleResult_t);
    fsciBleGetEnumValueFromBuffer(pInternalError->errorSource, *ppBuffer, gapInternalErrorSource_t);
    fsciBleGetUint16ValueFromBuffer(pInternalError->hciCommandOpcode, *ppBuffer);
}


void fsciBleGapGetBufferFromInternalError(gapInternalError_t* pInternalError, uint8_t** ppBuffer)
{
    /* Write gapInternalError_t fields in buffer */
    fsciBleGetBufferFromEnumValue(pInternalError->errorCode, *ppBuffer, bleResult_t);
    fsciBleGetBufferFromEnumValue(pInternalError->errorSource, *ppBuffer, gapInternalErrorSource_t);
    fsciBleGetBufferFromUint16Value(pInternalError->hciCommandOpcode, *ppBuffer);
}


void fsciBleGapGetConnParamUpdateReqFromBuffer(gapConnParamsUpdateReq_t* pConnParameterUpdateRequest, uint8_t** ppBuffer)
{
    /* Read gapConnParamsUpdateReq_t structure fields from buffer */
    fsciBleGetUint16ValueFromBuffer(pConnParameterUpdateRequest->intervalMin, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pConnParameterUpdateRequest->intervalMax, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pConnParameterUpdateRequest->slaveLatency, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pConnParameterUpdateRequest->timeoutMultiplier, *ppBuffer);
}


void fsciBleGapGetBufferFromConnParameterUpdateRequest(gapConnParamsUpdateReq_t* pConnParameterUpdateRequest, uint8_t** ppBuffer)
{
    /* Write gapConnParamsUpdateReq_t structure fields in buffer */
    fsciBleGetBufferFromUint16Value(pConnParameterUpdateRequest->intervalMin, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pConnParameterUpdateRequest->intervalMax, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pConnParameterUpdateRequest->slaveLatency, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pConnParameterUpdateRequest->timeoutMultiplier, *ppBuffer);
}


void fsciBleGapGetConnParameterUpdateCompleteFromBuffer(gapConnParamsUpdateComplete_t* pConnectionParameterUpdateComplete, uint8_t** ppBuffer)
{
    /* Read gapConnParamsUpdateComplete_t structure fields from buffer */
    fsciBleGetEnumValueFromBuffer(pConnectionParameterUpdateComplete->status, *ppBuffer, bleResult_t);
    fsciBleGetUint16ValueFromBuffer(pConnectionParameterUpdateComplete->connInterval, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pConnectionParameterUpdateComplete->connLatency, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pConnectionParameterUpdateComplete->supervisionTimeout, *ppBuffer);
}


void fsciBleGapGetBuffFromConnParameterUpdateComplete(gapConnParamsUpdateComplete_t* pConnParameterUpdateComplete, uint8_t** ppBuffer)
{
    /* Write gapConnParamsUpdateComplete_t structure fields in buffer */
    fsciBleGetBufferFromEnumValue(pConnParameterUpdateComplete->status, *ppBuffer, bleResult_t);
    fsciBleGetBufferFromUint16Value(pConnParameterUpdateComplete->connInterval, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pConnParameterUpdateComplete->connLatency, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pConnParameterUpdateComplete->supervisionTimeout, *ppBuffer);
}


void fsciBleGapGetConnLeDataLengthChangedFromBuffer(gapConnLeDataLengthChanged_t* pConnLeDataLengthChanged, uint8_t** ppBuffer)
{
    /* Read gapConnParamsUpdateReq_t structure fields from buffer */
    fsciBleGetUint16ValueFromBuffer(pConnLeDataLengthChanged->maxTxOctets, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pConnLeDataLengthChanged->maxTxTime, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pConnLeDataLengthChanged->maxRxOctets, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pConnLeDataLengthChanged->maxRxTime, *ppBuffer);
}


void fsciBleGapGetBufferFromConnLeDataLengthChanged(gapConnLeDataLengthChanged_t* pConnLeDataLengthChanged, uint8_t** ppBuffer)
{
    /* Write gapConnLeDataLengthChanged_t structure fields in buffer */
    fsciBleGetBufferFromUint16Value(pConnLeDataLengthChanged->maxTxOctets, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pConnLeDataLengthChanged->maxTxTime, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pConnLeDataLengthChanged->maxRxOctets, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pConnLeDataLengthChanged->maxRxTime, *ppBuffer);
}


void fsciBleGapGetIdentityInformationFromBuffer(gapIdentityInformation_t* pIdentityInformation, uint8_t** ppBuffer)
{
    /* Read gapIdentityInformation_t structure fields from buffer */
    fsciBleGetEnumValueFromBuffer(pIdentityInformation->identityAddress.idAddressType, *ppBuffer, bleAddressType_t);
    fsciBleGetAddressFromBuffer(pIdentityInformation->identityAddress.idAddress, *ppBuffer);
    fsciBleGetIrkFromBuffer(pIdentityInformation->irk, *ppBuffer);
    fsciBleGetEnumValueFromBuffer(pIdentityInformation->privacyMode, *ppBuffer, blePrivacyMode_t);
}


void fsciBleGapGetBufferFromIdentityInformation(const gapIdentityInformation_t* pIdentityInformation, uint8_t** ppBuffer)
{
    /* Write gapIdentityInformation_t structure fields in buffer */
    fsciBleGetBufferFromEnumValue(pIdentityInformation->identityAddress.idAddressType, *ppBuffer, bleAddressType_t);
    fsciBleGetBufferFromAddress(pIdentityInformation->identityAddress.idAddress, *ppBuffer);
    fsciBleGetBufferFromIrk((const void*)pIdentityInformation->irk, *ppBuffer);
    fsciBleGetBufferFromEnumValue(pIdentityInformation->privacyMode, *ppBuffer, blePrivacyMode_t);
}

uint16_t fsciBleGapGetGenericEventBufferSize(gapGenericEvent_t* pGenericEvent)
{
    /* Get the constant size for the needed buffer */
    uint16_t bufferSize = 0;

    /* Get the variable size for the needed buffer */
    switch(pGenericEvent->eventType)
    {
        case gInternalError_c:
            {
                bufferSize += fsciBleGapGetInternalErrorBufferSize(&pGenericEvent->internalError);
            }
            break;

        case gWhiteListSizeRead_c:
            {
                bufferSize += sizeof(uint8_t);
            }
            break;

        case gRandomAddressReady_c:
            {
                bufferSize += gcBleDeviceAddressSize_c;
                bufferSize += sizeof(uint8_t);  /* advHandle */
            }
            break;

        case gPublicAddressRead_c:
            {
                bufferSize += gcBleDeviceAddressSize_c;
            }
            break;

        case gRandomAddressSet_c:
            {
                bufferSize += sizeof(uint8_t);  /* advHandle */
            }
            break;

        case gAdvertisingSetupFailed_c:
            {
                bufferSize += sizeof(bleResult_t);
            }
            break;

#if defined(gBLE50_d) && (gBLE50_d == 1U)
        case gExtAdvertisingParametersSetupComplete_c:  /* Fall-through */
#endif
        case gAdvTxPowerLevelRead_c:
            {
                bufferSize += sizeof(int8_t);   /* advTxPowerLevel_dBm */
            }
            break;

        case gPrivateResolvableAddressVerified_c:
            {
                bufferSize += sizeof(bool_t);
            }
            break;

        case gLeScLocalOobData_c:
            {
                bufferSize += gSmpLeScRandomValueSize_c + gSmpLeScRandomConfirmValueSize_c;
            }
            break;

        case gHostPrivacyStateChanged_c:
            {
                bufferSize += sizeof(bool_t);
            }
            break;

        case gControllerPrivacyStateChanged_c:
            {
                bufferSize += sizeof(bool_t);
            }
            break;

        case gTxPowerLevelSetComplete_c:
            {
                bufferSize += sizeof(bleResult_t);
            }
            break;

        case gLePhyEvent_c:
            {
                bufferSize += sizeof(gapPhyEventType_t) + 3U * sizeof(uint8_t);
            }
            break;

        case gInitializationComplete_c:
            {
                bufferSize += sizeof(uint32_t) + sizeof(uint16_t) + 2U * sizeof(uint8_t);
            }
            break;

        case gControllerNotificationEvent_c:
            {
                bufferSize += sizeof(uint16_t) + sizeof(deviceId_t) + sizeof(int8_t) + sizeof(uint8_t) + sizeof(uint16_t) + sizeof(bleResult_t) + sizeof(uint16_t) + sizeof(uint8_t);
            }
            break;

        case gBondCreatedEvent_c:
            {
                bufferSize += sizeof(uint8_t) + sizeof(bleAddressType_t) + gcBleDeviceAddressSize_c;
            }
            break;

        case gTxEntryAvailable_c:
            {
                bufferSize += sizeof(uint8_t);
            }
            break;

        default:
            ; /* For MISRA compliance */
            break;
    }

    /* Return the size needed for the buffer */
    return bufferSize;
}


void fsciBleGapGetGenericEventFromBuffer(gapGenericEvent_t* pGenericEvent, uint8_t** ppBuffer)
{
    /* Read gapGenericEvent_t fields from buffer (without eventType) */
    switch(pGenericEvent->eventType)
    {
        case gInternalError_c:
            {
                fsciBleGapGetInternalErrorFromBuffer(&pGenericEvent->eventData.internalError, ppBuffer);
            }
            break;

        case gWhiteListSizeRead_c:
            {
                fsciBleGetUint8ValueFromBuffer(pGenericEvent->eventData.whiteListSize, *ppBuffer);
            }
            break;

        case gRandomAddressReady_c:
            {
                fsciBleGetAddressFromBuffer(pGenericEvent->eventData.addrReady.aAddress, *ppBuffer);
                fsciBleGetUint8ValueFromBuffer(pGenericEvent->eventData.addrReady.advHandle, *ppBuffer);
            }
            break;

        case gPublicAddressRead_c:
            {
                fsciBleGetAddressFromBuffer(pGenericEvent->eventData.aAddress, *ppBuffer);
            }
            break;

        case gRandomAddressSet_c:
            {
                fsciBleGetUint8ValueFromBuffer(pGenericEvent->eventData.advHandle, *ppBuffer);
            }
            break;

        case gAdvertisingSetupFailed_c:
            {
                fsciBleGetEnumValueFromBuffer(pGenericEvent->eventData.setupFailError, *ppBuffer, bleResult_t);
            }
            break;

#if defined(gBLE50_d) && (gBLE50_d == 1U)
        case gExtAdvertisingParametersSetupComplete_c:  /* Fall-through */
#endif
        case gAdvTxPowerLevelRead_c:
            {
                fsciBleGetUint8ValueFromBufferSigned(pGenericEvent->eventData.advTxPowerLevel_dBm, *ppBuffer);
            }
            break;

        case gPrivateResolvableAddressVerified_c:
            {
                fsciBleGetBoolValueFromBuffer(pGenericEvent->eventData.verified, *ppBuffer);
            }
            break;

        case gLeScLocalOobData_c:
            {
                fsciBleGetArrayFromBuffer(pGenericEvent->eventData.localOobData.randomValue, *ppBuffer, gSmpLeScRandomValueSize_c);
                fsciBleGetArrayFromBuffer(pGenericEvent->eventData.localOobData.confirmValue, *ppBuffer, gSmpLeScRandomConfirmValueSize_c);
            }
            break;

        case gHostPrivacyStateChanged_c:
            {
                fsciBleGetBoolValueFromBuffer(pGenericEvent->eventData.newHostPrivacyState, *ppBuffer);
            }
            break;

        case gControllerPrivacyStateChanged_c:
            {
                fsciBleGetBoolValueFromBuffer(pGenericEvent->eventData.newControllerPrivacyState, *ppBuffer);
            }
            break;

        case gTxPowerLevelSetComplete_c:
            {
                fsciBleGetEnumValueFromBuffer(pGenericEvent->eventData.txPowerLevelSetStatus, *ppBuffer, bleResult_t);
            }
            break;

        case gLePhyEvent_c:
            {
                fsciBleGetEnumValueFromBuffer(pGenericEvent->eventData.phyEvent.phyEventType, *ppBuffer, gapPhyEventType_t);
                if( gPhySetDefaultComplete_c != pGenericEvent->eventData.phyEvent.phyEventType )
                {
                    fsciBleGetDeviceIdFromBuffer(&pGenericEvent->eventData.phyEvent.deviceId, ppBuffer);
                    fsciBleGetUint8ValueFromBuffer(pGenericEvent->eventData.phyEvent.txPhy, *ppBuffer);
                    fsciBleGetUint8ValueFromBuffer(pGenericEvent->eventData.phyEvent.rxPhy, *ppBuffer);
                }
            }
            break;

        case gInitializationComplete_c:
            {
                fsciBleGetUint32ValueFromBuffer(pGenericEvent->eventData.initCompleteData.supportedFeatures, *ppBuffer);
                fsciBleGetUint16ValueFromBuffer(pGenericEvent->eventData.initCompleteData.maxAdvDataSize, *ppBuffer);
                fsciBleGetUint8ValueFromBuffer(pGenericEvent->eventData.initCompleteData.numOfSupportedAdvSets, *ppBuffer);
                fsciBleGetUint8ValueFromBuffer(pGenericEvent->eventData.initCompleteData.periodicAdvListSize, *ppBuffer);
            }
            break;

        case gControllerNotificationEvent_c:
            {
                fsciBleGetEnumValueFromBuffer(pGenericEvent->eventData.notifEvent.eventType, *ppBuffer, bleNotificationEventType_t);
                fsciBleGetDeviceIdFromBuffer(&pGenericEvent->eventData.notifEvent.deviceId, ppBuffer);
                fsciBleGetUint8ValueFromBufferSigned(pGenericEvent->eventData.notifEvent.rssi, *ppBuffer);
                fsciBleGetUint8ValueFromBuffer(pGenericEvent->eventData.notifEvent.channel, *ppBuffer);
                fsciBleGetUint16ValueFromBuffer(pGenericEvent->eventData.notifEvent.ce_counter, *ppBuffer);
                fsciBleGetEnumValueFromBuffer(pGenericEvent->eventData.notifEvent.status, *ppBuffer, bleResult_t);
                fsciBleGetUint16ValueFromBuffer(pGenericEvent->eventData.notifEvent.timestamp, *ppBuffer);
                fsciBleGetUint8ValueFromBuffer(pGenericEvent->eventData.notifEvent.adv_handle, *ppBuffer);
            }
            break;

        case gBondCreatedEvent_c:
            {
                fsciBleGetUint8ValueFromBuffer(pGenericEvent->eventData.bondCreatedEvent.nvmIndex, *ppBuffer);
                fsciBleGetEnumValueFromBuffer(pGenericEvent->eventData.bondCreatedEvent.addressType, *ppBuffer, bleAddressType_t);
                fsciBleGetAddressFromBuffer(pGenericEvent->eventData.bondCreatedEvent.address, *ppBuffer);
            }
            break;

        case gTxEntryAvailable_c:
            {
                fsciBleGetUint8ValueFromBuffer(pGenericEvent->eventData.deviceId, *ppBuffer);
            }
            break;

        default:
            ; /* For MISRA compliance */
            break;
    }
}


void fsciBleGapGetBufferFromGenericEvent(gapGenericEvent_t* pGenericEvent, uint8_t** ppBuffer)
{
    /* Write gapGenericEvent_t fields in buffer (without eventType) */
    switch(pGenericEvent->eventType)
    {
        case gInternalError_c:
            {
                fsciBleGapGetBufferFromInternalError(&pGenericEvent->eventData.internalError, ppBuffer);
            }
            break;

        case gWhiteListSizeRead_c:
            {
                fsciBleGetBufferFromUint8Value(pGenericEvent->eventData.whiteListSize, *ppBuffer);
            }
            break;

        case gRandomAddressReady_c:
            {
                fsciBleGetBufferFromAddress(pGenericEvent->eventData.addrReady.aAddress, *ppBuffer);
                fsciBleGetBufferFromUint8Value(pGenericEvent->eventData.addrReady.advHandle, *ppBuffer);
            }
            break;

        case gPublicAddressRead_c:
            {
                fsciBleGetBufferFromAddress(pGenericEvent->eventData.aAddress, *ppBuffer);
            }
            break;

        case gRandomAddressSet_c:
            {
                fsciBleGetBufferFromUint8Value(pGenericEvent->eventData.advHandle, *ppBuffer);
            }
            break;

        case gAdvertisingSetupFailed_c:
            {
                fsciBleGetBufferFromEnumValue(pGenericEvent->eventData.setupFailError, *ppBuffer, bleResult_t);
            }
            break;

#if defined(gBLE50_d) && (gBLE50_d == 1U)
        case gExtAdvertisingParametersSetupComplete_c:  /* Fall-through */
#endif
        case gAdvTxPowerLevelRead_c:
            {
                fsciBleGetBufferFromUint8Value((uint8_t)pGenericEvent->eventData.advTxPowerLevel_dBm, *ppBuffer);
            }
            break;

        case gPrivateResolvableAddressVerified_c:
            {
                fsciBleGetBufferFromBoolValue(pGenericEvent->eventData.verified, *ppBuffer);
            }
            break;

        case gLeScLocalOobData_c:
            {
                fsciBleGetBufferFromArray(pGenericEvent->eventData.localOobData.randomValue, *ppBuffer, gSmpLeScRandomValueSize_c);
                fsciBleGetBufferFromArray(pGenericEvent->eventData.localOobData.confirmValue, *ppBuffer, gSmpLeScRandomConfirmValueSize_c);
            }
            break;

        case gHostPrivacyStateChanged_c:
            {
                fsciBleGetBufferFromBoolValue(pGenericEvent->eventData.newHostPrivacyState, *ppBuffer);
            }
            break;

        case gControllerPrivacyStateChanged_c:
            {
                fsciBleGetBufferFromBoolValue(pGenericEvent->eventData.newControllerPrivacyState, *ppBuffer);
            }
            break;

        case gTxPowerLevelSetComplete_c:
            {
                fsciBleGetBufferFromEnumValue(pGenericEvent->eventData.txPowerLevelSetStatus, *ppBuffer, bleResult_t);
            }
            break;

        case gLePhyEvent_c:
            {
                fsciBleGetBufferFromEnumValue(pGenericEvent->eventData.phyEvent.phyEventType, *ppBuffer, gapPhyEventType_t);
                if( gPhySetDefaultComplete_c != pGenericEvent->eventData.phyEvent.phyEventType )
                {
                    fsciBleGetBufferFromDeviceId(&pGenericEvent->eventData.phyEvent.deviceId, ppBuffer);
                    fsciBleGetBufferFromUint8Value(pGenericEvent->eventData.phyEvent.txPhy, *ppBuffer);
                    fsciBleGetBufferFromUint8Value(pGenericEvent->eventData.phyEvent.rxPhy, *ppBuffer);
                }
            }
            break;

        case gInitializationComplete_c:
            {
                fsciBleGetBufferFromUint32Value(pGenericEvent->eventData.initCompleteData.supportedFeatures, *ppBuffer);
                fsciBleGetBufferFromUint16Value(pGenericEvent->eventData.initCompleteData.maxAdvDataSize, *ppBuffer);
                fsciBleGetBufferFromUint8Value(pGenericEvent->eventData.initCompleteData.numOfSupportedAdvSets, *ppBuffer);
                fsciBleGetBufferFromUint8Value(pGenericEvent->eventData.initCompleteData.periodicAdvListSize, *ppBuffer);
            }
            break;

        case gControllerNotificationEvent_c:
            {
                fsciBleGetBufferFromEnumValue(pGenericEvent->eventData.notifEvent.eventType, *ppBuffer, bleNotificationEventType_t);
                fsciBleGetBufferFromDeviceId(&pGenericEvent->eventData.notifEvent.deviceId, ppBuffer);
                fsciBleGetBufferFromUint8ValueSigned(pGenericEvent->eventData.notifEvent.rssi, *ppBuffer);
                fsciBleGetBufferFromUint8Value(pGenericEvent->eventData.notifEvent.channel, *ppBuffer);
                fsciBleGetBufferFromUint16Value(pGenericEvent->eventData.notifEvent.ce_counter, *ppBuffer);
                fsciBleGetBufferFromEnumValue(pGenericEvent->eventData.notifEvent.status, *ppBuffer, bleResult_t);
                fsciBleGetBufferFromUint16Value(pGenericEvent->eventData.notifEvent.timestamp, *ppBuffer);
                fsciBleGetBufferFromUint8Value(pGenericEvent->eventData.notifEvent.adv_handle, *ppBuffer);
            }
            break;

        case gBondCreatedEvent_c:
            {
                fsciBleGetBufferFromUint8Value(pGenericEvent->eventData.bondCreatedEvent.nvmIndex, *ppBuffer);
                fsciBleGetBufferFromEnumValue(pGenericEvent->eventData.bondCreatedEvent.addressType, *ppBuffer, bleAddressType_t);
                fsciBleGetBufferFromAddress(pGenericEvent->eventData.bondCreatedEvent.address, *ppBuffer);
            }
            break;

        case gTxEntryAvailable_c:
            {
                fsciBleGetBufferFromUint8Value(pGenericEvent->eventData.deviceId, *ppBuffer);
            }
            break;

        default:
            ; /* For MISRA compliance */
            break;
    }
}


uint16_t fsciBleGapGetAdvertisingEventBufferSize(gapAdvertisingEvent_t* pAdvertisingEvent)
{
    /* Get the constant size for the needed buffer */
    uint16_t bufferSize = 0;

    /* Get the variable size for the needed buffer */
    switch(pAdvertisingEvent->eventType)
    {
        case gAdvertisingCommandFailed_c:
            {
                bufferSize += sizeof(bleResult_t);
            }
            break;

#if defined(gBLE50_d) && (gBLE50_d == 1U)
        case gExtScanNotification_c:
            {
                bufferSize += sizeof(uint8_t);          /* handle */
                bufferSize += sizeof(bleAddressType_t); /* scannerAddrType */
                bufferSize += gcBleDeviceAddressSize_c; /* aScannerAddr */
                bufferSize += sizeof(bool_t);           /* scannerAddrResolved */
            }
            break;
        case gAdvertisingSetTerminated_c:
            {
                bufferSize += sizeof(bleResult_t);      /* status */
                bufferSize += sizeof(uint8_t);          /* handle */
            }
            break;
#endif

        default:
            ; /* For MISRA compliance */
            break;
    }

    /* Return the size needed for the buffer */
    return bufferSize;
}


void fsciBleGapGetAdvertisingEventFromBuffer(gapAdvertisingEvent_t* pAdvertisingEvent, uint8_t** ppBuffer)
{
    /* Read gapAdvertisingEvent_t fields from buffer (without eventType) */
    switch(pAdvertisingEvent->eventType)
    {
        case gAdvertisingCommandFailed_c:
            {
                fsciBleGetEnumValueFromBuffer(pAdvertisingEvent->eventData.failReason, *ppBuffer, bleResult_t);
            }
            break;
#if defined(gBLE50_d) && (gBLE50_d == 1U)
        case gAdvertisingSetTerminated_c:
            {
                fsciBleGetEnumValueFromBuffer(pAdvertisingEvent->eventData.advSetTerminated.status, *ppBuffer, bleResult_t);
                fsciBleGetUint8ValueFromBuffer(pAdvertisingEvent->eventData.advSetTerminated.handle, *ppBuffer);
            }
            break;
#endif
        default:
            ; /* For MISRA compliance */
            break;

    }
}


void fsciBleGapGetBuffFromAdvEvent(gapAdvertisingEvent_t* pAdvertisingEvent, uint8_t** ppBuffer)
{
    /* Write gapAdvertisingEvent_t fields in buffer (without eventType) */
    switch(pAdvertisingEvent->eventType)
    {
        case gAdvertisingCommandFailed_c:
            {
                fsciBleGetBufferFromEnumValue(pAdvertisingEvent->eventData.failReason, *ppBuffer, bleResult_t);
            }
            break;

#if defined(gBLE50_d) && (gBLE50_d == 1U)
        case gExtScanNotification_c:
            {
                fsciBleGetBufferFromUint8Value(pAdvertisingEvent->eventData.scanNotification.handle, *ppBuffer);
                fsciBleGetBufferFromEnumValue( pAdvertisingEvent->eventData.scanNotification.scannerAddrType, *ppBuffer, bleAddressType_t);
                fsciBleGetBufferFromAddress(   pAdvertisingEvent->eventData.scanNotification.aScannerAddr, *ppBuffer);
                fsciBleGetBufferFromBoolValue( pAdvertisingEvent->eventData.scanNotification.scannerAddrResolved, *ppBuffer);
            }
            break;
        case gAdvertisingSetTerminated_c:
            {
                fsciBleGetBufferFromEnumValue(pAdvertisingEvent->eventData.advSetTerminated.status, *ppBuffer, bleResult_t);
                fsciBleGetBufferFromUint8Value(pAdvertisingEvent->eventData.advSetTerminated.handle, *ppBuffer);
            }
            break;
#endif

        default:
            ; /* For MISRA compliance */
            break;

    }
}


gapScanningEvent_t* fsciBleGapAllocScanningEventForBuffer(gapScanningEventType_t eventType, uint8_t* pBuffer)
{
    uint16_t            variableLength = 0;
    gapScanningEvent_t* pScanningEvent;

    if(gDeviceScanned_c == eventType)
    {
        /* Go to dataLength field in gapScannedDevice_t structure */
        pBuffer += sizeof(bleAddressType_t) + gcBleDeviceAddressSize_c + sizeof(int8_t);

        /* Get dataLength field from buffer */
        fsciBleGetUint8ValueFromBuffer(variableLength, pBuffer);
    }
#if defined(gBLE50_d) && (gBLE50_d == 1U)
    else if (gExtDeviceScanned_c == eventType)
    {
        /* Go to dataLength field in gapExtScannedDevice_t structure */
        pBuffer += sizeof(bleAddressType_t) +
                   sizeof(bleDeviceAddress_t) +
                   sizeof(uint8_t) +
                   sizeof(bool_t) +
                   sizeof(bleAdvReportEventProperties_t) +
                   sizeof(int8_t) +
                   sizeof(int8_t) +
                   sizeof(uint8_t) +
                   sizeof(uint8_t) +
                   sizeof(uint16_t) +
                   sizeof(bool_t) +
                   sizeof(bleAddressType_t) +
                   sizeof(bleDeviceAddress_t);

        /* Get dataLength field from buffer */
        fsciBleGetUint16ValueFromBuffer(variableLength, pBuffer);
    }
    else if (gPeriodicDeviceScanned_c == eventType)
    {
        /* Go to dataLength field in gapPeriodicScannedDevice_t structure */
        pBuffer += sizeof(uint8_t) +
                   sizeof(bleAddressType_t) +
                   sizeof(bleDeviceAddress_t) +
                   sizeof(int8_t) +
                   sizeof(int8_t);

        /* Get dataLength field from buffer */
        fsciBleGetUint16ValueFromBuffer(variableLength, pBuffer);
    }
#endif

    /* Allocate memory for the scanning event */
    pScanningEvent = (gapScanningEvent_t*)MEM_BufferAlloc(sizeof(gapScanningEvent_t) + (uint32_t)variableLength);

    if(NULL != pScanningEvent)
    {
        /* Set event type in scanning event */
        pScanningEvent->eventType = eventType;

        if (gDeviceScanned_c == eventType)
        {
            /* Set pointer for the variable length data */
             pScanningEvent->eventData.scannedDevice.data = (uint8_t*)pScanningEvent + sizeof(gapScanningEvent_t);
        }
#if defined(gBLE50_d) && (gBLE50_d == 1U)
        else if (gExtDeviceScanned_c == eventType)
        {
            /* Set pointer for the variable length data */
            pScanningEvent->eventData.extScannedDevice.pData = (uint8_t*)pScanningEvent + sizeof(gapScanningEvent_t);
        }
        else if (gPeriodicDeviceScanned_c == eventType)
        {
            /* Set pointer for the variable length data */
            pScanningEvent->eventData.periodicScannedDevice.pData = (uint8_t*)pScanningEvent + sizeof(gapScanningEvent_t);
        }
#endif
    }

    /* Return memory allocated for the scanning event */
    return pScanningEvent;
}


uint16_t fsciBleGapGetScanningEventBufferSize(gapScanningEvent_t* pScanningEvent)
{
    /* Get the constant size for the needed buffer */
    uint16_t bufferSize = 0;

    /* Get the variable size for the needed buffer */
    switch(pScanningEvent->eventType)
    {
        case gScanCommandFailed_c:
            {
                bufferSize += sizeof(bleResult_t);
            }
            break;

        case gDeviceScanned_c:
            {
                bufferSize += (uint16_t)fsciBleGapGetScannedDeviceBufferSize(&pScanningEvent->eventData.scannedDevice);
                if( FALSE == pScanningEvent->eventData.scannedDevice.directRpaUsed )
                {
                    bufferSize -= gcBleDeviceAddressSize_c;
                }
            }
            break;
#if defined(gBLE50_d) && (gBLE50_d == 1U)
        case gExtDeviceScanned_c:
            {
                bufferSize += fsciBleGapGetExtScannedDeviceBufferSize(&pScanningEvent->eventData.extScannedDevice);
            }
            break;

        case gPeriodicDeviceScanned_c:
            {
                bufferSize += fsciBleGapGetPeriodicScannedDeviceBufferSize(&pScanningEvent->eventData.periodicScannedDevice);
            }
            break;

        case gPeriodicAdvSyncEstablished_c:
            {
                bufferSize += sizeof(bleResult_t);  /* Status */
                bufferSize += sizeof(uint16_t);     /* Sync Handle */
            }
            break;

        case gPeriodicAdvSyncLost_c:
            {
                bufferSize += sizeof(uint16_t);     /* Sync Handle */
            }
            break;

#endif

        default:
            ; /* For MISRA compliance */
            break;
    }

    /* Return the size needed for the buffer */
    return bufferSize;
}


void fsciBleGapGetScanningEventFromBuffer(gapScanningEvent_t* pScanningEvent, uint8_t** ppBuffer)
{
    /* Read gapScanningEvent_t fields from buffer (without eventType) */
    switch(pScanningEvent->eventType)
    {
        case gScanCommandFailed_c:
            {
                fsciBleGetEnumValueFromBuffer(pScanningEvent->eventData.failReason, *ppBuffer, bleResult_t);
            }
            break;

        case gDeviceScanned_c:
            {
                fsciBleGapGetScannedDeviceFromBuffer(&pScanningEvent->eventData.scannedDevice, ppBuffer);
            }
            break;
#if defined(gBLE50_d) && (gBLE50_d == 1U)
        case gExtDeviceScanned_c:
            {
                fsciBleGapGetExtScannedDeviceFromBuffer(&pScanningEvent->eventData.extScannedDevice, ppBuffer);
            }
            break;

        case gPeriodicDeviceScanned_c:
            {
                fsciBleGapGetPeriodicScannedDeviceFromBuffer(&pScanningEvent->eventData.periodicScannedDevice, ppBuffer);
            }
            break;

        case gPeriodicAdvSyncLost_c:
            {
                fsciBleGapGetSyncLostFromBuffer(&pScanningEvent->eventData.syncLost, ppBuffer);
            }
            break;
#endif

        default:
            ; /* For MISRA compliance */
            break;
    }
}


void fsciBleGapGetBufferFromScanningEvent(gapScanningEvent_t* pScanningEvent, uint8_t** ppBuffer)
{
    /* Write gapScanningEvent_t fields in buffer (without eventType) */
    switch(pScanningEvent->eventType)
    {
        case gScanCommandFailed_c:
            {
                fsciBleGetBufferFromEnumValue(pScanningEvent->eventData.failReason, *ppBuffer, bleResult_t);
            }
            break;

        case gDeviceScanned_c:
            {
                fsciBleGapGetBufferFromScannedDevice(&pScanningEvent->eventData.scannedDevice, ppBuffer);
            }
            break;

#if defined(gBLE50_d) && (gBLE50_d == 1U)
        case gExtDeviceScanned_c:
            {
                fsciBleGapGetBufferFromExtScannedDevice(&pScanningEvent->eventData.extScannedDevice, ppBuffer);
            }
            break;

        case gPeriodicDeviceScanned_c:
            {
                fsciBleGapGetBufferFromPerScannedDevice(&pScanningEvent->eventData.periodicScannedDevice, ppBuffer);
            }
            break;

        case gPeriodicAdvSyncEstablished_c:
            {
                fsciBleGetBufferFromEnumValue(pScanningEvent->eventData.syncEstb.status, *ppBuffer, bleResult_t);
                fsciBleGetBufferFromUint16Value(pScanningEvent->eventData.syncEstb.syncHandle, *ppBuffer);
            }
            break;

        case gPeriodicAdvSyncLost_c:
            {
                fsciBleGetBufferFromUint16Value(pScanningEvent->eventData.syncLost.syncHandle, *ppBuffer);
            }
            break;
#endif

        default:
            ; /* For MISRA compliance */
            break;
    }
}


gapConnectionEvent_t* fsciBleGapAllocConnectionEventForBuffer(gapConnectionEventType_t eventType, uint8_t* pBuffer)
{
    /* Allocate memory for the connection event */
    gapConnectionEvent_t* pConnectionEvent = (gapConnectionEvent_t*)MEM_BufferAlloc(sizeof(gapConnectionEvent_t));

    if(NULL != pConnectionEvent)
    {
        /* Set event type in buffer */
        pConnectionEvent->eventType = eventType;

        if(gConnEvtKeysReceived_c == eventType)
        {
            /* Allocate memory for the received keys */
            pConnectionEvent->eventData.keysReceivedEvent.pKeys = fsciBleGapAllocSmpKeysForBuffer(pBuffer);

            if(NULL == pConnectionEvent->eventData.keysReceivedEvent.pKeys)
            {
                /* No memory */
                fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);

                /* Free memory allocated for the connection event */
                (void)MEM_BufferFree(pConnectionEvent);

                pConnectionEvent = NULL;
            }
        }
    }

    /* Return the allocated connection event */
    return pConnectionEvent;
}


uint16_t fsciBleGapGetConnectionEventBufferSize(gapConnectionEvent_t* pConnectionEvent)
{
    /* Get the constant size for the needed buffer */
    uint16_t bufferSize = 0;

    /* Get the variable size for the needed buffer */
    switch(pConnectionEvent->eventType)
    {
        case gConnEvtConnected_c:
            {
                bufferSize += fsciBleGapGetConnectedEventBufferSize(&pConnectionEvent->eventData.connectedEvent);
                if( FALSE == pConnectionEvent->eventData.connectedEvent.peerRpaResolved )
                {
                    bufferSize -= gcBleDeviceAddressSize_c;
                }
                if( FALSE == pConnectionEvent->eventData.connectedEvent.localRpaUsed )
                {
                    bufferSize -= gcBleDeviceAddressSize_c;
                }
            }
            break;

        case gConnEvtPairingRequest_c:
        case gConnEvtPairingResponse_c:
            {
                bufferSize += fsciBleGapGetPairingParametersBufferSize(&pConnectionEvent->eventData.pairingEvent);
            }
            break;

        case gConnEvtAuthenticationRejected_c:
            {
                bufferSize += fsciBleGapGetAuthenticationRejectedEventBufferSize(&pConnectionEvent->eventData.authenticationRejectedEvent);
            }
            break;

        case gConnEvtSlaveSecurityRequest_c:
            {
                bufferSize += fsciBleGapGetSlaveSecurityRequestParametersBufferSize(&pConnectionEvent->eventData.slaveSecurityRequestEvent);
            }
            break;

        case gConnEvtKeyExchangeRequest_c:
            {
                bufferSize += fsciBleGapGetKeyExchangeRequestEventBufferSize(&pConnectionEvent->eventData.keyExchangeRequestEvent);
            }
            break;

        case gConnEvtKeysReceived_c:
            {
                bufferSize += fsciBleGapGetKeysReceivedEventBufferSize(&pConnectionEvent->eventData.keysReceivedEvent);
            }
            break;

        case gConnEvtPairingComplete_c:
            {
                bufferSize += fsciBleGapGetPairingCompleteEventBufferSize(&pConnectionEvent->eventData.pairingCompleteEvent);
            }
            break;

        case gConnEvtLongTermKeyRequest_c:
            {
                bufferSize += (uint16_t)fsciBleGapGetLongTermKeyRequestEventBufferSize(&pConnectionEvent->eventData.longTermKeyRequestEvent);
            }
            break;

        case gConnEvtEncryptionChanged_c:
            {
                bufferSize += fsciBleGapGetEncryptionChangedEventBufferSize(&pConnectionEvent->eventData.encryptionChangedEvent);
            }
            break;

        case gConnEvtDisconnected_c:
            {
                bufferSize += fsciBleGapGetDisconnectedEventBufferSize(&pConnectionEvent->eventData.disconnectedEvent);
            }
            break;

        case gConnEvtRssiRead_c:
        case gConnEvtTxPowerLevelRead_c:
            {
                bufferSize += sizeof(int8_t);
            }
            break;

        case gConnEvtPowerReadFailure_c:
            {
                bufferSize += sizeof(bleResult_t);
            }
            break;

        case gConnEvtPasskeyDisplay_c:
            {
                bufferSize += sizeof(uint32_t);
            }
            break;

        case gConnEvtParameterUpdateRequest_c:
            {
                bufferSize += fsciBleGapGetConnParameterUpdateRequestBufferSize(&pConnectionEvent->eventData.connectionUpdateRequest);
            }
            break;

        case gConnEvtParameterUpdateComplete_c:
            {
                bufferSize += fsciBleGapGetConnParameterUpdateCompleteBufferSize(&pConnectionEvent->eventData.connectionUpdateComplete);
            }
            break;

        case gConnEvtLeDataLengthChanged_c:
            {
                bufferSize += fsciBleGapGetConnLeDataLengthChangedBufferSize(&pConnectionEvent->eventData.leDataLengthChanged);
            }
            break;

        case gConnEvtLeScDisplayNumericValue_c:
            {
                bufferSize += fsciBleGapGetConnLeScDisplayNumericValueBufferSize(&pConnectionEvent->eventData.numericValueForDisplay);
            }
            break;

        case gConnEvtLeScKeypressNotification_c:
            {
                bufferSize += fsciBleGapGetConnLeScKeypressNotificationBufferSize(&pConnectionEvent->eventData.incomingKeypressNotification);
            }
            break;

        case gConnEvtChannelMapRead_c:
            {
                bufferSize += gcBleChannelMapSize_c;
            }
            break;

        case gConnEvtChannelMapReadFailure_c:
            {
                bufferSize += sizeof(bleResult_t);
            }
            break;

        default:
            ; /* For MISRA compliance */
            break;
    }

    /* Return the size needed for the buffer */
    return bufferSize;
}


void fsciBleGapGetConnectionEventFromBuffer(gapConnectionEvent_t* pConnectionEvent, uint8_t** ppBuffer)
{
    /* Read gapConnectionEvent_t fields from buffer (without eventType) */
    switch(pConnectionEvent->eventType)
    {
        case gConnEvtConnected_c:
            {
                fsciBleGapGetConnectedEventFromBuffer(&pConnectionEvent->eventData.connectedEvent, ppBuffer);
            }
            break;

        case gConnEvtPairingRequest_c:
        case gConnEvtPairingResponse_c:
            {
                fsciBleGapGetPairingParametersFromBuffer(&pConnectionEvent->eventData.pairingEvent, ppBuffer);
            }
            break;

        case gConnEvtAuthenticationRejected_c:
            {
               fsciBleGapGetAuthenticationRejectedEventFromBuffer(&pConnectionEvent->eventData.authenticationRejectedEvent, ppBuffer);
            }
            break;

        case gConnEvtSlaveSecurityRequest_c:
            {
                fsciBleGapGetSlaveSecurityRequestParametersFromBuffer(&pConnectionEvent->eventData.slaveSecurityRequestEvent, ppBuffer);
            }
            break;

        case gConnEvtKeyExchangeRequest_c:
            {
                fsciBleGapGetKeyExchangeRequestEventFromBuffer(&pConnectionEvent->eventData.keyExchangeRequestEvent, ppBuffer);
            }
            break;

        case gConnEvtKeysReceived_c:
            {
                fsciBleGapGetKeysReceivedEventFromBuffer(&pConnectionEvent->eventData.keysReceivedEvent, ppBuffer);
            }
            break;

        case gConnEvtPairingComplete_c:
            {
                fsciBleGapGetPairComplEventFromBuffer(&pConnectionEvent->eventData.pairingCompleteEvent, ppBuffer);
            }
            break;

        case gConnEvtLongTermKeyRequest_c:
            {
                fsciBleGapGetLongTermKeyRequestEventFromBuffer(&pConnectionEvent->eventData.longTermKeyRequestEvent, ppBuffer);
            }
            break;

        case gConnEvtEncryptionChanged_c:
            {
                fsciBleGapGetEncryptionChangedEventFromBuffer(&pConnectionEvent->eventData.encryptionChangedEvent, ppBuffer);
            }
            break;

        case gConnEvtDisconnected_c:
            {
                fsciBleGapGetDisconnectedEventFromBuffer(&pConnectionEvent->eventData.disconnectedEvent, ppBuffer);
            }
            break;

        case gConnEvtRssiRead_c:
            {
                fsciBleGetUint8ValueFromBufferSigned(pConnectionEvent->eventData.rssi_dBm, *ppBuffer);
            }
            break;

        case gConnEvtTxPowerLevelRead_c:
            {
                fsciBleGetUint8ValueFromBufferSigned(pConnectionEvent->eventData.txPowerLevel_dBm, *ppBuffer);
            }
            break;

        case gConnEvtPowerReadFailure_c:
            {
                fsciBleGetEnumValueFromBuffer(pConnectionEvent->eventData.failReason, *ppBuffer, bleResult_t);
            }
            break;

        case gConnEvtPasskeyDisplay_c:
            {
                fsciBleGetUint32ValueFromBuffer(pConnectionEvent->eventData.passkeyForDisplay, *ppBuffer);
            }
            break;

        case gConnEvtParameterUpdateRequest_c:
            {
                fsciBleGapGetConnParamUpdateReqFromBuffer(&pConnectionEvent->eventData.connectionUpdateRequest, ppBuffer);
            }
            break;

        case gConnEvtParameterUpdateComplete_c:
            {
                fsciBleGapGetConnParameterUpdateCompleteFromBuffer(&pConnectionEvent->eventData.connectionUpdateComplete, ppBuffer);
            }
            break;

        case gConnEvtLeDataLengthChanged_c:
            {
                fsciBleGapGetConnLeDataLengthChangedFromBuffer(&pConnectionEvent->eventData.leDataLengthChanged, ppBuffer);
            }
            break;

        case gConnEvtLeScDisplayNumericValue_c:
            {
                fsciBleGetUint32ValueFromBuffer(pConnectionEvent->eventData.numericValueForDisplay, *ppBuffer);
            }
            break;

        case gConnEvtLeScKeypressNotification_c:
            {
                fsciBleGetEnumValueFromBuffer(pConnectionEvent->eventData.incomingKeypressNotification, *ppBuffer, gapKeypressNotification_t);
            }
            break;

        case gConnEvtChannelMapRead_c:
            {
                fsciBleGetArrayFromBuffer(pConnectionEvent->eventData.channelMap, *ppBuffer, gcBleChannelMapSize_c);
            }
            break;

        case gConnEvtChannelMapReadFailure_c:
            {
                fsciBleGetEnumValueFromBuffer(pConnectionEvent->eventData.failReason, *ppBuffer, bleResult_t);
            }
            break;

        default:
                 ; /* For MISRA compliance */
            break;
    }
}


void fsciBleGapGetBufferFromConnectionEvent(gapConnectionEvent_t* pConnectionEvent, uint8_t** ppBuffer)
{
    /* Write gapConnectionEvent_t fields in buffer (without eventType) */
    switch(pConnectionEvent->eventType)
    {
        case gConnEvtConnected_c:
            {
                fsciBleGapGetBufferFromConnectedEvent(&pConnectionEvent->eventData.connectedEvent, ppBuffer);
            }
            break;

        case gConnEvtPairingRequest_c:
        case gConnEvtPairingResponse_c:
            {
                fsciBleGapGetBufferFromPairingParameters(&pConnectionEvent->eventData.pairingEvent, ppBuffer);
            }
            break;

        case gConnEvtAuthenticationRejected_c:
            {
               fsciBleGapGetBufferFromAuthenticationRejectedEvent(&pConnectionEvent->eventData.authenticationRejectedEvent, ppBuffer);
            }
            break;

        case gConnEvtSlaveSecurityRequest_c:
            {
                fsciBleGapGetBufferFromSlaveSecurityRequestParameters(&pConnectionEvent->eventData.slaveSecurityRequestEvent, ppBuffer);
            }
            break;

        case gConnEvtKeyExchangeRequest_c:
            {
                fsciBleGapGetBufferFromKeyExchangeRequestEvent(&pConnectionEvent->eventData.keyExchangeRequestEvent, ppBuffer);
            }
            break;

        case gConnEvtKeysReceived_c:
            {
                fsciBleGapGetBufferFromKeysReceivedEvent(&pConnectionEvent->eventData.keysReceivedEvent, ppBuffer);
            }
            break;

        case gConnEvtPairingComplete_c:
            {
                fsciBleGapGetBufferFromPairingCompleteEvent(&pConnectionEvent->eventData.pairingCompleteEvent, ppBuffer);
            }
            break;

        case gConnEvtLongTermKeyRequest_c:
            {
                fsciBleGapGetBufferFromLongTermKeyRequestEvent(&pConnectionEvent->eventData.longTermKeyRequestEvent, ppBuffer);
            }
            break;

        case gConnEvtEncryptionChanged_c:
            {
                fsciBleGapGetBufferFromEncryptionChangedEvent(&pConnectionEvent->eventData.encryptionChangedEvent, ppBuffer);
            }
            break;

        case gConnEvtDisconnected_c:
            {
                fsciBleGapGetBufferFromDisconnectedEvent(&pConnectionEvent->eventData.disconnectedEvent, ppBuffer);
            }
            break;

        case gConnEvtRssiRead_c:
            {
                fsciBleGetBufferFromUint8Value((uint8_t)pConnectionEvent->eventData.rssi_dBm, *ppBuffer);
            }
            break;

        case gConnEvtTxPowerLevelRead_c:
            {
                fsciBleGetBufferFromUint8Value((uint8_t)pConnectionEvent->eventData.txPowerLevel_dBm, *ppBuffer);
            }
            break;

        case gConnEvtPowerReadFailure_c:
            {
                fsciBleGetBufferFromEnumValue(pConnectionEvent->eventData.failReason, *ppBuffer, bleResult_t);
            }
            break;

        case gConnEvtPasskeyDisplay_c:
            {
                fsciBleGetBufferFromUint32Value(pConnectionEvent->eventData.passkeyForDisplay, *ppBuffer);
            }
            break;

        case gConnEvtParameterUpdateRequest_c:
            {
                fsciBleGapGetBufferFromConnParameterUpdateRequest(&pConnectionEvent->eventData.connectionUpdateRequest, ppBuffer);
            }
            break;

        case gConnEvtParameterUpdateComplete_c:
            {
                fsciBleGapGetBuffFromConnParameterUpdateComplete(&pConnectionEvent->eventData.connectionUpdateComplete, ppBuffer);
            }
            break;

        case gConnEvtLeDataLengthChanged_c:
            {
                fsciBleGapGetBufferFromConnLeDataLengthChanged(&pConnectionEvent->eventData.leDataLengthChanged, ppBuffer);
            }
            break;

        case gConnEvtLeScDisplayNumericValue_c:
            {
                fsciBleGetBufferFromUint32Value(pConnectionEvent->eventData.numericValueForDisplay, *ppBuffer);
            }
            break;

        case gConnEvtLeScKeypressNotification_c:
            {
                fsciBleGetBufferFromEnumValue(pConnectionEvent->eventData.incomingKeypressNotification, *ppBuffer, gapKeypressNotification_t);
            }
            break;

        case gConnEvtChannelMapRead_c:
            {
                fsciBleGetBufferFromArray(pConnectionEvent->eventData.channelMap, *ppBuffer, gcBleChannelMapSize_c);
            }
            break;

        case gConnEvtChannelMapReadFailure_c:
            {
                fsciBleGetBufferFromEnumValue(pConnectionEvent->eventData.failReason, *ppBuffer, bleResult_t);
            }
            break;

        default:
            ; /* For MISRA compliance */
            break;
    }
}


void fsciBleGapFreeConnectionEvent(gapConnectionEvent_t* pConnectionEvent)
{
    if(gConnEvtKeysReceived_c == pConnectionEvent->eventType)
    {
        /* Free memory allocated for the received keys */
        (void)MEM_BufferFree(pConnectionEvent->eventData.keysReceivedEvent.pKeys);
    }

    /* Free memory allocated for the connection event */
    (void)MEM_BufferFree(pConnectionEvent);
}


gapAutoConnectParams_t* fsciBleGapAllocAutoConnectParamsForBuffer(uint8_t* pBuffer)
{
    union
    {
        uint8_t*                                pConnectionRequestParamsTemp;
        gapConnectionRequestParameters_t*       aAutoConnectDataTemp;
    }connectionVars;

    uint8_t                 cNumAddresses;
    gapAutoConnectParams_t*	pAutoConnectParams;

    /* Get cNumAddresses from buffer */
    fsciBleGetUint8ValueFromBuffer(cNumAddresses, pBuffer);

    /* Allocate memory for pAutoConnectParams */
    pAutoConnectParams = (gapAutoConnectParams_t*)MEM_BufferAlloc(sizeof(gapAutoConnectParams_t) + (uint32_t)cNumAddresses * sizeof(gapConnectionRequestParameters_t));

    if(NULL != pAutoConnectParams)
    {
        /* Set aAutoConnectData pointer in gapAutoConnectParams_t structure */
        connectionVars.pConnectionRequestParamsTemp = (uint8_t*)pAutoConnectParams + sizeof(gapAutoConnectParams_t);
        pAutoConnectParams->aAutoConnectData = connectionVars.aAutoConnectDataTemp;
    }

    /* Return the buffer allocated for gapAutoConnectParams_t structure, or NULL */
    return pAutoConnectParams;
}


void fsciBleGapGetAutoConnectParamsFromBuffer(gapAutoConnectParams_t* pAutoConnectParams, uint8_t** ppBuffer)
{
    uint32_t iCount;

    /* Read gapAutoConnectParams_t fields from buffer */
    fsciBleGetUint8ValueFromBuffer(pAutoConnectParams->cNumAddresses, *ppBuffer);
    fsciBleGetBoolValueFromBuffer(pAutoConnectParams->writeInWhiteList, *ppBuffer);

    for(iCount = 0; iCount < pAutoConnectParams->cNumAddresses; iCount ++)
    {
        fsciBleGapGetConnectionRequestParametersFromBuffer(&pAutoConnectParams->aAutoConnectData[iCount], ppBuffer);
    }
}


void fsciBleGapGetBufferFromAutoConnectParams(gapAutoConnectParams_t* pAutoConnectParams, uint8_t** ppBuffer)
{
    uint32_t iCount;

    /* Write gapAutoConnectParams_t fields in buffer */
    fsciBleGetBufferFromUint8Value(pAutoConnectParams->cNumAddresses, *ppBuffer);
    fsciBleGetBufferFromBoolValue(pAutoConnectParams->writeInWhiteList, *ppBuffer);

    for(iCount = 0; iCount < pAutoConnectParams->cNumAddresses; iCount ++)
    {
        fsciBleGapGetBuffFromConnReqParameters(pAutoConnectParams->aAutoConnectData, ppBuffer);
    }
}


#if defined(gBLE50_d) && (gBLE50_d == 1U)
void fsciBleGapGetBufferFromPerAdvParameters(gapPeriodicAdvParameters_t* pAdvertisingParameters, uint8_t** ppBuffer)
{
    /* Write gapPeriodicAdvParameters_t fields in buffer */
    fsciBleGetBufferFromUint8Value( pAdvertisingParameters->handle,          *ppBuffer);
    fsciBleGetBufferFromBoolValue(  pAdvertisingParameters->addTxPowerInAdv, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pAdvertisingParameters->minInterval,     *ppBuffer);
    fsciBleGetBufferFromUint16Value(pAdvertisingParameters->maxInterval,     *ppBuffer);
}

void fsciBleGapGetPeriodicAdvParametersFromBuffer(gapPeriodicAdvParameters_t* pAdvertisingParameters, uint8_t** ppBuffer)
{
    /* Read gapPeriodicAdvParameters_t fields from buffer */
    fsciBleGetUint8ValueFromBuffer( pAdvertisingParameters->handle,          *ppBuffer);
    fsciBleGetBoolValueFromBuffer(  pAdvertisingParameters->addTxPowerInAdv, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pAdvertisingParameters->minInterval,     *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pAdvertisingParameters->maxInterval,     *ppBuffer);
}
#endif

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

#endif /* gFsciIncluded_c && gFsciBleGapLayerEnabled_d */

/*! *********************************************************************************
* @}
********************************************************************************** */
