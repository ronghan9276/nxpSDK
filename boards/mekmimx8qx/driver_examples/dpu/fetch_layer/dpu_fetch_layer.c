/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dpu.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "dpu_example.h"

#include "fsl_common.h"
#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Landscape or portrait. */
#if (APP_PANEL_WIDTH < APP_PANEL_HEIGHT)
#define APP_PORTRAIT 1
#else
#define APP_PORTRAIT 0
#endif

#if APP_PORTRAIT
#define APP_STREAM_WIDTH (APP_PANEL_WIDTH)
#define APP_STREAM_HEIGHT (APP_PANEL_HEIGHT / 2)
#else
#define APP_STREAM_WIDTH (APP_PANEL_WIDTH / 2)
#define APP_STREAM_HEIGHT (APP_PANEL_HEIGHT)
#endif

#define APP_SUBLAYER_WIDTH 160
#define APP_SUBLAYER_HEIGHT 120

#define APP_STREAM_COUNT 2
#define APP_SUBLAYER_COUNT 8

#define APP_MAKE_COLOR(red, green, blue, alpha) \
    ((((uint32_t)(alpha)) << 24U) | (((uint32_t)(red)) << 16U) | (((uint32_t)(green)) << 8U) | ((uint32_t)(blue)))

#define APP_COLOR_BLUE APP_MAKE_COLOR(0, 0, 0xFF, 0xFF)
#define APP_COLOR_GREEN APP_MAKE_COLOR(0, 0xFF, 0, 0xFF)
#define APP_COLOR_RED APP_MAKE_COLOR(0xFF, 0, 0, 0xFF)
#define APP_COLOR_YELLOW APP_MAKE_COLOR(0xFF, 0xFF, 0, 0xFF)
#define APP_COLOR_CYAN APP_MAKE_COLOR(0, 0xFF, 0xFF, 0xFF)
#define APP_COLOR_MAGENTA APP_MAKE_COLOR(0xFF, 0, 0xFF, 0xFF)
#define APP_COLOR_BLACK APP_MAKE_COLOR(0, 0, 0, 0xFF)
#define APP_COLOR_WHITE APP_MAKE_COLOR(0xFF, 0xFF, 0xFF, 0xFF)
#define APP_COLOR_SILVER APP_MAKE_COLOR(0xC0, 0xC0, 0xC0, 0xFF)
#define APP_COLOR_GRAY APP_MAKE_COLOR(0x80, 0x80, 0x80, 0xFF)

typedef void (*app_draw_func_t)(uint32_t *addr,
                                uint16_t startX,
                                uint16_t startY,
                                uint16_t width,
                                uint16_t height,
                                uint32_t color,
                                uint32_t strideWord);

typedef struct app_dpu_sublayer
{
    uint16_t offsetX;   /* Sublayer offset in the fetch unit output region. */
    uint16_t offsetY;   /* Sublayer offset in the fetch unit output region. */
    int16_t offsetIncX; /* Offset increase value when the frame update. */
    int16_t offsetIncY; /* Offset increase value when the frame update. */
    uint16_t height;    /* Height of the sublayer. */
    uint16_t width;     /* Width of the sublayer. */

    uint32_t fbAddr[2]; /* Frame buffer address. */
    uint8_t fbIdx;      /* Active frame buffer index. */

    uint8_t sublayerIdx; /* Sublayer index in the fetch unit. */

    /*
     * These parameters are used to initialize the frame buffer.
     * The fbInitColor[0] is used to initialize fbAddr[0], the fbInitColor[1]
     * is used to initialize fbAddr[1].
     */
    app_draw_func_t fbInitFunc; /* Function to initialize frame buffer. */
    uint32_t fbInitColor[2];    /* Color used to initialize the frame buffer. */

} app_uint8_t;

