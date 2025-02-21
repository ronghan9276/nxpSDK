/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <math.h>

#include "display_support.h"
#include "camera_support.h"
#include "fsl_pxp.h"

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"

#include "timer.h"
#include "image.h"
#include "chgui.h"

// ----------------------------- Bundle API -----------------------------
// Bundle includes.
#include "lenet_mnist.h"
#include "glow_bundle_utils.h"

// Statically allocate memory for constant weights (model weights) and initialize.
GLOW_MEM_ALIGN(LENET_MNIST_MEM_ALIGN)
uint8_t constantWeight[LENET_MNIST_CONSTANT_MEM_SIZE] = {
#include "lenet_mnist.weights.txt"
};

// Statically allocate memory for mutable weights (model input/output data).
GLOW_MEM_ALIGN(LENET_MNIST_MEM_ALIGN)
uint8_t mutableWeight[LENET_MNIST_MUTABLE_MEM_SIZE];

// Statically allocate memory for activations (model intermediate results).
GLOW_MEM_ALIGN(LENET_MNIST_MEM_ALIGN)
uint8_t activations[LENET_MNIST_ACTIVATIONS_MEM_SIZE];

// Bundle input data absolute address.
uint8_t *inputAddr = GLOW_GET_ADDR(mutableWeight, LENET_MNIST_data);

// Bundle output data absolute address.
uint8_t *outputAddr = GLOW_GET_ADDR(mutableWeight, LENET_MNIST_softmax);

// ---------------------------- Application -----------------------------
// Model input size
#define IMAGE_CHANNELS              3
#define MODEL_INPUT_HEIGHT          28
#define MODEL_INPUT_WIDTH           28
#define MODEL_INPUT_SIZE            MODEL_INPUT_HEIGHT * MODEL_INPUT_WIDTH * IMAGE_CHANNELS * sizeof(float)

#define MODEL_COLOR_ORDER           BGR_COLOR_ORDER
#define MODEL_IMAGE_LAYOUT          NCHW_LAYOUT
#define MODEL_IMAGE_SCALE_MODE      SCALE_0TO1

// Number of output classes for the model.
#define MODEL_NUM_OUTPUT_CLASSES  10

// Allocate buffer for input data. This buffer contains the input image
// pre-processed and serialized as text to include here.
/*
uint8_t imageData[MODEL_INPUT_SIZE] = {
#include "input_image.inc"
};
*/

// Class labels.
const char* LABELS[MODEL_NUM_OUTPUT_CLASSES] = {
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9"
};

//Define size of pixels to extract from camera image. This will be scaled down later to fit model input
#define EXTRACT_HEIGHT  140
#define EXTRACT_WIDTH   140

//Calculate start of selection rectangle
int Rec_x = (480-EXTRACT_WIDTH)/2;
int Rec_y = (272-EXTRACT_HEIGHT)/2;

#define DISPLAY_THRESHOLD 40

uint8_t color_threshold = 140;
bool display_threshold_reached=false;

/*******************************************************************************
 * CSI and LCD Definitions
 ******************************************************************************/
#define APP_FRAME_BUFFER_COUNT 4
/* Pixel format RGB565, bytesPerPixel is 2. */
#define APP_BPP 2

#if (FRAME_BUFFER_ALIGN > DEMO_CAMERA_BUFFER_ALIGN)
#define DEMO_FRAME_BUFFER_ALIGN FRAME_BUFFER_ALIGN
#else
#define CAMERA_FRAME_BUFFER_ALIGN DEMO_CAMERA_BUFFER_ALIGN
#endif

/* PXP */
#define ROTATE_DISPLAY kPXP_Rotate180
#define APP_PXP PXP

#define APP_LCD_BUFFER_COUNT 2

#define APP_IMG_WIDTH DEMO_PANEL_WIDTH
#define APP_IMG_HEIGHT DEMO_PANEL_HEIGHT

/* PS input buffer is square. */
#if APP_IMG_WIDTH > APP_IMG_HEIGHT
#define APP_PS_SIZE APP_IMG_WIDTH
#else
#define APP_PS_SIZE APP_IMG_HEIGHT
#endif

