include_guard()
message("utility_debug_console component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/str/fsl_str.c
    ${CMAKE_CURRENT_LIST_DIR}/debug_console/fsl_debug_console.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/str
    ${CMAKE_CURRENT_LIST_DIR}/debug_console
)


include(component_serial_manager_MIMXRT685S_cm33)

include(driver_common_MIMXRT685S_cm33)

