/*
 * The Clear BSD License
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "board.h"
#include "music.h"
#if defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT
#include "fsl_dmamux.h"
#endif
#include "fsl_sai_edma.h"
#include "fsl_debug_console.h"

#include "fsl_wm8960.h"
#include "fsl_device_registers.h"
#include "fsl_common.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* SAI and I2C instance and clock */
#define DEMO_SAI I2S0
#define DEMO_I2C LPI2C0
#define DEMO_SAI_CLKSRC kCLOCK_CoreSysClk
#define DEMO_SAI_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)
#define DEMO_I2C_CLKSRC kCLOCK_McgIrc48MClk
#define DEMO_I2C_CLK_FREQ CLOCK_GetFreq(kCLOCK_McgIrc48MClk)
#define DEMO_CODEC_WM8960 (1)
#define EXAMPLE_DMA (DMA0)
#define EXAMPLE_CHANNEL (0)
#define EXAMPLE_SAI_TX_SOURCE kDmaRequestMux0I2S0Tx

#define I2C_RELEASE_SDA_PORT PORTB
#define I2C_RELEASE_SCL_PORT PORTB
#define I2C_RELEASE_SDA_GPIO GPIOB
#define I2C_RELEASE_SDA_PIN 1U
#define I2C_RELEASE_SCL_GPIO GPIOB
#define I2C_RELEASE_SCL_PIN 0U
#define I2C_RELEASE_BUS_COUNT 100U
#define OVER_SAMPLE_RATE (384U)
#define BUFFER_SIZE (1600U)
#define BUFFER_NUM (2U)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_I2C_ReleaseBus(void);
static void callback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
AT_NONCACHEABLE_SECTION_INIT(sai_edma_handle_t txHandle) = {0};
edma_handle_t dmaHandle = {0};
codec_handle_t codecHandle = {0};
extern codec_config_t boardCodecConfig;
AT_NONCACHEABLE_SECTION_ALIGN(static uint8_t buffer[BUFFER_NUM*BUFFER_SIZE], 4);
volatile bool isFinished = false;
volatile uint32_t finishIndex = 0U;
volatile uint32_t emptyBlock = BUFFER_NUM;
/*******************************************************************************
 * Code
 ******************************************************************************/


static void i2c_release_bus_delay(void)
{
    uint32_t i = 0;
    for (i = 0; i < I2C_RELEASE_BUS_COUNT; i++)
    {
        __NOP();
    }
}

