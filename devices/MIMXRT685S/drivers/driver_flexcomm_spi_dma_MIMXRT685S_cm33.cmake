include_guard()
message("driver_flexcomm_spi_dma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_spi_dma.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_flexcomm_MIMXRT685S_cm33)

include(driver_flexcomm_spi_MIMXRT685S_cm33)

include(driver_lpc_dma_MIMXRT685S_cm33)

