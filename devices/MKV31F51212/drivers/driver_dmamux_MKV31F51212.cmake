if(NOT DRIVER_DMAMUX_MKV31F51212_INCLUDED)
    
    set(DRIVER_DMAMUX_MKV31F51212_INCLUDED true CACHE BOOL "driver_dmamux component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_dmamux.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common_MKV31F51212)

endif()
