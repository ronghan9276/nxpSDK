Overview
========
The FTM project is a demonstration program of the SDK FTM driver's dual-edge capture feature.
This feature is available only on certain SoC's.
The example sets up a FTM channel-pair for dual-edge capture. Once the input signal is received,
this example will print the capture values and period of the input signal on the terminal window.

Toolchain supported
===================
- IAR embedded Workbench  8.40.2
- Keil MDK  5.29
- GCC ARM Embedded  8.3.1
- MCUXpresso  11.1.0

Hardware requirements
=====================
- Mini/micro USB cable
- TWR-KV11Z75M board
- Personal Computer
- Primary Elevater board

Board settings
==============
 Connect input into J18-12

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
These instructions are displayed/shown on the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FTM dual-edge capture example
Once the input signal is received the input capture values are printed
The input signal's pulse width is calculated from the capture values & printed
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Customization options
=====================

