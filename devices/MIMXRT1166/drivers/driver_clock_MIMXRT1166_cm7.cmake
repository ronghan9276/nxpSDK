include_guard()
message("driver_clock component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_clock.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_common_MIMXRT1166_cm7)

include(driver_anatop_ai_MIMXRT1166_cm7)

include(driver_pmu_1_MIMXRT1166_cm7)

