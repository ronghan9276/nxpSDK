Overview
========
The flexio_uart_polling example shows how to use flexio uart driver in polling way:

In this example, a flexio simulated uart connect to PC through USB-Serial, the board will send back
all characters that PC send to the board.

Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- MCUXpresso  11.6.0
- GCC ARM Embedded  10.3.1

Hardware requirements
=====================
- Mini/micro USB cable
- MIMXRT1160-EVK board
- Personal Computer
- USB to Com Converter

Board settings
==============
Connect pin:
- RX of USB2COM to J26-2
- TX of USB2COM to J26-4
- GND of USB2COM to J10-14

Prepare the Demo
================
1.  Connect the USB2COM Converter to the host PC 
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
When the demo runs successfully, the log would be seen on the UART Terminal port which connected to the USB2COM like:

~~~~~~~~~~~~~~~~~~~~~
Flexio uart polling example
Board will send back received characters
~~~~~~~~~~~~~~~~~~~~~
