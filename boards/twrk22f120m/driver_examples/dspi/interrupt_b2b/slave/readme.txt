Overview
========
The dspi_interrupt_b2b example shows how to use DSPI driver in interrupt way:

In this example , we need two boards , one board used as DSPI master and another board used as DSPI slave.
The file 'dspi_interrupt_b2b_slave.c' includes the DSPI slave code.
This example does not use the transactional API in DSPI driver. It's a demonstration that how to use the interrupt in KSDK driver.

1. DSPI master send/received data to/from DSPI slave in interrupt . (DSPI Slave using interrupt to receive/send the data)

Toolchain supported
===================
- IAR embedded Workbench  8.40.2
- Keil MDK  5.29
- GCC ARM Embedded  8.3.1
- MCUXpresso  11.1.0

Hardware requirements
=====================
- Mini USB cable
- Two TWR-K22F120M boards
- Personal Computer
- Two Elevator Tower boards

Board settings
==============
SPI one board:
Transfer data from one instance to anther instance on the other board.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Master Board                            Slave Board
INSTANCE0(SPI0)     CONNECTS TO         INSTANCE1(SPI0)
Pin Name   Board Location     Pin Name  Board Location
SIN            B-44            SOUT        B-45
SOUT           B-45            SIN         B-44
SCK            B-48            SCK         B-48
PCS0           B-46            PCS0        B-46
GND            B-2             GND         B-2
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
DSPI board to board functional interrupt example.

 Slave example is running...

 Slave receive below data in 1st round transfer:
      1  2  3  4  5  6  7  8  9  A  B  C  D  E  F 10
     11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F 20
     21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30
     31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40

 Slave example is running...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Customization options
=====================

