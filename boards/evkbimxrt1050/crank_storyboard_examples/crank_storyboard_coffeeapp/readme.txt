Overview
========
This sample demonstrates the Storyboard engine in its low memory configuration while still providing a high-performance UI.


Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- MCUXpresso  11.6.0

Hardware requirements
=====================
- Micro USB cable
- EVKB-IMXRT1050 board
- RK043FN02H-CT or RK043FN66HS-CT6 LCD board
- Personal Computer

Board settings
==============
1. Connect the RK043FN02H-CT or RK043FN66HS-CT6 to board.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board. 
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Build the project, the project uses RK043FN66HS-CT6 by default, to use other panels,
    change
    #define DEMO_PANEL DEMO_PANEL_RK043FN66HS
    to
    #define DEMO_PANEL DEMO_PANEL_RK043FN02H
    in emwin_support.h
4.  Download the program to the target board.
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
Following text is displayed in the console:
***********************************************
* Crank Software Storyboard Demo
* Storyboard Runtime version :6.2.0 build 0
* Target platform : IMXRT1050-EVKB
* Target OS : FreeRTOS V10.2.1
* Target Filesystem : SBVFS
***********************************************
