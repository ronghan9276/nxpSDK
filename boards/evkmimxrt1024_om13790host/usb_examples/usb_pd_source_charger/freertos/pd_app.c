/*
 * Copyright 2016 - 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
/*${standard_header_anchor}*/
#include "usb_pd_config.h"
#include "usb_pd.h"
#include "usb_pd_i2c.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "pd_app.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "pd_power_interface.h"
#include "pd_board_config.h"
#include "pd_power_nx20p3483.h"
#include "fsl_adapter_timer.h"
#include "pin_mux.h"
#include "board.h"

#include "fsl_adapter_gpio.h"
#include "fsl_iomuxc.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if (PD_DEMO_PORTS_COUNT > PD_CONFIG_MAX_PORT)
#error "please increase the instance count"
#endif

#ifndef PD_TIMER_INSTANCE
#define PD_TIMER_INSTANCE (0)
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
uint32_t PD_DemoSoftTimer_msGet(void);
uint32_t PD_DemoSoftTimer_getInterval(uint32_t startTime);
uint32_t HW_I2CGetFreq(uint8_t i2cInstance);
void HW_I2CReleaseBus(void);
void PD_DemoInit(void);
void PD_DemoTaskFun(void);
void BOARD_InitHardware(void);
uint32_t HW_TimerGetFreq(void);
pd_status_t PD_PowerBoardReset(uint8_t port);
pd_status_t PD_DpmAppCommandCallback(void *callbackParam, uint32_t event, void *param);
void HW_TimerCallback(void *callbackParam);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static pd_source_pdo_t s_PortSourceCaps[] = {
    {
        /* PDO1: fixed supply: dual-role power; Externally Powered; no USB communication; dual-role data; 5V; 3A */
        .fixedPDO.dualRoleData    = 1U,
        .fixedPDO.dualRolePower   = 1U,
        .fixedPDO.externalPowered = 1U,
        .fixedPDO.fixedSupply     = kPDO_Fixed,
        .fixedPDO.maxCurrent      = (3U * 100U),
        .fixedPDO.peakCurrent     = 0U,
#if ((defined PD_CONFIG_REVISION) && (PD_CONFIG_REVISION >= PD_SPEC_REVISION_30))
        .fixedPDO.unchunkedSupported = 1U,
#endif
        .fixedPDO.usbCommunicationsCapable = 0U,
        .fixedPDO.usbSuspendSupported      = 0U,
        .fixedPDO.voltage                  = (5U * 1000U / 50U),
    },
    {
        /* PDO2: fixed Supply: 9V - 2A */
        .fixedPDO.fixedSupply = kPDO_Fixed,
        .fixedPDO.maxCurrent  = (2U * 100U),
        .fixedPDO.voltage     = (9 * 1000U / 50U),
    },
};

static pd_power_port_config_t s_PortPowerConfig = {
    (uint32_t *)&s_PortSourceCaps[0],                   /* source caps */
    NULL,                                               /* self sink caps */
    sizeof(s_PortSourceCaps) / sizeof(pd_source_pdo_t), /* source cap count */
    0,                                                  /* sink cap count */
    kPowerConfig_SourceOnly,                            /* typec role */
    PD_DEMO_TYPEC_CURRENT,                              /* source: Rp current level */
    kTypecTry_None,                                     /* drp try function */
    kDataConfig_DFP,                                    /* data function */
    1,                                                  /* support vconn */
    0,                                                  /* reserved */
    NULL,
    NULL,
    NULL,
};

#if (defined PD_DEMO_PORT1_ENABLE) && (PD_DEMO_PORT1_ENABLE)
static pd_phy_config_t s_Port1PhyConfig = {
    .i2cInstance   = kInterface_i2c0 + BOARD_PD_I2C_INDEX,
    .slaveAddress  = 0x52u,
    .i2cSrcClock   = 0u,
    .i2cReleaseBus = HW_I2CReleaseBus,
    .alertPort     = PD_PORT1_PHY_INTERRUPT_PORT,
    .alertPin      = PD_PORT1_PHY_INTERRUPT_PIN,
    .alertPriority = PD_PORT1_PHY_INTERRUPT_PRIORITY,
};

