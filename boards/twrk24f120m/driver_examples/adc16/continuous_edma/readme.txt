Overview
========
The ADC16 continuous EDMA demo application demonstrates the usage of the ADC and EDMA peripheral while in a continuous mode. The
ADC16 is first set to continuous mode. In continuous convert configuration, only the initial rising-edge to launch continuous conversions is
observed, and until conversion is aborted, the ADC16 continues to do conversions on the same SCn register that initiated the conversion. 
EDMA request will be asserted during an ADC16 conversion complete event noted when any of the SC1n[COCO] flags is asserted. EDMA will transfer
ADC16 results to memory and if users press any key, demo will average ADC16 results stored in memory and print average on the terminal.  

Toolchain supported
===================
- IAR embedded Workbench 8.11.3
- Keil MDK 5.23
- GCC ARM Embedded 6-2017-q2
- Kinetis Development Studio IDE 3.2.0
- MCUXpresso10.1.0

Hardware requirements
=====================
- Mini/Micro USB cable
- TWR-K24F120M board
- Personal Computer

Board settings
==============
Connect J1 1-2 to use potentiometer

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
Roll the potentiometer to change the ADC value.
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~
ADC16 CONTINUOUS EDMA DEMO
ADC16_DoAutoCalibration() Done.
Press any key to get user channel's ADC value ...
ADC value: 14085
ADC value: 13060
ADC value: 16951
ADC value: 18098
ADC value: 12493
ADC value: 22425
ADC value: 19049
~~~~~~~~~~~~~~~~~~~~~
Customization options
=====================

