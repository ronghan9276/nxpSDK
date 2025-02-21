Overview
========
This example demonstrates how to perform OTA firmware update of the board using AWS IoT.


Toolchain supported
===================
- IAR embedded Workbench  8.50.9
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT595 board
- Murata 1DX M.2 module
- Murata uSD M.2 Adapter
- Personal Computer

Board settings
==============
Make sure resistors R691~R697 are populated and resistors R611~R620,R660, R661 are removed on EVK-MIMXRT595 board.
Prepare the Demo
================
Prior launching the demo it is recommended to pre-build modified version of the application in .bin format to test the OTA update process.
It is also required to have ota_bootloder programmed to the FLASH memory. Please see readme for the ota_bootloader for details.
For comprehensive guide on seeting up AWS OTA, please see "AWS OTA User Guide.pdf" document.

Before running the demo it is mecessary to configure AWS IoT Console and update some of project files:

1.  Create AWS Account: https://console.aws.amazon.com/console/home

2.  Configure device in the AWS IoT Console base on this guide: https://docs.aws.amazon.com/iot/latest/developerguide/iot-sdk-setup.html

    Make note of example's "Thing name" and "REST API endpoint". These strings need to be set in the "aws_clientcredential.h".

    Example:
        static const char clientcredentialMQTT_BROKER_ENDPOINT[] = "abcdefgh123456.iot.us-west-2.amazonaws.com";
        #define clientcredentialIOT_THING_NAME "MyExample"

    In the next step you will get the "device certificate" and the "primary key". The device certificate and private key needs to be opened in text editor and its content copied into the "aws_clientcredential_keys.h".
    Or you can use the CertificateConfigurator.html (mcu-sdk-2.0\rtos\freertos\tools\certificate_configuration) to generate the "aws_clientcredential_keys.h".

    Example:
        #define keyCLIENT_CERTIFICATE_PEM "Paste client certificate here."

        Needs to be changed to:

        #define keyCLIENT_CERTIFICATE_PEM "-----BEGIN CERTIFICATE-----\n"\
        "MIIDWTCCAkGgAwIBAgIUfmv3zA+JULlMOxmz+upkAzhEkQ0wDQYJKoZIhvcNAQEL\n"\
        .
        .
        .
        "mepuT3lKmD0jZupsQ9vLQOA09rMjVMd0YPmI9ozvvWqLpjVvNTKVhsf/3slM\n"\
        "-----END CERTIFICATE-----\n"

    In the same way update the private key array.

3.  In case your board connects to the Internet using WiFi, it is necessary to configure also WiFi parameters in "aws_clientcredential.h",
    namely "clientcredentialWIFI_SSID" and "clientcredentialWIFI_PASSWORD".
    Otherwise connect board's RJ45 to a network with Internet access.
    Either way the example expects IP configuration to be assigned by DHCP server.

4.  Open example's project and build it.
    Known issue: MDK linker issues warning about unused boot_hdr sections. This does not affect the functionality of the example.

5.  Connect a USB cable between the PC host and the OpenSDA USB port on the target board.

6.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control

7.  Download the program to the target board.

8.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.


Running the demo
================
The OTA demo connects to the cloud service and expects an update package to be deployed.
Plese refer to https://docs.aws.amazon.com/freertos/latest/userguide/ota-manager.html on how to create an update job.
After the OTA agent (that is part the the demo) gets notification about the update it starts downloading the image and storing it into update partition of the FLASH memory.
Once the image is downloaded bootloader is notified about it and reboot in test-mode takes place.
If the updated firmware is able to run without issues the update is made permanent.
