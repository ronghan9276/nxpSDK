Overview
========
The DPU Fetch Layer example shows how to use the DPU driver to display multiple
layers. The DPU unit fetch_layer and fetch_warp support multiple layers, they
are both used in this example.

In this example, the screen is divided to two parts, the left part is for
content stream, fetch_layer is used in this stream. The right part is for
safty stream fetch_warp is used in this stream. In a fetch unit, the sub-layers
could not be alpha blended to another, so when the sub-layers overlay, the layer
with larger sub-layer index is shown.

The DPU unit layer_blend supports alpha blend, this function is enabled in the
content stream. The fetch_layer output is blend to const_frame output.

If this example runs success, rectangles and diamonds will move in the screen.

The DPU path is configured like this:

  **********************                    *********************
  *    Multi-Layer     *                    *   Multi-Layer     *
  *    Frame buffer    *                    *   Frame buffer    *
  *                    *                    *                   *
  **********************                    *********************
          |                                           |
          v                                           v
  +-----------------+   +-----------------+   +-----------------+   +-----------------+
  |                 |   |                 |   |                 |   |                 |
  |   FetchLayer0   |   |  Const Frame 0  |   |   FetchWarp2    |   |  Const Frame 4  |
  |                 |   |                 |   |                 |   |                 |
  +-----------------+   +-----------------+   +-----------------+   +-----------------+
          |                      |                    |                      |
          |                      v                    |                      v
          |             +-----------------+           |             +-----------------+
          |             |                 |           |             |                 |
          +------------>|   LayerBlend 0  |           +------------>|   LayerBlend 2  |
                        |                 |                         |                 |
                        +-----------------+                         +-----------------+
                                 |                                           |
                                 v                                           v
                        +-----------------+                         +-----------------+
                        |                 |                         |                 |
                        |  ExtDst 0 or 1  |                         |  ExtDst 4 or 5  |
                        |                 |                         |                 |
                        +-----------------+                         +-----------------+
                                 |                                           |       Safety stream
                                 |                                           v
        Content Stream           |                                  +-----------------+
                                 |                                  |                 |
                                 +--------------------------------->| FrameGen 0 or 1 |
                                                                    |                 |
                                                                    +-----------------+
                                                                             |
                                                                             v

Toolchain supported
===================
- IAR embedded Workbench  8.32.1
- GCC ARM Embedded  7.3.1

Hardware requirements
=====================
- Micro USB cable
- i.MX8QM MEK CPU Board
- J-Link Debug Probe
- 12V power supply
- MX8_DSI_OLED1 board
- Personal Computer

Another option is using monitor but not OLED panel, in this case MX8_DSI_OLED1 board
is not required, LVDS or MIPI_DSI could be used. To use LVDS, these are required:
- X-IMX-LVDS-HDMI convert board
- Monitor supports HDMI input
To use MIPI_DSI, these are required:
- X-IMX-MIPI-HDMI convert board
- Monitor supports HDMI input

Board settings
==============
No special is needed.

Prepare the Demo
================
1.  Connect 12V power supply and J-Link Debug Probe to the board.
2.  Use X-IMX-VAL-SAS cable to connect J9 and MX8_DSI_OLED1 board.
3.  Connect a USB cable between the host PC and the Debug port on the board (Refer "Getting Started with MCUXpresso SDK for i.MX 8QuadMax.pdf" for debug port information).
4.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
5.  Download the program to the target board (Please refer "Getting Started with MCUXpresso SDK for i.MX 8QuadMax.pdf" for how to run different targets).
6.  Launch the debugger in your IDE to begin running the example.

If use monitor to display through MIPI_DSI, change step 2 to:
    Use X-IMX-VAL-SAS cable to connect J9 and X-IMX-MIPI-HDMI board, and connect
    the X-IMX-MIPI-HDMI convert board with the monitor. Then change
    #define APP_DISPLAY_EXTERNAL_CONVERTOR 0
    to
    #define APP_DISPLAY_EXTERNAL_CONVERTOR 1
    in dpu_example.h.

If use monitor to display through LVDS, change step 2 to:
    Use X-IMX-VAL-SAS cable to connect J7 and X-IMX-LVDS-HDMI board, and connect
    the X-IMX-LVDS-HDMI convert board with the monitor. Then change
    #define APP_DISPLAY_EXTERNAL_CONVERTOR 0
    to
    #define APP_DISPLAY_EXTERNAL_CONVERTOR 1
    and change
    #define DPU_EXAMPLE_DI DPU_DI_MIPI
    to
    #define DPU_EXAMPLE_DI DPU_DI_LVDS
    in dpu_example.h.

Running the demo
================
When the example runs successfully, you can see screen output described in overview.

NOTE: Before load and run the project, press SW1 until D3/D5 are off, then press
SW1 until D3/D5 are on. This perform a whole reset.
Customization options
=====================