void BOARD_I2C_ReleaseBus(void)
{
    uint8_t i = 0;
    gpio_pin_config_t pin_config;
    port_pin_config_t i2c_pin_config = {0};

    /* Config pin mux as gpio */
    i2c_pin_config.pullSelect = kPORT_PullUp;
    i2c_pin_config.mux = kPORT_MuxAsGpio;

    pin_config.pinDirection = kGPIO_DigitalOutput;
    pin_config.outputLogic = 1U;
    CLOCK_EnableClock(kCLOCK_PortB);
    PORT_SetPinConfig(I2C_RELEASE_SCL_PORT, I2C_RELEASE_SCL_PIN, &i2c_pin_config);
    PORT_SetPinConfig(I2C_RELEASE_SCL_PORT, I2C_RELEASE_SDA_PIN, &i2c_pin_config);

    GPIO_PinInit(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, &pin_config);
    GPIO_PinInit(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, &pin_config);

    /* Drive SDA low first to simulate a start */
    GPIO_PinWrite(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 0U);
    i2c_release_bus_delay();

    /* Send 9 pulses on SCL and keep SDA high */
    for (i = 0; i < 9; i++)
    {
        GPIO_PinWrite(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 0U);
        i2c_release_bus_delay();

        GPIO_PinWrite(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 1U);
        i2c_release_bus_delay();

        GPIO_PinWrite(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 1U);
        i2c_release_bus_delay();
        i2c_release_bus_delay();
    }

    /* Send stop */
    GPIO_PinWrite(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_PinWrite(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_PinWrite(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 1U);
    i2c_release_bus_delay();

    GPIO_PinWrite(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 1U);
    i2c_release_bus_delay();
}
static void callback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData)
{
    if(kStatus_SAI_RxError == status)
    {
    }
    else
    {
        finishIndex++;
        emptyBlock++;
        /* Judge whether the music array is completely transfered. */
        if(MUSIC_LEN/BUFFER_SIZE == finishIndex)
        {
            isFinished = true;
        }
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    sai_config_t config;
    uint32_t mclkSourceClockHz = 0U;
    sai_transfer_format_t format;
    sai_transfer_t xfer;
    edma_config_t dmaConfig = {0};
    uint32_t cpy_index = 0U, tx_index=0U;
    uint32_t delayCycle = 500000U;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_I2C_ReleaseBus();
    BOARD_I2C_ConfigurePins();
    BOARD_InitDebugConsole();
    CLOCK_SetPllFllSelClock(3U); /* IRC48 MHz clock. */
    CLOCK_SetLpi2c0Clock(1);
    BOARD_Codec_I2C_Init();

    PRINTF("SAI example started!\n\r");

    /* Create EDMA handle */
    /*
     * dmaConfig.enableRoundRobinArbitration = false;
     * dmaConfig.enableHaltOnError = true;
     * dmaConfig.enableContinuousLinkMode = false;
     * dmaConfig.enableDebugMode = false;
     */
    EDMA_GetDefaultConfig(&dmaConfig);
    EDMA_Init(EXAMPLE_DMA, &dmaConfig);
    EDMA_CreateHandle(&dmaHandle, EXAMPLE_DMA, EXAMPLE_CHANNEL);

#if defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT
    DMAMUX_Init(DMAMUX0);
    DMAMUX_SetSource(DMAMUX0, EXAMPLE_CHANNEL, EXAMPLE_SAI_TX_SOURCE);
    DMAMUX_EnableChannel(DMAMUX0, EXAMPLE_CHANNEL);
#endif

    /* Init SAI module */
    /*
     * config.masterSlave = kSAI_Master;
     * config.mclkSource = kSAI_MclkSourceSysclk;
     * config.protocol = kSAI_BusLeftJustified;
     * config.syncMode = kSAI_ModeAsync;
     * config.mclkOutputEnable = true;
     */
    SAI_TxGetDefaultConfig(&config);
#if defined DEMO_CODEC_WM8524
    config.protocol = kSAI_BusI2S;
#endif
    SAI_TxInit(DEMO_SAI, &config);

    /* Configure the audio format */
    format.bitWidth = kSAI_WordWidth16bits;
    format.channel = 0U;
    format.sampleRate_Hz = kSAI_SampleRate16KHz;
#if (defined FSL_FEATURE_SAI_HAS_MCLKDIV_REGISTER && FSL_FEATURE_SAI_HAS_MCLKDIV_REGISTER) || \
    (defined FSL_FEATURE_PCC_HAS_SAI_DIVIDER && FSL_FEATURE_PCC_HAS_SAI_DIVIDER)
    format.masterClockHz = OVER_SAMPLE_RATE * format.sampleRate_Hz;
#else
    format.masterClockHz = DEMO_SAI_CLK_FREQ;
#endif
    format.protocol = config.protocol;
    format.stereo = kSAI_Stereo;
    format.isFrameSyncCompact = false;
#if defined(FSL_FEATURE_SAI_FIFO_COUNT) && (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    format.watermark = FSL_FEATURE_SAI_FIFO_COUNT / 2U;
#endif

    /* Use default setting to init codec */
    CODEC_Init(&codecHandle, &boardCodecConfig);
    CODEC_SetFormat(&codecHandle, format.masterClockHz, format.sampleRate_Hz, format.bitWidth);

#if defined(DEMO_CODEC_WM8524)
    wm8524_config_t codecConfig = {0};
    codecConfig.busPinNum = CODEC_BUS_PIN_NUM;
    codecConfig.busPin = CODEC_BUS_PIN;
    codecConfig.mutePin = CODEC_MUTE_PIN;
    codecConfig.mutePinNum = CODEC_MUTE_PIN_NUM;
    codecConfig.protocol = kWM8524_ProtocolI2S;
    WM8524_Init(&codecHandle, &codecConfig);
#endif


/* If need to handle audio error, enable sai interrupt */
#if defined(DEMO_SAI_IRQ)
    EnableIRQ(DEMO_SAI_IRQ);
    SAI_TxEnableInterrupts(DEMO_SAI, kSAI_FIFOErrorInterruptEnable);
#endif

#if defined(CODEC_CYCLE)
    delayCycle = CODEC_CYCLE;
#endif
    while (delayCycle)
    {
        __ASM("nop");
        delayCycle--;
    }

    SAI_TransferTxCreateHandleEDMA(DEMO_SAI, &txHandle, callback, NULL, &dmaHandle);

    mclkSourceClockHz = DEMO_SAI_CLK_FREQ;
    SAI_TransferTxSetFormatEDMA(DEMO_SAI, &txHandle, &format, mclkSourceClockHz, format.masterClockHz);

    /* Waiting until finished. */
    while(!isFinished)
    {
        if((emptyBlock > 0U) && (cpy_index < MUSIC_LEN/BUFFER_SIZE))
        {
             /* Fill in the buffers. */
             memcpy((uint8_t *)&buffer[BUFFER_SIZE*(cpy_index%BUFFER_NUM)],(uint8_t *)&music[cpy_index*BUFFER_SIZE],sizeof(uint8_t)*BUFFER_SIZE); 
             emptyBlock--;
             cpy_index++;
        }
        if(emptyBlock < BUFFER_NUM)
        {
            /*  xfer structure */
            xfer.data = (uint8_t *)&buffer[BUFFER_SIZE*(tx_index%BUFFER_NUM)];
            xfer.dataSize = BUFFER_SIZE;  
            /* Wait for available queue. */
            if(kStatus_Success == SAI_TransferSendEDMA(DEMO_SAI, &txHandle, &xfer))
            {  
                tx_index++;
            }
        }
    }
    
    /* Once transfer finish, disable SAI instance. */
    SAI_TransferAbortSendEDMA(DEMO_SAI, &txHandle);
    SAI_Deinit(DEMO_SAI);
    PRINTF("\n\r SAI EDMA example finished!\n\r ");
    while (1)
    {
    }
}

#if defined(SAI_ErrorIRQHandler)
void SAI_ErrorIRQHandler(void)
{
    /* Clear the FIFO error flag */
    SAI_TxClearStatusFlags(DEMO_SAI, kSAI_FIFOErrorFlag);

    /* Reset FIFO */
    SAI_TxSoftwareReset(DEMO_SAI, kSAI_ResetTypeFIFO);
/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
  exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
#endif
