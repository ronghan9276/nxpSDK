if(NOT UTILITIES_MISC_UTILITIES_K32L3A60_cm4_INCLUDED)
    
    set(UTILITIES_MISC_UTILITIES_K32L3A60_cm4_INCLUDED true CACHE BOOL "utilities_misc_utilities component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_sbrk.c
    )


endif()
