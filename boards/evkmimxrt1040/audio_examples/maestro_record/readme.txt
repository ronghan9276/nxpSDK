Overview
========
The maestro_demo application demonstrates audio processing on the ARM cortex core
utilizing the Maestro Audio Framework library.

Depending on target platform there are different features of the demo enabled.

    - loopback from microphone to speaker
    - recording microphone to a file
    - wake words + voice commands recognition

The application is controlled by commands from a shell interface using serial console.

Type "help" to see the command list. Similar description will be displayed on serial console:

    >> help

    "help": List all the registered commands

    "exit": Exit program

    "version": Display component versions

    "record_mic": Record MIC audio and either:
     - perform voice recognition (VIT)
     - playback on WM8904 codec
     - store samples to file.

     USAGE: record_mic [audio|file|vit] 20 [en|cn]
     The number defines length of recording in seconds.
     For voice recognition say supported WakeWord and in 3s frame supported command.
     Please note that this VIT demo is near-field and uses 1 on-board microphone.
     NOTE: this command returns to shell after record finished.

For custom VIT model generation (defining own wake words and voice commands) please use https://vit.nxp.com/


Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- GCC ARM Embedded  10.3.1
- MCUXpresso  11.6.0

Hardware requirements
=====================
- Micro USB cable
- JTAG/SWD debugger
- MIMXRT1040-EVK board
- Personal Computer
- Headphones with 3.5 mm stereo jack

Board settings
==============
Please insert the SDCARD into card slot(J20)

Prepare the Demo
================
1.  Connect a micro USB cable between the PC host and the debug USB port (J41) on the board
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Connect the headphones into the headphone jack on MIMXRT1040-EVK board (J12).
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Note:
There is limited RAM on this platform, which brings following limitations:
 - VIT is not enabled

Running the demo
================
When the example runs successfully, you should see similar output on the serial terminal as below:

**********************************
Maestro audio solutions demo start
**********************************

[APP_SDCARD_Task] start
[APP_Shell_Task] start

SHELL build: Nov  5 2020
Copyright  2020  NXP

>> [APP_SDCARD_Task] SD card drive mounted
