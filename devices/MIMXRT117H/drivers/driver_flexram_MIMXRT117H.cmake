if(NOT DRIVER_FLEXRAM_MIMXRT117H_INCLUDED)
    
    set(DRIVER_FLEXRAM_MIMXRT117H_INCLUDED true CACHE BOOL "driver_flexram component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_flexram.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common_MIMXRT117H)

endif()
