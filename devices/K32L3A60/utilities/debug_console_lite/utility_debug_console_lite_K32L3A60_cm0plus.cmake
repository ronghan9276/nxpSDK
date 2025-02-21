if(NOT UTILITY_DEBUG_CONSOLE_LITE_K32L3A60_cm0plus_INCLUDED)
    
    set(UTILITY_DEBUG_CONSOLE_LITE_K32L3A60_cm0plus_INCLUDED true CACHE BOOL "utility_debug_console_lite component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_debug_console.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(component_lpuart_adapter_K32L3A60_cm0plus)

    include(driver_common_K32L3A60_cm0plus)

endif()
