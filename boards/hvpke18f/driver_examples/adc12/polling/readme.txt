Overview
========

The adc12_polling example shows the simplest way to use ADC12 driver.

In this example, user should indicate a channel to provide a voltage signal (can be controlled by user) as the ADC12's sample input.
When running the project, typing any key into debug console would trigger the conversion. The execution would check the conversion completed flag in loop until the flag is asserted, which means the conversion is completed. Then read the conversion result value and print it to debug console.

Note, the default setting of initialization for the ADC converter is just an available configuration. User can change the
configuration structure's setting in application to fit the special requirement.

The auto-calibration is not essential but strongly recommended. It can help to adjust the converter itself and improve the
ADC12's performance.


Toolchain supported
===================
- IAR embedded Workbench  8.50.1
- Keil MDK  5.30
- GCC ARM Embedded  9.2.1
- MCUXpresso  11.2.0

Hardware requirements
=====================
- Micro USB cable
- HVP-KE18F board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1. Connect a micro USB cable between the PC host and the OpenSDA USB port on the board.
2. Open a serial terminal on PC for OpenSDA serial device with these settings:
   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, following information can be seen on the OpenSDA terminal:
ADC12 polling Example.
ADC Full Range: 256
Press any key to get user channel's ADC value ...
Customization options
=====================

