Overview
========

The sdramc example shows how to use SEMC controller driver to initialize the external SDRAM chip.



Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- GCC ARM Embedded  10.3.1
- MCUXpresso  11.6.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1020 board
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
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEMC SDRAM Example Start!

 SEMC SDRAM Memory 32 bit Write Start, Start Address 0x80000000, Data Length 4096 !

 SEMC SDRAM Read 32 bit Data Start, Start Address 0x80000000, Data Length 4096 !

 SEMC SDRAM 32 bit Data Write and Read Compare Start!

 SEMC SDRAM 32 bit Data Write and Read Compare Succeed!

 SEMC SDRAM Memory 16 bit Write Start, Start Address 0x80000000, Data Length 4096 !

 SEMC SDRAM Read 16 bit Data Start, Start Address 0x80000000, Data Length 4096 !

 SEMC SDRAM 16 bit Data Write and Read Compare Start!

 SEMC SDRAM 16 bit Data Write and Read Compare Succeed!

 SEMC SDRAM Memory 8 bit Write Start, Start Address 0x80000000, Data Length 4096 !

 SEMC SDRAM Read 8 bit Data Start, Start Address 0x80000000, Data Length 4096 !

 SEMC SDRAM 8 bit Data Write and Read Compare Start!

 SEMC SDRAM 8 bit Data Write and Read Compare Succeed!

 SEMC SDRAM Example End.


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Note:
To debug in qspiflash, following steps are needed:
1. Select the flash target and compile.
2. Set the SW8: 1 off 2 off 3 on 4 off, then power on the board and connect USB cable to J23.
3. Start debugging in IDE.
   - Keil: Click "Download (F8)" to program the image to qspiflash first then clicking "Start/Stop Debug Session (Ctrl+F5)" to start debugging.
