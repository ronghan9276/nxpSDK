Overview
========
The FTM project is a simple demonstration program of the SDK FTM driver. It sets up the FTM
hardware block to output a center-aligned PWM signal. The PWM dutycycle is periodically updated.
On boards that have an LED connected to the FTM pins, the user will see a change in LED brightness.

Note
If the FTM instance has only TPM features, please use the TPM driver.
Can be judged by FSL_FEATURE_FTM_IS_TPM_ONLY_INSTANCE(base) macro.

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
- Oscilloscope

Board settings
==============
To use UART on board, make sure that J505-3 connects to J505-4, J506-3 connects to J506-4

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
~~~~~~~~~~~~~~~~~~~~~~~
FTM example to output center-aligned PWM signal
You will see a change in LED brightness if an LED is connected to the FTM pin
If no LED is connected to the FTM pin, then probe the signal using an oscilloscope
~~~~~~~~~~~~~~~~~~~~~~~

You can use oscilloscope to measure FTM signal output (J501-9)
Customization options
=====================

