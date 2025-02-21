Overview
========
The EDMA memory to memory example is a simple demonstration program that uses the SDK software.
It excuates one shot transfer from source buffer to destination buffer using the SDK EDMA drivers.
The purpose of this example is to show how to use the EDMA and to provide a simple example for
debugging and further development.
                                                                     +---------------------------+                          +------------------+
                                                                     | tcd 1 major loop finished | -----------------------> | example complete |
                                                                     +---------------------------+                          +------------------+
                                                                       ^
                                                                       |
                                                                       |
              +---------------------------+  load tcd1               +---------------------------+  major loop not finish   +------------------+
              | tcd 0 major loop finished | -----------------------> |     tcd 1 major loop      | -----------------------> | tcd 1 minor loop |
              +---------------------------+                          +---------------------------+                          +------------------+
                ^                                                      ^                           minor loop finished        |
                |                                                      +------------------------------------------------------+
                |
+-------+     +---------------------------+  major loop not finish   +---------------------------+
| start | --> |     tcd 0 major loop      | -----------------------> |     tcd 0 minor loop      |
+-------+     +---------------------------+                          +---------------------------+
                ^                           minor loop finished        |
                +------------------------------------------------------+

Toolchain supported
===================
- MCUXpresso  11.6.0
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- GCC ARM Embedded  10.3.1

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1064 board
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
When the example runs successfully, you can see the similar information from the terminal as below.

~~~~~~~~~~~~~~~~~~~~~
EDMA scatter gather transfer example begin.



Destination Buffer:

0	0	0	0	0	0	0	0	



EDMA scatter gather transfer example finish.



Destination Buffer:

1	2	3	4	5	6	7	8	
~~~~~~~~~~~~~~~~~~~~~

