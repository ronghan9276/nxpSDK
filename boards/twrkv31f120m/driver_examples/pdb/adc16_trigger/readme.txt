Overview
========

The pdb_adc16_trigger example shows how to use the PDB to generate a ADC trigger.

Based on the basic counter, to use the ADC trigger, just to enable the ADC trigger's "milestone" and set the user-
defined value for it.
After the PDB counter is triggered to start, when the counter pass the "milestone", the ADC's Pre-Trigger would be
generated and sent to the ADC module.

In this example, the ADC16 is configured with hardware trigger and conversion complete interrupt enabled.
Once it gets the trigger from the PDB, the conversion goes, then the ISR would be executed.

Toolchain supported
===================
- IAR embedded Workbench  8.40.2
- Keil MDK  5.29
- GCC ARM Embedded  8.3.1
- MCUXpresso  11.1.0

Hardware requirements
=====================
- Mini/Micro USB cable
- TWR-KV31F120M board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board.
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Connect J3 1-2 to use potentiometer
4.  Download the program to the target board.
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
Roll the potentiometer to change the ADC conversion value.
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PDB ADC16 Pre-Trigger Example.
ADC Full Range: XXXX
Type any key into terminal to trigger the PDB and then trigger the ADC's conversion ...

PDB Interrupt Counter: 1
ADC Conversion Interrupt Counter: 1
ADC Conversion Value: 3030

Type any key into terminal to trigger the PDB and then trigger the ADC's conversion ...
...............
...............
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Customization options
=====================

