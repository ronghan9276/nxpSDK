if(NOT MIDDLEWARE_SDMMC_OSA_FREERTOS_K32L3A60_cm0plus_INCLUDED)
    
    set(MIDDLEWARE_SDMMC_OSA_FREERTOS_K32L3A60_cm0plus_INCLUDED true CACHE BOOL "middleware_sdmmc_osa_freertos component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/osa/fsl_sdmmc_osa.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/osa
    )


    include(component_osa_free_rtos_K32L3A60_cm0plus)

endif()
