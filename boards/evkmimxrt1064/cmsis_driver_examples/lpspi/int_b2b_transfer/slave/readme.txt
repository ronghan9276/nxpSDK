Overview
========
The lpspi_int_b2b_transfer example shows how to use LPSPI CMSIS driver in interrupt way:

In this example , we need two boards, one board used as LPSPI master and another board used as LPSPI slave.
The file 'cmsis_lpspi_int_b2b_transfer_slave.c' includes the LPSPI slave code.
This example uses the transactional API in LPSPI driver.

1. LPSPI master send/received data to/from LPSPI slave in interrupt . 

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
- Personal Computer

Board settings
==============
Weld 0Ω resistor to R278,R279,R280,R281.

LPSPI:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
       MASTER           connect to           SLAVE
Pin Name   Board Location     Pin Name    Board Location
SOUT       J24-4                SIN       J24-5
SIN        J24-5                SOUT      J24-4
SCK        J24-6                SCK       J24-6
PCS0       J24-3                PCS0      J24-3
GND        J24-7                GND       J24-7
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Prepare the Demo
================
1. Connect a mini USB cable between the PC host and the OpenSDA USB port on the board.
2. Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~
LPSPI CMSIS driver board to board interrupt example.

 Slave example is running...
This is LPSPI_SlaveSignalEvent_t
Slave receive data from master has completed!
This is LPSPI_SlaveSignalEvent_t
Slave transmit data to master has completed!

 Slave receive:
      1  2  3  4  5  6  7  8  9  A  B  C  D  E  F 10
     11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F 20
     21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F 30
     31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E 3F 40

 Slave example is running...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
