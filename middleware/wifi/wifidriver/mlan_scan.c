/** @file mlan_scan.c
 *
 *  @brief  This file provides wlan scan IOCTL and firmware command APIs
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
    10/28/2008: initial version
******************************************************/
#include <mlan_api.h>

/* Additional WMSDK header files */
#include <wmerrno.h>
#include <wm_os.h>

/* Always keep this include at the end of all include files */
#include <mlan_remap_mem_operations.h>
/********************************************************
                Local Constants
********************************************************/
int get_split_scan_delay_ms(void);

/** The maximum number of channels the firmware can scan per command */
#define MRVDRV_MAX_CHANNELS_PER_SPECIFIC_SCAN 3

/**
 * Number of channels to scan per firmware scan command issuance.
 *
 * Number restricted to prevent hitting the limit on the amount of scan data
 * returned in a single firmware scan command.
 */
#define MRVDRV_CHANNELS_PER_SCAN_CMD 4

/** Memory needed to store a max sized Channel List TLV for a firmware scan */
#define CHAN_TLV_MAX_SIZE \
    (sizeof(MrvlIEtypesHeader_t) + (MRVDRV_MAX_CHANNELS_PER_SPECIFIC_SCAN * sizeof(ChanScanParamSet_t)))

/** Memory needed to store supported rate */
#define RATE_TLV_MAX_SIZE (sizeof(MrvlIEtypes_RatesParamSet_t) + HOSTCMD_SUPPORTED_RATES)

/** Memory needed to store a max number/size WildCard SSID TLV for a firmware scan */
#define WILDCARD_SSID_TLV_MAX_SIZE \
    (MRVDRV_MAX_SSID_LIST_LENGTH * (sizeof(MrvlIEtypes_WildCardSsIdParamSet_t) + MRVDRV_MAX_SSID_LENGTH))

/** WPS TLV MAX size is MAX IE size plus 2 bytes for t_u16 MRVL TLV extension */
#define WPS_TLV_MAX_SIZE (sizeof(IEEEtypes_VendorSpecific_t) + 2)
/** Maximum memory needed for a wlan_scan_cmd_config with all TLVs at max */
#define MAX_SCAN_CFG_ALLOC                                                                          \
    (sizeof(wlan_scan_cmd_config) + sizeof(MrvlIEtypes_NumProbes_t) + sizeof(MrvlIETypes_HTCap_t) + \
     CHAN_TLV_MAX_SIZE + RATE_TLV_MAX_SIZE + WILDCARD_SSID_TLV_MAX_SIZE + WPS_TLV_MAX_SIZE)

/********************************************************
                Local Variables
********************************************************/

/* Global data required for split scan requests */
static bool split_scan_in_progress, abort_split_scan;

/**
 * Interally used to send a configured scan cmd between driver routines
 */
typedef union
{
    /** Scan configuration (variable length) */
    wlan_scan_cmd_config config;
    /** Max allocated block */
    t_u8 config_alloc_buf[MAX_SCAN_CFG_ALLOC];
} wlan_scan_cmd_config_tlv;

/********************************************************
                Global Variables
********************************************************/

/********************************************************
                Local Functions
********************************************************/
/** Cipher suite definition */
enum cipher_suite
{
    CIPHER_SUITE_TKIP,
    CIPHER_SUITE_CCMP,
    CIPHER_SUITE_MAX
};

static t_u8 wpa_oui[CIPHER_SUITE_MAX][4] = {
    {0x00, 0x50, 0xf2, 0x02}, /* TKIP */
    {0x00, 0x50, 0xf2, 0x04}, /* AES */
};

static t_u8 rsn_oui[CIPHER_SUITE_MAX][4] = {
    {0x00, 0x0f, 0xac, 0x02}, /* TKIP */
    {0x00, 0x0f, 0xac, 0x04}, /* AES */
};

static t_s32 wlan_find_worst_network_in_list(const BSSDescriptor_t *pbss_desc, t_u32 num_entries);

bool is_split_scan_complete()
{
    return (split_scan_in_progress == false);
}

/*
 * wmsdk: Split scan needs to be aborted at times by the application. This
 * API will help the caller do that.
 */
void wlan_abort_split_scan()
{
    if (split_scan_in_progress)
    {
        abort_split_scan = true;
    }
}

/**
 *  @brief This function will parse a given IE for a given OUI
 *
 *  Parse a given WPA/RSN IE to find if it has a given oui in PTK,
 *  if no OUI found for PTK it returns 0.
 *
 *  @param pbss_desc       A pointer to current BSS descriptor
 *  @return                0 on failure to find OUI, 1 on success.
 */
static t_u8 search_oui_in_ie(mlan_adapter *pmadapter, IEBody *ie_body, t_u8 *oui)
{
    t_u8 count;

    count = ie_body->PtkCnt[0];

    ENTER();
    /* There could be multiple OUIs for PTK hence 1) Take the length. 2) Check
       all the OUIs for AES. 3) If one of them is AES then pass success. */
    while (count)
    {
        if (!memcmp(pmadapter, ie_body->PtkBody, oui, sizeof(ie_body->PtkBody)))
        {
            LEAVE();
            return MLAN_OUI_PRESENT;
        }

        --count;
        if (count)
        {
            ie_body = (IEBody *)((t_u8 *)ie_body + sizeof(ie_body->PtkBody));
        }
    }

    PRINTM(MINFO, "The OUI %x:%x:%x:%x is not found in PTK \n", oui[0], oui[1], oui[2], oui[3]);
    LEAVE();
    return MLAN_OUI_NOT_PRESENT;
}

/**
 *  @brief This function will pass the correct ie and oui to search_oui_in_ie
 *
 *  Check the pbss_desc for appropriate IE and then check if RSN IE has AES
 *  OUI in it. If RSN IE does not have AES in PTK then return 0;
 *
 *  @param pbss_desc       A pointer to current BSS descriptor
 *  @return                0 on failure to find AES OUI, 1 on success.
 */
static t_u8 is_rsn_oui_present(mlan_adapter *pmadapter, BSSDescriptor_t *pbss_desc, t_u32 cipher_suite)
{
    t_u8 *oui       = MNULL;
    IEBody *ie_body = MNULL;
    t_u8 ret        = MLAN_OUI_NOT_PRESENT;

    ENTER();
    if (((pbss_desc->prsn_ie) && ((*(pbss_desc->prsn_ie)).ieee_hdr.element_id == RSN_IE)))
    {
        ie_body = (IEBody *)(((t_u8 *)pbss_desc->prsn_ie->data) + RSN_GTK_OUI_OFFSET);
        oui     = &rsn_oui[cipher_suite][0];
        if ((ret = search_oui_in_ie(pmadapter, ie_body, oui)) != 0U)
        {
            LEAVE();
            return ret;
        }
    }
    LEAVE();
    return ret;
}

/**
 *  @brief This function will pass the correct ie and oui to search_oui_in_ie
 *
 *  Check the pbss_desc for appropriate IE and then check if WPA IE has AES
 *  OUI in it. If WPA IE does not have AES in PTK then return 0;
 *
 *  @param pbss_desc       A pointer to current BSS descriptor
 *  @return                0 on failure to find AES OUI, 1 on success.
 */
static t_u8 is_wpa_oui_present(mlan_adapter *pmadapter, BSSDescriptor_t *pbss_desc, t_u32 cipher_suite)
{
    t_u8 *oui       = MNULL;
    IEBody *ie_body = MNULL;
    t_u8 ret        = MLAN_OUI_NOT_PRESENT;

    ENTER();
    if (((pbss_desc->pwpa_ie) && ((*(pbss_desc->pwpa_ie)).vend_hdr.element_id == WPA_IE)))
    {
        ie_body = (IEBody *)pbss_desc->pwpa_ie->data;
        oui     = &wpa_oui[cipher_suite][0];
        if ((ret = search_oui_in_ie(pmadapter, ie_body, oui)) != 0U)
        {
            LEAVE();
            return ret;
        }
    }
    LEAVE();
    return ret;
}

/**
 *  @brief Convert radio type scan parameter to a band config used in join cmd
 *
 *  @param radio_type Scan parameter indicating the radio used for a channel
 *                    in a scan command.
 *
 *  @return          Band type conversion of scanBand used in join/assoc cmds
 *
 */
static t_u8 radio_type_to_band(t_u8 radio_type)
{
    t_u8 ret_band;

    switch (radio_type)
    {
        case HostCmd_SCAN_RADIO_TYPE_A:
            ret_band = BAND_A;
            break;
        case HostCmd_SCAN_RADIO_TYPE_BG:
        default:
            ret_band = BAND_G;
            break;
    }

    return ret_band;
}

/**
 *  @brief compare config band and a band from the scan result,
 *  which is defined by functiion radio_type_to_band(t_u8 radio_type) above
 *
 *  @param cfg_band:  band configured
 *         scan_band: band from scan result
 *
 *  @return  matched: non-zero. unmatched: 0
 *
 */
static t_u8 wlan_is_band_compatible(t_u8 cfg_band, t_u8 scan_band)
{
    t_u8 band;
    switch (scan_band)
    {
        case BAND_A:
            band = BAND_A | BAND_AN | BAND_AAC;
            break;
        case BAND_G:
        default:
            band = BAND_B | BAND_G | BAND_GN | BAND_GAC;
    }
    return cfg_band & band;
}

/**
 *  @brief Create a channel list for the driver to scan based on region info
 *
 *  Use the driver region/band information to construct a comprehensive list
 *    of channels to scan.  This routine is used for any scan that is not
 *    provided a specific channel list to scan.
 *
 *  @param pmpriv           A pointer to mlan_private structure
 *  @param puser_scan_in    MNULL or pointer to scan configuration parameters
 *  @param pscan_chan_list  Output parameter: Resulting channel list to scan
 *  @param filtered_scan    Flag indicating whether or not a BSSID or SSID filter
 *                          is being sent in the command to firmware.  Used to
 *                          increase the number of channels sent in a scan
 *                          command and to disable the firmware channel scan
 *                          filter.
 *
 *  @return                 N/A
 */
static t_void wlan_scan_create_channel_list(IN mlan_private *pmpriv,
                                            IN const wlan_user_scan_cfg *puser_scan_in,
                                            OUT ChanScanParamSet_t *pscan_chan_list,
                                            IN t_u8 filtered_scan)
{
    mlan_adapter *pmadapter = pmpriv->adapter;
    region_chan_t *pscan_region;
    chan_freq_power_t *cfp;
    t_u32 region_idx;
    t_u32 chan_idx = 0;
    t_u32 next_chan;
    t_u8 scan_type;
    t_u8 radio_type;

    ENTER();

    for (region_idx = 0; region_idx < NELEMENTS(pmadapter->region_channel); region_idx++)
    {
        if (wlan_11d_support_is_enabled(pmpriv) && wlan_11d_is_enabled(pmpriv) && pmpriv->media_connected != MTRUE)
        {
            /* Scan all the supported chan for the first scan */
            if (!pmadapter->universal_channel[region_idx].valid)
                continue;
            pscan_region = &pmadapter->universal_channel[region_idx];
        }
        else
        {
            if (!pmadapter->region_channel[region_idx].valid)
                continue;
            pscan_region = &pmadapter->region_channel[region_idx];
        }

        if (puser_scan_in && !puser_scan_in->chan_list[0].chan_number &&
            puser_scan_in->chan_list[0].radio_type & BAND_SPECIFIED)
        {
            radio_type = puser_scan_in->chan_list[0].radio_type & ~BAND_SPECIFIED;
            if (!radio_type && (pscan_region->band != BAND_B) && (pscan_region->band != BAND_G))
                continue;
            if (radio_type && (pscan_region->band != BAND_A))
                continue;
        }
        if (!wlan_is_band_compatible(pmpriv->config_bands, pscan_region->band))
            continue;
        for (next_chan = 0; next_chan < pscan_region->num_cfp; next_chan++)
        {
            /* Set the default scan type to the user specified type, will later
               be changed to passive on a per channel basis if restricted by
               regulatory requirements (11d or 11h) */
            scan_type = pmadapter->scan_type;
            cfp       = pscan_region->pcfp + next_chan;
            if ((cfp->dynamic.flags & NXP_CHANNEL_DISABLED) != 0U)
                continue;

            if (scan_type == MLAN_SCAN_TYPE_ACTIVE && wlan_11d_support_is_enabled(pmpriv))
            {
                scan_type = wlan_11d_get_scan_type(pmpriv, pscan_region->band, (t_u8)cfp->channel,
                                                   &pmadapter->parsed_region_chan);
            }

            switch (pscan_region->band)
            {
#ifdef CONFIG_5GHz_SUPPORT
                case BAND_A:
                    pscan_chan_list[chan_idx].radio_type = HostCmd_SCAN_RADIO_TYPE_A;
                    if (!wlan_11d_is_enabled(pmpriv))
                    {
                        /* 11D not available... play it safe on DFS channels */
                        if (wlan_11h_radar_detect_required(pmpriv, (t_u8)cfp->channel))
                        {
                            scan_type = MLAN_SCAN_TYPE_PASSIVE;
                        }
                    }
                    break;
#endif
                case BAND_B:
                case BAND_G:
                    if (wlan_bg_scan_type_is_passive(pmpriv, (t_u8)cfp->channel))
                    {
                        scan_type = MLAN_SCAN_TYPE_PASSIVE;
                    }
                default:
                    pscan_chan_list[chan_idx].radio_type = HostCmd_SCAN_RADIO_TYPE_BG;
                    break;
            }

            if (puser_scan_in && puser_scan_in->chan_list[0].scan_time)
            {
                pscan_chan_list[chan_idx].max_scan_time =
                    wlan_cpu_to_le16((t_u16)puser_scan_in->chan_list[0].scan_time);
            }
            else if (scan_type == MLAN_SCAN_TYPE_PASSIVE)
            {
                pscan_chan_list[chan_idx].max_scan_time = wlan_cpu_to_le16(pmadapter->passive_scan_time);
            }
            else if (filtered_scan != 0U)
            {
                pscan_chan_list[chan_idx].max_scan_time = wlan_cpu_to_le16(pmadapter->specific_scan_time);
            }
            else
            {
                pscan_chan_list[chan_idx].max_scan_time = wlan_cpu_to_le16(pmadapter->active_scan_time);
            }

            if (scan_type == MLAN_SCAN_TYPE_PASSIVE)
            {
                pscan_chan_list[chan_idx].chan_scan_mode.passive_scan       = MTRUE;
                pscan_chan_list[chan_idx].chan_scan_mode.hidden_ssid_report = MTRUE;
            }
            else
            {
                pscan_chan_list[chan_idx].chan_scan_mode.passive_scan = MFALSE;
            }

            pscan_chan_list[chan_idx].chan_number = (t_u8)cfp->channel;

            wscan_d("Channel: %d Type: %s %d", cfp->channel, scan_type == MLAN_SCAN_TYPE_PASSIVE ? "Passive" : "Active",
                    cfp->max_tx_power);
            chan_idx++;

            if (filtered_scan != 0U)
            {
                pscan_chan_list[chan_idx].chan_scan_mode.disable_chan_filt = MTRUE;
            }
        }
    }

    LEAVE();
}

