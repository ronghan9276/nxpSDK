Overview
========
The fee_bple example shows how to use MCG driver to change from FEE mode to BLPE mode:

 1. How to use the mode functions for MCG mode switch.
 2. How to use the frequency functions to get current MCG frequency.
 3. Work flow
    Boot to Fee mode from default reset mode
    Change from FEE -> FBE -> BLPE
    Change back BLPE -> FBE -> FEE
    Get System clock in FEE mode to blink LED

In this example, because the debug console's clock frequency may change,
so the example running information is not output from debug console. Here the
LED blinks to show that the example finished successfully.

Toolchain supported
===================
- Keil MDK 5.24a
- IAR embedded Workbench 8.22.2
- GCC ARM Embedded 7-2017-q4-major
- MCUXpresso10.2.0

Hardware requirements
=====================
- Mini/Micro USB cable
- FRDMKL46Z board
- Personal Computer

Board settings
==============
No special board settings.

Prepare the Demo
================
1. Connect a mini/micro USB cable between the PC host and the OpenSDA USB port on FRDMKL46Z board.
2. Download the program to the target board.
3. Either press the reset button on your board or launch the debugger in your IDE to begin running
   the demo. For detailed instructions, see Getting Started with Software Development Kit for
   KL46Z.

Running the demo
================
When the example runs successfully, the board's LED will blink.
Customization options
=====================

