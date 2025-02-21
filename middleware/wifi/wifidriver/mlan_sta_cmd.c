/** @file mlan_sta_cmd.c
 *
 *  @brief This file provides the handling of command. It prepares command and sends it to firmware when it is ready
 *
 *  Copyright 2008-2021 NXP
 *
 *  NXP CONFIDENTIAL
 *  The source code contained or described herein and all documents related to
 *  the source code ("Materials") are owned by NXP, its
 *  suppliers and/or its licensors. Title to the Materials remains with NXP,
 *  its suppliers and/or its licensors. The Materials contain
 *  trade secrets and proprietary and confidential information of NXP, its
 *  suppliers and/or its licensors. The Materials are protected by worldwide copyright
 *  and trade secret laws and treaty provisions. No part of the Materials may be
 *  used, copied, reproduced, modified, published, uploaded, posted,
 *  transmitted, distributed, or disclosed in any way without NXP's prior
 *  express written permission.
 *
 *  No license under any patent, copyright, trade secret or other intellectual
 *  property right is granted to or conferred upon you by disclosure or delivery
 *  of the Materials, either expressly, by implication, inducement, estoppel or
 *  otherwise. Any license under such intellectual property rights must be
 *  express and approved by NXP in writing.
 *
 */

/******************************************************
Change log:
    10/21/2008: initial version
******************************************************/

#include <mlan_api.h>

/* Additional WMSDK header files */
#include <wmerrno.h>
#include <wm_os.h>

/* Always keep this include at the end of all include files */
#include <mlan_remap_mem_operations.h>
/********************************************************
                Local Variables
********************************************************/

/********************************************************
                Global Variables
********************************************************/

/********************************************************
                Local Functions
********************************************************/
#ifdef CONFIG_RF_TEST_MODE
/**
 *  @brief This function prepares command of MFG Continuous Tx cmd.
 *
 *  @param pmpriv       A pointer to mlan_private structure
 *  @param cmd          A pointer to HostCmd_DS_COMMAND structure
 *  @param action       The action: GET or SET
 *  @param pdata_buf    A pointer to data buffer
 *
 *  @return             MLAN_STATUS_SUCCESS
 */
