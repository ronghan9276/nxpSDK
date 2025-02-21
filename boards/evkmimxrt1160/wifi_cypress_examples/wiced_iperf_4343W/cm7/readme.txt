Overview
========
This is the IPerf example to check your bandwidth using the network performance measurement IPerf application on a PC as a client or a server.
IPv4 is implemented. The UDP implementation is based on lwIP community experimental patches, therefore some issues could be experienced.
UDP sending rate is calculated from the system time, which has a resolution of 1 ms in lwIP. Therefore the actual sending rate could be
a little lower or higher due to sending a calculated (rounded) number of frames each one or more milliseconds. It can also result in higher jitter.
The desired UDP sending rate is determined by the IPERF_UDP_CLIENT_RATE definition. If you want to change the rate without the need to compile
the application with a new value of IPERF_UDP_CLIENT_RATE, you can run the application as a UDP server instead and control the sending rate
by using the tradeoff mode from the PC application and determining the rate there.
For client modes, the address of the remote end where the server PC application is running is determined by the IPERF_SERVER_ADDRESS definition.

Instead of the command line IPerf application, for more convenience, it is recommended to use the JPerf2 graphical tool, which can be downloaded here: https://sourceforge.net/projects/iperf/files/jperf/jperf%202.0.0/jperf-2.0.0.zip/download
The example supports IPerf version 2.0.5. JPerf2, downloaded from the link above, contains version 1.7.0 of iperf.exe for Windows however.
Therefore the iperf.exe version has to be updated when using MS Windows. IPerf 2.0.5b for Windows can be downloaded from the following link:
https://iperf.fr/download/windows/iperf-2.0.5b-win32.zip
The contents of the downloaded archive have to be unpacked into jperf-2.0.0/bin folder, overwriting iperf.exe.
The application has been tested also with IPerf 2.0.10, which can be downloaded here:
https://sourceforge.net/projects/iperf2/files/

To experiment with the receive throughput, try to increase the value of TCP_WND in the file lwipopts.h and make sure
that the PBUF_POOL_SIZE is larger than (TCP_WND / TCP_MSS). Increase the PBUF_POOL_SIZE if necessary.
For RTOS applications, DEFAULT_THREAD_PRIO and TCPIP_THREAD_PRIO values can have effect on maximum throughput as well.

The demo is able to connect as a WiFi client to your local WiFi network or act as an AP so that it is possible to connect to it with you computer or smartphone.
The connection parameteres are defined by macros WIFI_SSID, WIFI_PASSWORD and WIFI_SECURITY.
Connection from a smartphone with Android OS was tested with 'Magic iPerf' application available in the Play store: https://play.google.com/store/apps/details?id=com.nextdoordeveloper.miperf.miperf

By default the example connects to network SSID "nxp-iperf" with "NXP0123456789" key.



Toolchain supported
===================
- IAR embedded Workbench  8.50.9
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.1

Hardware requirements
=====================
- 2x Micro USB cable
- MIMXRT1160-EVK board
- Personal Computer
- Murata 1DX or 1LV M.2 module
- Murata uSD M.2 Adapter
- 1 plug to receptable header cable

Board settings
==============
1.If you want to use the WIFI# LBEE5KL1DX-883 module integrated on the board(U16)
- Connect R366, R367, R369, R370, R371, R372, R404, R408, R787, R788, R789, R790, R791, R792, R823.
- Disconnect R838.
- Do not use M.2 interface(J54) and SD Card Socket(J15).
- Modify sdmmc_config.h, define macro BOARD_SDMMC_SD_CD_TYPE as kSD_DetectCardByHostDATA3.

2.If you want to use the M.2 interface(J54) to connect external wifi module
- Connect R366, R367, R369, R370, R371, R372, R404, R408, R823.
- Disconnect R787, R788, R789, R790, R791, R792, R838.
- Do not use  SD Card Socket(J15).
- Modify sdmmc_config.h, define macro BOARD_SDMMC_SD_CD_TYPE as kSD_DetectCardByHostDATA3.

3.If you want to use the SD Card Socket(J15) to connect external wifi module
- Connect J55.
- Disconnect R787, R788, R789, R790, R791, R792.
- Do not use M.2 interface(J54).
- Modify sdmmc_config.h, define macro BOARD_SDMMC_SD_CD_TYPE as kSD_DetectCardByGpioCD.
Please make sure the R136 is welded for card detection through GPIO.
Note: Since the GPIO CD pin is conflict with the ENET MDC pin on board, so once R136 is welded for sdcard detection, then ENET may not work properly.
It is recommended to provide power directly to Murata uSD M.2 Adapter board using secondary Micro USB cable.
Jumper J38 on the adapter board has to be set up accordingly to utilize external power.
The following pins between the MIMXRT1160-EVK board and Murata uSD M.2 Adapter are connected using the plug to receptable cables:
- MIMXRT1160-EVK board's connector J10, pin 10 to Murata uSD M.2 Adapter's connector J9, pin 3

