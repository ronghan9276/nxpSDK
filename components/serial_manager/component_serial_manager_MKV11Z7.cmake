if(NOT COMPONENT_SERIAL_MANAGER_MKV11Z7_INCLUDED)
    
    set(COMPONENT_SERIAL_MANAGER_MKV11Z7_INCLUDED true CACHE BOOL "component_serial_manager component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_component_serial_manager.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    #OR Logic component
    if(CONFIG_USE_component_serial_manager_uart_MKV11Z7)
         include(component_serial_manager_uart_MKV11Z7)
    endif()
    if(CONFIG_USE_component_serial_manager_usb_cdc_MKV11Z7)
         include(component_serial_manager_usb_cdc_MKV11Z7)
    endif()
    if(CONFIG_USE_component_serial_manager_virtual_MKV11Z7)
         include(component_serial_manager_virtual_MKV11Z7)
    endif()
    if(CONFIG_USE_component_serial_manager_swo_MKV11Z7)
         include(component_serial_manager_swo_MKV11Z7)
    endif()
    if(CONFIG_USE_component_serial_manager_rpmsg_MKV11Z7)
         include(component_serial_manager_rpmsg_MKV11Z7)
    endif()
    if(NOT (CONFIG_USE_component_serial_manager_uart_MKV11Z7 OR CONFIG_USE_component_serial_manager_usb_cdc_MKV11Z7 OR CONFIG_USE_component_serial_manager_virtual_MKV11Z7 OR CONFIG_USE_component_serial_manager_swo_MKV11Z7 OR CONFIG_USE_component_serial_manager_rpmsg_MKV11Z7))
        message(WARNING "Since component_serial_manager_uart_MKV11Z7/component_serial_manager_usb_cdc_MKV11Z7/component_serial_manager_virtual_MKV11Z7/component_serial_manager_swo_MKV11Z7/component_serial_manager_rpmsg_MKV11Z7 is not included at first or config in config.cmake file, use component_serial_manager_uart_MKV11Z7 by default.")
        include(component_serial_manager_uart_MKV11Z7)
    endif()

    include(driver_common_MKV11Z7)

    include(component_lists_MKV11Z7)

endif()
