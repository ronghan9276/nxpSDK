include_guard()
message("middleware_se_hostlib_serial_manager_usb_cdc component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/hostlib/hostLib/vcom/ksdk/usb_device_descriptor.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/hostlib/hostLib/vcom/ksdk
)


include(middleware_usb_device_cdc_external_MIMXRT1062)

include(driver_common_MIMXRT1062)

