Overview
========
The SDCARD FatFs FreeRTOS project is a demonstration program that uses the SDK software. It reads/writes
/erases the SD card continuously. The purpose of this example is to show how to use SDCARD driver
with FatFs and freeRTOS in SDK software to access SD card.
Note: The output log of the case is not constant, since difference of card access speed and platform will affect the behavior of card access task.

Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- MCUXpresso  11.6.0
- GCC ARM Embedded  10.3.1

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1160 board
- Personal Computer
- SD card

Board settings
==============
Please make sure R136 is weld for GPIO card detect.

Prepare the Demo
================
1.  Connect a micro USB cable between the PC host and the OpenSDA USB port on the board.
2.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Insert SD card to card slot
4.  Download the program to the target board.
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs successfully, the log would be seen on the terminal like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SDCARD fatfs freertos example.

Card inserted.

Make file system......The time may be long if the card capacity is big.

Create directory......
TASK1: write file successed.
TASK1: file access is blocking.
TASK1: file access is blocking.
TASK2: write file successed.
TASK2: file access is blocking.
TASK2: file access is blocking.
TASK1: finsied.
TASK2: finsied.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
