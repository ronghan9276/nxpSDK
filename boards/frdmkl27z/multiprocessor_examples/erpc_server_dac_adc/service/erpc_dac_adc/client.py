# Copyright (c) 2014-2016, Freescale Semiconductor, Inc.
# Copyright 2016 NXP
# All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause

#
# Generated by erpcgen 1.8.0 on Thu Oct  8 16:38:35 2020.
#
# AUTOGENERATED - DO NOT EDIT
#

import erpc
from . import common, interface

# Client for dac_adc
class dac_adcClient(interface.Idac_adc):
    def __init__(self, manager):
        super(dac_adcClient, self).__init__()
        self._clientManager = manager

    def adc_get_config(self, config):
        assert type(config) is erpc.Reference, "out parameter must be a Reference object"

        # Build remote function invocation message.
        request = self._clientManager.create_request()
        codec = request.codec
        codec.start_write_message(erpc.codec.MessageInfo(
                type=erpc.codec.MessageType.kInvocationMessage,
                service=self.SERVICE_ID,
                request=self.ADC_GET_CONFIG_ID,
                sequence=request.sequence))

        # Send request and process reply.
        self._clientManager.perform_request(request)
        config.value = common.AdcConfig()._read(codec)

    def convert_dac_adc(self, numberToConvert, result):
        assert type(result) is erpc.Reference, "out parameter must be a Reference object"

        # Build remote function invocation message.
        request = self._clientManager.create_request()
        codec = request.codec
        codec.start_write_message(erpc.codec.MessageInfo(
                type=erpc.codec.MessageType.kInvocationMessage,
                service=self.SERVICE_ID,
                request=self.CONVERT_DAC_ADC_ID,
                sequence=request.sequence))
        if numberToConvert is None:
            raise ValueError("numberToConvert is None")
        codec.write_uint32(numberToConvert)

        # Send request and process reply.
        self._clientManager.perform_request(request)
        result.value = codec.read_uint32()

    def set_led(self, whichLed):
        # Build remote function invocation message.
        request = self._clientManager.create_request()
        codec = request.codec
        codec.start_write_message(erpc.codec.MessageInfo(
                type=erpc.codec.MessageType.kInvocationMessage,
                service=self.SERVICE_ID,
                request=self.SET_LED_ID,
                sequence=request.sequence))
        if whichLed is None:
            raise ValueError("whichLed is None")
        codec.write_uint8(whichLed)

        # Send request and process reply.
        self._clientManager.perform_request(request)

    def read_senzor_mag_accel(self, results):
        assert type(results) is erpc.Reference, "out parameter must be a Reference object"

        # Build remote function invocation message.
        request = self._clientManager.create_request()
        codec = request.codec
        codec.start_write_message(erpc.codec.MessageInfo(
                type=erpc.codec.MessageType.kInvocationMessage,
                service=self.SERVICE_ID,
                request=self.READ_SENZOR_MAG_ACCEL_ID,
                sequence=request.sequence))

        # Send request and process reply.
        self._clientManager.perform_request(request)
        results.value = common.Vector()._read(codec)

    def board_get_name(self, name):
        assert type(name) is erpc.Reference, "out parameter must be a Reference object"

        # Build remote function invocation message.
        request = self._clientManager.create_request()
        codec = request.codec
        codec.start_write_message(erpc.codec.MessageInfo(
                type=erpc.codec.MessageType.kInvocationMessage,
                service=self.SERVICE_ID,
                request=self.BOARD_GET_NAME_ID,
                sequence=request.sequence))

        # Send request and process reply.
        self._clientManager.perform_request(request)
        name.value = codec.read_string()



