Overview
========
Application demonstrating how to use the a2dp sink feature.


Toolchain supported
===================
- MCUXpresso  11.6.0
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- GCC ARM Embedded  10.3.1

Hardware requirements
=====================
- Micro USB cable
- evkmimxrt1040 board
- Personal Computer
- One of the following modules:
  - AzureWave AW-CM358MA.M2
  - AzureWave AW-CM510MA.M2
  - Embedded Artists 1XK M.2 Module (EAR00385)
  - Embedded Artists 1ZM M.2 Module (EAR00364)

Board settings
==============
Before building the example application select Wi-Fi module macro in the app_config.h. (see #define WIFI_<SoC Name>_BOARD_<Module Name>).
If you want use the AzureWave WIFI_IW416_BOARD_AW_AM510MA, please change the macro to WIFI_IW416_BOARD_AW_AM510MA.
If you want use the AzureWave WIFI_88W8987_BOARD_AW_CM358MA, please change the macro to WIFI_88W8987_BOARD_AW_CM358MA.
If you want to use Embedded Artists Type 1XK module (EAR00385), please change the macro to WIFI_IW416_BOARD_MURATA_1XK_M2.
If you want to use Embedded Artists Type 1ZM module (EAR00364), please change the macro to WIFI_88W8987_BOARD_MURATA_1ZM_M2.


Jumper settings for RT1040 (enables external 5V supply):
connect J45 with external power
SW6 2-3
J40 1-2 




Murata Solution Board settings
Embedded Artists M.2 module resource page: https://www.embeddedartists.com/m2
Embedded Artists 1XK module datasheet: https://www.embeddedartists.com/doc/ds/1XK_M2_Datasheet.pdf
Embedded Artists 1ZM module datasheet: https://www.embeddedartists.com/doc/ds/1ZM_M2_Datasheet.pdf

AzureWave Solution Board settings
The hardware should be reworked according to the hardware rework guide for evkmimxrt595 and AW-CM510-M.2 in document Hardware Rework Guide for EdgeFast BT PAL.

The hardware should be reworked according to the hardware rework guide for evkmimxrt595 and AW-CM358-M.2 in document Hardware Rework Guide for EdgeFast BT PAL.



Note:
After downloaded binary into qspiflash and boot from qspiflash directly, 
please reset the board by pressing SW7 or power off and on the board to run the application.
Prepare the Demo
================

1.  Open example's project and build it.

2.  Connect a USB cable between the PC host and the OpenSDA USB port on the target board.

3.  Provide 5V voltage for the target board.

4.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control

5.  Download the program to the target board.

6.  Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
The log below shows the output of the example in the terminal window.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
USB Host stack successfully initialized
Bluetooth initialized
BR/EDR set connectable and discoverable done
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Procedures to run
1 Open Android phone, and connect the "a2dp sink" device in bluetooth setting window.
2 Play music in the phone
3 The music can be heared in the audio port of the board.
