Overview
========
The ntag_i2c_explorer_blink demo application show use of NT3H2111_2211 NTAG I�C plus Connected NFC Tag with I�C Interface Chip. 
This demo is intended to demonstrate basic communication with the device, just reading the state of one register which tells user about NFC field presence.
When the field is detected, the application switches LED on the board between ON and OFF state. Also, if UART communication thru some terminal is made, 
there are some text messages on the terminal. 

Toolchain supported
===================
- IAR embedded Workbench 7.80.4
- Keil MDK 5.21a
- GCC ARM Embedded 2016-5.4-q3
- Kinetis Development Studio IDE 3.2.0
- MCUXpresso0.8

Hardware requirements
=====================
- Mini/Micro USB cable
- FRDM-KW41Z board
- Personal Computer
- NTAG I2C plus antenna board - PCB or flex cable version + wires for connecting the boards OR
  - OR Arduino compatible shield OM29110ARD with NTAG I2C plus board
- NFC-enabled mobile phone, optionally could be used PC USB NFC reader


Board settings
==============
The example is configured to communicate with all NTAG pins
The connection should be set as following:
Board - NTAG
J3-04 - VCC
J3-06 - GND
J2-10 - SCL
J2-09 - SDA
J1-06 - FD

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
When the example runs successfully, you can see blinking LED on the FRDM board when presence of NFC field is detected by chip on the antenna board. 
Field detection is based on reading the state register, not by state of the FD Pin on the NTAG board.

Also, on the terminal window you can see output like below

 NTAG I2C blink example

 The LED is blinking when RF field is detected.

FIELD DETECTED!
FIELD LOST!
FIELD DETECTED!
FIELD LOST!
FIELD DETECTED!   

 
Customization options
=====================

