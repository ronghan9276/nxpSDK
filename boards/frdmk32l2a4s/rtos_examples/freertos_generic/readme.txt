Overview
========

This document explains the freertos_generic example. It is based on code FreeRTOS documentation from
http://www.freertos.org/Hardware-independent-RTOS-example.html. It shows combination of several
tasks with queue, software timer, tick hook and semaphore.

The example application creates three tasks. The prvQueueSendTask periodically sending data to
xQueue queue. The prvQueueReceiveTask is waiting for incoming message and counting number of
received messages. Task prvEventSemaphoreTask is waiting for xEventSemaphore semaphore given from
vApplicationTickHook. Tick hook give semaphore every 500 ms.

Other hook types used for RTOS and resource statistics are also demonstrated in example:
* vApplicationIdleHook
* vApplicationStackOverflowHook
* vApplicationMallocFailedHook



Toolchain supported
===================
- IAR embedded Workbench  8.50.9
- Keil MDK  5.33
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini USB cable
- FRDM-K32L2A4S board
- Personal Computer

Board settings
==============
No special is needed.

Prepare the Demo
================
1. Connect a mini USB cable between the PC host and the OpenSDA USB port on the board.
2. Open a serial terminal on PC for JLink serial device with these settings:
   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running
   the demo.

Running the demo
================
The following message shows in the terminal if the example runs successfully.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Event task is running.
Receive message counter: 1.
Receive message counter: 2.
Receive message counter: 3.
Receive message counter: 4.
Receive message counter: 5.
Receive message counter: 6.
Receive message counter: 7.
Receive message counter: 8.
Receive message counter: 9.
Receive message counter: 10.
Receive message counter: 11.
Receive message counter: 12.
Event task is running.
Receive message counter: 13.
Receive message counter: 14.
...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
