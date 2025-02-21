Overview
========
The Hello World QSPI demo application provides a sanity check for new SDK build environments and board bring up. It
prints the "Hello World" string to the terminal using the SDK UART drivers. The purpose of this demo is to show how to
compile SDK applications to run and boot from QSPI flash or a QSPI alias region.

This example can generate two different demos using a different linker file and a startup file:
Program boot from QSPI region.

Program boot from QSPI alias region (if the chip supports QSPI alias region).


Toolchain supported
===================
- IAR embedded Workbench  8.50.1
- Keil MDK  5.30
- GCC ARM Embedded  9.2.1
- MCUXpresso  11.2.0

Hardware requirements
=====================
- Mini/Micro USB cable
- FRDM-K82F board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
On the FRDMK-82 board, the user can use the USB port to download the demo program through blhost. At step 1, press the
SW2 button and connect to the USB cable to the target hardware.
Running the demo
================
Tool dependencies: Use the blhost and the elftosb tool included in Kinetis Bootloader for the K8x devices. The
package including these tools can be downloaded from www.nxp.com/kboot.

Steps for running this demo:

1. Press and hold the SW2 button (NMI button) while connecting a USB cable between the PC host and the OpenSDA USB port
(or USB port on some boards) on the board. The button should be pressed until the openSDA USB port is connected.

2. Build the demo project and generate the .srec output file. The example requires the use of the SREC file format.
The project can generate the srec file directly. If you want to generate the src output file in another location,
 use the following steps for your given toolchain:

  - IAR: open Option for demo Configuration -> Output Converter -> Choose "Generate additional output".
  Set the format as "Motorola", then rebuild the demo.

  - Keil: open Option for demo project -> User -> Choose "Post build" and write
    "fromelf.exe --m32combined  --output  "$L@L.srec"  "#L" "to the line.

  - KDS: open "Property" for demo project C/C++ Build -> Settings -> Toolchains -> Choose "Create flash image".
    Then C/C++ Build -> Settings -> Cross ARM GUN Create Flash Image -> General -> "Output file format". Choose "Motorola
    S-record" -> "OK".

  - Atollic: open "Property" for demo project C/C++ Build->Settings -> Tool settings -> Other -> Output format ->
    Choose "Convert Output" -> Choose "Format" to "S-record".

  - ARMGCC: Use the command "objcopy -O srec hello_world_qspi.elf hello_world_qspi.srec"
    to generate the srec output file.

  - MCUxpresso: open "Property" for demo project C/C++ Build -> Settings -> Build steps -> Post-build steps, choose "Edit...".
    Change the line # arm-none-eabi-objcopy -v -O binary "${BuildArtifactFileName}" "${BuildArtifactFileBaseName}.bin" to
    arm-none-eabi-objcopy -v -O srec "${BuildArtifactFileName}" "${BuildArtifactFileBaseName}.srec"
    Notice you shall remove the "#" at line begin.

3. Prepare the QSPI config block for BootROM.

    -  Generate qspi_config_block.bin using tools QCBGenerator in Kinetis Bootloader for the K8x devices, the path of
     the tool is in FSL_Kinetis_Bootloader_K80_Tools_1_0_0/FSL_Kinetis_Bootloader_K80_Tools_1_0_0/bin/win. Double click
     QCBGenerator.exe, it will generate a qspi_config_block.bin file.

    - If you are using a different flash chip, the qspi config block should be reconfigured in the source file, located in
     FSL_Kinetis_Bootloader_K80_Tools_1_0_0/demo/QCBGenerator. Users can use GCC/Visual Studio/Code Block to recompile
     a .bin file for the proper QSPI configuration block. The projects for VS and Code Block is provided in the folder.

    - For detailed information, see the documentation Kinetis Bootloader QuadSPI User's Guide.pdf in the Kinetis
    Bootloader tools downloaded.

4. Use elftosb tool to convert the srec image to secure binary (SB) format required by the blhost tool.

    - First a .bd file is needed, so open .bd file in:
     <SDK_Install>/boards/<board>/demo_apps/hello_world_qspi/hello_world_qspi.bd.

    When changing to another demo, change the srec file name in .bd file. Move the qspi_config_block.bin to the same
    folder with hello_world_qspi.bd, or change the path of qspi_config_block.bin in hello_world_qspi.bd file.

    - On the command line, use the command "./elftosb.exe -f kinetis -V -c hello_world_qspi.bd -o hello_world_qspi.sb" to generate an
    sb file.

5. Use blhost to configure the bootloader and download the image.
   - On the command line using blhost, "./blhost.exe -p COMxx -- receive-sb-file hello_world_qspi.sb" ("COMxx" means
   the virtual COM number of the board.)

   Notice:
      - If you are using UART as the communication interface between blhost and the target, do not open a terminal session until
      the flash is complete or the download may fail.

      - Some platforms can only use the USB port for hardware reasons, i.e., the Freescale Freedom FRDM-K82 development board. To use the USB interface, the command
      should be "./blhost.exe -u -- receive-sb-file hello_world_qspi.sb".

      - While use mcuxpresso, while you import this SDK example, please choose UART as output, not semihost. Mcux will have semihost as default output.

6. Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control

7. Press the reset button on your board.

8. You should see the "hello world" string printed to your terminal.
Customization options
=====================