/**
 *  @brief Construct and send multiple scan config commands to the firmware
 *
 *  Previous routines have created a wlan_scan_cmd_config with any requested
 *   TLVs.  This function splits the channel TLV into max_chan_per_scan lists
 *   and sends the portion of the channel TLV along with the other TLVs
 *   to the wlan_cmd routines for execution in the firmware.
 *
 *  @param pmpriv             A pointer to mlan_private structure
 *  @param pioctl_buf         A pointer to MLAN IOCTL Request buffer
 *  @param max_chan_per_scan  Maximum number channels to be included in each
 *                            scan command sent to firmware
 *  @param filtered_scan      Flag indicating whether or not a BSSID or SSID
 *                            filter is being used for the firmware command
 *                            scan command sent to firmware
 *  @param pscan_cfg_out      Scan configuration used for this scan.
 *  @param pchan_tlv_out      Pointer in the pscan_cfg_out where the channel TLV
 *                            should start.  This is past any other TLVs that
 *                            must be sent down in each firmware command.
 *  @param pscan_chan_list    List of channels to scan in max_chan_per_scan segments
 *
 *  @return                   MLAN_STATUS_SUCCESS or error return otherwise
 */
static mlan_status wlan_scan_channel_list(IN mlan_private *pmpriv,
                                          IN t_void *pioctl_buf,
                                          IN t_u32 max_chan_per_scan,
                                          IN t_u8 filtered_scan,
                                          OUT wlan_scan_cmd_config *pscan_cfg_out,
                                          OUT MrvlIEtypes_ChanListParamSet_t *pchan_tlv_out,
                                          IN ChanScanParamSet_t *pscan_chan_list)
{
    mlan_status ret         = MLAN_STATUS_SUCCESS;
    mlan_adapter *pmadapter = pmpriv->adapter;
    ChanScanParamSet_t *ptmp_chan_list;
    ChanScanParamSet_t *pstart_chan;
    pmlan_ioctl_req pioctl_req = (mlan_ioctl_req *)pioctl_buf;

    t_u32 tlv_idx;
    t_u32 total_scan_time;
    t_u32 done_early;
    t_u32 cmd_no;

    ENTER();

    if (!pscan_cfg_out || !pchan_tlv_out || !pscan_chan_list)
    {
        PRINTM(MINFO, "Scan: Null detect: %p, %p, %p\n", pscan_cfg_out, pchan_tlv_out, pscan_chan_list);
        if (pioctl_req)
            pioctl_req->status_code = MLAN_ERROR_CMD_SCAN_FAIL;
        LEAVE();
        return MLAN_STATUS_FAILURE;
    }
    if (!pscan_chan_list->chan_number)
    {
        PRINTM(MERROR, "Scan: No channel configured\n");
        if (pioctl_req)
            pioctl_req->status_code = MLAN_ERROR_CMD_SCAN_FAIL;
        LEAVE();
        return MLAN_STATUS_FAILURE;
    }

    pchan_tlv_out->header.type = wlan_cpu_to_le16(TLV_TYPE_CHANLIST);

    /* Set the temp channel struct pointer to the start of the desired list */
    ptmp_chan_list = pscan_chan_list;

    /* Loop through the desired channel list, sending a new firmware scan
       commands for each max_chan_per_scan channels (or for 1,6,11 individually
       if configured accordingly) */
    while (ptmp_chan_list->chan_number)
    {
        tlv_idx                   = 0;
        total_scan_time           = 0;
        pchan_tlv_out->header.len = 0;
        pstart_chan               = ptmp_chan_list;
        done_early                = MFALSE;

        /*
         * Construct the Channel TLV for the scan command.  Continue to
         * insert channel TLVs until:
         *   - the tlv_idx hits the maximum configured per scan command
         *   - the next channel to insert is 0 (end of desired channel list)
         *   - done_early is set (controlling individual scanning of 1,6,11)
         */
        while (tlv_idx < max_chan_per_scan && ptmp_chan_list->chan_number && !done_early)
        {
            wscan_d("Scan: Chan(%3d), Radio(%d), Mode(%d,%d), Dur(%d)", ptmp_chan_list->chan_number,
                    ptmp_chan_list->radio_type, ptmp_chan_list->chan_scan_mode.passive_scan,
                    ptmp_chan_list->chan_scan_mode.disable_chan_filt, wlan_le16_to_cpu(ptmp_chan_list->max_scan_time));

            /* Copy the current channel TLV to the command being prepared */
            (void)__memcpy(pmadapter, pchan_tlv_out->chan_scan_param + tlv_idx, ptmp_chan_list,
                           sizeof(pchan_tlv_out->chan_scan_param));

            /* Increment the TLV header length by the size appended */
            pchan_tlv_out->header.len += sizeof(pchan_tlv_out->chan_scan_param);

            /*
             * The tlv buffer length is set to the number of bytes of the
             *   between the channel tlv pointer and the start of the
             *   tlv buffer.  This compensates for any TLVs that were appended
             *   before the channel list.
             */
            pscan_cfg_out->tlv_buf_len = (t_u32)((t_u8 *)pchan_tlv_out - pscan_cfg_out->tlv_buf);

            /* Add the size of the channel tlv header and the data length */
            pscan_cfg_out->tlv_buf_len += (sizeof(pchan_tlv_out->header) + pchan_tlv_out->header.len);

            /* Increment the index to the channel tlv we are constructing */
            tlv_idx++;

            /* Count the total scan time per command */
            total_scan_time += wlan_le16_to_cpu(ptmp_chan_list->max_scan_time);

            done_early = MFALSE;

            /* Stop the loop if the *current* channel is in the 1,6,11 set and
               we are not filtering on a BSSID or SSID. */
            if (!filtered_scan && (ptmp_chan_list->chan_number == 1 || ptmp_chan_list->chan_number == 6 ||
                                   ptmp_chan_list->chan_number == 11))
            {
                done_early = MTRUE;
            }

            /* Increment the tmp pointer to the next channel to be scanned */
            ptmp_chan_list++;

            /* Stop the loop if the *next* channel is in the 1,6,11 set.  This
               will cause it to be the only channel scanned on the next
               interation */
            if (!filtered_scan && (ptmp_chan_list->chan_number == 1 || ptmp_chan_list->chan_number == 6 ||
                                   ptmp_chan_list->chan_number == 11))
            {
                done_early = MTRUE;
            }
        }

        /* The total scan time should be less than scan command timeout value */
        if (total_scan_time > MRVDRV_MAX_TOTAL_SCAN_TIME)
        {
            wscan_d("Total scan time %d ms is over limit (%d ms), scan skipped", total_scan_time,
                    MRVDRV_MAX_TOTAL_SCAN_TIME);
            if (pioctl_req)
                pioctl_req->status_code = MLAN_ERROR_CMD_SCAN_FAIL;
            ret = MLAN_STATUS_FAILURE;
            break;
        }

        pchan_tlv_out->header.len = wlan_cpu_to_le16(pchan_tlv_out->header.len);

        pmadapter->pscan_channels = pstart_chan;

        if (!ptmp_chan_list->chan_number)
        {
            /* wmsdk: Once we set this the response handling code can
               send event to the WLC manager. Since the event is send
               only after command response we can be sure that there
               is no race condition */
            split_scan_in_progress = false;
        }

        /* Send the scan command to the firmware with the specified cfg */
        cmd_no = HostCmd_CMD_802_11_SCAN;
        ret    = wlan_prepare_cmd(pmpriv, cmd_no, HostCmd_ACT_GEN_SET, 0, pioctl_buf, pscan_cfg_out);
        if (ret)
            break;

        /* This delay helps the UAP send beacons and avoids clients from
           disconnecting from the UAP. Issue was observed on Windows */
        /* fixme: Should this delay be conditional on UAP active? */
        os_thread_sleep(os_msec_to_ticks(get_split_scan_delay_ms()));
        if (abort_split_scan)
        {
            abort_split_scan       = false;
            split_scan_in_progress = false;
            break;
        }
    }

    LEAVE();

    if (ret)
    {
        return MLAN_STATUS_FAILURE;
    }

    return MLAN_STATUS_SUCCESS;
}

/**
 *  @brief Construct a wlan_scan_cmd_config structure to use in scan commands
 *
 *  Application layer or other functions can invoke wlan_scan_networks
 *    with a scan configuration supplied in a wlan_ioctl_user_scan_cfg struct.
 *    This structure is used as the basis of one or many wlan_scan_cmd_config
 *    commands that are sent to the command processing module and sent to
 *    firmware.
 *
 *  Create a wlan_scan_cmd_config based on the following user supplied
 *    parameters (if present):
 *             - SSID filter
 *             - BSSID filter
 *             - Number of Probes to be sent
 *             - Channel list
 *
 *  If the SSID or BSSID filter is not present, disable/clear the filter.
 *  If the number of probes is not set, use the adapter default setting
 *  Qualify the channel
 *
 *  @param pmpriv              A pointer to mlan_private structure
 *  @param puser_scan_in       MNULL or pointer to scan config parameters
 *  @param pscan_cfg_out       Output parameter: Resulting scan configuration
 *  @param ppchan_list_out     Output parameter: Pointer to the start of the
 *                             channel TLV portion of the output scan config
 *  @param pscan_chan_list     Output parameter: Pointer to the resulting
 *                             channel list to scan
 *  @param pmax_chan_per_scan  Output parameter: Number of channels to scan for
 *                             each issuance of the firmware scan command
 *  @param pfiltered_scan      Output parameter: Flag indicating whether or not
 *                             a BSSID or SSID filter is being sent in the
 *                             command to firmware. Used to increase the number
 *                             of channels sent in a scan command and to
 *                             disable the firmware channel scan filter.
 *  @param pscan_current_only  Output parameter: Flag indicating whether or not
 *                             we are only scanning our current active channel
 *
 *  @return                 MLAN_STATUS_SUCCESS or MLAN_STATUS_FAILURE
 */
