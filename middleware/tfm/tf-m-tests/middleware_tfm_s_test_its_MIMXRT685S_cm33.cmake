include_guard()
message("middleware_tfm_s_test_its component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/test/secure_fw/suites/its/its_tests_common.c
    ${CMAKE_CURRENT_LIST_DIR}/test/secure_fw/suites/its/secure/psa_its_s_interface_testsuite.c
    ${CMAKE_CURRENT_LIST_DIR}/test/secure_fw/suites/its/secure/psa_its_s_reliability_testsuite.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/test/secure_fw/suites/its
    ${CMAKE_CURRENT_LIST_DIR}/test/secure_fw/suites/its/secure
)


