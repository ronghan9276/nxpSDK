if(NOT MIDDLEWARE_USB_DEVICE_CONTROLLER_DRIVER_MIMXRT117H_INCLUDED)
    
    set(MIDDLEWARE_USB_DEVICE_CONTROLLER_DRIVER_MIMXRT117H_INCLUDED true CACHE BOOL "middleware_usb_device_controller_driver component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/device/usb_device_dci.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/device
    )


    #OR Logic component
    if(CONFIG_USE_middleware_usb_device_khci_MIMXRT117H)
         include(middleware_usb_device_khci_MIMXRT117H)
    endif()
    if(CONFIG_USE_middleware_usb_device_ehci_MIMXRT117H)
         include(middleware_usb_device_ehci_MIMXRT117H)
    endif()
    if(CONFIG_USE_middleware_usb_device_ip3511fs_MIMXRT117H)
         include(middleware_usb_device_ip3511fs_MIMXRT117H)
    endif()
    if(CONFIG_USE_middleware_usb_device_ip3511hs_MIMXRT117H)
         include(middleware_usb_device_ip3511hs_MIMXRT117H)
    endif()
    if(NOT (CONFIG_USE_middleware_usb_device_khci_MIMXRT117H OR CONFIG_USE_middleware_usb_device_ehci_MIMXRT117H OR CONFIG_USE_middleware_usb_device_ip3511fs_MIMXRT117H OR CONFIG_USE_middleware_usb_device_ip3511hs_MIMXRT117H))
        message(WARNING "Since middleware_usb_device_khci_MIMXRT117H/middleware_usb_device_ehci_MIMXRT117H/middleware_usb_device_ip3511fs_MIMXRT117H/middleware_usb_device_ip3511hs_MIMXRT117H is not included at first or config in config.cmake file, use middleware_usb_device_khci_MIMXRT117H by default.")
        include(middleware_usb_device_khci_MIMXRT117H)
    endif()

    include(component_osa_MIMXRT117H)

endif()
