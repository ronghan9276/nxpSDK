if(NOT COMPONENT_SERIAL_MANAGER_UART_MK22F51212_INCLUDED)
    
    set(COMPONENT_SERIAL_MANAGER_UART_MK22F51212_INCLUDED true CACHE BOOL "component_serial_manager_uart component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_component_serial_port_uart.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    #OR Logic component
    if(CONFIG_USE_driver_lpuart_MK22F51212)
         include(driver_lpuart_MK22F51212)
    endif()
    if(CONFIG_USE_driver_uart_MK22F51212)
         include(driver_uart_MK22F51212)
    endif()
    if(NOT (CONFIG_USE_driver_lpuart_MK22F51212 OR CONFIG_USE_driver_uart_MK22F51212))
        message(WARNING "Since driver_lpuart_MK22F51212/driver_uart_MK22F51212 is not included at first or config in config.cmake file, use driver_uart_MK22F51212 by default.")
        include(driver_uart_MK22F51212)
    endif()

    include(component_uart_adapter_MK22F51212)

    include(component_serial_manager_MK22F51212)

endif()
