if(NOT MIDDLEWARE_USB_DEVICE_STACK_EXTERNAL_K32L2A41A_INCLUDED)
    
    set(MIDDLEWARE_USB_DEVICE_STACK_EXTERNAL_K32L2A41A_INCLUDED true CACHE BOOL "middleware_usb_device_stack_external component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/output/source/device/class/usb_device_class.c
        ${CMAKE_CURRENT_LIST_DIR}/output/source/device/usb_device_ch9.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/output/source/device/class
        ${CMAKE_CURRENT_LIST_DIR}/output/source/device
    )


    include(component_osa_K32L2A41A)

    include(middleware_usb_device_controller_driver_K32L2A41A)

endif()
