if(NOT MIDDLEWARE_MULTICORE_ERPC_ERPC_MU_TRANSPORT_K32L3A60_cm4_INCLUDED)
    
    set(MIDDLEWARE_MULTICORE_ERPC_ERPC_MU_TRANSPORT_K32L3A60_cm4_INCLUDED true CACHE BOOL "middleware_multicore_erpc_eRPC_mu_transport component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/erpc/erpc_c/transports/erpc_mu_transport.cpp
        ${CMAKE_CURRENT_LIST_DIR}/erpc/erpc_c/setup/erpc_setup_mbf_dynamic.cpp
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/erpc/erpc_c/transports
    )


    include(middleware_multicore_erpc_common_K32L3A60_cm4)

endif()
