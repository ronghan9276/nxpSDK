Overview
========
The maestro_demo application demonstrates audio processing on the ARM cortex core
utilizing the Maestro Audio Framework library.

Depending on target platform there are different features of the demo enabled.

    - file decoding and playback
    - EAP effects during file playback

The application is controlled by commands from a shell interface using serial console.

Type "help" to see the command list. Similar description will be displayed on serial console:

    >> help

    "help": List all the registered commands

    "exit": Exit program

    "version": Display component versions

    "file": Perform audio file decode and playback

      USAGE: file [start|stop|pause|update|track|list|info]
        start             Play default (first found) or specified audio track file.
        stop              Stops actual playback.
        pause             Pause actual track or resume if already paused.
        update=<preset>   Apply current EAP parameters without attribute value
                          or switch to preset 1-10
        set=<preset>      Apply current EAP parameters without attribute value
                          or switch to preset 1-10
        list              List audio files on SD card available for playback
        get               Sync actual EAP parameters from library to ATT config structures.
        track=<filename>  Select audio track to play.
        list              List audio files available on mounted SD card.
        info              Prints playback info.
      EXAMPLE: Playback with eap effect: file track <audio_file> eap 3


Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- GCC ARM Embedded  10.3.1
- MCUXpresso  11.6.0

Hardware requirements
=====================
- Micro USB cable
- JTAG/SWD debugger
- EVK-MIMXRT1060 board
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
4.  Connect the headphones into the headphone jack on EVK-MIMXRT1060 board (J12).
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.
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
