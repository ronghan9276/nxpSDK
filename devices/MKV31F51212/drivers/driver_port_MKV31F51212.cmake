if(NOT DRIVER_PORT_MKV31F51212_INCLUDED)
    
    set(DRIVER_PORT_MKV31F51212_INCLUDED true CACHE BOOL "driver_port component is included.")


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    include(driver_common_MKV31F51212)

endif()
