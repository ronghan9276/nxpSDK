Overview
========
The dspi_half_duplex_edma_transfer_master example shows how to use driver API to transfer in half-duplex way.  

In this example, one spi instance as master and another spi instance on the other board as slave. Master sends
a piece of data to slave, and receive a piece of data from slave. This example checks if the data received from
slave is correct.
Besides, master will transfer in EDMA way. 

Toolchain supported
===================
- IAR embedded Workbench  8.50.9
- Keil MDK  5.33
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K28FA board
- Personal Computer

Board settings
==============
SPI one board:
Transfer data from one board instance to another board's instance.
SPI0 pins are connected with SPI0 pins of another board
Note: Please separate the connected wires, if not, mixed wires may caused
      electromagnetic interference and data will transfer error.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INSTANCE0(SPI0)     CONNECTS TO         INSTANCE0(SPI0)
Pin Name   Board Location     Pin Name  Board Location
SIN(PTA17)        J27 pin 20          SOUT(PTA16)       J27 pin 19
SOUT(PTA16)       J27 pin 19          SIN(PTA17)        J27 pin 20
SCK(PTA15)        J27 pin 18          SCK(PTA15)        J27 pin 18
PCS0(PTA14)       J27 pin 17          PCS0(PTA14)       J27 pin 17
GND               J2  pin 14          GND               J2  pin 14
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
This is DSPI half-duplex edma transfer example!
SPI master board will transmit data to slave board first, then receive data from slave board.
To make sure the transfer work successfully, please start the slave board first!
Besides, Master will transfer data by EDMA way, and slave will use EDMA way.

Master start to tansfer data...

The received data are:
      0x01  0x02  0x03  0x04  0x05  0x06  0x07  0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F  0x10
      0x11  0x12  0x13  0x14  0x15  0x16  0x17  0x18  0x19  0x1A  0x1B  0x1C  0x1D  0x1E  0x1F  0x20
      0x21  0x22  0x23  0x24  0x25  0x26  0x27  0x28  0x29  0x2A  0x2B  0x2C  0x2D  0x2E  0x2F  0x30
      0x31  0x32  0x33  0x34  0x35  0x36  0x37  0x38  0x39  0x3A  0x3B  0x3C  0x3D  0x3E  0x3F  0x40
DSPI half-duplex EDMA transfer all data matched!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
