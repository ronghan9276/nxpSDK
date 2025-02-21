if(NOT MIDDLEWARE_MCU-BOOT_DRV_MICROSECONDS_MKV31F51212_INCLUDED)
    
    set(MIDDLEWARE_MCU-BOOT_DRV_MICROSECONDS_MKV31F51212_INCLUDED true CACHE BOOL "middleware_mcu-boot_drv_microseconds component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/drivers/microseconds/src/microseconds_sysclk.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/drivers/microseconds
    )


endif()
