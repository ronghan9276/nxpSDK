Overview
========
The Power mode switch demo application demonstrates the use of power modes in the KSDK. The demo prints the power mode menu
through the debug console, where the user can set the MCU to a specific power mode. User can wakeup the core by key interrupt.
The purpose of this demo is to show how to switch between different power  modes, and how to configure a wakeup source and
wakeup the MCU from low power modes.

Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- GCC ARM Embedded  10.3.1
- MCUXpresso  11.6.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1020 board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board. 
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When running the demo, the debug console shows the menu to command the MCU to the target power mode.

~~~~~~~~~~~~~~~~~~~~~

CPU wakeup source 0x1...

***********************************************************
	Power Mode Switch Demo for iMXRT1021
***********************************************************

***********************************************************
CPU:             500000000 Hz
AHB:             500000000 Hz
SEMC:            62500000 Hz
IPG:             125000000 Hz
PER:             62500000 Hz
OSC:             24000000 Hz
RTC:             32768 Hz
USB1PLL:         480000000 Hz
USB1PLLPFD0:     392727258 Hz
USB1PLLPFD1:     246857130 Hz
USB1PLLPFD2:     332307684 Hz
USB1PLLPFD3:     576000000 Hz
SYSPLL:          528000000 Hz
SYSPLLPFD0:      351999990 Hz
SYSPLLPFD1:      594000000 Hz
SYSPLLPFD2:      527999994 Hz
SYSPLLPFD3:      527999994 Hz
ENETPLL0:        0 Hz
ENETPLL25M:      0 Hz
ENETPLL500M:     500000000 Hz
AUDIOPLL:        24000000 Hz
***********************************************************


########## Power Mode Switch Demo ###########

    Core Clock = 500000000Hz 
    Power mode: Over RUN

***********************************************************
CPU:             500000000 Hz
AHB:             500000000 Hz
SEMC:            125000000 Hz
IPG:             125000000 Hz
PER:             62500000 Hz
OSC:             24000000 Hz
RTC:             32768 Hz
***********************************************************


Select the desired operation 

Press  A for enter: Over RUN       - System Over Run mode
Press  B for enter: Full RUN       - System Full Run mode
Press  C for enter: Low Speed RUN  - System Low Speed Run mode
Press  D for enter: Low Power RUN  - System Low Power Run mode
Press  E for enter: System Idle    - System Wait mode
Press  F for enter: Low Power Idle - Low Power Idle mode
Press  G for enter: Suspend        - Suspend mode
Press  H for enter: SNVS           - Shutdown the system

Waiting for power mode select...


~~~~~~~~~~~~~~~~~~~~~


Note: Only input when the demo asks for input. Input entered at any other time might cause the debug console to overflow
and receive the wrong input value.

Note: When wake up from Suspend state, target will reset. Please run in flexspi_nor_debug and flexspi_nor_release targets to test Suspend states.

Note:
To download binary into external flash and boot from external flash directly, following steps are needed:
1. Compile flash target of the project, and get the binaray file "power_mode_switch_bm.bin".
2. Set the SW8: 1 off 2 off 3 on 4 off, then power on the board and connect USB cable to J23.
3. Drop the binaray into disk "RT1020-EVK" on PC.
4. Wait for the disk disappear and appear again which will take couple of seconds.
5. Reset the board by pressing SW3 or power off and on the board. 

Note:
To debug in external flash, following steps are needed:
1. Select the flash target and compile.
2. Set the SW8: 1 off 2 off 3 on 4 off, then power on the board and connect USB cable to J23.
3. Start debugging in IDE.
   - Keil: Click "Download (F8)" to program the image to external flash first then clicking "Start/Stop Debug Session (Ctrl+F5)" to start debugging.
