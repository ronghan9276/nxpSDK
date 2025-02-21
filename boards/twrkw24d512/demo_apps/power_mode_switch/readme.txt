Overview
========
The Power mode switch demo application demonstrates the use of power modes in the KSDK. The demo prints the power mode menu
through the debug console, where the user can set the MCU to a specific power mode. The user can also set the wakeup
source by following the debug console prompts. The purpose of this demo is to show how to switch between different power
 modes, and how to configure a wakeup source and wakeup the MCU from low power modes.

Toolchain supported
===================
- IAR embedded Workbench 7.80.4
- Keil MDK 5.21a
- GCC ARM Embedded 2016-5.4-q3
- Kinetis Development Studio IDE 3.2.0
- MCUXpresso0.8

Hardware requirements
=====================
- Mini/micro USB cable
- TWRKW24D512 board
- Personal Computer

Board settings
==============
No special board setting.

Prepare the Demo
================
1.  Connect a mini/micro USB cable between the PC host and the OpenSDA USB port on the board.
2.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 9600 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Press the reset button on your board to begin running the demo.

Running the demo
================
When runing the demo, the debug console shows the menu to tell how to set MCU
to target power mode.

NOTE: Only input when the demo asks to input, input at other time might make the
debug console overflow and get wrong result.
~~~~~~~~~~~~~~~~~~~~~
####################  Power Mode Switch Demo ####################

    Core Clock = 48000000Hz
    Power mode: RUN

Select the desired operation

Press  A for enter: RUN      - Normal RUN mode
Press  B for enter: WAIT     - Wait mode
Press  C for enter: STOP     - Stop mode
Press  D for enter: VLPR     - Very Low Power Run mode
Press  E for enter: VLPW     - Very Low Power Wait mode
Press  F for enter: VLPS     - Very Low Power Stop mode
Press  G for enter: LLS/LLS3 - Low Leakage Stop mode
Press  H for enter: VLLS0    - Very Low Leakage Stop 0 mode
Press  I for enter: VLLS1    - Very Low Leakage Stop 1 mode
Press  J for enter: VLLS2    - Very Low Leakage Stop 2 mode
Press  K for enter: VLLS3    - Very Low Leakage Stop 3 mode

Waiting for power mode select..
~~~~~~~~~~~~~~~~~~~~~
Customization options
=====================

