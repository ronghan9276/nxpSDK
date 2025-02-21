Overview
========
The lpspi_edma_b2b_transfer example shows how to use LPSPI driver in edma way:

In this example , we need two boards, one board used as LPSPI master and another board used as LPSPI slave.
The file 'lpspi_edma_b2b_transfer_slave.c' includes the LPSPI slave code.

1. LPSPI master send/received data to/from LPSPI slave in edma . (LPSPI Slave using edma to receive/send the data)

Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- GCC ARM Embedded  10.3.1
- MCUXpresso  11.6.0

Hardware requirements
=====================
- Mini/micro USB cable
- Two MIMXRT1060-EVKB board
- Personal Computer

Board settings
==============
Remove the resistor R347,R348,R349,R351,R363,R364,R365.
Weld 0Ω resistor to R346,R350,R356,R362.

SPI one board:
Transfer data from one board instance to another board's instance.
SPI0 pins are connected with SPI0 pins of another board
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INSTANCE0(SPI0)     CONNECTS TO         INSTANCE0(SPI0)
Pin Name   Board Location     Pin Name  Board Location
SOUT        J17 pin 4           SIN       J17 pin 5
SIN         J17 pin 5           SOUT      J17 pin 4
SCK         J17 pin 6           SCK       J17 pin 6
PCS0        J17 pin 3           PCS0      J17 pin 3 
GND         J17 pin 7           GND       J17 pin 7
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Prepare the Demo
================
1.  Connect a mini USB cable between the PC host and the OpenSDA USB port on the board.
2.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Reset the SoC and run the project.

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
LPSPI board to board edma example.

 Slave example is running...
This is LPSPI slave edma transfer completed callback.

This is LPSPI slave edma transfer completed callback.


 Slave receive:
      1  2  3  4  5  6  7  8  9  A  B  C  D  E  F 10
     11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F 20
     21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30
     31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Note: Please ensure not to insert any SD CARD device on two boards

