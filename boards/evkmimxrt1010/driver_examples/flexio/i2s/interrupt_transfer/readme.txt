Overview
========
The flexio_i2s_interrupt example shows how to use flexio_i2s driver with interrupt:

In this example, flexio acts as I2S module to record data from codec line and playbacks the recorded data at the same time using interrupt.

Toolchain supported
===================
- GCC ARM Embedded  10.3.1
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- MCUXpresso  11.6.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1010 board
- Headphone(OMTP standard)
- Personal Computer

Board settings
==============
- J11, headphone connected
- remove R85,R87,R88,R280 and connect FLEXIO pins to the pad close to U10 as follows:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Pin Name   Board Location     Pin Name    Board Location
RX_DATA    J54-2              RX_DATA     U10-16
TX_DATA    J26-8              TX_DATA     U10-14
SYNC       J26-6              SYNC        U10-13
BCLK       J26-4              BCLK        U10-12
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

Note:
To debug in qspiflash, following steps are needed:
1. Select the flash target and compile.
2. Set the SW8: 1 off 2 off 3 on 4 off, then power on the board and connect USB cable to J41.
3. Start debugging in IDE.
   - Keil: Click "Download (F8)" to program the image to qspiflash first then clicking "Start/Stop Debug Session (Ctrl+F5)" to start debugging.
