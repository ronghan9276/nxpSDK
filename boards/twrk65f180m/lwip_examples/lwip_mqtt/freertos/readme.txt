Overview
========

The lwip_mqtt demo application demonstrates MQTT client connecting to MQTT broker via unsecured socket.
The application obtains IP and DNS addresses from DHCP and resolves broker's hostname if needed.
Then it connects to the broker and subscribes to the "lwip_topic/#" and "lwip_other/#" topics.
Further it publishes five messages to the "lwip_topic/100" which are also received back
as the board is subscribed to the "lwip_topic/#".
Meanwhile it continues to receive messages published to the subscribed topics from other clients.


Toolchain supported
===================
- GCC ARM Embedded  8.3.1
- MCUXpresso  11.1.0
- IAR embedded Workbench  8.40.2
- Keil MDK  5.29

Hardware requirements
=====================
- Mini/micro USB cable
- RJ45 Network cable
- TWR-K65F180M board
- TWR-SER board
- Personal Computer

Board settings
==============
TWR-SER:
    - RMII mode - J2 3-4 shunt on, J3 2-3 shunt on, J12 shunt on 9,10.
Prepare the Demo
================
1.  Make sure the MQTT broker pointed to by EXAMPLE_MQTT_SERVER_HOST and EXAMPLE_MQTT_SERVER_PORT definitions
    is up and accessible on your network via unsecured socket. A public MQTT testing server can be used
    or you can install a broker locally and modify the definitions mentioned above.
2.  Change MQTT client ID string in the EXAMPLE_MQTT_CLIENT_ID definition to something unique.
    It is especially important when EXAMPLE_MQTT_SERVER_HOST points to a public broker or when you want
    to connect multiple boards to a same broker. Connecting more boards with the same MQTT client ID
    to the same broker may cause previously connected clients with the same ID to be disconnected.
3.  Connect a USB cable between the PC host and the OpenSDA(or USB to Serial) USB port on the target board.
4.  Open a serial terminal on PC for OpenSDA serial(or USB to Serial) device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
5.  Insert the Ethernet Cable into the target board's RJ45 port and connect it to a router (or other DHCP server capable device).
6.  Download the program to the target board.
7.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs, the log would be seen on the terminal like:

Initializing PHY...

************************************************
 MQTT client example
************************************************
Getting IP address from DHCP...

IPv4 Address     : 192.168.0.102
IPv4 Subnet mask : 255.255.255.0
IPv4 Gateway     : 192.168.0.100

Resolving "broker.hivemq.com"...
Connecting to MQTT broker at 18.185.216.165...
MQTT client "lwip_client-123" connected.
Subscribing to the topic "lwip_topic/#" with QoS 0...
Subscribing to the topic "lwip_other/#" with QoS 1...
Subscribed to the topic "lwip_topic/#".
Subscribed to the topic "lwip_other/#".
Going to publish to the topic "lwip_topic/100"...
Published to the topic "lwip_topic/100".
Received 18 bytes from the topic "lwip_topic/100": "message from board"
Going to publish to the topic "lwip_topic/100"...
Published to the topic "lwip_topic/100".
Received 18 bytes from the topic "lwip_topic/100": "message from board"
Going to publish to the topic "lwip_topic/100"...
Published to the topic "lwip_topic/100".
Received 18 bytes from the topic "lwip_topic/100": "message from board"
Going to publish to the topic "lwip_topic/100"...
Published to the topic "lwip_topic/100".
Received 18 bytes from the topic "lwip_topic/100": "message from board"
Going to publish to the topic "lwip_topic/100"...
Published to the topic "lwip_topic/100".
Received 18 bytes from the topic "lwip_topic/100": "message from board"
Customization options
=====================