pd_instance_config_t g_Port1PDConfig = {
    kDeviceType_NormalPowerPort, /* normal power port */
    kPD_PhyPTN5110,
    &s_Port1PhyConfig,
    &s_PortPowerConfig,
};
#endif

pd_instance_config_t *g_PortsConfigArray[] = {
#if (defined PD_DEMO_PORT1_ENABLE) && (PD_DEMO_PORT1_ENABLE)
    &g_Port1PDConfig,
#endif
};

#if (defined PD_DEMO_PORT1_ENABLE) && (PD_DEMO_PORT1_ENABLE > 0)
pd_app_t g_PDAppInstancePort1;
#endif
#if (defined PD_DEMO_PORT2_ENABLE) && (PD_DEMO_PORT2_ENABLE > 0)
pd_app_t g_PDAppInstancePort2;
#endif
#if (defined PD_DEMO_PORT3_ENABLE) && (PD_DEMO_PORT3_ENABLE > 0)
pd_app_t g_PDAppInstancePort3;
#endif
#if (defined PD_DEMO_PORT4_ENABLE) && (PD_DEMO_PORT4_ENABLE > 0)
pd_app_t g_PDAppInstancePort4;
#endif

pd_app_t *g_PDAppInstanceArray[] = {
#if (defined PD_DEMO_PORT1_ENABLE) && (PD_DEMO_PORT1_ENABLE > 0)
    &g_PDAppInstancePort1,
#endif
#if (defined PD_DEMO_PORT2_ENABLE) && (PD_DEMO_PORT2_ENABLE > 0)
    &g_PDAppInstancePort2,
#endif
#if (defined PD_DEMO_PORT3_ENABLE) && (PD_DEMO_PORT3_ENABLE > 0)
    &g_PDAppInstancePort3,
#endif
#if (defined PD_DEMO_PORT4_ENABLE) && (PD_DEMO_PORT4_ENABLE > 0)
    &g_PDAppInstancePort4,
#endif
};

pd_power_handle_callback_t callbackFunctions = {
    PD_PowerSrcTurnOnDefaultVbus,
    PD_PowerSrcTurnOnRequestVbus,
    PD_PowerSrcTurnOffVbus,
    PD_PowerSrcGotoMinReducePower,
    NULL,
    NULL,
    NULL,
    NULL,
    PD_PowerControlVconn,
};
volatile uint32_t g_SoftTimerCount;
TIMER_HANDLE_DEFINE(g_PDTimerHandle);
/*******************************************************************************
 * Code
 ******************************************************************************/
#define I2C_RELEASE_BUS_COUNT 1000U
#define PD_I2C_SCL            (22U)
#define PD_I2C_SDA            (23U)
#define PD_I2C_PORT           (3)

/* Select USB1 PLL (480 MHz) as master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_DIVIDER (5U)
/* Get frequency of lpi2c clock */
#define LPI2C_CLOCK_FREQUENCY ((60000000U) / (LPI2C_CLOCK_SOURCE_DIVIDER + 1U))
/* Select IPG Clock as PERCLK_CLK clock source */
#define USBPD_GPT_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for PERCLK_CLK clock source */
#define USBPD_GPT_CLOCK_DIVIDER_SELECT (0U)
/* Get source clock for GPT driver (GPT prescaler = 0) */
#define USBPD_GPT_CLK_FREQ (CLOCK_GetFreq(kCLOCK_IpgClk) / (USBPD_GPT_CLOCK_DIVIDER_SELECT + 1U))


uint32_t HW_TimerGetFreq(void)
{
    return USBPD_GPT_CLK_FREQ;
}

uint32_t HW_I2CGetFreq(uint8_t instance)
{
    return LPI2C_CLOCK_FREQUENCY;
}

static void i2c_release_bus_delay(void)
{
    uint32_t i = 0;
    for (i = 0; i < I2C_RELEASE_BUS_COUNT; i++)
    {
        __NOP();
    }
}

