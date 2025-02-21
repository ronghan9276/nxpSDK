# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 3.10.0)

# THE VERSION NUMBER
SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 0)

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})
SET(LIBRARY_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})


project(lwip_httpssrv_ota_wifi)

set(MCUX_SDK_PROJECT_NAME lwip_httpssrv_ota_wifi.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../app_config.h"
"${ProjDirPath}/../lwip_httpssrv_ota.c"
"${ProjDirPath}/../network_cfg.h"
"${ProjDirPath}/../init_wifi.c"
"${ProjDirPath}/../wpl.h"
"${ProjDirPath}/../wpl_nxp.c"
"${ProjDirPath}/../lwipopts.h"
"${ProjDirPath}/../httpsrv_fs_data.c"
"${ProjDirPath}/../mbedtls_config.h"
"${ProjDirPath}/../FreeRTOSConfig.h"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../wifi_config.h"
"${ProjDirPath}/../mcuboot_app_support.c"
"${ProjDirPath}/../mcuboot_app_support.h"
"${ProjDirPath}/../flash_partitioning.h"
"${ProjDirPath}/../sdmmc_config.c"
"${ProjDirPath}/../sdmmc_config.h"
"${ProjDirPath}/../wifi_bt_config.c"
"${ProjDirPath}/../wifi_bt_config.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../dcd.c"
"${ProjDirPath}/../dcd.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/..
    ${ProjDirPath}/../../..
)

if(CMAKE_BUILD_TYPE STREQUAL flexspi_nor_debug)
     target_compile_definitions(${MCUX_SDK_PROJECT_NAME}  PRIVATE MBEDTLS_CONFIG_FILE="mbedtls_config.h")
endif(CMAKE_BUILD_TYPE STREQUAL flexspi_nor_debug)

if(CMAKE_BUILD_TYPE STREQUAL flexspi_nor_release)
     target_compile_definitions(${MCUX_SDK_PROJECT_NAME}  PRIVATE MBEDTLS_CONFIG_FILE="mbedtls_config.h")
endif(CMAKE_BUILD_TYPE STREQUAL flexspi_nor_release)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../devices/MIMXRT1042/drivers
    ${ProjDirPath}/../../../../../components/flash/mflash/mimxrt1042
    ${ProjDirPath}/../../../../../middleware/mbedtls
    ${ProjDirPath}/../../../../../middleware/wifi_nxp
    ${ProjDirPath}/../../../../../rtos/freertos/freertos_kernel
    ${ProjDirPath}/../../../../../devices/MIMXRT1042/utilities
    ${ProjDirPath}/../../../../../middleware/sdmmc
    ${ProjDirPath}/../../../../../components/gpio
    ${ProjDirPath}/../../../../../middleware/lwip
    ${ProjDirPath}/../../../../../devices/MIMXRT1042
    ${ProjDirPath}/../../../../../components/uart
    ${ProjDirPath}/../../../../../components/serial_manager
    ${ProjDirPath}/../../../../../components/lists
    ${ProjDirPath}/../../../../../components/silicon_id
    ${ProjDirPath}/../../../../../CMSIS/Core/Include
    ${ProjDirPath}/../../../../../components/flash/mflash
    ${ProjDirPath}/../../../../../components/osa
    ${ProjDirPath}/../../../../../components/wifi_bt_module
)

# include modules
include(driver_trng_MIMXRT1042)

include(driver_dcp_MIMXRT1042)

include(driver_cache_armv7_m7_MIMXRT1042)

include(driver_flexspi_MIMXRT1042)

include(component_mflash_rt1040_MIMXRT1042)

include(middleware_mbedtls_MIMXRT1042)

include(middleware_mbedtls_port_ksdk_MIMXRT1042)

include(middleware_mbedtls_rt_MIMXRT1042)

include(middleware_wifi_wifidriver_MIMXRT1042)

include(middleware_freertos-kernel_MIMXRT1042)

include(utility_debug_console_MIMXRT1042)

include(middleware_wifi_sdio_MIMXRT1042)

include(middleware_wifi_fwdnld_MIMXRT1042)

include(middleware_sdmmc_sdio_MIMXRT1042)

include(middleware_sdmmc_common_MIMXRT1042)

include(middleware_sdmmc_host_usdhc_MIMXRT1042)

include(middleware_sdmmc_host_usdhc_freertos_MIMXRT1042)

include(component_igpio_adapter_MIMXRT1042)

include(middleware_lwip_apps_httpssrv_MIMXRT1042)

include(driver_clock_MIMXRT1042)

include(middleware_freertos-kernel_heap_3_MIMXRT1042)

include(middleware_lwip_MIMXRT1042)

include(middleware_wifi_MIMXRT1042)

include(driver_common_MIMXRT1042)

include(device_MIMXRT1042_CMSIS_MIMXRT1042)

include(component_lpuart_adapter_MIMXRT1042)

include(component_serial_manager_MIMXRT1042)

include(component_lists_MIMXRT1042)

include(component_serial_manager_uart_MIMXRT1042)

include(driver_lpuart_MIMXRT1042)

include(device_MIMXRT1042_startup_MIMXRT1042)

include(driver_iomuxc_MIMXRT1042)

include(utility_assert_MIMXRT1042)

include(driver_igpio_MIMXRT1042)

include(component_silicon_id_MIMXRT1042)

include(CMSIS_Include_core_cm_MIMXRT1042)

include(component_mflash_common_MIMXRT1042)

include(middleware_freertos-kernel_extension_MIMXRT1042)

include(middleware_wifi_sdio-2_MIMXRT1042)

include(middleware_sdmmc_osa_freertos_MIMXRT1042)

include(component_osa_free_rtos_MIMXRT1042)

include(driver_usdhc_MIMXRT1042)

include(component_wifi_bt_module_tx_pwr_limits_MIMXRT1042)

include(middleware_lwip_apps_httpsrv_MIMXRT1042)

include(utilities_misc_utilities_MIMXRT1042)

include(device_MIMXRT1042_system_MIMXRT1042)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/lwip_httpssrv_ota.bin)

