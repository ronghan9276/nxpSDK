include_guard()
message("middleware_freertos-aws_iot_demos_shadow component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/demos/device_shadow_for_aws/shadow_demo_main.c
)


include(middleware_freertos-aws_iot_demos_MIMXRT595S_cm33)

include(middleware_freertos-aws_iot_libraries_abstractions_transport_MIMXRT595S_cm33)

include(middleware_freertos-aws_iot_libraries_corejason_MIMXRT595S_cm33)

include(middleware_freertos-aws_iot_libraries_device_shadow_for_aws_MIMXRT595S_cm33)

include(middleware_freertos-aws_iot_mqtt_demo_helpers_MIMXRT595S_cm33)

include(middleware_freertos-kernel_MIMXRT595S_cm33)

