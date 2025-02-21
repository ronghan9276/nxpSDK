if(NOT DRIVER_DCDC_SOC_MIMXRT117H_INCLUDED)
    
    set(DRIVER_DCDC_SOC_MIMXRT117H_INCLUDED true CACHE BOOL "driver_dcdc_soc component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_dcdc.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common_MIMXRT117H)

endif()
