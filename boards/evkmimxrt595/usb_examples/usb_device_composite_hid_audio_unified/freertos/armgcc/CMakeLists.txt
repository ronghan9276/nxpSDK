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


project(dev_composite_hid_audio_unified_freertos)

set(MCUX_SDK_PROJECT_NAME dev_composite_hid_audio_unified_freertos.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../usb_audio_config.h"
"${ProjDirPath}/../audio_unified.c"
"${ProjDirPath}/../audio_unified.h"
"${ProjDirPath}/../composite.c"
"${ProjDirPath}/../composite.h"
"${ProjDirPath}/../hid_keyboard.c"
"${ProjDirPath}/../hid_keyboard.h"
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
"${ProjDirPath}/../usb_device_ch9.c"
"${ProjDirPath}/../usb_device_ch9.h"
"${ProjDirPath}/../usb_device_class.c"
"${ProjDirPath}/../usb_device_class.h"
"${ProjDirPath}/../usb_device_audio.c"
"${ProjDirPath}/../usb_device_audio.h"
"${ProjDirPath}/../usb_device_hid.c"
"${ProjDirPath}/../usb_device_hid.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/..
    ${ProjDirPath}/../../../..
)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../../middleware/usb
    ${ProjDirPath}/../../../../../../devices/MIMXRT595S/drivers
    ${ProjDirPath}/../../../../../../components/codec/wm8904
    ${ProjDirPath}/../../../../../../components/codec
    ${ProjDirPath}/../../../../../../components/codec/i2c
    ${ProjDirPath}/../../../../../../components/i2c
    ${ProjDirPath}/../../../../../../components/audio
    ${ProjDirPath}/../../../../../../rtos/freertos/freertos_kernel
    ${ProjDirPath}/../../../../../../devices/MIMXRT595S
    ${ProjDirPath}/../../../../../../devices/MIMXRT595S/utilities
    ${ProjDirPath}/../../../../../../components/uart
    ${ProjDirPath}/../../../../../../components/serial_manager
    ${ProjDirPath}/../../../../../../components/lists
    ${ProjDirPath}/../../../../flash_config
    ${ProjDirPath}/../../../../../../components/osa
    ${ProjDirPath}/../../../../../../CMSIS/Core/Include
)

# include modules
include(middleware_usb_device_ip3511hs_MIMXRT595S_cm33)

include(middleware_usb_phy_MIMXRT595S_cm33)

include(driver_flexcomm_i2c_MIMXRT595S_cm33)

include(driver_flexcomm_i2s_MIMXRT595S_cm33)

include(driver_flexcomm_i2s_dma_MIMXRT595S_cm33)

include(driver_lpc_dma_MIMXRT595S_cm33)

include(driver_flexcomm_usart_MIMXRT595S_cm33)

include(driver_wm8904_MIMXRT595S_cm33)

include(driver_i3c_MIMXRT595S_cm33)

include(driver_pint_MIMXRT595S_cm33)

include(driver_inputmux_MIMXRT595S_cm33)

include(driver_ctimer_MIMXRT595S_cm33)

include(driver_codec_MIMXRT595S_cm33)

include(driver_common_MIMXRT595S_cm33)

include(component_wm8904_adapter_MIMXRT595S_cm33)

include(component_codec_i2c_MIMXRT595S_cm33)

include(component_i3c_adapter_MIMXRT595S_cm33)

include(component_audio_flexcomm_i2s_dma_adapter_MIMXRT595S_cm33)

include(middleware_freertos-kernel_heap_4_MIMXRT595S_cm33)

include(middleware_freertos-kernel_MIMXRT595S_cm33)

include(driver_clock_MIMXRT595S_cm33)

include(device_MIMXRT595S_CMSIS_MIMXRT595S_cm33)

include(utility_debug_console_MIMXRT595S_cm33)

include(utility_assert_MIMXRT595S_cm33)

include(component_usart_adapter_MIMXRT595S_cm33)

include(driver_power_MIMXRT595S_cm33)

include(driver_flexspi_MIMXRT595S_cm33)

include(driver_cache_cache64_MIMXRT595S_cm33)

include(component_serial_manager_MIMXRT595S_cm33)

include(component_lists_MIMXRT595S_cm33)

include(component_serial_manager_uart_MIMXRT595S_cm33)

include(driver_flash_config_evkmimxrt595_MIMXRT595S_cm33)

include(device_MIMXRT595S_startup_MIMXRT595S_cm33)

include(driver_flexcomm_MIMXRT595S_cm33)

include(driver_lpc_iopctl_MIMXRT595S_cm33)

include(driver_lpc_gpio_MIMXRT595S_cm33)

include(driver_reset_MIMXRT595S_cm33)

include(middleware_freertos-kernel_cm33_nonsecure_port_MIMXRT595S_cm33)

include(middleware_usb_device_controller_driver_MIMXRT595S_cm33)

include(component_osa_MIMXRT595S_cm33)

include(middleware_usb_common_header_MIMXRT595S_cm33)

include(CMSIS_Include_core_cm_MIMXRT595S_cm33)

include(middleware_usb_device_common_header_MIMXRT595S_cm33)

include(driver_inputmux_connections_MIMXRT595S_cm33)

include(middleware_freertos-kernel_extension_MIMXRT595S_cm33)

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

