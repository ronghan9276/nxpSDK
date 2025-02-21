include_guard()
message("middleware_psatest_ns_initial_attestation_2 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/lib/ext/qcbor/src/ieee754.c
    ${CMAKE_CURRENT_LIST_DIR}/lib/ext/qcbor/src/qcbor_decode.c
    ${CMAKE_CURRENT_LIST_DIR}/lib/ext/qcbor/src/qcbor_encode.c
    ${CMAKE_CURRENT_LIST_DIR}/lib/ext/qcbor/src/UsefulBuf.c
    ${CMAKE_CURRENT_LIST_DIR}/platform/ext/common/template/tfm_initial_attest_pub_key.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/lib/ext/t_cose/inc
    ${CMAKE_CURRENT_LIST_DIR}/lib/ext/qcbor/src
    ${CMAKE_CURRENT_LIST_DIR}/lib/ext/qcbor/inc
    ${CMAKE_CURRENT_LIST_DIR}/lib/ext/qcbor/util
    ${CMAKE_CURRENT_LIST_DIR}/secure_fw/partitions/initial_attestation
)


