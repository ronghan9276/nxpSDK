Overview
========
The Hello World project is a simple demonstration program that uses the SDK UART drivere in
combination with uC/OS-II. It prints the "Hello World" message ten times to the terminal. The purpose of this
demo is to show how to use the debug console and to provide a simple project for debugging and
further development.

The example application creates one task called hello_task. This task print "Hello world." message
via debug console utility and suspend itself. It also showing systick initialization and its practical use
in message delay.



Toolchain supported
===================
- IAR embedded Workbench 7.70.1
- Keil MDK 5.20
- GCC ARM Embedded 2015-4.9-q3
- Kinetis Development Studio IDE 3.2.0
- Atollic TrueSTUDIO 5.5.2

Hardware requirements
=====================
- Mini/micro USB cable
- TWR-K80F150M board
- Personal Computer

Board settings
==============
This example project does not call for any special hardware configurations.
Although not required, the recommendation is to leave the development board's jumper settings
and configurations in default state when running this example.
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
After the board is flashed the Tera Term will print "Hello world" message on terminal.

Example output:
Hello world.
Hello world.
Hello world.
Hello world.
Hello world.
Hello world.
Hello world.
Hello world.
Hello world.
Hello world.
Customization options
=====================

