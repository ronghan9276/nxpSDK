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


project(aws_tests_wifi_nxp_cm4)

set(MCUX_SDK_PROJECT_NAME aws_tests_wifi_nxp_cm4.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../../application_code/cm4/main.c"
"${ProjDirPath}/../app_config.h"
"${ProjDirPath}/../sdmmc_config.c"
"${ProjDirPath}/../sdmmc_config.h"
"${ProjDirPath}/../wifi_bt_config.c"
"${ProjDirPath}/../wifi_bt_config.h"
"${ProjDirPath}/../config_files/aws_ggd_config.h"
"${ProjDirPath}/../config_files/aws_mbedtls_config.h"
"${ProjDirPath}/../config_files/aws_test_runner_config.h"
"${ProjDirPath}/../config_files/aws_test_tcp_config.h"
"${ProjDirPath}/../config_files/aws_test_wifi_config.h"
"${ProjDirPath}/../config_files/aws_wifi_config.h"
"${ProjDirPath}/../config_files/core_http_config.h"
"${ProjDirPath}/../config_files/core_mqtt_config.h"
"${ProjDirPath}/../config_files/core_pkcs11_config.h"
"${ProjDirPath}/../config_files/core_test_pkcs11_config.h"
"${ProjDirPath}/../config_files/FreeRTOSConfig.h"
"${ProjDirPath}/../config_files/FreeRTOSIPConfig.h"
"${ProjDirPath}/../config_files/iot_config.h"
"${ProjDirPath}/../config_files/iot_secure_sockets_config.h"
"${ProjDirPath}/../config_files/shadow_config.h"
"${ProjDirPath}/../config_files/unity_config.h"
"${ProjDirPath}/../config_files/lwipopts.h"
"${ProjDirPath}/../wifi_config.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../dcd.c"
"${ProjDirPath}/../dcd.h"
"${ProjDirPath}/../evkmimxrt1160_connect_cm4_cm4side.jlinkscript"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/../../../..
    ${ProjDirPath}/../config_files
    ${ProjDirPath}/..
    ${ProjDirPath}/../../../../../src/aws_examples/common/config_files_wifi_nxp
    ${ProjDirPath}/../../../common/cm4
)

if(CMAKE_BUILD_TYPE STREQUAL flexspi_nor_debug)
     target_compile_definitions(${MCUX_SDK_PROJECT_NAME}  PRIVATE MBEDTLS_CONFIG_FILE="aws_mbedtls_config.h")
endif(CMAKE_BUILD_TYPE STREQUAL flexspi_nor_debug)

if(CMAKE_BUILD_TYPE STREQUAL flexspi_nor_release)
     target_compile_definitions(${MCUX_SDK_PROJECT_NAME}  PRIVATE MBEDTLS_CONFIG_FILE="aws_mbedtls_config.h")
endif(CMAKE_BUILD_TYPE STREQUAL flexspi_nor_release)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../../devices/MIMXRT1166/drivers
    ${ProjDirPath}/../../../../../../components/flash/mflash
    ${ProjDirPath}/../../../../../../components/flash/mflash/mimxrt1160
    ${ProjDirPath}/../../../../../../devices/MIMXRT1166/drivers/cm4
    ${ProjDirPath}/../../../../../../middleware/mbedtls
    ${ProjDirPath}/../../../../../../middleware/wifi_nxp
    ${ProjDirPath}/../../../../../../rtos/freertos/freertos_kernel
    ${ProjDirPath}/../../../../../../devices/MIMXRT1166/utilities
    ${ProjDirPath}/../../../../../../middleware/sdmmc
    ${ProjDirPath}/../../../../../../components/gpio
    ${ProjDirPath}/../../../../../../rtos/freertos
    ${ProjDirPath}/../../../../../../middleware/lwip
    ${ProjDirPath}/../../../../../../components/wifi_bt_module
    ${ProjDirPath}/../../../../../../devices/MIMXRT1166
    ${ProjDirPath}/../../../../../../components/uart
    ${ProjDirPath}/../../../../../../components/serial_manager
    ${ProjDirPath}/../../../../../../components/lists
    ${ProjDirPath}/../../../../../../devices/MIMXRT1166/xip
    ${ProjDirPath}/../../../../xip
    ${ProjDirPath}/../../../../../../components/silicon_id
    ${ProjDirPath}/../../../../../../CMSIS/Core/Include
    ${ProjDirPath}/../../../../../../components/osa
)

