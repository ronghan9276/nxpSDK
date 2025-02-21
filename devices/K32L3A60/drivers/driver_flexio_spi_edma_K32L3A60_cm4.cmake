if(NOT DRIVER_FLEXIO_SPI_EDMA_K32L3A60_cm4_INCLUDED)
    
    set(DRIVER_FLEXIO_SPI_EDMA_K32L3A60_cm4_INCLUDED true CACHE BOOL "driver_flexio_spi_edma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_flexio_spi_edma.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_edma_K32L3A60_cm4)

    include(driver_flexio_spi_K32L3A60_cm4)

endif()
