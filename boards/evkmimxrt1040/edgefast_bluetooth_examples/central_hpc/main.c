/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"

#include "FreeRTOS.h"
#include "task.h"

#include "central_hpc.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_adapter_uart.h"
#include "controller.h"
#include "usb_host_config.h"
#include "usb_phy.h"
#include "usb_host.h"
#include "fsl_lpuart_edma.h"
#include "fsl_dmamux.h"
#if (((defined(CONFIG_BT_SMP)) && (CONFIG_BT_SMP)))
#include "ksdk_mbedtls.h"
#endif /* CONFIG_BT_SMP */
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if defined(__GIC_PRIO_BITS)
#define USB_HOST_INTERRUPT_PRIORITY (25U)
#elif defined(__NVIC_PRIO_BITS) && (__NVIC_PRIO_BITS >= 3)
#define USB_HOST_INTERRUPT_PRIORITY (6U)
#else
#define USB_HOST_INTERRUPT_PRIORITY (3U)
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern void BOARD_InitHardware(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/
static void flexspi_clock_init(void)
{
#if defined(XIP_EXTERNAL_FLASH) && (XIP_EXTERNAL_FLASH == 1)
    CLOCK_SetMux(kCLOCK_FlexspiMux, 0x2); /* Choose PLL2 PFD2 clock as flexspi source clock. 396M */
    CLOCK_SetDiv(kCLOCK_FlexspiDiv, 2);   /* flexspi clock 133M. */
#else
    const clock_usb_pll_config_t g_ccmConfigUsbPll = {.loopDivider = 0U};
    CLOCK_InitUsb1Pll(&g_ccmConfigUsbPll);
    CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 24);   /* Set PLL3 PFD0 clock 360MHZ. */
    CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); /* Choose PLL3 PFD0 clock as flexspi source clock. */
    CLOCK_SetDiv(kCLOCK_FlexspiDiv, 2);   /* flexspi clock 120M. */
#endif
}


#if (defined(WIFI_88W8987_BOARD_MURATA_1ZM_M2) || defined(WIFI_IW416_BOARD_MURATA_1XK_M2))
int controller_hci_uart_get_configuration(controller_hci_uart_config_t *config)
{
    if (NULL == config)
    {
        return -1;
    }
    config->clockSrc        = BOARD_BT_UART_CLK_FREQ;
    config->defaultBaudrate = 115200u;
    config->runningBaudrate = BOARD_BT_UART_BAUDRATE;
    config->instance        = BOARD_BT_UART_INSTANCE;
    config->enableRxRTS     = 1u;
    config->enableTxCTS     = 1u;
#if (defined(HAL_UART_DMA_ENABLE) && (HAL_UART_DMA_ENABLE > 0U))
    config->dma_instance     = 0U;
    config->rx_channel       = 0U;
    config->tx_channel       = 1U;
    config->dma_mux_instance = 0U;
    config->rx_request       = kDmaRequestMuxLPUART3Rx;
    config->tx_request       = kDmaRequestMuxLPUART3Tx;
#endif
    return 0;
}
#elif defined(WIFI_BOARD_AW_AM457)

#else
#endif
#if (defined(CONFIG_BT_SNOOP) && (CONFIG_BT_SNOOP > 0))
void USB_HostClockInit(void)
{
    usb_phy_config_struct_t phyConfig = {
        BOARD_USB_PHY_D_CAL,
        BOARD_USB_PHY_TXCAL45DP,
        BOARD_USB_PHY_TXCAL45DM,
    };

    if (CONTROLLER_ID == kUSB_ControllerEhci0)
    {
        CLOCK_EnableUsbhs0PhyPllClock(kCLOCK_Usbphy480M, 480000000U);
        CLOCK_EnableUsbhs0Clock(kCLOCK_Usb480M, 480000000U);
    }

    USB_EhciPhyInit(CONTROLLER_ID, BOARD_XTAL0_CLK_HZ, &phyConfig);
}

void USB_HostIsrEnable(void)
{
    uint8_t irqNumber;

    uint8_t usbHOSTEhciIrq[] = USBHS_IRQS;
    irqNumber                = usbHOSTEhciIrq[CONTROLLER_ID - kUSB_ControllerEhci0];

/* Install isr, set priority, and enable IRQ. */
#if defined(__GIC_PRIO_BITS)
    GIC_SetPriority((IRQn_Type)irqNumber, USB_HOST_INTERRUPT_PRIORITY);
#else
    NVIC_SetPriority((IRQn_Type)irqNumber, USB_HOST_INTERRUPT_PRIORITY);
#endif
    EnableIRQ((IRQn_Type)irqNumber);
}
#endif

int main(void)
{
    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
    SCB_DisableDCache();
#if (defined(HAL_UART_DMA_ENABLE) && (HAL_UART_DMA_ENABLE > 0U))
    DMAMUX_Type *dmaMuxBases[] = DMAMUX_BASE_PTRS;
    edma_config_t config;
    DMA_Type *dmaBases[] = DMA_BASE_PTRS;
    DMAMUX_Init(dmaMuxBases[0]);
    EDMA_GetDefaultConfig(&config);
    EDMA_Init(dmaBases[0], &config);
#endif
    /*flexspi flash clock*/
    CLOCK_SetMux(kCLOCK_FlexspiMux, 0x2); /* Choose PLL2 PFD2 clock as flexspi source clock. 396M */
    CLOCK_SetDiv(kCLOCK_FlexspiDiv, 2);   /* flexspi clock 133M. */

#if (((defined(CONFIG_BT_SMP)) && (CONFIG_BT_SMP)))
    CRYPTO_InitHardware();
#endif /* CONFIG_BT_SMP */
    flexspi_clock_init();

    if (xTaskCreate(central_hpc_task, "central_hpc_task", configMINIMAL_STACK_SIZE * 8, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
    {
        PRINTF("central hpc task creation failed!\r\n");
        while (1)
            ;
    }

    vTaskStartScheduler();
    for (;;)
        ;
}

void *pvPortCalloc(size_t xNum, size_t xSize)
{
    void *pvReturn;

    pvReturn = pvPortMalloc(xNum * xSize);
    if (pvReturn != NULL)
    {
        memset(pvReturn, 0x00, xNum * xSize);
    }

    return pvReturn;
}
