Overview
========
This example demonstrates usage of eRPC between PC and board using UART transport layer.
Board acts like a server and the PC as client. When client starts, it generates two random
matrixes and sends them to server. Server then performs matrix multiplication and sends
result data back to client. Result matrix is then printed on the PC side.

eRPC documentation
eRPC specific files are stored in: middleware\multicore\erpc
eRPC documentation is stored in: middleware\multicore\erpc\doc
eRPC is open-source project stored on github: https://github.com/EmbeddedRPC/erpc
eRPC documentation can be also found in: http://embeddedrpc.github.io

PC Side Setup (Python)
1. Make sure you have Python installed on your PC
2. Install serial module by executing following command in command line: "python -m pip install pyserial"
3. Install eRPC module to Python by executing setup.py located in: middleware\multicore\erpc\erpc_python - "python setup.py install"

Usage of run_uart.py
usage: run_uart.py [-h] [-c] [-s] [-p PORT] [-b BD]

eRPC Matrix Multiply example

optional arguments:
  -h, --help            show this help message an
  -c, --client          Run client
  -s, --server          Run server
  -p PORT, --port PORT  Serial port
  -b BD, --bd BD        Baud rate (default value is 115200)

Either server or client has to be selected to run

Example:
To run PC side as a client with a board connected as a server to COM3 execute:
"run_uart.py --client --port COM3"

Toolchain supported
===================
- IAR embedded Workbench  8.50.9
- MCUXpresso  11.3.0
- Keil MDK  5.33
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Mini USB cable
- FRDM-K32L2B board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the USB port on the target board.
2.  Download the erpc_server_matrix_multiply_uart example to the target board.
3.  Start server first.
4.  Then start client on PC to begin running the demo.

For detailed instructions, see the appropriate board User's Guide.

Running the demo
================
When the demo runs successfully, the log below shows the output of the Client eRPC Matrix Multiply demo 
in the Phyton Shell window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Matrix #1
  21   33   37   37    9
  23   45   43    0   32
  38   44    8   15   36
  18   18   38   44   16
  22   23    0   38    7

Matrix #2
  11   23   27   45   11
   7   19   23   24    6
  32   26   49   43   16
  22   48   36   34   41
  27   20   32   31   11

eRPC request is sent to the server

Result matrix
2703 4028 4759 4865 2637
2808 3142 4787 4956 1563
2284 3358 4122 4736 1821
2940 4176 4858 4868 2894
1428 2907 2715 3051 2015

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
