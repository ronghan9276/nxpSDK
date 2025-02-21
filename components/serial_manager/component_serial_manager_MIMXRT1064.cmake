include_guard()
message("component_serial_manager component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_component_serial_manager.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


#OR Logic component
if(CONFIG_USE_component_serial_manager_uart_MIMXRT1064)
     include(component_serial_manager_uart_MIMXRT1064)
endif()
if(CONFIG_USE_component_serial_manager_usb_cdc_MIMXRT1064)
     include(component_serial_manager_usb_cdc_MIMXRT1064)
endif()
if(CONFIG_USE_component_serial_manager_virtual_MIMXRT1064)
     include(component_serial_manager_virtual_MIMXRT1064)
endif()
if(CONFIG_USE_component_serial_manager_swo_MIMXRT1064)
     include(component_serial_manager_swo_MIMXRT1064)
endif()
if(CONFIG_USE_component_serial_manager_rpmsg_MIMXRT1064)
     include(component_serial_manager_rpmsg_MIMXRT1064)
endif()
if(CONFIG_USE_component_serial_manager_spi_MIMXRT1064)
     include(component_serial_manager_spi_MIMXRT1064)
endif()
if(NOT (CONFIG_USE_component_serial_manager_uart_MIMXRT1064 OR CONFIG_USE_component_serial_manager_usb_cdc_MIMXRT1064 OR CONFIG_USE_component_serial_manager_virtual_MIMXRT1064 OR CONFIG_USE_component_serial_manager_swo_MIMXRT1064 OR CONFIG_USE_component_serial_manager_rpmsg_MIMXRT1064 OR CONFIG_USE_component_serial_manager_spi_MIMXRT1064))
    message(WARNING "Since component_serial_manager_uart_MIMXRT1064/component_serial_manager_usb_cdc_MIMXRT1064/component_serial_manager_virtual_MIMXRT1064/component_serial_manager_swo_MIMXRT1064/component_serial_manager_rpmsg_MIMXRT1064/component_serial_manager_spi_MIMXRT1064 is not included at first or config in config.cmake file, use component_serial_manager_uart_MIMXRT1064 by default.")
    include(component_serial_manager_uart_MIMXRT1064)
endif()

include(driver_common_MIMXRT1064)

include(component_lists_MIMXRT1064)

