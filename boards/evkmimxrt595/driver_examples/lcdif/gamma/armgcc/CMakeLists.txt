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


project(lcdif_gamma)

set(MCUX_SDK_PROJECT_NAME lcdif_gamma.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../lcdif_gamma.c"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../../lcdif_support.h"
"${ProjDirPath}/../../lcdif_support.c"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/..
    ${ProjDirPath}/../..
)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../../devices/MIMXRT595S/drivers
    ${ProjDirPath}/../../../../../../components/video
    ${ProjDirPath}/../../../../../../components/video/display
    ${ProjDirPath}/../../../../../../components/video/display/rm68191
    ${ProjDirPath}/../../../../../../components/video/display/mipi_dsi_cmd
    ${ProjDirPath}/../../../../../../components/video/display/rm68200
    ${ProjDirPath}/../../../../../../devices/MIMXRT595S/utilities/debug_console_lite
    ${ProjDirPath}/../../../../../../components/video/display/hx8394
    ${ProjDirPath}/../../../../../../devices/MIMXRT595S
    ${ProjDirPath}/../../../../../../components/uart
    ${ProjDirPath}/../../../../../../components/lists
    ${ProjDirPath}/../../../../flash_config
    ${ProjDirPath}/../../../../../../CMSIS/Core/Include
    ${ProjDirPath}/../../../../../../devices/MIMXRT595S/utilities
)

# include modules
include(driver_clock_MIMXRT595S_cm33)

include(driver_power_MIMXRT595S_cm33)

include(driver_inputmux_MIMXRT595S_cm33)

include(driver_video-common_MIMXRT595S_cm33)

include(driver_display-common_MIMXRT595S_cm33)

include(driver_display-rm68191_MIMXRT595S_cm33)

include(driver_mipi_dsi_MIMXRT595S_cm33)

include(driver_display-mipi-dsi-cmd_MIMXRT595S_cm33)

include(driver_common_MIMXRT595S_cm33)

include(driver_lpc_gpio_MIMXRT595S_cm33)

include(driver_display-rm68200_MIMXRT595S_cm33)

include(utility_debug_console_lite_MIMXRT595S_cm33)

include(utility_assert_lite_MIMXRT595S_cm33)

include(driver_display-hx8394_MIMXRT595S_cm33)

include(driver_lcdif_MIMXRT595S_cm33)

include(device_MIMXRT595S_CMSIS_MIMXRT595S_cm33)

include(component_usart_adapter_MIMXRT595S_cm33)

include(driver_flexspi_MIMXRT595S_cm33)

include(driver_cache_cache64_MIMXRT595S_cm33)

include(component_lists_MIMXRT595S_cm33)

include(driver_flexcomm_usart_MIMXRT595S_cm33)

include(driver_flash_config_evkmimxrt595_MIMXRT595S_cm33)

include(device_MIMXRT595S_startup_MIMXRT595S_cm33)

include(driver_flexcomm_MIMXRT595S_cm33)

include(driver_lpc_iopctl_MIMXRT595S_cm33)

include(driver_reset_MIMXRT595S_cm33)

include(CMSIS_Include_core_cm_MIMXRT595S_cm33)

include(driver_inputmux_connections_MIMXRT595S_cm33)

include(driver_soc_mipi_dsi_MIMXRT595S_cm33)

include(utilities_misc_utilities_MIMXRT595S_cm33)

include(driver_iap_MIMXRT595S_cm33)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/sdk20-app.bin)

