include_guard()
message("middleware_freertos-aws_iot_libraries_freertos_plus_standard_utils component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/libraries/freertos_plus/standard/utils/src/iot_system_init.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/libraries/freertos_plus/standard/utils/include
)


include(middleware_freertos-kernel_MIMXRT1166_cm7)

include(middleware_freertos-aws_iot_libraries_freertos_plus_standard_crypto_MIMXRT1166_cm7)

include(middleware_freertos-aws_iot_libraries_abstractions_secure_sockets_MIMXRT1166_cm7)

