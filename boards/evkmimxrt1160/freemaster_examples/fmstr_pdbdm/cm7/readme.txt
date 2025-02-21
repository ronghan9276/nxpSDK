Hardware requirements
=====================
- Mini/micro USB cable
- Target microcontroller board
- Personal Computer
- FreeMASTER 2.5 or later installed on PC

Multi-core considerations
=========================
There are example applications prepared for both CM4 and CM7 cores of the RT116x target platform. 
The debugger is typically able to load and run the code on any of the cores, but only one core 
is default (CM7) and will run automatically after reset. This means that the flash-based targets 
(and both Debug and Release targets on MCUXpresso IDE) are only usable on the default core.
Also note that the PDBDM demo cannot run simultaneously with the debugger session, which 
makes the RAM-based targets unusable.

SDRAM considerations
====================
Note that the PDBDM buffer must be put in non-cacheable memory. In SDRAM targets, the
_pdbdm buffer is put to non-cacheable section by user code in main.c.

Board settings
==============
No special settings are required. The demo communicates by uploading and
downloading communication frames directly to/from the microcontroller
RAM buffer using the Debug USB port. Standard debugger must not be active 
during the FreeMASTER communication.

Prepare the demo
===============
1.  Connect a USB cable between the host PC and the Debug USB port on the target board.
2.  Use one of the flash-based build targets.
3.  Compile and download the program to the target microcontroller.
4.  Run and resume application execution when debugger stops in the main() function.

Disconnect the debugger
=======================
5.  Terminate the debugger session to release the JTAG interface for FreeMASTER use.
6.  Reset the target board to make sure it runs after detaching the debugger.

Connect with FreeMASTER
=======================
7.  Run FreeMASTER, use the Connection Wizard or open Project Options.
8.  Select communication using the FreeMASTER Packet Driven BDM Communication (PD-BDM) plug-in.
9.  Configure the PD-BDM plug-in:
     - Use the same "underlying" BDM/JTAG interface as used in debugger (typically CMSIS-DAP).
     - Configure this BDM/JTAG interface and test its connection.
     - Specify or search for a RAM address of the "_pdbdm" communication buffer.
     - Test connection and close the configuration dialog.
10.  Start communication, FreeMASTER loads the initial TSA Active Content links in the Welcome page.
11. Click the "FreeMASTER Demonstration Project (embedded in device)" in the Welcome page.
12. The demo is now running, you should be able to watch variable values and graphs.

More information
================
Read more information about FreeMASTER tool at http://www.nxp.com/freemaster.
Feel free to ask questions and report issues at FreeMASTER's 
community page at https://community.nxp.com/community/freemaster