static mlan_status wlan_scan_setup_scan_config(IN mlan_private *pmpriv,
                                               IN const wlan_user_scan_cfg *puser_scan_in,
                                               OUT wlan_scan_cmd_config *pscan_cfg_out,
                                               OUT MrvlIEtypes_ChanListParamSet_t **ppchan_list_out,
                                               OUT ChanScanParamSet_t *pscan_chan_list,
                                               OUT t_u8 *pmax_chan_per_scan,
                                               OUT t_u8 *pfiltered_scan,
                                               OUT t_u8 *pscan_current_only)
{
    mlan_adapter *pmadapter = pmpriv->adapter;
    mlan_status ret         = MLAN_STATUS_SUCCESS;
    MrvlIEtypes_NumProbes_t *pnum_probes_tlv;
    MrvlIEtypes_WildCardSsIdParamSet_t *pwildcard_ssid_tlv;
    MrvlIEtypes_RatesParamSet_t *prates_tlv;
    const t_u8 zero_mac[MLAN_MAC_ADDR_LENGTH] = {0, 0, 0, 0, 0, 0};
    t_u8 *ptlv_pos;
    t_u32 num_probes;
    t_u32 ssid_len;
    t_u32 chan_idx;
    t_u32 scan_type;
    t_u16 scan_dur;
    t_u8 channel;
    t_u8 radio_type;
    t_u32 ssid_idx;
    t_u8 ssid_filter;
    WLAN_802_11_RATES rates;
    t_u32 rates_size;
    MrvlIETypes_HTCap_t *pht_cap;
    MrvlIETypes_VHTCap_t *pvht_cap;

    ENTER();

    /* The tlv_buf_len is calculated for each scan command.  The TLVs added in
       this routine will be preserved since the routine that sends the command
       will append channelTLVs at *ppchan_list_out.  The difference between the
       *ppchan_list_out and the tlv_buf start will be used to calculate the
       size of anything we add in this routine. */
    pscan_cfg_out->tlv_buf_len = 0;

    /* Running tlv pointer.  Assigned to ppchan_list_out at end of function so
       later routines know where channels can be added to the command buf */
    ptlv_pos = pscan_cfg_out->tlv_buf;

    /* Initialize the scan as un-filtered; the flag is later set to TRUE below
       if a SSID or BSSID filter is sent in the command */
    *pfiltered_scan = MFALSE;

    /* Initialize the scan as not being only on the current channel.  If the
       channel list is customized, only contains one channel, and is the active
       channel, this is set true and data flow is not halted. */
    *pscan_current_only = MFALSE;

    if (puser_scan_in)
    {
        ssid_filter = MFALSE;

        /* Set the bss type scan filter, use Adapter setting if unset */
        pscan_cfg_out->bss_mode =
            (puser_scan_in->bss_mode ? (t_u8)puser_scan_in->bss_mode : (t_u8)pmadapter->scan_mode);

        /* Set the number of probes to send, use Adapter setting if unset */
        num_probes = (puser_scan_in->num_probes ? puser_scan_in->num_probes : pmadapter->scan_probes);
        /*
         * Set the BSSID filter to the incoming configuration,
         *   if non-zero.  If not set, it will remain disabled (all zeros).
         */
        (void)__memcpy(pmadapter, pscan_cfg_out->specific_bssid, puser_scan_in->specific_bssid,
                       sizeof(pscan_cfg_out->specific_bssid));

        for (ssid_idx = 0; ((ssid_idx < NELEMENTS(puser_scan_in->ssid_list)) &&
                            (*puser_scan_in->ssid_list[ssid_idx].ssid || puser_scan_in->ssid_list[ssid_idx].max_len));
             ssid_idx++)
        {
            ssid_len = wlan_strlen((char *)puser_scan_in->ssid_list[ssid_idx].ssid);

            pwildcard_ssid_tlv                  = (MrvlIEtypes_WildCardSsIdParamSet_t *)ptlv_pos;
            pwildcard_ssid_tlv->header.type     = wlan_cpu_to_le16(TLV_TYPE_WILDCARDSSID);
            pwildcard_ssid_tlv->header.len      = (t_u16)(ssid_len + sizeof(pwildcard_ssid_tlv->max_ssid_length));
            pwildcard_ssid_tlv->max_ssid_length = puser_scan_in->ssid_list[ssid_idx].max_len;

            (void)__memcpy(pmadapter, pwildcard_ssid_tlv->ssid, puser_scan_in->ssid_list[ssid_idx].ssid,
                           MIN(MLAN_MAX_SSID_LENGTH, ssid_len));

            ptlv_pos += (sizeof(pwildcard_ssid_tlv->header) + pwildcard_ssid_tlv->header.len);

            pwildcard_ssid_tlv->header.len = wlan_cpu_to_le16(pwildcard_ssid_tlv->header.len);

            PRINTM(MINFO, "Scan: ssid_list[%d]: %s, %d\n", ssid_idx, pwildcard_ssid_tlv->ssid,
                   pwildcard_ssid_tlv->max_ssid_length);

            if (ssid_len)
                ssid_filter = MTRUE;
        }

        /*
         *  The default number of channels sent in the command is low to
         *    ensure the response buffer from the firmware does not truncate
         *    scan results.  That is not an issue with an SSID or BSSID
         *    filter applied to the scan results in the firmware.
         */
        if ((ssid_idx && ssid_filter) || memcmp(pmadapter, pscan_cfg_out->specific_bssid, &zero_mac, sizeof(zero_mac)))
        {
            *pfiltered_scan = MTRUE;
        }
    }
    else
    {
        pscan_cfg_out->bss_mode = (t_u8)pmadapter->scan_mode;
        num_probes              = pmadapter->scan_probes;
    }

    /*
     *  If a specific BSSID or SSID is used, the number of channels in the
     *  scan command will be increased to the absolute maximum.
     */
    if (*pfiltered_scan)
        *pmax_chan_per_scan = MRVDRV_MAX_CHANNELS_PER_SPECIFIC_SCAN;
    else
        *pmax_chan_per_scan = MRVDRV_CHANNELS_PER_SCAN_CMD;

    /* If the input config or adapter has the number of Probes set, add tlv */
    if (num_probes)
    {
        PRINTM(MINFO, "Scan: num_probes = %d\n", num_probes);

        pnum_probes_tlv              = (MrvlIEtypes_NumProbes_t *)ptlv_pos;
        pnum_probes_tlv->header.type = wlan_cpu_to_le16(TLV_TYPE_NUMPROBES);
        pnum_probes_tlv->header.len  = sizeof(pnum_probes_tlv->num_probes);
        pnum_probes_tlv->num_probes  = wlan_cpu_to_le16((t_u16)num_probes);

        ptlv_pos += sizeof(pnum_probes_tlv->header) + pnum_probes_tlv->header.len;

        pnum_probes_tlv->header.len = wlan_cpu_to_le16(pnum_probes_tlv->header.len);
    }

    /* Append rates tlv */
    (void)__memset(pmadapter, rates, 0, sizeof(rates));

    rates_size = wlan_get_supported_rates(
        pmpriv, pmpriv->bss_mode,
        (pmpriv->bss_mode == MLAN_BSS_MODE_INFRA) ? pmpriv->config_bands : pmadapter->adhoc_start_band, rates);

    prates_tlv              = (MrvlIEtypes_RatesParamSet_t *)ptlv_pos;
    prates_tlv->header.type = wlan_cpu_to_le16(TLV_TYPE_RATES);
    prates_tlv->header.len  = wlan_cpu_to_le16((t_u16)rates_size);
    (void)__memcpy(pmadapter, prates_tlv->rates, rates, rates_size);
    ptlv_pos += sizeof(prates_tlv->header) + rates_size;

    PRINTM(MINFO, "SCAN_CMD: Rates size = %d\n", rates_size);

    if (ISSUPP_11NENABLED(pmpriv->adapter->fw_cap_info) &&
        (pmpriv->config_bands & BAND_GN || pmpriv->config_bands & BAND_AN) && wmsdk_is_11N_enabled())
    {
        pht_cap = (MrvlIETypes_HTCap_t *)ptlv_pos;
        (void)__memset(pmadapter, pht_cap, 0, sizeof(MrvlIETypes_HTCap_t));
        pht_cap->header.type = wlan_cpu_to_le16(HT_CAPABILITY);
        pht_cap->header.len  = sizeof(HTCap_t);
        wlan_fill_ht_cap_tlv(pmpriv, pht_cap, pmpriv->config_bands);
        HEXDUMP("SCAN: HT_CAPABILITIES IE", (t_u8 *)pht_cap, sizeof(MrvlIETypes_HTCap_t));
        ptlv_pos += sizeof(MrvlIETypes_HTCap_t);
        pht_cap->header.len = wlan_cpu_to_le16(pht_cap->header.len);
    }

    if (ISSUPP_11ACENABLED(pmpriv->adapter->fw_cap_info) && (pmpriv->config_bands & BAND_AAC))
    {
        pvht_cap = (MrvlIETypes_VHTCap_t *)ptlv_pos;
        (void)__memset(pmadapter, pvht_cap, 0, sizeof(MrvlIETypes_VHTCap_t));
        pvht_cap->header.type = wlan_cpu_to_le16(VHT_CAPABILITY);
        pvht_cap->header.len  = sizeof(VHT_capa_t);
        wlan_fill_vht_cap_tlv(pmpriv, pvht_cap, pmpriv->config_bands, MFALSE);
        HEXDUMP("SCAN: VHT_CAPABILITIES IE", (t_u8 *)pvht_cap, sizeof(MrvlIETypes_VHTCap_t));
        ptlv_pos += sizeof(MrvlIETypes_VHTCap_t);
        pvht_cap->header.len = wlan_cpu_to_le16(pvht_cap->header.len);
    }

    /* fixme: enable this later when req. */

    /*
     * Set the output for the channel TLV to the address in the tlv buffer
     *   past any TLVs that were added in this function (SSID, num_probes).
     *   Channel TLVs will be added past this for each scan command, preserving
     *   the TLVs that were previously added.
     */
    *ppchan_list_out = (MrvlIEtypes_ChanListParamSet_t *)ptlv_pos;

    if (puser_scan_in && puser_scan_in->chan_list[0].chan_number)
    {
        PRINTM(MINFO, "Scan: Using supplied channel list\n");

        for (chan_idx = 0; chan_idx < WLAN_USER_SCAN_CHAN_MAX && puser_scan_in->chan_list[chan_idx].chan_number;
             chan_idx++)
        {
            radio_type = puser_scan_in->chan_list[chan_idx].radio_type;
            if (!wlan_is_band_compatible(pmpriv->config_bands, radio_type_to_band(radio_type)))
                continue;

            channel                                   = puser_scan_in->chan_list[chan_idx].chan_number;
            (pscan_chan_list + chan_idx)->chan_number = channel;

            (pscan_chan_list + chan_idx)->radio_type = radio_type;

            scan_type = puser_scan_in->chan_list[chan_idx].scan_type;
            if (scan_type == MLAN_SCAN_TYPE_UNCHANGED)
                scan_type = pmadapter->scan_type;

            if (radio_type == HostCmd_SCAN_RADIO_TYPE_A)
            {
                if (pmadapter->fw_bands & BAND_A)
                    PRINTM(MINFO, "UserScan request for A Band channel %d!!\n", channel);
                else
                {
                    PRINTM(MERROR, "Scan in A band is not allowed!!\n");
                    ret = MLAN_STATUS_FAILURE;
                    LEAVE();
                    return ret;
                }
            }

            if (pmadapter->active_scan_triggered == MFALSE)
            {
                /* Prevent active scanning on a radar controlled channel */
                if (radio_type == HostCmd_SCAN_RADIO_TYPE_A)
                {
                    if (wlan_11h_radar_detect_required(pmpriv, channel))
                    {
                        scan_type = MLAN_SCAN_TYPE_PASSIVE;
                    }
                }
                if (radio_type == HostCmd_SCAN_RADIO_TYPE_BG)
                {
                    if (wlan_bg_scan_type_is_passive(pmpriv, channel))
                    {
                        scan_type = MLAN_SCAN_TYPE_PASSIVE;
                    }
                }
            }
            if (scan_type == MLAN_SCAN_TYPE_PASSIVE)
            {
                (pscan_chan_list + chan_idx)->chan_scan_mode.passive_scan       = MTRUE;
                (pscan_chan_list + chan_idx)->chan_scan_mode.hidden_ssid_report = MTRUE;
                ;
            }
            else
            {
                (pscan_chan_list + chan_idx)->chan_scan_mode.passive_scan = MFALSE;
            }

            if (puser_scan_in->chan_list[chan_idx].scan_time)
            {
                scan_dur = (t_u16)puser_scan_in->chan_list[chan_idx].scan_time;
            }
            else
            {
                if (scan_type == MLAN_SCAN_TYPE_PASSIVE)
                {
                    scan_dur = pmadapter->passive_scan_time;
                }
                else if (*pfiltered_scan)
                {
                    scan_dur = pmadapter->specific_scan_time;
                }
                else
                {
                    scan_dur = pmadapter->active_scan_time;
                }
            }

            (pscan_chan_list + chan_idx)->min_scan_time = wlan_cpu_to_le16(scan_dur);
            (pscan_chan_list + chan_idx)->max_scan_time = wlan_cpu_to_le16(scan_dur);

            wscan_d("Channel: %d Type: %s ", channel, scan_type == MLAN_SCAN_TYPE_PASSIVE ? "Passive" : "Active");
        }

        /* Check if we are only scanning the current channel */
        if ((chan_idx == 1) &&
            (puser_scan_in->chan_list[0].chan_number == pmpriv->curr_bss_params.bss_descriptor.channel))
        {
            *pscan_current_only = MTRUE;
            PRINTM(MINFO, "Scan: Scanning current channel only\n");
        }
    }
    else
    {
        PRINTM(MINFO, "Scan: Creating full region channel list\n");
        wlan_scan_create_channel_list(pmpriv, puser_scan_in, pscan_chan_list, *pfiltered_scan);
    }

    LEAVE();
    return ret;
}

/**
 *  @brief Inspect the scan response buffer for pointers to expected TLVs
 *
 *  TLVs can be included at the end of the scan response BSS information.
 *    Parse the data in the buffer for pointers to TLVs that can potentially
 *    be passed back in the response
 *
 *  @param pmadapter        Pointer to the mlan_adapter structure
 *  @param ptlv             Pointer to the start of the TLV buffer to parse
 *  @param tlv_buf_size     Size of the TLV buffer
 *  @param req_tlv_type     Request TLV's type
 *  @param pptlv            Output parameter: Pointer to the request TLV if found
 *
 *  @return                 N/A
 */
