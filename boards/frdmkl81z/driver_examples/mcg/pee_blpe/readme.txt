Overview
========
The pee_bple example shows how to use MCG driver to change from PEE mode to BLPE mode:

 1. How to use the mode functions for MCG mode switch.
 2. How to use the frequency functions to get current MCG frequency.
 3. Work flow
    Boot to PEE mode from default reset mode
    Change mode PEE -> PBE -> BLPE
    Change back BLPE -> PBE -> PEE
    Get System clock in PEE mode to blink LED

In this example, because the debug console's clock frequency may change,
so the example running information is not output from debug console. Here the
LED blinks to show that the example finished successfully.
Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-KL81Z board
- Personal Computer

Board settings
==============
No special board settings.

Prepare the Demo
================
1. Connect a USB cable between the PC host and the OpenSDA USB port on the target board.
2. Download the program to the target board.
3. Either press the reset button on your board or launch the debugger in your IDE to begin running the example..

Running the demo
================
When the example runs successfully, the board's LED will blink.

Toolchain supported
===================
- IAR embedded Workbench  8.32.1
- Keil MDK  5.26
- GCC ARM Embedded  7.3.1
- MCUXpresso 10.3.0

