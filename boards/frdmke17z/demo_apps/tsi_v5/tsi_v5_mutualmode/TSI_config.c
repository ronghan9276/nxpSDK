/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "TSI_config.h"

/*
 * Key and TSI channel mapping table definition
 */
key_tsi_mapping_t key_TSI[] = {
    /* TSI allocation for Mutual Key (2 TSI channels are connected to 1 mutual-key)*/
    {TSI0, {kTSI_Chnl_5}, kTSI_Chnl_7, 40U, 0U, 0U, 0U, 0U, 0U}, /* Mutual KEY 1 on FRDM-TOUCH board */
    {TSI0, {kTSI_Chnl_5}, kTSI_Chnl_6, 32U, 0U, 0U, 0U, 0U, 0U}, /* Mutual KEY 2 on FRDM-TOUCH board */
    {TSI0, {kTSI_Chnl_4}, kTSI_Chnl_7, 80U, 0U, 0U, 0U, 0U, 0U}, /* Mutual KEY 3 on FRDM-TOUCH board */
    {TSI0, {kTSI_Chnl_4}, kTSI_Chnl_6, 45U, 0U, 0U, 0U, 0U, 0U}, /* Mutual KEY 4 on FRDM-TOUCH board */

    /* Do NOT move {0xFFU, 0xFFU, 0xFFU, 0xFFU} which indicates the end of the array */
    {TSI0, {0xFFU}, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU} /* The end of the array */
};

/* If slider not needed, please fill 0xFFU */
slider_tsi_mapping_t slider_TSI[] = {
    /* tsi0, tsi1, tsi0_baseline, tsi1_baseline, baseline_delta, touch_delta */
    /* {kTSI_Chnl9, kTSI_Chnl10, 0, 0, 5, 100}, */
    /* {kTSI_Chnl9, kTSI_Chnl10, 0, 0, 5, 100}, */

    /* Do NOT move {0xFFU, 0xFFU, 0xFFU, 0xFFU} which indicates the end of the array */
    {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU} /* The end of the array */
};
