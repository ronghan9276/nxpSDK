# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 3.1.1)

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


project(sai)

set(MCUX_SDK_PROJECT_NAME sai.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../ffconf.h"
"${ProjDirPath}/../recordtoSdcard.c"
"${ProjDirPath}/../sdmmc_config.h"
"${ProjDirPath}/../sdmmc_config.c"
"${ProjDirPath}/../sai.h"
"${ProjDirPath}/../sai.c"
"${ProjDirPath}/../recordPlayback.c"
"${ProjDirPath}/../playbackSineWave.c"
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
    ${ProjDirPath}/../../../../../devices/MK66F18/drivers
    ${ProjDirPath}/../../../../../components/codec/da7212
    ${ProjDirPath}/../../../../../components/codec
    ${ProjDirPath}/../../../../../components/codec/port/da7212
    ${ProjDirPath}/../../../../../components/codec/i2c
    ${ProjDirPath}/../../../../../components/i2c
    ${ProjDirPath}/../../../../../middleware/fatfs
    ${ProjDirPath}/../../../../../CMSIS/DSP/Lib
    ${ProjDirPath}/../../../../../middleware/sdmmc
    ${ProjDirPath}/../../../../../devices/MK66F18/utilities/debug_console_lite
    ${ProjDirPath}/../../../../../devices/MK66F18
    ${ProjDirPath}/../../../../../components/uart
    ${ProjDirPath}/../../../../../components/lists
    ${ProjDirPath}/../../../../../CMSIS/Include
    ${ProjDirPath}/../../../../../components/osa
    ${ProjDirPath}/../../../../../devices/MK66F18/utilities
)

# include modules
include(driver_i2c_MK66F18)

include(driver_dialog7212_MK66F18)

include(driver_codec_MK66F18)

include(driver_common_MK66F18)

include(component_da7212_adapter_MK66F18)

include(component_codec_i2c_MK66F18)

include(component_i2c_adapter_MK66F18)

include(driver_sdhc_MK66F18)

include(middleware_fatfs_MK66F18)

include(middleware_fatfs_sd_MK66F18)

include(CMSIS_DSP_Lib_arm_cortexM4lf_math_MK66F18)

include(middleware_sdmmc_sd_MK66F18)

include(middleware_sdmmc_common_MK66F18)

include(middleware_sdmmc_host_sdhc_MK66F18)

include(middleware_sdmmc_host_sdhc_interrupt_MK66F18)

include(utility_debug_console_lite_MK66F18)

include(utility_assert_lite_MK66F18)

include(driver_port_MK66F18)

include(driver_gpio_MK66F18)

include(driver_clock_MK66F18)

include(driver_sai_MK66F18)

include(driver_sai_edma_MK66F18)

include(driver_dmamux_MK66F18)

include(driver_edma_MK66F18)

include(driver_sysmpu_MK66F18)

include(driver_flash_MK66F18)

include(device_MK66F18_CMSIS_MK66F18)

include(component_uart_adapter_MK66F18)

include(component_lists_MK66F18)

include(driver_uart_MK66F18)

include(device_MK66F18_startup_MK66F18)

include(driver_lpuart_MK66F18)

include(driver_smc_MK66F18)

include(CMSIS_Include_core_cm4_MK66F18)

include(CMSIS_Include_common_MK66F18)

include(CMSIS_Include_dsp_MK66F18)

include(middleware_sdmmc_osa_bm_MK66F18)

include(component_osa_bm_MK66F18)

include(utilities_misc_utilities_MK66F18)

include(device_MK66F18_system_MK66F18)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

if(CMAKE_BUILD_TYPE STREQUAL debug)
    target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${ProjDirPath}/../../../../../CMSIS/DSP/Lib/GCC/libarm_cortexM4lf_math.a)
endif()

if(CMAKE_BUILD_TYPE STREQUAL release)
    target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${ProjDirPath}/../../../../../CMSIS/DSP/Lib/GCC/libarm_cortexM4lf_math.a)
endif()

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)


