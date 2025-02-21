/*
 * Copyright 2020 NXP
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
product: Peripherals v8.0
processor: MKE18F512xxx16
package_id: MKE18F512VLL16
mcu_data: ksdk2_0
processor_version: 0.8.1
board: TWR-KE18F
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: 2c871b10-d359-4ad0-bb59-0e87bb984e76
  called_from_default_init: true
  id_prefix: DEMO_
  selectedCore: core0
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
 * DMA initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'DMA'
- type: 'edma'
- mode: 'basic'
- custom_name_enabled: 'true'
- type_id: 'edma_6d0dd4e17e2f179c7d42d98767129ede'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'DMA'
- config_sets:
  - fsl_edma:
    - common_settings:
      - enableContinuousLinkMode: 'false'
      - enableHaltOnError: 'false'
      - enableRoundRobinArbitration: 'false'
      - enableDebugMode: 'false'
    - dma_table:
      - 0: []
      - 1: []
    - edma_channels:
      - 0:
        - apiMode: 'nontrans'
        - edma_channel:
          - channel_prefix_id: 'CH0'
          - eDMAn: '0'
          - eDMA_source: 'kDmaRequestMux0LPI2C0Tx'
          - enableTriggerInput: 'false'
          - init_channel_priority: 'false'
          - edma_channel_Preemption:
            - enableChannelPreemption: 'false'
            - enablePreemptAbility: 'false'
            - channelPriority: '0'
        - resetChannel: 'true'
        - enableChannelRequest: 'false'
        - enableAsyncRequest: 'true'
        - enableAutoStop: 'true'
        - enableMinorLoop: 'false'
        - minorLoopConfig:
          - offsetType: 'disabled'
          - mloff: '0'
        - init_channel_link: 'false'
        - channel_link: 'kEDMA_LinkNone'
        - linkedChannel: '0'
        - init_bandwidth: 'false'
        - bandwidth: 'kEDMA_BandwidthStallNone'
        - init_modulo: 'false'
        - s_mod: 'kEDMA_ModuloDisable'
        - d_mod: 'kEDMA_ModuloDisable'
        - nontransEnable: 'false'
        - nontrans_config:
          - tcdID: 'CH0_transfer'
          - saddr_expr: '&srcAddr[0]'
          - saddr_def: 'uint32_t srcAddr[]'
          - soff: 'sizeof(srcAddr[0])'
          - soff_def: ''
          - ssize: 'kEDMA_TransferSize1Bytes'
          - daddr_expr: '&dstAddr[0]'
          - daddr_def: 'uint32_t dstAddr[]'
          - doff: 'sizeof(dstAddr[0])'
          - doff_def: ''
          - dsize: 'kEDMA_TransferSize1Bytes'
          - nbytes: '1'
        - channel_enabled_interrupts: ''
        - init_interruptsEnable: 'false'
        - interrupt_channel:
          - IRQn: 'DMA0_IRQn'
          - enable_priority: 'false'
          - priority: '0'
          - enable_custom_name: 'false'
      - 1:
        - apiMode: 'nontrans'
        - edma_channel:
          - channel_prefix_id: 'CH1'
          - eDMAn: '1'
          - eDMA_source: 'kDmaRequestMux0LPI2C0Rx'
          - enableTriggerInput: 'false'
          - init_channel_priority: 'false'
          - edma_channel_Preemption:
            - enableChannelPreemption: 'false'
            - enablePreemptAbility: 'false'
            - channelPriority: '0'
        - resetChannel: 'true'
        - enableChannelRequest: 'false'
        - enableAsyncRequest: 'true'
        - enableAutoStop: 'true'
        - enableMinorLoop: 'false'
        - minorLoopConfig:
          - offsetType: 'disabled'
          - mloff: '0'
        - init_channel_link: 'false'
        - channel_link: 'kEDMA_LinkNone'
        - linkedChannel: '0'
        - init_bandwidth: 'false'
        - bandwidth: 'kEDMA_BandwidthStallNone'
        - init_modulo: 'false'
        - s_mod: 'kEDMA_ModuloDisable'
        - d_mod: 'kEDMA_ModuloDisable'
        - nontransEnable: 'false'
        - nontrans_config:
          - tcdID: 'CH1_transfer'
          - saddr_expr: ''
          - saddr_def: ''
          - soff: '0U'
          - soff_def: ''
          - ssize: 'kEDMA_TransferSize1Bytes'
          - daddr_expr: ''
          - daddr_def: ''
          - doff: '0U'
          - doff_def: ''
          - dsize: 'kEDMA_TransferSize1Bytes'
          - nbytes: '1'
        - channel_enabled_interrupts: ''
        - init_interruptsEnable: 'false'
        - interrupt_channel:
          - IRQn: 'DMA1_IRQn'
          - enable_priority: 'false'
          - priority: '0'
          - enable_custom_name: 'false'
    - errInterruptConfig:
      - enableErrInterrupt: 'false'
      - errorInterrupt:
        - IRQn: 'DMA_Error_IRQn'
        - enable_priority: 'false'
        - priority: '0'
        - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const edma_config_t DEMO_DMA_config = {
  .enableContinuousLinkMode = false,
  .enableHaltOnError = false,
  .enableRoundRobinArbitration = false,
  .enableDebugMode = false
};

void DEMO_DMA_init(void) {

  /* Channel CH0 initialization */
  /* Set the source kDmaRequestMux0LPI2C0Tx request in the DMAMUX */
  DMAMUX_SetSource(DEMO_DMA_DMAMUX_BASEADDR, DEMO_DMA_CH0_DMA_CHANNEL, DEMO_DMA_CH0_DMA_REQUEST);
  /* Enable the channel 0 in the DMAMUX */
  DMAMUX_EnableChannel(DEMO_DMA_DMAMUX_BASEADDR, DEMO_DMA_CH0_DMA_CHANNEL);
  /* DMA channel 0 reset */
  EDMA_ResetChannel(DEMO_DMA_DMA_BASEADDR, DEMO_DMA_CH0_DMA_CHANNEL);
  /* DMA channel 0 peripheral request */
  EDMA_EnableAsyncRequest(DEMO_DMA_DMA_BASEADDR, DEMO_DMA_CH0_DMA_CHANNEL, true);
  /* DMA hardware channel 0 request auto stop */
  EDMA_EnableAutoStopRequest(DEMO_DMA_DMA_BASEADDR, DEMO_DMA_CH0_DMA_CHANNEL, true);

  /* Channel CH1 initialization */
  /* Set the source kDmaRequestMux0LPI2C0Rx request in the DMAMUX */
  DMAMUX_SetSource(DEMO_DMA_DMAMUX_BASEADDR, DEMO_DMA_CH1_DMA_CHANNEL, DEMO_DMA_CH1_DMA_REQUEST);
  /* Enable the channel 1 in the DMAMUX */
  DMAMUX_EnableChannel(DEMO_DMA_DMAMUX_BASEADDR, DEMO_DMA_CH1_DMA_CHANNEL);
  /* DMA channel 1 reset */
  EDMA_ResetChannel(DEMO_DMA_DMA_BASEADDR, DEMO_DMA_CH1_DMA_CHANNEL);
  /* DMA channel 1 peripheral request */
  EDMA_EnableAsyncRequest(DEMO_DMA_DMA_BASEADDR, DEMO_DMA_CH1_DMA_CHANNEL, true);
  /* DMA hardware channel 1 request auto stop */
  EDMA_EnableAutoStopRequest(DEMO_DMA_DMA_BASEADDR, DEMO_DMA_CH1_DMA_CHANNEL, true);
}

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
      - debugEnable: 'true'
      - ignoreAck: 'false'
      - pinConfig: 'kLPI2C_2PinOpenDrain'
      - baudRate_Hz: '400000'
      - busIdleTimeout_ns: '0'
      - pinLowTimeout_ns: '0'
      - sdaGlitchFilterWidth_ns: '0'
      - sclGlitchFilterWidth_ns: '0'
      - hostRequest:
        - enable: 'false'
        - source: 'kLPI2C_HostRequestExternalPin'
        - polarity: 'kLPI2C_HostRequestPinActiveHigh'
      - edmaRequestSources: 'enableRx enableTx'
    - transfer:
      - blocking: 'false'
      - flags: ''
      - slaveAddress: '0'
      - direction: 'kLPI2C_Write'
      - subaddress: '0'
      - subaddressSize: '1'
      - dataSize: '1'
      - callback:
        - name: 'lpi2c_master_callback'
        - userData: ''
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const lpi2c_master_config_t DEMO_LPI2C_masterConfig = {
  .enableMaster = true,
  .enableDoze = true,
  .debugEnable = true,
  .ignoreAck = false,
  .pinConfig = kLPI2C_2PinOpenDrain,
  .baudRate_Hz = 400000,
  .busIdleTimeout_ns = 0,
  .pinLowTimeout_ns = 0,
  .sdaGlitchFilterWidth_ns = 0,
  .sclGlitchFilterWidth_ns = 0,
  .hostRequest = {
    .enable = false,
    .source = kLPI2C_HostRequestExternalPin,
    .polarity = kLPI2C_HostRequestPinActiveHigh
  }
};
lpi2c_master_transfer_t DEMO_LPI2C_masterTransfer = {
  .flags = kLPI2C_TransferDefaultFlag,
  .slaveAddress = 0,
  .direction = kLPI2C_Write,
  .subaddress = 0,
  .subaddressSize = 1,
  .data = DEMO_LPI2C_masterBuffer,
  .dataSize = 1
};
lpi2c_master_handle_t DEMO_LPI2C_masterHandle;
uint8_t DEMO_LPI2C_masterBuffer[DEMO_LPI2C_MASTER_BUFFER_SIZE];

