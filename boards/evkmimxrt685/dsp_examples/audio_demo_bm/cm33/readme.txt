Overview
========
The audio baremetal demo demonstrates audio processing using DSP core.
It uses the DMIC working with I2S. One channel Audio data is converted to samples in the DMIC module.
Then, the data is placed into the memory buffer. Last, it is sent to the I2S
buffer and output to the CODEC, where the audio data will be heard from lineout.

Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- GCC ARM Embedded  10.3.1
- MCUXpresso  11.6.0

Hardware requirements
=====================
- Micro USB cable
- JTAG/SWD debugger
- EVK-MIMXRT685 board
- Personal Computer
- Headphones with 3.5 mm stereo jack

Board settings
==============

To enable the example audio using WM8904 codec, connect jumpers as follows:
  JP7-1        <-->        JP7-2
  JP8-1        <-->        JP8-2

Prepare the Demo
================
1.  Connect headphones to Audio HP / Line-Out connector (J4).
2.  Connect a micro USB cable between the PC host and the debug USB port (J5) on the board
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program for CM33 core to the target board.
5.  Launch the debugger in your IDE to begin running the demo.
6.  If building debug configuration, download the program for DSP core to the target board.
7.  If building debug configuration, launch the Xtensa IDE or xt-gdb debugger to
begin running the demo.

NOTE: DSP image can only be debugged using J-Link debugger.  See
'Getting Started with Xplorer for EVK-MIMXRT685.pdf' for more information.

Running the demo
================
The following lines are printed to the serial terminal when the demo program is executed.

    Configure WM8904 codec

    Configure I2S

This example transfers data from DMIC to Codec. Connect headphone/earphone on audio out of the board.
Speak into the DMIC or play audio near the DMIC (U40, U41), and you will hear sound on the left channel of
headphone/earphone.