typedef struct app_dpu_stream
{
    /* General. */
    uint16_t height;
    uint16_t width;

    /* Fetch unit. */
    dpu_unit_t fetchUnit;
    app_uint8_t *sublayers;
    uint8_t sublayerCount;

    /* Const frame. */
    dpu_unit_t constFrame;
    uint32_t constColor;

    /* Layer blend. */
    dpu_unit_t layerBlend;
    uint8_t layerBlendPrimSrc;
    uint8_t layerBlendSecSrc;

    /* Ext Dst. */
    dpu_unit_t extDst;
    uint8_t extDstSrc;

    /* Pipeline. */
    dpu_unit_t pipeline;

    volatile bool isShadowLoadPending;

    /* Interrupt. */
    uint32_t intGroup0;
    uint32_t intGroup1;
} app_dpu_stream_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/


static void APP_DrawRectangle(uint32_t *addr,
                              uint16_t startX,
                              uint16_t startY,
                              uint16_t width,
                              uint16_t height,
                              uint32_t color,
                              uint32_t strideWord);

static void APP_DrawDiamond(uint32_t *addr,
                            uint16_t startX,
                            uint16_t startY,
                            uint16_t width,
                            uint16_t height,
                            uint32_t color,
                            uint32_t strideWord);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*
 * This example uses 2 streams, each stream uses 8 sublayers, and each sublayer
 * uses 2 frame buffers. So there are 32 frame buffers.
 */
AT_NONCACHEABLE_SECTION_ALIGN(
    uint32_t s_frameBuffers[APP_STREAM_COUNT][APP_SUBLAYER_COUNT][2][APP_SUBLAYER_WIDTH][APP_SUBLAYER_HEIGHT], 32);

app_uint8_t safetySreamSublayer[] = {
    /* sublayer 0 */
    {
        .offsetX     = 0,
        .offsetY     = 0,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .fbAddr      = {(uint32_t)s_frameBuffers[0][0][0], (uint32_t)s_frameBuffers[0][0][1]},
        .fbIdx       = 0,
        .sublayerIdx = 0,
        .fbInitFunc  = APP_DrawRectangle,
        .fbInitColor = {APP_COLOR_GRAY, APP_COLOR_SILVER},
    },
    /* sublayer 1 */
    {
        .offsetX     = APP_STREAM_WIDTH / 2,
        .offsetY     = 0,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .fbAddr      = {(uint32_t)s_frameBuffers[0][1][0], (uint32_t)s_frameBuffers[0][1][1]},
        .fbIdx       = 0,
        .sublayerIdx = 1,
        .fbInitFunc  = APP_DrawRectangle,
        .fbInitColor = {APP_COLOR_RED, APP_COLOR_CYAN},
    },
    /* sublayer 2 */
    {
        .offsetX     = 0,
        .offsetY     = APP_STREAM_HEIGHT / 4,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .fbAddr      = {(uint32_t)s_frameBuffers[0][2][0], (uint32_t)s_frameBuffers[0][2][1]},
        .fbIdx       = 0,
        .sublayerIdx = 2,
        .fbInitFunc  = APP_DrawRectangle,
        .fbInitColor = {APP_COLOR_GREEN, APP_COLOR_MAGENTA},
    },
    /* sublayer 3 */
    {
        .offsetX     = APP_STREAM_WIDTH / 2,
        .offsetY     = APP_STREAM_HEIGHT / 4,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .fbAddr      = {(uint32_t)s_frameBuffers[0][3][0], (uint32_t)s_frameBuffers[0][3][1]},
        .fbIdx       = 0,
        .sublayerIdx = 3,
        .fbInitFunc  = APP_DrawRectangle,
        .fbInitColor = {APP_COLOR_BLUE, APP_COLOR_YELLOW},
    },
    /* sublayer 4 */
    {
        .offsetX     = 0,
        .offsetY     = APP_STREAM_HEIGHT / 2,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .fbAddr      = {(uint32_t)s_frameBuffers[0][4][0], (uint32_t)s_frameBuffers[0][4][1]},
        .fbIdx       = 0,
        .sublayerIdx = 4,
        .fbInitFunc  = APP_DrawDiamond,
        .fbInitColor = {APP_COLOR_MAGENTA, APP_COLOR_GREEN},
    },
    /* sublayer 5 */
    {
        .offsetX     = APP_STREAM_WIDTH / 2,
        .offsetY     = APP_STREAM_HEIGHT / 2,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .fbAddr      = {(uint32_t)s_frameBuffers[0][5][0], (uint32_t)s_frameBuffers[0][5][1]},
        .fbIdx       = 0,
        .sublayerIdx = 5,
        .fbInitFunc  = APP_DrawDiamond,
        .fbInitColor = {APP_COLOR_YELLOW, APP_COLOR_BLUE},
    },
    /* sublayer 6 */
    {
        .offsetX     = 0,
        .offsetY     = APP_STREAM_HEIGHT * 3 / 4,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .fbAddr      = {(uint32_t)s_frameBuffers[0][6][0], (uint32_t)s_frameBuffers[0][6][1]},
        .fbIdx       = 0,
        .sublayerIdx = 6,
        .fbInitFunc  = APP_DrawDiamond,
        .fbInitColor = {APP_COLOR_CYAN, APP_COLOR_RED},
    },
    /* sublayer 7 */
    {
        .offsetX     = APP_STREAM_WIDTH / 2,
        .offsetY     = APP_STREAM_HEIGHT * 3 / 4,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .fbAddr      = {(uint32_t)s_frameBuffers[0][7][0], (uint32_t)s_frameBuffers[0][7][1]},
        .fbIdx       = 0,
        .sublayerIdx = 7,
        .fbInitFunc  = APP_DrawDiamond,
        .fbInitColor = {APP_COLOR_SILVER, APP_COLOR_GRAY},
    },
};

