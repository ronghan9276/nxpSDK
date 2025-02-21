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


project(usb_pd_bm)

set(MCUX_SDK_PROJECT_NAME usb_pd_bm.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../pd_board_config.h"
"${ProjDirPath}/../pd_app_demo.c"
"${ProjDirPath}/../pd_app.c"
"${ProjDirPath}/../pd_app.h"
"${ProjDirPath}/../pd_command_app.c"
"${ProjDirPath}/../pd_command_interface.c"
"${ProjDirPath}/../pd_command_interface.h"
"${ProjDirPath}/../pd_power_app.c"
"${ProjDirPath}/../pd_power_interface.c"
"${ProjDirPath}/../pd_power_interface.h"
"${ProjDirPath}/../usb_pd_config.h"
"${ProjDirPath}/../pd_power_nx20p3483.c"
"${ProjDirPath}/../pd_power_nx20p3483.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../dcd.c"
"${ProjDirPath}/../dcd.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/..
)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../../devices/MIMXRT1021/drivers
    ${ProjDirPath}/../../../../../../components/i2c
    ${ProjDirPath}/../../../../../../middleware/usb
    ${ProjDirPath}/../../../../../../middleware
    ${ProjDirPath}/../../../../../../components/osa
    ${ProjDirPath}/../../../../../../devices/MIMXRT1021
    ${ProjDirPath}/../../../../../../devices/MIMXRT1021/utilities
    ${ProjDirPath}/../../../../../../devices/MIMXRT1021/xip
    ${ProjDirPath}/../../../../../evkmimxrt1020/xip
    ${ProjDirPath}/../../../../../../components/uart
    ${ProjDirPath}/../../../../../../components/serial_manager
    ${ProjDirPath}/../../../../../../components/lists
    ${ProjDirPath}/../../../../../../components/gpio
    ${ProjDirPath}/../../../../../../components/timer
    ${ProjDirPath}/../../../../../../CMSIS/Core/Include
)

# include modules
include(driver_igpio_MIMXRT1021)

include(driver_gpt_MIMXRT1021)

include(driver_lpi2c_MIMXRT1021)

include(driver_lpi2c_edma_MIMXRT1021)

include(driver_edma_MIMXRT1021)

include(driver_dmamux_MIMXRT1021)

include(component_lpi2c_adapter_MIMXRT1021)

include(middleware_usb_pd_phy_ptn5110_MIMXRT1021)

include(middleware_baremetal_MIMXRT1021)

include(middleware_usb_pd_MIMXRT1021)

include(component_osa_bm_MIMXRT1021)

include(driver_clock_MIMXRT1021)

include(driver_common_MIMXRT1021)

include(device_MIMXRT1021_CMSIS_MIMXRT1021)

include(device_MIMXRT1021_startup_MIMXRT1021)

include(driver_lpuart_MIMXRT1021)

include(driver_iomuxc_MIMXRT1021)

include(utility_assert_MIMXRT1021)

include(driver_xip_device_MIMXRT1021)

include(driver_xip_board_evkmimxrt1020_MIMXRT1021)

include(utility_debug_console_MIMXRT1021)

include(component_lpuart_adapter_MIMXRT1021)

include(component_serial_manager_MIMXRT1021)

include(component_lists_MIMXRT1021)

include(component_serial_manager_uart_MIMXRT1021)

include(component_igpio_adapter_MIMXRT1021)

include(component_gpt_adapter_MIMXRT1021)

include(CMSIS_Include_core_cm_MIMXRT1021)

include(component_osa_MIMXRT1021)

include(middleware_usb_common_header_MIMXRT1021)

include(utilities_misc_utilities_MIMXRT1021)

include(device_MIMXRT1021_system_MIMXRT1021)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)


