/*
 * Copyright 2019-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "littlevgl_support.h"
#include "display_support.h"
#include "lvgl.h"
#if defined(SDK_OS_FREE_RTOS)
#include "FreeRTOS.h"
#include "semphr.h"
#endif
#include "board.h"

#include "fsl_gpio.h"
#include "fsl_power.h"
#include "fsl_debug_console.h"

#if (DEMO_PANEL == DEMO_PANEL_RM67162)
#include "fsl_ft3267.h"
#elif (DEMO_PANEL == DEMO_PANEL_TFT_PROTO_5)
#include "fsl_i2c.h"
#include "fsl_ft5406.h"
#elif ((DEMO_PANEL_RK055AHD091 == DEMO_PANEL) || (DEMO_PANEL_RK055IQH091 == DEMO_PANEL))
#include "fsl_gt911.h"
#endif

#if LV_USE_GPU && LV_USE_GPU_NXP_VG_LITE
#include "vg_lite.h"
#include "vg_lite_platform.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if LV_USE_GPU && LV_USE_GPU_NXP_VG_LITE
#define VG_LITE_MAX_CONTIGUOUS_SIZE 0x100000
#define VG_LITE_COMMAND_BUFFER_SIZE (128 << 10)
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void DEMO_FlushDisplay(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);

static void DEMO_InitTouch(void);

static bool DEMO_ReadTouch(lv_indev_drv_t *drv, lv_indev_data_t *data);

static void DEMO_BufferSwitchOffCallback(void *param, void *switchOffBuffer);

#if ((DEMO_PANEL == DEMO_PANEL_RM67162) || (DEMO_PANEL_RK055AHD091 == DEMO_PANEL) || \
     (DEMO_PANEL_RK055IQH091 == DEMO_PANEL))
void BOARD_PullMIPIPanelTouchResetPin(bool pullUp);
#endif

#if ((DEMO_PANEL_RK055AHD091 == DEMO_PANEL) || (DEMO_PANEL_RK055IQH091 == DEMO_PANEL))
static void BOARD_ConfigMIPIPanelTouchIntPin(gt911_int_pin_mode_t mode);
#endif

#if LV_USE_GPU && LV_USE_GPU_NXP_VG_LITE
static status_t BOARD_PrepareVGLiteController(void);

static status_t BOARD_InitVGliteClock(void);
#endif /* LV_USE_GPU_NXP_VG_LITE */

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(SDK_OS_FREE_RTOS)
static SemaphoreHandle_t s_transferDone;
#else
static volatile bool s_transferDone;
#endif

#if (DEMO_PANEL == DEMO_PANEL_RM67162)
static ft3267_handle_t s_touchHandle;
static volatile bool s_touchEvent = false;

static const ft3267_config_t s_touchConfig = {
    .I2C_ReceiveFunc  = BOARD_MIPIPanelTouch_I2C_Receive,
    .pullResetPinFunc = BOARD_PullMIPIPanelTouchResetPin,
    .pullPowerPinFunc = NULL,
    .timeDelayMsFunc  = VIDEO_DelayMs,
};

#elif ((DEMO_PANEL_RK055AHD091 == DEMO_PANEL) || (DEMO_PANEL_RK055IQH091 == DEMO_PANEL))
/* GT911 I2C address depends on the int pin state during initialization.
 * On this board, the touch panel int pin is forced to input, so the I2C address
 * could not be configured, driver select the one which works.
 */
static gt911_handle_t s_touchHandle;
static const gt911_config_t s_touchConfig = {
    .I2C_SendFunc     = BOARD_MIPIPanelTouch_I2C_Send,
    .I2C_ReceiveFunc  = BOARD_MIPIPanelTouch_I2C_Receive,
    .pullResetPinFunc = BOARD_PullMIPIPanelTouchResetPin,
    .intPinFunc       = BOARD_ConfigMIPIPanelTouchIntPin,
    .timeDelayMsFunc  = VIDEO_DelayMs,
    .touchPointNum    = 1,
    .i2cAddrMode      = kGT911_I2cAddrAny,
    .intTrigMode      = kGT911_IntRisingEdge,
};
static int s_touchResolutionX;
static int s_touchResolutionY;
#endif

