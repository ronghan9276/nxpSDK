if(NOT DRIVER_PIT_MK64F12_INCLUDED)
    
    set(DRIVER_PIT_MK64F12_INCLUDED true CACHE BOOL "driver_pit component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_pit.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common_MK64F12)

endif()
