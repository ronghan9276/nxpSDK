include_guard()
message("driver_tfa9896 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_hal_registers.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_tfa9896.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_common_MIMXRT595S_cm33)

include(component_codec_i2c_MIMXRT595S_cm33)

