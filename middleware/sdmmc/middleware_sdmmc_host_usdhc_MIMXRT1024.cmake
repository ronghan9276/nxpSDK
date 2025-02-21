include_guard()
message("middleware_sdmmc_host_usdhc component is included.")


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/host/usdhc
)

#OR Logic component
if(CONFIG_USE_middleware_sdmmc_host_usdhc_freertos_MIMXRT1024)
     include(middleware_sdmmc_host_usdhc_freertos_MIMXRT1024)
endif()
if(CONFIG_USE_middleware_sdmmc_host_usdhc_interrupt_MIMXRT1024)
     include(middleware_sdmmc_host_usdhc_interrupt_MIMXRT1024)
endif()
if(CONFIG_USE_middleware_sdmmc_host_usdhc_polling_MIMXRT1024)
     include(middleware_sdmmc_host_usdhc_polling_MIMXRT1024)
endif()
if(CONFIG_USE_middleware_sdmmc_host_usdhc_azurertos_MIMXRT1024)
     include(middleware_sdmmc_host_usdhc_azurertos_MIMXRT1024)
endif()
if(NOT (CONFIG_USE_middleware_sdmmc_host_usdhc_freertos_MIMXRT1024 OR CONFIG_USE_middleware_sdmmc_host_usdhc_interrupt_MIMXRT1024 OR CONFIG_USE_middleware_sdmmc_host_usdhc_polling_MIMXRT1024 OR CONFIG_USE_middleware_sdmmc_host_usdhc_azurertos_MIMXRT1024))
    message(WARNING "Since middleware_sdmmc_host_usdhc_freertos_MIMXRT1024/middleware_sdmmc_host_usdhc_interrupt_MIMXRT1024/middleware_sdmmc_host_usdhc_polling_MIMXRT1024/middleware_sdmmc_host_usdhc_azurertos_MIMXRT1024 is not included at first or config in config.cmake file, use middleware_sdmmc_host_usdhc_interrupt_MIMXRT1024 by default.")
    include(middleware_sdmmc_host_usdhc_interrupt_MIMXRT1024)
endif()

