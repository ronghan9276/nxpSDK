Overview
========
The flexio_i2c_interrupt example shows how to use flexio i2c master driver in interrupt way:

In this example, a flexio simulated i2c master connect to an I2C slave.

Toolchain supported
===================
- IAR embedded Workbench  8.40.2
- Keil MDK  5.29
- GCC ARM Embedded  8.3.1
- MCUXpresso  11.1.0

Hardware requirements
=====================
- Mini/micro USB cable
- TWR-K80F150M board
- Primary Elevator
- Personal Computer

Board settings
==============
The flexio_i2c_interrupt example is requires connecting the FLEXIO pins with the I2C pins
Insert TWR-K80F150M board into Primary Elevator. The connection should be set as following:
- B69-Elevator, B50-Elevator connected
- B70-Elevator, B51-Elevator connected

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
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

~~~~~~~~~~~~~~~~~~~~~
FlexIO I2C interrupt - I2C interrupt
Master will send data :
0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07
0x08  0x09  0x0A  0x0B  0x0C

Slave received data :
0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07
0x08  0x09  0x0A  0x0B  0x0C
~~~~~~~~~~~~~~~~~~~~~
Customization options
=====================

