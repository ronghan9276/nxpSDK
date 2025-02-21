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


project(keyboard2mouse_freertos_cm7)

set(MCUX_SDK_PROJECT_NAME keyboard2mouse_freertos_cm7.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../app.h"
"${ProjDirPath}/../app.c"
"${ProjDirPath}/../host_keyboard.c"
"${ProjDirPath}/../host_keyboard.h"
"${ProjDirPath}/../usb_host_config.h"
"${ProjDirPath}/../device_mouse.c"
"${ProjDirPath}/../device_mouse.h"
"${ProjDirPath}/../usb_device_descriptor.c"
"${ProjDirPath}/../usb_device_descriptor.h"
"${ProjDirPath}/../usb_device_config.h"
"${ProjDirPath}/../FreeRTOSConfig.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../dcd.c"
"${ProjDirPath}/../dcd.h"
"${ProjDirPath}/../usb_device_ch9.c"
"${ProjDirPath}/../usb_device_ch9.h"
"${ProjDirPath}/../usb_device_class.c"
"${ProjDirPath}/../usb_device_class.h"
"${ProjDirPath}/../usb_device_hid.c"
"${ProjDirPath}/../usb_device_hid.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/..
    ${ProjDirPath}/../../../../..
)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../../../middleware/usb
    ${ProjDirPath}/../../../../../../../rtos/freertos/freertos_kernel
    ${ProjDirPath}/../../../../../../../devices/MIMXRT1166/drivers
    ${ProjDirPath}/../../../../../../../devices/MIMXRT1166
    ${ProjDirPath}/../../../../../../../devices/MIMXRT1166/utilities
    ${ProjDirPath}/../../../../../../../components/uart
    ${ProjDirPath}/../../../../../../../components/serial_manager
    ${ProjDirPath}/../../../../../../../components/lists
    ${ProjDirPath}/../../../../../../../devices/MIMXRT1166/xip
    ${ProjDirPath}/../../../../../xip
    ${ProjDirPath}/../../../../../../../components/osa
    ${ProjDirPath}/../../../../../../../devices/MIMXRT1166/drivers/cm7
    ${ProjDirPath}/../../../../../../../CMSIS/Core/Include
)

# include modules
include(middleware_usb_device_ehci_MIMXRT1166_cm7)

include(middleware_usb_host_ehci_MIMXRT1166_cm7)

include(middleware_usb_phy_MIMXRT1166_cm7)

include(middleware_freertos-kernel_heap_4_MIMXRT1166_cm7)

include(middleware_freertos-kernel_MIMXRT1166_cm7)

include(middleware_usb_host_hid_MIMXRT1166_cm7)

include(driver_clock_MIMXRT1166_cm7)

include(driver_common_MIMXRT1166_cm7)

include(device_MIMXRT1166_CMSIS_MIMXRT1166_cm7)

include(utility_debug_console_MIMXRT1166_cm7)

include(component_lpuart_adapter_MIMXRT1166_cm7)

include(component_serial_manager_MIMXRT1166_cm7)

include(component_lists_MIMXRT1166_cm7)

include(component_serial_manager_uart_MIMXRT1166_cm7)

include(driver_lpuart_MIMXRT1166_cm7)

include(device_MIMXRT1166_startup_MIMXRT1166_cm7)

include(driver_iomuxc_MIMXRT1166_cm7)

include(utility_assert_MIMXRT1166_cm7)

include(driver_igpio_MIMXRT1166_cm7)

include(driver_xip_device_MIMXRT1166_cm7)

include(driver_xip_board_evkmimxrt1160_MIMXRT1166_cm7)

include(middleware_usb_host_stack_MIMXRT1166_cm7)

include(component_osa_MIMXRT1166_cm7)

include(middleware_usb_device_controller_driver_MIMXRT1166_cm7)

include(driver_pmu_1_MIMXRT1166_cm7)

include(driver_dcdc_soc_MIMXRT1166_cm7)

include(driver_cache_armv7_m7_MIMXRT1166_cm7)

include(middleware_usb_common_header_MIMXRT1166_cm7)

include(driver_anatop_ai_MIMXRT1166_cm7)

include(CMSIS_Include_core_cm_MIMXRT1166_cm7)

include(middleware_usb_device_common_header_MIMXRT1166_cm7)

include(middleware_usb_host_common_header_MIMXRT1166_cm7)

include(middleware_freertos-kernel_extension_MIMXRT1166_cm7)

include(utilities_misc_utilities_MIMXRT1166_cm7)

include(device_MIMXRT1166_system_MIMXRT1166_cm7)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)


