include_guard()
message("driver_cmsis_lpspi component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_lpspi_cmsis.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_lpspi_edma_MIMXRT1042)

include(driver_lpspi_MIMXRT1042)

include(CMSIS_Driver_Include_SPI_MIMXRT1042)

