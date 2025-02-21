Overview
========
The sai_edma_ping_pong_buffer example shows how to use sai driver with EDMA scatter gather feature to implement ping pong buffer case.

In this example, one sai instance playbacks the audio data received from external codec.

Toolchain supported
===================
- IAR embedded Workbench  9.10.2
- Keil MDK  5.34
- GCC ARM Embedded  10.2.1
- MCUXpresso  11.5.0

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K66F board
- Personal Computer
- Headphoney(OMTP standard)
- Line-in line

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
4. Insert the headphones into the headphone jack on FRDM-K66F board (J28). Insert line-in line into J29.
5. Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs, the log would be seen on the OpenSDA terminal like:
~~~~~~~~~~~~~~~~~~~
SAI EDMA ping pong buffer example started!
~~~~~~~~~~~~~~~~~~~
