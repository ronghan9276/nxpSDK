/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(FSL_FEATURE_SOC_CASPER_COUNT) && (FSL_FEATURE_SOC_CASPER_COUNT > 0)
#include "fsl_casper.h"


#if (defined(MBEDTLS_MCUX_CASPER_ECC) && (MBEDTLS_MCUX_CASPER_ECC == 1)) || (defined(MBEDTLS_MCUX_CASPER_PKHA) && defined(MBEDTLS_RSA_PUBLIC_ALT) && defined(MBEDTLS_RSA_C))
/* Initialize CASPER */
static volatile bool casper_init_is_done = false;
static void mbedtls_casper_init(void)
{
    /* Initialize CASPER */
    CASPER_Init(CASPER);
    
    casper_init_is_done = true;
}

static void reverse_array(uint8_t *src, size_t src_len)
{
    int i;

    for (i = 0; i < src_len / 2; i++)
    {
        uint8_t tmp;

        tmp = src[i];
        src[i] = src[src_len - 1 - i];
        src[src_len - 1 - i] = tmp;
    }
}
#endif

/******************************************************************************/
/*************************** PKHA  ********************************************/
/******************************************************************************/
#if defined(MBEDTLS_MCUX_CASPER_PKHA) && defined(MBEDTLS_RSA_PUBLIC_ALT) && defined(MBEDTLS_RSA_C)

#include "mbedtls/rsa.h"
#include "mbedtls/oid.h"

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#define mbedtls_printf printf
#define mbedtls_calloc calloc
#define mbedtls_free   free
#endif

/* Parameter validation macros */
#define RSA_VALIDATE_RET( cond )                                       \
    MBEDTLS_INTERNAL_VALIDATE_RET( cond, MBEDTLS_ERR_RSA_BAD_INPUT_DATA )
/*
 * Do an RSA public key operation
 */
static int mbedtls_casper_mpi_exp_mod_shim(mbedtls_mpi *X,
                                    const mbedtls_mpi *A,
                                    const mbedtls_mpi *E,
                                    const mbedtls_mpi *N /*, mbedtls_mpi *_RR */)
{
    int ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
    size_t sizeA = mbedtls_mpi_size(A);
    size_t sizeN = mbedtls_mpi_size(N);
    uint8_t *ptrX = mbedtls_calloc(3, MBEDTLS_MCUX_PKHA_INT_MAX_BYTES);
    uint8_t *ptrA = ptrX + MBEDTLS_MCUX_PKHA_INT_MAX_BYTES;
    uint8_t *ptrN = ptrA + MBEDTLS_MCUX_PKHA_INT_MAX_BYTES;

    if (NULL == ptrX)
    {
        ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
        goto cleanup;   
    }

    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(A, ptrA, sizeA));
    reverse_array(ptrA, sizeA);

    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(N, ptrN, sizeN));
    reverse_array(ptrN, sizeN);

    CASPER_ModExp(CASPER, ptrA, ptrN, sizeN / 4, E->p[0], ptrX);

    reverse_array(ptrX, sizeN);
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(X, ptrX, sizeN));
cleanup:
    if (ptrX != NULL)
    {
        mbedtls_free(ptrX);
    }

    return ret;
}

/*
 * Do an RSA public key operation
 */
int mbedtls_rsa_public( mbedtls_rsa_context *ctx,
                const unsigned char *input,
                unsigned char *output )
{
    int ret;
    size_t olen;
    mbedtls_mpi T;
    RSA_VALIDATE_RET( ctx != NULL );
    RSA_VALIDATE_RET( input != NULL );
    RSA_VALIDATE_RET( output != NULL );
    
    if(casper_init_is_done == false)
    {
        mbedtls_casper_init();
    }

    mbedtls_mpi_init(&T);

#if defined(MBEDTLS_THREADING_C)
    if ((ret = mbedtls_mutex_lock(&ctx->mutex)) != 0)
        return (ret);
#endif

    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&T, input, ctx->len));

    if (mbedtls_mpi_cmp_mpi(&T, &ctx->N) >= 0)
    {
        ret = MBEDTLS_ERR_MPI_BAD_INPUT_DATA;
        goto cleanup;
    }

    olen = ctx->len;
    MBEDTLS_MPI_CHK(mbedtls_casper_mpi_exp_mod_shim(&T, &T, &ctx->E, &ctx->N /*, &ctx->RN */));
    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(&T, output, olen));

cleanup:
#if defined(MBEDTLS_THREADING_C)
    if (mbedtls_mutex_unlock(&ctx->mutex) != 0)
        return (MBEDTLS_ERR_THREADING_MUTEX_ERROR);
#endif

    mbedtls_mpi_free(&T);

    if (ret != 0)
        return (MBEDTLS_ERR_RSA_PUBLIC_FAILED + ret);

    return (0);
}

#endif /* MBEDTLS_MCUX_CASPER_PKHA && MBEDTLS_RSA_PUBLIC_ALT && MBEDTLS_RSA_C */


