if(NOT UTILITY_DEBUG_CONSOLE_K32L3A60_cm0plus_INCLUDED)
    
    set(UTILITY_DEBUG_CONSOLE_K32L3A60_cm0plus_INCLUDED true CACHE BOOL "utility_debug_console component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/str/fsl_str.c
        ${CMAKE_CURRENT_LIST_DIR}/debug_console/fsl_debug_console.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/str
        ${CMAKE_CURRENT_LIST_DIR}/debug_console
    )


    include(component_serial_manager_K32L3A60_cm0plus)

    include(driver_common_K32L3A60_cm0plus)

endif()
