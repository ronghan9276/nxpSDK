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


project(flexio_spi_edma_lpspi_transfer_slave_dynamic)

set(MCUX_SDK_PROJECT_NAME flexio_spi_edma_lpspi_transfer_slave_dynamic.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../flexio_spi_slave_dynamic.c"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
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
    ${ProjDirPath}/../../../../../../../../devices/MIMXRT1052/utilities/debug_console_lite
    ${ProjDirPath}/../../../../../../../../devices/MIMXRT1052/drivers
    ${ProjDirPath}/../../../../../../../../devices/MIMXRT1052
    ${ProjDirPath}/../../../../../../../../components/uart
    ${ProjDirPath}/../../../../../../../../components/lists
    ${ProjDirPath}/../../../../../../../../devices/MIMXRT1052/xip
    ${ProjDirPath}/../../../../../../xip
    ${ProjDirPath}/../../../../../../../../components/silicon_id
    ${ProjDirPath}/../../../../../../../../CMSIS/Core/Include
    ${ProjDirPath}/../../../../../../../../devices/MIMXRT1052/utilities
)

# include modules
include(utility_debug_console_lite_MIMXRT1052)

include(utility_assert_lite_MIMXRT1052)

include(driver_dmamux_MIMXRT1052)

include(driver_edma_MIMXRT1052)

include(driver_clock_MIMXRT1052)

include(driver_flexio_MIMXRT1052)

include(driver_flexio_spi_MIMXRT1052)

include(driver_flexio_spi_edma_MIMXRT1052)

include(driver_lpspi_MIMXRT1052)

include(driver_lpspi_edma_MIMXRT1052)

include(driver_common_MIMXRT1052)

include(device_MIMXRT1052_CMSIS_MIMXRT1052)

include(component_lpuart_adapter_MIMXRT1052)

include(component_lists_MIMXRT1052)

include(driver_lpuart_MIMXRT1052)

include(device_MIMXRT1052_startup_MIMXRT1052)

include(driver_iomuxc_MIMXRT1052)

include(driver_igpio_MIMXRT1052)

include(driver_xip_device_MIMXRT1052)

include(driver_xip_board_evkbimxrt1050_MIMXRT1052)

include(component_silicon_id_MIMXRT1052)

include(CMSIS_Include_core_cm_MIMXRT1052)

include(utilities_misc_utilities_MIMXRT1052)

include(device_MIMXRT1052_system_MIMXRT1052)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)


