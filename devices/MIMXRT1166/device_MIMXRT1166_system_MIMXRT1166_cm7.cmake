include_guard()
message("device_MIMXRT1166_system component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/system_MIMXRT1166_cm7.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(device_MIMXRT1166_CMSIS_MIMXRT1166_cm7)

