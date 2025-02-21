Overview
========

The adc16_polling example shows the simplest way to use ADC16 driver.

In this example, user should indicate a channel to provide a voltage signal (can be controlled by user) as the ADC16's
sample input. When running the project, typing any key into debug console would trigger the conversion. The execution 
would check the conversion completed flag in loop until the flag is asserted, which means the conversion is completed. 
Then read the conversion result value and print it to debug console.

Note, the default setting of initialization for the ADC converter is just an available configuration. User can change
the configuration structure's setting in application to fit the special requirement.

The auto-calibration is not essential but strongly recommended. It can help to adjust the converter itself and improve
the ADC16's performance.
Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-KL81Z board
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
3.  Connect external signal source to J4-12
4.  Download the program to the target board.
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ADC16 polling Example.
ADC16_DoAutoCalibration() Done.
ADC Full Range: XXXX
Press any key to get user channel's ADC value ...
ADC Value: 1985
ADC Value: 1689
ADC Value: 1355
ADC Value: 1625
ADC Value: 1575
ADC Value: 1471
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Toolchain supported
===================
- IAR embedded Workbench  8.32.1
- Keil MDK  5.26
- GCC ARM Embedded  7.3.1
- MCUXpresso 10.3.0

