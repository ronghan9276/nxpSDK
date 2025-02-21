include_guard()
message("middleware_freertos-aws_iot_vendor_nxp_wifi component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/vendors/nxp/wifi/nxp/iot_wifi.c
)


include(middleware_freertos-aws_iot_libraries_abstractions_wifi_MIMXRT1062)

include(middleware_wifi_MIMXRT1062)

