/*! *********************************************************************************
 * \addtogroup BLE
 * @{
 ********************************************************************************** */
/*
* Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*!
\file       ble_init.h
*/

#ifndef _BLE_INIT_H_
#define _BLE_INIT_H_

/************************************************************************************
*************************************************************************************
* Includes
*************************************************************************************
************************************************************************************/
#include "ble_general.h"

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief  Performs full initialization of the BLE stack.
*
* \param[in] genericCallback  Callback used by the Host Stack to propagate GAP generic 
* events to the application.
*
* \return  gBleSuccess_c or error.
*
* \remarks The gInitializationComplete_c generic GAP event is triggered on completion.
*
********************************************************************************** */
bleResult_t Ble_Initialize
(
    gapGenericCallback_t gapGenericCallback
);

#endif /* _BLE_INIT_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
