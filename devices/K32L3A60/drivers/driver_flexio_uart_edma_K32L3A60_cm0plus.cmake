if(NOT DRIVER_FLEXIO_UART_EDMA_K32L3A60_cm0plus_INCLUDED)
    
    set(DRIVER_FLEXIO_UART_EDMA_K32L3A60_cm0plus_INCLUDED true CACHE BOOL "driver_flexio_uart_edma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_flexio_uart_edma.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_flexio_uart_K32L3A60_cm0plus)

    include(driver_edma_K32L3A60_cm0plus)

endif()
