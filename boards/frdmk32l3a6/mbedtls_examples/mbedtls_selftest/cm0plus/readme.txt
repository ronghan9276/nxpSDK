Overview
========
The mbdedTLS SelfTest program performs cryptographic algorithm testing and prints results to the
terminal.


Toolchain supported
===================
- Keil MDK  5.33
- IAR embedded Workbench  8.50.9
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K32L3A6 board
- Personal Computer

Board settings
==============
No special settings are required.
If download M0+ core project, need to let MCU boot from M0+ core, please follow below steps:
1. Download blhost.exe from www.nxp.com/kboot.
2. Connect J8 on baord to PC using USB cable.
3. After PC recognize the USB HID device, go to blhost.exe folder, open command line.
4. Run command “blhost.exe -u -- flash-erase-all-unsecure”, it will erase the flash on chip.
5. Run command “blhost.exe -u -- flash-program-once 0x84 4 ffffffbf”, set FOPT3 to boot from M0+ core.

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
When the demo runs successfully, the terminal will display similar information like the following:

  
  MD5 test #1: passed
  MD5 test #2: passed
  MD5 test #3: passed
  MD5 test #4: passed
  MD5 test #5: passed
  MD5 test #6: passed
  MD5 test #7: passed

  SHA-1 test #1: passed
  SHA-1 test #2: passed
  SHA-1 test #3: passed

  SHA-224 test #1: passed
  SHA-224 test #2: passed
  SHA-224 test #3: passed
  SHA-256 test #1: passed
  SHA-256 test #2: passed
  SHA-256 test #3: passed

  SHA-384 test #1: passed
  SHA-384 test #2: passed
  SHA-384 test #3: passed
  SHA-512 test #1: passed
  SHA-512 test #2: passed
  SHA-512 test #3: passed

  DES -ECB- 56 (dec): passed
  DES -ECB- 56 (enc): passed
  DES3-ECB-112 (dec): passed
  DES3-ECB-112 (enc): passed
  DES3-ECB-168 (dec): passed
  DES3-ECB-168 (enc): passed

  DES -CBC- 56 (dec): passed
  DES -CBC- 56 (enc): passed
  DES3-CBC-112 (dec): passed
  DES3-CBC-112 (enc): passed
  DES3-CBC-168 (dec): passed
  DES3-CBC-168 (enc): passed

  AES-ECB-128 (dec): passed
  AES-ECB-128 (enc): passed
  AES-ECB-192 (dec): passed
  AES-ECB-192 (enc): passed
  AES-ECB-256 (dec): passed
  AES-ECB-256 (enc): passed

  AES-CBC-128 (dec): passed
  AES-CBC-128 (enc): passed
  AES-CBC-192 (dec): passed
  AES-CBC-192 (enc): passed
  AES-CBC-256 (dec): passed
  AES-CBC-256 (enc): passed

  AES-CFB128-128 (dec): passed
  AES-CFB128-128 (enc): passed
  AES-CFB128-192 (dec): passed
  AES-CFB128-192 (enc): passed
  AES-CFB128-256 (dec): passed
  AES-CFB128-256 (enc): passed

  AES-CTR-128 (dec): passed
  AES-CTR-128 (enc): passed
  AES-CTR-128 (dec): passed
  AES-CTR-128 (enc): passed
  AES-CTR-128 (dec): passed
  AES-CTR-128 (enc): passed

  AES-GCM-128 #0 (enc): passed
  AES-GCM-128 #0 (dec): passed
  AES-GCM-128 #0 split (enc): passed
  AES-GCM-128 #0 split (dec): passed
  AES-GCM-128 #1 (enc): passed
  AES-GCM-128 #1 (dec): passed
  AES-GCM-128 #1 split (enc): passed
  AES-GCM-128 #1 split (dec): passed
  AES-GCM-128 #2 (enc): passed
  AES-GCM-128 #2 (dec): passed
  AES-GCM-128 #2 split (enc): passed
  AES-GCM-128 #2 split (dec): passed
  AES-GCM-128 #3 (enc): passed
  AES-GCM-128 #3 (dec): passed
  AES-GCM-128 #3 split (enc): passed
  AES-GCM-128 #3 split (dec): passed
  AES-GCM-128 #4 (enc): passed
  AES-GCM-128 #4 (dec): passed
  AES-GCM-128 #4 split (enc): passed
  AES-GCM-128 #4 split (dec): passed
  AES-GCM-128 #5 (enc): passed
  AES-GCM-128 #5 (dec): passed
  AES-GCM-128 #5 split (enc): passed
  AES-GCM-128 #5 split (dec): passed
  AES-GCM-192 #0 (enc): passed
  AES-GCM-192 #0 (dec): passed
  AES-GCM-192 #0 split (enc): passed
  AES-GCM-192 #0 split (dec): passed
  AES-GCM-192 #1 (enc): passed
  AES-GCM-192 #1 (dec): passed
  AES-GCM-192 #1 split (enc): passed
  AES-GCM-192 #1 split (dec): passed
  AES-GCM-192 #2 (enc): passed
  AES-GCM-192 #2 (dec): passed
  AES-GCM-192 #2 split (enc): passed
  AES-GCM-192 #2 split (dec): passed
  AES-GCM-192 #3 (enc): passed
  AES-GCM-192 #3 (dec): passed
  AES-GCM-192 #3 split (enc): passed
  AES-GCM-192 #3 split (dec): passed
  AES-GCM-192 #4 (enc): passed
  AES-GCM-192 #4 (dec): passed
  AES-GCM-192 #4 split (enc): passed
  AES-GCM-192 #4 split (dec): passed
  AES-GCM-192 #5 (enc): passed
  AES-GCM-192 #5 (dec): passed
  AES-GCM-192 #5 split (enc): passed
  AES-GCM-192 #5 split (dec): passed
  AES-GCM-256 #0 (enc): passed
  AES-GCM-256 #0 (dec): passed
  AES-GCM-256 #0 split (enc): passed
  AES-GCM-256 #0 split (dec): passed
  AES-GCM-256 #1 (enc): passed
  AES-GCM-256 #1 (dec): passed
  AES-GCM-256 #1 split (enc): passed
  AES-GCM-256 #1 split (dec): passed
  AES-GCM-256 #2 (enc): passed
  AES-GCM-256 #2 (dec): passed
  AES-GCM-256 #2 split (enc): passed
  AES-GCM-256 #2 split (dec): passed
  AES-GCM-256 #3 (enc): passed
  AES-GCM-256 #3 (dec): passed
  AES-GCM-256 #3 split (enc): passed
  AES-GCM-256 #3 split (dec): passed
  AES-GCM-256 #4 (enc): passed
  AES-GCM-256 #4 (dec): passed
  AES-GCM-256 #4 split (enc): passed
  AES-GCM-256 #4 split (dec): passed
  AES-GCM-256 #5 (enc): passed
  AES-GCM-256 #5 (dec): passed
  AES-GCM-256 #5 split (enc): passed
  AES-GCM-256 #5 split (dec): passed

  CCM-AES #1: passed
  CCM-AES #2: passed
  CCM-AES #3: passed

  Base64 encoding test: passed
  Base64 decoding test: passed

  MPI test #1 (mul_mpi): passed
  MPI test #2 (div_mpi): passed
  MPI test #3 (exp_mod): passed
  MPI test #4 (inv_mod): passed
  MPI test #5 (simple gcd): passed

  RSA parse key #1       : passed
  RSA-1024 key validation: passed
  PKCS#1 encryption      : passed
  PKCS#1 decryption      : passed
  PKCS#1 data sign       : passed
  PKCS#1 sig. verify     : passed

  X.509 certificate load: passed
  X.509 signature verify: passed

  CTR_DRBG (PR = TRUE) : passed
  CTR_DRBG (PR = FALSE): passed

  HMAC_DRBG (PR = True) : passed
  HMAC_DRBG (PR = False) : passed

  ECP test #1 (constant op_count, base point G): passed
  ECP test #2 (constant op_count, other point): passed

  DHM parameter load: passed

  ENTROPY test: passed

  PBKDF2 (SHA1) #0: passed
  PBKDF2 (SHA1) #1: passed
  PBKDF2 (SHA1) #2: passed
  PBKDF2 (SHA1) #3: passed
  PBKDF2 (SHA1) #4: passed
  PBKDF2 (SHA1) #5: passed

  Executed 18 test suites

                           [ All tests PASS ]
