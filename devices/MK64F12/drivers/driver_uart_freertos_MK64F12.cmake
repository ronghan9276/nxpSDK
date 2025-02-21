if(NOT DRIVER_UART_FREERTOS_MK64F12_INCLUDED)
    
    set(DRIVER_UART_FREERTOS_MK64F12_INCLUDED true CACHE BOOL "driver_uart_freertos component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_uart_freertos.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_uart_MK64F12)

    include(middleware_freertos-kernel_MK64F12)

endif()
