Overview
========
Application demonstrating very basic BLE Central role functionality by scanning for other BLE devices and establishing a connection to the first one with a strong enough signal.
Except that this application specifically looks for HPS Server and programs a set of characteristics that configures a Hyper Text Transfer Protocol (HTTP) request, initiate this request, and then read the response once connected.


Toolchain supported
===================
- MCUXpresso  11.6.0
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- GCC ARM Embedded  10.3.1

Hardware requirements
=====================
- Micro USB cable
- evkmimxrt595 board
- Personal Computer
- USB to serial converter
- One of the following modules:
  - AzureWave AW-CM358MA.M2
  - AzureWave AW-CM510MA.M2
  - Embedded Artists 1XK M.2 Module (EAR00385)
  - Embedded Artists 1ZM M.2 Module (EAR00364)

Board settings
==============
Before building the example application select Wi-Fi module macro in the app_config.h. (see #define WIFI_<SoC Name>_BOARD_<Module Name>).
If you want to use AzureWave WIFI_IW416_BOARD_AW_AM510MA, please change the macro to WIFI_IW416_BOARD_AW_AM510MA.
If you want to use AzureWave WIFI_88W8987_BOARD_AW_CM358MA, please change the macro to WIFI_88W8987_BOARD_AW_CM358MA.
If you want to use Embedded Artists Type 1XK module (EAR00385), please change the macro to WIFI_IW416_BOARD_MURATA_1XK_M2.
If you want to use Embedded Artists Type 1ZM module (EAR00364), please change the macro to WIFI_88W8987_BOARD_MURATA_1ZM_M2.


Jumper settings for RT595 (enables external 5V supply):
connect J39 with external power
JP4 1-2
J27 1 - TX of USB to serial converter
J27 2 - RX of USB to serial converter


Debug console UART is configured to use pins of J27, connect the board with PC by USB/UART converter:
- board UART RX (pin 1 on J27) - connect to TX pin on converter
- board UART TX (pin 2 on J27) - connect to RX pin on converter
- board GND (pin 7 on J29) - connect to GND pin on converter

Murata Solution Board settings
Embedded Artists M.2 module resource page: https://www.embeddedartists.com/m2
Embedded Artists 1XK module datasheet: https://www.embeddedartists.com/doc/ds/1XK_M2_Datasheet.pdf
Embedded Artists 1ZM module datasheet: https://www.embeddedartists.com/doc/ds/1ZM_M2_Datasheet.pdf

AzureWave Solution Board settings
The hardware should be reworked according to the Hardware Rework Guide for MIMXRT595-EVK and AW-AM510MA in document Hardware Rework Guide for EdgeFast BT PAL.

The hardware should be reworked according to the Hardware Rework Guide for MIMXRT595-EVK and AW-CM358MA in document Hardware Rework Guide for EdgeFast BT PAL.

Note:
After downloaded binary into qspiflash and boot from qspiflash directly, 
please reset the board by pressing SW3 or power off and on the board to run the application.
For K32W061 controller, it's not supported. Code supporting K32W061 is kept, but isn't verified. 
Prepare the Demo
================

1.  Open example's project and build it.

2.  Connect a USB cable between the PC host and the OpenSDA USB port on the target board.

3.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control

4.  Download the program to the target board.

5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
The demo does not require user interaction. The application will automatically start scanning and will connect to the first advertiser who is advertising the HTTP Proxy Service. If the connection is successful, the application performs service discovery to find the characteristics of the HTTP Proxy Service. If discovery is successful, the application will perform a GET for the URI http://nxp.com by writing the URI and the Control Point characteristics of the HTTP Proxy Service.

The application will display the received response in the console after it gets notified through the HTTP Status Code characteristic. Example output:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Received HTTP Status 500
Reading Headers...
HTTP Headers: HTTPHEADER
Reading Body...
HTTP Body: HTTPBODY
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