app_dpu_stream_t safetyStream = {
    /* General. */
    .height = APP_STREAM_HEIGHT,
    .width  = APP_STREAM_WIDTH,

    /* Fetch unit. */
    .fetchUnit     = kDPU_FetchWarp2,
    .sublayers     = safetySreamSublayer,
    .sublayerCount = ARRAY_SIZE(safetySreamSublayer),

    /* Const frame. */
    .constFrame = kDPU_ConstFrame4,
    .constColor = DPU_MAKE_CONST_COLOR(0x00, 0x00, 0x00, 0xFF),

    /* Layer blend. */
    .layerBlend        = kDPU_LayerBlend2,
    .layerBlendPrimSrc = kDPU_UnitSrcConstFrame4,
    .layerBlendSecSrc  = kDPU_UnitSrcFetchWarp2,

    /* Ext Dst. */
    .extDst    = APP_SAFETY_STREAM_EXTDST,
    .extDstSrc = kDPU_UnitSrcLayerBlend2,

    /* Pipeline. */
    .pipeline = APP_SAFETY_STREAM_PIPELINE,

    /* Interrupt. */
    .intGroup0 = APP_SAFETY_STREAM_INT_GROUP0,
    .intGroup1 = APP_SAFETY_STREAM_INT_GROUP1,
};

