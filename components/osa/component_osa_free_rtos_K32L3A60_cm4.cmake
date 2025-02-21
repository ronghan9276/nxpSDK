if(NOT COMPONENT_OSA_FREE_RTOS_K32L3A60_cm4_INCLUDED)
    
    set(COMPONENT_OSA_FREE_RTOS_K32L3A60_cm4_INCLUDED true CACHE BOOL "component_osa_free_rtos component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(middleware_freertos-kernel_K32L3A60_cm4)

    include(driver_common_K32L3A60_cm4)

    include(component_lists_K32L3A60_cm4)

endif()
