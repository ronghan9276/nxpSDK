if(NOT MIDDLEWARE_FMSTR_K32L3A60_cm4_INCLUDED)
    
    set(MIDDLEWARE_FMSTR_K32L3A60_cm4_INCLUDED true CACHE BOOL "middleware_fmstr component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/common/freemaster_appcmd.c
        ${CMAKE_CURRENT_LIST_DIR}/src/common/freemaster_pipes.c
        ${CMAKE_CURRENT_LIST_DIR}/src/common/freemaster_protocol.c
        ${CMAKE_CURRENT_LIST_DIR}/src/common/freemaster_rec.c
        ${CMAKE_CURRENT_LIST_DIR}/src/common/freemaster_scope.c
        ${CMAKE_CURRENT_LIST_DIR}/src/common/freemaster_tsa.c
        ${CMAKE_CURRENT_LIST_DIR}/src/common/freemaster_ures.c
        ${CMAKE_CURRENT_LIST_DIR}/src/common/freemaster_utils.c
        ${CMAKE_CURRENT_LIST_DIR}/src/common/freemaster_can.c
        ${CMAKE_CURRENT_LIST_DIR}/src/common/freemaster_sha.c
        ${CMAKE_CURRENT_LIST_DIR}/src/common/freemaster_pdbdm.c
        ${CMAKE_CURRENT_LIST_DIR}/src/common/freemaster_serial.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/common
    )


endif()