static t_void wlan_ret_802_11_scan_get_tlv_ptrs(IN pmlan_adapter pmadapter,
                                                IN MrvlIEtypes_Data_t *ptlv,
                                                IN t_u32 tlv_buf_size,
                                                IN t_u32 req_tlv_type,
                                                OUT MrvlIEtypes_Data_t **pptlv)
{
    MrvlIEtypes_Data_t *pcurrent_tlv;
    t_u32 tlv_buf_left;
    t_u32 tlv_type;
    t_u32 tlv_len;

    ENTER();

    pcurrent_tlv = ptlv;
    tlv_buf_left = tlv_buf_size;
    *pptlv       = MNULL;

    PRINTM(MINFO, "SCAN_RESP: tlv_buf_size = %d\n", tlv_buf_size);

    while (tlv_buf_left >= sizeof(MrvlIEtypesHeader_t))
    {
        tlv_type = wlan_le16_to_cpu(pcurrent_tlv->header.type);
        tlv_len  = wlan_le16_to_cpu(pcurrent_tlv->header.len);

        if (sizeof(ptlv->header) + tlv_len > tlv_buf_left)
        {
            PRINTM(MERROR, "SCAN_RESP: TLV buffer corrupt\n");
            break;
        }

        if (req_tlv_type == tlv_type)
        {
            switch (tlv_type)
            {
                case TLV_TYPE_TSFTIMESTAMP:
                    PRINTM(MINFO, "SCAN_RESP: TSF Timestamp TLV, len = %d\n", tlv_len);
                    *pptlv = (MrvlIEtypes_Data_t *)pcurrent_tlv;
                    break;
                case TLV_TYPE_CHANNELBANDLIST:
                    PRINTM(MINFO, "SCAN_RESP: CHANNEL BAND LIST TLV, len = %d\n", tlv_len);
                    *pptlv = (MrvlIEtypes_Data_t *)pcurrent_tlv;
                    break;
                default:
                    PRINTM(MERROR, "SCAN_RESP: Unhandled TLV = %d\n", tlv_type);
                    /* Give up, this seems corrupted */
                    LEAVE();
                    return;
            }
        }

        if (*pptlv != NULL)
        {
            // HEXDUMP("SCAN_RESP: TLV Buf", (t_u8 *)*pptlv+4, tlv_len);
            break;
        }

        tlv_buf_left -= (sizeof(ptlv->header) + tlv_len);
        pcurrent_tlv = (MrvlIEtypes_Data_t *)(pcurrent_tlv->data + tlv_len);

    } /* while */

    LEAVE();
}

void check_for_wps_ie(
    const uint8_t *OuiType, bool *wps_IE_exist, t_u16 *wps_session, void *element_data, unsigned element_len);

/**
 *  @brief Interpret a BSS scan response returned from the firmware
 *
 *  Parse the various fixed fields and IEs passed back for a BSS probe
 *   response or beacon from the scan command.  Record information as needed
 *   in the scan table BSSDescriptor_t for that entry.
 *
 *  @param pmadapter    A pointer to mlan_adapter structure
 *  @param pbss_entry   Output parameter: Pointer to the BSS Entry
 *  @param pbeacon_info Pointer to the Beacon information
 *  @param bytes_left   Number of bytes left to parse
 *
 *  @return             MLAN_STATUS_SUCCESS or MLAN_STATUS_FAILURE
 */
