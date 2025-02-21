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


project(tfm_regression_ns)

set(MCUX_SDK_PROJECT_NAME tfm_regression_ns.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../../../../../../middleware/tfm/tf-m/platform/ext/target/nxp/mimxrt685audevk/Device/Source/armgcc/startup_MIMXRT685S_cm33_ns.S"
"${ProjDirPath}/../../../../../../devices/MIMXRT685S/system_MIMXRT685S_cm33.c"
"${ProjDirPath}/../../../../../../devices/MIMXRT685S/system_MIMXRT685S_cm33.h"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../hardware_init.c"
"${ProjDirPath}/../app.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/../../../../../../devices/MIMXRT685S
    ${ProjDirPath}/..
)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} PRE_BUILD COMMAND
${TOOLCHAIN_DIR}/bin/arm-none-eabi-gcc -E -P -xc -I${ProjDirPath}/../../../../../../middleware/tfm/tf-m/platform/ext/target/nxp/mimxrt685audevk/partition ${ProjDirPath}/../../../../../../middleware/tfm/tf-m/platform/ext/target/nxp/common/armgcc/tfm_common_ns.ld -o ${ProjDirPath}/../../../../../../middleware/tfm/tf-m/platform/ext/target/nxp/common/armgcc/tfm_common_ns_pre.ld
)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../../devices/MIMXRT685S/drivers
    ${ProjDirPath}/../../../../../../middleware/tfm/tf-m
    ${ProjDirPath}/../../../../../../middleware/tfm/tf-m-tests
    ${ProjDirPath}/../../../../../../devices/MIMXRT685S
    ${ProjDirPath}/../../../../../../devices/MIMXRT685S/utilities
    ${ProjDirPath}/../../../../../../components/uart
    ${ProjDirPath}/../../../../flash_config
    ${ProjDirPath}/../../../../../../components/serial_manager
    ${ProjDirPath}/../../../../../../components/lists
    ${ProjDirPath}/../../../../../../CMSIS/Core/Include
    ${ProjDirPath}/../../../../../../CMSIS/RTOS2/RTX/Library
    ${ProjDirPath}/../../../../../../CMSIS/RTOS2
    ${ProjDirPath}/../../../../../../CMSIS/RTOS2/Include
)

# include modules
include(driver_ctimer_MIMXRT685S_cm33)

include(middleware_tfm_ns_mimxrt685audevk_MIMXRT685S_cm33)

include(middleware_tfm_ns_test_MIMXRT685S_cm33)

include(middleware_tfm_ns_test_s_MIMXRT685S_cm33)

include(middleware_tfm_ns_test_its_MIMXRT685S_cm33)

include(middleware_tfm_ns_test_ps_MIMXRT685S_cm33)

include(middleware_tfm_ns_test_platform_MIMXRT685S_cm33)

include(middleware_tfm_ns_test_attestation_MIMXRT685S_cm33)

include(middleware_tfm_ns_test_crypto_MIMXRT685S_cm33)

include(middleware_tfm_ns_test_qcbor_MIMXRT685S_cm33)

include(middleware_tfm_ns_test_ipc_MIMXRT685S_cm33)

include(middleware_tfm_ns_ipc_api_MIMXRT685S_cm33)

include(middleware_tfm_ns_test_core_MIMXRT685S_cm33)

include(driver_common_MIMXRT685S_cm33)

include(driver_clock_MIMXRT685S_cm33)

include(driver_power_MIMXRT685S_cm33)

include(driver_reset_MIMXRT685S_cm33)

include(device_MIMXRT685S_CMSIS_MIMXRT685S_cm33)

include(utility_debug_console_MIMXRT685S_cm33)

include(utility_assert_MIMXRT685S_cm33)

include(component_usart_adapter_MIMXRT685S_cm33)

include(driver_flash_config_mimxrt685audevk_MIMXRT685S_cm33)

include(driver_flexspi_MIMXRT685S_cm33)

include(driver_cache_cache64_MIMXRT685S_cm33)

include(component_serial_manager_MIMXRT685S_cm33)

include(component_lists_MIMXRT685S_cm33)

include(component_serial_manager_uart_MIMXRT685S_cm33)

include(driver_flexcomm_usart_MIMXRT685S_cm33)

include(driver_flexcomm_MIMXRT685S_cm33)

include(driver_lpc_iopctl_MIMXRT685S_cm33)

include(driver_lpc_gpio_MIMXRT685S_cm33)

include(CMSIS_Include_core_cm_MIMXRT685S_cm33)

include(middleware_tfm_ns_MIMXRT685S_cm33)

include(middleware_tfmtests_ns_MIMXRT685S_cm33)

include(CMSIS_RTOS2_NonSecure_MIMXRT685S_cm33)

include(CMSIS_RTOS2_Common_MIMXRT685S_cm33)

include(CMSIS_Device_API_OSTick_MIMXRT685S_cm33)

include(CMSIS_Device_API_RTOS2_MIMXRT685S_cm33)

include(middleware_tfm_memory_utils_MIMXRT685S_cm33)

include(middleware_tfm_t_cose_sign1_verify_MIMXRT685S_cm33)

include(middleware_tfmtests_ns_test_attestation_MIMXRT685S_cm33)

include(middleware_tfm_platform_test_MIMXRT685S_cm33)

include(utilities_misc_utilities_MIMXRT685S_cm33)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

if(CMAKE_BUILD_TYPE STREQUAL debug)
    target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${ProjDirPath}/../../tfm_regression_s/armgcc/${CMAKE_BUILD_TYPE}/tfm_regression_s_CMSE_Lib.o)
endif(CMAKE_BUILD_TYPE STREQUAL debug)

if(CMAKE_BUILD_TYPE STREQUAL debug)
    target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${ProjDirPath}/../../../../../../CMSIS/RTOS2/RTX/Library/GCC/libRTX_V8MMFN.a)
endif(CMAKE_BUILD_TYPE STREQUAL debug)

if(CMAKE_BUILD_TYPE STREQUAL release)
    target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${ProjDirPath}/../../tfm_regression_s/armgcc/${CMAKE_BUILD_TYPE}/tfm_regression_s_CMSE_Lib.o)
endif(CMAKE_BUILD_TYPE STREQUAL release)

if(CMAKE_BUILD_TYPE STREQUAL release)
    target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${ProjDirPath}/../../../../../../CMSIS/RTOS2/RTX/Library/GCC/libRTX_V8MMFN.a)
endif(CMAKE_BUILD_TYPE STREQUAL release)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/sdk20-app.bin)