#if LV_USE_GPU && LV_USE_GPU_NXP_VG_LITE
static uint32_t registerMemBase = 0x40240000;
static uint32_t gpu_mem_base    = 0x0;

/*
 * In case custom VGLite memory parameters are used, the application needs to
 * allocate and publish the VGLite heap base, its size and the size of the
 * command buffer(s) using the following global variables:
 */
extern void *vglite_heap_base;
extern uint32_t vglite_heap_size;
extern uint32_t vglite_cmd_buff_size;

#if (CUSTOM_VGLITE_MEMORY_CONFIG == 0)
/* VGLite driver heap */
AT_NONCACHEABLE_SECTION_ALIGN(uint8_t contiguous_mem[VG_LITE_MAX_CONTIGUOUS_SIZE], 64);

void *vglite_heap_base        = &contiguous_mem;
uint32_t vglite_heap_size     = VG_LITE_MAX_CONTIGUOUS_SIZE;
uint32_t vglite_cmd_buff_size = VG_LITE_COMMAND_BUFFER_SIZE;
#endif /* CUSTOM_VGLITE_MEMORY_CONFIG */
#endif /* LV_USE_GPU_NXP_VG_LITE */

/*******************************************************************************
 * Code
 ******************************************************************************/

void lv_port_pre_init(void)
{
}

void lv_port_disp_init(void)
{
    static lv_disp_buf_t disp_buf;

    memset((void *)DEMO_BUFFER0_ADDR, 0, DEMO_BUFFER_WIDTH * DEMO_BUFFER_HEIGHT * DEMO_BUFFER_BYTE_PER_PIXEL);
    memset((void *)DEMO_BUFFER1_ADDR, 0, DEMO_BUFFER_WIDTH * DEMO_BUFFER_HEIGHT * DEMO_BUFFER_BYTE_PER_PIXEL);
    lv_disp_buf_init(&disp_buf, (void *)DEMO_BUFFER0_ADDR, (void *)DEMO_BUFFER1_ADDR, LV_HOR_RES_MAX * LV_VER_RES_MAX);

    status_t status;
    dc_fb_info_t fbInfo;

#if LV_USE_GPU && LV_USE_GPU_NXP_VG_LITE
    /* Initialize GPU. */
    BOARD_PrepareVGLiteController();
#endif

    /*-------------------------
     * Initialize your display
     * -----------------------*/
    BOARD_PrepareDisplayController();

    status = g_dc.ops->init(&g_dc);
    if (kStatus_Success != status)
    {
        assert(0);
    }

    g_dc.ops->getLayerDefaultConfig(&g_dc, 0, &fbInfo);
    fbInfo.pixelFormat = DEMO_BUFFER_PIXEL_FORMAT;
    fbInfo.width       = DEMO_BUFFER_WIDTH;
    fbInfo.height      = DEMO_BUFFER_HEIGHT;
    fbInfo.startX      = DEMO_BUFFER_START_X;
    fbInfo.startY      = DEMO_BUFFER_START_Y;
    fbInfo.strideBytes = DEMO_BUFFER_STRIDE_BYTE;
    g_dc.ops->setLayerConfig(&g_dc, 0, &fbInfo);

    g_dc.ops->setCallback(&g_dc, 0, DEMO_BufferSwitchOffCallback, NULL);

#if defined(SDK_OS_FREE_RTOS)
    s_transferDone = xSemaphoreCreateBinary();
    if (NULL == s_transferDone)
    {
        PRINTF("Frame semaphore create failed\r\n");
        assert(0);
    }
#else
    s_transferDone = false;
#endif

    /* Clear initial frame. */
    memset((void *)DEMO_BUFFER1_ADDR, 0, DEMO_BUFFER_STRIDE_BYTE * DEMO_BUFFER_HEIGHT);
    g_dc.ops->setFrameBuffer(&g_dc, 0, (void *)DEMO_BUFFER1_ADDR);

    /* Wait for frame buffer sent to display controller video memory. */
    if ((g_dc.ops->getProperty(&g_dc) & kDC_FB_ReserveFrameBuffer) == 0)
    {
#if defined(SDK_OS_FREE_RTOS)
        if (xSemaphoreTake(s_transferDone, portMAX_DELAY) != pdTRUE)
        {
            PRINTF("Wait semaphore error: s_transferDone\r\n");
            assert(0);
        }
#else
        while (false == s_transferDone)
        {
        }
#endif
    }

    g_dc.ops->enableLayer(&g_dc, 0);

    /*-----------------------------------
     * Register the display in LittlevGL
     *----------------------------------*/

    lv_disp_drv_t disp_drv;      /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = LV_HOR_RES_MAX;
    disp_drv.ver_res = LV_VER_RES_MAX;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = DEMO_FlushDisplay;

    /*Set a display buffer*/
    disp_drv.buffer = &disp_buf;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);