static mlan_status wlan_interpret_bss_desc_with_ie(IN pmlan_adapter pmadapter,
                                                   OUT BSSDescriptor_t *pbss_entry,
                                                   IN t_u8 **pbeacon_info,
                                                   IN t_u32 *bytes_left)
{
    mlan_status ret = MLAN_STATUS_SUCCESS;
    IEEEtypes_ElementId_e element_id;
    IEEEtypes_FhParamSet_t *pfh_param_set;
    IEEEtypes_DsParamSet_t *pds_param_set;
    IEEEtypes_DtimParamSet_t *pdtim_param_set;
    IEEEtypes_CfParamSet_t *pcf_param_set;
    IEEEtypes_IbssParamSet_t *pibss_param_set;
    IEEEtypes_CapInfo_t *pcap_info;
    WLAN_802_11_FIXED_IEs fixed_ie;
    t_u8 *pcurrent_ptr;
    t_u8 *prate;
    t_u8 element_len;
    t_u16 total_ie_len;
    t_u8 bytes_to_copy;
    t_u8 rate_size;
    t_u16 beacon_size;
    t_u8 found_data_rate_ie;
    t_u32 bytes_left_for_current_beacon;
    /* IEEEtypes_ERPInfo_t *perp_info; */

    IEEEtypes_VendorSpecific_t *pvendor_ie;
    const t_u8 wpa_oui[4] = {0x00, 0x50, 0xf2, 0x01};
    const t_u8 wmm_oui[4] = {0x00, 0x50, 0xf2, 0x02};
    IEEEtypes_CountryInfoSet_t *pcountry_info;

    ENTER();

    found_data_rate_ie = MFALSE;
    rate_size          = 0;
    beacon_size        = 0;

    if (*bytes_left >= sizeof(beacon_size))
    {
        /* Extract & convert beacon size from the command buffer */
        (void)__memcpy(pmadapter, &beacon_size, *pbeacon_info, sizeof(beacon_size));
        beacon_size = wlan_le16_to_cpu(beacon_size);
        *bytes_left -= sizeof(beacon_size);
        *pbeacon_info += sizeof(beacon_size);
    }

    if (!beacon_size || beacon_size > *bytes_left)
    {
        *pbeacon_info += *bytes_left;
        *bytes_left = 0;

        LEAVE();
        return MLAN_STATUS_FAILURE;
    }

    /* Initialize the current working beacon pointer for this BSS iteration */
    pcurrent_ptr = *pbeacon_info;

    /* Advance the return beacon pointer past the current beacon */
    *pbeacon_info += beacon_size;
    *bytes_left -= beacon_size;

    bytes_left_for_current_beacon = beacon_size;

    if (bytes_left_for_current_beacon < (MLAN_MAC_ADDR_LENGTH + sizeof(t_u8) + sizeof(WLAN_802_11_FIXED_IEs)))
    {
        PRINTM(MERROR, "InterpretIE: Not enough bytes left\n");
        LEAVE();
        return MLAN_STATUS_FAILURE;
    }

    (void)__memcpy(pmadapter, pbss_entry->mac_address, pcurrent_ptr, MLAN_MAC_ADDR_LENGTH);
    PRINTM(MINFO, "InterpretIE: AP MAC Addr-%02x:%02x:%02x:%02x:%02x:%02x\n", pbss_entry->mac_address[0],
           pbss_entry->mac_address[1], pbss_entry->mac_address[2], pbss_entry->mac_address[3],
           pbss_entry->mac_address[4], pbss_entry->mac_address[5]);

    pcurrent_ptr += MLAN_MAC_ADDR_LENGTH;
    bytes_left_for_current_beacon -= MLAN_MAC_ADDR_LENGTH;

    /*
     * Next 4 fields are RSSI (for legacy scan only), time stamp,
     *   beacon interval, and capability information
     */
    /* RSSI is 1 byte long */
    pbss_entry->rssi = (t_s32)(*pcurrent_ptr);
    PRINTM(MINFO, "InterpretIE: RSSI=%02X\n", *pcurrent_ptr);
    pcurrent_ptr += 1;
    bytes_left_for_current_beacon -= 1;

    /*
     *  The RSSI is not part of the beacon/probe response.  After we have
     *    advanced pcurrent_ptr past the RSSI field, save the remaining
     *    data for use at the application layer
     */
    pbss_entry->pbeacon_buf     = pcurrent_ptr;
    pbss_entry->beacon_buf_size = bytes_left_for_current_beacon;

    pcurrent_ptr += 8;
    bytes_left_for_current_beacon -= 8;

    /* Beacon interval is 2 bytes long */
    (void)__memcpy(pmadapter, &fixed_ie.beacon_interval, pcurrent_ptr, 2);
    pbss_entry->beacon_period = wlan_le16_to_cpu(fixed_ie.beacon_interval);
    pcurrent_ptr += 2;
    bytes_left_for_current_beacon -= 2;

    /* Capability information is 2 bytes long */
    (void)__memcpy(pmadapter, &fixed_ie.capabilities, pcurrent_ptr, 2);
    PRINTM(MINFO, "InterpretIE: fixed_ie.capabilities=0x%X\n", fixed_ie.capabilities);
    fixed_ie.capabilities = wlan_le16_to_cpu(fixed_ie.capabilities);
    pcap_info             = (IEEEtypes_CapInfo_t *)&fixed_ie.capabilities;
    (void)__memcpy(pmadapter, &pbss_entry->cap_info, pcap_info, sizeof(IEEEtypes_CapInfo_t));
    pcurrent_ptr += 2;
    bytes_left_for_current_beacon -= 2;

    /* Rest of the current buffer are IE's */
    PRINTM(MINFO, "InterpretIE: IELength for this AP = %d\n", bytes_left_for_current_beacon);

    HEXDUMP("InterpretIE: IE info", (t_u8 *)pcurrent_ptr, bytes_left_for_current_beacon);

    if (pcap_info->privacy)
    {
        PRINTM(MINFO, "InterpretIE: AP WEP enabled\n");
        pbss_entry->privacy = Wlan802_11PrivFilter8021xWEP;
    }
    else
    {
        pbss_entry->privacy = Wlan802_11PrivFilterAcceptAll;
    }

    if (pcap_info->ibss == 1)
    {
        pbss_entry->bss_mode = MLAN_BSS_MODE_IBSS;
    }
    else
    {
        pbss_entry->bss_mode = MLAN_BSS_MODE_INFRA;
    }

    /* Process variable IE */
    while (bytes_left_for_current_beacon >= 2)
    {
        element_id   = (IEEEtypes_ElementId_e)(*((t_u8 *)pcurrent_ptr));
        element_len  = *((t_u8 *)pcurrent_ptr + 1);
        total_ie_len = element_len + sizeof(IEEEtypes_Header_t);

        if (bytes_left_for_current_beacon < total_ie_len)
        {
            PRINTM(MERROR,
                   "InterpretIE: Error in processing IE, "
                   "bytes left < IE length\n");
            bytes_left_for_current_beacon = 0;
            continue;
        }

        switch (element_id)
        {
            case SSID:
                if (element_len > MRVDRV_MAX_SSID_LENGTH)
                {
                    bytes_left_for_current_beacon = 0;
                    continue;
                }
                pbss_entry->ssid.ssid_len = element_len;
                (void)__memcpy(pmadapter, pbss_entry->ssid.ssid, (pcurrent_ptr + 2), element_len);
                wscan_d("AP: %s", pbss_entry->ssid.ssid);
                PRINTM(MINFO, "InterpretIE: ssid: %-32s\n", pbss_entry->ssid.ssid);
                break;

            case SUPPORTED_RATES:
                if (element_len > WLAN_SUPPORTED_RATES)
                {
                    bytes_left_for_current_beacon = 0;
                    continue;
                }
                (void)__memcpy(pmadapter, pbss_entry->data_rates, pcurrent_ptr + 2, element_len);
                (void)__memcpy(pmadapter, pbss_entry->supported_rates, pcurrent_ptr + 2, element_len);
                HEXDUMP("InterpretIE: SupportedRates:", pbss_entry->supported_rates, element_len);
                rate_size          = element_len;
                found_data_rate_ie = MTRUE;
                break;

            case FH_PARAM_SET:
                pfh_param_set                = (IEEEtypes_FhParamSet_t *)pcurrent_ptr;
                pbss_entry->network_type_use = Wlan802_11FH;
                (void)__memcpy(pmadapter, &pbss_entry->phy_param_set.fh_param_set, pfh_param_set,
                               MIN(total_ie_len, sizeof(IEEEtypes_FhParamSet_t)));
                pbss_entry->phy_param_set.fh_param_set.len =
                    MIN(element_len, (sizeof(IEEEtypes_FhParamSet_t) - sizeof(IEEEtypes_Header_t)));
                pbss_entry->phy_param_set.fh_param_set.dwell_time =
                    wlan_le16_to_cpu(pbss_entry->phy_param_set.fh_param_set.dwell_time);
                break;

            case DS_PARAM_SET:
                pds_param_set = (IEEEtypes_DsParamSet_t *)pcurrent_ptr;

                pbss_entry->network_type_use = Wlan802_11DS;
                pbss_entry->channel          = pds_param_set->current_chan;

                (void)__memcpy(pmadapter, &pbss_entry->phy_param_set.ds_param_set, pds_param_set,
                               MIN(total_ie_len, sizeof(IEEEtypes_DsParamSet_t)));
                pbss_entry->phy_param_set.ds_param_set.len =
                    MIN(element_len, (sizeof(IEEEtypes_DsParamSet_t) - sizeof(IEEEtypes_Header_t)));
                break;

            case CF_PARAM_SET:
                pcf_param_set = (IEEEtypes_CfParamSet_t *)pcurrent_ptr;
                (void)__memcpy(pmadapter, &pbss_entry->ss_param_set.cf_param_set, pcf_param_set,
                               MIN(total_ie_len, sizeof(IEEEtypes_CfParamSet_t)));
                pbss_entry->ss_param_set.cf_param_set.len =
                    MIN(element_len, (sizeof(IEEEtypes_CfParamSet_t) - sizeof(IEEEtypes_Header_t)));
                break;

            case DTIM_PARAM_SET:
                pdtim_param_set = (IEEEtypes_DtimParamSet_t *)pcurrent_ptr;

                pbss_entry->dtim_period = pdtim_param_set->dtim_period;
                break;

            case IBSS_PARAM_SET:
                pibss_param_set         = (IEEEtypes_IbssParamSet_t *)pcurrent_ptr;
                pbss_entry->atim_window = wlan_le16_to_cpu(pibss_param_set->atim_window);
                (void)__memcpy(pmadapter, &pbss_entry->ss_param_set.ibss_param_set, pibss_param_set,
                               MIN(total_ie_len, sizeof(IEEEtypes_IbssParamSet_t)));
                pbss_entry->ss_param_set.ibss_param_set.len =
                    MIN(element_len, (sizeof(IEEEtypes_IbssParamSet_t) - sizeof(IEEEtypes_Header_t)));
                break;

                /* Handle Country Info IE */
            case COUNTRY_INFO:
                /* Disabling this because IEEEtypes_CountryInfoSet_t size
                   is 254 bytes. Check later if can be optimized */
                pcountry_info = (IEEEtypes_CountryInfoSet_t *)pcurrent_ptr;

                if (pcountry_info->len < sizeof(pcountry_info->country_code) ||
                    (unsigned)(pcountry_info->len + 2) > sizeof(IEEEtypes_CountryInfoFullSet_t))
                {
                    PRINTM(MERROR,
                           "InterpretIE: 11D- Err "
                           "country_info len =%d min=%d max=%d\n",
                           pcountry_info->len, sizeof(pcountry_info->country_code),
                           sizeof(IEEEtypes_CountryInfoFullSet_t));
                    LEAVE();
                    return MLAN_STATUS_FAILURE;
                }

                (void)__memcpy(pmadapter, &pbss_entry->country_info, pcountry_info, pcountry_info->len + 2);
                HEXDUMP("InterpretIE: 11D- country_info:", (t_u8 *)pcountry_info, (t_u32)(pcountry_info->len + 2));
                break;
            case POWER_CONSTRAINT:
            case POWER_CAPABILITY:
            case TPC_REPORT:
            case CHANNEL_SWITCH_ANN:
            case QUIET:
            case IBSS_DFS:
            case SUPPORTED_CHANNELS:
            case TPC_REQUEST:
                /* fixme: Not enabled yet */
                /* wlan_11h_process_bss_elem(pmadapter, &pbss_entry->wlan_11h_bss_info, */
                /*                       pcurrent_ptr); */
                break;
            case EXTENDED_SUPPORTED_RATES:
                /*
                 * Only process extended supported rate
                 * if data rate is already found.
                 * Data rate IE should come before
                 * extended supported rate IE
                 */
                if (found_data_rate_ie)
                {
                    if ((element_len + rate_size) > WLAN_SUPPORTED_RATES)
                    {
                        bytes_to_copy = (WLAN_SUPPORTED_RATES - rate_size);
                    }
                    else
                    {
                        bytes_to_copy = element_len;
                    }

                    prate = (t_u8 *)pbss_entry->data_rates;
                    prate += rate_size;
                    (void)__memcpy(pmadapter, prate, pcurrent_ptr + 2, bytes_to_copy);

                    prate = (t_u8 *)pbss_entry->supported_rates;
                    prate += rate_size;
                    (void)__memcpy(pmadapter, prate, pcurrent_ptr + 2, bytes_to_copy);
                }
                HEXDUMP("InterpretIE: ExtSupportedRates:", pbss_entry->supported_rates, element_len + rate_size);
                break;

            case VENDOR_SPECIFIC_221:
                pvendor_ie = (IEEEtypes_VendorSpecific_t *)pcurrent_ptr;

                if (!memcmp(pmadapter, pvendor_ie->vend_hdr.oui, wpa_oui, sizeof(wpa_oui)))
                {
                    /* Save it here since we do not have beacon buffer */
                    /* fixme : Verify if this is the right approach. This had to be
                       done because IEEEtypes_Rsn_t was not the correct data
                       structure to map here  */
                    if (element_len <= (sizeof(pbss_entry->wpa_ie_buff) - sizeof(IEEEtypes_Header_t)))
                    {
                        (void)__memcpy(NULL, pbss_entry->wpa_ie_buff, pcurrent_ptr,
                                       element_len + sizeof(IEEEtypes_Header_t));
                        pbss_entry->pwpa_ie         = (IEEEtypes_VendorSpecific_t *)pbss_entry->wpa_ie_buff;
                        pbss_entry->wpa_ie_buff_len = element_len + sizeof(IEEEtypes_Header_t);

                        if (wifi_check_bss_entry_wpa2_entp_only(pbss_entry, VENDOR_SPECIFIC_221))
                            return MLAN_STATUS_RESOURCE;
                    }
                    else
                        wifi_e("Insufficient space to save WPA_IE size: %d", element_len);

                    /* pbss_entry->pwpa_ie = */
                    /*     (IEEEtypes_VendorSpecific_t *) pcurrent_ptr; */
                    /* pbss_entry->wpa_offset = */
                    /*     (t_u16) (pcurrent_ptr - pbss_entry->pbeacon_buf); */
                    HEXDUMP("InterpretIE: Resp WPA_IE", (t_u8 *)pbss_entry->pwpa_ie,
                            ((*(pbss_entry->pwpa_ie)).vend_hdr.len + sizeof(IEEEtypes_Header_t)));
                }
                else if (!memcmp(pmadapter, pvendor_ie->vend_hdr.oui, wmm_oui, sizeof(wmm_oui)))
                {
                    if (total_ie_len == sizeof(IEEEtypes_WmmParameter_t) || total_ie_len == sizeof(IEEEtypes_WmmInfo_t))
                    {
                        /*
                         * Only accept and copy the WMM IE if it matches
                         * the size expected for the WMM Info IE or the
                         * WMM Parameter IE.
                         */
                        (void)__memcpy(pmadapter, (t_u8 *)&pbss_entry->wmm_ie, pcurrent_ptr, total_ie_len);
                        HEXDUMP("InterpretIE: Resp WMM_IE", (t_u8 *)&pbss_entry->wmm_ie, total_ie_len);
                    }
                }
                break;
            case RSN_IE:
                /* Save it here since we do not have beacon buffer */
                /* fixme : Verify if this is the right approach. This had to be
                   done because IEEEtypes_Rsn_t was not the correct data
                   structure to map here  */
                if (element_len <= (sizeof(pbss_entry->rsn_ie_buff) - sizeof(IEEEtypes_Header_t)))
                {
                    (void)__memcpy(NULL, pbss_entry->rsn_ie_buff, pcurrent_ptr,
                                   element_len + sizeof(IEEEtypes_Header_t));
                    pbss_entry->rsn_ie_buff_len = element_len + sizeof(IEEEtypes_Header_t);
                    pbss_entry->prsn_ie         = (IEEEtypes_Generic_t *)pbss_entry->rsn_ie_buff;

                    if (wifi_check_bss_entry_wpa2_entp_only(pbss_entry, RSN_IE))
                        return MLAN_STATUS_RESOURCE;
                }
                else
                    wifi_e("Insufficient space to save RSN_IE size: %d", element_len);

                /* pbss_entry->prsn_ie = (IEEEtypes_Generic_t *) pcurrent_ptr; */
                /* pbss_entry->rsn_offset = */
                /*     (t_u16) (pcurrent_ptr - pbss_entry->pbeacon_buf); */
                HEXDUMP("InterpretIE: Resp RSN_IE", (t_u8 *)pbss_entry->prsn_ie,
                        (*(pbss_entry->prsn_ie)).ieee_hdr.len + sizeof(IEEEtypes_Header_t));
                break;
            case WAPI_IE:
                break;
            case HT_CAPABILITY:
                /* Save it here since we do not have beacon buffer */
                (void)__memcpy(NULL, &pbss_entry->ht_cap_saved, pcurrent_ptr, sizeof(IEEEtypes_HTCap_t));
                pbss_entry->pht_cap = &pbss_entry->ht_cap_saved;
                /* pbss_entry->pht_cap = (IEEEtypes_HTCap_t *) pcurrent_ptr; */
                /* pbss_entry->ht_cap_offset = */
                /*     (t_u16) (pcurrent_ptr - pbss_entry->pbeacon_buf); */
                HEXDUMP("InterpretIE: Resp HTCAP_IE", (t_u8 *)pbss_entry->pht_cap,
                        (*(pbss_entry->pht_cap)).ieee_hdr.len + sizeof(IEEEtypes_Header_t));
                break;
            case HT_OPERATION:
                /* Save it here since we do not have beacon buffer */
                (void)__memcpy(NULL, &pbss_entry->ht_info_saved, pcurrent_ptr, sizeof(IEEEtypes_HTInfo_t));
                pbss_entry->pht_info = &pbss_entry->ht_info_saved;
                /* pbss_entry->pht_info = (IEEEtypes_HTInfo_t *) pcurrent_ptr; */
                /* pbss_entry->ht_info_offset = */
                /*     (t_u16) (pcurrent_ptr - pbss_entry->pbeacon_buf); */
                HEXDUMP("InterpretIE: Resp HTINFO_IE", (t_u8 *)pbss_entry->pht_info,
                        (*(pbss_entry->pht_info)).ieee_hdr.len + sizeof(IEEEtypes_Header_t));
                break;
            case BSSCO_2040:
                /* Save it here since we do not have beacon buffer */
                (void)__memcpy(NULL, &pbss_entry->bss_co_2040_saved, pcurrent_ptr, sizeof(IEEEtypes_2040BSSCo_t));
                pbss_entry->pbss_co_2040 = &pbss_entry->bss_co_2040_saved;
                /* pbss_entry->pbss_co_2040 = (IEEEtypes_2040BSSCo_t *) pcurrent_ptr; */
                /* pbss_entry->bss_co_2040_offset = */
                /*     (t_u16) (pcurrent_ptr - pbss_entry->pbeacon_buf); */
                HEXDUMP("InterpretIE: Resp 2040BSSCOEXISTANCE_IE", (t_u8 *)pbss_entry->pbss_co_2040,
                        (*(pbss_entry->pbss_co_2040)).ieee_hdr.len + sizeof(IEEEtypes_Header_t));
                break;
            case VHT_CAPABILITY:
                /* Save it here since we do not have beacon buffer */
                (void)__memcpy(NULL, &pbss_entry->vht_cap_saved, pcurrent_ptr, sizeof(IEEEtypes_VHTCap_t));
                pbss_entry->pvht_cap = &pbss_entry->vht_cap_saved;
                break;
            case VHT_OPERATION:
                /* Save it here since we do not have beacon buffer */
                (void)__memcpy(NULL, &pbss_entry->vht_oprat_saved, pcurrent_ptr, sizeof(IEEEtypes_VHTOprat_t));
                pbss_entry->pvht_oprat = &pbss_entry->vht_oprat_saved;
                break;
            case VHT_TX_POWER_ENV:
                /* Save it here since we do not have beacon buffer */
                (void)__memcpy(NULL, &pbss_entry->vht_txpower_saved, pcurrent_ptr, sizeof(IEEEtypes_VHTtxpower_t));
                pbss_entry->pvht_txpower = &pbss_entry->vht_txpower_saved;
                break;
            case OPER_MODE_NTF:
                /* Save it here since we do not have beacon buffer */
                (void)__memcpy(NULL, &pbss_entry->poper_mode_saved, pcurrent_ptr, sizeof(IEEEtypes_OperModeNtf_t));
                pbss_entry->ppoper_mode = &pbss_entry->poper_mode_saved;
                break;
            case EXT_CAPABILITY:
                /* Save it here since we do not have beacon buffer */
                (void)__memcpy(NULL, &pbss_entry->ext_cap_saved, pcurrent_ptr, sizeof(IEEEtypes_ExtCap_t));
                pbss_entry->pext_cap = &pbss_entry->ext_cap_saved;
                break;
            case RSNX_IE:
                pbss_entry->prsnx_ie    = (IEEEtypes_Generic_t *)pcurrent_ptr;
                pbss_entry->rsnx_offset = (t_u16)(pcurrent_ptr - pbss_entry->pbeacon_buf);
                HEXDUMP("InterpretIE: Resp RSNX_IE", (t_u8 *)pbss_entry->prsnx_ie,
                        (*(pbss_entry->prsnx_ie)).ieee_hdr.len + sizeof(IEEEtypes_Header_t));
                break;

            default:
                break;
        }

        pcurrent_ptr += element_len + 2;

        /* Need to account for IE ID and IE Len */
        bytes_left_for_current_beacon -= (element_len + 2);

    } /* while (bytes_left_for_current_beacon > 2) */

    if (wifi_check_bss_entry_wpa2_entp_only(pbss_entry, 0))
        return MLAN_STATUS_RESOURCE;

    LEAVE();
    return ret;
}

