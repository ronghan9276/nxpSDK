Overview
========
This example demonstrates how to use the LCDIF gamma correction feature. In this
example, the gamma corretion table is set to invert the original picture. The
original picture is gradual changed gray bars, the gamma correction is continuously
enabled and disabled, so you can see the screen switch between the original
picture and the inverted picture.

Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- GCC ARM Embedded  10.3.1
- MCUXpresso  11.6.0

Hardware requirements
=====================
- Micro USB cable
- EVK-MIMXRT595 board
- Personal Computer
- RK055AHD091 panel or RK055MHD091 panel

Board settings
==============
Connect the MIPI panel to EVK-MIMXRT595 board J44.

Prepare the Demo
================
1.  Connect a micro USB cable between the PC host and the CMSIS DAP USB port (J40) on the board
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Build the project, this project uses RK055MHD091 panel by default, to use the RK055AHD091 panel,
    change #define USE_MIPI_PANEL MIPI_PANEL_RK055MHD091 to #define USE_MIPI_PANEL MIPI_PANEL_RK055AHD091
    in lcdif_support.h.
4.  Download the program to the target board.
5.  Launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs, the screen shows what described in overview.
