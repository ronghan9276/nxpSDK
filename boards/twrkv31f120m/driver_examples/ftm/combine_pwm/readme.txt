Overview
========
The FTM project is a demonstration program of generating a combined PWM signal by the SDK FTM driver. It sets up the FTM
hardware block to output PWM signals on two TPM channels. The example also shows the complementary mode of operation
and deadtime insertion.
On boards that have 2 LEDs connected to the FTM pins, the user will see a change in LED brightness.
And if the board do not support LEDs to show, the outputs can be observed by oscilloscope.

Toolchain supported
===================
- IAR embedded Workbench  8.40.2
- Keil MDK  5.29
- GCC ARM Embedded  8.3.1
- MCUXpresso  11.1.0

Hardware requirements
=====================
- Mini/micro USB cable
- TWR-KV31F120M board
- Personal Computer

Board settings
==============
Connect oscilloscope to B34

Prepare the Demo
================
1. Connect a USB cable between the PC host and the OpenSDA USB port on the board.
2. Open a serial terminal with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
These instructions are displayed/shown on the terminal window:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FTM example to output combined complementary PWM signals on two channels

You will see a change in LED brightness if an LED is connected to the FTM pin
If no LED is connected to the FTM pin, then probe the signal using an oscilloscope
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 At this example you will see the green led changes its brightness,
 and you can measure and observe another signal by oscilloscope in B34 pin.
Customization options
=====================

