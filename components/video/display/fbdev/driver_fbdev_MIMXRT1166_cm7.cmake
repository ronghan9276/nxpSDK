include_guard()
message("driver_fbdev component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_fbdev.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_dc-fb-common_MIMXRT1166_cm7)

include(middleware_freertos-kernel_MIMXRT1166_cm7)

