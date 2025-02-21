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

To experiment with the receive throughput, try to increase the value of TCP_WND in the file lwipopts.h and make sure
that the PBUF_POOL_SIZE is larger than (TCP_WND / TCP_MSS). Increase the PBUF_POOL_SIZE if necessary.
For RTOS applications, DEFAULT_THREAD_PRIO and TCPIP_THREAD_PRIO values can have effect on maximum throughput as well.

The demo is able to connect as a WiFi client to your local WiFi network or act as an AP so that it is possible to connect to it with you computer or smartphone.
The connection parameteres are defined by macros EXT_AP_SSID, EXT_AP_PASSPHRASE
Connection from a smartphone with Android OS was tested with 'Magic iPerf' application available in the Play store: https://play.google.com/store/apps/details?id=com.nextdoordeveloper.miperf.miperf

By default the example connects to network SSID "nxp_wifi_demo" with Open Security.

Before building the example application select Wi-Fi module macro in the app_config.h. (see #define WIFI_<SoC Name>_BOARD_<Module Name>).
For more information about Wi-Fi module connection see:
    readme_modules.txt
    Getting started guide on supported modules configuration:
    https://www.nxp.com/document/guide/getting-started-with-nxp-wi-fi-modules-using-i-mx-rt-platform:GS-WIFI-MODULES-IMXRT-PLATFORM



Toolchain supported
===================
- IAR embedded Workbench  9.10.2
- Keil MDK  5.34
- GCC ARM Embedded  10.2.1
- MCUXpresso  11.5.0

Hardware requirements
=====================
- Micro USB cable
- EVK-MIMXRT595 board
- Personal Computer
- USB/UART converter (3.3V logic level)


Board settings
==============
JP4: 1-2

Debug console UART is configured to use pins of J27, connect the board with PC by USB/UART converter:
- board UART RX (pin 1 on J27) - connect to TX pin on converter
- board UART TX (pin 2 on J27) - connect to RX pin on converter
- board GND (pin 7 on J29) - connect to GND pin on converter

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

    wifi iperf demo
    Initialize WLAN Driver
    MAC Address: C0:E4:34:5A:98:E9
    For Soft AP demonstration
    Start a Soft AP using option "A" in WPA2 security mode from menu
    This also starts DHCP Server with IP 192.168.10.1, NETMASK 255.255.255.0
    For Station demonstration
    Start an External AP with SSID as "nxp_wifi_demo" in Open mode
    Start DHCP Server on External AP
    Station network is configured with Dynamic address assignment
    Application provides IPerf support
    Set IPERF_SERVER_ADDRESS while using as IPerf Client
      A  Start Soft AP
      S  Stop Soft AP
      s  Start Scan for external APs
      c  Connect to External AP (SSID='nxp_wifi_demo')
      D  Disconnect from External AP
      I  Enable IEEE PS on Station
      i  Disable IEEE PS on Station
      d  Enable Deep sleep on Station
      e  Disable Deep sleep on Station
      p  Print All Network info
      P  Print DHCP Server info
      1  TCP server mode (RX only test)
      2  TCP client mode (TX only test)
      3  TCP client dual mode (TX and RX in parallel)
      4  TCP client tradeoff mode (TX and RX sequentially)
      5  UDP server mode (RX only test)
      6  UDP client mode (TX only test)
      7  UDP client dual mode (TX and RX in parallel)
      8  UDP client tradeoff mode (TX and RX sequentially)
      h  Help (print this menu)
      H  Print extended help
    [net] Initialized TCP/IP networking stack
    WLAN Driver Version   : v1.3.r21.p1
    WLAN Firmware Version : w8977o-V2, RF87XX, FP91, 16.91.10.p89, WPA2_CVE_FIX 1, PVE_FIX 1

3. Select the desired mode of operation for WiFi, A - Start Soft AP, c - Connect to External AP (SSID='nxp_mrvl')
4. Start the JPerf application, using the jperf-2.0.0/jperf.bat batch file.
    It can be downloaded here: https://sourceforge.net/projects/iperf/files/jperf/jperf%202.0.0/jperf-2.0.0.zip/download.
    When using Windows, replace the content of the jperf-2.0.0/bin folder with the files from the following zip: https://iperf.fr/download/windows/iperf-2.0.5b-win32.zip.
    When using Linux, iperf binary version 2.0.5 must be installed separately (possibly using package manager) and present on the     system path.
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
        TCP window size: 85.3 KByte (default)
        ------------------------------------------------------------
        [  4] local 192.168.2.101 port 5001 connected with 192.168.2.100 port 49153
        [ ID] Interval       Transfer     Bandwidth
        [  4]  0.0- 1.0 sec   N   KBytes  N    Kbits/sec
        [  4]  1.0- 2.0 sec   N   KBytes  N    Kbits/sec
        [  4]  2.0- 3.0 sec   N   KBytes  N    Kbits/sec
        [  4]  3.0- 4.0 sec   N   KBytes  N    Kbits/sec
        [  4]  4.0- 5.0 sec   N   KBytes  N    Kbits/sec
        [  4]  5.0- 6.0 sec   N   KBytes  N    Kbits/sec
        [  4]  6.0- 7.0 sec   N   KBytes  N    Kbits/sec
        [  4]  7.0- 8.0 sec   N   KBytes  N    Kbits/sec
        [  4]  8.0- 9.0 sec   N   KBytes  N    Kbits/sec
        [  4]  9.0-10.0 sec   N   KBytes  N    Kbits/sec
        [  4]  0.0-10.0 sec   N   KBytes  N    Kbits/sec
        ------------------------------------------------------------
        Client connecting to 192.168.2.100, TCP port 5001
        TCP window size: 85.0 KByte (default)
        ------------------------------------------------------------
        [  4] local 192.168.2.101 port 40954 connected with 192.168.2.100 port 5001
        [  4]  0.0- 1.0 sec   N   KBytes  N    Kbits/sec
        [  4]  1.0- 2.0 sec   N   KBytes  N    Kbits/sec
        [  4]  2.0- 3.0 sec   N   KBytes  N    Kbits/sec
        [  4]  3.0- 4.0 sec   N   KBytes  N    Kbits/sec
        [  4]  4.0- 5.0 sec   N   KBytes  N    Kbits/sec
        [  4]  5.0- 6.0 sec   N   KBytes  N    Kbits/sec
        [  4]  6.0- 7.0 sec   N   KBytes  N    Kbits/sec
        [  4]  7.0- 8.0 sec   N   KBytes  N    Kbits/sec
        [  4]  8.0- 9.0 sec   N   KBytes  N    Kbits/sec
        [  4]  9.0-10.0 sec   N   KBytes  N    Kbits/sec
        [  4]  0.0-10.8 sec   N   KBytes  N    Kbits/sec

10. Also, when the test is finished, the log would be seen on the terminal like below,
	where occurrences of the symbol "N" would be replaced by actual measured values.
    The log will vary depending on the selected mode:
        Enter mode number: 4
        Minimum ever free heap size: 51152
        -------------------------------------------------
         TCP_DONE_CLIENT (TX)
         Local address : 192.168.2.100  Port 49153
         Remote address : 192.168.2.101  Port 5001
         Bytes Transferred N
         Duration (ms) N
         Bandwidth (kbitpsec) N
        -------------------------------------------------
         TCP_DONE_SERVER (RX)
         Local address : 192.168.2.100  Port 5001
         Remote address : 192.168.2.101  Port 40954
         Bytes Transferred N
         Duration (ms) N
         Bandwidth (kbitpsec) N

11. It is also possible to press the SPACE key when the test is running or finished.
    If it is pressed when test is in progress, the running test will be aborted
    and the main menu will appear. If the test is already finished, the main menu
    will appear directly. From the main menu, new test can be run.