#define APP_PS_ULC_X 0U
#define APP_PS_ULC_Y 0U
#define APP_PS_LRC_X (APP_IMG_WIDTH -1U)
#define APP_PS_LRC_Y (APP_IMG_HEIGHT- 1U)

#define APP_RED 0xF100U
#define APP_GREEN 0x07E0U
#define APP_BLUE 0x001FU
#define APP_WHITE 0xFFFFU
#define APP_PXP_PS_FORMAT kPXP_PsPixelFormatRGB565
#define APP_PXP_AS_FORMAT kPXP_AsPixelFormatRGB565
#define APP_PXP_OUT_FORMAT kPXP_OutputPixelFormatRGB565
#define APP_DC_FORMAT kVIDEO_PixelFormatRGB565

/* Tresholds */
#define DETECTION_TRESHOLD 60

#define INPUT_MEAN_SHIFT {125,123,114}
#define INPUT_RIGHT_SHIFT {8,8,8}



/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void APP_BufferSwitchOffCallback(void *param, void *switchOffBuffer);
static void APP_CSIFullBufferReady(camera_receiver_handle_t *handle,
                                  status_t status, void *userData);
static void APP_Rotate(uint32_t input_buffer, uint32_t output_buffer);
static void APP_InitPxp(void);
static void APP_InitCamera(void);
static void APP_InitDisplay(void);
static void APP_CsiRgb565Start(void);
static void APP_CsiRgb565Refresh(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if !defined(__ARMCC_VERSION)
AT_NONCACHEABLE_SECTION_ALIGN(
    static uint16_t s_frameBuffer[APP_FRAME_BUFFER_COUNT][DEMO_PANEL_HEIGHT][DEMO_PANEL_WIDTH],
    CAMERA_FRAME_BUFFER_ALIGN);

AT_NONCACHEABLE_SECTION_ALIGN(
    static uint16_t s_lcdBuf[APP_LCD_BUFFER_COUNT][DEMO_PANEL_HEIGHT][DEMO_PANEL_WIDTH],
    CAMERA_FRAME_BUFFER_ALIGN);

#else
AT_NONCACHEABLE_SECTION_ALIGN_INIT(
    static uint16_t s_frameBuffer[APP_FRAME_BUFFER_COUNT][DEMO_PANEL_HEIGHT][DEMO_PANEL_WIDTH],
    CAMERA_FRAME_BUFFER_ALIGN);

AT_NONCACHEABLE_SECTION_ALIGN_INIT(
    static uint16_t s_lcdBuf[APP_LCD_BUFFER_COUNT][DEMO_PANEL_HEIGHT][DEMO_PANEL_WIDTH],
    CAMERA_FRAME_BUFFER_ALIGN);
#endif

/*
 * When new frame buffer sent to display, it might not be shown immediately.
 * Application could use callback to get new frame shown notification, at the
 * same time, when this flag is set, application could write to the older
 * frame buffer.
 */
static volatile bool s_newFrameShown = false;
static dc_fb_info_t fbInfo;

static volatile bool g_isCamDataExtracted = false;
static uint16_t pExtract[EXTRACT_WIDTH * EXTRACT_HEIGHT];

static uint32_t cameraReceivedFrameAddr;
static uint8_t curLcdBufferIdx = 0;

uint32_t max_idx, display_idx, last_max_idx;
float last_max_val=0;

static uint8_t s_data[EXTRACT_WIDTH * EXTRACT_HEIGHT * 3];
static uint8_t s_monochrome[MODEL_INPUT_WIDTH * MODEL_INPUT_HEIGHT];

/*******************************************************************************
 * Code
 ******************************************************************************/
void GUI_DrawPixel(int color, int x, int y)
{
	unsigned int r=(color & 0xFF0000) >> 16;
	unsigned int g=(color & 0x00FF00) >> 8;
	unsigned int b=(color & 0x0000FF);
	DrawPixel((uint16_t*)s_lcdBuf[curLcdBufferIdx], x, y,  r,g, b);
}

/*!
 * @brief Rotate image PXP.
 * param input_buffer pointer to source image buffer.
 * param output_buffer pointer to output buffer for storing result.
 */
static void APP_Rotate(uint32_t input_buffer, uint32_t output_buffer)
{
  APP_PXP->PS_BUF = input_buffer;
  APP_PXP->OUT_BUF = output_buffer;
  /* Prepare next buffer for LCD. */
  PXP_SetRotateConfig(APP_PXP, kPXP_RotateOutputBuffer, ROTATE_DISPLAY, kPXP_FlipDisable);

  PXP_Start(APP_PXP);

  /* Wait for process complete. */
  while (!(kPXP_CompleteFlag & PXP_GetStatusFlags(APP_PXP)))
  {
  }

  PXP_ClearStatusFlags(APP_PXP, kPXP_CompleteFlag);
}

/*!
 * @brief Initializes PXP.
 */
static void APP_InitPxp(void)
{
  PXP_Init(APP_PXP);

  /* PS configure. */
  const pxp_ps_buffer_config_t psBufferConfig = {
    .pixelFormat = APP_PXP_PS_FORMAT,
    .swapByte    = false,
    .bufferAddr  = 0U,
    .bufferAddrU = 0U,
    .bufferAddrV = 0U,
    .pitchBytes  = APP_PS_SIZE * APP_BPP,
  };

  PXP_SetProcessSurfaceBackGroundColor(APP_PXP, 0U);

  PXP_SetProcessSurfaceBufferConfig(APP_PXP, &psBufferConfig);
  PXP_SetProcessSurfacePosition(APP_PXP, APP_PS_ULC_X, APP_PS_ULC_Y, APP_PS_LRC_X, APP_PS_LRC_Y);

  /* Disable AS. */
  PXP_SetAlphaSurfacePosition(APP_PXP, 0xFFFFU, 0xFFFFU, 0U, 0U);

  pxp_output_buffer_config_t outputBufferConfig;
  /* Output config. */
  outputBufferConfig.pixelFormat    = APP_PXP_OUT_FORMAT;
  outputBufferConfig.interlacedMode = kPXP_OutputProgressive;
  outputBufferConfig.buffer0Addr    = 0U;
  outputBufferConfig.buffer1Addr    = 0U;
  outputBufferConfig.pitchBytes     = APP_IMG_WIDTH * APP_BPP;
  outputBufferConfig.width          = APP_IMG_WIDTH;
  outputBufferConfig.height         = APP_IMG_HEIGHT;

  PXP_SetOutputBufferConfig(APP_PXP, &outputBufferConfig);

  /* Disable CSC1, it is enabled by default. */
  PXP_EnableCsc1(APP_PXP, false);
}

/*!
 * @brief Initializes camera.
 */
static void APP_InitCamera(void)
{
  const camera_config_t cameraConfig = {
    .pixelFormat   = kVIDEO_PixelFormatRGB565,
    .bytesPerPixel = APP_BPP,
    .resolution    = FSL_VIDEO_RESOLUTION(DEMO_CAMERA_WIDTH, DEMO_CAMERA_HEIGHT),
    /* Set the camera buffer stride according to panel, so that if
     * camera resoution is smaller than display, it can still be shown
     * correct in the screen.
     */
    .frameBufferLinePitch_Bytes = DEMO_PANEL_WIDTH * APP_BPP,
    .interface                  = kCAMERA_InterfaceGatedClock,
    .controlFlags               = DEMO_CAMERA_CONTROL_FLAGS,
    .framePerSec                = 30,
  };
  
  memset(s_frameBuffer, 0, sizeof(s_frameBuffer));

  BOARD_InitCameraResource();

  CAMERA_RECEIVER_Init(&cameraReceiver, &cameraConfig, APP_CSIFullBufferReady, NULL);

  if (kStatus_Success != CAMERA_DEVICE_Init(&cameraDevice, &cameraConfig))
  {
    PRINTF("Camera device initialization failed\r\n");
    while (1) {}
  }

  CAMERA_DEVICE_Start(&cameraDevice);

  /* Submit the empty frame buffers to buffer queue. */
  for (uint32_t i = 0; i < APP_FRAME_BUFFER_COUNT; i++)
  {
     CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, (uint32_t)(s_frameBuffer[i]));
  }
}

