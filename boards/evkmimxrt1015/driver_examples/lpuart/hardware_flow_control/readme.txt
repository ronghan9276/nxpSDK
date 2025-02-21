Overview
========
The lpuart_hardware_flow_control Example project is to demonstrate usage of the hardware flow control function.
This example will send data to itself(loopback), and hardware flow control will be enabled in the example.
The CTS(clear-to-send) pin is for transmiter to check if receiver is ready, if the CTS pin is assert, transmiter start
to send data. The RTS(request-to-send) is a pin for receiver to inform the transmiter if receiver is ready to receive
data. So, please connect RTS to CTS pin directly.

Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- GCC ARM Embedded  10.3.1
- MCUXpresso  11.6.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1015 board
- Personal Computer

Board settings
==============
This example will send data to itself(loopback),
and hardware flow control will be enabled in the example.

To make the example work, connections needed to be as follows:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Pin Name  Board Location  connect to  Pin Name  Board Location
  RX        J17-8            			 TX        J18-2  
 RTS_B		J19-5						CTS_B	   j19-4
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is LPUART hardware flow control example on one board.
This example will send data to itself and will use hardware flow control to avoid the overflow.
Please make sure you make the correct line connection. Basically, the connection is: 
      LPUART_TX    --     LPUART_RX    
      LPUART_RTS   --     LPUART_CTS  
Data matched! Transfer successfully.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Note:
To debug in qspiflash, following steps are needed:
1. Select the flash target and compile.
3. Set the SW8: 1 off 2 off 3 on 4 off, then power on the board and connect USB cable to J23.
4. Start debugging in IDE.
   - Keil: Click "Download (F8)" to program the image to qspiflash first then clicking "Start/Stop Debug Session (Ctrl+F5)" to start debugging.