/**
 *  @brief Post process the scan table after a new scan command has completed
 *
 *  Inspect each entry of the scan table and try to find an entry that
 *    matches our current associated/joined network from the scan.  If
 *    one is found, update the stored copy of the BSSDescriptor for our
 *    current network.
 *
 *  Debug dump the current scan table contents if compiled accordingly.
 *
 *  @param pmpriv       A pointer to mlan_private structure
 *
 *  @return             N/A
 */
/* static */ t_void wlan_scan_process_results(IN mlan_private *pmpriv)
{
    /*
     * Prepares domain info from scan table and downloads the
     *   domain info command to the FW.
     */
    if (wlan_11d_support_is_enabled(pmpriv))
    {
        if (pmpriv->support_11d != NULL)
            pmpriv->support_11d->wlan_11d_prepare_dnld_domain_info_cmd_p(pmpriv);
    }

    LEAVE();
}

/********************************************************
                Global Functions
********************************************************/

/**
 *  @brief Check if a scanned network compatible with the driver settings
 *
 *   WEP     WPA     WPA2    ad-hoc  encrypt                      Network
 * enabled enabled  enabled   AES     mode   Privacy  WPA  WPA2  Compatible
 *    0       0        0       0      NONE      0      0    0   yes No security
 *    0       1        0       0       x        1x     1    x   yes WPA (disable HT if no AES)
 *    0       0        1       0       x        1x     x    1   yes WPA2 (disable HT if no AES)
 *    0       0        0       1      NONE      1      0    0   yes Ad-hoc AES
 *    1       0        0       0      NONE      1      0    0   yes Static WEP (disable HT)
 *    0       0        0       0     !=NONE     1      0    0   yes Dynamic WEP
 *
 *  @param pmpriv  A pointer to mlan_private
 *  @param index   Index in scan table to check against current driver settings
 *  @param mode    Network mode: Infrastructure or IBSS
 *
 *  @return        Index in ScanTable, or negative value if error
 */
t_s32 wlan_is_network_compatible(IN mlan_private *pmpriv, IN t_u32 index, IN t_u32 mode)
{
    mlan_adapter *pmadapter = pmpriv->adapter;
    BSSDescriptor_t *pbss_desc;

    ENTER();

    pbss_desc              = &pmadapter->pscan_table[index];
    pbss_desc->disable_11n = MFALSE;

    /* Don't check for compatibility if roaming */
    if ((pmpriv->media_connected == MTRUE) && (pmpriv->bss_mode == MLAN_BSS_MODE_INFRA) &&
        (pbss_desc->bss_mode == MLAN_BSS_MODE_INFRA))
    {
        LEAVE();
        return index;
    }

    /* fixme: Disabled for now */
    if ((pbss_desc->bss_mode == mode) && (pmpriv->sec_info.ewpa_enabled == MTRUE))
    {
        if (((pbss_desc->pwpa_ie) && ((*(pbss_desc->pwpa_ie)).vend_hdr.element_id == WPA_IE)) ||
            ((pbss_desc->prsn_ie) && ((*(pbss_desc->prsn_ie)).ieee_hdr.element_id == RSN_IE)))
        {
            if (((pmpriv->adapter->config_bands & BAND_GN || pmpriv->adapter->config_bands & BAND_AN) &&
                 pbss_desc->pht_cap) &&
                (pmpriv->bss_mode == MLAN_BSS_MODE_INFRA) &&
                !is_wpa_oui_present(pmpriv->adapter, pbss_desc, CIPHER_SUITE_CCMP) &&
                !is_rsn_oui_present(pmpriv->adapter, pbss_desc, CIPHER_SUITE_CCMP))
            {
                if (is_wpa_oui_present(pmpriv->adapter, pbss_desc, CIPHER_SUITE_TKIP) ||
                    is_rsn_oui_present(pmpriv->adapter, pbss_desc, CIPHER_SUITE_TKIP))
                {
                    PRINTM(MINFO, "Disable 11n if AES is not supported by AP\n");
                    pbss_desc->disable_11n = MTRUE;
                }
                else
                {
                    LEAVE();
                    return -1;
                }
            }
            LEAVE();
            return index;
        }
        else
        {
            PRINTM(MINFO, "ewpa_enabled: Ignore none WPA/WPA2 AP\n");
            LEAVE();
            return -1;
        }
    }

    if (pmpriv->sec_info.wapi_enabled &&
        (pbss_desc->pwapi_ie && ((*(pbss_desc->pwapi_ie)).ieee_hdr.element_id == WAPI_IE)))
    {
        PRINTM(MINFO, "Return success for WAPI AP\n");
        LEAVE();
        return index;
    }

    if (pbss_desc->bss_mode == mode)
    {
        if (pmpriv->sec_info.wep_status == Wlan802_11WEPDisabled && !pmpriv->sec_info.wpa_enabled &&
            !pmpriv->sec_info.wpa2_enabled &&
            ((!pbss_desc->pwpa_ie) || ((*(pbss_desc->pwpa_ie)).vend_hdr.element_id != WPA_IE)) &&
            ((!pbss_desc->prsn_ie) || ((*(pbss_desc->prsn_ie)).ieee_hdr.element_id != RSN_IE)) &&
            !pmpriv->adhoc_aes_enabled && pmpriv->sec_info.encryption_mode == MLAN_ENCRYPTION_MODE_NONE &&
            !pbss_desc->privacy)
        {
            /* No security */
            LEAVE();
            return index;
        }
        else if (pmpriv->sec_info.wep_status == Wlan802_11WEPEnabled && !pmpriv->sec_info.wpa_enabled &&
                 !pmpriv->sec_info.wpa2_enabled && !pmpriv->adhoc_aes_enabled && pbss_desc->privacy)
        {
            /* Static WEP enabled */
            PRINTM(MINFO, "Disable 11n in WEP mode\n");
            pbss_desc->disable_11n = MTRUE;
            LEAVE();
            return index;
        }
        else if (pmpriv->sec_info.wep_status == Wlan802_11WEPDisabled && pmpriv->sec_info.wpa_enabled &&
                 !pmpriv->sec_info.wpa2_enabled &&
                 ((pbss_desc->pwpa_ie) && ((*(pbss_desc->pwpa_ie)).vend_hdr.element_id == WPA_IE)) &&
                 !pmpriv->adhoc_aes_enabled
                 /*
                  * Privacy bit may NOT be set in some APs like LinkSys WRT54G
                  * && pbss_desc->privacy
                  */
        )
        {
            /* WPA enabled */
            PRINTM(MINFO,
                   "wlan_is_network_compatible() WPA: index=%d wpa_ie=%#x "
                   "rsn_ie=%#x WEP=%s WPA=%s WPA2=%s EncMode=%#x "
                   "privacy=%#x\n",
                   index, (pbss_desc->pwpa_ie) ? (*(pbss_desc->pwpa_ie)).vend_hdr.element_id : 0,
                   (pbss_desc->prsn_ie) ? (*(pbss_desc->prsn_ie)).ieee_hdr.element_id : 0,
                   (pmpriv->sec_info.wep_status == Wlan802_11WEPEnabled) ? "e" : "d",
                   (pmpriv->sec_info.wpa_enabled) ? "e" : "d", (pmpriv->sec_info.wpa2_enabled) ? "e" : "d",
                   pmpriv->sec_info.encryption_mode, pbss_desc->privacy);
            if (((pmpriv->adapter->config_bands & BAND_GN || pmpriv->adapter->config_bands & BAND_AN) &&
                 pbss_desc->pht_cap) &&
                (pmpriv->bss_mode == MLAN_BSS_MODE_INFRA) &&
                !is_wpa_oui_present(pmpriv->adapter, pbss_desc, CIPHER_SUITE_CCMP))
            {
                if (is_wpa_oui_present(pmpriv->adapter, pbss_desc, CIPHER_SUITE_TKIP) != 0U)
                {
                    PRINTM(MINFO, "Disable 11n if AES is not supported by AP\n");
                    pbss_desc->disable_11n = MTRUE;
                }
                else
                {
                    LEAVE();
                    return -1;
                }
            }
            LEAVE();
            return index;
        }
        else if (pmpriv->sec_info.wep_status == Wlan802_11WEPDisabled && !pmpriv->sec_info.wpa_enabled &&
                 pmpriv->sec_info.wpa2_enabled &&
                 ((pbss_desc->prsn_ie) && ((*(pbss_desc->prsn_ie)).ieee_hdr.element_id == RSN_IE)) &&
                 !pmpriv->adhoc_aes_enabled
                 /*
                  * Privacy bit may NOT be set in some APs like LinkSys WRT54G
                  * && pbss_desc->privacy
                  */
        )
        {
            /* WPA2 enabled */
            PRINTM(MINFO,
                   "wlan_is_network_compatible() WPA2: index=%d wpa_ie=%#x "
                   "rsn_ie=%#x WEP=%s WPA=%s WPA2=%s EncMode=%#x "
                   "privacy=%#x\n",
                   index, (pbss_desc->pwpa_ie) ? (*(pbss_desc->pwpa_ie)).vend_hdr.element_id : 0,
                   (pbss_desc->prsn_ie) ? (*(pbss_desc->prsn_ie)).ieee_hdr.element_id : 0,
                   (pmpriv->sec_info.wep_status == Wlan802_11WEPEnabled) ? "e" : "d",
                   (pmpriv->sec_info.wpa_enabled) ? "e" : "d", (pmpriv->sec_info.wpa2_enabled) ? "e" : "d",
                   pmpriv->sec_info.encryption_mode, pbss_desc->privacy);
            if (((pmpriv->adapter->config_bands & BAND_GN || pmpriv->adapter->config_bands & BAND_AN) &&
                 pbss_desc->pht_cap) &&
                (pmpriv->bss_mode == MLAN_BSS_MODE_INFRA) &&
                !is_rsn_oui_present(pmpriv->adapter, pbss_desc, CIPHER_SUITE_CCMP))
            {
                if (is_rsn_oui_present(pmpriv->adapter, pbss_desc, CIPHER_SUITE_TKIP) != 0U)
                {
                    PRINTM(MINFO, "Disable 11n if AES is not supported by AP\n");
                    pbss_desc->disable_11n = MTRUE;
                }
                else
                {
                    LEAVE();
                    return -1;
                }
            }
            LEAVE();
            return index;
        }
        else if (pmpriv->sec_info.wep_status == Wlan802_11WEPDisabled && !pmpriv->sec_info.wpa_enabled &&
                 !pmpriv->sec_info.wpa2_enabled &&
                 ((!pbss_desc->pwpa_ie) || ((*(pbss_desc->pwpa_ie)).vend_hdr.element_id != WPA_IE)) &&
                 ((!pbss_desc->prsn_ie) || ((*(pbss_desc->prsn_ie)).ieee_hdr.element_id != RSN_IE)) &&
                 pmpriv->adhoc_aes_enabled && pmpriv->sec_info.encryption_mode == MLAN_ENCRYPTION_MODE_NONE &&
                 pbss_desc->privacy)
        {
            /* Ad-hoc AES enabled */
            LEAVE();
            return index;
        }
        else if (pmpriv->sec_info.wep_status == Wlan802_11WEPDisabled && !pmpriv->sec_info.wpa_enabled &&
                 !pmpriv->sec_info.wpa2_enabled &&
                 ((!pbss_desc->pwpa_ie) || ((*(pbss_desc->pwpa_ie)).vend_hdr.element_id != WPA_IE)) &&
                 ((!pbss_desc->prsn_ie) || ((*(pbss_desc->prsn_ie)).ieee_hdr.element_id != RSN_IE)) &&
                 !pmpriv->adhoc_aes_enabled && pmpriv->sec_info.encryption_mode != MLAN_ENCRYPTION_MODE_NONE &&
                 pbss_desc->privacy)
        {
            /* Dynamic WEP enabled */
            PRINTM(MINFO,
                   "wlan_is_network_compatible() dynamic WEP: index=%d "
                   "wpa_ie=%#x rsn_ie=%#x EncMode=%#x privacy=%#x\n",
                   index, (pbss_desc->pwpa_ie) ? (*(pbss_desc->pwpa_ie)).vend_hdr.element_id : 0,
                   (pbss_desc->prsn_ie) ? (*(pbss_desc->prsn_ie)).ieee_hdr.element_id : 0,
                   pmpriv->sec_info.encryption_mode, pbss_desc->privacy);
            LEAVE();
            return index;
        }

        else
        {
            /* Security doesn't match */
            PRINTM(MINFO,
                   "wlan_is_network_compatible() FAILED: index=%d wpa_ie=%#x "
                   "rsn_ie=%#x WEP=%s WPA=%s WPA2=%s EncMode=%#x privacy=%#x\n",
                   index, (pbss_desc->pwpa_ie) ? (*(pbss_desc->pwpa_ie)).vend_hdr.element_id : 0,
                   (pbss_desc->prsn_ie) ? (*(pbss_desc->prsn_ie)).ieee_hdr.element_id : 0,
                   (pmpriv->sec_info.wep_status == Wlan802_11WEPEnabled) ? "e" : "d",
                   (pmpriv->sec_info.wpa_enabled) ? "e" : "d", (pmpriv->sec_info.wpa2_enabled) ? "e" : "d",
                   pmpriv->sec_info.encryption_mode, pbss_desc->privacy);
            LEAVE();
            return -1;
        }
    }

    /* Mode doesn't match */
    LEAVE();
    return -1;
}

