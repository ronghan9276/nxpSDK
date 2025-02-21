include_guard()
message("middleware_lwip_apps_lwiperf component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/apps/lwiperf/lwiperf.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/include/lwip/apps
)


#OR Logic component
if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1021)
     include(middleware_freertos-kernel_MIMXRT1021)
endif()
if(CONFIG_USE_middleware_baremetal_MIMXRT1021)
     include(middleware_baremetal_MIMXRT1021)
endif()
if(NOT (CONFIG_USE_middleware_freertos-kernel_MIMXRT1021 OR CONFIG_USE_middleware_baremetal_MIMXRT1021))
    message(WARNING "Since middleware_freertos-kernel_MIMXRT1021/middleware_baremetal_MIMXRT1021 is not included at first or config in config.cmake file, use middleware_freertos-kernel_MIMXRT1021 by default.")
    include(middleware_freertos-kernel_MIMXRT1021)
endif()

include(middleware_lwip_MIMXRT1021)

