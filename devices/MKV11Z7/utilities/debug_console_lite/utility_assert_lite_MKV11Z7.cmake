if(NOT UTILITY_ASSERT_LITE_MKV11Z7_INCLUDED)
    
    set(UTILITY_ASSERT_LITE_MKV11Z7_INCLUDED true CACHE BOOL "utility_assert_lite component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_assert.c
    )


    include(utility_debug_console_lite_MKV11Z7)

endif()
