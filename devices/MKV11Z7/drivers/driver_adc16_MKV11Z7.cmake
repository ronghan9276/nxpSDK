if(NOT DRIVER_ADC16_MKV11Z7_INCLUDED)
    
    set(DRIVER_ADC16_MKV11Z7_INCLUDED true CACHE BOOL "driver_adc16 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_adc16.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common_MKV11Z7)

endif()
