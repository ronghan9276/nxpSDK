if(NOT MIDDLEWARE_USB_HOST_CDC_K32L2A41A_INCLUDED)
    
    set(MIDDLEWARE_USB_HOST_CDC_K32L2A41A_INCLUDED true CACHE BOOL "middleware_usb_host_cdc component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/host/class/usb_host_cdc.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/host/class
    )


    include(middleware_usb_host_stack_K32L2A41A)

endif()
