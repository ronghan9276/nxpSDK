include_guard()
message("middleware_mcu-boot_MIMXRT1042_drivers component is included.")


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/targets/MIMXRT1042/src
)

