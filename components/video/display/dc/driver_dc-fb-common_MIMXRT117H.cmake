if(NOT DRIVER_DC-FB-COMMON_MIMXRT117H_INCLUDED)
    
    set(DRIVER_DC-FB-COMMON_MIMXRT117H_INCLUDED true CACHE BOOL "driver_dc-fb-common component is included.")


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    include(driver_video-common_MIMXRT117H)

endif()
