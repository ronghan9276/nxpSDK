Overview
========
The flexio_i2s_interrupt example shows how to use flexio_i2s driver with interrupt:

In this example, flexio acts as I2S module to record data from codec line and playbacks the recorded data at the same time using interrupt.

Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- GCC ARM Embedded  10.3.1
- MCUXpresso  11.6.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1064 board
- Headphone(OMTP standard)
- Personal Computer

Board settings
==============
- J12, headphone connected
- remove R98,R99,R100,R101 and connect FLEXIO pins to the pad close to U13 as follows:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Pin Name   Board Location     Pin Name    Board Location
RX_DATA    SW5-1              RX_DATA     U13-16
TX_DATA    SW5-2              TX_DATA     U13-14
SYNC       SW5-3              SYNC        U13-13
BCLK       SW5-4              BCLK        U13-12
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================

Note: This demo uses both headphone mic and board main mic(P1) as input source. The headphone mic provides left
channel data, and main mic (P1) provides right channel data. If users found there is noise while do record operation,
most probably it is the headphone standard issue (OMTP and CTIA standard difference). You should use the OMTP
standard headphone. You can disable the left channel by using an headphone without microphone feature.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When the demo runs successfully, the log would be seen on the OpenSDA terminal like as below.

~~~~~~~~~~~~~~~~~~~~~
FLEXIO_I2S interrupt example started!

FLEXIO_I2S interrupt example finished!
~~~~~~~~~~~~~~~~~~~~~
