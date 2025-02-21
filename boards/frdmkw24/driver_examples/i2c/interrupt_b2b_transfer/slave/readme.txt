Overview
========
The i2c_interrupt_b2b_transfer_slave example shows how to use i2c driver as slave to do board to board transfer 
with interrupt:

In this example, one i2c instance as slave and another i2c instance on the other board as master. Master sends a 
piece of data to slave, and receive a piece of data from slave. This example checks if the data received from 
slave is correct.

Toolchain supported
===================
- IAR embedded Workbench 7.80.4
- Keil MDK 5.21a
- GCC ARM Embedded 2016-5.4-q3
- Kinetis Development Studio IDE 3.2.0
- MCUXpresso0.8

Hardware requirements
=====================
- Mini USB cable
- FRDM-KW24 board
- Personal Computer

Board settings
==============
I2C one board:
  + Transfer data from MASTER_BOARD to SLAVE_BOARD of I2C interface, I2C pins of MASTER_BOARD are connected with
    I2C pins of SLAVE_BOARD
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MASTER_BOARD        CONNECTS TO          SLAVE_BOARD
Pin Name   Board Location     Pin Name   Board Location
I2C0_SCL       J2-20         I2C0_SCL      J2-20
I2C0_SDA       J2-18         I2C0_SDA      J2-18
GND            J2-14         GND           J2-14
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.
~~~~~~~~~~~~~~
I2C board2board interrupt example -- Slave transfer.

End of I2C example .
~~~~~~~~~~~~~~
Customization options
=====================