Prepare the Demo
================
1.  Connect a micro USB cable between the PC host and the CMSIS DAP USB port on the board
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Connect the WiFi module to SD card slot.
4.  Download the program to the target board.
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.


Running the demo
================
1. Adjust the IPERF_SERVER_ADDRESS definition to the IP address where the JPerf PC application will be accessible and rebuild it.
2. When the demo starts, a welcome message and a menu would appear on the terminal:

************************************************
 IPERF example
************************************************

Please select WiFi operation mode:

    a: Access point mode
    c: Client mode

Enter mode:

3. Select the desired mode of operation for WiFi, for AP mode the output would be similar to following:

Initializing WiFi connection...
WLAN MAC Address : 10:98:C3:72:C3:34
WLAN Firmware    : wl0: Mar 12 2019 23:51:54 version 13.10.271.154 (r712270) FWID 01-6b3ca8a7
WLAN CLM         : API: 18.2 Data: 9.10.0 Compiler: 1.36.1 ClmImport: 1.34.1 Creation: 2019-03-12 23:42:29
Successfully initialized WiFi module
Starting Access Point: SSID: nxp-iperf, Chnl: 1
Network ready IP: 192.168.1.1

Please select one of the following modes to run IPERF with:

    1: TCP server mode (RX test)
    2: TCP client mode (TX test)
    3: UDP server mode (RX test)
    4: UDP client mode (TX test)

Enter mode number:

4. Start the JPerf application, using the jperf-2.0.0/jperf.bat batch file.
    It can be downloaded here: https://sourceforge.net/projects/iperf/files/jperf/jperf%202.0.0/jperf-2.0.0.zip/download.
    When using Windows, replace the content of the jperf-2.0.0/bin folder with the files from the following zip: https://iperf.fr/download/windows/iperf-2.0.5b-win32.zip.
    When using Linux, iperf binary version 2.0.5 must be installed separately (possibly using package manager) and present on the system path.
5. To run lwIP IPERF in client mode, select "Server" radio button in JPerf and press the [Run iperf!] button.
6. To run lwIP IPERF in server mode, select "Client radio button and enter the IP address assigned to the board by DHCP
    as IPv4 address to the "server address" parameter in JPerf.
7. Enter the desired mode number into the terminal.
8. If server mode has been selected in the terminal (and client mode in JPerf), press the [Run iperf!] button now.
9. When the test is finished, the output log of JPerf would be seen like below,
	where occurrences of the symbol "N" would be replaced by actual measured values.
    The log will vary depending on the selected mode:
		bin/iperf.exe -s -P 0 -i 1 -p 5001 -f k
        ------------------------------------------------------------
        Server listening on TCP port 5001
        TCP window size: 63.0 KByte (default)
        ------------------------------------------------------------
        [  4] local 192.168.0.100 port 5001 connected with 192.168.0.102 port 49156
        [ ID] Interval       Transfer     Bandwidth
        [  4]  0.0- 1.0 sec  N    KBytes  N     Kbits/sec
        [  4]  1.0- 2.0 sec  N    KBytes  N     Kbits/sec
        [  4]  2.0- 3.0 sec  N    KBytes  N     Kbits/sec
        [  4]  3.0- 4.0 sec  N    KBytes  N     Kbits/sec
        [  4]  4.0- 5.0 sec  N    KBytes  N     Kbits/sec
        [  4]  5.0- 6.0 sec  N    KBytes  N     Kbits/sec
        [  4]  6.0- 7.0 sec  N    KBytes  N     Kbits/sec
        [  4]  7.0- 8.0 sec  N    KBytes  N     Kbits/sec
        [  4]  8.0- 9.0 sec  N    KBytes  N     Kbits/sec
        [  4]  0.0-10.0 sec  N    KBytes  N     Kbits/sec
10. Also, when the test is finished, the log would be seen on the terminal like below,
	where occurrences of the symbol "N" would be replaced by actual measured values.
    The log will vary depending on the selected mode:
        Enter mode number: 2
        Press SPACE to abort the test and return to main menu
        -------------------------------------------------
         TCP_DONE_CLIENT (TX)
         Local address : 192.168.0.102  Port 49156
         Remote address : 192.168.0.100  Port 5001
         Bytes Transferred N
         Duration (ms) N
         Bandwidth (kbitpsec) N

11. It is also possible to press the SPACE key when the test is running or finished.
    If it is pressed when test is in progress, the running test will be aborted
    and the main menu will appear. If the test is already finished, the main menu
    will appear directly. From the main menu, new test can be run.
