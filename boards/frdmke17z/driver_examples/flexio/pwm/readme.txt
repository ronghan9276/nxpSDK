Overview
========
This demo describes how to use SDK drivers to implement the PWM feature by FLEXIO IP module.
It outputs the PWM singal with fixed frequency defined by "DEMO_FLEXIO_FREQUENCY" in source code
and dynamic duty from 99 to 1 to one of the FLEXIO pin.

Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- GCC ARM Embedded  10.3.1
- MCUXpresso  11.6.0

Hardware requirements
=====================
- Micro USB cable
- FRDM-KE17Z board
- Personal Computer

Board settings
==============
The example requires connection between the flexio output pin and oscilloscope.
The connection should be set as following:
J3-1(FRDM-KE17Z board) -> Anode of oscilloscope.
J3-14(FRDM-KE17Z board) -> Cathode of oscilloscope.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board.
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
When the demo runs successfully, you can use oscilloscope to check the waveform.
And these messages are displayed/shown on the terminal window:
~~~~~~~~~~~~
FLEXIO_PWM demo start.
~~~~~~~~~~~~
