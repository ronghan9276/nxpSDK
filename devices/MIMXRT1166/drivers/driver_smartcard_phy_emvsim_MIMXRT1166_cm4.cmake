include_guard()
message("driver_smartcard_phy_emvsim component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_smartcard_phy_emvsim.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_smartcard_emvsim_MIMXRT1166_cm4)

include(driver_common_MIMXRT1166_cm4)

