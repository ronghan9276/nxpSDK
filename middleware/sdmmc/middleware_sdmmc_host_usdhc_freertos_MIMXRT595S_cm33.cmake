include_guard()
message("middleware_sdmmc_host_usdhc_freertos component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/host/usdhc/non_blocking/fsl_sdmmc_host.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/host/usdhc
)


include(middleware_sdmmc_common_MIMXRT595S_cm33)

include(middleware_sdmmc_osa_freertos_MIMXRT595S_cm33)

include(driver_usdhc_MIMXRT595S_cm33)

