Overview
========
The Hello World demo application provides a sanity check for the new SDK build environments and board bring up. The Hello
World demo prints the "Hello World" string to the terminal using the SDK UART drivers. The purpose of this demo is to
show how to use the UART, and to provide a simple project for debugging and further development.
Note: Please input one character at a time. If you input too many characters each time, the receiver may overflow
because the low level UART uses simple polling way for receiving. If you want to try inputting many characters each time,
just define DEBUG_CONSOLE_TRANSFER_NON_BLOCKING in your project to use the advanced debug console utility.

Toolchain supported
===================
- IAR embedded Workbench  8.50.1
- Keil MDK  5.30
- GCC ARM Embedded  9.2.1
- MCUXpresso  11.2.0

Hardware requirements
=====================
- Two Mini USB cable
- FRDM-KL43Z board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board for downloading
    the program and supply power for the board, connect another USB cable between host PC and USB port
	on the target board.
2.  Download the program to the target board.
3.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.
4.  Open a serial terminal(like putty) to communicate with the board via virtual com.

Running the demo
================
The log below shows the output of this demo in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
hello world.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Terminal will echo back the received characters.
Customization options
=====================

