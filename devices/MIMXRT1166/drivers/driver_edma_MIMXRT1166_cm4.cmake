include_guard()
message("driver_edma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_edma.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_memory_MIMXRT1166_cm4)

include(driver_common_MIMXRT1166_cm4)

include(driver_dmamux_MIMXRT1166_cm4)

