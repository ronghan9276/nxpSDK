if(NOT COMPONENT_LOG_BACKEND_DEBUGCONSOLE_MK22F51212_INCLUDED)
    
    set(COMPONENT_LOG_BACKEND_DEBUGCONSOLE_MK22F51212_INCLUDED true CACHE BOOL "component_log_backend_debugconsole component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_component_log_backend_debugconsole.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common_MK22F51212)

    include(component_log_MK22F51212)

    include(utility_debug_console_MK22F51212)

endif()