# include modules
include(driver_caam_MIMXRT1166_cm4)

include(driver_flexspi_MIMXRT1166_cm4)

include(component_mflash_file_MIMXRT1166_cm4)

include(component_mflash_rt1160_MIMXRT1166_cm4)

include(component_mflash_common_MIMXRT1166_cm4)

include(driver_cache_lmem_MIMXRT1166_cm4)

include(middleware_mbedtls_MIMXRT1166_cm4)

include(middleware_mbedtls_port_ksdk_MIMXRT1166_cm4)

include(middleware_mbedtls_rt2_MIMXRT1166_cm4)

include(middleware_wifi_wifidriver_MIMXRT1166_cm4)

include(middleware_freertos-kernel_MIMXRT1166_cm4)

include(utility_debug_console_MIMXRT1166_cm4)

include(middleware_wifi_sdio_MIMXRT1166_cm4)

include(middleware_wifi_fwdnld_MIMXRT1166_cm4)

include(middleware_sdmmc_sdio_MIMXRT1166_cm4)

include(middleware_sdmmc_common_MIMXRT1166_cm4)

include(middleware_sdmmc_host_usdhc_MIMXRT1166_cm4)

include(middleware_sdmmc_host_usdhc_freertos_MIMXRT1166_cm4)

include(component_igpio_adapter_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_demos_dev_mode_key_provisioning_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_vendor_nxp_wifi_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_tests_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_vendor_nxp_secure_sockets_lwip_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_freertos_plus_aws_greengrass_MIMXRT1166_cm4)

include(middleware_lwip_MIMXRT1166_cm4)

include(middleware_wifi_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_abstractions_transport_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_abstractions_secure_sockets_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_logging_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_coremqtt_MIMXRT1166_cm4)

include(component_wifi_bt_module_tx_pwr_limits_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_3rdparty_mbedtls_config_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_3rdparty_pkcs11_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_abstractions_pkcs11_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_abstractions_pkcs11_mbedtls_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_vendor_nxp_pkcs11_MIMXRT1166_cm4)

include(middleware_freertos-kernel_heap_4_MIMXRT1166_cm4)

include(driver_clock_MIMXRT1166_cm4)

include(driver_common_MIMXRT1166_cm4)

include(device_MIMXRT1166_CMSIS_MIMXRT1166_cm4)

include(component_lpuart_adapter_MIMXRT1166_cm4)

include(component_serial_manager_MIMXRT1166_cm4)

include(component_lists_MIMXRT1166_cm4)

include(component_serial_manager_uart_MIMXRT1166_cm4)

include(driver_lpuart_MIMXRT1166_cm4)

include(device_MIMXRT1166_startup_MIMXRT1166_cm4)

include(driver_iomuxc_MIMXRT1166_cm4)

include(utility_assert_MIMXRT1166_cm4)

include(driver_igpio_MIMXRT1166_cm4)

include(driver_xip_device_MIMXRT1166_cm4)

include(driver_xip_board_evkmimxrt1160_MIMXRT1166_cm4)

include(driver_pmu_1_MIMXRT1166_cm4)

include(driver_dcdc_soc_MIMXRT1166_cm4)

include(component_silicon_id_MIMXRT1166_cm4)

include(driver_memory_MIMXRT1166_cm4)

include(driver_anatop_ai_MIMXRT1166_cm4)

include(CMSIS_Include_core_cm_MIMXRT1166_cm4)

include(middleware_freertos-kernel_extension_MIMXRT1166_cm4)

include(middleware_wifi_sdio-2_MIMXRT1166_cm4)

include(middleware_sdmmc_osa_freertos_MIMXRT1166_cm4)

include(component_osa_free_rtos_MIMXRT1166_cm4)

include(driver_usdhc_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_c_sdk_standard_common_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_abstractions_platform_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_abstractions_wifi_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_abstractions_backoff_algorithm_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_device_shadow_for_aws_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_corehttp_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_3rdparty_http_parser_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_3rdparty_jsmn_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_freertos_plus_standard_tls_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_3rdparty_mbedtls_utils_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_freertos_plus_standard_crypto_MIMXRT1166_cm4)

include(middleware_freertos-aws_iot_libraries_freertos_plus_standard_utils_MIMXRT1166_cm4)

include(utilities_misc_utilities_MIMXRT1166_cm4)

include(device_MIMXRT1166_system_MIMXRT1166_cm4)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)


