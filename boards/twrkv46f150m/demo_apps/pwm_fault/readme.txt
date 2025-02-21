Overview
========
This demo application demonstrates the EflexPWM fault demo.
This application demonstrates the pulse with modulation function of EflexPWM module. It outputs the
PWM to control the intensity of the LED. PWM shut down when a fault signal is detected on the CMP
output. One input of CMP, other input is from internal DAC.

Toolchain supported
===================
- IAR embedded Workbench  8.50.1
- Keil MDK  5.30
- GCC ARM Embedded  9.2.1
- MCUXpresso  11.2.0

Hardware requirements
=====================
- Mini/micro USB cable
- TWR-KV46F150M board
- Personal Computer

Board settings
==============
To use UART on board, make sure that J505-3 connects to J505-4, J506-3 connects to J506-4

Prepare the Demo
================
1.  Connect a mini/micro USB cable between the PC host and the OpenSDA USB port on TWR-KV46F150M board.
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
The log below shows the output of the pwm fault demo in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Welcome to PWM Fault demo
Use oscilloscope to see PWM signal at probe pin: J501 Pin 9
Connect pin J501_13 to high level and ground to see change.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note:
The level state on pin J501_13 determines the output of the PWM signal
- When at low level, the PWM signal will output at pin J501_9.
- When at high level, the PWM signal output will be disabled.
Customization options
=====================

