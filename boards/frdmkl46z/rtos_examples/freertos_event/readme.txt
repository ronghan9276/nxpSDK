Overview
========
This document explains the freertos_event example. It shows how task waits for an event (defined set
of bits in event group). This event can be set by any other process or interrupt in the system.

The example application creates three tasks. Two write tasks write_task_1 and write_task_2
continuously setting event bit 0 and bit 1.

Read_task is waiting for any event bit and printing actual state on console. Event bits are
automatically cleared after read task is entered.

Three possible states can occurre:
Both bits are set.z
Bit B0 is set.
Bit B1 is set.


Toolchain supported
===================
- Keil MDK 5.24a
- IAR embedded Workbench 8.22.2
- GCC ARM Embedded 7-2017-q4-major
- MCUXpresso10.2.0

Hardware requirements
=====================
- Mini/Micro USB cable
- FRDM-KL46Z board
- Personal Computer

Board settings
==============
This example project does not call for any special hardware configurations.
Although not required, the recommendation is to leave the development board's jumper settings
and configurations in default state when running this example.
Prepare the Demo
================

Running the demo
================
After the board is flashed the Tera Term will start printing the state of event bits.

Example output:
Bit B1 is set.
Bit B0 is set.
Bit B1 is set.
Bit B0 is set.
Bit B1 is set
Customization options
=====================

