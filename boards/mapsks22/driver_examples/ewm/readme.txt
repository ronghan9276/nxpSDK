Overview
========
The EWM Example project is to demonstrate usage of the KSDK EWM driver.
In the example, EWM counter is continuously refreshed until button is pressed.
Once the button is pressed, EWM counter will expire and interrupt will be generated.
After the first pressing, another interrupt can be triggered by pressing button again.

Toolchain supported
===================
- Keil MDK 5.24a
- IAR embedded Workbench 8.22.2
- GCC ARM Embedded 7-2017-q4-major
- MCUXpresso10.2.0

Hardware requirements
=====================
- Mini/micro USB cable
- MAPS-KS22F256 board & MAPS-DOCK board
- Personal Computer

Board settings
==============
The ewm example is configured to use UART1 with PTE0 and PTE1 pins. To make JLink serial
device work, the jumpers on MAPS-DOCK board should be set as following:
- JP7 on MAPS-Dock: UART0 related jumpers connected

Prepare the Demo
================
1. Connect a mini USB cable between the PC host and the USB port (CN14) on MAPS-DOCK board.
2. Open a serial terminal on PC for JLink serial device with these settings:
   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running
   the demo.

Running the demo
================

When the example runs successfully, you can see the similar information from the terminal as below.

~~~~~~~~~~~~~~~~~~~~~
EWM example
Press SW3 to expire EWM
EWM interrupt is occurred
Press SW3 to expire EWM again
~~~~~~~~~~~~~~~~~~~~~
Customization options
=====================