app_uint8_t contentSreamSublayer[] = {
    /* sublayer 0 */
    {
        .offsetX     = 0,
        .offsetY     = 0,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .fbAddr      = {(uint32_t)s_frameBuffers[1][0][0], (uint32_t)s_frameBuffers[1][0][1]},
        .fbIdx       = 0,
        .sublayerIdx = 0,
        .fbInitFunc  = APP_DrawRectangle,
        .fbInitColor = {APP_COLOR_GRAY, APP_COLOR_SILVER},
    },
    /* sublayer 1 */
    {
        .offsetX     = APP_STREAM_WIDTH / 2,
        .offsetY     = 0,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .fbAddr      = {(uint32_t)s_frameBuffers[1][1][0], (uint32_t)s_frameBuffers[1][1][1]},
        .fbIdx       = 0,
        .sublayerIdx = 1,
        .fbInitFunc  = APP_DrawRectangle,
        .fbInitColor = {APP_COLOR_RED, APP_COLOR_CYAN},
    },
    /* sublayer 2 */
    {
        .offsetX     = 0,
        .offsetY     = APP_STREAM_HEIGHT / 4,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .fbAddr      = {(uint32_t)s_frameBuffers[1][2][0], (uint32_t)s_frameBuffers[1][2][1]},
        .fbIdx       = 0,
        .sublayerIdx = 2,
        .fbInitFunc  = APP_DrawRectangle,
        .fbInitColor = {APP_COLOR_GREEN, APP_COLOR_MAGENTA},
    },
    /* sublayer 3 */
    {
        .offsetX     = APP_STREAM_WIDTH / 2,
        .offsetY     = APP_STREAM_HEIGHT / 4,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .fbAddr      = {(uint32_t)s_frameBuffers[1][3][0], (uint32_t)s_frameBuffers[1][3][1]},
        .fbIdx       = 0,
        .sublayerIdx = 3,
        .fbInitFunc  = APP_DrawRectangle,
        .fbInitColor = {APP_COLOR_BLUE, APP_COLOR_YELLOW},
    },
    /* sublayer 4 */
    {
        .offsetX     = 0,
        .offsetY     = APP_STREAM_HEIGHT / 2,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .fbAddr      = {(uint32_t)s_frameBuffers[1][4][0], (uint32_t)s_frameBuffers[1][4][1]},
        .fbIdx       = 0,
        .sublayerIdx = 4,
        .fbInitFunc  = APP_DrawDiamond,
        .fbInitColor = {APP_COLOR_MAGENTA, APP_COLOR_GREEN},
    },
    /* sublayer 5 */
    {
        .offsetX     = APP_STREAM_WIDTH / 2,
        .offsetY     = APP_STREAM_HEIGHT / 2,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .fbAddr      = {(uint32_t)s_frameBuffers[1][5][0], (uint32_t)s_frameBuffers[1][5][1]},
        .fbIdx       = 0,
        .sublayerIdx = 5,
        .fbInitFunc  = APP_DrawDiamond,
        .fbInitColor = {APP_COLOR_YELLOW, APP_COLOR_BLUE},
    },
    /* sublayer 6 */
    {
        .offsetX     = 0,
        .offsetY     = APP_STREAM_HEIGHT * 3 / 4,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .fbAddr      = {(uint32_t)s_frameBuffers[1][6][0], (uint32_t)s_frameBuffers[1][6][1]},
        .fbIdx       = 0,
        .sublayerIdx = 6,
        .fbInitFunc  = APP_DrawDiamond,
        .fbInitColor = {APP_COLOR_CYAN, APP_COLOR_RED},
    },
    /* sublayer 7 */
    {
        .offsetX     = APP_STREAM_WIDTH / 2,
        .offsetY     = APP_STREAM_HEIGHT * 3 / 4,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .fbAddr      = {(uint32_t)s_frameBuffers[1][7][0], (uint32_t)s_frameBuffers[1][7][1]},
        .fbIdx       = 0,
        .sublayerIdx = 7,
        .fbInitFunc  = APP_DrawDiamond,
        .fbInitColor = {APP_COLOR_SILVER, APP_COLOR_GRAY},
    },
};

app_dpu_stream_t contentStream = {
    /* General. */
    .height = APP_STREAM_HEIGHT,
    .width  = APP_STREAM_WIDTH,

    /* Fetch unit. */
    .fetchUnit     = kDPU_FetchLayer0,
    .sublayers     = contentSreamSublayer,
    .sublayerCount = ARRAY_SIZE(contentSreamSublayer),

    /* Const frame. */
    .constFrame = kDPU_ConstFrame0,
    .constColor = DPU_MAKE_CONST_COLOR(0xFF, 0xFF, 0xFF, 0xFF),

    /* Layer blend. */
    .layerBlend        = kDPU_LayerBlend0,
    .layerBlendPrimSrc = kDPU_UnitSrcConstFrame0,
    .layerBlendSecSrc  = kDPU_UnitSrcFetchLayer0,

    /* Ext Dst. */
    .extDst    = APP_CONTENT_STREAM_EXTDST,
    .extDstSrc = kDPU_UnitSrcLayerBlend0,

    /* Pipeline. */
    .pipeline = APP_CONTENT_STREAM_PIPELINE,

    /* Interrupt. */
    .intGroup0 = APP_CONTENT_STREAM_INT_GROUP0,
    .intGroup1 = APP_CONTENT_STREAM_INT_GROUP1,
};

