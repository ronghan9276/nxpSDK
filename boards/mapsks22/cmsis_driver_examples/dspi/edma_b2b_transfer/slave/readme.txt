Overview
========
The dspi_edma_b2b_transfer example shows how to use DSPI CMSIS driver in edma way:

In this example , we need two boards, one board used as DSPI master and another board used as DSPI slave.
The file 'dspi_edma_b2b_transfer_slave.c' includes the DSPI slave code.

1. DSPI master send/received data to/from DSPI slave in edma . 

Toolchain supported
===================
- Keil MDK 5.24a
- IAR embedded Workbench 8.22.2
- GCC ARM Embedded 7-2017-q4-major
- MCUXpresso10.2.0

Hardware requirements
=====================
- Mini/micro USB cable
- Two MAPS-KS22F256 boards & two MAPS-DOCK boards
- Personal Computer

Board settings
==============
The dspi example is configured to use UART1 with PTE0 and PTE1 pins. To make JLink serial
device work, the jumpers on MAPS-DOCK board should be set as following:
- JP7 on MAPS-Dock: UART0 related jumpers connected

SPI one board:
Transfer data from one instance to anther instance on the other board.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Master Board                            Slave Board
INSTANCE0(SPI0)     CONNECTS TO         INSTANCE1(SPI0)
Pin Name   Board Location     Pin Name  Board Location
SIN        PTD3(Pin-96)        SOUT      PTD2(Pin-95)
SOUT       PTD2(Pin-95)        SIN       PTD3(Pin-96)
SCK        PTC5(Pin-77)        SCK       PTC5(Pin-77)
PCS0       PTC4(Pin-76)        PCS0      PTC4(Pin-76)
GND        CN5-GND             GND       CN5-GND
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
DSPI CMSIS driver board to board edma example.

 Slave example is running...
This is DSPI_SlaveSignalEvent_t
Slave receive data from master has completed!
This is DSPI_SlaveSignalEvent_t
Slave transmit data to master has completed!

 Slave receive:
      1  2  3  4  5  6  7  8  9  A  B  C  D  E  F 10
     11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F 20
     21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30
     31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40

 Slave example is running...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Customization options
=====================

