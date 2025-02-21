/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v7.0
processor: MKE18F512xxx16
package_id: MKE18F512VLL16
mcu_data: ksdk2_0
processor_version: 0.7.0
board: TWR-KE18F
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: 12d2edbc-820e-4aa6-924f-04ddec6a2278
  called_from_default_init: true
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system_54b53072540eeeb8f8e9343e71f28176'
- global_system_definitions: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'msg'
- type_id: 'msg_6e2baaf3b97dbeef01c0043275f9a0e7'
- global_messages: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * LPI2C initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LPI2C'
- type: 'lpi2c'
- mode: 'master'
- custom_name_enabled: 'true'
- type_id: 'lpi2c_db68d4f4f06a22e25ab51fe9bd6db4d2'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'LPI2C0'
- config_sets:
  - main:
    - clockSource: 'Lpi2cClock'
    - clockSourceFreq: 'GetIpFreq'
    - interrupt:
      - IRQn: 'LPI2C0_IRQn'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - quick_selection: 'qs_interrupt'
  - master:
    - mode: 'transfer'
    - config:
      - enableMaster: 'true'
      - enableDoze: 'true'
      - debugEnable: 'false'
      - ignoreAck: 'false'
      - pinConfig: 'kLPI2C_2PinOpenDrain'
      - baudRate_Hz: '100000'
      - busIdleTimeout_ns: '0'
      - pinLowTimeout_ns: '0'
      - sdaGlitchFilterWidth_ns: '0'
      - sclGlitchFilterWidth_ns: '0'
      - hostRequest:
        - enable: 'false'
        - source: 'kLPI2C_HostRequestExternalPin'
        - polarity: 'kLPI2C_HostRequestPinActiveHigh'
    - transfer:
      - blocking: 'false'
      - flags: ''
      - slaveAddress: '0'
      - direction: 'kLPI2C_Write'
      - subaddress: '0'
      - subaddressSize: '1'
      - dataSize: '1'
      - callback:
        - name: ''
        - userData: ''
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const lpi2c_master_config_t LPI2C_masterConfig = {
    .enableMaster            = true,
    .enableDoze              = true,
    .debugEnable             = false,
    .ignoreAck               = false,
    .pinConfig               = kLPI2C_2PinOpenDrain,
    .baudRate_Hz             = 100000,
    .busIdleTimeout_ns       = 0,
    .pinLowTimeout_ns        = 0,
    .sdaGlitchFilterWidth_ns = 0,
    .sclGlitchFilterWidth_ns = 0,
    .hostRequest             = {
        .enable = false, .source = kLPI2C_HostRequestExternalPin, .polarity = kLPI2C_HostRequestPinActiveHigh}};
lpi2c_master_transfer_t LPI2C_masterTransfer = {.flags          = kLPI2C_TransferDefaultFlag,
                                                .slaveAddress   = 0,
                                                .direction      = kLPI2C_Write,
                                                .subaddress     = 0,
                                                .subaddressSize = 1,
                                                .data           = LPI2C_masterBuffer,
                                                .dataSize       = 1};
lpi2c_master_handle_t LPI2C_masterHandle;
uint8_t LPI2C_masterBuffer[LPI2C_MASTER_BUFFER_SIZE];

void LPI2C_init(void)
{
    LPI2C_MasterInit(LPI2C_PERIPHERAL, &LPI2C_masterConfig, LPI2C_CLOCK_FREQ);
    LPI2C_MasterTransferCreateHandle(LPI2C_PERIPHERAL, &LPI2C_masterHandle, NULL, NULL);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
    /* Initialize components */
    LPI2C_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
    BOARD_InitPeripherals();
}