/*******************************************************************************
 * Code
 ******************************************************************************/

bool APP_IsStreamShadowPending(app_dpu_stream_t *stream)
{
    return stream->isShadowLoadPending;
}

void APP_TriggerStreamShadowLoad(app_dpu_stream_t *stream)
{
    /* Trigger the shadow load. */
    stream->isShadowLoadPending = true;
    DPU_TriggerPipelineShadowLoad(APP_DPU, stream->pipeline);
}

void APP_CheckAndUpdateStreamStatus(app_dpu_stream_t *stream, uint32_t intGroup0Flags, uint32_t intGroup1Flags)
{
    if ((intGroup0Flags & stream->intGroup0) || (intGroup1Flags & stream->intGroup1))
    {
        stream->isShadowLoadPending = false;
    }
}

void APP_UpdateSublayer(app_uint8_t *sublayer, uint16_t streamHeight, uint16_t streamWidth, dpu_unit_t fetchUnit)
{
    /* Switch to use the other frame buffer or not. */
    bool fbSwitch = false;

    if (0U == sublayer->offsetX)
    {
        sublayer->offsetIncX = 1;
        fbSwitch             = true;
    }
    else if (streamWidth - sublayer->width - 1 <= sublayer->offsetX)
    {
        sublayer->offsetX    = streamWidth - sublayer->width - 1;
        sublayer->offsetIncX = -1;
        fbSwitch             = true;
    }

    if (0U == sublayer->offsetY)
    {
        sublayer->offsetIncY = 1;
        fbSwitch             = true;
    }
    else if (streamHeight - sublayer->height - 1 <= sublayer->offsetY)
    {
        sublayer->offsetY    = streamHeight - sublayer->height - 1;
        sublayer->offsetIncY = -1;
        fbSwitch             = true;
    }

    if (fbSwitch)
    {
        sublayer->fbIdx ^= 1;
        DPU_SetFetchUnitSrcBufferAddr(APP_DPU, fetchUnit, sublayer->sublayerIdx,
                                      (uint32_t)sublayer->fbAddr[sublayer->fbIdx]);
    }

    /* Update the format: color and offset. */
    sublayer->offsetX += sublayer->offsetIncX;
    sublayer->offsetY += sublayer->offsetIncY;

    DPU_SetFetchUnitOffset(APP_DPU, fetchUnit, sublayer->sublayerIdx, sublayer->offsetX, sublayer->offsetY);
}

void APP_UpdateStream(app_dpu_stream_t *stream)
{
    uint8_t sublayerIdx;

    if (!stream->isShadowLoadPending)
    {
        for (sublayerIdx = 0; sublayerIdx < stream->sublayerCount; sublayerIdx++)
        {
            APP_UpdateSublayer(&(stream->sublayers[sublayerIdx]), stream->height, stream->width, stream->fetchUnit);
        }

        /* Trigger the shadow load. */
        DPU_TriggerPipelineShadowLoad(APP_DPU, stream->pipeline);
        stream->isShadowLoadPending = true;
    }
}

void APP_InitFrameBuffer(app_uint8_t *sublayer)
{
    sublayer->fbIdx = 0;
    sublayer->fbInitFunc((uint32_t *)sublayer->fbAddr[0], 0, 0, sublayer->width, sublayer->height,
                         sublayer->fbInitColor[0], sublayer->width);
    sublayer->fbInitFunc((uint32_t *)sublayer->fbAddr[1], 0, 0, sublayer->width, sublayer->height,
                         sublayer->fbInitColor[1], sublayer->width);
}

