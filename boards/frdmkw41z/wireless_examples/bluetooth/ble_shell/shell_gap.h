/*! *********************************************************************************
 * \defgroup SHELL GAP
 * @{
 ********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
* 
* file
*
* This file is the interface file for the GAP Shell module
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef _SHELL_GAP_H_
#define _SHELL_GAP_H_

/*************************************************************************************
**************************************************************************************
* Public macros
**************************************************************************************
*************************************************************************************/
#include "l2ca_interface.h"

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */
/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

int8_t  ShellGap_Command(uint8_t argc, char * argv[]);
void    ShellGap_GenericCallback (gapGenericEvent_t* pGenericEvent);

void ShellGap_L2caControlCallback
(
    l2capControlMessageType_t  messageType,
    void* pMessage
);

#ifdef __cplusplus
}
#endif 


#endif /* _SHELL_GAP_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */
