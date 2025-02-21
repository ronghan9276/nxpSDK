Overview
========
The ADC16 continuous EDMA demo application demonstrates the usage of the ADC and EDMA peripheral while in a continuous mode. The
ADC16 is first set to continuous mode. In continuous convert configuration, only the initial rising-edge to launch continuous conversions is
observed, and until conversion is aborted, the ADC16 continues to do conversions on the same SCn register that initiated the conversion. 
EDMA request will be asserted during an ADC16 conversion complete event noted when any of the SC1n[COCO] flags is asserted. EDMA will transfer
ADC16 results to memory and if users press any key, demo will average ADC16 results stored in memory and print average on the terminal.  

Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- GCC ARM Embedded  10.3.1
- MCUXpresso  11.6.0

Hardware requirements
=====================
- Mini/Micro USB cable
- FRDM-KV31F board
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
3.  Connect external signal in J2-1
4.  Download the program to the target board.
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ADC16 CONTINUOUS EDMA DEMO
ADC16_DoAutoCalibration() Done.
ADC Full Range: XXXX
Press any key to get user channel's ADC value ...
ADC value: 23794
ADC value: 24067
ADC value: 24016
ADC value: 21998
ADC value: 21898
ADC value: 20131
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
