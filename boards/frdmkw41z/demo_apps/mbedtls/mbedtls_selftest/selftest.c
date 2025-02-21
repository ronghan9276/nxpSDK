/*
 *  Self-test demonstration program
 *
 *  Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/entropy.h"
#include "mbedtls/entropy_poll.h"
#include "mbedtls/hmac_drbg.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/dhm.h"
#include "mbedtls/gcm.h"
#include "mbedtls/ccm.h"
#include "mbedtls/md2.h"
#include "mbedtls/md4.h"
#include "mbedtls/md5.h"
#include "mbedtls/ripemd160.h"
#include "mbedtls/sha1.h"
#include "mbedtls/sha256.h"
#include "mbedtls/sha512.h"
#include "mbedtls/arc4.h"
#include "mbedtls/des.h"
#include "mbedtls/aes.h"
#include "mbedtls/camellia.h"
#include "mbedtls/base64.h"
#include "mbedtls/bignum.h"
#include "mbedtls/rsa.h"
#include "mbedtls/x509.h"
#include "mbedtls/xtea.h"
#include "mbedtls/pkcs5.h"
#include "mbedtls/ecp.h"
#include "mbedtls/ecjpake.h"
#include "mbedtls/timing.h"

#include <string.h>

#if defined(MBEDTLS_PLATFORM_C)
#if defined(FREESCALE_KSDK_BM)
#include "board.h"
#include "fsl_debug_console.h"

#define mbedtls_printf PRINTF
#define mbedtls_snprintf snprintf
#define mbedtls_exit return
#define MBEDTLS_EXIT_SUCCESS 0
#define MBEDTLS_EXIT_FAILURE 1
#else
#include "mbedtls/platform.h"
#endif
#else
#include <stdio.h>
#include <stdlib.h>
#define mbedtls_printf printf
#define mbedtls_snprintf snprintf
#define mbedtls_exit exit
#define MBEDTLS_EXIT_SUCCESS EXIT_SUCCESS
#define MBEDTLS_EXIT_FAILURE EXIT_FAILURE
#endif

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
#include "mbedtls/memory_buffer_alloc.h"
#endif

#if FSL_FEATURE_SOC_LTC_COUNT
#include "fsl_ltc.h"
#endif
#if FSL_FEATURE_SOC_TRNG_COUNT
#include "fsl_trng.h"
#elif FSL_FEATURE_SOC_RNG_COUNT
#include "fsl_rnga.h"
#endif

#include "pin_mux.h"
#include <stdbool.h>
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define CORE_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)

/*******************************************************************************
* Prototypes
******************************************************************************/

/*******************************************************************************
* Variables
******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
#if RUN_TEST_SNPRINTF
static int test_snprintf(size_t n, const char ref_buf[10], int ref_ret)
{
    int ret;
    char buf[10] = "xxxxxxxxx";
    const char ref[10] = "xxxxxxxxx";

    ret = mbedtls_snprintf(buf, n, "%s", "123");
    if (ret < 0 || (size_t)ret >= n)
        ret = -1;

    if (strncmp(ref_buf, buf, sizeof(buf)) != 0 || ref_ret != ret || memcmp(buf + n, ref + n, sizeof(buf) - n) != 0)
    {
        return (1);
    }

    return (0);
}

static int run_test_snprintf(void)
{
    return (test_snprintf(0, "xxxxxxxxx", -1) != 0 || test_snprintf(1, "", -1) != 0 || test_snprintf(2, "1", -1) != 0 ||
            test_snprintf(3, "12", -1) != 0 || test_snprintf(4, "123", 3) != 0 || test_snprintf(5, "123", 3) != 0);
}
#endif

/*
 * Check if a seed file is present, and if not create one for the entropy
 * self-test. If this fails, we attempt the test anyway, so no error is passed
 * back.
 */
#if defined(MBEDTLS_ENTROPY_C) && defined(MBEDTLS_ENTROPY_NV_SEED) && !defined(MBEDTLS_NO_PLATFORM_ENTROPY)
static void create_entropy_seed_file(void)
{
    int result;
    size_t output_len = 0;
    unsigned char seed_value[MBEDTLS_ENTROPY_BLOCK_SIZE];

    /* Attempt to read the entropy seed file. If this fails - attempt to write
     * to the file to ensure one is present. */
    result = mbedtls_platform_std_nv_seed_read(seed_value, MBEDTLS_ENTROPY_BLOCK_SIZE);
    if (0 == result)
        return;

    result = mbedtls_platform_entropy_poll(NULL, seed_value, MBEDTLS_ENTROPY_BLOCK_SIZE, &output_len);
    if (0 != result)
        return;

    if (MBEDTLS_ENTROPY_BLOCK_SIZE != output_len)
        return;

    mbedtls_platform_std_nv_seed_write(seed_value, MBEDTLS_ENTROPY_BLOCK_SIZE);
}
#endif

