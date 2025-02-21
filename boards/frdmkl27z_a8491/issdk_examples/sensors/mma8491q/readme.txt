Hardware requirements
===================
- Mini/micro USB cable
- FRDMKL27Z board
- FRDM-STBC-A8491 board
- Personal Computer

Demo Overview
============
The MMA8491Q example application demonstrates the MMA8491Q sensor Tilt and Accel data collection.
The example demonstrates configuration of all registers required to read out samples from MMA8491Q.

The application constantly activate sensor and reads out samples.

Prepare the Demo
===============
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
===============
When the demo runs successfully, you can see the Samples printed to the terminal.

Note: you must rotate the board to get the samples to change.
