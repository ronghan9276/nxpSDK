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


project(lwip_httpscli_mbedTLS_freertos)

set(MCUX_SDK_PROJECT_NAME lwip_httpscli_mbedTLS_freertos.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../lwip_httpscli_mbedTLS_freertos.c"
"${ProjDirPath}/../lwipopts.h"
"${ProjDirPath}/../mbedtls_config_client.h"
"${ProjDirPath}/../FreeRTOSConfig.h"
"${ProjDirPath}/../httpsclient.c"
"${ProjDirPath}/../httpsclient.h"
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
    ${ProjDirPath}/../../../..
)

if(CMAKE_BUILD_TYPE STREQUAL flexspi_nor_sdram_debug)
     target_compile_definitions(${MCUX_SDK_PROJECT_NAME}  PRIVATE MBEDTLS_CONFIG_FILE="mbedtls_config_client.h")
endif(CMAKE_BUILD_TYPE STREQUAL flexspi_nor_sdram_debug)

if(CMAKE_BUILD_TYPE STREQUAL flexspi_nor_sdram_release)
     target_compile_definitions(${MCUX_SDK_PROJECT_NAME}  PRIVATE MBEDTLS_CONFIG_FILE="mbedtls_config_client.h")
endif(CMAKE_BUILD_TYPE STREQUAL flexspi_nor_sdram_release)

if(CMAKE_BUILD_TYPE STREQUAL sdram_debug)
     target_compile_definitions(${MCUX_SDK_PROJECT_NAME}  PRIVATE MBEDTLS_CONFIG_FILE="mbedtls_config_client.h")
endif(CMAKE_BUILD_TYPE STREQUAL sdram_debug)

if(CMAKE_BUILD_TYPE STREQUAL sdram_release)
     target_compile_definitions(${MCUX_SDK_PROJECT_NAME}  PRIVATE MBEDTLS_CONFIG_FILE="mbedtls_config_client.h")
endif(CMAKE_BUILD_TYPE STREQUAL sdram_release)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../../components/phy/mdio/enet
    ${ProjDirPath}/../../../../../../components/phy/device/phyksz8081
    ${ProjDirPath}/../../../../../../devices/MIMXRT1062/drivers
    ${ProjDirPath}/../../../../../../middleware/mbedtls
    ${ProjDirPath}/../../../../../../middleware/lwip
    ${ProjDirPath}/../../../../../../components/phy
    ${ProjDirPath}/../../../../../../devices/MIMXRT1062/utilities
    ${ProjDirPath}/../../../../../../rtos/freertos
    ${ProjDirPath}/../../../../../../devices/MIMXRT1062
    ${ProjDirPath}/../../../../../../components/uart
    ${ProjDirPath}/../../../../../../components/serial_manager
    ${ProjDirPath}/../../../../../../components/lists
    ${ProjDirPath}/../../../../../../devices/MIMXRT1062/xip
    ${ProjDirPath}/../../../../xip
    ${ProjDirPath}/../../../../../../CMSIS/Core/Include
)

# include modules
include(driver_mdio-enet_MIMXRT1062)

include(driver_phy-device-ksz8081_MIMXRT1062)

include(driver_trng_MIMXRT1062)

include(driver_dcp_MIMXRT1062)

include(driver_cache_armv7_m7_MIMXRT1062)

include(middleware_mbedtls_MIMXRT1062)

include(middleware_mbedtls_port_ksdk_MIMXRT1062)

include(middleware_mbedtls_rt_MIMXRT1062)

include(middleware_lwip_enet_ethernetif_MIMXRT1062)

include(middleware_lwip_MIMXRT1062)

include(driver_phy-common_MIMXRT1062)

include(driver_enet_MIMXRT1062)

include(utility_debug_console_MIMXRT1062)

include(driver_clock_MIMXRT1062)

include(middleware_freertos-kernel_heap_4_MIMXRT1062)

include(driver_common_MIMXRT1062)

include(device_MIMXRT1062_CMSIS_MIMXRT1062)

include(component_lpuart_adapter_MIMXRT1062)

include(component_serial_manager_MIMXRT1062)

include(component_lists_MIMXRT1062)

include(component_serial_manager_uart_MIMXRT1062)

include(driver_lpuart_MIMXRT1062)

include(device_MIMXRT1062_startup_MIMXRT1062)

include(driver_iomuxc_MIMXRT1062)

include(utility_assert_MIMXRT1062)

include(driver_igpio_MIMXRT1062)

include(driver_xip_device_MIMXRT1062)

include(driver_xip_board_evkbmimxrt1060_MIMXRT1062)

include(driver_mdio-common_MIMXRT1062)

include(CMSIS_Include_core_cm_MIMXRT1062)

include(middleware_freertos-kernel_MIMXRT1062)

include(middleware_freertos-kernel_extension_MIMXRT1062)

include(utilities_misc_utilities_MIMXRT1062)

include(device_MIMXRT1062_system_MIMXRT1062)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)


