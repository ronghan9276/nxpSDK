if(NOT COMPONENT_SERIAL_MANAGER_K32L3A60_cm4_INCLUDED)
    
    set(COMPONENT_SERIAL_MANAGER_K32L3A60_cm4_INCLUDED true CACHE BOOL "component_serial_manager component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_component_serial_manager.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    #OR Logic component
    if(CONFIG_USE_component_serial_manager_uart_K32L3A60_cm4)
         include(component_serial_manager_uart_K32L3A60_cm4)
    endif()
    if(CONFIG_USE_component_serial_manager_usb_cdc_K32L3A60_cm4)
         include(component_serial_manager_usb_cdc_K32L3A60_cm4)
    endif()
    if(CONFIG_USE_component_serial_manager_virtual_K32L3A60_cm4)
         include(component_serial_manager_virtual_K32L3A60_cm4)
    endif()
    if(CONFIG_USE_component_serial_manager_swo_K32L3A60_cm4)
         include(component_serial_manager_swo_K32L3A60_cm4)
    endif()
    if(CONFIG_USE_component_serial_manager_rpmsg_K32L3A60_cm4)
         include(component_serial_manager_rpmsg_K32L3A60_cm4)
    endif()
    if(NOT (CONFIG_USE_component_serial_manager_uart_K32L3A60_cm4 OR CONFIG_USE_component_serial_manager_usb_cdc_K32L3A60_cm4 OR CONFIG_USE_component_serial_manager_virtual_K32L3A60_cm4 OR CONFIG_USE_component_serial_manager_swo_K32L3A60_cm4 OR CONFIG_USE_component_serial_manager_rpmsg_K32L3A60_cm4))
        message(WARNING "Since component_serial_manager_uart_K32L3A60_cm4/component_serial_manager_usb_cdc_K32L3A60_cm4/component_serial_manager_virtual_K32L3A60_cm4/component_serial_manager_swo_K32L3A60_cm4/component_serial_manager_rpmsg_K32L3A60_cm4 is not included at first or config in config.cmake file, use component_serial_manager_uart_K32L3A60_cm4 by default.")
        include(component_serial_manager_uart_K32L3A60_cm4)
    endif()

    include(driver_common_K32L3A60_cm4)

    include(component_lists_K32L3A60_cm4)

endif()
