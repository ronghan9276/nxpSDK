Overview
========
This document explains the freertos_tickless example. It shows the CPU enter at sleep mode and then 
it is waked up by expired time delay that using LPTMR module or occur any a hardware interrupt.


Toolchain supported
===================
- IAR embedded Workbench 8.11.1
- Keil MDK 5.23
- GCC ARM Embedded 2016-5.4-q3
- Kinetis Development Studio IDE 3.2.0
- MCUXpresso10.3.1

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-KW36 board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
Connect a serial cable from the debug UART port of the board to the PC. Start Tera Term
(http://ttssh2.osdn.jp) and make a connection to the virtual serial port.

1. Start Tera Term
2. New connection -> Serial
3. Set appropriate COMx port (x is port number) in Port context menu. Number is provided by operation
   system and could be different from computer to computer. Select COM number related to virtual
   serial port. Confirm selected port by OK button.
4. Set following connection parameters in menu Setup->Serial port...
        Baud rate:    115200
        Data:         8
        Parity:       none
        Stop:         1
        Flow control: none
5.  Confirm selected parameters by OK button.


Running the demo
================
After the board is flashed the Tera Term will start periodically printing number tick count when the CPU 
is running.

When the CPU is running and get tick count number, press button on board that suggest message display on 
console screen ("eg:Press SW3 <or SW1,SW2> to wake up the CPU") to wake up CPU then Tera Term 
will printing “CPU waked up by EXT interrupt” message.

Example output:

Tickless Demo example
Press SW3 to wake up the CPU
Tick count :
0
5000
CPU waked up by EXT interrupt
10000
CPU waked up by EXT interrupt
15000
CPU waked up by EXT interrupt
CPU waked up by EXT interrupt
20000
25000
30000

Explanation of the example
The example application will get tick count number after every period time delay vTaskDelay(time)
When this function called the CPU enter to sleep mode a period of time that called by vTaskDelay 
function.

While the CPU is sleeping, if press SW3 button once or several time on board then CPU waked up 
by external interrupt and continuous enter sleep mode after complete interrupt service.
The period of time delay is not change after occur external interrupt.
Customization options
=====================

