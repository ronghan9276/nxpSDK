Overview
========
The pflash example shows how to use flash driver to operate program flash:



Toolchain supported
===================
- IAR embedded Workbench  8.50.1
- Keil MDK  5.30
- GCC ARM Embedded  9.2.1
- MCUXpresso  11.2.0

Hardware requirements
=====================
- Micro USB cable
- TWR-KE18F board
- Personal Computer

Board settings
==============
This example project does not call for any special hardware configurations.
Although not required, the recommendation is to leave the development board's jumper settings
and configurations in default state when running this example.

Prepare the Demo
================
1. Connect a micro USB cable between the PC host and the OpenSDA USB port on the board.
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
~~~~~~~~~~~~
 PFlash Example Start 

 PFlash Information: 
 Total Program Flash Size:  512 KB, Hex: (0x80000)
 Program Flash Sector Size: 4 KB, Hex: (0x1000) 
 Flash is UNSECURE!

 Erase a sector of flash
 Successfully Erased Sector 0x7f000 -> 0x80000

 Program a buffer to a sector of flash 
 Successfully Programmed and Verified Location 0x7f000 -> 0x7f010 

 End of PFlash Example 
~~~~~~~~~~~~
Customization options
=====================

