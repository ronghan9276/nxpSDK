include_guard()
message("middleware_edgefast_wifi component is included.")


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

include(middleware_wifi_MIMXRT1064)

