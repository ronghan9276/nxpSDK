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


project(lpuart_9bit_interrupt_transfer)

set(MCUX_SDK_PROJECT_NAME lpuart_9bit_interrupt_transfer.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../lpuart_9bit_interrupt_transfer.c"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/..
)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../../devices/MIMXRT1015/utilities/debug_console_lite
    ${ProjDirPath}/../../../../../../devices/MIMXRT1015/drivers
    ${ProjDirPath}/../../../../../../devices/MIMXRT1015
    ${ProjDirPath}/../../../../../../components/uart
    ${ProjDirPath}/../../../../../../components/lists
    ${ProjDirPath}/../../../../../../devices/MIMXRT1015/xip
    ${ProjDirPath}/../../../../xip
    ${ProjDirPath}/../../../../../../CMSIS/Core/Include
    ${ProjDirPath}/../../../../../../devices/MIMXRT1015/utilities
)

# include modules
include(utility_debug_console_lite_MIMXRT1015)

include(utility_assert_lite_MIMXRT1015)

include(driver_lpuart_MIMXRT1015)

include(driver_clock_MIMXRT1015)

include(driver_common_MIMXRT1015)

include(device_MIMXRT1015_CMSIS_MIMXRT1015)

include(component_lpuart_adapter_MIMXRT1015)

include(component_lists_MIMXRT1015)

include(device_MIMXRT1015_startup_MIMXRT1015)

include(driver_iomuxc_MIMXRT1015)

include(driver_igpio_MIMXRT1015)

include(driver_xip_device_MIMXRT1015)

include(driver_xip_board_evkmimxrt1015_MIMXRT1015)

include(CMSIS_Include_core_cm_MIMXRT1015)

include(utilities_misc_utilities_MIMXRT1015)

include(device_MIMXRT1015_system_MIMXRT1015)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)


