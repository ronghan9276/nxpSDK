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


project(led_control_bm)

set(MCUX_SDK_PROJECT_NAME led_control_bm.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../led_control.c"
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
    ${ProjDirPath}/..
)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../../devices/MK64F12/drivers
    ${ProjDirPath}/../../../../../../devices/MK64F12/utilities
    ${ProjDirPath}/../../../../../../components/led
    ${ProjDirPath}/../../../../../../components/timer_manager
    ${ProjDirPath}/../../../../../../components/gpio
    ${ProjDirPath}/../../../../../../components/button
    ${ProjDirPath}/../../../../../../components/lists
    ${ProjDirPath}/../../../../../../components/timer
    ${ProjDirPath}/../../../../../../components/panic
    ${ProjDirPath}/../../../../../../components/serial_manager
    ${ProjDirPath}/../../../../../../components/osa
    ${ProjDirPath}/../../../../../../devices/MK64F12
    ${ProjDirPath}/../../../../../../components/uart
    ${ProjDirPath}/../../../../../../CMSIS/Include
)

# include modules
include(driver_ftm_MK64F12)

include(utility_shell_MK64F12)

include(driver_sysmpu_MK64F12)

include(component_led_MK64F12)

include(driver_common_MK64F12)

include(component_timer_manager_MK64F12)

include(component_gpio_adapter_MK64F12)

include(component_button_MK64F12)

include(component_lists_MK64F12)

include(component_ftm_adapter_MK64F12)

include(driver_gpio_MK64F12)

include(component_panic_MK64F12)

include(component_serial_manager_MK64F12)

include(component_serial_manager_uart_MK64F12)

include(component_osa_bm_MK64F12)

include(driver_flash_MK64F12)

include(driver_clock_MK64F12)

include(utility_debug_console_MK64F12)

include(driver_port_MK64F12)

include(driver_uart_MK64F12)

include(driver_smc_MK64F12)

include(device_MK64F12_CMSIS_MK64F12)

include(component_uart_adapter_MK64F12)

include(device_MK64F12_startup_MK64F12)

include(utility_assert_MK64F12)

include(CMSIS_Include_core_cm4_MK64F12)

include(CMSIS_Include_common_MK64F12)

include(CMSIS_Include_dsp_MK64F12)

include(utilities_misc_utilities_MK64F12)

include(device_MK64F12_system_MK64F12)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)