/**
 *  @brief Internal function used to start a scan based on an input config
 *
 *  Use the input user scan configuration information when provided in
 *    order to send the appropriate scan commands to firmware to populate or
 *    update the internal driver scan table
 *
 *  @param pmpriv          A pointer to mlan_private structure
 *  @param pioctl_buf      A pointer to MLAN IOCTL Request buffer
 *  @param puser_scan_in   Pointer to the input configuration for the requested
 *                         scan.
 *
 *  @return              MLAN_STATUS_SUCCESS or < 0 if error
 */
mlan_status wlan_scan_networks(IN mlan_private *pmpriv,
                               IN t_void *pioctl_buf,
                               IN const wlan_user_scan_cfg *puser_scan_in)
{
    mlan_status ret         = MLAN_STATUS_SUCCESS;
    mlan_adapter *pmadapter = pmpriv->adapter;
    mlan_callbacks *pcb     = (mlan_callbacks *)&pmadapter->callbacks;
    /* cmd_ctrl_node *pcmd_node = MNULL; */
    pmlan_ioctl_req pioctl_req = (mlan_ioctl_req *)pioctl_buf;

    wlan_scan_cmd_config_tlv *pscan_cfg_out = MNULL;
    MrvlIEtypes_ChanListParamSet_t *pchan_list_out;
    t_u32 buf_size;
    ChanScanParamSet_t *pscan_chan_list;

    t_u8 keep_previous_scan;
    t_u8 filtered_scan;
    t_u8 scan_current_chan_only;
    t_u8 max_chan_per_scan;

    ENTER();

    ret = pcb->moal_malloc(pmadapter->pmoal_handle, sizeof(wlan_scan_cmd_config_tlv), MLAN_MEM_DEF,
                           (t_u8 **)&pscan_cfg_out);
    if (ret != MLAN_STATUS_SUCCESS || !pscan_cfg_out)
    {
        PRINTM(MERROR, "Memory allocation for pscan_cfg_out failed!\n");
        if (pioctl_req)
            pioctl_req->status_code = MLAN_ERROR_NO_MEM;
        LEAVE();
        return MLAN_STATUS_FAILURE;
    }

    buf_size = sizeof(ChanScanParamSet_t) * WLAN_USER_SCAN_CHAN_MAX;
    ret      = pcb->moal_malloc(pmadapter->pmoal_handle, buf_size, MLAN_MEM_DEF, (t_u8 **)&pscan_chan_list);
    if (ret != MLAN_STATUS_SUCCESS || !pscan_chan_list)
    {
        PRINTM(MERROR, "Failed to allocate scan_chan_list\n");
        if (pscan_cfg_out)
            pcb->moal_mfree(pmadapter->pmoal_handle, (t_u8 *)pscan_cfg_out);
        if (pioctl_req)
            pioctl_req->status_code = MLAN_ERROR_NO_MEM;
        LEAVE();
        return MLAN_STATUS_FAILURE;
    }

    (void)__memset(pmadapter, pscan_chan_list, 0x00, buf_size);
    (void)__memset(pmadapter, pscan_cfg_out, 0x00, sizeof(wlan_scan_cmd_config_tlv));

    keep_previous_scan = MFALSE;

    ret = wlan_scan_setup_scan_config(pmpriv, puser_scan_in, &pscan_cfg_out->config, &pchan_list_out, pscan_chan_list,
                                      &max_chan_per_scan, &filtered_scan, &scan_current_chan_only);
    if (ret != MLAN_STATUS_SUCCESS)
    {
        PRINTM(MERROR, "Failed to setup scan config\n");
        if (pscan_cfg_out)
            pcb->moal_mfree(pmadapter->pmoal_handle, (t_u8 *)pscan_cfg_out);
        if (pscan_chan_list)
            pcb->moal_mfree(pmadapter->pmoal_handle, (t_u8 *)pscan_chan_list);
        if (pioctl_req)
            pioctl_req->status_code = MLAN_ERROR_INVALID_PARAMETER;
        LEAVE();
        return MLAN_STATUS_FAILURE;
    }

    if (puser_scan_in)
    {
        keep_previous_scan = puser_scan_in->keep_previous_scan;
    }

    if (keep_previous_scan == MFALSE)
    {
        (void)__memset(pmadapter, pmadapter->pscan_table, 0x00, sizeof(BSSDescriptor_t) * MRVDRV_MAX_BSSID_LIST);
        pmadapter->num_in_scan_table = 0;
    }

    split_scan_in_progress = true;
    ret = wlan_scan_channel_list(pmpriv, pioctl_buf, max_chan_per_scan, filtered_scan, &pscan_cfg_out->config,
                                 pchan_list_out, pscan_chan_list);
    /* Get scan command from scan_pending_q and put to cmd_pending_q */
    if (ret == MLAN_STATUS_SUCCESS)
    {
        /* fixme: This functionality is not needed. Recheck later */
    }
    if (pscan_cfg_out)
        pcb->moal_mfree(pmadapter->pmoal_handle, (t_u8 *)pscan_cfg_out);

    if (pscan_chan_list)
        pcb->moal_mfree(pmadapter->pmoal_handle, (t_u8 *)pscan_chan_list);

    LEAVE();
    return ret;
}

/**
 *  @brief Prepare a scan command to be sent to the firmware
 *
 *  Use the wlan_scan_cmd_config sent to the command processing module in
 *   the wlan_prepare_cmd to configure a HostCmd_DS_802_11_SCAN command
 *   struct to send to firmware.
 *
 *  The fixed fields specifying the BSS type and BSSID filters as well as a
 *   variable number/length of TLVs are sent in the command to firmware.
 *
 *  @param pmpriv     A pointer to mlan_private structure
 *  @param pcmd       A pointer to HostCmd_DS_COMMAND structure to be sent to
 *                    firmware with the HostCmd_DS_801_11_SCAN structure
 *  @param pdata_buf  Void pointer cast of a wlan_scan_cmd_config struct used
 *                    to set the fields/TLVs for the command sent to firmware
 *
 *  @return           MLAN_STATUS_SUCCESS
 */
