include_guard()
message("middleware_freertos-aws_iot_libraries_abstractions_pkcs11 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/libraries/abstractions/pkcs11/corePKCS11/source/core_pkcs11.c
    ${CMAKE_CURRENT_LIST_DIR}/libraries/abstractions/pkcs11/corePKCS11/source/core_pki_utils.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/libraries/abstractions/pkcs11/corePKCS11/source/include
)


include(middleware_freertos-aws_iot_libraries_3rdparty_pkcs11_MIMXRT595S_cm33)

