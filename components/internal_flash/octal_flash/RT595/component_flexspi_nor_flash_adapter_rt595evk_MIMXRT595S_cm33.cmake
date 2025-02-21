include_guard()
message("component_flexspi_nor_flash_adapter_rt595evk component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_flexspi_nor_flash.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_common_MIMXRT595S_cm33)

include(driver_flexspi_MIMXRT595S_cm33)

include(component_flexspi_nor_flash_adapter_MIMXRT595S_cm33)

