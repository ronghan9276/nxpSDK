Overview
========
The EDMA memory to memory example is a simple demonstration program that uses the SDK software.
It excuates one shot transfer from source buffer to destination buffer using the SDK EDMA drivers.
The purpose of this example is to show how to use the EDMA and to provide a simple example for
debugging and further development.
Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-KL82Z board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1. Connect a USB cable between the host PC and the OpenSDA USB port on the target board.
2. Open a serial terminal with the following settings:
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

~~~~~~~~~~~~~~~~~~~~~
EDMA scatter_gather transfer example begin.

Destination Buffer:
0       0       0       0       0       0       0       0

EDMA scatter_gather transfer example finish.

Destination Buffer:
1       2       3       4       5       6       7       8
~~~~~~~~~~~~~~~~~~~~~

Toolchain supported
===================
- IAR embedded Workbench  8.32.1
- Keil MDK  5.26
- GCC ARM Embedded  7.3.1
- MCUXpresso 10.3.0