void DEMO_LPI2C_init(void) {
  LPI2C_MasterInit(DEMO_LPI2C_PERIPHERAL, &DEMO_LPI2C_masterConfig, DEMO_LPI2C_CLOCK_FREQ);
  LPI2C_MasterTransferCreateHandle(DEMO_LPI2C_PERIPHERAL, &DEMO_LPI2C_masterHandle, lpi2c_master_callback, NULL);
  /* Enable Master eDMA request sources: Tx, Rx */
  LPI2C_MasterEnableDMA(DEMO_LPI2C_PERIPHERAL, true, true);
}

/***********************************************************************************************************************
 * LPIT initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LPIT'
- type: 'lpit'
- mode: 'LPIT_GENERAL'
- custom_name_enabled: 'true'
- type_id: 'lpit_8e4186d834c8d9f4b6c0dadcc9dc2f05'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'LPIT0'
- config_sets:
  - fsl_lpit:
    - lpitConfig:
      - enableRunInDebug: 'true'
      - enableRunInDoze: 'true'
    - timingConfig:
      - clockSource: 'AsyncPeripheralClock'
      - clockSourceFreq: 'BOARD_BootClockRUN'
    - channels:
      - 0:
        - lpitChannelPrefixID: 'Channel'
        - channelNumber: '0'
        - enableChain: 'false'
        - timerMode: 'kLPIT_PeriodicCounter'
        - timerPeriod: '500ms'
        - lpit_trigger_select_t: 'internal_trigger_0'
        - enableReloadOnTriggerBool: 'false'
        - enableStopOnTimeout: 'false'
        - enableStartOnTriggerBool: 'false'
        - startTimer: 'true'
        - enableInterrupt: 'true'
        - interrupt:
          - IRQn: 'LPIT0_Ch0_IRQn'
          - enable_priority: 'false'
          - priority: '0'
          - enable_custom_name: 'true'
          - handler_custom_name: 'LPIT_IRQHandler'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const lpit_chnl_params_t DEMO_LPIT_Channel_struct = {
  .chainChannel = false,
  .timerMode = kLPIT_PeriodicCounter,
  .triggerSource = kLPIT_TriggerSource_Internal,
  .triggerSelect = kLPIT_Trigger_TimerChn0,
  .enableReloadOnTrigger = false,
  .enableStopOnTimeout = false,
  .enableStartOnTrigger = false
};
const lpit_config_t DEMO_LPIT_config = {
  .enableRunInDebug = true,
  .enableRunInDoze = true
};

void DEMO_LPIT_init(void) {
  /* Initialize the LPIT. */
  LPIT_Init(DEMO_LPIT_PERIPHERAL, &DEMO_LPIT_config);
  /* Setup channel 0. */
  LPIT_SetupChannel(DEMO_LPIT_PERIPHERAL, DEMO_LPIT_CHANNEL, &DEMO_LPIT_Channel_struct);
  /* Set channel 0 period to 4000000 ticks. */
  LPIT_SetTimerPeriod(DEMO_LPIT_PERIPHERAL, DEMO_LPIT_CHANNEL, DEMO_LPIT_CHANNEL_TICKS);
  /* Enable interrupts from channel Channel. */
  LPIT_EnableInterrupts(DEMO_LPIT_PERIPHERAL, kLPIT_Channel0TimerInterruptEnable);
  /* Enable interrupt DEMO_LPIT_0_IRQN request in the NVIC */
  EnableIRQ(DEMO_LPIT_0_IRQN);
  /* Start channel 0. */
  LPIT_StartTimer(DEMO_LPIT_PERIPHERAL, DEMO_LPIT_CHANNEL);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Global initialization */
  DMAMUX_Init(DEMO_DMA_DMAMUX_BASEADDR);
  EDMA_Init(DEMO_DMA_DMA_BASEADDR, &DEMO_DMA_config);

  /* Initialize components */
  DEMO_DMA_init();
  DEMO_LPI2C_init();
  DEMO_LPIT_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