static mlan_status wlan_cmd_mfg_tx_cont(pmlan_private pmpriv, HostCmd_DS_COMMAND *cmd, t_u16 action, t_void *pdata_buf)
{
    HostCmd_DS_MFG_CMD_TX_CONT *mcmd = (HostCmd_DS_MFG_CMD_TX_CONT *)&cmd->params.mfg_tx_cont;
    mlan_ds_mfg_cmd_tx_cont *cfg     = (mlan_ds_mfg_cmd_tx_cont *)pdata_buf;

    ENTER();

    (void)__memset(pmpriv->adapter, mcmd, 0x00, sizeof(HostCmd_DS_MFG_CMD_TX_CONT));

    cmd->command = wlan_cpu_to_le16(HostCmd_CMD_MFG_COMMAND);
    cmd->size    = wlan_cpu_to_le16(sizeof(HostCmd_DS_MFG_CMD_TX_CONT) + S_DS_GEN);

    mcmd->mfg_cmd = wlan_cpu_to_le32(cfg->mfg_cmd);
    mcmd->action  = wlan_cpu_to_le16(action);
    if (action == HostCmd_ACT_GEN_SET)
    {
        mcmd->enable_tx       = wlan_cpu_to_le32(cfg->enable_tx);
        mcmd->cw_mode         = wlan_cpu_to_le32(cfg->cw_mode);
        mcmd->payload_pattern = wlan_cpu_to_le32(cfg->payload_pattern);
        mcmd->cs_mode         = wlan_cpu_to_le32(cfg->cs_mode);
        mcmd->act_sub_ch      = wlan_cpu_to_le32(cfg->act_sub_ch);
        mcmd->tx_rate         = wlan_cpu_to_le32(cfg->tx_rate);
    }

    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of MFG Tx frame.
 *
 *  @param pmpriv       A pointer to mlan_private structure
 *  @param cmd          A pointer to HostCmd_DS_COMMAND structure
 *  @param action       The action: GET or SET
 *  @param pdata_buf    A pointer to data buffer
 *
 *  @return             MLAN_STATUS_SUCCESS
 */
static mlan_status wlan_cmd_mfg_tx_frame(pmlan_private pmpriv, HostCmd_DS_COMMAND *cmd, t_u16 action, t_void *pdata_buf)
{
    HostCmd_DS_MFG_CMD_TX_FRAME2 *mcmd = (HostCmd_DS_MFG_CMD_TX_FRAME2 *)&cmd->params.mfg_tx_frame2;
    mlan_ds_mfg_cmd_tx_frame2 *cfg     = (mlan_ds_mfg_cmd_tx_frame2 *)pdata_buf;

    ENTER();

    (void)__memset(pmpriv->adapter, mcmd, 0x00, sizeof(HostCmd_DS_MFG_CMD_TX_FRAME2));

    cmd->command = wlan_cpu_to_le16(HostCmd_CMD_MFG_COMMAND);
    cmd->size    = wlan_cpu_to_le16(sizeof(HostCmd_DS_MFG_CMD_TX_FRAME2) + S_DS_GEN);

    mcmd->mfg_cmd = wlan_cpu_to_le32(cfg->mfg_cmd);
    mcmd->action  = wlan_cpu_to_le16(action);
    if (action == HostCmd_ACT_GEN_SET)
    {
        mcmd->enable            = wlan_cpu_to_le32(cfg->enable);
        mcmd->data_rate         = wlan_cpu_to_le32(cfg->data_rate);
        mcmd->frame_pattern     = wlan_cpu_to_le32(cfg->frame_pattern);
        mcmd->frame_length      = wlan_cpu_to_le32(cfg->frame_length);
        mcmd->adjust_burst_sifs = wlan_cpu_to_le16(cfg->adjust_burst_sifs);
        mcmd->burst_sifs_in_us  = wlan_cpu_to_le32(cfg->burst_sifs_in_us);
        mcmd->short_preamble    = wlan_cpu_to_le32(cfg->short_preamble);
        mcmd->act_sub_ch        = wlan_cpu_to_le32(cfg->act_sub_ch);
        mcmd->short_gi          = wlan_cpu_to_le32(cfg->short_gi);
        mcmd->tx_bf             = wlan_cpu_to_le32(cfg->tx_bf);
        mcmd->gf_mode           = wlan_cpu_to_le32(cfg->gf_mode);
        mcmd->stbc              = wlan_cpu_to_le32(cfg->stbc);
        (void)__memcpy(pmpriv->adapter, mcmd->bssid, cfg->bssid, MLAN_MAC_ADDR_LENGTH);
    }

    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of MFG cmd.
 *
 *  @param pmpriv       A pointer to mlan_private structure
 *  @param cmd          A pointer to HostCmd_DS_COMMAND structure
 *  @param action       The action: GET or SET
 *  @param pdata_buf    A pointer to data buffer
 *
 *  @return             MLAN_STATUS_SUCCESS
 */
static mlan_status wlan_cmd_mfg(pmlan_private pmpriv, HostCmd_DS_COMMAND *cmd, t_u16 action, t_void *pdata_buf)
{
    HostCmd_DS_MFG_CMD_GENERIC_CFG *mcmd = (HostCmd_DS_MFG_CMD_GENERIC_CFG *)&cmd->params.mfg_generic_cfg;
    mlan_ds_mfg_cmd_generic_cfg *cfg     = (mlan_ds_mfg_cmd_generic_cfg *)pdata_buf;
    mlan_status ret                      = MLAN_STATUS_SUCCESS;

    ENTER();

    if (!mcmd || !cfg)
    {
        ret = MLAN_STATUS_FAILURE;
        goto cmd_mfg_done;
    }

    (void)__memset(pmpriv->adapter, mcmd, 0x00, sizeof(HostCmd_DS_MFG_CMD_GENERIC_CFG));

    switch (cfg->mfg_cmd)
    {
        case MFG_CMD_TX_FRAME:
            ret = wlan_cmd_mfg_tx_frame(pmpriv, cmd, action, pdata_buf);
            goto cmd_mfg_done;
            break;
        case MFG_CMD_TX_CONT:
            ret = wlan_cmd_mfg_tx_cont(pmpriv, cmd, action, pdata_buf);
            goto cmd_mfg_done;
            break;
        case MFG_CMD_SET_TEST_MODE:
        case MFG_CMD_UNSET_TEST_MODE:
        case MFG_CMD_TX_ANT:
        case MFG_CMD_RX_ANT:
        case MFG_CMD_RF_CHAN:
        case MFG_CMD_CLR_RX_ERR:
        case MFG_CMD_RF_BAND_AG:
        case MFG_CMD_RF_CHANNELBW:
        case MFG_CMD_RFPWR:
            break;
        default:
            ret = MLAN_STATUS_FAILURE;
            goto cmd_mfg_done;
    }
    cmd->command = wlan_cpu_to_le16(HostCmd_CMD_MFG_COMMAND);
    cmd->size    = wlan_cpu_to_le16(sizeof(HostCmd_DS_MFG_CMD_GENERIC_CFG) + S_DS_GEN);

    mcmd->mfg_cmd = wlan_cpu_to_le32(cfg->mfg_cmd);
    mcmd->action  = wlan_cpu_to_le16(action);
    if (action == HostCmd_ACT_GEN_SET)
    {
        mcmd->data1 = wlan_cpu_to_le32(cfg->data1);
        mcmd->data2 = wlan_cpu_to_le32(cfg->data2);
        mcmd->data3 = wlan_cpu_to_le32(cfg->data3);
    }
cmd_mfg_done:
    LEAVE();
    return ret;
}
#endif

/**
 *  @brief This function prepares command of RSSI info.
 *
 *  @param pmpriv       A pointer to mlan_private structure
 *  @param pcmd         A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   Command action
 *
 *  @return             MLAN_STATUS_SUCCESS
 */
static mlan_status wlan_cmd_802_11_rssi_info(IN pmlan_private pmpriv, IN HostCmd_DS_COMMAND *pcmd, IN t_u16 cmd_action)
{
    ENTER();

    pcmd->command                 = wlan_cpu_to_le16(HostCmd_CMD_RSSI_INFO);
    pcmd->size                    = wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_RSSI_INFO) + S_DS_GEN);
    pcmd->params.rssi_info.action = wlan_cpu_to_le16(cmd_action);
    pcmd->params.rssi_info.ndata  = wlan_cpu_to_le16(pmpriv->data_avg_factor);
    pcmd->params.rssi_info.nbcn   = wlan_cpu_to_le16(pmpriv->bcn_avg_factor);

    /* Reset SNR/NF/RSSI values in private structure */
    pmpriv->data_rssi_last = 0;
    pmpriv->data_nf_last   = 0;
    pmpriv->data_rssi_avg  = 0;
    pmpriv->data_nf_avg    = 0;
    pmpriv->bcn_rssi_last  = 0;
    pmpriv->bcn_nf_last    = 0;
    pmpriv->bcn_rssi_avg   = 0;
    pmpriv->bcn_nf_avg     = 0;

    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of mac_control.
 *
 *  @param pmpriv       A pointer to mlan_private structure
 *  @param pcmd         A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   Command action
 *  @param pdata_buf    A pointer to command information buffer
 *
 *  @return             MLAN_STATUS_SUCCESS or MLAN_STATUS_FAILURE
 */
static mlan_status wlan_cmd_mac_control(IN pmlan_private pmpriv,
                                        IN HostCmd_DS_COMMAND *pcmd,
                                        IN t_u16 cmd_action,
                                        IN t_void *pdata_buf)
{
    HostCmd_DS_MAC_CONTROL *pmac = &pcmd->params.mac_ctrl;
    t_u16 action                 = *((t_u16 *)pdata_buf);

    ENTER();

    if (cmd_action != HostCmd_ACT_GEN_SET)
    {
        PRINTM(MERROR, "wlan_cmd_mac_control(): support SET only.\n");
        LEAVE();
        return MLAN_STATUS_FAILURE;
    }

    pcmd->command = wlan_cpu_to_le16(HostCmd_CMD_MAC_CONTROL);
    pcmd->size    = wlan_cpu_to_le16(sizeof(HostCmd_DS_MAC_CONTROL) + S_DS_GEN);
    pmac->action  = wlan_cpu_to_le16(action);

    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of snmp_mib.
 *
 *  @param pmpriv       A pointer to mlan_private structure
 *  @param cmd          A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   The action: GET or SET
 *  @param cmd_oid      OID: ENABLE or DISABLE
 *  @param pdata_buf    A pointer to command information buffer
 *
 *  @return             MLAN_STATUS_SUCCESS
 */
static mlan_status wlan_cmd_802_11_snmp_mib(
    IN pmlan_private pmpriv, IN HostCmd_DS_COMMAND *cmd, IN t_u16 cmd_action, IN t_u32 cmd_oid, IN t_void *pdata_buf)
{
    HostCmd_DS_802_11_SNMP_MIB *psnmp_mib = &cmd->params.smib;
    t_u32 ul_temp;

    ENTER();
    PRINTM(MINFO, "SNMP_CMD: cmd_oid = 0x%x\n", cmd_oid);
    cmd->command = wlan_cpu_to_le16(HostCmd_CMD_802_11_SNMP_MIB);
    cmd->size    = sizeof(HostCmd_DS_802_11_SNMP_MIB) - 1 + S_DS_GEN;

    if (cmd_action == HostCmd_ACT_GEN_GET)
    {
        psnmp_mib->query_type = wlan_cpu_to_le16(HostCmd_ACT_GEN_GET);
        psnmp_mib->buf_size   = wlan_cpu_to_le16(MAX_SNMP_BUF_SIZE);
        cmd->size += MAX_SNMP_BUF_SIZE;
    }

    switch (cmd_oid)
    {
        case Dot11D_i:
            psnmp_mib->oid = wlan_cpu_to_le16((t_u16)Dot11D_i);
            if (cmd_action == HostCmd_ACT_GEN_SET)
            {
                psnmp_mib->query_type          = wlan_cpu_to_le16(HostCmd_ACT_GEN_SET);
                psnmp_mib->buf_size            = wlan_cpu_to_le16(sizeof(t_u16));
                ul_temp                        = *(t_u32 *)pdata_buf;
                *((t_u16 *)(psnmp_mib->value)) = wlan_cpu_to_le16((t_u16)ul_temp);
                cmd->size += sizeof(t_u16);
            }
            break;
        case Dot11H_i:
            psnmp_mib->oid = wlan_cpu_to_le16((t_u16)Dot11H_i);
            if (cmd_action == HostCmd_ACT_GEN_SET)
            {
                psnmp_mib->query_type          = wlan_cpu_to_le16(HostCmd_ACT_GEN_SET);
                psnmp_mib->buf_size            = wlan_cpu_to_le16(sizeof(t_u16));
                ul_temp                        = *(t_u32 *)pdata_buf;
                *((t_u16 *)(psnmp_mib->value)) = wlan_cpu_to_le16((t_u16)ul_temp);
                cmd->size += sizeof(t_u16);
            }
            break;
        case ECSAEnable_i:
            psnmp_mib->oid = wlan_cpu_to_le16((t_u16)ECSAEnable_i);
            if (cmd_action == HostCmd_ACT_GEN_SET)
            {
                psnmp_mib->query_type = wlan_cpu_to_le16(HostCmd_ACT_GEN_SET);
                psnmp_mib->buf_size   = wlan_cpu_to_le16(sizeof(t_u8));
                psnmp_mib->value[0]   = *((t_u8 *)pdata_buf);
                cmd->size += sizeof(t_u8);
            }
            break;
        default:
            break;
    }
    cmd->size = wlan_cpu_to_le16(cmd->size);
    PRINTM(MINFO, "SNMP_CMD: Action=0x%x, OID=0x%x, OIDSize=0x%x, Value=0x%x\n", cmd_action, cmd_oid,
           wlan_le16_to_cpu(psnmp_mib->buf_size), wlan_le16_to_cpu(*(t_u16 *)psnmp_mib->value));
    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of get_log.
 *
 *  @param pmpriv       A pointer to mlan_private structure
 *  @param cmd          A pointer to HostCmd_DS_COMMAND structure
 *
 *  @return             MLAN_STATUS_SUCCESS
 */
static mlan_status wlan_cmd_802_11_get_log(IN pmlan_private pmpriv, IN HostCmd_DS_COMMAND *cmd)
{
    ENTER();
    cmd->command = wlan_cpu_to_le16(HostCmd_CMD_802_11_GET_LOG);
    cmd->size    = wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_GET_LOG) + S_DS_GEN);
    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of tx_power_cfg.
 *
 *  @param pmpriv      A pointer to mlan_private structure
 *  @param cmd         A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action  The action: GET or SET
 *  @param pdata_buf   A pointer to data buffer
 *
 *  @return            MLAN_STATUS_SUCCESS
 */
static mlan_status wlan_cmd_tx_power_cfg(IN pmlan_private pmpriv,
                                         IN HostCmd_DS_COMMAND *cmd,
                                         IN t_u16 cmd_action,
                                         IN t_void *pdata_buf)
{
    MrvlTypes_Power_Group_t *ppg_tlv = MNULL;
    HostCmd_DS_TXPWR_CFG *ptxp       = MNULL;
    HostCmd_DS_TXPWR_CFG *ptxp_cfg   = &cmd->params.txp_cfg;

    ENTER();

    cmd->command = wlan_cpu_to_le16(HostCmd_CMD_TXPWR_CFG);
    cmd->size    = wlan_cpu_to_le16(S_DS_GEN + sizeof(HostCmd_DS_TXPWR_CFG));
    switch (cmd_action)
    {
        case HostCmd_ACT_GEN_SET:
            ptxp = (HostCmd_DS_TXPWR_CFG *)pdata_buf;
            if (ptxp->mode)
            {
                ppg_tlv = (MrvlTypes_Power_Group_t *)((t_u8 *)pdata_buf + sizeof(HostCmd_DS_TXPWR_CFG));
                (void)memmove(pmpriv->adapter, ptxp_cfg, pdata_buf,
                              sizeof(HostCmd_DS_TXPWR_CFG) + sizeof(MrvlTypes_Power_Group_t) + ppg_tlv->length);

                ppg_tlv = (MrvlTypes_Power_Group_t *)((t_u8 *)&cmd->params + sizeof(HostCmd_DS_TXPWR_CFG));
                cmd->size += wlan_cpu_to_le16(sizeof(MrvlTypes_Power_Group_t) + ppg_tlv->length);
                ppg_tlv->type   = wlan_cpu_to_le16(ppg_tlv->type);
                ppg_tlv->length = wlan_cpu_to_le16(ppg_tlv->length);
            }
            else
            {
                (void)memmove(pmpriv->adapter, ptxp_cfg, pdata_buf, sizeof(HostCmd_DS_TXPWR_CFG));
            }
            ptxp_cfg->action    = wlan_cpu_to_le16(cmd_action);
            ptxp_cfg->cfg_index = wlan_cpu_to_le16(ptxp_cfg->cfg_index);
            ptxp_cfg->mode      = wlan_cpu_to_le32(ptxp_cfg->mode);
            break;
        case HostCmd_ACT_GEN_GET:
            ptxp_cfg->action = wlan_cpu_to_le16(cmd_action);
            break;
    }

    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of rf_tx_power.
 *
 *  @param pmpriv     A pointer to wlan_private structure
 *  @param cmd        A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action the action: GET or SET
 *  @param pdata_buf  A pointer to data buffer
 *  @return           MLAN_STATUS_SUCCESS
 */
static mlan_status wlan_cmd_802_11_rf_tx_power(IN pmlan_private pmpriv,
                                               IN HostCmd_DS_COMMAND *cmd,
                                               IN t_u16 cmd_action,
                                               IN t_void *pdata_buf)
{
    HostCmd_DS_802_11_RF_TX_POWER *prtp = &cmd->params.txp;

    ENTER();

    cmd->size    = wlan_cpu_to_le16((sizeof(HostCmd_DS_802_11_RF_TX_POWER)) + S_DS_GEN);
    cmd->command = wlan_cpu_to_le16(HostCmd_CMD_802_11_RF_TX_POWER);
    prtp->action = cmd_action;

    PRINTM(MINFO, "RF_TX_POWER_CMD: Size:%d Cmd:0x%x Act:%d\n", cmd->size, cmd->command, prtp->action);

    switch (cmd_action)
    {
        case HostCmd_ACT_GEN_GET:
            prtp->action        = wlan_cpu_to_le16(HostCmd_ACT_GEN_GET);
            prtp->current_level = 0;
            break;

        case HostCmd_ACT_GEN_SET:
            prtp->action        = wlan_cpu_to_le16(HostCmd_ACT_GEN_SET);
            prtp->current_level = wlan_cpu_to_le16(*((t_u16 *)pdata_buf));
            break;
    }
    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/**
 * @brief This function prepares command of hs_cfg.
 *
 * @param pmpriv       A pointer to mlan_private structure
 * @param cmd          A pointer to HostCmd_DS_COMMAND structure
 * @param cmd_action   The action: GET or SET
 * @param pdata_buf    A pointer to data buffer
 *
 * @return             MLAN_STATUS_SUCCESS
 */
static mlan_status wlan_cmd_802_11_hs_cfg(IN pmlan_private pmpriv,
                                          IN HostCmd_DS_COMMAND *cmd,
                                          IN t_u16 cmd_action,
                                          IN hs_config_param *pdata_buf)
{
    HostCmd_DS_802_11_HS_CFG_ENH *phs_cfg = &cmd->params.opt_hs_cfg;
    t_u16 hs_activate                     = MFALSE;

    ENTER();
    if (pdata_buf == MNULL)
    {
        /* New Activate command */
        hs_activate = MTRUE;
    }
    cmd->command = wlan_cpu_to_le16(HostCmd_CMD_802_11_HS_CFG_ENH);

    cmd->size = wlan_cpu_to_le16(S_DS_GEN + sizeof(HostCmd_DS_802_11_HS_CFG_ENH));

    if (hs_activate != 0U)
    {
        phs_cfg->action                       = wlan_cpu_to_le16(HS_ACTIVATE);
        phs_cfg->params.hs_activate.resp_ctrl = wlan_cpu_to_le16(RESP_NEEDED);
    }
    else
    {
        phs_cfg->action                      = wlan_cpu_to_le16(HS_CONFIGURE);
        phs_cfg->params.hs_config.conditions = wlan_cpu_to_le32(pdata_buf->conditions);
        phs_cfg->params.hs_config.gpio       = pdata_buf->gpio;
        phs_cfg->params.hs_config.gap        = pdata_buf->gap;
        PRINTM(MCMND, "HS_CFG_CMD: condition:0x%x gpio:0x%x gap:0x%x\n", phs_cfg->params.hs_config.conditions,
               phs_cfg->params.hs_config.gpio, phs_cfg->params.hs_config.gap);
    }

    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of mac_address.
 *
 *  @param pmpriv       A pointer to mlan_private structure
 *  @param cmd          A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   The action: GET or SET
 *
 *  @return             MLAN_STATUS_SUCCESS
 */
static mlan_status wlan_cmd_802_11_mac_address(IN pmlan_private pmpriv,
                                               IN HostCmd_DS_COMMAND *cmd,
                                               IN t_u16 cmd_action,
                                               t_void *pdata_buf)
{
    ENTER();
    cmd->command = wlan_cpu_to_le16(HostCmd_CMD_802_11_MAC_ADDRESS);
    cmd->size    = wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_MAC_ADDRESS) + S_DS_GEN);
    cmd->result  = 0;

    cmd->params.mac_addr.action = wlan_cpu_to_le16(cmd_action);

    if (cmd_action == HostCmd_ACT_GEN_SET)
    {
        (void)__memcpy(pmpriv->adapter, cmd->params.mac_addr.mac_addr, pdata_buf, MLAN_MAC_ADDR_LENGTH);
        // HEXDUMP("SET_CMD: MAC ADDRESS-", priv->CurrentAddr, 6);
    }
    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of mac_multicast_adr.
 *
 *  @param pmpriv       A pointer to mlan_private structure
 *  @param cmd          A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   The action: GET or SET
 *  @param pdata_buf    A pointer to data buffer
 *
 *  @return             MLAN_STATUS_SUCCESS
 */
static mlan_status wlan_cmd_mac_multicast_adr(IN pmlan_private pmpriv,
                                              IN HostCmd_DS_COMMAND *cmd,
                                              IN t_u16 cmd_action,
                                              IN t_void *pdata_buf)
{
    mlan_multicast_list *pmcast_list       = (mlan_multicast_list *)pdata_buf;
    HostCmd_DS_MAC_MULTICAST_ADR *pmc_addr = &cmd->params.mc_addr;

    ENTER();
    cmd->size    = wlan_cpu_to_le16(sizeof(HostCmd_DS_MAC_MULTICAST_ADR) + S_DS_GEN);
    cmd->command = wlan_cpu_to_le16(HostCmd_CMD_MAC_MULTICAST_ADR);

    pmc_addr->action      = wlan_cpu_to_le16(cmd_action);
    pmc_addr->num_of_adrs = wlan_cpu_to_le16((t_u16)pmcast_list->num_multicast_addr);
    (void)__memcpy(pmpriv->adapter, pmc_addr->mac_list, pmcast_list->mac_list,
                   pmcast_list->num_multicast_addr * MLAN_MAC_ADDR_LENGTH);

    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of deauthenticate.
 *
 * @param pmpriv       A pointer to mlan_private structure
 * @param cmd          A pointer to HostCmd_DS_COMMAND structure
 * @param pdata_buf    A pointer to data buffer
 *
 * @return             MLAN_STATUS_SUCCESS
 */
/* static */ mlan_status wlan_cmd_802_11_deauthenticate(IN pmlan_private pmpriv,
                                                        IN HostCmd_DS_COMMAND *cmd,
                                                        IN t_void *pdata_buf)
{
    HostCmd_DS_802_11_DEAUTHENTICATE *pdeauth = &cmd->params.deauth;

    ENTER();

    cmd->command = wlan_cpu_to_le16(HostCmd_CMD_802_11_DEAUTHENTICATE);
    cmd->size    = wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_DEAUTHENTICATE) + S_DS_GEN);

    /* Set AP MAC address */
    (void)__memcpy(pmpriv->adapter, pdeauth->mac_addr, (t_u8 *)pdata_buf, MLAN_MAC_ADDR_LENGTH);

    PRINTM(MCMND, "Deauth: %02x:%02x:%02x:%02x:%02x:%02x\n", pdeauth->mac_addr[0], pdeauth->mac_addr[1],
           pdeauth->mac_addr[2], pdeauth->mac_addr[3], pdeauth->mac_addr[4], pdeauth->mac_addr[5]);

    if (pmpriv->adapter->state_11h.recvd_chanswann_event)
    {
/** Reason code 36 = Requested from peer station as it is leaving the BSS */
#define REASON_CODE_PEER_STA_LEAVING 36
        pdeauth->reason_code = wlan_cpu_to_le16(REASON_CODE_PEER_STA_LEAVING);
    }
    else
    {
/** Reason code 3 = Station is leaving */
#define REASON_CODE_STA_LEAVING 3
        pdeauth->reason_code = wlan_cpu_to_le16(REASON_CODE_STA_LEAVING);
    }

    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of key_material.
 *
 *  @param pmpriv       A pointer to mlan_private structure
 *  @param cmd          A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   The action: GET or SET
 *  @param cmd_oid      OID: ENABLE or DISABLE
 *  @param pdata_buf    A pointer to data buffer
 *
 *  @return             MLAN_STATUS_SUCCESS or MLAN_STATUS_FAILURE
 */
static mlan_status wlan_cmd_802_11_key_material(
    IN pmlan_private pmpriv, IN HostCmd_DS_COMMAND *cmd, IN t_u16 cmd_action, IN t_u32 cmd_oid, IN t_void *pdata_buf)
{
    HostCmd_DS_802_11_KEY_MATERIAL *pkey_material = &cmd->params.key_material;
    mlan_ds_encrypt_key *pkey                     = (mlan_ds_encrypt_key *)pdata_buf;
    mlan_status ret                               = MLAN_STATUS_SUCCESS;

    ENTER();
    if (!pkey)
    {
        ret = MLAN_STATUS_FAILURE;
        goto done;
    }
    cmd->command          = wlan_cpu_to_le16(HostCmd_CMD_802_11_KEY_MATERIAL);
    pkey_material->action = wlan_cpu_to_le16(cmd_action);
    if (cmd_action == HostCmd_ACT_GEN_GET)
    {
        PRINTM(MCMND, "GET Key\n");
        pkey_material->key_param_set.key_idx = pkey->key_index & KEY_INDEX_MASK;
        pkey_material->key_param_set.type    = wlan_cpu_to_le16(TLV_TYPE_KEY_PARAM_V2);
        pkey_material->key_param_set.length  = wlan_cpu_to_le16(KEY_PARAMS_FIXED_LEN);
        (void)__memcpy(pmpriv->adapter, pkey_material->key_param_set.mac_addr, pkey->mac_addr, MLAN_MAC_ADDR_LENGTH);
        if (pkey->key_flags & KEY_FLAG_GROUP_KEY)
            pkey_material->key_param_set.key_info |= KEY_INFO_MCAST_KEY;
        else
            pkey_material->key_param_set.key_info |= KEY_INFO_UCAST_KEY;
        if (pkey->key_flags & KEY_FLAG_AES_MCAST_IGTK)
            pkey_material->key_param_set.key_info = KEY_INFO_CMAC_AES_KEY;
        pkey_material->key_param_set.key_info = wlan_cpu_to_le16(pkey_material->key_param_set.key_info);
        cmd->size = wlan_cpu_to_le16(sizeof(MrvlIEtypesHeader_t) + S_DS_GEN + KEY_PARAMS_FIXED_LEN +
                                     sizeof(pkey_material->action));
        goto done;
    }
    (void)__memset(pmpriv->adapter, &pkey_material->key_param_set, 0, sizeof(MrvlIEtype_KeyParamSetV2_t));
    if (pkey->key_flags & KEY_FLAG_REMOVE_KEY)
    {
        pkey_material->action                 = wlan_cpu_to_le16(HostCmd_ACT_GEN_REMOVE);
        pkey_material->key_param_set.type     = wlan_cpu_to_le16(TLV_TYPE_KEY_PARAM_V2);
        pkey_material->key_param_set.length   = wlan_cpu_to_le16(KEY_PARAMS_FIXED_LEN);
        pkey_material->key_param_set.key_idx  = pkey->key_index & KEY_INDEX_MASK;
        pkey_material->key_param_set.key_info = KEY_INFO_MCAST_KEY | KEY_INFO_UCAST_KEY;
        (void)__memcpy(pmpriv->adapter, pkey_material->key_param_set.mac_addr, pkey->mac_addr, MLAN_MAC_ADDR_LENGTH);
        cmd->size = wlan_cpu_to_le16(sizeof(MrvlIEtypesHeader_t) + S_DS_GEN + KEY_PARAMS_FIXED_LEN +
                                     sizeof(pkey_material->action));
        PRINTM(MCMND, "Remove Key\n");
        goto done;
    }
    pkey_material->action                 = wlan_cpu_to_le16(HostCmd_ACT_GEN_SET);
    pkey_material->key_param_set.key_idx  = pkey->key_index & KEY_INDEX_MASK;
    pkey_material->key_param_set.type     = wlan_cpu_to_le16(TLV_TYPE_KEY_PARAM_V2);
    pkey_material->key_param_set.key_info = KEY_INFO_ENABLE_KEY;
    (void)__memcpy(pmpriv->adapter, pkey_material->key_param_set.mac_addr, pkey->mac_addr, MLAN_MAC_ADDR_LENGTH);
    if (pkey->key_len <= MAX_WEP_KEY_SIZE)
    {
        pkey_material->key_param_set.length   = wlan_cpu_to_le16(KEY_PARAMS_FIXED_LEN + sizeof(wep_param_t));
        pkey_material->key_param_set.key_type = KEY_TYPE_ID_WEP;
        if (pkey->is_current_wep_key)
        {
            pkey_material->key_param_set.key_info |= KEY_INFO_MCAST_KEY | KEY_INFO_UCAST_KEY;
            if (pkey_material->key_param_set.key_idx == (pmpriv->wep_key_curr_index & KEY_INDEX_MASK))
                pkey_material->key_param_set.key_info |= KEY_INFO_DEFAULT_KEY;
        }
        else
        {
            if (pkey->key_flags & KEY_FLAG_GROUP_KEY)
                pkey_material->key_param_set.key_info |= KEY_INFO_MCAST_KEY;
            else
                pkey_material->key_param_set.key_info |= KEY_INFO_UCAST_KEY;
            if (pkey->key_flags & KEY_FLAG_SET_TX_KEY)
                pkey_material->key_param_set.key_info |= KEY_INFO_DEFAULT_KEY;
        }
        pkey_material->key_param_set.key_info               = wlan_cpu_to_le16(pkey_material->key_param_set.key_info);
        pkey_material->key_param_set.key_params.wep.key_len = wlan_cpu_to_le16(pkey->key_len);
        (void)__memcpy(pmpriv->adapter, pkey_material->key_param_set.key_params.wep.key, pkey->key_material,
                       pkey->key_len);
        cmd->size = wlan_cpu_to_le16(sizeof(MrvlIEtypesHeader_t) + S_DS_GEN + KEY_PARAMS_FIXED_LEN +
                                     sizeof(wep_param_t) + sizeof(pkey_material->action));
        PRINTM(MCMND, "Set WEP Key\n");
        goto done;
    }
    if (pkey->key_flags & KEY_FLAG_GROUP_KEY)
        pkey_material->key_param_set.key_info |= KEY_INFO_MCAST_KEY;
    else
        pkey_material->key_param_set.key_info |= KEY_INFO_UCAST_KEY;
    if (pkey->key_flags & KEY_FLAG_SET_TX_KEY)
        pkey_material->key_param_set.key_info |= KEY_INFO_TX_KEY | KEY_INFO_RX_KEY;
    else
        pkey_material->key_param_set.key_info |= KEY_INFO_RX_KEY;
    if (pmpriv->bss_mode == MLAN_BSS_MODE_INFRA)
    {
        /* Enable default key for WPA/WPA2 */
        if (!pmpriv->wpa_is_gtk_set)
            pkey_material->key_param_set.key_info |= KEY_INFO_DEFAULT_KEY;
    }
    else
    {
        pkey_material->key_param_set.key_info |= KEY_INFO_DEFAULT_KEY;
        /* Enable unicast bit for WPA-NONE/ADHOC_AES */
        if ((!pmpriv->sec_info.wpa2_enabled) && (pkey->key_flags & KEY_FLAG_SET_TX_KEY))
            pkey_material->key_param_set.key_info |= KEY_INFO_UCAST_KEY;
    }
    pkey_material->key_param_set.key_info = wlan_cpu_to_le16(pkey_material->key_param_set.key_info);
    if (pkey->key_len == WPA_AES_KEY_LEN && !(pkey->key_flags & KEY_FLAG_AES_MCAST_IGTK))
    {
        if (pkey->key_flags & (KEY_FLAG_RX_SEQ_VALID | KEY_FLAG_TX_SEQ_VALID))
            (void)__memcpy(pmpriv->adapter, pkey_material->key_param_set.key_params.aes.pn, pkey->pn, SEQ_MAX_SIZE);
        pkey_material->key_param_set.key_type               = KEY_TYPE_ID_AES;
        pkey_material->key_param_set.key_params.aes.key_len = wlan_cpu_to_le16(pkey->key_len);
        (void)__memcpy(pmpriv->adapter, pkey_material->key_param_set.key_params.aes.key, pkey->key_material,
                       pkey->key_len);
        pkey_material->key_param_set.length = wlan_cpu_to_le16(KEY_PARAMS_FIXED_LEN + sizeof(aes_param));
        cmd->size = wlan_cpu_to_le16(sizeof(MrvlIEtypesHeader_t) + S_DS_GEN + KEY_PARAMS_FIXED_LEN + sizeof(aes_param) +
                                     sizeof(pkey_material->action));
        PRINTM(MCMND, "Set AES Key\n");
        goto done;
    }
    if (pkey->key_len == WPA_IGTK_KEY_LEN && (pkey->key_flags & KEY_FLAG_AES_MCAST_IGTK))
    {
        if (pkey->key_flags & (KEY_FLAG_RX_SEQ_VALID | KEY_FLAG_TX_SEQ_VALID))
            (void)__memcpy(pmpriv->adapter, pkey_material->key_param_set.key_params.cmac_aes.ipn, pkey->pn,
                           SEQ_MAX_SIZE);
        pkey_material->key_param_set.key_info &= ~KEY_INFO_MCAST_KEY;
        pkey_material->key_param_set.key_info |= wlan_cpu_to_le16(KEY_INFO_AES_MCAST_IGTK);
        pkey_material->key_param_set.key_type                    = KEY_TYPE_ID_AES_CMAC;
        pkey_material->key_param_set.key_params.cmac_aes.key_len = wlan_cpu_to_le16(pkey->key_len);
        (void)__memcpy(pmpriv->adapter, pkey_material->key_param_set.key_params.cmac_aes.key, pkey->key_material,
                       pkey->key_len);
        pkey_material->key_param_set.length = wlan_cpu_to_le16(KEY_PARAMS_FIXED_LEN + sizeof(cmac_aes_param));
        cmd->size = wlan_cpu_to_le16(sizeof(MrvlIEtypesHeader_t) + S_DS_GEN + KEY_PARAMS_FIXED_LEN +
                                     sizeof(cmac_aes_param) + sizeof(pkey_material->action));
        PRINTM(MCMND, "Set CMAC AES Key\n");
        goto done;
    }
    if (pkey->key_len == WPA_TKIP_KEY_LEN)
    {
        if (pkey->key_flags & (KEY_FLAG_RX_SEQ_VALID | KEY_FLAG_TX_SEQ_VALID))
            (void)__memcpy(pmpriv->adapter, pkey_material->key_param_set.key_params.tkip.pn, pkey->pn, SEQ_MAX_SIZE);
        pkey_material->key_param_set.key_type                = KEY_TYPE_ID_TKIP;
        pkey_material->key_param_set.key_params.tkip.key_len = wlan_cpu_to_le16(pkey->key_len);
        (void)__memcpy(pmpriv->adapter, pkey_material->key_param_set.key_params.tkip.key, pkey->key_material,
                       pkey->key_len);
        pkey_material->key_param_set.length = wlan_cpu_to_le16(KEY_PARAMS_FIXED_LEN + sizeof(tkip_param));
        cmd->size = wlan_cpu_to_le16(sizeof(MrvlIEtypesHeader_t) + S_DS_GEN + KEY_PARAMS_FIXED_LEN +
                                     sizeof(tkip_param) + sizeof(pkey_material->action));
        PRINTM(MCMND, "Set TKIP Key\n");
    }
done:
#if 0
	dump_hex(cmd, cmd->size);
#endif
    LEAVE();
    return ret;
}

/**
 *  @brief This function prepares command of supplicant pmk
 *
 *  @param pmpriv       A pointer to mlan_private structure
 *  @param cmd          A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   The action: GET or SET
 *  @param pdata_buf    A pointer to data buffer
 *
 *  @return             MLAN_STATUS_SUCCESS or MLAN_STATUS_FAILURE
 */
static mlan_status wlan_cmd_802_11_supplicant_pmk(IN pmlan_private pmpriv,
                                                  IN HostCmd_DS_COMMAND *cmd,
                                                  IN t_u16 cmd_action,
                                                  IN t_void *pdata_buf)
{
    MrvlIEtypes_PMK_t *ppmk_tlv                        = MNULL;
    MrvlIEtypes_Passphrase_t *ppassphrase_tlv          = MNULL;
    MrvlIEtypes_Password_t *ppassword_tlv              = MNULL;
    MrvlIEtypes_SsIdParamSet_t *pssid_tlv              = MNULL;
    MrvlIEtypes_Bssid_t *pbssid_tlv                    = MNULL;
    HostCmd_DS_802_11_SUPPLICANT_PMK *pesupplicant_psk = &cmd->params.esupplicant_psk;
    t_u8 *ptlv_buffer                                  = (t_u8 *)pesupplicant_psk->tlv_buffer;
    mlan_ds_passphrase *psk                            = (mlan_ds_passphrase *)pdata_buf;
    t_u8 zero_mac[]                                    = {0, 0, 0, 0, 0, 0};

    ENTER();
    /*
     * Parse the rest of the buf here
     *      1)  <ssid="valid ssid"> - This will get the passphrase, AKMP
     *          for specified ssid, if none specified then it will get all.
     *          Eg: iwpriv <mlanX> passphrase 0:ssid=nxp
     *      2)  <psk="psk">:<passphrase="passphare">:<bssid="00:50:43:ef:23:f3">
     *          <ssid="valid ssid"> - passphrase and psk cannot be provided to
     *          the same SSID, Takes one SSID at a time, If ssid= is present
     *          the it should contain a passphrase or psk. If no arguments are
     *          provided then AKMP=802.1x, and passphrase should be provided
     *          after association.
     *          End of each parameter should be followed by a ':'(except for the
     *          last parameter) as the delimiter. If ':' has to be used in
     *          an SSID then a '/' should be preceded to ':' as a escape.
     *          Eg:iwpriv <mlanX> passphrase
     *                    "1:ssid=mrvl AP:psk=abcdefgh:bssid=00:50:43:ef:23:f3"
     *          iwpriv <mlanX> passphrase
     *                 "1:ssid=mrvl/: AP:psk=abcdefgd:bssid=00:50:43:ef:23:f3"
     *          iwpriv <mlanX> passphrase "1:ssid=mrvlAP:psk=abcdefgd"
     *      3)  <ssid="valid ssid"> - This will clear the passphrase
     *          for specified ssid, if none specified then it will clear all.
     *          Eg: iwpriv <mlanX> passphrase 2:ssid=nxp
     */

    /* -1 is for t_u8 TlvBuffer[1] as this should not be included */
    cmd->size = sizeof(HostCmd_DS_802_11_SUPPLICANT_PMK) + S_DS_GEN - 1;
    if (psk->ssid.ssid_len)
    {
        pssid_tlv              = (MrvlIEtypes_SsIdParamSet_t *)ptlv_buffer;
        pssid_tlv->header.type = wlan_cpu_to_le16(TLV_TYPE_SSID);
        pssid_tlv->header.len  = (t_u16)MIN(MLAN_MAX_SSID_LENGTH, psk->ssid.ssid_len);
        (void)__memcpy(pmpriv->adapter, (char *)pssid_tlv->ssid, psk->ssid.ssid,
                       MIN(MLAN_MAX_SSID_LENGTH, psk->ssid.ssid_len));
        ptlv_buffer += (pssid_tlv->header.len + sizeof(MrvlIEtypesHeader_t));
        cmd->size += (pssid_tlv->header.len + sizeof(MrvlIEtypesHeader_t));
        pssid_tlv->header.len = wlan_cpu_to_le16(pssid_tlv->header.len);
    }
    if (memcmp(pmpriv->adapter, (t_u8 *)&psk->bssid, zero_mac, sizeof(zero_mac)))
    {
        pbssid_tlv              = (MrvlIEtypes_Bssid_t *)ptlv_buffer;
        pbssid_tlv->header.type = wlan_cpu_to_le16(TLV_TYPE_BSSID);
        pbssid_tlv->header.len  = MLAN_MAC_ADDR_LENGTH;
        (void)__memcpy(pmpriv->adapter, pbssid_tlv->bssid, (t_u8 *)&psk->bssid, MLAN_MAC_ADDR_LENGTH);
        ptlv_buffer += (pbssid_tlv->header.len + sizeof(MrvlIEtypesHeader_t));
        cmd->size += (pbssid_tlv->header.len + sizeof(MrvlIEtypesHeader_t));
        pbssid_tlv->header.len = wlan_cpu_to_le16(pbssid_tlv->header.len);
    }
    if (psk->psk_type == MLAN_PSK_PASSPHRASE)
    {
        ppassphrase_tlv              = (MrvlIEtypes_Passphrase_t *)ptlv_buffer;
        ppassphrase_tlv->header.type = wlan_cpu_to_le16(TLV_TYPE_PASSPHRASE);
        ppassphrase_tlv->header.len  = (t_u16)MIN(MLAN_MAX_PASSPHRASE_LENGTH, psk->psk.passphrase.passphrase_len);
        (void)__memcpy(pmpriv->adapter, ppassphrase_tlv->passphrase, psk->psk.passphrase.passphrase,
                       MIN(MLAN_MAX_PASSPHRASE_LENGTH, psk->psk.passphrase.passphrase_len));
        ptlv_buffer += (ppassphrase_tlv->header.len + sizeof(MrvlIEtypesHeader_t));
        cmd->size += (ppassphrase_tlv->header.len + sizeof(MrvlIEtypesHeader_t));
        ppassphrase_tlv->header.len = wlan_cpu_to_le16(ppassphrase_tlv->header.len);
    }
    if (psk->psk_type == MLAN_PSK_PASSWORD)
    {
        ppassword_tlv              = (MrvlIEtypes_Password_t *)ptlv_buffer;
        ppassword_tlv->header.type = wlan_cpu_to_le16(TLV_TYPE_WPA3_SAE_PASSWORD);
        ppassword_tlv->header.len  = (t_u16)MIN(MLAN_MAX_PASSWORD_LENGTH, psk->password.password_len);
        (void)__memcpy(pmpriv->adapter, ppassword_tlv->password, psk->password.password,
                       MIN(MLAN_MAX_PASSWORD_LENGTH, psk->password.password_len));
        ptlv_buffer += (ppassword_tlv->header.len + sizeof(MrvlIEtypesHeader_t));
        cmd->size += (ppassword_tlv->header.len + sizeof(MrvlIEtypesHeader_t));
        ppassword_tlv->header.len = wlan_cpu_to_le16(ppassword_tlv->header.len);
    }
    if (psk->psk_type == MLAN_PSK_PMK)
    {
        ppmk_tlv              = (MrvlIEtypes_PMK_t *)ptlv_buffer;
        ppmk_tlv->header.type = wlan_cpu_to_le16(TLV_TYPE_PMK);
        ppmk_tlv->header.len  = MLAN_MAX_KEY_LENGTH;
        (void)__memcpy(pmpriv->adapter, ppmk_tlv->pmk, psk->psk.pmk.pmk, MLAN_MAX_KEY_LENGTH);
        ptlv_buffer += (ppmk_tlv->header.len + sizeof(MrvlIEtypesHeader_t));
        cmd->size += (ppmk_tlv->header.len + sizeof(MrvlIEtypesHeader_t));
        ppmk_tlv->header.len = wlan_cpu_to_le16(ppmk_tlv->header.len);
    }
    if ((cmd_action == HostCmd_ACT_GEN_SET) &&
        ((pssid_tlv || pbssid_tlv) && (!ppmk_tlv && !ppassphrase_tlv && !ppassword_tlv)))
    {
        PRINTM(MERROR, "Invalid case,ssid/bssid present without pmk or passphrase or password\n");
        LEAVE();
        return MLAN_STATUS_FAILURE;
    }
    cmd->command                   = wlan_cpu_to_le16(HostCmd_CMD_SUPPLICANT_PMK);
    pesupplicant_psk->action       = wlan_cpu_to_le16(cmd_action);
    pesupplicant_psk->cache_result = 0;
    cmd->size                      = wlan_cpu_to_le16(cmd->size);
    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of rf_channel.
 *
 *  @param pmpriv       A pointer to mlan_private structure
 *  @param cmd          A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   The action: GET or SET
 *  @param pdata_buf    A pointer to data buffer
 *
 *  @return             MLAN_STATUS_SUCCESS
 */
static mlan_status wlan_cmd_802_11_rf_channel(IN pmlan_private pmpriv,
                                              IN HostCmd_DS_COMMAND *cmd,
                                              IN t_u16 cmd_action,
                                              IN t_void *pdata_buf)
{
    HostCmd_DS_802_11_RF_CHANNEL *prf_chan = &cmd->params.rf_channel;

    ENTER();

    cmd->command = wlan_cpu_to_le16(HostCmd_CMD_802_11_RF_CHANNEL);
    cmd->size    = wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_RF_CHANNEL) + S_DS_GEN);

    if (cmd_action == HostCmd_ACT_GEN_SET)
    {
        if ((pmpriv->adapter->adhoc_start_band & BAND_A) || (pmpriv->adapter->adhoc_start_band & BAND_AN))
            prf_chan->rf_type = HostCmd_SCAN_RADIO_TYPE_A;
        SET_SECONDARYCHAN(prf_chan->rf_type, pmpriv->adapter->chan_bandwidth);
        prf_chan->rf_type         = wlan_cpu_to_le16(prf_chan->rf_type);
        prf_chan->current_channel = wlan_cpu_to_le16(*((t_u16 *)pdata_buf));
    }
    prf_chan->action = wlan_cpu_to_le16(cmd_action);
    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of mgmt IE list.
 *
 *  @param pmpriv       A pointer to mlan_private structure
 *  @param cmd          A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   The action: GET or SET
 *  @param pdata_buf	A pointer to data buffer
 *
 *  @return             MLAN_STATUS_SUCCESS
 */
static mlan_status wlan_cmd_mgmt_ie_list(IN pmlan_private pmpriv,
                                         IN HostCmd_DS_COMMAND *cmd,
                                         IN t_u16 cmd_action,
                                         IN t_void *pdata_buf)
{
    t_u16 req_len = 0, travel_len = 0;
    custom_ie *cptr                            = MNULL;
    mlan_ds_misc_custom_ie *cust_ie            = MNULL;
    HostCmd_DS_MGMT_IE_LIST_CFG *pmgmt_ie_list = &(cmd->params.mgmt_ie_list);

    ENTER();

    cmd->command          = wlan_cpu_to_le16(HostCmd_CMD_MGMT_IE_LIST);
    cmd->size             = sizeof(HostCmd_DS_MGMT_IE_LIST_CFG) + S_DS_GEN;
    cmd->result           = 0;
    pmgmt_ie_list->action = wlan_cpu_to_le16(cmd_action);

    cust_ie                        = (mlan_ds_misc_custom_ie *)pdata_buf;
    pmgmt_ie_list->ds_mgmt_ie.type = wlan_cpu_to_le16(cust_ie->type);
    pmgmt_ie_list->ds_mgmt_ie.len  = wlan_cpu_to_le16(cust_ie->len);

    if (pmgmt_ie_list && cust_ie)
    {
        req_len    = cust_ie->len;
        travel_len = 0;
        /* conversion for index, mask, len */
        if (req_len == sizeof(t_u16))
            cust_ie->ie_data_list[0].ie_index = wlan_cpu_to_le16(cust_ie->ie_data_list[0].ie_index);

        while (req_len > sizeof(t_u16))
        {
            cptr = (custom_ie *)(((t_u8 *)cust_ie->ie_data_list) + travel_len);
            travel_len += cptr->ie_length + sizeof(custom_ie) - MAX_IE_SIZE;
            req_len -= cptr->ie_length + sizeof(custom_ie) - MAX_IE_SIZE;
            cptr->ie_index          = wlan_cpu_to_le16(cptr->ie_index);
            cptr->mgmt_subtype_mask = wlan_cpu_to_le16(cptr->mgmt_subtype_mask);
            cptr->ie_length         = wlan_cpu_to_le16(cptr->ie_length);
        }
        if (cust_ie->len)
            (void)__memcpy(pmpriv->adapter, pmgmt_ie_list->ds_mgmt_ie.ie_data_list, cust_ie->ie_data_list,
                           cust_ie->len);
    }

    cmd->size -= (MAX_MGMT_IE_INDEX_TO_FW * sizeof(custom_ie)) + sizeof(tlvbuf_max_mgmt_ie);
    cmd->size += cust_ie->len;
    cmd->size = wlan_cpu_to_le16(cmd->size);

    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of reg_access.
 *
 *  @param cmd          A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   the action: GET or SET
 *  @param pdata_buf    A pointer to data buffer
 *  @return             MLAN_STATUS_SUCCESS or MLAN_STATUS_FAILURE
 */
/* static */ mlan_status wlan_cmd_reg_access(IN HostCmd_DS_COMMAND *cmd, IN t_u16 cmd_action, IN t_void *pdata_buf)
{
    mlan_ds_reg_rw *reg_rw;

    ENTER();

    reg_rw = (mlan_ds_reg_rw *)pdata_buf;
    switch (cmd->command)
    {
        case HostCmd_CMD_MAC_REG_ACCESS:
        {
            HostCmd_DS_MAC_REG_ACCESS *mac_reg;
            cmd->size       = wlan_cpu_to_le16(sizeof(HostCmd_DS_MAC_REG_ACCESS) + S_DS_GEN);
            mac_reg         = (HostCmd_DS_MAC_REG_ACCESS *)&cmd->params.mac_reg;
            mac_reg->action = wlan_cpu_to_le16(cmd_action);
            mac_reg->offset = wlan_cpu_to_le16((t_u16)reg_rw->offset);
            mac_reg->value  = wlan_cpu_to_le32(reg_rw->value);
            break;
        }
        case HostCmd_CMD_BBP_REG_ACCESS:
        {
            HostCmd_DS_BBP_REG_ACCESS *bbp_reg;
            cmd->size       = wlan_cpu_to_le16(sizeof(HostCmd_DS_BBP_REG_ACCESS) + S_DS_GEN);
            bbp_reg         = (HostCmd_DS_BBP_REG_ACCESS *)&cmd->params.bbp_reg;
            bbp_reg->action = wlan_cpu_to_le16(cmd_action);
            bbp_reg->offset = wlan_cpu_to_le16((t_u16)reg_rw->offset);
            bbp_reg->value  = (t_u8)reg_rw->value;
            break;
        }
        case HostCmd_CMD_RF_REG_ACCESS:
        {
            HostCmd_DS_RF_REG_ACCESS *rf_reg;
            cmd->size      = wlan_cpu_to_le16(sizeof(HostCmd_DS_RF_REG_ACCESS) + S_DS_GEN);
            rf_reg         = (HostCmd_DS_RF_REG_ACCESS *)&cmd->params.rf_reg;
            rf_reg->action = wlan_cpu_to_le16(cmd_action);
            rf_reg->offset = wlan_cpu_to_le16((t_u16)reg_rw->offset);
            rf_reg->value  = (t_u8)reg_rw->value;
            break;
        }
        case HostCmd_CMD_CAU_REG_ACCESS:
        {
            HostCmd_DS_RF_REG_ACCESS *cau_reg;
            cmd->size       = wlan_cpu_to_le16(sizeof(HostCmd_DS_RF_REG_ACCESS) + S_DS_GEN);
            cau_reg         = (HostCmd_DS_RF_REG_ACCESS *)&cmd->params.rf_reg;
            cau_reg->action = wlan_cpu_to_le16(cmd_action);
            cau_reg->offset = wlan_cpu_to_le16((t_u16)reg_rw->offset);
            cau_reg->value  = (t_u8)reg_rw->value;
            break;
        }
        case HostCmd_CMD_802_11_EEPROM_ACCESS:
        {
            mlan_ds_read_eeprom *rd_eeprom              = (mlan_ds_read_eeprom *)pdata_buf;
            HostCmd_DS_802_11_EEPROM_ACCESS *cmd_eeprom = (HostCmd_DS_802_11_EEPROM_ACCESS *)&cmd->params.eeprom;
            cmd->size              = wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_EEPROM_ACCESS) + S_DS_GEN);
            cmd_eeprom->action     = wlan_cpu_to_le16(cmd_action);
            cmd_eeprom->offset     = wlan_cpu_to_le16(rd_eeprom->offset);
            cmd_eeprom->byte_count = wlan_cpu_to_le16(rd_eeprom->byte_count);
            cmd_eeprom->value      = 0;
            break;
        }
        default:
            LEAVE();
            return MLAN_STATUS_FAILURE;
    }
    cmd->command = wlan_cpu_to_le16(cmd->command);

    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of mem_access.
 *
 *  @param cmd          A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   the action: GET or SET
 *  @param pdata_buf    A pointer to data buffer
 *  @return             MLAN_STATUS_SUCCESS
 */
mlan_status wlan_cmd_mem_access(IN HostCmd_DS_COMMAND *cmd, IN t_u16 cmd_action, IN t_void *pdata_buf)
{
    mlan_ds_mem_rw *mem_rw            = (mlan_ds_mem_rw *)pdata_buf;
    HostCmd_DS_MEM_ACCESS *mem_access = (HostCmd_DS_MEM_ACCESS *)&cmd->params.mem;

    ENTER();

    cmd->command = wlan_cpu_to_le16(HostCmd_CMD_MEM_ACCESS);
    cmd->size    = wlan_cpu_to_le16(sizeof(HostCmd_DS_MEM_ACCESS) + S_DS_GEN);

    mem_access->action = wlan_cpu_to_le16(cmd_action);
    mem_access->addr   = wlan_cpu_to_le32(mem_rw->addr);
    mem_access->value  = wlan_cpu_to_le32(mem_rw->value);

    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of auto_reconnect
 *
 *  @param cmd          A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   the action: GET or SET
 *  @param pdata_buf    A pointer to data buffer
 *  @return             MLAN_STATUS_SUCCESS
 */
mlan_status wlan_cmd_auto_reconnect(IN HostCmd_DS_COMMAND *cmd, IN t_u16 cmd_action, IN t_void *pdata_buf)
{
    mlan_ds_auto_reconnect *auto_reconnect = (mlan_ds_auto_reconnect *)pdata_buf;
    HostCmd_DS_AUTO_RECONNECT *auto_reconn = (HostCmd_DS_AUTO_RECONNECT *)&cmd->params.auto_reconnect;

    ENTER();

    cmd->command = wlan_cpu_to_le16(HostCmd_CMD_AUTO_RECONNECT);
    cmd->size    = wlan_cpu_to_le16(sizeof(HostCmd_DS_AUTO_RECONNECT) + S_DS_GEN);

    auto_reconn->action             = wlan_cpu_to_le16(cmd_action);
    auto_reconn->reconnect_counter  = auto_reconnect->reconnect_counter;
    auto_reconn->reconnect_interval = auto_reconnect->reconnect_interval;
    auto_reconn->flags              = wlan_cpu_to_le16(auto_reconnect->flags);

    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

#if 0
/**
 *  @brief This function prepares command of rx management indication
 *
 *  @param cmd          A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   the action: GET or SET
 *  @param pdata_buf    A pointer to data buffer
 *  @return             MLAN_STATUS_SUCCESS
 */
mlan_status wlan_cmd_rx_mgmt_indication(IN pmlan_private pmpriv,
                                        IN HostCmd_DS_COMMAND *cmd,
                                        IN t_u16 cmd_action,
                                        IN t_void *pdata_buf)
{
    mlan_ds_rx_mgmt_indication *rx_mgmt_indication = (mlan_ds_rx_mgmt_indication *)pdata_buf;
    HostCmd_DS_RX_MGMT_IND *rx_mgmt                = (HostCmd_DS_RX_MGMT_IND *)&cmd->params.rx_mgmt_ind;

    ENTER();

    /* Set passthru mask for mgmt frame */
    pmpriv->mgmt_frame_passthru_mask = rx_mgmt_indication->mgmt_subtype_mask;

    cmd->command = wlan_cpu_to_le16(HostCmd_CMD_RX_MGMT_IND);
    cmd->size    = wlan_cpu_to_le16(sizeof(HostCmd_DS_RX_MGMT_IND) + S_DS_GEN);

    rx_mgmt->action            = wlan_cpu_to_le16(cmd_action);
    rx_mgmt->mgmt_subtype_mask = wlan_cpu_to_le32(rx_mgmt_indication->mgmt_subtype_mask);

    LEAVE();
    return MLAN_STATUS_SUCCESS;
}
#endif

/**
 *  @brief This function prepares command of OTP user data.
 *
 *  @param pmpriv    	A pointer to mlan_private structure
 *  @param cmd          A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   the action: GET or SET
 *  @param pdata_buf    A pointer to data buffer
 *  @return             MLAN_STATUS_SUCCESS
 */
static mlan_status wlan_cmd_otp_user_data(IN pmlan_private pmpriv,
                                          IN HostCmd_DS_COMMAND *cmd,
                                          IN t_u16 cmd_action,
                                          IN t_void *pdata_buf)
{
    mlan_ds_misc_otp_user_data *user_data   = (mlan_ds_misc_otp_user_data *)pdata_buf;
    HostCmd_DS_OTP_USER_DATA *cmd_user_data = (HostCmd_DS_OTP_USER_DATA *)&cmd->params.otp_user_data;
    t_u16 cmd_size                          = 0;

    ENTER();

    cmd->command = wlan_cpu_to_le16(HostCmd_CMD_OTP_READ_USER_DATA);
    cmd_size     = sizeof(HostCmd_DS_OTP_USER_DATA) + S_DS_GEN - 1;

    cmd_user_data->action           = wlan_cpu_to_le16(cmd_action);
    cmd_user_data->reserved         = 0;
    cmd_user_data->user_data_length = wlan_cpu_to_le16(user_data->user_data_length);
    /* wmsdk: below change is added in order to count user_data_length size
     * for SET/Write operation only, in case GET/Read it is not required
     * (SDIO cmd size remains same).
     */
    if (cmd_action == HostCmd_ACT_GEN_SET)
        cmd_size += user_data->user_data_length;
    cmd->size = wlan_cpu_to_le16(cmd_size);

    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/********************************************************
                Global Functions
********************************************************/

/**
 *  @brief This function prepare the command before sending to firmware.
 *
 *  @param priv       A pointer to mlan_private structure
 *  @param cmd_no       Command number
 *  @param cmd_action   Command action: GET or SET
 *  @param cmd_oid      Cmd oid: treated as sub command
 *  @param pioctl_buf   A pointer to MLAN IOCTL Request buffer
 *  @param pdata_buf    A pointer to information buffer
 *  @param pcmd_buf      A pointer to cmd buf
 *
 *  @return             MLAN_STATUS_SUCCESS or MLAN_STATUS_FAILURE
 */
mlan_status wlan_ops_sta_prepare_cmd(IN t_void *priv,
                                     IN t_u16 cmd_no,
                                     IN t_u16 cmd_action,
                                     IN t_u32 cmd_oid,
                                     IN t_void *pioctl_buf,
                                     IN t_void *pdata_buf,
                                     IN t_void *pcmd_buf)
{
    HostCmd_DS_COMMAND *cmd_ptr = (HostCmd_DS_COMMAND *)pcmd_buf;
    mlan_private *pmpriv        = (mlan_private *)priv;
    mlan_status ret             = MLAN_STATUS_SUCCESS;

    ENTER();

    /* Prepare command */
    switch (cmd_no)
    {
        case HostCmd_CMD_MAC_CONTROL:
            ret = wlan_cmd_mac_control(pmpriv, cmd_ptr, cmd_action, pdata_buf);
            break;
        case HostCmd_CMD_802_11_MAC_ADDRESS:
            ret = wlan_cmd_802_11_mac_address(pmpriv, cmd_ptr, cmd_action, pdata_buf);
            break;
        case HostCmd_CMD_MAC_MULTICAST_ADR:
            ret = wlan_cmd_mac_multicast_adr(pmpriv, cmd_ptr, cmd_action, pdata_buf);
            break;
        case HostCmd_CMD_TX_RATE_CFG:
            ret = wlan_cmd_tx_rate_cfg(pmpriv, cmd_ptr, cmd_action, pdata_buf);
            break;
        case HostCmd_CMD_802_11_RF_ANTENNA:
            ret = wlan_cmd_802_11_rf_antenna(pmpriv, cmd_ptr, cmd_action, pdata_buf);
            break;
        case HostCmd_CMD_TXPWR_CFG:
            ret = wlan_cmd_tx_power_cfg(pmpriv, cmd_ptr, cmd_action, pdata_buf);
            break;
        case HostCmd_CMD_802_11_RF_TX_POWER:
            ret = wlan_cmd_802_11_rf_tx_power(pmpriv, cmd_ptr, cmd_action, pdata_buf);
            break;
        case HostCmd_CMD_802_11_HS_CFG_ENH:
            ret = wlan_cmd_802_11_hs_cfg(pmpriv, cmd_ptr, cmd_action, (hs_config_param *)pdata_buf);
            break;
        case HostCmd_CMD_802_11_SCAN:
            ret = wlan_cmd_802_11_scan(pmpriv, cmd_ptr, pdata_buf);
            break;
        case HostCmd_CMD_802_11_ASSOCIATE:
            ret = wlan_cmd_802_11_associate(pmpriv, cmd_ptr, pdata_buf);
            break;
        case HostCmd_CMD_802_11_GET_LOG:
            ret = wlan_cmd_802_11_get_log(pmpriv, cmd_ptr);
            break;
        case HostCmd_CMD_RSSI_INFO:
            ret = wlan_cmd_802_11_rssi_info(pmpriv, cmd_ptr, cmd_action);
            break;
        case HostCmd_CMD_802_11_SNMP_MIB:
            ret = wlan_cmd_802_11_snmp_mib(pmpriv, cmd_ptr, cmd_action, cmd_oid, pdata_buf);
            break;
        case HostCmd_CMD_802_11_TX_RATE_QUERY:
            cmd_ptr->command = wlan_cpu_to_le16(HostCmd_CMD_802_11_TX_RATE_QUERY);
            cmd_ptr->size    = wlan_cpu_to_le16(sizeof(HostCmd_TX_RATE_QUERY) + S_DS_GEN);
            pmpriv->tx_rate  = 0;
            ret              = MLAN_STATUS_SUCCESS;
            break;
        case HostCmd_CMD_TBTT_OFFSET:
            cmd_ptr->command                   = wlan_cpu_to_le16(HostCmd_CMD_TBTT_OFFSET);
            cmd_ptr->size                      = wlan_cpu_to_le16(S_DS_GEN + sizeof(t_u16));
            cmd_ptr->params.tbtt_offset.action = HostCmd_ACT_GEN_GET;
            ret                                = MLAN_STATUS_SUCCESS;
            break;
        case HostCmd_CMD_VERSION_EXT:
            (void)__memset(pmpriv->adapter, cmd_ptr, 0x00, sizeof(HostCmd_DS_COMMAND));
            cmd_ptr->command                       = wlan_cpu_to_le16(cmd_no);
            cmd_ptr->params.verext.version_str_sel = *(t_u8 *)pdata_buf;
            cmd_ptr->size                          = wlan_cpu_to_le16(sizeof(HostCmd_DS_VERSION_EXT) + S_DS_GEN);
            ret                                    = MLAN_STATUS_SUCCESS;
            break;
        case HostCmd_CMD_802_11_RF_CHANNEL:
            ret = wlan_cmd_802_11_rf_channel(pmpriv, cmd_ptr, cmd_action, pdata_buf);
            break;
        case HostCmd_CMD_11N_ADDBA_REQ:
            ret = wlan_cmd_11n_addba_req(pmpriv, cmd_ptr, pdata_buf);
            break;
        case HostCmd_CMD_11N_DELBA:
            ret = wlan_cmd_11n_delba(pmpriv, cmd_ptr, pdata_buf);
            break;
        case HostCmd_CMD_11N_ADDBA_RSP:
            ret = wlan_cmd_11n_addba_rspgen(pmpriv, cmd_ptr, pdata_buf);
            break;
        case HostCmd_CMD_802_11_KEY_MATERIAL:
            ret = wlan_cmd_802_11_key_material(pmpriv, cmd_ptr, cmd_action, cmd_oid, pdata_buf);
            break;
        case HostCmd_CMD_SUPPLICANT_PMK:
            ret = wlan_cmd_802_11_supplicant_pmk(pmpriv, cmd_ptr, cmd_action, pdata_buf);
            break;
        case HostCmd_CMD_802_11D_DOMAIN_INFO:
            if (pmpriv->support_11d_APIs)
                ret = pmpriv->support_11d_APIs->wlan_cmd_802_11d_domain_info_p(pmpriv, cmd_ptr, cmd_action);
            break;
        case HostCmd_CMD_11N_CFG:
            ret = wlan_cmd_11n_cfg(pmpriv, cmd_ptr, cmd_action, pdata_buf);
            break;
        case HostCmd_CMD_11AC_CFG:
            ret = wlan_cmd_11ac_cfg(pmpriv, cmd_ptr, cmd_action, pdata_buf);
            break;
        case HostCmd_CMD_MGMT_IE_LIST:
            ret = wlan_cmd_mgmt_ie_list(pmpriv, cmd_ptr, cmd_action, pdata_buf);
            break;
        case HostCmd_CMD_802_11_REMAIN_ON_CHANNEL:
            ret = wlan_cmd_remain_on_channel(pmpriv, cmd_ptr, cmd_action, pdata_buf);
            break;
        case HostCmd_CMD_OTP_READ_USER_DATA:
            ret = wlan_cmd_otp_user_data(pmpriv, cmd_ptr, cmd_action, pdata_buf);
            break;
        case HostCmd_CMD_GET_TSF:
            ret = wlan_cmd_get_tsf(pmpriv, cmd_ptr, cmd_action);
            break;
#ifdef CONFIG_RF_TEST_MODE
        case HostCmd_CMD_MFG_COMMAND:
            ret = wlan_cmd_mfg(pmpriv, cmd_ptr, cmd_action, pdata_buf);
            break;
#endif
        default:
            PRINTM(MERROR, "PREP_CMD: unknown command- %#x\n", cmd_no);
            ret = MLAN_STATUS_FAILURE;
            break;
    }

    LEAVE();
    return ret;
}
