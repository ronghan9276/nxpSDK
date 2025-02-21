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


project(tensorflow_lite_micro_cifar10_fusionf1_cm33)

set(MCUX_SDK_PROJECT_NAME tensorflow_lite_micro_cifar10_fusionf1_cm33.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../board_init.h"
"${ProjDirPath}/../incbin.S"
"${ProjDirPath}/../dsp_config.h"
"${ProjDirPath}/../main.c"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../board_init.c"
"${ProjDirPath}/../dsp_support.c"
"${ProjDirPath}/../dsp_support.h"
"${ProjDirPath}/../../fusionf1/binary/dsp_reset_release.bin"
"${ProjDirPath}/../../fusionf1/binary/dsp_text_release.bin"
"${ProjDirPath}/../../fusionf1/binary/dsp_data_release.bin"
"${ProjDirPath}/../pmic_support.c"
"${ProjDirPath}/../pmic_support.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/../../fusionf1/binary
    ${ProjDirPath}/..
)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../../components/lists
    ${ProjDirPath}/../../../../../../devices/MIMXRT595S/drivers
    ${ProjDirPath}/../../../../../../components/uart
    ${ProjDirPath}/../../../../../../devices/MIMXRT595S
    ${ProjDirPath}/../../../../flash_config
    ${ProjDirPath}/../../../../../../components/pca9420
    ${ProjDirPath}/../../../../../../devices/MIMXRT595S/utilities/debug_console_lite
    ${ProjDirPath}/../../../../../../devices/MIMXRT595S/utilities
    ${ProjDirPath}/../../../../../../CMSIS/Core/Include
)

# include modules
include(component_lists_MIMXRT595S_cm33)

include(driver_common_MIMXRT595S_cm33)

include(component_usart_adapter_MIMXRT595S_cm33)

include(driver_flexcomm_usart_MIMXRT595S_cm33)

include(device_MIMXRT595S_CMSIS_MIMXRT595S_cm33)

include(device_MIMXRT595S_startup_MIMXRT595S_cm33)

include(driver_cache_cache64_MIMXRT595S_cm33)

include(driver_clock_MIMXRT595S_cm33)

include(driver_dsp_MIMXRT595S_cm33)

include(driver_flash_config_evkmimxrt595_MIMXRT595S_cm33)

include(driver_flexcomm_MIMXRT595S_cm33)

include(driver_flexcomm_i2c_MIMXRT595S_cm33)

include(driver_flexspi_MIMXRT595S_cm33)

include(driver_inputmux_MIMXRT595S_cm33)

include(driver_lpc_gpio_MIMXRT595S_cm33)

include(driver_lpc_iopctl_MIMXRT595S_cm33)

include(driver_pca9420_MIMXRT595S_cm33)

include(driver_power_MIMXRT595S_cm33)

include(driver_reset_MIMXRT595S_cm33)

include(utility_debug_console_lite_MIMXRT595S_cm33)

include(utility_assert_lite_MIMXRT595S_cm33)

include(utilities_misc_utilities_MIMXRT595S_cm33)

include(CMSIS_Include_core_cm_MIMXRT595S_cm33)

include(driver_iap_MIMXRT595S_cm33)

include(driver_inputmux_connections_MIMXRT595S_cm33)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)


