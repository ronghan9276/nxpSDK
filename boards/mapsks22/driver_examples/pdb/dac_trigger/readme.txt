Overview
========

The pdb_dac_trigger example shows how to use the PDB to generate a DAC trigger.

Based on the basic counter, to use the DAC trigger, just to enable the DAC trigger's "milestone" and set the user-
defined value for it.
The DAC's "milestone" is called as "interval". Multiple DAC trigger intervals can be included into one PDB counter's cycle.
DAC trigger's counter would reset after the trigger is created and start counting again to the interval value.

In this example, the DAC is configured with hardware buffer enabled in normal work mode. Once it gets the trigger from 
the PDB, the buffer read pointer increases.

Toolchain supported
===================
- Keil MDK 5.24a
- IAR embedded Workbench 8.22.2
- GCC ARM Embedded 7-2017-q4-major
- MCUXpresso10.2.0

Hardware requirements
=====================
- Mini/micro USB cable
- MAPS-KS22F256 board & MAPS-DOCK board
- Personal Computer

Board settings
==============
The pdb_dac_trigger example is configured to use UART1 with PTE0 and PTE1 pins. To make JLink serial
device work, the jumpers on MAPS-DOCK board should be set as following:
- JP7 on MAPS-Dock: UART0 related jumpers connected

Prepare the Demo
================
1. Connect a mini USB cable between the PC host and the USB port (CN14) on MAPS-DOCK board.
2. Open a serial terminal on PC for JLink serial device with these settings:
   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running
   the demo.

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PDB DAC trigger Example.

DAC Buffer Information
          Buffer index max  : 15
          Buffer watermark  : 14
Type any key into terminal to trigger the DAC buffer through PDB ...

DAC Buffer Index  0: ReadPointerTopPositionEvent
DAC Buffer Index  1:
DAC Buffer Index  2:
DAC Buffer Index  3:
DAC Buffer Index  4:
DAC Buffer Index  5:
DAC Buffer Index  6:
DAC Buffer Index  7:
DAC Buffer Index  8:
DAC Buffer Index  9:
DAC Buffer Index 10:
DAC Buffer Index 11:
DAC Buffer Index 12:
DAC Buffer Index 13:
DAC Buffer Index 14: WatermarkEvent
DAC Buffer Index 15: ReadPointerBottomPositionEvent
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Customization options
=====================

