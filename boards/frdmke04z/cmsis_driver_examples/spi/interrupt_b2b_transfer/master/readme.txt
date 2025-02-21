Overview
========
The spi_interrupt_b2b_transfer example shows how to use spi CMSIS driver in interrupt way:

In this example , we need two boards, one board used as spi master and another board used as spi slave.
The file 'spi_interrupt_b2b_transfer_master.c' includes the spi master code.
This example uses the transactional API in spi driver.

1. spi master send/received data to/from spi slave in interrupt . 

Toolchain supported
===================
- Keil MDK  5.34
- IAR embedded Workbench  9.10.2

Hardware requirements
=====================
- Mini USB cable
- Two FRDM-KE04Z boards
- Personal Computer

Board settings
==============
SPI board to board:
Transfers data through SPI interface. SPI0 pins of the master board are
connected to the SPI0 pins of the slave board.
When using this example, Please make sure the R17 is welded, and this resistance
may be not welded in some board.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MASTER BOARD           CONNECTS TO         SLAVE BOARD
Pin Name   Board Location     Pin Name  Board Location
MISO       J2 pin 8           MISO      J2 pin 8
MOSI       J2 pin 10          MOSI      J2 pin 10
SCK        J2 pin 12          SCK       J2 pin 12
PCS0       J2 pin 6           PCS0      J2 pin 6
GND        J2 pin 14          GND       J2 pin 14
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

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SPI CMSIS interrupt transfer start.
This example use one spi instance as master and another as slave on one board.
Master and slave are both use interrupt way.
Please make sure you make the correct line connection. Basically, the connection is: 
SPI_master -- SPI_slave   
   CLK      --    CLK  
   PCS      --    PCS  
   MOSI     --    MOSI 
   MISO     --    MISO 

 Master transmit:

  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
 10 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F
 20 21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F
 30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F

SPI transfer all data matched!

 Master received:

  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
 10 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F
 20 21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F
 30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
