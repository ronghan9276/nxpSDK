Overview
========
CMSIS-Driver defines generic peripheral driver interfaces for middleware making it reusable across a wide 
range of supported microcontroller devices. The API connects microcontroller peripherals with middleware 
that implements for example communication stacks, file systems, or graphic user interfaces. 
More information and usage method please refer to http://www.keil.com/pack/doc/cmsis/Driver/html/index.html.

The cmsis_uart_interrupt_transfer example shows how to use uart cmsis driver in interrupt way:

In this example, one uart instance connect to PC through uart, the board will
send back all characters that PC send to the board.

Note: The example echo every 8 characters, so input 8 characters every time.

Toolchain supported
===================
- IAR embedded Workbench  8.50.9
- Keil MDK  5.33
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini USB cable
- USB to TTL converter
- FRDM-KL27Z board
- Personal Computer

Board settings
==============
Connect the USB to TTL converter to FRDM-KL27Z board.
FRDM-KL27Z UART pins:
- TX of USB2COM to J1-5
- RX of USB2COM to J1-7
- GND of USB2COM to J2-14

Prepare the Demo
================
1.  Connect a mini USB cable between the PC host and the OpenSDA USB port on the board.
2.  Connect the USB to TTL converter to PC host.
3.  Open a serial terminal on PC for the USB to TTL converter with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Reset the SoC and run the project.

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
USART CMSIS interrupt example
Board receives 8 characters then sends them out
Now please input:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When you input 8 characters, system will echo it by UART and them would be seen on the OpenSDA terminal.

