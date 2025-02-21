Overview
========
The ntag_i2c_explorer_demo demo application show use of NT3H2111_2211 NTAG I?C plus Connected NFC Tag with I?C Interface Chip. 
This demo is intended to demonstrate communication with the device in SRAM pass thru mode and external application.
Demo should use NFC application on the PC or Mobile phone as a counterpart.
Android Mobile app could be found on Play Store by name NTAG I2C Demoboard, PC app could be found on NXP site on the following address:
http://www.nxp.com/products/identification-and-security/nfc-and-reader-ics/connected-tag-solutions/ntag-ic-plus-explorer-kit-with-nfc-reader-development-kit:OM5569-NT322ER?tab=Design_Tools_Tab
 

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
- NFC-enabled mobile phone, optionally could be used PC NFC reader
- wires for connecting the boards

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
5.  Install and start NXP NTAG I2C Demo application on the mobile phone or install drivers for NFC reader for the PC and install and start the PC application

Running the demo
================
When the example runs successfully, you can communicate with NTAG I2C Demo application thru the connected antenna board with connected FRDM board after tapping the devices to each other.  
Use the GUI controls to control behavior of the communication.
Temperature sensor and LCD on the board are not supported in the current release. 

When connected to PC, you can see the some other information from the terminal as below.


 NTAG I2C demo example

 FSL I2C Driver

LED Demo
LED status: 2
LED status: 1
Performing the speed test
Speed test time1: 629 ms, time2: 380 ms
LED Demo
Board Ver.: W41 FW    Ver.: 2.0
Board Ver.: W41 FW    Ver.: 2.0
Button status: 4
Button status: 0
Customization options
=====================