void APP_InitStream(app_dpu_stream_t *stream)
{
    dpu_const_frame_config_t cfConfig;
    dpu_layer_blend_config_t lbConfig;
    dpu_fetch_unit_config_t fetchConfig;
    dpu_src_buffer_config_t sbConfig;

    /* Pipeline. */
    DPU_InitPipeline(APP_DPU, stream->pipeline);

    /* ExtDst. */
    DPU_InitExtDst(APP_DPU, stream->extDst, DPU_MAKE_SRC_REG1(stream->extDstSrc));

    /* Layer blend. */
    DPU_InitLayerBlend(APP_DPU, stream->layerBlend,
                       DPU_MAKE_SRC_REG2(stream->layerBlendPrimSrc, stream->layerBlendSecSrc));
    DPU_LayerBlendGetDefaultConfig(&lbConfig);
    lbConfig.constAlpha         = 32;
    lbConfig.primColorBlendMode = kDPU_BlendConstAlpha;
    lbConfig.secColorBlendMode  = kDPU_BlendConstAlphaInv;
    DPU_SetLayerBlendConfig(APP_DPU, stream->layerBlend, &lbConfig);
    DPU_EnableLayerBlend(APP_DPU, stream->layerBlend, true);

    /* Const frame. */
    cfConfig.frameWidth  = stream->width;
    cfConfig.frameHeight = stream->height;
    cfConfig.constColor  = stream->constColor;

    DPU_InitConstFrame(APP_DPU, stream->constFrame);
    DPU_SetConstFrameConfig(APP_DPU, stream->constFrame, &cfConfig);

    /* Fetch unit. */
    DPU_FetchUnitGetDefaultConfig(&fetchConfig);
    fetchConfig.frameHeight = stream->height;
    fetchConfig.frameWidth  = stream->width;
    DPU_InitFetchUnit(APP_DPU, stream->fetchUnit, &fetchConfig);

    DPU_SrcBufferGetDefaultConfig(&sbConfig);

    sbConfig.strideBytes  = 4 * APP_SUBLAYER_WIDTH;
    sbConfig.bitsPerPixel = 32;
    sbConfig.pixelFormat  = kDPU_PixelFormatARGB8888;
    sbConfig.bufferHeight = APP_SUBLAYER_HEIGHT;
    sbConfig.bufferWidth  = APP_SUBLAYER_WIDTH;
    sbConfig.constColor   = DPU_MAKE_CONST_COLOR(0, 0, 0, 0);

    for (uint8_t i = 0; i < stream->sublayerCount; i++)
    {
        sbConfig.baseAddr = stream->sublayers[i].fbAddr[0];

        APP_InitFrameBuffer(&stream->sublayers[i]);
        DPU_SetFetchUnitSrcBufferConfig(APP_DPU, stream->fetchUnit, stream->sublayers[i].sublayerIdx, &sbConfig);
        DPU_SetFetchUnitOffset(APP_DPU, stream->fetchUnit, stream->sublayers[i].sublayerIdx,
                               stream->sublayers[i].offsetX, stream->sublayers[i].offsetY);
        DPU_EnableFetchUnitSrcBuffer(APP_DPU, stream->fetchUnit, stream->sublayers[i].sublayerIdx, true);
    }

    APP_TriggerStreamShadowLoad(stream);

    DPU_EnableInterrupts(APP_DPU, 0, stream->intGroup0);
    DPU_EnableInterrupts(APP_DPU, 1, stream->intGroup1);
}

static void APP_DrawRectangle(uint32_t *addr,
                              uint16_t startX,
                              uint16_t startY,
                              uint16_t width,
                              uint16_t height,
                              uint32_t color,
                              uint32_t strideWord)
{
    uint16_t x, y;

    for (y = startY; y < startY + height; y++)
    {
        for (x = startX; x < startX + width; x++)
        {
            *(addr + strideWord * y + x) = color;
        }
    }
}

