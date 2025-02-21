Overview
========
The lpi2c_functional_interrupt example shows how to use lpi2c functional driver to build a interrupt based application:

In this example , one lpi2c instance used as lpi2c master and another lpi2c instance used as lpi2c slave .
1. lpi2c master send data using interrupt to lpi2c slave in interrupt .
2. lpi2c master read data using interrupt from lpi2c slave in interrupt .
3. The example assumes that the connection is OK between master and slave, so there's NO error handling code.

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
- Primary Elevator
- Personal Computer

Board settings
==============
The example requires connecting the between two LPI2C pins
Insert TWR-KE18F board into Primary Elevator. The connection should be set as following:
- A7-Elevator, B50-Elevator connected
- A8-Elevator, B51-Elevator connected

Prepare the Demo
================
1. Connect a micro USB cable between the PC host and the OpenSDA USB port on the board.
2. Open a serial terminal on PC for OpenSDA serial device with these settings:
   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.

~~~~~~~~~~~~~~~~~~~~~
LPI2C example -- MasterFunctionalInterrupt_SlaveFunctionalInterrupt.

Master will send data :

0x 0  0x 1  0x 2  0x 3  0x 4  0x 5  0x 6  0x 7

0x 8  0x 9  0x a  0x b  0x c  0x d  0x e  0x f

0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17

0x18  0x19  0x1a  0x1b  0x1c  0x1d  0x1e  0x1f


Slave received data :

0x 0  0x 1  0x 2  0x 3  0x 4  0x 5  0x 6  0x 7

0x 8  0x 9  0x a  0x b  0x c  0x d  0x e  0x f

0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17

0x18  0x19  0x1a  0x1b  0x1c  0x1d  0x1e  0x1f


This time , slave will send data:

0xff  0xfe  0xfd  0xfc  0xfb  0xfa  0xf9  0xf8

0xf7  0xf6  0xf5  0xf4  0xf3  0xf2  0xf1  0xf0

0xef  0xee  0xed  0xec  0xeb  0xea  0xe9  0xe8

0xe7  0xe6  0xe5  0xe4  0xe3  0xe2  0xe1  0xe0


Master received data :

0xff  0xfe  0xfd  0xfc  0xfb  0xfa  0xf9  0xf8

0xf7  0xf6  0xf5  0xf4  0xf3  0xf2  0xf1  0xf0

0xef  0xee  0xed  0xec  0xeb  0xea  0xe9  0xe8

0xe7  0xe6  0xe5  0xe4  0xe3  0xe2  0xe1  0xe0

End of LPI2C example .
~~~~~~~~~~~~~~~~~~~~~
Customization options
=====================