/******************************************************************************/
/*************************** ECP  *********************************************/
/******************************************************************************/
#if defined(MBEDTLS_ECP_C)

#include "mbedtls/ecp.h"
#include "mbedtls/threading.h"
#include "mbedtls/platform_util.h"

#include <string.h>

#if defined(MBEDTLS_MCUX_CASPER_ECC) && (MBEDTLS_MCUX_CASPER_ECC == 1)

#if defined(MBEDTLS_ECP_DP_SECP192R1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_SECP224R1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_SECP192K1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_SECP224K1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_SECP256K1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_BP256R1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_BP384R1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_BP512R1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_CURVE25519_ENABLED) || \
    defined(MBEDTLS_ECP_DP_CURVE448_ENABLED) || \
    (defined(MBEDTLS_ECP_DP_SECP256R1_ENABLED) && defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED)) 
#error "CASPER hw acceleration supports only one curve for SECP256R1 or SECP384R1."
#endif

#if defined(CASPER_ECC_P256) && (CASPER_ECC_P256 > 0)
#define ECC_SIZE_BITS (256)
#elif defined(CASPER_ECC_P384) && (CASPER_ECC_P384 > 0)
#define ECC_SIZE_BITS (384)
#endif

/* Parameter validation macros based on platform_util.h */
#define ECP_VALIDATE_RET( cond )    \
    MBEDTLS_INTERNAL_VALIDATE_RET( cond, MBEDTLS_ERR_ECP_BAD_INPUT_DATA )
#define ECP_VALIDATE( cond )        \
    MBEDTLS_INTERNAL_VALIDATE( cond )

#define ECC_SIZE_BYTES (ECC_SIZE_BITS / 8) /* 32 for 256 bits and 48 for 384 bits */

typedef struct _ecp
{
    union
    {
        uint8_t b[4 + ECC_SIZE_BYTES * 2];
        uint32_t w[(4 + ECC_SIZE_BYTES * 2) / 4];
    } data;
} casper_ecp_t;

#if defined(MBEDTLS_ECP_MUL_COMB_ALT)
int ecp_mul_comb(mbedtls_ecp_group *grp,
                 mbedtls_ecp_point *R,
                 const mbedtls_mpi *m,
                 const mbedtls_ecp_point *P,
                 int (*f_rng)(void *, unsigned char *, size_t),
                 void *p_rng,
                 mbedtls_ecp_restart_ctx *rs_ctx ) /* TBD: rs_ctx is not used MBEDTLS_ECP_RESTARTABLE is not supported */
{
    casper_ecp_t p                                = {0};
    uint32_t M[ECC_SIZE_BYTES / sizeof(uint32_t)] = {0};

    size_t olen = sizeof(casper_ecp_t);

    mbedtls_ecp_point_write_binary(grp, P, MBEDTLS_ECP_PF_UNCOMPRESSED, &olen, &p.data.b[3], sizeof(casper_ecp_t));
    reverse_array(&p.data.b[4], ECC_SIZE_BYTES);
    reverse_array(&p.data.b[4 + ECC_SIZE_BYTES], ECC_SIZE_BYTES);
    CASPER_ecc_init();

    if (mbedtls_mpi_size(m) > sizeof(M))
    {
        __BKPT(0);
        return MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL;
    }
    mbedtls_mpi_write_binary(m, (void *)M, ECC_SIZE_BYTES);
    reverse_array((void *)M, ECC_SIZE_BYTES);
#if (ECC_SIZE_BITS == 256)
    CASPER_ECC_SECP256R1_Mul(CASPER, &p.data.w[1], &p.data.w[1 + (ECC_SIZE_BYTES / sizeof(uint32_t))], &p.data.w[1],
                             &p.data.w[1 + (ECC_SIZE_BYTES / sizeof(uint32_t))], (void *)M);
#elif (ECC_SIZE_BITS == 384)
    CASPER_ECC_SECP384R1_Mul(CASPER, &p.data.w[1], &p.data.w[1 + (ECC_SIZE_BYTES / sizeof(uint32_t))], &p.data.w[1],
                             &p.data.w[1 + (ECC_SIZE_BYTES / sizeof(uint32_t))], (void *)M);
#endif
    reverse_array(&p.data.b[4], ECC_SIZE_BYTES);
    reverse_array(&p.data.b[4 + ECC_SIZE_BYTES], ECC_SIZE_BYTES);
    mbedtls_ecp_point_read_binary(grp, R, &p.data.b[3], 2 * ECC_SIZE_BYTES + 1);
    return 0;
}
#endif /* MBEDTLS_ECP_MUL_COMB_ALT */

#if defined(MBEDTLS_ECP_MULADD_ALT)

extern int ecp_add( const mbedtls_ecp_group *grp, mbedtls_ecp_point *R,
                    const mbedtls_ecp_point *P,
                    const mbedtls_ecp_point *Q );
/*
 * Restartable linear combination
 * NOT constant-time
 */