void HW_I2CReleaseBus(void)
{
    hal_gpio_pin_config_t config;

    GPIO_HANDLE_DEFINE(pdI2cSclGpio);

    GPIO_HANDLE_DEFINE(pdI2cSdaGpio);

    uint8_t i = 0;

    /* Config pin mux as gpio */
    CLOCK_EnableClock(kCLOCK_Iomuxc); /* iomuxc clock (iomuxc_clk_enable): 0x03u */

    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_02_GPIO3_IO22, /* GPIO_SD_B1_02 is configured as GPIO3_IO22 */
                     0U); /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_03_GPIO3_IO23, /* GPIO_SD_B1_03 is configured as GPIO3_IO23 */
                     0U); /* Software Input On Field: Input Path is determined by functionality */

    /* Init I2C GPIO */

    config.direction = kHAL_GpioDirectionOut;

    config.port = PD_I2C_PORT;

    config.pin = PD_I2C_SCL;

    config.level = 1;

    HAL_GpioInit((hal_gpio_handle_t)pdI2cSclGpio, &config);

    config.pin = PD_I2C_SDA;

    HAL_GpioInit((hal_gpio_handle_t)pdI2cSdaGpio, &config);

    i2c_release_bus_delay();

    /* Drive SDA low first to simulate a start */
    HAL_GpioSetOutput((hal_gpio_handle_t)pdI2cSdaGpio, 0U);
    i2c_release_bus_delay();

    /* Send 9 pulses on SCL and keep SDA high */
    for (i = 0; i < 9; i++)
    {
        HAL_GpioSetOutput((hal_gpio_handle_t)pdI2cSclGpio, 0U);
        i2c_release_bus_delay();

        HAL_GpioSetOutput((hal_gpio_handle_t)pdI2cSdaGpio, 1U);
        i2c_release_bus_delay();

        HAL_GpioSetOutput((hal_gpio_handle_t)pdI2cSclGpio, 1U);
        i2c_release_bus_delay();
        i2c_release_bus_delay();
    }

    /* Send stop */
    HAL_GpioSetOutput((hal_gpio_handle_t)pdI2cSclGpio, 0U);
    i2c_release_bus_delay();

    HAL_GpioSetOutput((hal_gpio_handle_t)pdI2cSdaGpio, 0U);
    i2c_release_bus_delay();

    HAL_GpioSetOutput((hal_gpio_handle_t)pdI2cSclGpio, 1U);
    i2c_release_bus_delay();

    HAL_GpioSetOutput((hal_gpio_handle_t)pdI2cSdaGpio, 1U);
    i2c_release_bus_delay();
    /* De-init I2C GPIO */

    HAL_GpioDeinit((hal_gpio_handle_t)pdI2cSclGpio);

    HAL_GpioDeinit((hal_gpio_handle_t)pdI2cSdaGpio);

    /* re-configure pin mux as i2c */
    LPI2C4_InitPins();
}


static void PD_GpioInit(pd_app_t *pdAppInstance)
{
    pd_demo_io_init_t portsDemoPinConfigArray[] = {
#if (defined PD_DEMO_PORT1_ENABLE) && (PD_DEMO_PORT1_ENABLE)
        {
            .extraEnSrcPort = PD_PORT1_EXTRA_SRC_PORT,
            .extraEnSrcPin  = PD_PORT1_EXTRA_SRC_PIN,
        },
#endif
    };
    pd_demo_io_init_t *demoGpioPinConfig = &portsDemoPinConfigArray[pdAppInstance->portNumber - 1];
    hal_gpio_pin_config_t config;

    config.direction = kHAL_GpioDirectionOut;
    config.port      = demoGpioPinConfig->extraEnSrcPort;
    config.pin       = demoGpioPinConfig->extraEnSrcPin;
    config.level     = 1;
    HAL_GpioInit((hal_gpio_handle_t *)(&pdAppInstance->gpioExtraSrcHandle[0]), &config);
}

