include_guard()
message("middleware_usb_pd_phy_ptn5110 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/pd/ptn5110/usb_pd_ptn5110_connect.c
    ${CMAKE_CURRENT_LIST_DIR}/pd/ptn5110/usb_pd_ptn5110_hal.c
    ${CMAKE_CURRENT_LIST_DIR}/pd/ptn5110/usb_pd_ptn5110_interface.c
    ${CMAKE_CURRENT_LIST_DIR}/pd/ptn5110/usb_pd_ptn5110_msg.c
    ${CMAKE_CURRENT_LIST_DIR}/pd/usb_pd_timer.c
    ${CMAKE_CURRENT_LIST_DIR}/pd/phy_interface/usb_pd_i2c.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/pd/ptn5110
    ${CMAKE_CURRENT_LIST_DIR}/pd
    ${CMAKE_CURRENT_LIST_DIR}/pd/phy_interface
)


include(component_igpio_adapter_MIMXRT1015)

include(component_lpi2c_adapter_MIMXRT1015)

include(component_osa_MIMXRT1015)

include(middleware_usb_common_header_MIMXRT1015)