/*!
 * @brief Initializes LCD.
 */
static void APP_InitDisplay(void)
{
  status_t status;

  BOARD_PrepareDisplayController();

  status = g_dc.ops->init(&g_dc);
  if (kStatus_Success != status)
  {
    PRINTF("Display initialization failed\r\n");
    assert(0);
  }

  g_dc.ops->getLayerDefaultConfig(&g_dc, 0, &fbInfo);
  fbInfo.pixelFormat = kVIDEO_PixelFormatRGB565;
  fbInfo.width       = DEMO_PANEL_WIDTH;
  fbInfo.height      = DEMO_PANEL_HEIGHT;
  fbInfo.strideBytes = DEMO_PANEL_WIDTH * APP_BPP;
  g_dc.ops->setLayerConfig(&g_dc, 0, &fbInfo);

  g_dc.ops->setCallback(&g_dc, 0, APP_BufferSwitchOffCallback, NULL);
}

/*!
 * @brief Start CSI processing.
 */
static void APP_CsiRgb565Start(void)
{
  CAMERA_RECEIVER_Start(&cameraReceiver);

  /* Wait to get the full frame buffer to show. */
  while (kStatus_Success !=
    CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, &cameraReceivedFrameAddr)) {}

  APP_Rotate(cameraReceivedFrameAddr, (uint32_t)s_lcdBuf[curLcdBufferIdx]);

  s_newFrameShown = false;
  g_dc.ops->setFrameBuffer(&g_dc, 0, (void *)s_lcdBuf[curLcdBufferIdx]);

  /* For the DBI interface display, application must wait for the first
     frame buffer sent to the panel. */
  if ((g_dc.ops->getProperty(&g_dc) & kDC_FB_ReserveFrameBuffer) == 0)
  {
    while (s_newFrameShown == false) {}
  }

  s_newFrameShown = true;

  g_dc.ops->enableLayer(&g_dc, 0);
}