static pd_status_t PD_DpmConnectCallback(void *callbackParam, uint32_t event, void *param)
{
    pd_status_t status      = kStatus_PD_Error;
    pd_app_t *pdAppInstance = (pd_app_t *)callbackParam;

    switch (event)
    {
        case PD_DISCONNECTED:
            PD_PowerSrcTurnOffVbus(pdAppInstance, kVbusPower_Stable);
            PRINTF("port %d disconnect\r\n", pdAppInstance->portNumber);
            status = kStatus_PD_Success;
            break;

        case PD_CONNECT_ROLE_CHANGE:
        case PD_CONNECTED:
        {
            uint8_t roleInfo;

            PD_NX20PExitDeadBatteryMode(pdAppInstance->portNumber);
            PD_Control(pdAppInstance->pdHandle, PD_CONTROL_GET_POWER_ROLE, &roleInfo);
            if (roleInfo == kPD_PowerRoleSource)
            {
                PRINTF("port %d provide default 5V vbus\r\n", pdAppInstance->portNumber);
            }

            status = kStatus_PD_Success;
            break;
        }

        default:
            break;
    }

    return status;
}

static pd_status_t PD_DpmDemoAppCallback(void *callbackParam, uint32_t event, void *param)
{
    pd_status_t status      = kStatus_PD_Error;
    pd_app_t *pdAppInstance = (pd_app_t *)callbackParam;

    switch (event)
    {
        case PD_FUNCTION_DISABLED:
            /* need hard or software reset */
            status = kStatus_PD_Success;
            break;

        case PD_CONNECTED:
        case PD_CONNECT_ROLE_CHANGE:
        case PD_DISCONNECTED:
            status = PD_DpmConnectCallback(callbackParam, event, param);
            break;

        case PD_DPM_OVP_OCP_FAULT:
            PD_NX20PClearInt(pdAppInstance->portNumber);
            break;

        case PD_DPM_VBUS_ALARM:
            /* Users need to take care of this. Some corrective actions may be taken, such as disconnect
               or debounce time to turn off the power switch. It is up to the system power management. */
            break;

        default:
            status = PD_DpmAppCommandCallback(callbackParam, event, param);
            break;
    }
    return status;
}

static void PD_AppInit(void)
{
    uint8_t index;
    pd_app_t *pdAppInstance;
    pd_app_t *pdAppInstanceArray[] = {
#if (defined PD_DEMO_PORT1_ENABLE) && (PD_DEMO_PORT1_ENABLE > 0)
        &g_PDAppInstancePort1,
#else
        NULL,
#endif
#if (defined PD_DEMO_PORT2_ENABLE) && (PD_DEMO_PORT2_ENABLE > 0)
        &g_PDAppInstancePort2,
#else
        NULL,
#endif
#if (defined PD_DEMO_PORT3_ENABLE) && (PD_DEMO_PORT3_ENABLE > 0)
        &g_PDAppInstancePort3,
#else
        NULL,
#endif
#if (defined PD_DEMO_PORT4_ENABLE) && (PD_DEMO_PORT4_ENABLE > 0)
        &g_PDAppInstancePort4,
#else
        NULL,
#endif
    };

    g_SoftTimerCount = 0;
    for (index = 0; index < 4; ++index)
    {
        if (pdAppInstanceArray[index] != NULL)
        {
            pdAppInstanceArray[index]->portNumber = (index + 1);
        }
    }

    for (index = 0; index < PD_DEMO_PORTS_COUNT; ++index)
    {
        pdAppInstance                = g_PDAppInstanceArray[index];
        pdAppInstance->pdHandle      = NULL;
        pdAppInstance->pdConfigParam = g_PortsConfigArray[index];
        ((pd_phy_config_t *)pdAppInstance->pdConfigParam->phyConfig)->i2cSrcClock =
            HW_I2CGetFreq(((pd_phy_config_t *)pdAppInstance->pdConfigParam->phyConfig)->i2cInstance);
        if (PD_InstanceInit(&pdAppInstance->pdHandle, PD_DpmDemoAppCallback, &callbackFunctions, pdAppInstance,
                            g_PortsConfigArray[index]) != kStatus_PD_Success)
        {
            PRINTF("pd port %d init fail\r\n", pdAppInstance->portNumber);
        }
        else
        {
            PD_GpioInit(pdAppInstance);
            PD_PowerBoardControlInit(pdAppInstance->portNumber, pdAppInstance->pdHandle,
                                     (hal_gpio_handle_t)(&pdAppInstance->gpioExtraSrcHandle[0]));

            pdAppInstance->msgSop = kPD_MsgSOP;
            PRINTF("pd port %d init success\r\n", pdAppInstance->portNumber);
        }
    }
}

