Overview
========
This is the Wi-Fi Test mode example to demonstrate the test mode support usage.

Before building the example application select Wi-Fi module macro in the app_config.h. (see #define WIFI_<SoC Name>_BOARD_<Module Name>).
For more information about Wi-Fi module connection see:
    readme_modules.txt
    Getting started guide on supported modules configuration:
    https://www.nxp.com/document/guide/getting-started-with-nxp-wi-fi-modules-using-i-mx-rt-platform:GS-WIFI-MODULES-IMXRT-PLATFORM



Toolchain supported
===================
- IAR embedded Workbench  9.30.1
- Keil MDK  5.37
- GCC ARM Embedded  10.3.1
- MCUXpresso  11.6.0

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
1. Add CLI init API in applications main function.
2. Add WLAN CLI init API once WLAN Connection Manager gets initialized correctly.
3. When the demo starts, a welcome message would appear on the terminal, press enter for command prompt:
   Press tab or type help to list out all available CLI commands.

wifi test mode demo
Initialize CLI
Initialize WLAN Driver
MAC Address: 00:13:43:91:8A:3D 
[net] Initialized TCP/IP networking stack
app_cb: WLAN: received event 10
app_cb: WLAN initialized
WLAN Test Mode CLIs are initialized
CLIs Available:

help 
wlan-version 
wlan-mac 
wlan-set-rf-test-mode 
wlan-set-rf-channel <channel>
wlan-get-rf-channel 
wlan-set-rf-band <band>
wlan-get-rf-band 
wlan-set-rf-bandwidth <bandwidth>
wlan-get-rf-bandwidth 
wlan-get-rf-per 
wlan-set-rf-tx-cont-mode <enable_tx> <cw_mode> <payload_pattern> <cs_mode> <act_sub_ch> <tx_rate>
wlan-set-rf-tx-antenna <antenna>
wlan-get-rf-tx-antenna 
wlan-set-rf-rx-antenna <antenna>
wlan-get-rf-rx-antenna 
wlan-set-rf-tx-power <tx_power> <modulation> <path_id>
wlan-set-rf-tx-frame <start> <data_rate> <frame_pattern> <frame_len> <adjust_burst_sifs> <burst_sifs_in_us> <short_preamble> <act_sub_ch> <short_gi> <adv_coding> <tx_bf> <gf_mode> <stbc> <bssid>

# 
# wlan-set-rf-test-mode
RF Test Mode configuration successful

# 
# wlan-set-rf-channel 6
Channel configuration successful

# wlan-get-rf-channel
Configured channel is: 6

# wlan-set-rf-band 0
RF Band configuration successful

# wlan-get-rf-band
Configured RF Band is: 2.4G

# wlan-set-rf-bandwidth 0
Bandwidth configuration successful

# wlan-get-rf-bandwidth
Configured bandwidth is: 20MHz

# 
# wlan-get-and-reset-rf-per
PER is as below: 
  Total Rx Packet Count                    : 3
  Total Rx Multicast/Broadcast Packet Count: 3
  Total Rx Packets with FCS error          : 2

# wlan-set-rf-tx-antenna 1
Tx Antenna configuration successful

# wlan-get-rf-tx-antenna
Configured Tx Antenna is: Main

# wlan-set-rf-rx-antenna 2
Rx Antenna configuration successful

# wlan-get-rf-rx-antenna
Configured Rx Antenna is: Aux

# wlan-set-rf-tx-power 8 1 1
Tx Power configuration successful
  Power         : 8 dBm
  Modulation    : OFDM
  Path ID       : PathB

# wlan-set-rf-tx-frame 1 7 2730 256 0 0 0 0 0 0 0 0 0 ad:ad:23:12:45:57
Tx Frame configuration successful
  Enable                    : enable
  Tx Data Rate              : 7
  Payload Pattern           : 0x00000AAA
  Payload Length            : 0x00000100
  Adjust Burst SIFS3 Gap    : disable
  Burst SIFS in us          : 0 us
  Short Preamble            : disable
  Active SubChannel         : low
  Short GI                  : disable
  Adv Coding                : disable
  Beamforming               : disable
  GreenField Mode           : disable
  STBC                      : disable
  BSSID                     : AD:AD:23:12:45:57 

