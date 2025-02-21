Overview
========

The cmt example shows the simplest way to use CMT driver.

In this example, the CMT is work as Time mode and used to modulation 11 bit numbers of data.
The CMT is configured to generate a 40000hz carrier generator signal through a modulator gate
configured with different mark/space time period to represent bit 1 and bit 0. 
The modulated data rate is 9600.

Note, The end of cycle interrupt provides a means for the user to reload new mark/space values
into the modulator data registers. Modulator data register updates will take effect at the end 
of the current modulation cycle. The CMT internal down-counter and space period register are
updated at the end of every modulation cycle, irrespective of interrupt handling and the state
of the interrupt. so please make sure the IRQ handler process is shorter than the modulation
cycle to ensure the new mark/space counter is prepared before each end of modulation cycle.

Toolchain supported
===================
- IAR embedded Workbench 8.11.3
- Keil MDK 5.23
- GCC ARM Embedded 6-2017-q2
- Kinetis Development Studio IDE 3.2.0
- MCUXpresso10.1.0

Hardware requirements
=====================
- Mini/micro USB cable
- TWR-K24F120M board
- Personal Computer
- Osciloscope

Board settings
==============
Osciloscope needs configuring to easily capture the signal:
    - Trigger should be used to capture the output signal.
    - Set the voltage range to 1 voltage, and adjust the scale to make the smallest time unit to about 400 us.
    - Connect a oscilloscope the pin 1 of the Jumper 19 on TWR-K24F120M.

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
When the example runs successfully, the following message is displayed in the terminal:
~~~~~~~~~~~~~~~~~~~~~~~~
CMT Example Start.

CMT DATA Modulate Finished.

CMT Example End.
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Note

The example modulates 11 bit data is modulated and output as: 10001100011.

The output waveform is captured on the oscilloscope like:
    - data order: 1 -> 0 -> 0 -> 0 -> 1 -> 1 -> 0 -> 0 -> 0 -> 1 -> 1
    - the period of the basic carrier generator signal is 25 microsecond
    - bit 1 is about four normal carrier signal period.
    - bit 0 is about one normal carrier signal period and three space carrier signal period.
Customization options
=====================

