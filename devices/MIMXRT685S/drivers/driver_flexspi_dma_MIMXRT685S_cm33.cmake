include_guard()
message("driver_flexspi_dma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_flexspi_dma.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_flexspi_MIMXRT685S_cm33)

include(driver_lpc_dma_MIMXRT685S_cm33)

