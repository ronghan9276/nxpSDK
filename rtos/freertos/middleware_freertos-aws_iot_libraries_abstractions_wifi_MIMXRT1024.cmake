if(NOT MIDDLEWARE_FREERTOS-AWS_IOT_LIBRARIES_ABSTRACTIONS_WIFI_MIMXRT1024_INCLUDED)
    
    set(MIDDLEWARE_FREERTOS-AWS_IOT_LIBRARIES_ABSTRACTIONS_WIFI_MIMXRT1024_INCLUDED true CACHE BOOL "middleware_freertos-aws_iot_libraries_abstractions_wifi component is included.")


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/libraries/abstractions/wifi/include
    )

    include(middleware_freertos-aws_iot_common_MIMXRT1024)

    include(middleware_freertos-kernel_MIMXRT1024)

endif()
