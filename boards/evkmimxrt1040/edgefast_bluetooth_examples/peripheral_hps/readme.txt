Overview
========
Application demonstrating the BLE Peripheral role, except that this application specifically exposes the HTTP Proxy GATT Service.


Toolchain supported
===================
- MCUXpresso  11.6.0
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- GCC ARM Embedded  10.3.1

Hardware requirements
=====================
- Micro USB cable
- evkmimxrt1040 board
- Personal Computer
- One of the following modules:
  - AzureWave AW-AM457-uSD
  - AzureWave AW-CM358-uSD
  - K32W061

Board settings
==============

Jumper settings for AzureWave AW-AM457-uSD Module:
  - J11 2-3: VIO_SD 3.3V (Voltage level of SDIO pins is 3.3V)
  - J2  1-2: 3.3V VIO_uSD (Power Supply from uSD connector)
  - J4  2-3: 3.3V VIO

The hardware should be reworked according to the hardware rework guide for evkmimxrt1040 and AW-AM457-uSD in document Hardware Rework Guide for EdgeFast BT PAL.
The pin connect for UART HCI as the following table,
------------------------------------------------------------------------------------
PIN NAME | AW-AM457-USD |   I.MXRT1040   | PIN NAME OF RT1040 | GPIO NAME OF RT1040
------------------------------------------------------------------------------------
UART_TXD |  J10(pin 4)  |   J16(pin 1)   |    LPUART3_RXD     | GPIO_AD_B1_07
UART_RXD |  J10(pin 2)  |   J16(pin 2)   |    LPUART3_TXD     | GPIO_AD_B1_06
UART_RTS |  J10(pin 6)  |   J33(pin 3)   |    LPUART3_CTS     | GPIO_AD_B1_04
UART_CTS |  J10(pin 8)  |   J33(pin 4)   |    LPUART3_RTS     | GPIO_AD_B1_05
GND      |  J6(pin 7)   |   J32(pin 7)   |    GND             | GND
------------------------------------------------------------------------------------

Jumper settings for AzureWave AW-CM358-uSD Module:
  - J2 1-2: 3.3V VIO_uSD (Power Supply from uSD connector)
  - J4 1-2: VIO 1.8V (Voltage level of SDIO pins is 1.8V)

The hardware should be reworked according to the hardware rework guide for evkmimxrt1040 and AW-CM358-uSD in document Hardware Rework Guide for EdgeFast BT PAL.
The pin connect for UART HCI as the following table,
------------------------------------------------------------------------------------
PIN NAME | AW-CM358-USD |   I.MXRT1040   | PIN NAME OF RT1040 | GPIO NAME OF RT1040
------------------------------------------------------------------------------------
UART_TXD |  J10(pin 4)  |   J16(pin 1)   |    LPUART3_RXD     | GPIO_AD_B1_07
UART_RXD |  J10(pin 2)  |   J16(pin 2)   |    LPUART3_TXD     | GPIO_AD_B1_06
UART_RTS |  J10(pin 6)  |   J33(pin 3)   |    LPUART3_CTS     | GPIO_AD_B1_04
UART_CTS |  J10(pin 8)  |   J33(pin 4)   |    LPUART3_RTS     | GPIO_AD_B1_05
GND      |  J6(pin 7)   |   J32(pin 7)   |    GND             | GND
------------------------------------------------------------------------------------

For K32W061, the readme located in <sdk>/middleware/wireless/ethermind/port/pal/mcux/bluetooth/controller/k32w061 explains how to flash the transceiver image and the hardware rework required.
The pin connect for UART HCI as the following table,
------------------------------------------------------------------------------------
PIN NAME | DK6 (K32W061) |   I.MXRT1040   | PIN NAME OF RT1040 | GPIO NAME OF RT1040
------------------------------------------------------------------------------------
UART_TXD |  PIO(pin 8)   |   J16(pin 1)   |    LPUART3_RXD     | GPIO_AD_B1_07
UART_RXD |  PIO(pin 9)   |   J16(pin 2)   |    LPUART3_TXD     | GPIO_AD_B1_06
UART_RTS |  PIO(pin 6)   |   J33(pin 3)   |    LPUART3_CTS     | GPIO_AD_B1_04
UART_CTS |  PIO(pin 7)   |   J33(pin 4)   |    LPUART3_RTS     | GPIO_AD_B1_05
------------------------------------------------------------------------------------

Note:
After downloaded binary into qspiflash and boot from qspiflash directly, 
please reset the board by pressing SW9 or power off and on the board to run the application.
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
The demo does not require user interaction. The application will automatically start advertising the HTTP Proxy Service and it will accept the first connection request it receives. The application is then ready to process HTTP requests from the peer. The application simulates processing of the HTTP request. It will always return HTTP Status Code 500 and preset values for HTTP Headers and HTTP Body. Example output:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Processing request...
Request processed.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