int main(int argc, char *argv[])
{
    int v, suites_tested = 0, suites_failed = 0;
#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
    unsigned char buf[1000000];
#endif
    void *pointer;

#if defined(FREESCALE_KSDK_BM)
    /* HW init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
#if FSL_FEATURE_SOC_LTC_COUNT
    /* Initialize LTC driver.
     * This enables clocking and resets the module to a known state. */
    LTC_Init(LTC0);
#endif
    { /* Init RNG module.*/
#if defined(FSL_FEATURE_SOC_TRNG_COUNT) && (FSL_FEATURE_SOC_TRNG_COUNT > 0)
        trng_config_t trngConfig;

        TRNG_GetDefaultConfig(&trngConfig);
        /* Set sample mode of the TRNG ring oscillator to Von Neumann, for better random data.*/
        trngConfig.sampleMode = kTRNG_SampleModeVonNeumann;
        /* Initialize TRNG */
        TRNG_Init(TRNG0, &trngConfig);
#elif defined(FSL_FEATURE_SOC_RNG_COUNT) && (FSL_FEATURE_SOC_RNG_COUNT > 0)
        RNGA_Init(RNG);
        RNGA_Seed(RNG, SIM->UIDL);
#endif
    }
#endif

    /*
     * The C standard doesn't guarantee that all-bits-0 is the representation
     * of a NULL pointer. We do however use that in our code for initializing
     * structures, which should work on every modern platform. Let's be sure.
     */
    memset(&pointer, 0, sizeof(void *));
    if (pointer != NULL)
    {
        mbedtls_printf("all-bits-zero is not a NULL pointer\r\n");
        mbedtls_exit(MBEDTLS_EXIT_FAILURE);
    }

/*
 * Make sure we have a snprintf that correctly zero-terminates
 */
#if RUN_TEST_SNPRINTF /* Test is failed for UV */
    if (run_test_snprintf() != 0)
    {
        mbedtls_printf("the snprintf implementation is broken\r\n");
        mbedtls_exit(MBEDTLS_EXIT_FAILURE);
    }
#endif
    if (argc == 2 && (strcmp(argv[1], "--quiet") == 0 || strcmp(argv[1], "-q") == 0))
    {
        v = 0;
    }
    else
    {
        v = 1;
        mbedtls_printf("\r\n");
    }

#if defined(MBEDTLS_SELF_TEST)

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
    mbedtls_memory_buffer_alloc_init(buf, sizeof(buf));
#endif

#if defined(MBEDTLS_MD2_C)
    if (mbedtls_md2_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_MD4_C)
    if (mbedtls_md4_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_MD5_C)
    if (mbedtls_md5_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_RIPEMD160_C)
    if (mbedtls_ripemd160_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_SHA1_C)
    if (mbedtls_sha1_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_SHA256_C)
    if (mbedtls_sha256_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_SHA512_C)
    if (mbedtls_sha512_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_ARC4_C)
    if (mbedtls_arc4_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_DES_C)
    if (mbedtls_des_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_AES_C)
    if (mbedtls_aes_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_GCM_C) && defined(MBEDTLS_AES_C)
    if (mbedtls_gcm_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_CCM_C) && defined(MBEDTLS_AES_C)
    if (mbedtls_ccm_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_BASE64_C)
    if (mbedtls_base64_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_BIGNUM_C)
    if (mbedtls_mpi_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_RSA_C)
    if (mbedtls_rsa_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if 0 /* Disabled cause of memory limit for some platforms. */
#if defined(MBEDTLS_X509_USE_C)
    if( mbedtls_x509_self_test( v ) != 0 )
    {
        suites_failed++;
    }
    suites_tested++;
#endif
#endif

#if defined(MBEDTLS_XTEA_C)
    if (mbedtls_xtea_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_CAMELLIA_C)
    if (mbedtls_camellia_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_CTR_DRBG_C)
    if (mbedtls_ctr_drbg_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_HMAC_DRBG_C)
    if (mbedtls_hmac_drbg_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_ECP_C)
    if (mbedtls_ecp_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_ECJPAKE_C)
    if (mbedtls_ecjpake_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_DHM_C)
    if (mbedtls_dhm_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_ENTROPY_C)

#if defined(MBEDTLS_ENTROPY_NV_SEED) && !defined(MBEDTLS_NO_PLATFORM_ENTROPY)
    create_entropy_seed_file();
#endif

    if (mbedtls_entropy_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#if defined(MBEDTLS_PKCS5_C)
    if (mbedtls_pkcs5_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

/* Slow tests last */

#if defined(MBEDTLS_TIMING_C)
    if (mbedtls_timing_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

#else
    mbedtls_printf(" MBEDTLS_SELF_TEST not defined.\r\n");
#endif

    if (v != 0)
    {
#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C) && defined(MBEDTLS_MEMORY_DEBUG)
        mbedtls_memory_buffer_alloc_status();
#endif
    }

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
    mbedtls_memory_buffer_alloc_free();
    if (mbedtls_memory_buffer_alloc_self_test(v) != 0)
    {
        suites_failed++;
    }
    suites_tested++;
#endif

    if (v != 0)
    {
        mbedtls_printf("  Executed %d test suites\n\n", suites_tested);

        if (suites_failed > 0)
        {
            mbedtls_printf("  [ %d tests FAIL ]\n\n", suites_failed);
        }
        else
        {
            mbedtls_printf("  [ All tests PASS ]\n\n");
        }
#if defined(_WIN32)
        mbedtls_printf("  Press Enter to exit this program.\r\n");
        fflush(stdout);
        getchar();
#endif
    }

    if (suites_failed > 0)
        mbedtls_exit(MBEDTLS_EXIT_FAILURE);

    /* return() is here to prevent compiler warnings */
    return (MBEDTLS_EXIT_SUCCESS);
}
