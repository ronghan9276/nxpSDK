/*
 * Copyright (c) 2018-2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*********** WARNING: This is an auto-generated file. Do not edit! ***********/

#ifndef __TFM_SERVICE_LIST_INC__
#define __TFM_SERVICE_LIST_INC__

#ifdef TFM_PARTITION_PROTECTED_STORAGE
#include "secure_fw/partitions/protected_storage/psa_manifest/tfm_protected_storage.h"
#endif /* TFM_PARTITION_PROTECTED_STORAGE */

#ifdef TFM_PARTITION_INTERNAL_TRUSTED_STORAGE
#include "secure_fw/partitions/internal_trusted_storage/psa_manifest/tfm_internal_trusted_storage.h"
#endif /* TFM_PARTITION_INTERNAL_TRUSTED_STORAGE */

#ifdef TFM_PARTITION_AUDIT_LOG
#include "secure_fw/partitions/audit_logging/psa_manifest/tfm_audit_logging.h"
#endif /* TFM_PARTITION_AUDIT_LOG */

#ifdef TFM_PARTITION_CRYPTO
#include "secure_fw/partitions/crypto/psa_manifest/tfm_crypto.h"
#endif /* TFM_PARTITION_CRYPTO */

#ifdef TFM_PARTITION_PLATFORM
#include "secure_fw/partitions/platform/psa_manifest/tfm_platform.h"
#endif /* TFM_PARTITION_PLATFORM */

#ifdef TFM_PARTITION_INITIAL_ATTESTATION
#include "secure_fw/partitions/initial_attestation/psa_manifest/tfm_initial_attestation.h"
#endif /* TFM_PARTITION_INITIAL_ATTESTATION */

#ifdef TFM_PARTITION_TEST_CORE
#include "test_services/tfm_core_test/psa_manifest/tfm_ss_core_test.h"
#endif /* TFM_PARTITION_TEST_CORE */

#ifdef TFM_PARTITION_TEST_CORE
#include "test_services/tfm_core_test_2/psa_manifest/tfm_ss_core_test_2.h"
#endif /* TFM_PARTITION_TEST_CORE */

#ifdef TFM_PARTITION_TEST_SECURE_SERVICES
#include "test_services/tfm_secure_client_service/psa_manifest/tfm_secure_client_service.h"
#endif /* TFM_PARTITION_TEST_SECURE_SERVICES */

#ifdef TFM_PARTITION_TEST_CORE_IPC
#include "test_services/tfm_ipc_service/psa_manifest/tfm_ipc_service_test.h"
#endif /* TFM_PARTITION_TEST_CORE_IPC */

#ifdef TFM_PARTITION_TEST_CORE_IPC
#include "test_services/tfm_ipc_client/psa_manifest/tfm_ipc_client_test.h"
#endif /* TFM_PARTITION_TEST_CORE_IPC */

#ifdef TFM_ENABLE_IRQ_TEST
#include "test_services/tfm_irq_test_service_1/psa_manifest/tfm_irq_test_service_1.h"
#endif /* TFM_ENABLE_IRQ_TEST */

#ifdef TFM_PARTITION_TEST_PS
#include "test_services/tfm_ps_test_service/psa_manifest/tfm_ps_test_service.h"
#endif /* TFM_PARTITION_TEST_PS */

#ifdef TFM_PARTITION_TEST_SECURE_SERVICES
#include "test_services/tfm_secure_client_2/psa_manifest/tfm_secure_client_2.h"
#endif /* TFM_PARTITION_TEST_SECURE_SERVICES */

#ifdef TFM_PARTITION_PSA_PROXY
#include "secure_fw/partitions/psa_proxy/psa_manifest/tfm_psa_proxy.h"
#endif /* TFM_PARTITION_PSA_PROXY */

#ifdef TFM_PARTITION_FIRMWARE_UPDATE
#include "secure_fw/partitions/firmware_update/psa_manifest/tfm_firmware_update.h"
#endif /* TFM_PARTITION_FIRMWARE_UPDATE */

#ifdef TFM_PARTITION_FFM11
#include "secure_fw/partitions/tfm_ffm11_partition/psa_manifest/tfm_ffm11_partition.h"
#endif /* TFM_PARTITION_FFM11 */