/*!
 * @brief Process camera buffer and send it to LCD.
  */
static void APP_CsiRgb565Refresh()
{
  /* Wait to get the full frame buffer to show. */
  while (kStatus_Success !=
    CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, &cameraReceivedFrameAddr)) {}

  curLcdBufferIdx ^= 1U;
  APP_Rotate(cameraReceivedFrameAddr, (uint32_t)s_lcdBuf[curLcdBufferIdx]);

  /* Check if camera buffer is extracted for new inference. */
  if (!g_isCamDataExtracted)
  {
    /* Extract image from camera. */
    ExtractImage(pExtract, Rec_x, Rec_y, EXTRACT_WIDTH, EXTRACT_HEIGHT, (uint16_t *)cameraReceivedFrameAddr);

    /* Draw red rectangle when do extraction. */
    DrawRect((uint16_t*)s_lcdBuf[curLcdBufferIdx],Rec_x, Rec_y, EXTRACT_WIDTH, EXTRACT_HEIGHT, 255, 0, 0);
    g_isCamDataExtracted= true;
  }
  else
  {
    /* Draw white rectangle for aiming. */
    DrawRect((uint16_t*)s_lcdBuf[curLcdBufferIdx], Rec_x, Rec_y, EXTRACT_WIDTH, EXTRACT_HEIGHT, 255, 255, 255);
  }

  /* Print result to screen */
  if(display_threshold_reached)
  {
	  GUI_printf(Rec_x+EXTRACT_WIDTH-8, Rec_y+EXTRACT_HEIGHT+20, LABELS[display_idx]);
  }
  else
  {
	  GUI_printf(Rec_x+EXTRACT_WIDTH-8, Rec_y+EXTRACT_HEIGHT+20, "Unknown");
  }
  s_newFrameShown = false;
  g_dc.ops->setFrameBuffer(&g_dc, 0, (void *)s_lcdBuf[curLcdBufferIdx]);
}

/*!
 * @brief Set new empty buffer for CSI.
 */
static void APP_BufferSwitchOffCallback(void *param, void *switchOffBuffer)
{
  s_newFrameShown = true;
  CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, (uint32_t)cameraReceivedFrameAddr);
}