#if LV_USE_GPU && LV_USE_GPU_NXP_VG_LITE
    if (vg_lite_init(64, 64) != VG_LITE_SUCCESS) {
        PRINTF("VGLite init error. STOP.");
        vg_lite_close();
        assert(0);
    }
#endif
}

static void DEMO_BufferSwitchOffCallback(void *param, void *switchOffBuffer)
{
#if defined(SDK_OS_FREE_RTOS)
    BaseType_t taskAwake = pdFALSE;

    xSemaphoreGiveFromISR(s_transferDone, &taskAwake);
    portYIELD_FROM_ISR(taskAwake);
#else
    s_transferDone = true;
#endif
}

static void DEMO_FlushDisplay(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
#if !defined(SDK_OS_FREE_RTOS)
    s_transferDone = false;
#endif

    g_dc.ops->setFrameBuffer(&g_dc, 0, (void *)color_p);

#if defined(SDK_OS_FREE_RTOS)
    if (xSemaphoreTake(s_transferDone, portMAX_DELAY) == pdTRUE)
    {
        /* IMPORTANT!!!
         * Inform the graphics library that you are ready with the flushing*/
        lv_disp_flush_ready(disp_drv);
    }
    else
    {
        PRINTF("Display flush failed\r\n");
        assert(0);
    }
#else
    while (!s_transferDone)
    {
    }

    /* IMPORTANT!!!
     * Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
#endif
}

void lv_port_indev_init(void)
{
    lv_indev_drv_t indev_drv;

    /*------------------
     * Touchpad
     * -----------------*/

    /*Initialize your touchpad */
    DEMO_InitTouch();

    /*Register a touchpad input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type    = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = DEMO_ReadTouch;
    lv_indev_drv_register(&indev_drv);
}

#if ((DEMO_PANEL == DEMO_PANEL_RM67162) || (DEMO_PANEL_RK055AHD091 == DEMO_PANEL) || \
     (DEMO_PANEL_RK055IQH091 == DEMO_PANEL))
void BOARD_PullMIPIPanelTouchResetPin(bool pullUp)
{
    if (pullUp)
    {
        GPIO_PinWrite(GPIO, BOARD_MIPI_PANEL_TOUCH_RST_PORT, BOARD_MIPI_PANEL_TOUCH_RST_PIN, 1);
    }
    else
    {
        GPIO_PinWrite(GPIO, BOARD_MIPI_PANEL_TOUCH_RST_PORT, BOARD_MIPI_PANEL_TOUCH_RST_PIN, 0);
    }
}
#endif

#if (DEMO_PANEL == DEMO_PANEL_RM67162)
void BOARD_TouchIntHandler(void)
{
    s_touchEvent = true;
}

/*Initialize your touchpad*/
static void DEMO_InitTouch(void)
{
    status_t status;

    const gpio_pin_config_t resetPinConfig  = {.pinDirection = kGPIO_DigitalOutput, .outputLogic = 0};
    const gpio_pin_config_t intPinConfig    = {.pinDirection = kGPIO_DigitalInput, .outputLogic = 0};
    gpio_interrupt_config_t intPinIntConfig = {kGPIO_PinIntEnableEdge, kGPIO_PinIntEnableLowOrFall};

    GPIO_PinInit(GPIO, BOARD_MIPI_PANEL_TOUCH_RST_PORT, BOARD_MIPI_PANEL_TOUCH_RST_PIN, &resetPinConfig);

    status = FT3267_Init(&s_touchHandle, &s_touchConfig);

    if (kStatus_Success != status)
    {
        PRINTF("Touch IC initialization failed\r\n");
        assert(false);
    }

    GPIO_PinInit(GPIO, BOARD_MIPI_PANEL_TOUCH_INT_PORT, BOARD_MIPI_PANEL_TOUCH_INT_PIN, &intPinConfig);
    GPIO_SetPinInterruptConfig(GPIO, BOARD_MIPI_PANEL_TOUCH_INT_PORT, BOARD_MIPI_PANEL_TOUCH_INT_PIN, &intPinIntConfig);
    GPIO_PinEnableInterrupt(GPIO, BOARD_MIPI_PANEL_TOUCH_INT_PORT, BOARD_MIPI_PANEL_TOUCH_INT_PIN, kGPIO_InterruptA);
}

/* Will be called by the library to read the touchpad */
static bool DEMO_ReadTouch(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    touch_event_t touch_event;
    static int touch_x = 0;
    static int touch_y = 0;

    data->state = LV_INDEV_STATE_REL;

    if (s_touchEvent)
    {
        if (kStatus_Success == FT3267_GetSingleTouch(&s_touchHandle, &touch_event, &touch_x, &touch_y))
        {
            if ((touch_event == kTouch_Down) || (touch_event == kTouch_Contact))
            {
                data->state = LV_INDEV_STATE_PR;
                touch_x     = LCD_WIDTH - touch_x;
                touch_y     = LCD_HEIGHT - touch_y;
            }
        }

        s_touchEvent = false;
    }

    /*Set the last pressed coordinates*/
    data->point.x = touch_x;
    data->point.y = touch_y;

    /*Return `false` because we are not buffering and no more data to read*/
    return false;
}

#elif ((DEMO_PANEL_RK055AHD091 == DEMO_PANEL) || (DEMO_PANEL_RK055IQH091 == DEMO_PANEL))

static void BOARD_ConfigMIPIPanelTouchIntPin(gt911_int_pin_mode_t mode)
{
    if (mode == kGT911_IntPinInput)
    {
        GPIO->DIRCLR[BOARD_MIPI_PANEL_TOUCH_INT_PORT] = (1U << BOARD_MIPI_PANEL_TOUCH_INT_PIN);
    }
    else
    {
        if (mode == kGT911_IntPinPullDown)
        {
            GPIO_PinWrite(GPIO, BOARD_MIPI_PANEL_TOUCH_INT_PORT, BOARD_MIPI_PANEL_TOUCH_INT_PIN, 1);
        }
        else
        {
            GPIO_PinWrite(GPIO, BOARD_MIPI_PANEL_TOUCH_INT_PORT, BOARD_MIPI_PANEL_TOUCH_INT_PIN, 0);
        }

        GPIO->DIRSET[BOARD_MIPI_PANEL_TOUCH_INT_PORT] = (1U << BOARD_MIPI_PANEL_TOUCH_INT_PIN);
    }
}

/*Initialize your touchpad*/
static void DEMO_InitTouch(void)
{
    status_t status;

    const gpio_pin_config_t resetPinConfig = {.pinDirection = kGPIO_DigitalOutput, .outputLogic = 0};

    GPIO_PinInit(GPIO, BOARD_MIPI_PANEL_TOUCH_RST_PORT, BOARD_MIPI_PANEL_TOUCH_RST_PIN, &resetPinConfig);
    GPIO_PinInit(GPIO, BOARD_MIPI_PANEL_TOUCH_INT_PORT, BOARD_MIPI_PANEL_TOUCH_INT_PIN, &resetPinConfig);

    status = GT911_Init(&s_touchHandle, &s_touchConfig);

    if (kStatus_Success != status)
    {
        PRINTF("Touch IC initialization failed\r\n");
        assert(false);
    }

    GT911_GetResolution(&s_touchHandle, &s_touchResolutionX, &s_touchResolutionY);
}

/* Will be called by the library to read the touchpad */
static bool DEMO_ReadTouch(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    static int touch_x = 0;
    static int touch_y = 0;

    if (kStatus_Success == GT911_GetSingleTouch(&s_touchHandle, &touch_x, &touch_y))
    {
        data->state = LV_INDEV_STATE_PR;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }

    /*Set the last pressed coordinates*/
    data->point.x = touch_x * DEMO_PANEL_WIDTH / s_touchResolutionX;
    data->point.y = touch_y * DEMO_PANEL_HEIGHT / s_touchResolutionY;

    /*Return `false` because we are not buffering and no more data to read*/
    return false;
}

#else

static ft5406_handle_t touch_handle;

/*Initialize your touchpad*/
static void DEMO_InitTouch(void)
{
    status_t status;
    i2c_master_config_t masterConfig;

    I2C_MasterGetDefaultConfig(&masterConfig);

    /* Change the default baudrate configuration */
    masterConfig.baudRate_Bps = 100000;

    /* Initialize the I2C master peripheral */
    I2C_MasterInit(BOARD_SSD1963_TOUCH_I2C_BASEADDR, &masterConfig, BOARD_SSD1963_TOUCH_I2C_CLOCK_FREQ);

    /* Initialize touch panel controller */
    status = FT5406_Init(&touch_handle, BOARD_SSD1963_TOUCH_I2C_BASEADDR);
    if (status != kStatus_Success)
    {
        PRINTF("Touch panel init failed\n");
    }
}

/* Will be called by the library to read the touchpad */
static bool DEMO_ReadTouch(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    touch_event_t touch_event;
    static int touch_x = 0;
    static int touch_y = 0;

    data->state = LV_INDEV_STATE_REL;

    if (kStatus_Success == FT5406_GetSingleTouch(&touch_handle, &touch_event, &touch_x, &touch_y))
    {
        if ((touch_event == kTouch_Down) || (touch_event == kTouch_Contact))
        {
            data->state = LV_INDEV_STATE_PR;
        }
    }

    /*Set the last pressed coordinates*/
    data->point.x = touch_x;
    data->point.y = touch_y;

    /*Return `false` because we are not buffering and no more data to read*/
    return false;
}
#endif

#if LV_USE_GPU && LV_USE_GPU_NXP_VG_LITE
void GPU_DriverIRQHandler(void)
{
    vg_lite_IRQHandler();
}

static status_t BOARD_InitVGliteClock(void)
{
    SYSCTL0->PDRUNCFG1_CLR = SYSCTL0_PDRUNCFG1_GPU_SRAM_APD_MASK;
    SYSCTL0->PDRUNCFG1_CLR = SYSCTL0_PDRUNCFG1_GPU_SRAM_PPD_MASK;
    POWER_ApplyPD();

    CLOCK_AttachClk(kMAIN_CLK_to_GPU_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivGpuClk, 2);
    CLOCK_EnableClock(kCLOCK_Gpu);
    CLOCK_EnableClock(kCLOCK_AxiSwitch);

    RESET_ClearPeripheralReset(kGPU_RST_SHIFT_RSTn);
    RESET_ClearPeripheralReset(kAXI_SWITCH_RST_SHIFT_RSTn);

    NVIC_SetPriority(GPU_IRQn, 3);
    EnableIRQ((IRQn_Type)GPU_IRQn);

    return kStatus_Success;
}

status_t BOARD_PrepareVGLiteController(void)
{
    status_t status;

    status = BOARD_InitVGliteClock();

    if (kStatus_Success != status)
    {
        return status;
    }

    vg_lite_init_mem(registerMemBase, gpu_mem_base, vglite_heap_base, vglite_heap_size);

    vg_lite_set_command_buffer_size(vglite_cmd_buff_size);

    return kStatus_Success;
}
#endif /* LV_USE_GPU_NXP_VG_LITE */
