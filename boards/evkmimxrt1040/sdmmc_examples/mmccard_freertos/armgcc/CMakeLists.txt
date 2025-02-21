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


project(mmccard_freertos)

set(MCUX_SDK_PROJECT_NAME mmccard_freertos.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../mmccard_freertos.c"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../sdmmc_config.c"
"${ProjDirPath}/../sdmmc_config.h"
"${ProjDirPath}/../FreeRTOSConfig.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../dcd.c"
"${ProjDirPath}/../dcd.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/..
)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../devices/MIMXRT1042/drivers
    ${ProjDirPath}/../../../../../middleware/sdmmc
    ${ProjDirPath}/../../../../../components/gpio
    ${ProjDirPath}/../../../../../rtos/freertos/freertos_kernel
    ${ProjDirPath}/../../../../../devices/MIMXRT1042
    ${ProjDirPath}/../../../../../devices/MIMXRT1042/utilities
    ${ProjDirPath}/../../../../../components/uart
    ${ProjDirPath}/../../../../../components/serial_manager
    ${ProjDirPath}/../../../../../components/lists
    ${ProjDirPath}/../../../../../devices/MIMXRT1042/xip
    ${ProjDirPath}/../../../xip
    ${ProjDirPath}/../../../../../components/silicon_id
    ${ProjDirPath}/../../../../../CMSIS/Core/Include
    ${ProjDirPath}/../../../../../components/osa
)

# include modules
include(driver_igpio_MIMXRT1042)

include(driver_cache_armv7_m7_MIMXRT1042)

include(driver_usdhc_MIMXRT1042)

include(middleware_sdmmc_mmc_MIMXRT1042)

include(middleware_sdmmc_common_MIMXRT1042)

include(middleware_sdmmc_host_usdhc_MIMXRT1042)

include(middleware_sdmmc_host_usdhc_freertos_MIMXRT1042)

include(component_igpio_adapter_MIMXRT1042)

include(middleware_freertos-kernel_MIMXRT1042)

include(middleware_freertos-kernel_heap_4_MIMXRT1042)

include(driver_clock_MIMXRT1042)

include(driver_common_MIMXRT1042)

include(device_MIMXRT1042_CMSIS_MIMXRT1042)

include(utility_debug_console_MIMXRT1042)

include(component_lpuart_adapter_MIMXRT1042)

include(component_serial_manager_MIMXRT1042)

include(component_lists_MIMXRT1042)

include(component_serial_manager_uart_MIMXRT1042)

include(driver_lpuart_MIMXRT1042)

include(device_MIMXRT1042_startup_MIMXRT1042)

include(driver_iomuxc_MIMXRT1042)

include(utility_assert_MIMXRT1042)

include(driver_xip_device_MIMXRT1042)

include(driver_xip_board_evkmimxrt1040_MIMXRT1042)

include(component_silicon_id_MIMXRT1042)

include(CMSIS_Include_core_cm_MIMXRT1042)

include(middleware_sdmmc_osa_freertos_MIMXRT1042)

include(component_osa_free_rtos_MIMXRT1042)

include(middleware_freertos-kernel_extension_MIMXRT1042)

include(utilities_misc_utilities_MIMXRT1042)

include(device_MIMXRT1042_system_MIMXRT1042)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)


