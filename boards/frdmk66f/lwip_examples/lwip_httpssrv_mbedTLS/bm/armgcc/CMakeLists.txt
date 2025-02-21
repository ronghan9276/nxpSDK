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


project(lwip_httpssrv_mbedTLS_bm)

set(MCUX_SDK_PROJECT_NAME lwip_httpssrv_mbedTLS_bm.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../httpd_mbedtls.c"
"${ProjDirPath}/../httpd_mbedtls.h"
"${ProjDirPath}/../lwip_httpssrv_mbedTLS_bm.c"
"${ProjDirPath}/../lwipopts.h"
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

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../../components/phy/mdio/enet
    ${ProjDirPath}/../../../../../../components/phy/device/phyksz8081
    ${ProjDirPath}/../../../../../../devices/MK66F18/drivers
    ${ProjDirPath}/../../../../../../middleware/mmcau
    ${ProjDirPath}/../../../../../../middleware/mbedtls
    ${ProjDirPath}/../../../../../../middleware/lwip
    ${ProjDirPath}/../../../../../../components/phy
    ${ProjDirPath}/../../../../../../devices/MK66F18/utilities
    ${ProjDirPath}/../../../../../../devices/MK66F18
    ${ProjDirPath}/../../../../../../components/uart
    ${ProjDirPath}/../../../../../../components/serial_manager
    ${ProjDirPath}/../../../../../../components/lists
    ${ProjDirPath}/../../../../../../CMSIS/Include
)

# include modules
include(driver_mdio-enet_MK66F18)

include(driver_phy-device-ksz8081_MK66F18)

include(driver_rnga_MK66F18)

include(middleware_mmcau_cm4_cm7_MK66F18)

include(middleware_mbedtls_port_ksdk_MK66F18)

include(middleware_mbedtls_kinetis_MK66F18)

include(middleware_lwip_apps_httpd_MK66F18)

include(middleware_lwip_enet_ethernetif_MK66F18)

include(middleware_lwip_MK66F18)

include(driver_phy-common_MK66F18)

include(driver_enet_MK66F18)

include(utility_debug_console_MK66F18)

include(middleware_mbedtls_MK66F18)

include(driver_port_MK66F18)

include(driver_sim_MK66F18)

include(driver_clock_MK66F18)

include(driver_flash_MK66F18)

include(driver_common_MK66F18)

include(device_MK66F18_CMSIS_MK66F18)

include(component_uart_adapter_MK66F18)

include(component_serial_manager_MK66F18)

include(component_lists_MK66F18)

include(component_serial_manager_uart_MK66F18)

include(driver_uart_MK66F18)

include(device_MK66F18_startup_MK66F18)

include(driver_lpuart_MK66F18)

include(driver_smc_MK66F18)

include(driver_gpio_MK66F18)

include(utility_assert_MK66F18)

include(driver_mdio-common_MK66F18)

include(CMSIS_Include_core_cm4_MK66F18)

include(CMSIS_Include_common_MK66F18)

include(CMSIS_Include_dsp_MK66F18)

include(middleware_mmcau_common_files_MK66F18)

include(middleware_lwip_apps_httpd_support_MK66F18)

include(utilities_misc_utilities_MK66F18)

include(device_MK66F18_system_MK66F18)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

if(CMAKE_BUILD_TYPE STREQUAL debug)
    target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${ProjDirPath}/../../../../../../middleware/mmcau/asm-cm4-cm7/lib_mmcau.a)
endif()

if(CMAKE_BUILD_TYPE STREQUAL release)
    target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${ProjDirPath}/../../../../../../middleware/mmcau/asm-cm4-cm7/lib_mmcau.a)
endif()

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)


