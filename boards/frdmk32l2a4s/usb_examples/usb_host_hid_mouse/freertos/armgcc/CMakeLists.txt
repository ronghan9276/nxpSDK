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


project(host_hid_mouse_freertos)

set(MCUX_SDK_PROJECT_NAME host_hid_mouse_freertos.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../app.h"
"${ProjDirPath}/../app.c"
"${ProjDirPath}/../host_mouse.c"
"${ProjDirPath}/../host_mouse.h"
"${ProjDirPath}/../usb_host_config.h"
"${ProjDirPath}/../FreeRTOSConfig.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/.. debug
    ${ProjDirPath}/../../../.. debug
    ${ProjDirPath}/..
    ${ProjDirPath}/../../../..
)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../../middleware/usb
    ${ProjDirPath}/../../../../../../rtos/freertos
    ${ProjDirPath}/../../../../../../devices/K32L2A41A/drivers
    ${ProjDirPath}/../../../../../../devices/K32L2A41A
    ${ProjDirPath}/../../../../../../devices/K32L2A41A/utilities
    ${ProjDirPath}/../../../../../../components/uart
    ${ProjDirPath}/../../../../../../components/serial_manager
    ${ProjDirPath}/../../../../../../components/lists
    ${ProjDirPath}/../../../../../../components/osa
    ${ProjDirPath}/../../../../../../CMSIS/Include
)

# include modules
include(middleware_usb_host_khci_K32L2A41A)

include(middleware_freertos-kernel_heap_4_K32L2A41A)

include(middleware_freertos-kernel_K32L2A41A)

include(middleware_usb_host_hid_K32L2A41A)

include(driver_smc_K32L2A41A)

include(driver_clock_K32L2A41A)

include(driver_common_K32L2A41A)

include(device_K32L2A41A_CMSIS_K32L2A41A)

include(device_K32L2A41A_startup_K32L2A41A)

include(driver_lpuart_K32L2A41A)

include(driver_gpio_K32L2A41A)

include(utility_assert_K32L2A41A)

include(utility_debug_console_K32L2A41A)

include(component_lpuart_adapter_K32L2A41A)

include(component_serial_manager_K32L2A41A)

include(component_lists_K32L2A41A)

include(component_serial_manager_uart_K32L2A41A)

include(driver_port_K32L2A41A)

include(middleware_usb_host_stack_K32L2A41A)

include(component_osa_K32L2A41A)

include(middleware_usb_host_common_header_K32L2A41A)

include(CMSIS_Include_core_cm0plus_K32L2A41A)

include(CMSIS_Include_common_K32L2A41A)

include(CMSIS_Include_dsp_K32L2A41A)

include(middleware_usb_common_header_K32L2A41A)

include(middleware_freertos-kernel_extension_K32L2A41A)

include(utilities_misc_utilities_K32L2A41A)

include(device_K32L2A41A_system_K32L2A41A)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)


