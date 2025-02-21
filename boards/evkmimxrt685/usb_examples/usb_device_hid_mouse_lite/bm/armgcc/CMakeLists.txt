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


project(dev_hid_mouse_lite_bm)

set(MCUX_SDK_PROJECT_NAME dev_hid_mouse_lite_bm.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../usb_hsdcd_config.h"
"${ProjDirPath}/../mouse.c"
"${ProjDirPath}/../mouse.h"
"${ProjDirPath}/../usb_device_descriptor.c"
"${ProjDirPath}/../usb_device_descriptor.h"
"${ProjDirPath}/../usb_device_ch9.c"
"${ProjDirPath}/../usb_device_ch9.h"
"${ProjDirPath}/../usb_device_hid.c"
"${ProjDirPath}/../usb_device_hid.h"
"${ProjDirPath}/../usb_device_config.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../../../../../../middleware/usb/dcd/usb_hsdcd.c"
"${ProjDirPath}/../../../../../../middleware/usb/dcd/usb_hsdcd.h"
"${ProjDirPath}/../../../../../../middleware/usb/dcd/usb_charger_detect.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/..
    ${ProjDirPath}/../../../../../../middleware/usb/dcd
)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../../middleware/usb
    ${ProjDirPath}/../../../../../../devices/MIMXRT685S/utilities/debug_console_lite
    ${ProjDirPath}/../../../../../../middleware
    ${ProjDirPath}/../../../../../../devices/MIMXRT685S/drivers
    ${ProjDirPath}/../../../../../../devices/MIMXRT685S
    ${ProjDirPath}/../../../../../../components/uart
    ${ProjDirPath}/../../../../flash_config
    ${ProjDirPath}/../../../../../../components/lists
    ${ProjDirPath}/../../../../../../components/osa
    ${ProjDirPath}/../../../../../../CMSIS/Core/Include
    ${ProjDirPath}/../../../../../../devices/MIMXRT685S/utilities
)

# include modules
include(middleware_usb_device_ip3511hs_MIMXRT685S_cm33)

include(middleware_usb_phy_MIMXRT685S_cm33)

include(utility_debug_console_lite_MIMXRT685S_cm33)

include(utility_assert_lite_MIMXRT685S_cm33)

include(middleware_baremetal_MIMXRT685S_cm33)

include(driver_clock_MIMXRT685S_cm33)

include(driver_common_MIMXRT685S_cm33)

include(device_MIMXRT685S_CMSIS_MIMXRT685S_cm33)

include(component_usart_adapter_MIMXRT685S_cm33)

include(driver_power_MIMXRT685S_cm33)

include(driver_flash_config_evkmimxrt685_MIMXRT685S_cm33)

include(component_lists_MIMXRT685S_cm33)

include(driver_flexcomm_usart_MIMXRT685S_cm33)

include(driver_cache_cache64_MIMXRT685S_cm33)

include(driver_flexspi_MIMXRT685S_cm33)

include(device_MIMXRT685S_startup_MIMXRT685S_cm33)

include(driver_flexcomm_MIMXRT685S_cm33)

include(driver_lpc_iopctl_MIMXRT685S_cm33)

include(driver_lpc_gpio_MIMXRT685S_cm33)

include(driver_reset_MIMXRT685S_cm33)

include(middleware_usb_device_controller_driver_MIMXRT685S_cm33)

include(component_osa_MIMXRT685S_cm33)

include(middleware_usb_common_header_MIMXRT685S_cm33)

include(CMSIS_Include_core_cm_MIMXRT685S_cm33)

include(middleware_usb_device_common_header_MIMXRT685S_cm33)

include(utilities_misc_utilities_MIMXRT685S_cm33)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/sdk20-app.bin)