static void APP_CSIFullBufferReady(camera_receiver_handle_t *handle,
                                   status_t status, void *userData)
{
  if (s_newFrameShown)
  {
    APP_CsiRgb565Refresh();
  }
}



/*!
 * @brief  Run inference. It processed static image if static image is not NULL
 * otherwise camera input is processed.
 *
 * param staticImage pointer to address of static image. Use NULL when static image
 * is not required.
 * param staticImageLen size of static image.
 */
void run_inference(const uint8_t *image_data, const char* labels[], uint8_t scale_mode)
{
	  // Timer variables.
	  uint32_t start_time = 0U;
	  uint32_t stop_time = 0U;
	  uint32_t duration_ms = 0U;

	  // Produce input data for bundle.
	  // Copy the pre-processed image data into the bundle input buffer.s)
	  float *bundleInput =(float *)inputAddr;


	  //Do scaling on image.
      for (int idx = 0; idx < MODEL_INPUT_HEIGHT * MODEL_INPUT_WIDTH; idx++)
      {
        if(scale_mode==SCALE_NEG1TO1)
        {
          bundleInput[idx]=(((((float)image_data[idx])/255.0)*2)-1.0);
        }
        else if(scale_mode==SCALE_0TO1)
        {
          bundleInput[idx]=(((float)image_data[idx])/255.0);
        }
        else if(scale_mode==SCALE_NEG128TO127)
        {
          bundleInput[idx]=(((float)image_data[idx])-128);
        }
        else if(scale_mode==SCALE_0TO255)
        {
           //Do nothing as data already scaled from 0 to 255
           bundleInput[idx]=(float)image_data[idx];
        }
     }


	  // Perform inference and compute inference time.
	  start_time = get_time_in_us();
	  lenet_mnist(constantWeight, mutableWeight, activations);
	  stop_time = get_time_in_us();
	  duration_ms = (stop_time - start_time) / 1000;

	  // Get classification top1 result and confidence.
	  float *out_data = (float*)(outputAddr);
	  float max_val = 0.0;

	  for(int i = 0; i < MODEL_NUM_OUTPUT_CLASSES; i++) {
	    if (out_data[i] > max_val) {
	      max_val = out_data[i];
	      max_idx = i;
	    }
	  }

	  //Update LCD display category if get same result twice in a row.
	  if(max_idx==last_max_idx)
	  {
		  display_idx=max_idx;

		  //If get two low confidence results in a row, display "Unknown" on screen instead of result
		  if((max_val*100)>DISPLAY_THRESHOLD && (last_max_val*100)>DISPLAY_THRESHOLD)
		  {
			  display_threshold_reached=true;
		  }
		  else
		  {
			  display_threshold_reached=false;
		  }
	  }
	  last_max_idx=max_idx;
	  last_max_val=max_val;

	  // Print classification results if Confidence > Threshold.
	  PRINTF("Top1 class = %lu (%s)\r\n", max_idx, LABELS[max_idx]);
	  PRINTF("Confidence = 0.%03u\r\n",(int)(max_val*1000));
	  PRINTF("Inference time = %lu (ms)\r\n", duration_ms);
}


