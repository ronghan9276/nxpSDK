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


project(erpc_matrix_multiply_rpmsg_rtos_cm4)

set(MCUX_SDK_PROJECT_NAME erpc_matrix_multiply_rpmsg_rtos_cm4.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../../../erpc_common/erpc_error_handler.h"
"${ProjDirPath}/../../../erpc_common/erpc_error_handler.cpp"
"${ProjDirPath}/../../../erpc_common/erpc_matrix_multiply/service/erpc_matrix_multiply.erpc"
"${ProjDirPath}/../../../erpc_common/erpc_matrix_multiply/service/erpc_matrix_multiply.h"
"${ProjDirPath}/../../../erpc_common/erpc_matrix_multiply/service/erpc_matrix_multiply_server.h"
"${ProjDirPath}/../../../erpc_common/erpc_matrix_multiply/service/erpc_matrix_multiply_server.cpp"
"${ProjDirPath}/../main_core1.c"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../../rpmsg_config.h"
"${ProjDirPath}/../../erpc_config.h"
"${ProjDirPath}/../FreeRTOSConfig.h"
"${ProjDirPath}/../dcd.c"
"${ProjDirPath}/../dcd.h"
"${ProjDirPath}/../evkmimxrt1160_connect_cm4_cm4side.jlinkscript"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/..
    ${ProjDirPath}/../../../erpc_common
    ${ProjDirPath}/../../../erpc_common/erpc_matrix_multiply/service
    ${ProjDirPath}/../..
)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../../middleware/multicore
    ${ProjDirPath}/../../../../../../devices/MIMXRT1166/drivers
    ${ProjDirPath}/../../../../../../rtos/freertos/freertos_kernel
    ${ProjDirPath}/../../../../../../devices/MIMXRT1166
    ${ProjDirPath}/../../../../../../devices/MIMXRT1166/utilities
    ${ProjDirPath}/../../../../../../components/uart
    ${ProjDirPath}/../../../../../../components/serial_manager
    ${ProjDirPath}/../../../../../../components/lists
    ${ProjDirPath}/../../../../../../devices/MIMXRT1166/xip
    ${ProjDirPath}/../../../../xip
    ${ProjDirPath}/../../../../../../devices/MIMXRT1166/drivers/cm4
    ${ProjDirPath}/../../../../../../components/silicon_id
    ${ProjDirPath}/../../../../../../CMSIS/Core/Include
)

# include modules
include(middleware_multicore_mcmgr_imxrt1160_MIMXRT1166_cm4)

include(middleware_multicore_rpmsg_lite_imxrt1160_freertos_MIMXRT1166_cm4)

include(middleware_multicore_rpmsg_lite_MIMXRT1166_cm4)

include(middleware_multicore_rpmsg_lite_freertos_MIMXRT1166_cm4)

include(driver_clock_MIMXRT1166_cm4)

include(driver_mu_MIMXRT1166_cm4)

include(middleware_multicore_erpc_eRPC_server_MIMXRT1166_cm4)

include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_remote_c_wrapper_MIMXRT1166_cm4)

include(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport_MIMXRT1166_cm4)

include(middleware_multicore_erpc_eRPC_port_freertos_MIMXRT1166_cm4)

include(middleware_freertos-kernel_MIMXRT1166_cm4)

include(middleware_multicore_mcmgr_MIMXRT1166_cm4)

include(middleware_freertos-kernel_heap_4_MIMXRT1166_cm4)

include(middleware_multicore_erpc_doc_MIMXRT1166_cm4)

include(driver_common_MIMXRT1166_cm4)

include(device_MIMXRT1166_CMSIS_MIMXRT1166_cm4)

include(utility_debug_console_MIMXRT1166_cm4)

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

include(driver_cache_lmem_MIMXRT1166_cm4)

include(component_silicon_id_MIMXRT1166_cm4)

include(driver_anatop_ai_MIMXRT1166_cm4)

include(CMSIS_Include_core_cm_MIMXRT1166_cm4)

include(middleware_freertos-kernel_extension_MIMXRT1166_cm4)

include(middleware_multicore_erpc_common_MIMXRT1166_cm4)

include(utilities_misc_utilities_MIMXRT1166_cm4)

include(device_MIMXRT1166_system_MIMXRT1166_cm4)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/core1_image.bin)

