Overview
========
The sai_interrupt_transfer example shows how to use sai driver with interrupt:

In this example, one sai instance playbacks the audio data stored in flash/SRAM using interrupt.

Toolchain supported
===================
- GCC ARM Embedded  10.3.1
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- MCUXpresso  11.6.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1064 board
- Personal Computer
- Headphone(OMTP standard)

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
4. Insert the headphones into the headphone jack on EVK-MIMXRT1064 board (J12).
5. Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
note: This demo uses 44.1KHZ sample rate to play a wav music.

When the demo runs successfully, you can hear the tone and the log would be seen on the OpenSDA terminal like:

~~~~~~~~~~~~~~~~~~~
SAI example started!
SAI example finished!
~~~~~~~~~~~~~~~~~~~
