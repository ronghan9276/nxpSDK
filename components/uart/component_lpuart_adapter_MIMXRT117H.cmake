if(NOT COMPONENT_LPUART_ADAPTER_MIMXRT117H_INCLUDED)
    
    set(COMPONENT_LPUART_ADAPTER_MIMXRT117H_INCLUDED true CACHE BOOL "component_lpuart_adapter component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_lpuart.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common_MIMXRT117H)

    include(driver_lpuart_MIMXRT117H)

endif()
