Hardware requirements
===================
- Mini/micro USB cable
- EVKMIMXRT595 board with easy access to MCU input/output through Arduino™ R3 compatible I/O connectors
- FRDM-STBC-AGM01 board
- Personal Computer

Board settings
==============
On FRDM-STBC-AGM01 sensor shield board:
--------------------------------------
For I2C Mode: The examples use I2C1 and Pins 2-3 of Jumpers J6 and J7 on FRDM-STBC-AGM01 should be connected.
For SPI Mode: The examples use SPI0 and the FRDM-STBC-AGM01 needs to be rewired for SPI which requires removal of Resistor R3.

Demo Overview
============
The FXAS21002 FIFO example application demonstrates the use of the FXAS21002 sensor in Buffered (FIFO) Mode.
The example demonstrates configuration of all registers reguired to put the sensor in FIFO Mode and read out samples.

The sensor reads samples and are buffered upto the configured Water Mark Level and then a Flag is set.
The application consistently checks the Flag and when set, reads out all(count=Water Mark Level) samples.

Prepare the Demo
===============
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
===============
When the demo runs successfully, you can see the Samples printed to the terminal.

Note: you must rotate the board to get the samples to change.