void convert_to_monochrome(uint8_t *color, uint8_t *monochrome)
{
	/* Convert color values to a single monochrome value, using luminosity values for better accuracy */
   //.2125 * Red
   //.7154 * Green
   //.0721 * Blue
   //Algorithm is slightly different based on color order and layout order
    for (int idx = 0; idx < MODEL_INPUT_HEIGHT * MODEL_INPUT_WIDTH; idx++)
    {

    	if(MODEL_COLOR_ORDER==RGB_COLOR_ORDER)
    	{
    		if(MODEL_IMAGE_LAYOUT==NCHW_LAYOUT)
    		{
    		  //RGB NCHW
    		  monochrome[idx]=(int)(.2125*color[idx]+.7154*color[idx+MODEL_INPUT_WIDTH*MODEL_INPUT_HEIGHT]+.0721*color[idx+MODEL_INPUT_WIDTH*MODEL_INPUT_HEIGHT*2]);
    		}
    		else
    		{
    		  //RGB NHWC
      		  monochrome[idx]=(int)(.2125*color[idx*3]+.7154*color[idx*3+1]+.0721*color[idx*3+2]);
    		}
    	}
    	else
    	{
    		if(MODEL_IMAGE_LAYOUT==NCHW_LAYOUT)
    		{
    		  //BGR NCHW
    		  monochrome[idx]=(int)(.0721*color[idx]+.7154*color[idx+MODEL_INPUT_WIDTH*MODEL_INPUT_HEIGHT]+.2125*color[idx+MODEL_INPUT_WIDTH*MODEL_INPUT_HEIGHT*2]);
    		}
    		else
    		{
    		  //BGR NCHW
      		  monochrome[idx]=(int)(.0721*color[idx*3]+.7154*color[idx*3+1]+.2125*color[idx*3+2]);
    		}
    	}
    }

    /* LeNet MNIST model expects white numbers on black background. Because camera is looking at black numbers on white background, flip the contrast */
    for (int idx = 0; idx < MODEL_INPUT_HEIGHT * MODEL_INPUT_WIDTH; idx++)
    {
    	monochrome[idx]=((monochrome[idx]-255)*-1);

    	//To also help with accuracy, make pixels max/min values
    	if(monochrome[idx]<color_threshold)
    	{
    		monochrome[idx]=0;
    	}
    	else
    	{
    		monochrome[idx]=255;
    	}

    	//Makes number thicker by adding extra width if value to the left was zero for better accuracy
    	if((monochrome[idx-1]==0) && (monochrome[idx]==255))
    	{
    		monochrome[idx-1]=255;
    	}
    }
}

/* Calibrate for white level if needed */
void calibrate(uint8_t *monochrome)
{
    uint32_t average=0;
    for (int idx = 0; idx < MODEL_INPUT_HEIGHT * MODEL_INPUT_WIDTH; idx++)
    {
    	average+=monochrome[idx];
    }
    average=average/(MODEL_INPUT_WIDTH*MODEL_INPUT_HEIGHT);
    color_threshold=average+20;
    PRINTF("New color threshold is %d\r\n",color_threshold);
}

/*!
 * @brief Main function
 */
int main(void)
{
  /* Init board hardware. */
  BOARD_ConfigMPU();
  BOARD_InitPins();
  BOARD_InitDEBUG_UARTPins();
  BOARD_InitSDRAMPins();
  BOARD_EarlyPrepareCamera();
  BOARD_InitCSIPins();
  BOARD_InitLCDPins();
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();

  NVIC_SetPriorityGrouping(3);
  init_timer();

  PRINTF("LeNet MNIST Camera Demo with Glow\r\n");

  APP_InitCamera();
  APP_InitDisplay();
  APP_InitPxp();
  /* Start CSI transfer */
  APP_CsiRgb565Start();



  Image prev_scale = {
    .width = EXTRACT_WIDTH,
    .height = EXTRACT_HEIGHT,
    .channels = IMAGE_CHANNELS,
  };

  Image *after_scale;

  uint8_t wanted_width = MODEL_INPUT_WIDTH;
  uint8_t wanted_height = MODEL_INPUT_HEIGHT;
  double dx = 1.0 * wanted_width / EXTRACT_WIDTH;
  double dy = 1.0 * wanted_height / EXTRACT_HEIGHT;

  after_scale = ImCreate(&prev_scale, dx, dy);

  PRINTF("\r\nProcessing camera data\r\n");
  while (1)
  {
    if (g_isCamDataExtracted)
    {
    	//Get extracted camera data and put it the proper order for this model
       CSI2Image(s_data, EXTRACT_WIDTH, EXTRACT_HEIGHT, pExtract, MODEL_COLOR_ORDER, MODEL_IMAGE_LAYOUT);

       /* Resize data array to MODEL_INPUT_WIDTH x MODEL_INPUT_HEIGHT*/
       prev_scale.imageData = s_data;
       after_scale = ImScale(&prev_scale, after_scale, dx, dy);

       /* Convert the color image to monochrome */
       convert_to_monochrome(after_scale->imageData, s_monochrome);

       /* Run inference on the resized and decolorized data */
       run_inference(s_monochrome, LABELS, MODEL_IMAGE_SCALE_MODE);
       g_isCamDataExtracted = false;
    }
  }
}

