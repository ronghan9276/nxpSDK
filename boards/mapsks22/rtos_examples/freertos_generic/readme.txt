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
- Keil MDK 5.24a
- IAR embedded Workbench 8.22.2
- GCC ARM Embedded 7-2017-q4-major
- MCUXpresso10.2.0

Hardware requirements
=====================
- J-Link ARM
- Mini USB cable
- MAPS-KS22F256 board & MAPS-DOCK board
- Personal Computer

Board settings
==============
The hello_world demo is configured to use UART1 with PTE0 and PTE1 pins. To make JLink serial
device work, the jumpers on MAPS-DOCK board should be set as following:
- JP7 on MAPS-Dock: UART0 related jumpers connected
Prepare the Demo
================

Running the demo
================
After the board is flashed the Tera Term will start periodically printing the state of generic example.

Example output:
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
Customization options
=====================

