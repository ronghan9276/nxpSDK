Overview
========
The ACMP Interrupt project is a simple demonstration program that uses the SDK software. It
compares the selected analog input with ACMP internal DAC output continuously and toggle the LED
when the final comparison result changed. The purpose of this demo is to show how to use the
ACMP driver in SDK software by interrupt way. The ACMP can be configured based on default
configuration returned by the API ACMP_GetDefaultConfig(). The default configuration is: high
speed is not enabled, invert output is not enabled, unfiltered output is not enabled, pin out
is not enabled, offset level is level 0, hysteresis level is level 0.


Toolchain supported
===================
- IAR embedded Workbench  8.50.1
- Keil MDK  5.30
- GCC ARM Embedded  9.2.1
- MCUXpresso  11.2.0

Hardware requirements
=====================
- Micro USB cable
- TWR-KE18F board
- Personal Computer
- Primary Elevator

Board settings
==============
This example project uses ACMP instance 1 to compare the voltage signal input from channel 5(PTD9)
with the voltage signal(half of VDDA) output by ACMP's internal DAC and output different result.
Green LED will turn ON/OFF corresponding to different result. So the voltage signal input from PTD9
should be changed to observe the dynamical LED state.
- Input signal to B50 Elevator

Prepare the Demo
================
1. Connect a micro USB cable between the PC host and the OpenSDA USB port on the board.
2. Open a serial terminal on PC for OpenSDA serial device with these settings:
   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
Before example running, please connect the analog input voltage to stable external voltage generator
to avoid floating voltage and adjust external voltage generator to be higher than reference DAC output
(half of referene voltage) to make the initial comparison result to be 0.

When the demo runs successfully, following information can be seen on the terminal:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The example compares analog input to the reference DAC output(CMP positive port).

The terminal will print CMP's output value when press any key.

Please press any key to get CMP's output value.

The analog input is LOWER than DAC output

The analog input is HIGHER than DAC output
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Customization options
=====================

