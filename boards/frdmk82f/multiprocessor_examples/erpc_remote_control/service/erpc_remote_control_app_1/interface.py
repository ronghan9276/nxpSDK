# Copyright (c) 2014-2016, Freescale Semiconductor, Inc.
# Copyright 2016 NXP
# All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause

#
# Generated by erpcgen 1.7.4 on Thu Apr 16 10:59:26 2020.
#
# AUTOGENERATED - DO NOT EDIT
#

import erpc

# Abstract base class for remote_control_app_1
class Iremote_control_app_1(object):
    SERVICE_ID = 2
    BUTTON_PRESSED_ID = 1

   #Return which button was pressed
    def button_pressed(self, which):
        raise NotImplementedError()