/* ms */
uint32_t PD_DemoSoftTimer_msGet(void)
{
    return g_SoftTimerCount;
}

/* ms */
uint32_t PD_DemoSoftTimer_getInterval(uint32_t startTime)
{
    if (g_SoftTimerCount >= startTime)
    {
        return (g_SoftTimerCount - startTime);
    }
    else
    {
        return (0xFFFFFFFFu - (startTime - g_SoftTimerCount));
    }
}

void HW_TimerCallback(void *callbackParam)
{
    /* Callback into timer service */
    uint8_t index;
    for (index = 0; index < PD_DEMO_PORTS_COUNT; ++index)
    {
        PD_TimerIsrFunction(g_PDAppInstanceArray[index]->pdHandle);
    }
    g_SoftTimerCount++;
}

static void PD_AppTimerInit(void)
{
    hal_timer_config_t halTimerConfig;
    halTimerConfig.timeout     = 1000;
    halTimerConfig.srcClock_Hz = HW_TimerGetFreq();
    halTimerConfig.instance    = PD_TIMER_INSTANCE;
    HAL_TimerInit((hal_timer_handle_t)&g_PDTimerHandle[0], &halTimerConfig);

    HAL_TimerInstallCallback((hal_timer_handle_t)&g_PDTimerHandle[0], HW_TimerCallback, NULL);
    HAL_TimerEnable((hal_timer_handle_t)&g_PDTimerHandle[0]);
}

#if (defined PD_CONFIG_COMMON_TASK) && (PD_CONFIG_COMMON_TASK)
void PD_PortsTask(void *arg)
{
    while (1)
    {
        PD_Task();
    }
}
#else
void PD_PortTask(void *arg)
{
    pd_app_t *pdAppInstance = (pd_app_t *)arg;
    while (1)
    {
        PD_InstanceTask(pdAppInstance->pdHandle);
    }
}
#endif

static void pd_demo_task(void *arg)
{
    /* @TEST_ANCHOR */
    PD_AppTimerInit();
    PD_AppInit();
    PD_DemoInit();

#if (defined PD_CONFIG_COMMON_TASK) && (PD_CONFIG_COMMON_TASK)
    if (xTaskCreate(PD_PortsTask, "PD", (2048u + 512u) / sizeof(portSTACK_TYPE), NULL, 5, NULL) != pdPASS)
    {
        PRINTF("create task error\r\n");
    }
#else
    for (uint8_t index = 0; index < PD_DEMO_PORTS_COUNT; ++index)
    {
        if (xTaskCreate(PD_PortTask, "port", (2048u + 512u) / sizeof(portSTACK_TYPE), g_PDAppInstanceArray[index], 5,
                        NULL) != pdPASS)
        {
            PRINTF("create task error\r\n");
        }
    }
#endif

    vTaskDelete(NULL);
}

int main(void)
{
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    HW_I2CReleaseBus();
    BOARD_InitDebugConsole();
    NVIC_SetPriority(BOARD_UART_IRQ, 5);
    CLOCK_SetMux(kCLOCK_Lpi2cMux, LPI2C_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, LPI2C_CLOCK_SOURCE_DIVIDER);
    /*Clock setting for GPT*/
    CLOCK_SetMux(kCLOCK_PerclkMux, USBPD_GPT_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_PerclkDiv, USBPD_GPT_CLOCK_DIVIDER_SELECT);
    LPI2C4_InitPins();

    if (xTaskCreate(pd_demo_task, "demo", (1024u + 512u) / sizeof(portSTACK_TYPE), NULL, 4, NULL) != pdPASS)
    {
        PRINTF("create demo task error\r\n");
    }

    vTaskStartScheduler();

    while (1)
    {
        ;
    }
}
