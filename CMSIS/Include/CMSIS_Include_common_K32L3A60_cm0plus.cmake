if(NOT CMSIS_INCLUDE_COMMON_K32L3A60_cm0plus_INCLUDED)
    
    set(CMSIS_INCLUDE_COMMON_K32L3A60_cm0plus_INCLUDED true CACHE BOOL "CMSIS_Include_common component is included.")


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

endif()
