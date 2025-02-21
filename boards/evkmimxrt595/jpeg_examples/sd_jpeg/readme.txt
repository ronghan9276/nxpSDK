Overview
========
The SD JPEG Demo application reads the JPEG pictures from the SD card, decodes
them, and shows them in the LCD panel one by one.
Note: Please make sure the card you are using is FAT32 format.

Toolchain supported
===================
- IAR embedded Workbench  8.50.9
- Keil MDK  5.33
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Micro USB cable
- TFT Proto 5" CAPACITIVE board HW REV 1.01 by Mikroelektronika. (Named as SSD1963 panel in project. Not necessary if use MIPI panel)
- EVK-MIMXRT595
- Personal Computer
- RK055AHD091 MIPI panel (Not necessary if use other panel)
- RM67162 smart MIPI panel (Not necessary if use other panel)
- SD card

Board settings
==============
1. To use SSD1963 panel:
Connect SSD1963 panel to J43.
2. Make sure resistors R691~R697 are populated and resistors R611~R620,R660, R661 are removed.


2. To use MIPI panel:
Connect MIPI panel to J44.

3. Unzip the pics.zip, place the jpg pictures to the SD card.
4. Insert the SDCARD into card slot.

Prepare the Demo
================
The demo use SSD1963 panel by default, to use MIPI RK055AHD091 panel, change the macro
DEMO_PANEL to DEMO_PANEL_RK055AHD091 in display_support.h. To use RM67162 MIPI
smart panel, change the macro DEMO_PANEL to DEMO_PANEL_RM67162 in display_support.h.

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
If this example runs correctly, pictures are shown in the lcd panel one by one.
