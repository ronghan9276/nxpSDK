include_guard(GLOBAL)
message("component_serial_manager component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_component_serial_manager.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


#OR Logic component
if(CONFIG_USE_component_serial_manager_uart_MKE15Z7)
     include(component_serial_manager_uart_MKE15Z7)
endif()
if(CONFIG_USE_component_serial_manager_usb_cdc_MKE15Z7)
     include(component_serial_manager_usb_cdc_MKE15Z7)
endif()
if(CONFIG_USE_component_serial_manager_virtual_MKE15Z7)
     include(component_serial_manager_virtual_MKE15Z7)
endif()
if(CONFIG_USE_component_serial_manager_swo_MKE15Z7)
     include(component_serial_manager_swo_MKE15Z7)
endif()
if(CONFIG_USE_component_serial_manager_rpmsg_MKE15Z7)
     include(component_serial_manager_rpmsg_MKE15Z7)
endif()
if(NOT (CONFIG_USE_component_serial_manager_uart_MKE15Z7 OR CONFIG_USE_component_serial_manager_usb_cdc_MKE15Z7 OR CONFIG_USE_component_serial_manager_virtual_MKE15Z7 OR CONFIG_USE_component_serial_manager_swo_MKE15Z7 OR CONFIG_USE_component_serial_manager_rpmsg_MKE15Z7))
    message(WARNING "Since component_serial_manager_uart_MKE15Z7/component_serial_manager_usb_cdc_MKE15Z7/component_serial_manager_virtual_MKE15Z7/component_serial_manager_swo_MKE15Z7/component_serial_manager_rpmsg_MKE15Z7 is not included at first or config in config.cmake file, use component_serial_manager_uart_MKE15Z7 by default.")
    include(component_serial_manager_uart_MKE15Z7)
endif()

include(driver_common_MKE15Z7)

include(component_lists_MKE15Z7)

