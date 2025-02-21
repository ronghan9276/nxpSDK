Overview
========

The lwip_ping demo application demonstrates a Ping Demo on the lwIP TCP/IP stack, which uses the ICMP protocol. The
application periodically sends the ICMP echo request to a PC, and processes the PC reply. Type "ping $board_address"
in the PC command window to send an ICMP echo request to the board. The lwIP stack sends the ICMP echo reply back to the
PC.


Toolchain supported
===================
- IAR embedded Workbench  8.40.2
- Keil MDK  5.29
- GCC ARM Embedded  8.3.1
- MCUXpresso  11.1.0

Hardware requirements
=====================
- Mini/micro USB cable
- RJ45 Network cable
- TWR-K64F120M board
- TWR-SER board
- Personal Computer

Board settings
==============
TWR-SER:
    - RMII mode - J2 3-4 shunt on, J3 2-3 shunt on, J12 shunt on 9,10.
Prepare the Demo
================
1.  Connect a USB cable between the PC host and the OpenSDA(or USB to Serial) USB port on the target board.
2.  Open a serial terminal on PC for OpenSDA serial(or USB to Serial) device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Insert the Ethernet Cable into the target board's RJ45 port and connect it to your PC network adapter.
4.  Configure the host PC IP address to 192.168.0.100.
5.  Open a web browser.
6.  Download the program to the target board.
7.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs, the log would be seen on the terminal like:
	Initializing PHY...

	************************************************
	 PING example
	************************************************
	 IPv4 Address     : 192.168.0.102
	 IPv4 Subnet mask : 255.255.255.0
	 IPv4 Gateway     : 192.168.0.100
	************************************************
	ping: send
	192.168.0.100


	ping: recv
	192.168.0.100
	 4 ms

	ping: send
	192.168.0.100


	ping: recv
	192.168.0.100
	 3 ms

	ping: send
	192.168.0.100


	ping: recv
	192.168.0.100
	 3 ms

Customization options
=====================