int mbedtls_ecp_muladd_restartable(
             mbedtls_ecp_group *grp, mbedtls_ecp_point *R,
             const mbedtls_mpi *m, const mbedtls_ecp_point *P,
             const mbedtls_mpi *n, const mbedtls_ecp_point *Q,
             mbedtls_ecp_restart_ctx *rs_ctx ) /* TBD restartable is not implemented */
{
    casper_ecp_t p1 = {0};
    casper_ecp_t p2 = {0};

    uint32_t M[ECC_SIZE_BYTES / sizeof(uint32_t)] = {0};
    uint32_t N[ECC_SIZE_BYTES / sizeof(uint32_t)] = {0};

    size_t olen1 = sizeof(casper_ecp_t);

    /* shortcut for (m == 1) && (n == 1). this case is point addition. */
    /* this shortcut follows original mbedtls_ecp_muladd() implementation */
    /* and is required for ecjpake_ecp_add3(). */
    if ((mbedtls_mpi_cmp_int(m, 1) == 0) && (mbedtls_mpi_cmp_int(n, 1) == 0))
    {
        return ecp_add(grp, R, P, Q);
    }

    mbedtls_ecp_point_write_binary(grp, P, MBEDTLS_ECP_PF_UNCOMPRESSED, &olen1, &p1.data.b[3], sizeof(casper_ecp_t));
    reverse_array(&p1.data.b[4], ECC_SIZE_BYTES);
    reverse_array(&p1.data.b[4 + ECC_SIZE_BYTES], ECC_SIZE_BYTES);

    CASPER_ecc_init();

    if (mbedtls_mpi_size(m) > sizeof(M))
    {
        __BKPT(0);
        return MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL;
    }
    mbedtls_mpi_write_binary(m, (void *)M, ECC_SIZE_BYTES);
    reverse_array((void *)M, ECC_SIZE_BYTES);
    /* */
    size_t olen2 = sizeof(casper_ecp_t);

    mbedtls_ecp_point_write_binary(grp, Q, MBEDTLS_ECP_PF_UNCOMPRESSED, &olen2, &p2.data.b[3], sizeof(casper_ecp_t));
    reverse_array(&p2.data.b[4], ECC_SIZE_BYTES);
    reverse_array(&p2.data.b[4 + ECC_SIZE_BYTES], ECC_SIZE_BYTES);

    if (mbedtls_mpi_size(n) > sizeof(N))
    {
        __BKPT(0);
        return MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL;
    }
    mbedtls_mpi_write_binary(n, (void *)N, ECC_SIZE_BYTES);
    reverse_array((void *)N, ECC_SIZE_BYTES);
#if (ECC_SIZE_BITS == 256)
    CASPER_ECC_SECP256R1_MulAdd(CASPER, &p1.data.w[1], &p1.data.w[1 + (ECC_SIZE_BYTES / sizeof(uint32_t))],
                                &p1.data.w[1], &p1.data.w[1 + (ECC_SIZE_BYTES / sizeof(uint32_t))], (void *)M,
                                &p2.data.w[1], &p2.data.w[1 + (ECC_SIZE_BYTES / sizeof(uint32_t))], (void *)N);
#elif (ECC_SIZE_BITS == 384)
    CASPER_ECC_SECP384R1_MulAdd(CASPER, &p1.data.w[1], &p1.data.w[1 + (ECC_SIZE_BYTES / sizeof(uint32_t))],
                                &p1.data.w[1], &p1.data.w[1 + (ECC_SIZE_BYTES / sizeof(uint32_t))], (void *)M,
                                &p2.data.w[1], &p2.data.w[1 + (ECC_SIZE_BYTES / sizeof(uint32_t))], (void *)N);
#endif
    reverse_array(&p1.data.b[4], ECC_SIZE_BYTES);
    reverse_array(&p1.data.b[4 + ECC_SIZE_BYTES], ECC_SIZE_BYTES);
    mbedtls_ecp_point_read_binary(grp, R, &p1.data.b[3], 2 * ECC_SIZE_BYTES + 1);
    return 0;
}

/*
 * Linear combination
 * NOT constant-time
 */
int mbedtls_ecp_muladd( mbedtls_ecp_group *grp, mbedtls_ecp_point *R,
             const mbedtls_mpi *m, const mbedtls_ecp_point *P,
             const mbedtls_mpi *n, const mbedtls_ecp_point *Q )
{
    ECP_VALIDATE_RET( grp != NULL );
    ECP_VALIDATE_RET( R   != NULL );
    ECP_VALIDATE_RET( m   != NULL );
    ECP_VALIDATE_RET( P   != NULL );
    ECP_VALIDATE_RET( n   != NULL );
    ECP_VALIDATE_RET( Q   != NULL );
    return( mbedtls_ecp_muladd_restartable( grp, R, m, P, n, Q, NULL ) );
}
#endif /* MBEDTLS_ECP_MULADD_ALT */

#endif /* MBEDTLS_MCUX_CASPER_ECC */

#endif /* MBEDTLS_ECP_C */


#endif /* FSL_FEATURE_SOC_CASPER_COUNT */