mlan_status wlan_cmd_802_11_scan(IN mlan_private *pmpriv, IN HostCmd_DS_COMMAND *pcmd, IN t_void *pdata_buf)
{
    HostCmd_DS_802_11_SCAN *pscan_cmd = &pcmd->params.scan;
    wlan_scan_cmd_config *pscan_cfg;

    ENTER();

    pscan_cfg = (wlan_scan_cmd_config *)pdata_buf;

    /* Set fixed field variables in scan command */
    pscan_cmd->bss_mode = pscan_cfg->bss_mode;
    (void)__memcpy(pmpriv->adapter, pscan_cmd->bssid, pscan_cfg->specific_bssid, sizeof(pscan_cmd->bssid));
    (void)__memcpy(pmpriv->adapter, pscan_cmd->tlv_buffer, pscan_cfg->tlv_buf, pscan_cfg->tlv_buf_len);

    pcmd->command = wlan_cpu_to_le16(HostCmd_CMD_802_11_SCAN);

    /* Size is equal to the sizeof(fixed portions) + the TLV len + header */
    pcmd->size = (t_u16)wlan_cpu_to_le16(
        (t_u16)(sizeof(pscan_cmd->bss_mode) + sizeof(pscan_cmd->bssid) + pscan_cfg->tlv_buf_len + S_DS_GEN));

    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/*
 * Fills the pointer variables with correct address.
 *
 * Original mlan stores the entire beacon. We cannot do that as it would
 * take approx 4K RAM per entry. Instead we have added some variables to
 * the original BSSDescriptor_t structure. These will keep the data needed
 * later. The pointers in this structure which would (ideally) point to
 * addresses in beacon buffer now point to these internal variables.
 *
 * Due beacon parsing a separate structure was used. That is mem-copied
 * into an entry in the static BSS_List. After this copy the internal
 * pointers still point to buffer addresses in the separate structure. We
 * will update them here.
 */
static void adjust_pointers_to_internal_buffers(BSSDescriptor_t *pbss_entry)
{
    if (pbss_entry->pht_cap != NULL)
        pbss_entry->pht_cap = &pbss_entry->ht_cap_saved;
    if (pbss_entry->pht_info != NULL)
        pbss_entry->pht_info = &pbss_entry->ht_info_saved;
    if (pbss_entry->pht_info != NULL)
        pbss_entry->pht_info = &pbss_entry->ht_info_saved;
    if (pbss_entry->pbss_co_2040 != NULL)
        pbss_entry->pbss_co_2040 = &pbss_entry->bss_co_2040_saved;
    if (pbss_entry->pwpa_ie != NULL)
        pbss_entry->pwpa_ie = (IEEEtypes_VendorSpecific_t *)pbss_entry->wpa_ie_buff;
    if (pbss_entry->prsn_ie != NULL)
        pbss_entry->prsn_ie = (IEEEtypes_Generic_t *)pbss_entry->rsn_ie_buff;
}

/**
 *  @brief This function handles the command response of scan
 *
 *   The response buffer for the scan command has the following
 *      memory layout:
 *
 *     .-------------------------------------------------------------.
 *     |  Header (4 * sizeof(t_u16)):  Standard command response hdr |
 *     .-------------------------------------------------------------.
 *     |  BufSize (t_u16) : sizeof the BSS Description data          |
 *     .-------------------------------------------------------------.
 *     |  NumOfSet (t_u8) : Number of BSS Descs returned             |
 *     .-------------------------------------------------------------.
 *     |  BSSDescription data (variable, size given in BufSize)      |
 *     .-------------------------------------------------------------.
 *     |  TLV data (variable, size calculated using Header->Size,    |
 *     |            BufSize and sizeof the fixed fields above)       |
 *     .-------------------------------------------------------------.
 *
 *  @param pmpriv       A pointer to mlan_private structure
 *  @param resp         A pointer to HostCmd_DS_COMMAND
 *  @param pioctl_buf   A pointer to mlan_ioctl_req structure
 *
 *  @return             MLAN_STATUS_SUCCESS or MLAN_STATUS_FAILURE
 */
mlan_status wlan_ret_802_11_scan(IN mlan_private *pmpriv, IN HostCmd_DS_COMMAND *resp, IN t_void *pioctl_buf)
{
    mlan_status ret            = MLAN_STATUS_SUCCESS;
    mlan_adapter *pmadapter    = pmpriv->adapter;
    mlan_callbacks *pcb        = MNULL;
    mlan_ioctl_req *pioctl_req = (mlan_ioctl_req *)pioctl_buf;
    /* cmd_ctrl_node *pcmd_node = MNULL; */
    HostCmd_DS_802_11_SCAN_RSP *pscan_rsp = MNULL;
    BSSDescriptor_t *bss_new_entry        = MNULL;
    MrvlIEtypes_Data_t *ptlv;
    MrvlIEtypes_TsfTimestamp_t *ptsf_tlv = MNULL;
    t_u8 *pbss_info;
    t_u32 scan_resp_size;
    t_u32 bytes_left;
    t_u32 num_in_table;
    t_u32 bss_idx;
    t_u32 idx;
    t_u32 tlv_buf_size;
    t_u64 tsf_val;
    chan_freq_power_t *cfp;
    MrvlIEtypes_ChanBandListParamSet_t *pchan_band_tlv = MNULL;
    ChanBandParamSet_t *pchan_band;
    t_u8 band;
    t_u8 is_bgscan_resp;
    /* t_u32 age_ts_usec; */
    t_u32 lowest_rssi_index = 0;

    ENTER();
    pcb = (pmlan_callbacks)&pmadapter->callbacks;

    is_bgscan_resp = (resp->command == HostCmd_CMD_802_11_BG_SCAN_QUERY);
    if (is_bgscan_resp)
    {
        pscan_rsp = &resp->params.bg_scan_query_resp.scan_resp;
    }
    else
    {
        pscan_rsp = &resp->params.scan_resp;
    }

    /* Note: We do not expect to have the entire list of AP's with us in
       the driver. This is because we are memory constrained. So will
       modify the handling of the AP list and keep only AP's with high RSSI */

    bytes_left = wlan_le16_to_cpu(pscan_rsp->bss_descript_size);
    PRINTM(MINFO, "SCAN_RESP: bss_descript_size %d\n", bytes_left);

    scan_resp_size = resp->size;

    PRINTM(MINFO, "SCAN_RESP: returned %d APs before parsing\n", pscan_rsp->number_of_sets);

    num_in_table = pmadapter->num_in_scan_table;
    pbss_info    = pscan_rsp->bss_desc_and_tlv_buffer;

    /*
     * The size of the TLV buffer is equal to the entire command response
     *   size (scan_resp_size) minus the fixed fields (sizeof()'s), the
     *   BSS Descriptions (bss_descript_size as bytesLef) and the command
     *   response header (S_DS_GEN)
     */
    tlv_buf_size = scan_resp_size -
                   (bytes_left + sizeof(pscan_rsp->bss_descript_size) + sizeof(pscan_rsp->number_of_sets) + S_DS_GEN);

    ptlv = (MrvlIEtypes_Data_t *)(pscan_rsp->bss_desc_and_tlv_buffer + bytes_left);

    /* Search the TLV buffer space in the scan response for any valid TLVs */
    wlan_ret_802_11_scan_get_tlv_ptrs(pmadapter, ptlv, tlv_buf_size, TLV_TYPE_TSFTIMESTAMP,
                                      (MrvlIEtypes_Data_t **)&ptsf_tlv);

    /* Search the TLV buffer space in the scan response for any valid TLVs */
    wlan_ret_802_11_scan_get_tlv_ptrs(pmadapter, ptlv, tlv_buf_size, TLV_TYPE_CHANNELBANDLIST,
                                      (MrvlIEtypes_Data_t **)&pchan_band_tlv);

    /*
     *  Process each scan response returned (pscan_rsp->number_of_sets).  Save
     *    the information in the bss_new_entry and then insert into the
     *    driver scan table either as an update to an existing entry
     *    or as an addition at the end of the table
     */
    ret = pcb->moal_malloc(pmadapter->pmoal_handle, sizeof(BSSDescriptor_t), MLAN_MEM_DEF, (t_u8 **)&bss_new_entry);

    if (ret != MLAN_STATUS_SUCCESS || !bss_new_entry)
    {
        PRINTM(MERROR, "Memory allocation for bss_new_entry failed!\n");
        if (pioctl_req)
            pioctl_req->status_code = MLAN_ERROR_NO_MEM;
        ret = MLAN_STATUS_FAILURE;
        goto done;
    }

    for (idx = 0; idx < pscan_rsp->number_of_sets && bytes_left; idx++)
    {
        /* Zero out the bss_new_entry we are about to store info in */
        (void)__memset(pmadapter, bss_new_entry, 0x00, sizeof(BSSDescriptor_t));

        /* Process the data fields and IEs returned for this BSS */
        if (wlan_interpret_bss_desc_with_ie(pmadapter, bss_new_entry, &pbss_info, &bytes_left) == MLAN_STATUS_SUCCESS)
        {
            PRINTM(MINFO, "SCAN_RESP: BSSID = %02x:%02x:%02x:%02x:%02x:%02x\n", bss_new_entry->mac_address[0],
                   bss_new_entry->mac_address[1], bss_new_entry->mac_address[2], bss_new_entry->mac_address[3],
                   bss_new_entry->mac_address[4], bss_new_entry->mac_address[5]);
            /*
             * Search the scan table for the same bssid
             */
            for (bss_idx = 0; bss_idx < num_in_table; bss_idx++)
            {
                if (!memcmp(pmadapter, bss_new_entry->mac_address, pmadapter->pscan_table[bss_idx].mac_address,
                            sizeof(bss_new_entry->mac_address)))
                {
                    /*
                     * If the SSID matches as well, it is a duplicate of
                     *   this entry.  Keep the bss_idx set to this
                     *   entry so we replace the old contents in the table
                     */
                    if ((bss_new_entry->ssid.ssid_len == pmadapter->pscan_table[bss_idx].ssid.ssid_len) &&
                        (!memcmp(pmadapter, bss_new_entry->ssid.ssid, pmadapter->pscan_table[bss_idx].ssid.ssid,
                                 bss_new_entry->ssid.ssid_len)))
                    {
                        PRINTM(MINFO, "SCAN_RESP: Duplicate of index: %d\n", bss_idx);
                        break;
                    }
                }
            }
            /*
             * If the bss_idx is equal to the number of entries in the table,
             *   the new entry was not a duplicate; append it to the scan
             *   table
             */
            if (bss_idx == num_in_table)
            {
                /* Range check the bss_idx, keep it limited to the last entry */
                if (bss_idx == MRVDRV_MAX_BSSID_LIST)
                {
                    lowest_rssi_index = wlan_find_worst_network_in_list(pmadapter->pscan_table, MRVDRV_MAX_BSSID_LIST);
                }
                else
                {
                    num_in_table++;
                }
            }

            /* fixme: Don't know if we need this right now */
            /*
             * If the TSF TLV was appended to the scan results, save
             *   this entry's TSF value in the networkTSF field.  The
             *   networkTSF is the firmware's TSF value at the time the
             *   beacon or probe response was received.
             */
            if (ptsf_tlv)
            {
                (void)__memcpy(pmpriv->adapter, &tsf_val, &ptsf_tlv->tsf_data[idx * TSF_DATA_SIZE], sizeof(tsf_val));
                tsf_val = wlan_le64_to_cpu(tsf_val);
                (void)__memcpy(pmpriv->adapter, &bss_new_entry->network_tsf, &tsf_val,
                               sizeof(bss_new_entry->network_tsf));
            }
            band = BAND_G;
            if (pchan_band_tlv)
            {
                pchan_band = &pchan_band_tlv->chan_band_param[idx];
                band       = radio_type_to_band(pchan_band->radio_type & (MBIT(0) | MBIT(1)));
            }

            /* Save the band designation for this entry for use in join */
            bss_new_entry->bss_band = band;
            cfp                     = wlan_find_cfp_by_band_and_channel(pmadapter, (t_u8)bss_new_entry->bss_band,
                                                    (t_u16)bss_new_entry->channel);

            if (cfp)
                bss_new_entry->freq = cfp->freq;
            else
                bss_new_entry->freq = 0;
            if (bss_idx == MRVDRV_MAX_BSSID_LIST)
            {
                if (pmadapter->pscan_table[lowest_rssi_index].rssi > bss_new_entry->rssi)
                {
                    (void)__memcpy(pmadapter, &pmadapter->pscan_table[lowest_rssi_index], bss_new_entry,
                                   sizeof(pmadapter->pscan_table[lowest_rssi_index]));
                    adjust_pointers_to_internal_buffers(&pmadapter->pscan_table[lowest_rssi_index]);
                }
            }
            else
            {
                /* Copy the locally created bss_new_entry to the scan table */
                (void)__memcpy(pmadapter, &pmadapter->pscan_table[bss_idx], bss_new_entry,
                               sizeof(pmadapter->pscan_table[bss_idx]));
                adjust_pointers_to_internal_buffers(&pmadapter->pscan_table[bss_idx]);
            }
        }
        else
        {
            /* Error parsing/interpreting the scan response, skipped */
            PRINTM(MERROR, "SCAN_RESP: wlan_interpret_bss_desc_with_ie returned error\n");
        }
    }

    PRINTM(MINFO, "SCAN_RESP: Scanned %2d APs, %d valid, %d total\n", pscan_rsp->number_of_sets,
           num_in_table - pmadapter->num_in_scan_table, num_in_table);

    /* Update the total number of BSSIDs in the scan table */
    pmadapter->num_in_scan_table = num_in_table;

    /* fixme: the following code does not seem relevant */

done:
    if (bss_new_entry)
        pcb->moal_mfree(pmadapter->pmoal_handle, (t_u8 *)bss_new_entry);

    LEAVE();
    return ret;
}

/**
 *  @brief This function finds ssid in ssid list.
 *
 *  @param pmpriv       A pointer to mlan_private structure
 *  @param ssid         SSID to find in the list
 *  @param bssid        BSSID to qualify the SSID selection (if provided)
 *  @param mode         Network mode: Infrastructure or IBSS
 *
 *  @return             index in BSSID list or < 0 if error
 */
t_s32 wlan_find_ssid_in_list(IN mlan_private *pmpriv, IN mlan_802_11_ssid *ssid, IN t_u8 *bssid, IN t_u32 mode)
{
    mlan_adapter *pmadapter = pmpriv->adapter;
    t_s32 net               = -1, j;
    t_u8 best_rssi          = 0;
    t_u32 i;

    ENTER();
    PRINTM(MINFO, "Num of entries in scan table = %d\n", pmadapter->num_in_scan_table);

    /*
     * Loop through the table until the maximum is reached or until a match
     *   is found based on the bssid field comparison
     */
    for (i = 0; i < pmadapter->num_in_scan_table && (!bssid || (bssid && net < 0)); i++)
    {
        if (!wlan_ssid_cmp(pmadapter, &pmadapter->pscan_table[i].ssid, ssid) &&
            (!bssid || !memcmp(pmadapter, pmadapter->pscan_table[i].mac_address, bssid, MLAN_MAC_ADDR_LENGTH)))
        {
            if (((mode == MLAN_BSS_MODE_INFRA) &&
                 !wlan_is_band_compatible(pmpriv->config_bands, pmadapter->pscan_table[i].bss_band)) ||
                (wlan_find_cfp_by_band_and_channel(pmadapter, (t_u8)pmadapter->pscan_table[i].bss_band,
                                                   (t_u16)pmadapter->pscan_table[i].channel) == MNULL))
            {
                continue;
            }

            switch (mode)
            {
                case MLAN_BSS_MODE_INFRA:
                case MLAN_BSS_MODE_IBSS:
                    j = wlan_is_network_compatible(pmpriv, i, mode);

                    if (j >= 0)
                    {
                        if (SCAN_RSSI(pmadapter->pscan_table[i].rssi) > best_rssi)
                        {
                            best_rssi = SCAN_RSSI(pmadapter->pscan_table[i].rssi);
                            net       = i;
                        }
                    }
                    else
                    {
                        if (net == -1)
                        {
                            net = j;
                        }
                    }
                    break;
                case MLAN_BSS_MODE_AUTO:
                default:
                    /*
                     * Do not check compatibility if the mode requested is
                     *   Auto/Unknown.  Allows generic find to work without
                     *   verifying against the Adapter security settings
                     */
                    if (SCAN_RSSI(pmadapter->pscan_table[i].rssi) > best_rssi)
                    {
                        best_rssi = SCAN_RSSI(pmadapter->pscan_table[i].rssi);
                        net       = i;
                    }
                    break;
            }
        }
    }

    LEAVE();
    return net;
}

/**
 *  @brief This function finds a specific compatible BSSID in the scan list
 *
 *  @param pmpriv       A pointer to mlan_private structure
 *  @param bssid        BSSID to find in the scan list
 *  @param mode         Network mode: Infrastructure or IBSS
 *
 *  @return             index in BSSID list or < 0 if error
 */
t_s32 wlan_find_bssid_in_list(IN mlan_private *pmpriv, IN t_u8 *bssid, IN t_u32 mode)
{
    mlan_adapter *pmadapter = pmpriv->adapter;
    t_s32 net               = -1;
    t_u32 i;

    ENTER();

    if (!bssid)
    {
        LEAVE();
        return -1;
    }

    PRINTM(MINFO, "FindBSSID: Num of BSSIDs = %d\n", pmadapter->num_in_scan_table);

    /*
     * Look through the scan table for a compatible match. The ret return
     *   variable will be equal to the index in the scan table (greater
     *   than zero) if the network is compatible.  The loop will continue
     *   past a matched bssid that is not compatible in case there is an
     *   AP with multiple SSIDs assigned to the same BSSID
     */
    for (i = 0; net < 0 && i < pmadapter->num_in_scan_table; i++)
    {
        if (!memcmp(pmadapter, pmadapter->pscan_table[i].mac_address, bssid, MLAN_MAC_ADDR_LENGTH))
        {
            if (((mode == MLAN_BSS_MODE_INFRA) &&
                 !wlan_is_band_compatible(pmpriv->config_bands, pmadapter->pscan_table[i].bss_band)) ||
                (wlan_find_cfp_by_band_and_channel(pmadapter, (t_u8)pmadapter->pscan_table[i].bss_band,
                                                   (t_u16)pmadapter->pscan_table[i].channel) == MNULL))
            {
                continue;
            }
            switch (mode)
            {
                case MLAN_BSS_MODE_INFRA:
                case MLAN_BSS_MODE_IBSS:
                    /* fixme: temp disable. enable after below function is enabled */
                    /* net = wlan_is_network_compatible(pmpriv, i, mode); */
                    break;
                default:
                    net = i;
                    break;
            }
        }
    }

    LEAVE();
    return net;
}

/**
 *  @brief Compare two SSIDs
 *
 *  @param pmadapter A pointer to mlan_adapter structure
 *  @param ssid1     A pointer to ssid to compare
 *  @param ssid2     A pointer to ssid to compare
 *
 *  @return         0--ssid is same, otherwise is different
 */
t_s32 wlan_ssid_cmp(IN pmlan_adapter pmadapter, IN mlan_802_11_ssid *ssid1, IN mlan_802_11_ssid *ssid2)
{
    ENTER();

    if (!ssid1 || !ssid2)
    {
        LEAVE();
        return -1;
    }

    if (ssid1->ssid_len != ssid2->ssid_len)
    {
        LEAVE();
        return -1;
    }

    LEAVE();
    return memcmp(pmadapter, ssid1->ssid, ssid2->ssid, ssid1->ssid_len);
}

static t_s32 wlan_find_worst_network_in_list(const BSSDescriptor_t *pbss_desc, t_u32 num_entries)
{
    t_u32 worst_net = 0;
    /* To start with */
    t_s32 worst_rssi = pbss_desc[worst_net].rssi;
    t_u32 i;

    ENTER();

    for (i = 1; i < num_entries; i++)
    {
        /* Smaller is better i.e. smaller rssi value here means better
           signal strength */
        if (pbss_desc[i].rssi > worst_rssi)
        {
            worst_rssi = pbss_desc[i].rssi;
            worst_net  = i;
        }
    }

    LEAVE();
    return worst_net;
}
