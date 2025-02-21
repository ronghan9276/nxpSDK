if(NOT DRIVER_VIDEO-I2C_MIMXRT117H_INCLUDED)
    
    set(DRIVER_VIDEO-I2C_MIMXRT117H_INCLUDED true CACHE BOOL "driver_video-i2c component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_video_i2c.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common_MIMXRT117H)

endif()
