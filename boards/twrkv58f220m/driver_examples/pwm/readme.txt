Overview
========
The PWM project is a simple demonstration program of the SDK PWM driver.
The pulse width modulator (PWM) module contains PWM submodules, each of which is set up to control a single half-bridge power stage.
Fault channel support is provided. This PWM module can generate various switching patterns, including highly sophisticated waveforms.
It can be used to control all known Switched Mode Power Supplies (SMPS) topologies.

Toolchain supported
===================
- IAR embedded Workbench  8.50.1
- Keil MDK  5.30
- GCC ARM Embedded  9.2.1
- MCUXpresso  11.2.0

Hardware requirements
=====================
- Mini/micro USB cable
- TWR-KV58F220M board
- Personal Computer
- TWR-ELEV Primary boards

Board settings
==============
No special settings are required.

* Probe the pwm signal using an oscilloscope
 - At Primary B63
 - At Primary A76
 - At Primary A78

Prepare the Demo
================
1. Connect a USB cable between the PC host and the OpenSDA USB port on the board.
2. Open a serial terminal with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:
~~~~~~~~~~~~~~~~~~~~~~~~
FlexPWM driver example
~~~~~~~~~~~~~~~~~~~~~~~
Customization options
=====================