static void APP_DrawDiamond(uint32_t *addr,
                            uint16_t startX,
                            uint16_t startY,
                            uint16_t width,
                            uint16_t height,
                            uint32_t color,
                            uint32_t strideWord)
{
    uint16_t x, y;
    uint16_t lineWidth;
    float ratio = (float)width / (float)height;

    for (y = 0; y <= height / 2; y++)
    {
        lineWidth = (uint16_t)((float)y * ratio);

        for (x = startX + width / 2 - lineWidth; x < startX + width / 2 + lineWidth; x++)
        {
            *(addr + strideWord * (startY + y) + x) = color;
        }

        for (x = startX + width / 2 - lineWidth; x < startX + width / 2 + lineWidth; x++)
        {
            *(addr + strideWord * (startY + height - y) + x) = color;
        }
    }
}

void APP_DPU_FetchLayer(void)
{
    dpu_display_timing_config_t displayTimingConfig;
    dpu_display_config_t displayConfig;

    DPU_Init(APP_DPU);

    DPU_PreparePathConfig(APP_DPU);

    DPU_DisplayTimingGetDefaultConfig(&displayTimingConfig);

    displayTimingConfig.flags  = APP_DPU_TIMING_FLAGS;
    displayTimingConfig.width  = APP_PANEL_WIDTH;
    displayTimingConfig.hsw    = APP_HSW;
    displayTimingConfig.hfp    = APP_HFP;
    displayTimingConfig.hbp    = APP_HBP;
    displayTimingConfig.height = APP_PANEL_HEIGHT;
    displayTimingConfig.vsw    = APP_VSW;
    displayTimingConfig.vfp    = APP_VFP;
    displayTimingConfig.vbp    = APP_VBP;

    DPU_InitDisplayTiming(APP_DPU, APP_DPU_DISPLAY_INDEX, &displayTimingConfig);

    DPU_DisplayGetDefaultConfig(&displayConfig);
    displayConfig.displayMode = kDPU_DisplayPrimOnTop;

    displayConfig.secAreaStartX = 1;
    displayConfig.secAreaStartY = 1;

#if APP_PORTRAIT
    displayConfig.primAreaStartX = 1;
    displayConfig.primAreaStartY = APP_STREAM_HEIGHT + 1;
#else
    displayConfig.primAreaStartX = APP_STREAM_WIDTH + 1;
    displayConfig.primAreaStartY = 1;
#endif

    APP_InitStream(&safetyStream);
    APP_InitStream(&contentStream);

    DPU_SetDisplayConfig(APP_DPU, APP_DPU_DISPLAY_INDEX, &displayConfig);

    DPU_TriggerDisplayShadowLoad(APP_DPU, APP_DPU_DISPLAY_INDEX);

    /*
     * Initialize workflow:
     * 1. Init DPU
     * 2. Configure pixel link.
     * 3. Init and start display interface.
     * 4. Start DPU
     */
    APP_InitPixelLink();

    APP_StartDisplayInterface();

    DPU_StartDisplay(APP_DPU, APP_DPU_DISPLAY_INDEX);
}

void DPU_IRQHandler(void)
{
    uint32_t intGroup0Flags, intGroup1Flags;
    intGroup0Flags = DPU_GetInterruptsPendingFlags(APP_DPU, 0);
    intGroup1Flags = DPU_GetInterruptsPendingFlags(APP_DPU, 1);

    APP_CheckAndUpdateStreamStatus(&safetyStream, intGroup0Flags, intGroup1Flags);
    APP_CheckAndUpdateStreamStatus(&contentStream, intGroup0Flags, intGroup1Flags);

    DPU_ClearInterruptsPendingFlags(APP_DPU, 0, intGroup0Flags);
    DPU_ClearInterruptsPendingFlags(APP_DPU, 1, intGroup1Flags);
    __DSB();
}

/*!
 * @brief Main function
 */
int main(void)
{
    sc_ipc_t ipc;

    ipc = BOARD_InitRpc();
    BOARD_InitPins(ipc);
    BOARD_BootClockRUN();
    BOARD_PrepareDisplay();
    BOARD_InitMemory();
    BOARD_InitDebugConsole();

    PRINTF("DPU fetch layer example start...\r\n");

    /* Start the DPU. */
    APP_DPU_FetchLayer();

    /* Run and update the display content */
    while (1)
    {
        APP_UpdateStream(&safetyStream);
        APP_UpdateStream(&contentStream);
    }
}
