Overview
========
This is a small ping demo of the high-performance NetX Duo TCP/IP stack.
And the device registers the number of ping received and write it into
PING.txt which is stored on a RAM disk and can be read  as a USB Mass
Storage Device.


Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- GCC ARM Embedded  10.3.1
- MCUXpresso  11.6.0

Hardware requirements
=====================
- Mini/micro USB cable
- Network cable RJ45 standard
- MIMXRT1160-EVK board
- Personal Computer

Board settings
==============
On MIMXRT1160-EVK REVC board, GPIO_AD_32 uses as ENET_MDC in this example which is muxed with the SD1_CD_B,
please check the R1926 and R136 connected to SD1_CD_B. If they are populated with resistor and SD card is
inserted, this time enet can't access PHY.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board.
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  This example uses 1G port by default. If using the 100M ENET port, set the macro
    BOARD_NETWORK_USE_100M_ENET_PORT in board.h to 1.
4.  Compile the demo.
5.  Download the program to the target board.
6.  Insert an Ethernet cable to the default Ethernet RJ45 port labelled "1G ENET" and connect it to
    an Ethernet switch. Note that if set BOARD_NETWORK_USE_100M_ENET_PORT, the RJ45 port should be
    the one labelled "100M ENET".
7.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo is running, the serial port will output:

Start the ping example...
DHCP In Progress...
IP address: 192.168.2.10
Mask: 255.255.255.0

It shows that the board gets a new IP address, for example, 192.168.2.10. Then, on a PC,
use the ping command to ping the new IP address of the board, for example:

$ ping 192.168.2.10
Pinging 192.168.2.10 with 32 bytes of data:
Reply from 192.168.2.10: bytes=32 time=5ms TTL=127
Reply from 192.168.2.10: bytes=32 time=4ms TTL=127
Reply from 192.168.2.10: bytes=32 time=3ms TTL=127
Reply from 192.168.2.10: bytes=32 time=2ms TTL=127

It shows that the example program running on the board can handle ping packages.

Connect a USB cable between the PC and the USB device port (USB OTG,J9) of the board.
You will observe a disk being enumerated.

Go to the enumerated disk and check the content of the PING.txt file, it will have ping
received count “Ping count is 4”.

Note: USB storage is not designed for a way to manage storage that can be easily sync with
file system, since USB storage access disk sector by sector instead of by files. Thus, any
updates on file will not be visible until the USB cable is removed and then connected back
again. So, if any ping is received while the USB cable was connected will not be visible to
users until user unplug and re-plug the USB cable between the PC and the USB device port.

