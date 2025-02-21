if(NOT MIDDLEWARE_FREERTOS-AWS_IOT_VENDOR_NXP_PKCS11_MIMXRT1176_cm4_INCLUDED)
    
    set(MIDDLEWARE_FREERTOS-AWS_IOT_VENDOR_NXP_PKCS11_MIMXRT1176_cm4_INCLUDED true CACHE BOOL "middleware_freertos-aws_iot_vendor_nxp_pkcs11 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/vendors/nxp/pkcs11/common/iot_pkcs11_pal.c
    )


    include(middleware_freertos-kernel_MIMXRT1176_cm4)

    include(middleware_freertos-aws_iot_libraries_freertos_plus_standard_crypto_MIMXRT1176_cm4)

    include(middleware_freertos-aws_iot_libraries_freertos_plus_standard_pkcs11_MIMXRT1176_cm4)

    include(component_mflash_file_MIMXRT1176_cm4)

endif()
