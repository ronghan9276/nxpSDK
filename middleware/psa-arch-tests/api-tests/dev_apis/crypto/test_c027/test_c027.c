/** @file
 * Copyright (c) 2019-2020, Arm Limited or its affiliates. All rights reserved.
 * SPDX-License-Identifier : Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/

#include "val_interfaces.h"
#include "val_target.h"
#include "test_c027.h"
#include "test_data.h"

const client_test_t test_c027_crypto_list[] = {
    NULL,
    psa_mac_update_test,
    psa_mac_update_invalid_operator_test,
    NULL,
};

static uint32_t g_test_count = 1;
//NXP static uint8_t  data[BUFFER_SIZE];

int32_t psa_mac_update_test(caller_security_t caller __UNUSED)
{
    uint8_t  data[BUFFER_SIZE];
    int                   num_checks = sizeof(check1)/sizeof(check1[0]);
    int32_t               i, status;
    size_t                length;
    psa_mac_operation_t   operation;
    psa_key_attributes_t  attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_key_handle_t      key_handle;

    if (num_checks == 0)
    {
        val->print(PRINT_TEST, "No test available for the selected crypto configuration\n", 0);
        return RESULT_SKIP(VAL_STATUS_NO_TESTS);
    }

    /* Initialize the PSA crypto library*/
    status = val->crypto_function(VAL_CRYPTO_INIT);
    TEST_ASSERT_EQUAL(status, PSA_SUCCESS, TEST_CHECKPOINT_NUM(1));

    for (i = 0; i < num_checks; i++)
    {
        val->print(PRINT_TEST, "[Check %d] ", g_test_count++);
        val->print(PRINT_TEST, check1[i].test_desc, 0);
        memset(&operation, 0, sizeof(operation));
        memset(data, 0, sizeof(data));

        /* Setting up the watchdog timer for each check */
        status = val->wd_reprogram_timer(WD_CRYPTO_TIMEOUT);
        TEST_ASSERT_EQUAL(status, VAL_STATUS_SUCCESS, TEST_CHECKPOINT_NUM(2));

        /* Setup the attributes for the key */
        val->crypto_function(VAL_CRYPTO_SET_KEY_TYPE, &attributes, check1[i].key_type);
        val->crypto_function(VAL_CRYPTO_SET_KEY_USAGE_FLAGS, &attributes, check1[i].usage);
        val->crypto_function(VAL_CRYPTO_SET_KEY_ALGORITHM, &attributes, check1[i].key_alg);

        /* Import the key data into the key slot */
        status = val->crypto_function(VAL_CRYPTO_IMPORT_KEY, &attributes, check1[i].key_data,
                 check1[i].key_length, &key_handle);
        TEST_ASSERT_EQUAL(status, PSA_SUCCESS, TEST_CHECKPOINT_NUM(3));

        /* Start a multipart MAC calculation operation */
        status = val->crypto_function(VAL_CRYPTO_MAC_SIGN_SETUP, &operation,
                    key_handle, check1[i].key_alg);
        TEST_ASSERT_EQUAL(status, PSA_SUCCESS, TEST_CHECKPOINT_NUM(4));

        /* Add a message fragment to a multipart MAC operation */
        status = val->crypto_function(VAL_CRYPTO_MAC_UPDATE, &operation, check1[i].data,
                    check1[i].data_size);
        TEST_ASSERT_EQUAL(status, check1[i].expected_status, TEST_CHECKPOINT_NUM(5));

        if (check1[i].expected_status != PSA_SUCCESS)
        {
            /* Abort a MAC operation */
            status = val->crypto_function(VAL_CRYPTO_MAC_ABORT, &operation);
            TEST_ASSERT_EQUAL(status, PSA_SUCCESS, TEST_CHECKPOINT_NUM(6));

            /* Destroy the key */
            status = val->crypto_function(VAL_CRYPTO_DESTROY_KEY, key_handle);
            TEST_ASSERT_EQUAL(status, PSA_SUCCESS, TEST_CHECKPOINT_NUM(7));

            continue;
        }

        /* Finish the calculation of the MAC of a message */
        status = val->crypto_function(VAL_CRYPTO_MAC_SIGN_FINISH, &operation, data,
                    sizeof(data), &length);
        TEST_ASSERT_EQUAL(status, PSA_SUCCESS, TEST_CHECKPOINT_NUM(8));

        /* Add a message fragment to the same multipart MAC operation*/
        status = val->crypto_function(VAL_CRYPTO_MAC_UPDATE, &operation, check1[i].data,
                    check1[i].data_size);
        TEST_ASSERT_EQUAL(status, PSA_ERROR_BAD_STATE, TEST_CHECKPOINT_NUM(9));

        /* Abort a MAC operation */
        status = val->crypto_function(VAL_CRYPTO_MAC_ABORT, &operation);
        TEST_ASSERT_EQUAL(status, PSA_SUCCESS, TEST_CHECKPOINT_NUM(10));

        /* Destroy the key */
        status = val->crypto_function(VAL_CRYPTO_DESTROY_KEY, key_handle);
        TEST_ASSERT_EQUAL(status, PSA_SUCCESS, TEST_CHECKPOINT_NUM(11));
    }

    return VAL_STATUS_SUCCESS;
}

int32_t psa_mac_update_invalid_operator_test(caller_security_t caller __UNUSED)
{
    uint8_t  data[BUFFER_SIZE];
    int32_t             i, status;
    psa_mac_operation_t operation[] = {psa_mac_operation_init(), PSA_MAC_OPERATION_INIT, {0} };
    int32_t             operation_count = sizeof(operation)/sizeof(operation[0]);

    memset(data, 0, sizeof(data));
    val->print(PRINT_TEST, "[Check %d] ", g_test_count++);
    val->print(PRINT_TEST, "Test psa_mac_update without mac setup\n", 0);

    /* Initialize the PSA crypto library*/
    status = val->crypto_function(VAL_CRYPTO_INIT);
    TEST_ASSERT_EQUAL(status, PSA_SUCCESS, TEST_CHECKPOINT_NUM(1));

    for (i = 0; i < operation_count; i++)
    {

        /* Start a multipart MAC calculation for each operation */
        status = val->crypto_function(VAL_CRYPTO_MAC_UPDATE, &operation[i], data,
                     sizeof(data)/sizeof(data[0]));
        TEST_ASSERT_EQUAL(status, PSA_ERROR_BAD_STATE, TEST_CHECKPOINT_NUM(2));

        /* Abort the MAC operations */
        status = val->crypto_function(VAL_CRYPTO_MAC_ABORT, &operation[i]);
        TEST_ASSERT_EQUAL(status, PSA_SUCCESS, TEST_CHECKPOINT_NUM(3));
    }

    return VAL_STATUS_SUCCESS;
}
