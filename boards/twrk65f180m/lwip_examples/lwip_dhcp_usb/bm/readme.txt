Overview
========

The lwip_dhcp demo application demonstrates a DHCP and ping demo on the lwIP TCP/IP and USB stack.
The application acts as a DHCP client and prints the status as it is progressing.
Once the interface is being bound to an IP address obtained from DHCP server, address information is printed.
The application will get ip adress www.nxp.com and ping the ip address.


Toolchain supported
===================
- IAR embedded Workbench  8.40.2
- Keil MDK  5.29
- GCC ARM Embedded  8.3.1
- MCUXpresso  11.1.0

Hardware requirements
=====================
- Mini/micro USB cable
- TWR-K65F180M board
- TWR-SER board
- Personal Computer

Board settings
==============
  - The Jumper settings:\n J13 1-2, J9 7-8, Remove all jumpers from J23.
Prepare the Demo
================
1.  Connect a USB cable between the PC host and the OpenSDA(or USB to Serial) USB port on the target board.
2.  Open a serial terminal on PC for OpenSDA serial(or USB to Serial) device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
refer to MCUXpresso SDK USB RNDIS & LWIP User Guide
Customization options
=====================

