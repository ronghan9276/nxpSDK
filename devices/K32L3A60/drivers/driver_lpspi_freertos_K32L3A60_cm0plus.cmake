if(NOT DRIVER_LPSPI_FREERTOS_K32L3A60_cm0plus_INCLUDED)
    
    set(DRIVER_LPSPI_FREERTOS_K32L3A60_cm0plus_INCLUDED true CACHE BOOL "driver_lpspi_freertos component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_lpspi_freertos.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_lpspi_K32L3A60_cm0plus)

    include(middleware_freertos-kernel_K32L3A60_cm0plus)

endif()
