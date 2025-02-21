include_guard()
message("middleware_multicore_mcmgr_imxrt1160 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/mcmgr/src/mcmgr_internal_core_api_imxrt1160.c
    ${CMAKE_CURRENT_LIST_DIR}/mcmgr/src/mcmgr_mu_internal.c
)


include(middleware_multicore_mcmgr_MIMXRT1166_cm4)

include(driver_mu_MIMXRT1166_cm4)

