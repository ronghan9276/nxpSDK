Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-KV10Z board
- FRDM-MC-LVBLDC low-voltage evaluation board 
- Linix 45ZWN24-40 motor (for sensorless three wires cable only) 
- Personal Computer

Boards settings
===============
The MCU board does not require any hardware configuration or jumper settings. 
It contains no jumpers. The low-voltage evaluation board does not require any hardware configuration or jumper settings as well. 

Prepare the Demo
===============
1.  Connect the FRDM-MC-LVBLDC shield on top of the FRDM-KV10Z board. 
2.  Connect the BLDC motor 3-phase wires into the screw terminals on the board. 
3.  Plug in the USB cable from the USB host to the OpenSDA micro USB connector. 
4.  Plug in a 12 V DC power supply to the DC power jack. 

Running the demo
================
Press button SW2 on FRDM-KV10Z board to switch on or off demonstration mode - the motor will rotate. 

More information
================
For more information open the user guide in KSDK install folder\docs\MOTOR_CONTROL\BLDCDEMOUG.pdf or visit the page: http://www.nxp.com/motorcontrol_bldc and find the doccument BLDCAPPACUG - 3-Phase Brushless DC (BLDC) Motor control User Guides.