const struct tfm_spm_service_db_t service_db[] =
{
#ifdef TFM_PARTITION_PROTECTED_STORAGE
    /******** TFM_SP_PS ********/
    {
        .name = "TFM_PS_SET",
        .partition_id = TFM_SP_PS,
        .signal = TFM_PS_SET_SIGNAL,
        .sid = 0x00000060,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_PS_GET",
        .partition_id = TFM_SP_PS,
        .signal = TFM_PS_GET_SIGNAL,
        .sid = 0x00000061,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_PS_GET_INFO",
        .partition_id = TFM_SP_PS,
        .signal = TFM_PS_GET_INFO_SIGNAL,
        .sid = 0x00000062,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_PS_REMOVE",
        .partition_id = TFM_SP_PS,
        .signal = TFM_PS_REMOVE_SIGNAL,
        .sid = 0x00000063,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_PS_GET_SUPPORT",
        .partition_id = TFM_SP_PS,
        .signal = TFM_PS_GET_SUPPORT_SIGNAL,
        .sid = 0x00000064,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
#endif /* TFM_PARTITION_PROTECTED_STORAGE */

#ifdef TFM_PARTITION_INTERNAL_TRUSTED_STORAGE
    /******** TFM_SP_ITS ********/
    {
        .name = "TFM_ITS_SET",
        .partition_id = TFM_SP_ITS,
        .signal = TFM_ITS_SET_SIGNAL,
        .sid = 0x00000070,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_ITS_GET",
        .partition_id = TFM_SP_ITS,
        .signal = TFM_ITS_GET_SIGNAL,
        .sid = 0x00000071,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_ITS_GET_INFO",
        .partition_id = TFM_SP_ITS,
        .signal = TFM_ITS_GET_INFO_SIGNAL,
        .sid = 0x00000072,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_ITS_REMOVE",
        .partition_id = TFM_SP_ITS,
        .signal = TFM_ITS_REMOVE_SIGNAL,
        .sid = 0x00000073,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
#endif /* TFM_PARTITION_INTERNAL_TRUSTED_STORAGE */

#ifdef TFM_PARTITION_CRYPTO
    /******** TFM_SP_CRYPTO ********/
    {
        .name = "TFM_CRYPTO",
        .partition_id = TFM_SP_CRYPTO,
        .signal = TFM_CRYPTO_SIGNAL,
        .sid = 0x00000080,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
#endif /* TFM_PARTITION_CRYPTO */

#ifdef TFM_PARTITION_PLATFORM
    /******** TFM_SP_PLATFORM ********/
    {
        .name = "TFM_SP_PLATFORM_SYSTEM_RESET",
        .partition_id = TFM_SP_PLATFORM,
        .signal = TFM_SP_PLATFORM_SYSTEM_RESET_SIGNAL,
        .sid = 0x00000040,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_SP_PLATFORM_IOCTL",
        .partition_id = TFM_SP_PLATFORM,
        .signal = TFM_SP_PLATFORM_IOCTL_SIGNAL,
        .sid = 0x00000041,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_SP_PLATFORM_NV_COUNTER",
        .partition_id = TFM_SP_PLATFORM,
        .signal = TFM_SP_PLATFORM_NV_COUNTER_SIGNAL,
        .sid = 0x00000042,
        .non_secure_client = false,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
#endif /* TFM_PARTITION_PLATFORM */

#ifdef TFM_PARTITION_INITIAL_ATTESTATION
    /******** TFM_SP_INITIAL_ATTESTATION ********/
    {
        .name = "TFM_ATTEST_GET_TOKEN",
        .partition_id = TFM_SP_INITIAL_ATTESTATION,
        .signal = TFM_ATTEST_GET_TOKEN_SIGNAL,
        .sid = 0x00000020,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_ATTEST_GET_TOKEN_SIZE",
        .partition_id = TFM_SP_INITIAL_ATTESTATION,
        .signal = TFM_ATTEST_GET_TOKEN_SIZE_SIGNAL,
        .sid = 0x00000021,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_ATTEST_GET_PUBLIC_KEY",
        .partition_id = TFM_SP_INITIAL_ATTESTATION,
        .signal = TFM_ATTEST_GET_PUBLIC_KEY_SIGNAL,
        .sid = 0x00000022,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
#endif /* TFM_PARTITION_INITIAL_ATTESTATION */

#ifdef TFM_PARTITION_TEST_CORE
    /******** TFM_SP_CORE_TEST ********/
    {
        .name = "SPM_CORE_TEST_INIT_SUCCESS",
        .partition_id = TFM_SP_CORE_TEST,
        .signal = SPM_CORE_TEST_INIT_SUCCESS_SIGNAL,
        .sid = 0x0000F020,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "SPM_CORE_TEST_DIRECT_RECURSION",
        .partition_id = TFM_SP_CORE_TEST,
        .signal = SPM_CORE_TEST_DIRECT_RECURSION_SIGNAL,
        .sid = 0x0000F021,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "SPM_CORE_TEST_SS_TO_SS",
        .partition_id = TFM_SP_CORE_TEST,
        .signal = SPM_CORE_TEST_SS_TO_SS_SIGNAL,
        .sid = 0x0000F024,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "SPM_CORE_TEST_SS_TO_SS_BUFFER",
        .partition_id = TFM_SP_CORE_TEST,
        .signal = SPM_CORE_TEST_SS_TO_SS_BUFFER_SIGNAL,
        .sid = 0x0000F025,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "SPM_CORE_TEST_OUTVEC_WRITE",
        .partition_id = TFM_SP_CORE_TEST,
        .signal = SPM_CORE_TEST_OUTVEC_WRITE_SIGNAL,
        .sid = 0x0000F026,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "SPM_CORE_TEST_PERIPHERAL_ACCESS",
        .partition_id = TFM_SP_CORE_TEST,
        .signal = SPM_CORE_TEST_PERIPHERAL_ACCESS_SIGNAL,
        .sid = 0x0000F027,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "SPM_CORE_TEST_GET_CALLER_CLIENT_ID",
        .partition_id = TFM_SP_CORE_TEST,
        .signal = SPM_CORE_TEST_GET_CALLER_CLIENT_ID_SIGNAL,
        .sid = 0x0000F028,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "SPM_CORE_TEST_SPM_REQUEST",
        .partition_id = TFM_SP_CORE_TEST,
        .signal = SPM_CORE_TEST_SPM_REQUEST_SIGNAL,
        .sid = 0x0000F029,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "SPM_CORE_TEST_BLOCK",
        .partition_id = TFM_SP_CORE_TEST,
        .signal = SPM_CORE_TEST_BLOCK_SIGNAL,
        .sid = 0x0000F02A,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "SPM_CORE_TEST_NS_THREAD",
        .partition_id = TFM_SP_CORE_TEST,
        .signal = SPM_CORE_TEST_NS_THREAD_SIGNAL,
        .sid = 0x0000F02B,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
#endif /* TFM_PARTITION_TEST_CORE */

#ifdef TFM_PARTITION_TEST_CORE
    /******** TFM_SP_CORE_TEST_2 ********/
    {
        .name = "SPM_CORE_TEST_2_SLAVE_SERVICE",
        .partition_id = TFM_SP_CORE_TEST_2,
        .signal = SPM_CORE_TEST_2_SLAVE_SERVICE_SIGNAL,
        .sid = 0x0000F040,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "SPM_CORE_TEST_2_CHECK_CALLER_CLIENT_ID",
        .partition_id = TFM_SP_CORE_TEST_2,
        .signal = SPM_CORE_TEST_2_CHECK_CALLER_CLIENT_ID_SIGNAL,
        .sid = 0x0000F041,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "SPM_CORE_TEST_2_GET_EVERY_SECOND_BYTE",
        .partition_id = TFM_SP_CORE_TEST_2,
        .signal = SPM_CORE_TEST_2_GET_EVERY_SECOND_BYTE_SIGNAL,
        .sid = 0x0000F042,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "SPM_CORE_TEST_2_INVERT",
        .partition_id = TFM_SP_CORE_TEST_2,
        .signal = SPM_CORE_TEST_2_INVERT_SIGNAL,
        .sid = 0x0000F043,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "SPM_CORE_TEST_2_PREPARE_TEST_SCENARIO",
        .partition_id = TFM_SP_CORE_TEST_2,
        .signal = SPM_CORE_TEST_2_PREPARE_TEST_SCENARIO_SIGNAL,
        .sid = 0x0000F044,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "SPM_CORE_TEST_2_EXECUTE_TEST_SCENARIO",
        .partition_id = TFM_SP_CORE_TEST_2,
        .signal = SPM_CORE_TEST_2_EXECUTE_TEST_SCENARIO_SIGNAL,
        .sid = 0x0000F045,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
#endif /* TFM_PARTITION_TEST_CORE */

#ifdef TFM_PARTITION_TEST_SECURE_SERVICES
    /******** TFM_SP_SECURE_TEST_PARTITION ********/
    {
        .name = "TFM_SECURE_CLIENT_SFN_RUN_TESTS",
        .partition_id = TFM_SP_SECURE_TEST_PARTITION,
        .signal = TFM_SECURE_CLIENT_SFN_RUN_TESTS_SIGNAL,
        .sid = 0x0000F000,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
#endif /* TFM_PARTITION_TEST_SECURE_SERVICES */

#ifdef TFM_PARTITION_TEST_CORE_IPC
    /******** TFM_SP_IPC_SERVICE_TEST ********/
    {
        .name = "IPC_SERVICE_TEST_BASIC",
        .partition_id = TFM_SP_IPC_SERVICE_TEST,
        .signal = IPC_SERVICE_TEST_BASIC_SIGNAL,
        .sid = 0x0000F080,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "IPC_SERVICE_TEST_PSA_ACCESS_APP_MEM",
        .partition_id = TFM_SP_IPC_SERVICE_TEST,
        .signal = IPC_SERVICE_TEST_PSA_ACCESS_APP_MEM_SIGNAL,
        .sid = 0x0000F081,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "IPC_SERVICE_TEST_PSA_ACCESS_APP_READ_ONLY_MEM",
        .partition_id = TFM_SP_IPC_SERVICE_TEST,
        .signal = IPC_SERVICE_TEST_PSA_ACCESS_APP_READ_ONLY_MEM_SIGNAL,
        .sid = 0x0000F082,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "IPC_SERVICE_TEST_APP_ACCESS_PSA_MEM",
        .partition_id = TFM_SP_IPC_SERVICE_TEST,
        .signal = IPC_SERVICE_TEST_APP_ACCESS_PSA_MEM_SIGNAL,
        .sid = 0x0000F083,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "IPC_SERVICE_TEST_CLIENT_PROGRAMMER_ERROR",
        .partition_id = TFM_SP_IPC_SERVICE_TEST,
        .signal = IPC_SERVICE_TEST_CLIENT_PROGRAMMER_ERROR_SIGNAL,
        .sid = 0x0000F084,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
#endif /* TFM_PARTITION_TEST_CORE_IPC */

#ifdef TFM_PARTITION_TEST_CORE_IPC
    /******** TFM_SP_IPC_CLIENT_TEST ********/
    {
        .name = "IPC_CLIENT_TEST_BASIC",
        .partition_id = TFM_SP_IPC_CLIENT_TEST,
        .signal = IPC_CLIENT_TEST_BASIC_SIGNAL,
        .sid = 0x0000F060,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "IPC_CLIENT_TEST_PSA_ACCESS_APP_MEM",
        .partition_id = TFM_SP_IPC_CLIENT_TEST,
        .signal = IPC_CLIENT_TEST_PSA_ACCESS_APP_MEM_SIGNAL,
        .sid = 0x0000F061,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "IPC_CLIENT_TEST_PSA_ACCESS_APP_READ_ONLY_MEM",
        .partition_id = TFM_SP_IPC_CLIENT_TEST,
        .signal = IPC_CLIENT_TEST_PSA_ACCESS_APP_READ_ONLY_MEM_SIGNAL,
        .sid = 0x0000F062,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "IPC_CLIENT_TEST_APP_ACCESS_PSA_MEM",
        .partition_id = TFM_SP_IPC_CLIENT_TEST,
        .signal = IPC_CLIENT_TEST_APP_ACCESS_PSA_MEM_SIGNAL,
        .sid = 0x0000F063,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "IPC_CLIENT_TEST_MEM_CHECK",
        .partition_id = TFM_SP_IPC_CLIENT_TEST,
        .signal = IPC_CLIENT_TEST_MEM_CHECK_SIGNAL,
        .sid = 0x0000F064,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "IPC_CLIENT_TEST_RETRIEVE_APP_MEM",
        .partition_id = TFM_SP_IPC_CLIENT_TEST,
        .signal = IPC_CLIENT_TEST_RETRIEVE_APP_MEM_SIGNAL,
        .sid = 0x0000F065,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
#endif /* TFM_PARTITION_TEST_CORE_IPC */

#ifdef TFM_ENABLE_IRQ_TEST
    /******** TFM_IRQ_TEST_1 ********/
    {
        .name = "SPM_CORE_IRQ_TEST_1_PREPARE_TEST_SCENARIO",
        .partition_id = TFM_IRQ_TEST_1,
        .signal = SPM_CORE_IRQ_TEST_1_PREPARE_TEST_SCENARIO_SIGNAL,
        .sid = 0x0000F0A0,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "SPM_CORE_IRQ_TEST_1_EXECUTE_TEST_SCENARIO",
        .partition_id = TFM_IRQ_TEST_1,
        .signal = SPM_CORE_IRQ_TEST_1_EXECUTE_TEST_SCENARIO_SIGNAL,
        .sid = 0x0000F0A1,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
#endif /* TFM_ENABLE_IRQ_TEST */

#ifdef TFM_PARTITION_TEST_PS
    /******** TFM_SP_PS_TEST ********/
    {
        .name = "TFM_PS_TEST_PREPARE",
        .partition_id = TFM_SP_PS_TEST,
        .signal = TFM_PS_TEST_PREPARE_SIGNAL,
        .sid = 0x0000F0C0,
        .non_secure_client = false,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
#endif /* TFM_PARTITION_TEST_PS */

#ifdef TFM_PARTITION_TEST_SECURE_SERVICES
    /******** TFM_SP_SECURE_CLIENT_2 ********/
    {
        .name = "TFM_SECURE_CLIENT_2",
        .partition_id = TFM_SP_SECURE_CLIENT_2,
        .signal = TFM_SECURE_CLIENT_2_SIGNAL,
        .sid = 0x0000F0E0,
        .non_secure_client = false,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
#endif /* TFM_PARTITION_TEST_SECURE_SERVICES */

#ifdef TFM_PARTITION_PSA_PROXY
    /******** TFM_SP_PSA_PROXY ********/
    {
        .name = "TFM_CRYPTO",
        .partition_id = TFM_SP_PSA_PROXY,
        .signal = TFM_CRYPTO_SIGNAL,
        .sid = 0x00000080,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_ATTEST_GET_TOKEN",
        .partition_id = TFM_SP_PSA_PROXY,
        .signal = TFM_ATTEST_GET_TOKEN_SIGNAL,
        .sid = 0x00000020,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_ATTEST_GET_TOKEN_SIZE",
        .partition_id = TFM_SP_PSA_PROXY,
        .signal = TFM_ATTEST_GET_TOKEN_SIZE_SIGNAL,
        .sid = 0x00000021,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_ATTEST_GET_PUBLIC_KEY",
        .partition_id = TFM_SP_PSA_PROXY,
        .signal = TFM_ATTEST_GET_PUBLIC_KEY_SIGNAL,
        .sid = 0x00000022,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_ITS_SET",
        .partition_id = TFM_SP_PSA_PROXY,
        .signal = TFM_ITS_SET_SIGNAL,
        .sid = 0x00000070,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_ITS_GET",
        .partition_id = TFM_SP_PSA_PROXY,
        .signal = TFM_ITS_GET_SIGNAL,
        .sid = 0x00000071,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_ITS_GET_INFO",
        .partition_id = TFM_SP_PSA_PROXY,
        .signal = TFM_ITS_GET_INFO_SIGNAL,
        .sid = 0x00000072,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_ITS_REMOVE",
        .partition_id = TFM_SP_PSA_PROXY,
        .signal = TFM_ITS_REMOVE_SIGNAL,
        .sid = 0x00000073,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_SP_PLATFORM_SYSTEM_RESET",
        .partition_id = TFM_SP_PSA_PROXY,
        .signal = TFM_SP_PLATFORM_SYSTEM_RESET_SIGNAL,
        .sid = 0x00000040,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_SP_PLATFORM_IOCTL",
        .partition_id = TFM_SP_PSA_PROXY,
        .signal = TFM_SP_PLATFORM_IOCTL_SIGNAL,
        .sid = 0x00000041,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_SP_PLATFORM_NV_COUNTER",
        .partition_id = TFM_SP_PSA_PROXY,
        .signal = TFM_SP_PLATFORM_NV_COUNTER_SIGNAL,
        .sid = 0x00000042,
        .non_secure_client = false,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_PS_SET",
        .partition_id = TFM_SP_PSA_PROXY,
        .signal = TFM_PS_SET_SIGNAL,
        .sid = 0x00000060,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_PS_GET",
        .partition_id = TFM_SP_PSA_PROXY,
        .signal = TFM_PS_GET_SIGNAL,
        .sid = 0x00000061,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_PS_GET_INFO",
        .partition_id = TFM_SP_PSA_PROXY,
        .signal = TFM_PS_GET_INFO_SIGNAL,
        .sid = 0x00000062,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_PS_REMOVE",
        .partition_id = TFM_SP_PSA_PROXY,
        .signal = TFM_PS_REMOVE_SIGNAL,
        .sid = 0x00000063,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_PS_GET_SUPPORT",
        .partition_id = TFM_SP_PSA_PROXY,
        .signal = TFM_PS_GET_SUPPORT_SIGNAL,
        .sid = 0x00000064,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
#endif /* TFM_PARTITION_PSA_PROXY */

#ifdef TFM_PARTITION_FIRMWARE_UPDATE
    /******** TFM_SP_FWU ********/
    {
        .name = "TFM_FWU_WRITE",
        .partition_id = TFM_SP_FWU,
        .signal = TFM_FWU_WRITE_SIGNAL,
        .sid = 0x000000A0,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_FWU_INSTALL",
        .partition_id = TFM_SP_FWU,
        .signal = TFM_FWU_INSTALL_SIGNAL,
        .sid = 0x000000A1,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_FWU_ABORT",
        .partition_id = TFM_SP_FWU,
        .signal = TFM_FWU_ABORT_SIGNAL,
        .sid = 0x000000A2,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_FWU_QUERY",
        .partition_id = TFM_SP_FWU,
        .signal = TFM_FWU_QUERY_SIGNAL,
        .sid = 0x000000A3,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_FWU_REQUEST_REBOOT",
        .partition_id = TFM_SP_FWU,
        .signal = TFM_FWU_REQUEST_REBOOT_SIGNAL,
        .sid = 0x000000A4,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
    {
        .name = "TFM_FWU_ACCEPT",
        .partition_id = TFM_SP_FWU,
        .signal = TFM_FWU_ACCEPT_SIGNAL,
        .sid = 0x000000A5,
        .non_secure_client = true,
        .connection_based = true,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_STRICT
    },
#endif /* TFM_PARTITION_FIRMWARE_UPDATE */

#ifdef TFM_PARTITION_FFM11
    /******** TFM_SP_FFM11 ********/
    {
        .name = "TFM_FFM11_SERVICE1",
        .partition_id = TFM_SP_FFM11,
        .signal = TFM_FFM11_SERVICE1_SIGNAL,
        .sid = 0x0000F120,
        .non_secure_client = true,
        .connection_based = false,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_RELAXED
    },
    {
        .name = "TFM_FFM11_SERVICE2",
        .partition_id = TFM_SP_FFM11,
        .signal = TFM_FFM11_SERVICE2_SIGNAL,
        .sid = 0x0000F121,
        .non_secure_client = true,
        .connection_based = false,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_RELAXED
    },
    {
        .name = "TFM_FFM11_SERVICE3",
        .partition_id = TFM_SP_FFM11,
        .signal = TFM_FFM11_SERVICE3_SIGNAL,
        .sid = 0x0000F122,
        .non_secure_client = true,
        .connection_based = false,
        .version = 1,
        .version_policy = TFM_VERSION_POLICY_RELAXED
    },
#endif /* TFM_PARTITION_FFM11 */

};

/**************************************************************************/
/** The service list */
/**************************************************************************/
struct tfm_spm_service_t service[] =
{
#ifdef TFM_PARTITION_PROTECTED_STORAGE
    /******** TFM_SP_PS ********/
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
#endif /* TFM_PARTITION_PROTECTED_STORAGE */

#ifdef TFM_PARTITION_INTERNAL_TRUSTED_STORAGE
    /******** TFM_SP_ITS ********/
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
#endif /* TFM_PARTITION_INTERNAL_TRUSTED_STORAGE */

#ifdef TFM_PARTITION_CRYPTO
    /******** TFM_SP_CRYPTO ********/
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
#endif /* TFM_PARTITION_CRYPTO */

#ifdef TFM_PARTITION_PLATFORM
    /******** TFM_SP_PLATFORM ********/
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
#endif /* TFM_PARTITION_PLATFORM */

#ifdef TFM_PARTITION_INITIAL_ATTESTATION
    /******** TFM_SP_INITIAL_ATTESTATION ********/
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
#endif /* TFM_PARTITION_INITIAL_ATTESTATION */

#ifdef TFM_PARTITION_TEST_CORE
    /******** TFM_SP_CORE_TEST ********/
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
#endif /* TFM_PARTITION_TEST_CORE */

#ifdef TFM_PARTITION_TEST_CORE
    /******** TFM_SP_CORE_TEST_2 ********/
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
#endif /* TFM_PARTITION_TEST_CORE */

#ifdef TFM_PARTITION_TEST_SECURE_SERVICES
    /******** TFM_SP_SECURE_TEST_PARTITION ********/
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
#endif /* TFM_PARTITION_TEST_SECURE_SERVICES */

#ifdef TFM_PARTITION_TEST_CORE_IPC
    /******** TFM_SP_IPC_SERVICE_TEST ********/
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
#endif /* TFM_PARTITION_TEST_CORE_IPC */

#ifdef TFM_PARTITION_TEST_CORE_IPC
    /******** TFM_SP_IPC_CLIENT_TEST ********/
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
#endif /* TFM_PARTITION_TEST_CORE_IPC */

#ifdef TFM_ENABLE_IRQ_TEST
    /******** TFM_IRQ_TEST_1 ********/
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
#endif /* TFM_ENABLE_IRQ_TEST */

#ifdef TFM_PARTITION_TEST_PS
    /******** TFM_SP_PS_TEST ********/
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
#endif /* TFM_PARTITION_TEST_PS */

#ifdef TFM_PARTITION_TEST_SECURE_SERVICES
    /******** TFM_SP_SECURE_CLIENT_2 ********/
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
#endif /* TFM_PARTITION_TEST_SECURE_SERVICES */

#ifdef TFM_PARTITION_PSA_PROXY
    /******** TFM_SP_PSA_PROXY ********/
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
#endif /* TFM_PARTITION_PSA_PROXY */

#ifdef TFM_PARTITION_FIRMWARE_UPDATE
    /******** TFM_SP_FWU ********/
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
#endif /* TFM_PARTITION_FIRMWARE_UPDATE */

#ifdef TFM_PARTITION_FFM11
    /******** TFM_SP_FFM11 ********/
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
    {
        .service_db = NULL,
        .partition = NULL,
        .handle_list = {0},
        .list = {0},
    },
#endif /* TFM_PARTITION_FFM11 */

};

/* p_service field of tracking table will be populated in spm_init() */
struct stateless_service_tracking_t stateless_service_ref[] = {
    {
        .sid = 0x0000F121,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0x0000F122,
    },
    {
        .sid = 0x0000F120,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
    {
        .sid = 0,
    },
};

#endif /* __TFM_SERVICE_LIST_INC__ */
