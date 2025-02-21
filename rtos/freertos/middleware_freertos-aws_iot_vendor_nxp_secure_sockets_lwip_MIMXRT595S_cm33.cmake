include_guard()
message("middleware_freertos-aws_iot_vendor_nxp_secure_sockets_lwip component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/vendors/nxp/secure_sockets/lwip/iot_secure_sockets.c
)


include(middleware_freertos-aws_iot_libraries_abstractions_secure_sockets_MIMXRT595S_cm33)

include(middleware_freertos-aws_iot_libraries_freertos_plus_standard_tls_MIMXRT595S_cm33)

include(middleware_lwip_MIMXRT595S_cm33)

include(middleware_freertos-kernel_MIMXRT595S_cm33)

