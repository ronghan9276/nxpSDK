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


project(mbedtls_selftest)

set(MCUX_SDK_PROJECT_NAME mbedtls_selftest.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../selftest.c"
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

if(CMAKE_BUILD_TYPE STREQUAL debug)
     target_compile_definitions(${MCUX_SDK_PROJECT_NAME}  PRIVATE MBEDTLS_CONFIG_FILE="ksdk_mbedtls_config.h")
endif(CMAKE_BUILD_TYPE STREQUAL debug)

if(CMAKE_BUILD_TYPE STREQUAL release)
     target_compile_definitions(${MCUX_SDK_PROJECT_NAME}  PRIVATE MBEDTLS_CONFIG_FILE="ksdk_mbedtls_config.h")
endif(CMAKE_BUILD_TYPE STREQUAL release)

if(CMAKE_BUILD_TYPE STREQUAL flash_debug)
     target_compile_definitions(${MCUX_SDK_PROJECT_NAME}  PRIVATE MBEDTLS_CONFIG_FILE="ksdk_mbedtls_config.h")
endif(CMAKE_BUILD_TYPE STREQUAL flash_debug)

if(CMAKE_BUILD_TYPE STREQUAL flash_release)
     target_compile_definitions(${MCUX_SDK_PROJECT_NAME}  PRIVATE MBEDTLS_CONFIG_FILE="ksdk_mbedtls_config.h")
endif(CMAKE_BUILD_TYPE STREQUAL flash_release)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../devices/MIMXRT595S/drivers
    ${ProjDirPath}/../../../../../middleware/mbedtls
    ${ProjDirPath}/../../../../../devices/MIMXRT595S
    ${ProjDirPath}/../../../../../devices/MIMXRT595S/utilities
    ${ProjDirPath}/../../../../../components/uart
    ${ProjDirPath}/../../../../../components/serial_manager
    ${ProjDirPath}/../../../../../components/lists
    ${ProjDirPath}/../../../flash_config
    ${ProjDirPath}/../../../../../CMSIS/Core/Include
)

# include modules
include(driver_casper_MIMXRT595S_cm33)

include(driver_hashcrypt_MIMXRT595S_cm33)

include(driver_trng_MIMXRT595S_cm33)

include(middleware_mbedtls_MIMXRT595S_cm33)

include(middleware_mbedtls_port_ksdk_MIMXRT595S_cm33)

include(middleware_mbedtls_rt1_MIMXRT595S_cm33)

include(driver_common_MIMXRT595S_cm33)

include(driver_clock_MIMXRT595S_cm33)

include(driver_power_MIMXRT595S_cm33)

include(driver_reset_MIMXRT595S_cm33)

include(device_MIMXRT595S_CMSIS_MIMXRT595S_cm33)

include(utility_debug_console_MIMXRT595S_cm33)

include(utility_assert_MIMXRT595S_cm33)

include(component_usart_adapter_MIMXRT595S_cm33)

include(driver_flexspi_MIMXRT595S_cm33)

include(driver_cache_cache64_MIMXRT595S_cm33)

include(component_serial_manager_MIMXRT595S_cm33)

include(component_lists_MIMXRT595S_cm33)

include(component_serial_manager_uart_MIMXRT595S_cm33)

include(driver_flexcomm_usart_MIMXRT595S_cm33)

include(driver_flash_config_evkmimxrt595_MIMXRT595S_cm33)

include(device_MIMXRT595S_startup_MIMXRT595S_cm33)

include(driver_flexcomm_MIMXRT595S_cm33)

include(driver_lpc_iopctl_MIMXRT595S_cm33)

include(driver_lpc_gpio_MIMXRT595S_cm33)

include(CMSIS_Include_core_cm_MIMXRT595S_cm33)

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

