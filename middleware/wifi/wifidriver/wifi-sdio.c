/** @file wifi-sdio.c
 *
 *  @brief  This file provides WLAN Card related API
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

#include <mlan_api.h>

#include <mlan_sdio_api.h>

/* Additional WMSDK header files */
#include <wmerrno.h>
#include <wm_os.h>
#include <wm_utils.h>
#include <mlan_fw.h>
#include "wifi-sdio.h"
#include "wifi-internal.h"
#include "fsl_sdmmc_common.h"
#include "fsl_sdmmc_host.h"
#include "fsl_common.h"
#include "sdmmc_config.h"
#include "sdio.h"
#include "firmware_dnld.h"

/* Buffer pointers to point to command and, command response buffer */
static uint8_t cmd_buf[WIFI_FW_CMDBUF_SIZE];
t_u32 seqnum;
// static int pm_handle;

/*
 * Used to authorize the SDIO interrupt handler to accept the incoming
 * packet from the SDIO interface. If this flag is set a semaphore is
 * signalled.
 */
bool g_txrx_flag;

int mlan_subsys_init(void);

t_u8 txportno;

t_u32 last_resp_rcvd, last_cmd_sent;

static os_mutex_t txrx_mutex;
os_thread_t wifi_core_thread;

static struct
{
    /* Where the cmdresp/event should be dispached depends on its value */
    /* int special; */
    /* Default queue where the cmdresp/events will be sent */
    xQueueHandle *event_queue;
    int (*wifi_low_level_input)(const uint8_t interface, const uint8_t *buffer, const uint16_t len);
} bus;

/* fixme: This structure is not present in mlan and can be removed later */
typedef MLAN_PACK_START struct
{
    t_u16 size;
    t_u16 pkttype;
    HostCmd_DS_COMMAND hostcmd;
} MLAN_PACK_END SDIOPkt;

SDIOPkt *sdiopkt = (SDIOPkt *)outbuf;

void wrapper_wlan_cmd_11n_cfg(void *hostcmd);
void wrapper_wifi_ret_mib(void *resp);

uint32_t dev_value1 = -1;
uint8_t dev_mac_addr[MLAN_MAC_ADDR_LENGTH];
static uint8_t dev_fw_ver_ext[MLAN_MAX_VER_STR_LEN];

int wifi_sdio_lock()
{
    return os_mutex_get(&txrx_mutex, OS_WAIT_FOREVER);
}

void wifi_sdio_unlock()
{
    os_mutex_put(&txrx_mutex);
}

uint32_t wifi_get_device_value1()
{
    return dev_value1;
}

int wifi_get_device_mac_addr(wifi_mac_addr_t *mac_addr)
{
    (void)memcpy(mac_addr->mac, dev_mac_addr, MLAN_MAC_ADDR_LENGTH);
    return WM_SUCCESS;
}

int wifi_get_device_firmware_version_ext(wifi_fw_version_ext_t *fw_ver_ext)
{
    (void)memcpy(fw_ver_ext->version_str, dev_fw_ver_ext, MLAN_MAX_VER_STR_LEN);
    return WM_SUCCESS;
}

/* Initializes the driver struct */
static int wlan_init_struct()
{
    if (txrx_mutex == NULL)
    {
        int status = os_mutex_create(&txrx_mutex, "txrx", OS_MUTEX_INHERIT);
        if (status != WM_SUCCESS)
            return status;
    }
    return WM_SUCCESS;
}

int raw_process_pkt_hdrs(void *pbuf, t_u32 payloadlen, t_u8 interface)
{
    mlan_private *pmpriv = (mlan_private *)mlan_adap->priv[0];
    SDIOPkt *sdiohdr     = (SDIOPkt *)pbuf;
    TxPD *ptxpd          = (TxPD *)((uint8_t *)pbuf + INTF_HEADER_LEN);

    ptxpd->bss_type      = interface;
    ptxpd->bss_num       = GET_BSS_NUM(pmpriv);
    ptxpd->tx_pkt_offset = 0x14; /* we'll just make this constant */
    ptxpd->tx_pkt_length = payloadlen - ptxpd->tx_pkt_offset - INTF_HEADER_LEN;
    ptxpd->tx_pkt_type   = 0xE5;
    ptxpd->tx_control    = 0;
    ptxpd->priority      = 0;
    ptxpd->flags         = 0;
    ptxpd->pkt_delay_2ms = 0;

    sdiohdr->size = payloadlen + ptxpd->tx_pkt_offset + INTF_HEADER_LEN;

    return ptxpd->tx_pkt_offset + INTF_HEADER_LEN;
}

/*
 * fixme: mlan_sta_tx.c can be used directly here. This functionality is
 * already present there.
 */
/* SDIO  TxPD  PAYLOAD | 4 | 22 | payload | */

void process_pkt_hdrs(void *pbuf, t_u32 payloadlen, t_u8 interface)
{
    mlan_private *pmpriv = (mlan_private *)mlan_adap->priv[0];
    SDIOPkt *sdiohdr     = (SDIOPkt *)pbuf;
    TxPD *ptxpd          = (TxPD *)((uint8_t *)pbuf + INTF_HEADER_LEN);
#ifdef CONFIG_WMM
    t_u8 *data_ptr = (t_u8 *)pbuf;
#endif
    ptxpd->bss_type      = interface;
    ptxpd->bss_num       = GET_BSS_NUM(pmpriv);
    ptxpd->tx_pkt_offset = 0x16; /* we'll just make this constant */
    ptxpd->tx_pkt_length = payloadlen - ptxpd->tx_pkt_offset - INTF_HEADER_LEN;
    if (ptxpd->tx_pkt_type == 0xe5)
    {
        ptxpd->tx_pkt_offset = 0x14; /* Override for special frame */
        payloadlen -= ptxpd->tx_pkt_offset + INTF_HEADER_LEN;
    }
    ptxpd->tx_control = 0;
#ifdef CONFIG_WMM
    t_u8 type_ip_offset = ptxpd->tx_pkt_offset + INTF_HEADER_LEN + MLAN_MAC_ADDR_LENGTH + MLAN_MAC_ADDR_LENGTH;
    if (data_ptr[type_ip_offset] == 0x8 && data_ptr[type_ip_offset + 1] == 0x0)
        ptxpd->priority = (data_ptr[type_ip_offset + 3] / 32);
    else
        ptxpd->priority = 0;
#else
    ptxpd->priority = 0;
#endif
    ptxpd->flags         = 0;
    ptxpd->pkt_delay_2ms = 0;

    sdiohdr->size = payloadlen;
}

int bus_register_event_queue(xQueueHandle *event_queue)
{
    if (bus.event_queue != NULL)
        return -WM_FAIL;

    bus.event_queue = event_queue;

    return WM_SUCCESS;
}

void bus_deregister_event_queue()
{
    if (bus.event_queue != NULL)
        bus.event_queue = NULL;
}

int bus_register_data_input_function(int (*wifi_low_level_input)(const uint8_t interface,
                                                                 const uint8_t *buffer,
                                                                 const uint16_t len))
{
    if (bus.wifi_low_level_input != NULL)
        return -WM_FAIL;

    bus.wifi_low_level_input = wifi_low_level_input;

    return WM_SUCCESS;
}

void bus_deregister_data_input_funtion(void)
{
    bus.wifi_low_level_input = NULL;
}

void wifi_get_mac_address_from_cmdresp(void *resp, t_u8 *mac_addr);
void wifi_get_firmware_ver_ext_from_cmdresp(void *resp, t_u8 *fw_ver_ext);
void wifi_get_value1_from_cmdresp(void *resp, uint32_t *dev_value1);
mlan_status wlan_handle_cmd_resp_packet(t_u8 *pmbuf)
{
    HostCmd_DS_GEN *cmdresp;
    t_u32 cmdtype;

    cmdresp = (HostCmd_DS_GEN *)(pmbuf + INTF_HEADER_LEN); /* size + pkttype=4 */
    cmdtype = cmdresp->command & HostCmd_CMD_ID_MASK;

    last_resp_rcvd = cmdtype;

    if ((cmdresp->command & 0xf000) != 0x8000)
    {
        wifi_io_d("cmdresp->command = (0x%x)", cmdresp->command);
    }

    /* Do not process response of wlan firmware shutdown command
     *
     * This is required to flush out any previous response
     * from the wlan_deinit() which might have been called
     * prior to this.
     *
     */
    if ((cmdresp->command & 0x00ff) == HostCmd_CMD_FUNC_SHUTDOWN)
        return MLAN_STATUS_SUCCESS;

    if ((cmdresp->command & 0x0fff) != last_cmd_sent)
    {
        wifi_io_d("cmdresp->command = (0x%x) last_cmd_sent = (0x%x)", cmdresp->command, last_cmd_sent);
    }

    if (cmdresp->result != 0U)
    {
        wifi_io_d("cmdresp->result = (0x%x)", cmdresp->result);
    }

    wifi_io_d("Resp : (0x%x)", cmdtype);
    switch (cmdtype)
    {
        case HostCmd_CMD_MAC_CONTROL:
        case HostCmd_CMD_FUNC_INIT:
        case HostCmd_CMD_CFG_DATA:
            break;
        case HostCmd_CMD_MAC_REG_ACCESS:
            wifi_get_value1_from_cmdresp(cmdresp, &dev_value1);
            break;
        case HostCmd_CMD_802_11_MAC_ADDRESS:
            wifi_get_mac_address_from_cmdresp(cmdresp, dev_mac_addr);
            break;
#ifdef OTP_CHANINFO
        case HostCmd_CMD_CHAN_REGION_CFG:
            wlan_ret_chan_region_cfg((mlan_private *)mlan_adap->priv[0], (HostCmd_DS_COMMAND *)cmdresp, NULL);
            break;
#endif
        case HostCmd_CMD_GET_HW_SPEC:
            wlan_ret_get_hw_spec((mlan_private *)mlan_adap->priv[0], (HostCmd_DS_COMMAND *)cmdresp, NULL);
            break;
        case HostCmd_CMD_VERSION_EXT:
            wifi_get_firmware_ver_ext_from_cmdresp(cmdresp, dev_fw_ver_ext);
            break;
        case HostCmd_CMD_11N_CFG:
        case HostCmd_CMD_AMSDU_AGGR_CTRL:
            break;
        case HostCmd_CMD_FUNC_SHUTDOWN:
            break;
#ifdef WLAN_LOW_POWER_ENABLE
        case HostCmd_CMD_LOW_POWER_MODE:
            break;
#endif
        case HostCmd_CMD_ED_MAC_MODE:
        case HostCmd_CMD_CHANNEL_TRPC_CONFIG:
            break;
        default:
            wifi_io_d("Unimplemented Resp : (0x%x)", cmdtype);
#ifdef CONFIG_WIFI_IO_DUMP
            dump_hex(cmdresp, cmdresp->size);
#endif
            break;
    }

    return MLAN_STATUS_SUCCESS;
}

/*
 * Accepts event and command packets. Redirects them to queues if
 * registered. If queues are not registered (as is the case during
 * initialization then the packet is given to lower layer cmd/event
 * handling part.
 */
static mlan_status wlan_decode_rx_packet(t_u8 *pmbuf, t_u32 upld_type)
{
    if (upld_type == MLAN_TYPE_DATA)
        return MLAN_STATUS_FAILURE;

    if (upld_type == MLAN_TYPE_CMD)
        wifi_io_d("  --- Rx: Cmd Response ---");
    else
        wifi_io_d(" --- Rx: EVENT Response ---");

    SDIOPkt *sdiopkt = (SDIOPkt *)pmbuf;
    int ret;
    struct bus_message msg;

    if (bus.event_queue != NULL)
    {
        if (upld_type == MLAN_TYPE_CMD)
            msg.data = wifi_mem_malloc_cmdrespbuf(sdiopkt->size);
        else
            msg.data = wifi_malloc_eventbuf(sdiopkt->size);

        if (!msg.data)
        {
            wifi_io_e("[fail] Buffer alloc: T: %d S: %d", upld_type, sdiopkt->size);
            return MLAN_STATUS_FAILURE;
        }

        msg.event = upld_type;
        (void)memcpy(msg.data, pmbuf, sdiopkt->size);

        ret = os_queue_send(bus.event_queue, &msg, os_msec_to_ticks(WIFI_RESP_WAIT_TIME));

        if (ret != WM_SUCCESS)
        {
            wifi_io_e("Failed to send response on Queue");
            return MLAN_STATUS_FAILURE;
        }
    }
    else
    {
        /* No queues registered yet. Use local handling */
        wlan_handle_cmd_resp_packet(pmbuf);
    }

    return MLAN_STATUS_SUCCESS;
}

t_u32 get_ioport()
{
    return mlan_adap->ioport;
}

static t_u8 *wlan_read_rcv_packet(t_u32 port, t_u32 rxlen, t_u32 rx_blocks, t_u32 *type, bool aggr)
{
    t_u32 blksize = MLAN_SDIO_BLOCK_SIZE;
    uint32_t resp;
    int ret;
#ifdef CONFIG_SDIO_MULTI_PORT_RX_AGGR
    int i = 0;

retry_read:
    /* addr = 0 fn = 1 */
    ret = sdio_drv_read(port, 1, rx_blocks, blksize, inbuf, &resp);

    if (aggr && !ret)
    {
        wifi_d("sdio mp cmd53 read failed: %d ioport=0x%x retry=%d\r\n", ret, port, i);
        i++;
        if (!sdio_drv_creg_write(HOST_TO_CARD_EVENT_REG, 1, HOST_TERM_CMD53, &resp))
            wifi_d("Set Term cmd53 failed\r\n");
        if (i > MAX_READ_IOMEM_RETRY)
        {
            wifi_io_e("sdio_drv_read failed (%d)", ret);
#ifdef CONFIG_WIFI_FW_DEBUG
            wifi_sdio_reg_dbg(NULL);
            if (wm_wifi.wifi_usb_mount_cb != NULL)
            {
                ret = wm_wifi.wifi_usb_mount_cb();
                if (ret == WM_SUCCESS)
                    wifi_dump_firmware_info(NULL);
                else
                    wifi_e("USB mounting failed");
            }
            else
                wifi_e("USB mount callback is not registered");
#endif
            return NULL;
        }
        goto retry_read;
    }
#else
    /* addr = 0 fn = 1 */
    ret = sdio_drv_read(port, 1, rx_blocks, blksize, inbuf, &resp);
    if (!ret)
    {
        wifi_io_e("sdio_drv_read failed (%d)", ret);
#ifdef CONFIG_WIFI_FW_DEBUG
        wifi_sdio_reg_dbg(NULL);
        if (wm_wifi.wifi_usb_mount_cb != NULL)
        {
            ret = wm_wifi.wifi_usb_mount_cb();
            if (ret == WM_SUCCESS)
                wifi_dump_firmware_info(NULL);
            else
                wifi_e("USB mounting failed");
        }
        else
            wifi_e("USB mount callback is not registered");

#endif
        return NULL;
    }
#endif

    SDIOPkt *insdiopkt = (SDIOPkt *)inbuf;
    *type              = insdiopkt->pkttype;

#ifdef CONFIG_WIFI_IO_DUMP
    if (insdiopkt->pkttype != 0)
    {
        (void)PRINTF("wlan_read_rcv_packet: DUMP:");
        dump_hex((t_u8 *)inbuf, rx_blocks * blksize);
    }
#endif /* CONFIG_WIFI_IO_DUMP */

    return inbuf;
}

static t_u32 wlan_get_next_seq_num()
{
    seqnum++;
    return seqnum;
}

void wifi_prepare_set_cal_data_cmd(void *cmd, int seq_number);
static int _wlan_set_cal_data()
{
    t_u32 tx_blocks = 4, buflen = MLAN_SDIO_BLOCK_SIZE;
    uint32_t resp;

    (void)memset(outbuf, 0, SDIO_OUTBUF_LEN);

    /* sdiopkt = outbuf */
    wifi_prepare_set_cal_data_cmd(&sdiopkt->hostcmd, wlan_get_next_seq_num());

    sdiopkt->pkttype = MLAN_TYPE_CMD;
    sdiopkt->size    = sdiopkt->hostcmd.size + INTF_HEADER_LEN;

    last_cmd_sent = HostCmd_CMD_CFG_DATA;

    /* send CMD53 to write the command to get mac address */
#if defined(SD8801)
    sdio_drv_write(mlan_adap->ioport, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    sdio_drv_write(mlan_adap->ioport | CMD_PORT_SLCT, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#endif

    return true;
}

void wifi_prepare_reconfigure_tx_buf_cmd(HostCmd_DS_COMMAND *cmd, int seq_number);

static int _wlan_reconfigure_tx_buffers()
{
    t_u32 tx_blocks = 4, buflen = MLAN_SDIO_BLOCK_SIZE;
    uint32_t resp;

    (void)memset(outbuf, 0, SDIO_OUTBUF_LEN);

    /* sdiopkt = outbuf */
    wifi_prepare_reconfigure_tx_buf_cmd(&sdiopkt->hostcmd, wlan_get_next_seq_num());
    sdiopkt->pkttype = MLAN_TYPE_CMD;
    sdiopkt->size    = sdiopkt->hostcmd.size + INTF_HEADER_LEN;

    last_cmd_sent = HostCmd_CMD_RECONFIGURE_TX_BUFF;

    /* send CMD53 to write the command to get mac address */
#if defined(SD8801)
    sdio_drv_write(mlan_adap->ioport, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    sdio_drv_write(mlan_adap->ioport | CMD_PORT_SLCT, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#endif

    return true;
}

void wifi_prepare_get_mac_addr_cmd(void *cmd, int seq_number);
void wifi_prepare_get_channel_region_cfg_cmd(HostCmd_DS_COMMAND *cmd, int seq_number);
void wifi_prepare_get_hw_spec_cmd(HostCmd_DS_COMMAND *cmd, int seq_number);

#ifdef OTP_CHANINFO
static int wlan_get_channel_region_cfg()
{
    uint32_t tx_blocks = 1, buflen = MLAN_SDIO_BLOCK_SIZE;
    uint32_t resp;
    (void)memset(outbuf, 0, buflen);
    /* sdiopkt = outbuf */
    wifi_prepare_get_channel_region_cfg_cmd(&sdiopkt->hostcmd, wlan_get_next_seq_num());

    sdiopkt->pkttype = MLAN_TYPE_CMD;
    sdiopkt->size    = sdiopkt->hostcmd.size + INTF_HEADER_LEN;

    last_cmd_sent = HostCmd_CMD_CHAN_REGION_CFG;
#if defined(SD8801)
    sdio_drv_write(mlan_adap->ioport, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    sdio_drv_write(mlan_adap->ioport | CMD_PORT_SLCT, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#endif

    return true;
}
#endif

static int wlan_get_hw_spec()
{
    uint32_t tx_blocks = 1, buflen = MLAN_SDIO_BLOCK_SIZE;
    uint32_t resp;
    (void)memset(outbuf, 0, buflen);
    /* sdiopkt = outbuf */
    wifi_prepare_get_hw_spec_cmd(&sdiopkt->hostcmd, wlan_get_next_seq_num());

    sdiopkt->pkttype = MLAN_TYPE_CMD;
    sdiopkt->size    = sdiopkt->hostcmd.size + INTF_HEADER_LEN;

    last_cmd_sent = HostCmd_CMD_GET_HW_SPEC;
#if defined(SD8801)
    sdio_drv_write(mlan_adap->ioport, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    sdio_drv_write(mlan_adap->ioport | CMD_PORT_SLCT, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#endif

    return true;
}

static int wlan_get_mac_addr()
{
    t_u32 tx_blocks = 1, buflen = MLAN_SDIO_BLOCK_SIZE;
    uint32_t resp;

    (void)memset(outbuf, 0, buflen);

    /* sdiopkt = outbuf */
    wifi_prepare_get_mac_addr_cmd(&sdiopkt->hostcmd, wlan_get_next_seq_num());

    sdiopkt->pkttype = MLAN_TYPE_CMD;
    sdiopkt->size    = sdiopkt->hostcmd.size + INTF_HEADER_LEN;

    last_cmd_sent = HostCmd_CMD_802_11_MAC_ADDRESS;

    /* send CMD53 to write the command to get mac address */
#if defined(SD8801)
    sdio_drv_write(mlan_adap->ioport, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    sdio_drv_write(mlan_adap->ioport | CMD_PORT_SLCT, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#endif

    return true;
}

void wifi_prepare_get_fw_ver_ext_cmd(void *cmd, int seq_number, int version_str_sel);
static int wlan_get_fw_ver_ext(int version_str_sel)
{
    t_u32 tx_blocks = 1, buflen = MLAN_SDIO_BLOCK_SIZE;
    uint32_t resp;

    (void)memset(outbuf, 0, buflen);

    /* sdiopkt = outbuf */
    wifi_prepare_get_fw_ver_ext_cmd(&sdiopkt->hostcmd, wlan_get_next_seq_num(), version_str_sel);

    sdiopkt->pkttype = MLAN_TYPE_CMD;
    sdiopkt->size    = sdiopkt->hostcmd.size + INTF_HEADER_LEN;

    last_cmd_sent = HostCmd_CMD_VERSION_EXT;

    /* send CMD53 to write the command to get mac address */
#if defined(SD8801)
    sdio_drv_write(mlan_adap->ioport, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    sdio_drv_write(mlan_adap->ioport | CMD_PORT_SLCT, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#endif

    return true;
}

void wifi_prepare_get_value1(void *cmd, int seq_number);

static int wlan_get_value1()
{
    t_u32 tx_blocks = 1, buflen = MLAN_SDIO_BLOCK_SIZE;
    uint32_t resp;

    (void)memset(outbuf, 0, buflen);

    /* sdiopkt = outbuf */
    wifi_prepare_get_value1(&sdiopkt->hostcmd, wlan_get_next_seq_num());

    sdiopkt->pkttype = MLAN_TYPE_CMD;
    sdiopkt->size    = sdiopkt->hostcmd.size + INTF_HEADER_LEN;

    last_cmd_sent = HostCmd_CMD_MAC_REG_ACCESS;

#if defined(SD8801)
    sdio_drv_write(mlan_adap->ioport, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    sdio_drv_write(mlan_adap->ioport | CMD_PORT_SLCT, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#endif

    return true;
}

void wifi_prepare_set_mac_addr_cmd(void *cmd, int seq_number);
static int _wlan_set_mac_addr()
{
    t_u32 tx_blocks = 1, buflen = MLAN_SDIO_BLOCK_SIZE;
    uint32_t resp;

    (void)memset(outbuf, 0, buflen);

    /* sdiopkt = outbuf */
    wifi_prepare_set_mac_addr_cmd(&sdiopkt->hostcmd, wlan_get_next_seq_num());

    sdiopkt->pkttype = MLAN_TYPE_CMD;
    sdiopkt->size    = sdiopkt->hostcmd.size + INTF_HEADER_LEN;

    last_cmd_sent = HostCmd_CMD_802_11_MAC_ADDRESS;

    /* send CMD53 to write the command to get mac address */
#if defined(SD8801)
    sdio_drv_write(mlan_adap->ioport, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    sdio_drv_write(mlan_adap->ioport | CMD_PORT_SLCT, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#endif

    return true;
}

static int wlan_set_11n_cfg()
{
    t_u32 tx_blocks = 1, buflen = MLAN_SDIO_BLOCK_SIZE;
    uint32_t resp;

    (void)memset(outbuf, 0, SDIO_OUTBUF_LEN);
    wrapper_wlan_cmd_11n_cfg(&sdiopkt->hostcmd);
    /* sdiopkt = outbuf */
    sdiopkt->hostcmd.seq_num = wlan_get_next_seq_num();
    sdiopkt->pkttype         = MLAN_TYPE_CMD;
    last_cmd_sent            = HostCmd_CMD_11N_CFG;

#if defined(SD8801)
    sdio_drv_write(mlan_adap->ioport, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    sdio_drv_write(mlan_adap->ioport | CMD_PORT_SLCT, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#endif

    return true;
}

void wifi_prepare_enable_amsdu_cmd(void *cmd, int seq_number);
static int wlan_enable_amsdu()
{
    t_u32 tx_blocks = 1, buflen = MLAN_SDIO_BLOCK_SIZE;
    uint32_t resp;

    (void)memset(outbuf, 0, buflen);

    /* sdiopkt = outbuf */
    wifi_prepare_enable_amsdu_cmd(&sdiopkt->hostcmd, wlan_get_next_seq_num());

    sdiopkt->pkttype = MLAN_TYPE_CMD;
    sdiopkt->size    = sdiopkt->hostcmd.size + INTF_HEADER_LEN;

    last_cmd_sent = HostCmd_CMD_AMSDU_AGGR_CTRL;

#if defined(SD8801)
    sdio_drv_write(mlan_adap->ioport, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    sdio_drv_write(mlan_adap->ioport | CMD_PORT_SLCT, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#endif

    return true;
}

static int wlan_cmd_shutdown()
{
    t_u32 tx_blocks = 1, buflen = MLAN_SDIO_BLOCK_SIZE;
    uint32_t resp;

    (void)memset(outbuf, 0, buflen);

    /* sdiopkt = outbuf */
    sdiopkt->hostcmd.command = HostCmd_CMD_FUNC_SHUTDOWN;
    sdiopkt->hostcmd.size    = S_DS_GEN;
    sdiopkt->hostcmd.seq_num = wlan_get_next_seq_num();
    sdiopkt->hostcmd.result  = 0;

    sdiopkt->pkttype = MLAN_TYPE_CMD;
    sdiopkt->size    = sdiopkt->hostcmd.size + INTF_HEADER_LEN;

    last_cmd_sent = HostCmd_CMD_FUNC_SHUTDOWN;

    sdio_drv_write(mlan_adap->ioport, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);

    return true;
}

void wlan_prepare_mac_control_cmd(void *cmd, int seq_number);
static int wlan_set_mac_ctrl()
{
    t_u32 tx_blocks = 1, buflen = MLAN_SDIO_BLOCK_SIZE;
    uint32_t resp;

    (void)memset(outbuf, 0, buflen);

    /* sdiopkt = outbuf */
    wlan_prepare_mac_control_cmd(&sdiopkt->hostcmd, wlan_get_next_seq_num());

    sdiopkt->pkttype = MLAN_TYPE_CMD;
    sdiopkt->size    = sdiopkt->hostcmd.size + INTF_HEADER_LEN;

    last_cmd_sent = HostCmd_CMD_MAC_CONTROL;

    /* send CMD53 to write the command to set mac control */
#if defined(SD8801)
    sdio_drv_write(mlan_adap->ioport, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    sdio_drv_write(mlan_adap->ioport | CMD_PORT_SLCT, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#endif

    return true;
}

static int wlan_cmd_init()
{
    t_u32 tx_blocks = 1, buflen = MLAN_SDIO_BLOCK_SIZE;
    uint32_t resp;

    (void)memset(outbuf, 0, buflen);

    /* sdiopkt = outbuf */
    sdiopkt->hostcmd.command = HostCmd_CMD_FUNC_INIT;
    sdiopkt->hostcmd.size    = S_DS_GEN;
    sdiopkt->hostcmd.seq_num = wlan_get_next_seq_num();
    sdiopkt->hostcmd.result  = 0;

    sdiopkt->pkttype = MLAN_TYPE_CMD;
    sdiopkt->size    = sdiopkt->hostcmd.size + INTF_HEADER_LEN;

    last_cmd_sent = HostCmd_CMD_FUNC_INIT;

#if defined(SD8801)
    sdio_drv_write(mlan_adap->ioport, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    sdio_drv_write(mlan_adap->ioport | CMD_PORT_SLCT, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#endif

    return true;
}

#ifdef WLAN_LOW_POWER_ENABLE
void wifi_prepare_low_power_mode_cmd(HostCmd_DS_COMMAND *cmd, int seq_number);
static int wlan_set_low_power_mode()
{
    t_u32 tx_blocks = 1, buflen = MLAN_SDIO_BLOCK_SIZE;
    uint32_t resp;

    (void)memset(outbuf, 0, buflen);

    /* sdiopkt = outbuf */

    wifi_prepare_low_power_mode_cmd(&sdiopkt->hostcmd, wlan_get_next_seq_num());

    sdiopkt->pkttype = MLAN_TYPE_CMD;
    sdiopkt->size    = sdiopkt->hostcmd.size + INTF_HEADER_LEN;

    last_cmd_sent = HostCmd_CMD_LOW_POWER_MODE;

    sdio_drv_write(mlan_adap->ioport, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
    return true;
}
#endif

mlan_status wlan_process_int_status(mlan_adapter *pmadapter);
/* Setup the firmware with commands */
static void wlan_fw_init_cfg()
{
    wifi_io_d("FWCMD : INIT (0xa9)");

    wlan_cmd_init();

    while (last_resp_rcvd != HostCmd_CMD_FUNC_INIT)
    {
        os_thread_sleep(os_msec_to_ticks(10));
        wlan_process_int_status(mlan_adap);
    }

#ifdef WLAN_LOW_POWER_ENABLE
    if (low_power_mode)
    {
        wifi_io_d("CMD : LOW_POWER_MODE (0x128)");

        wlan_set_low_power_mode();

        while (last_resp_rcvd != HostCmd_CMD_LOW_POWER_MODE)
        {
            os_thread_sleep(os_msec_to_ticks(10));
            wlan_process_int_status(mlan_adap);
        }
    }
#endif
    if (cal_data_valid)
    {
        PRINTF("Setting up new cal data\r\n");
        wifi_io_d("CMD : SET_CAL_DATA (0x8f)");

        _wlan_set_cal_data();

        while (last_resp_rcvd != HostCmd_CMD_CFG_DATA)
        {
            os_thread_sleep(os_msec_to_ticks(10));
            wlan_process_int_status(mlan_adap);
        }
        /* When cal data set command is sent, fimrware looses alignment of SDIO Tx buffers.
         * So we need to send reconfigure command. This can be removed if fix is added in firmware.
         */
        _wlan_reconfigure_tx_buffers();

        while (last_resp_rcvd != HostCmd_CMD_RECONFIGURE_TX_BUFF)
        {
            os_thread_sleep(os_msec_to_ticks(10));
            wlan_process_int_status(mlan_adap);
        }
    }

    if (mac_addr_valid)
    {
        wifi_io_d("CMD : SET_MAC_ADDR (0x4d)");

        _wlan_set_mac_addr();

        while (last_resp_rcvd != HostCmd_CMD_802_11_MAC_ADDRESS)
        {
            os_thread_sleep(os_msec_to_ticks(10));
            wlan_process_int_status(mlan_adap);
        }
    }

#ifdef OTP_CHANINFO
    wifi_io_d("CMD : Channel Region CFG (0x0242)");

    wlan_get_channel_region_cfg();

    while (last_resp_rcvd != HostCmd_CMD_CHAN_REGION_CFG)
    {
        os_thread_sleep(os_msec_to_ticks(10));
        wlan_process_int_status(mlan_adap);
    }
#endif

    wifi_io_d("CMD : GET_HW_SPEC (0x03)");

    wlan_get_hw_spec();

    while (last_resp_rcvd != HostCmd_CMD_GET_HW_SPEC)
    {
        os_thread_sleep(os_msec_to_ticks(10));
        wlan_process_int_status(mlan_adap);
    }

    wlan_get_value1();

    while (last_resp_rcvd != HostCmd_CMD_MAC_REG_ACCESS)
    {
        os_thread_sleep(os_msec_to_ticks(10));
        wlan_process_int_status(mlan_adap);
    }

    wifi_io_d("CMD : GET_FW_VER_EXT (0x97)");

    wlan_get_fw_ver_ext(0);

    while (last_resp_rcvd != HostCmd_CMD_VERSION_EXT)
    {
        os_thread_sleep(os_msec_to_ticks(10));
        wlan_process_int_status(mlan_adap);
    }

    wifi_io_d("CMD : GET_MAC_ADDR (0x4d)");

    wlan_get_mac_addr();

    while (last_resp_rcvd != HostCmd_CMD_802_11_MAC_ADDRESS)
    {
        os_thread_sleep(os_msec_to_ticks(10));
        wlan_process_int_status(mlan_adap);
    }

    wifi_io_d("CMD : GET_FW_VER_EXT (0x97)");

    wlan_get_fw_ver_ext(3);

    while (last_resp_rcvd != HostCmd_CMD_VERSION_EXT)
    {
        os_thread_sleep(os_msec_to_ticks(10));
        wlan_process_int_status(mlan_adap);
    }

    wifi_io_d("CMD : MAC_CTRL (0x28)");

    wlan_set_mac_ctrl();

    while (last_resp_rcvd != HostCmd_CMD_MAC_CONTROL)
    {
        os_thread_sleep(os_msec_to_ticks(10));
        wlan_process_int_status(mlan_adap);
    }

    wifi_io_d("CMD : GET_FW_VER_EXT (0x97)");

    wlan_get_fw_ver_ext(4);

    while (last_resp_rcvd != HostCmd_CMD_VERSION_EXT)
    {
        os_thread_sleep(os_msec_to_ticks(10));
        wlan_process_int_status(mlan_adap);
    }

    wlan_set_11n_cfg();

    while (last_resp_rcvd != HostCmd_CMD_11N_CFG)
    {
        os_thread_sleep(os_msec_to_ticks(1));
        wlan_process_int_status(mlan_adap);
    }

    wlan_enable_amsdu();

    while (last_resp_rcvd != HostCmd_CMD_AMSDU_AGGR_CTRL)
    {
        os_thread_sleep(os_msec_to_ticks(1));
        wlan_process_int_status(mlan_adap);
    }

    return;
}

int wlan_send_sdio_cmd(t_u8 *buf, t_u32 tx_blocks, t_u32 buflen)
{
    SDIOPkt *sdio = (SDIOPkt *)outbuf;
    uint32_t resp;

    wifi_sdio_lock();

    (void)memcpy(outbuf, buf, tx_blocks * buflen);
    sdio->pkttype = MLAN_TYPE_CMD;
    sdio->size    = sdio->hostcmd.size + INTF_HEADER_LEN;

#ifdef CONFIG_WIFI_IO_DUMP
    (void)PRINTF("OUT_CMD");
    dump_hex(outbuf, sdio->size);
#endif /* CONFIG_WIFI_IO_DUMP */
#if defined(SD8801)
    sdio_drv_write(mlan_adap->ioport, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    sdio_drv_write(mlan_adap->ioport | CMD_PORT_SLCT, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#endif

    last_cmd_sent = sdio->hostcmd.command;
    wifi_sdio_unlock();

    return WM_SUCCESS;
}

int wifi_send_cmdbuffer(t_u32 tx_blocks, t_u32 len)
{
    return wlan_send_sdio_cmd(cmd_buf, tx_blocks, len);
}

t_u16 get_mp_end_port(void);
#ifdef CONFIG_WMM
extern int retry_attempts;

static int get_free_port(void)
{
    /* Check if the port is available */
    if (!((1 << txportno) & mlan_adap->mp_wr_bitmap))
    {
#ifdef CONFIG_WIFI_IO_DEBUG
        wifi_io_e(
            "txportno out of sync txportno "
            "= (%d) mp_wr_bitmap = (0x%x)",
            txportno, mlan_adap->mp_wr_bitmap);
#endif /* CONFIG_WIFI_IO_DEBUG */

        return -WM_FAIL;
    }
    else
    {
        /* Mark the port number we will use */
        mlan_adap->mp_wr_bitmap &= ~(1 << txportno);
    }
    return WM_SUCCESS;
}

mlan_status wlan_xmit_wmm_pkt(t_u8 interface, t_u32 txlen, t_u8 *tx_buf)
{
    t_u32 tx_blocks = 0, buflen = 0;
    uint32_t resp;
    int ret   = false;
    int retry = retry_attempts;
    wifi_io_info_d("OUT: i/f: %d len: %d", interface, tx_blocks * buflen);

    calculate_sdio_write_params(txlen, &tx_blocks, &buflen);
#ifdef CONFIG_WIFI_IO_DEBUG
    (void)PRINTF("%s: txportno = %d mlan_adap->mp_wr_bitmap: %x\n\r", __func__, txportno, mlan_adap->mp_wr_bitmap);
#endif /* CONFIG_WIFI_IO_DEBUG */
retry_xmit:
    wifi_sdio_lock();
    ret = get_free_port();
    if (ret == -WM_FAIL)
    {
        wifi_sdio_unlock();
        if (!retry)
        {
            return MLAN_STATUS_FAILURE;
        }
        else
        {
            retry--;
            /* Allow the other thread to run and hence
             * update the write bitmap so that pkt
             * can be sent to FW */
            os_thread_sleep(1);
            goto retry_xmit;
        }
    }
    process_pkt_hdrs(tx_buf, txlen, interface);
    /* send CMD53 */
    ret = sdio_drv_write(mlan_adap->ioport + txportno, 1, tx_blocks, buflen, tx_buf, &resp);

    txportno++;
    if (txportno == mlan_adap->mp_end_port)
    {
#if defined(SD8801)
        txportno = 1;
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
        txportno = 0;
#endif
    }

    if (ret == false)
    {
        wifi_io_e("sdio_drv_write failed (%d)", ret);
#ifdef CONFIG_WIFI_FW_DEBUG
        wifi_sdio_reg_dbg(NULL);
        if (wm_wifi.wifi_usb_mount_cb != NULL)
        {
            ret = wm_wifi.wifi_usb_mount_cb();
            if (ret == WM_SUCCESS)
                wifi_dump_firmware_info(NULL);
            else
                wifi_e("USB mounting failed");
        }
        else
            wifi_e("USB mount callback is not registered");
#endif
        wifi_sdio_unlock();
        return MLAN_STATUS_FAILURE;
    }

    wifi_sdio_unlock();
    return MLAN_STATUS_SUCCESS;
}
#endif
mlan_status wlan_xmit_pkt(t_u32 txlen, t_u8 interface)
{
    t_u32 tx_blocks = 0, buflen = 0;
    uint32_t resp;
    int ret;

    wifi_io_info_d("OUT: i/f: %d len: %d", interface, txlen);
    calculate_sdio_write_params(txlen, &tx_blocks, &buflen);
#ifdef CONFIG_WIFI_IO_DEBUG
    (void)PRINTF("%s: txportno = %d mlan_adap->mp_wr_bitmap: %x\n\r", __func__, txportno, mlan_adap->mp_wr_bitmap);
#endif /* CONFIG_WIFI_IO_DEBUG */
    /* Check if the port is available */
    if (!((1 << txportno) & mlan_adap->mp_wr_bitmap))
    {
        /*
         * fixme: This condition is triggered in legacy as well as
         * this new code. Check this out later.
         */
#ifdef CONFIG_WIFI_IO_DEBUG
        wifi_io_e(
            "txportno out of sync txportno "
            "= (%d) mp_wr_bitmap = (0x%x)",
            txportno, mlan_adap->mp_wr_bitmap);
#endif /* CONFIG_WIFI_IO_DEBUG */
        return MLAN_STATUS_RESOURCE;
    }
    else
    {
        /* Mark the port number we will use */
        mlan_adap->mp_wr_bitmap &= ~(1 << txportno);
    }
    process_pkt_hdrs((t_u8 *)outbuf, txlen, interface);
    /* send CMD53 */
    ret = sdio_drv_write(mlan_adap->ioport + txportno, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);

    txportno++;
    if (txportno == mlan_adap->mp_end_port)
#if defined(SD8801)
        txportno = 1;
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
        txportno = 0;
#endif

    if (ret == false)
    {
        wifi_io_e("sdio_drv_write failed (%d)", ret);
#ifdef CONFIG_WIFI_FW_DEBUG
        wifi_sdio_reg_dbg(NULL);
        if (wm_wifi.wifi_usb_mount_cb != NULL)
        {
            ret = wm_wifi.wifi_usb_mount_cb();
            if (ret == WM_SUCCESS)
                wifi_dump_firmware_info(NULL);
            else
                wifi_e("USB mounting failed");
        }
        else
            wifi_e("USB mount callback is not registered");
#endif
        return MLAN_STATUS_FAILURE;
    }
    return MLAN_STATUS_SUCCESS;
}

/*
 * This function gets interrupt status.
 */
t_void wlan_interrupt(mlan_adapter *pmadapter)
{
    /* Read SDIO multiple port group registers */
    uint32_t resp = 0;
    int ret;
    t_u8 *mp_regs = pmadapter->mp_regs;

    /* Read the registers in DMA aligned buffer */
#if defined(SD8801)
    ret = sdio_drv_read(0, 1, 1, MAX_MP_REGS, mp_regs, &resp);
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    ret = sdio_drv_read(REG_PORT | MLAN_SDIO_BYTE_MODE_MASK, 1, 1, MAX_MP_REGS, mp_regs, &resp);
#endif

    if (!ret)
        return;

    t_u8 sdio_ireg = mp_regs[HOST_INT_STATUS_REG];

    if (sdio_ireg != 0U)
    {
        /*
         * DN_LD_HOST_INT_STATUS and/or UP_LD_HOST_INT_STATUS
         * Clear the interrupt status register
         */
        pmadapter->sdio_ireg |= sdio_ireg;
    }

#ifdef CONFIG_WIFI_IO_DEBUG
    t_u32 rd_bitmap, wr_bitmap;
#if defined(SD8801)
    rd_bitmap = ((t_u16)mp_regs[RD_BITMAP_U]) << 8;
    rd_bitmap |= (t_u16)mp_regs[RD_BITMAP_L];
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    rd_bitmap = (t_u32)mp_regs[RD_BITMAP_L];
    rd_bitmap |= ((t_u32)mp_regs[RD_BITMAP_U]) << 8;
    rd_bitmap |= ((t_u32)mp_regs[RD_BITMAP_1L]) << 16;
    rd_bitmap |= ((t_u32)mp_regs[RD_BITMAP_1U]) << 24;
#endif

    (void)PRINTF("INT : rd_bitmap=0x%x\n\r", rd_bitmap);

#if defined(SD8801)
    wr_bitmap = ((t_u16)mp_regs[WR_BITMAP_U]) << 8;
    wr_bitmap |= (t_u16)mp_regs[WR_BITMAP_L];
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    wr_bitmap = (t_u32)mp_regs[WR_BITMAP_L];
    wr_bitmap |= ((t_u32)mp_regs[WR_BITMAP_U]) << 8;
    wr_bitmap |= ((t_u32)mp_regs[WR_BITMAP_1L]) << 16;
    wr_bitmap |= ((t_u32)mp_regs[WR_BITMAP_1U]) << 24;
#endif

    (void)PRINTF("INT : wr_bitmap=0x%x\n\r", wr_bitmap);

    (void)PRINTF("INT : sdio_ireg = (0x%x)\r\n", sdio_ireg);
#endif /* CONFIG_WIFI_IO_DEBUG */
}

#ifdef CONFIG_SDIO_MULTI_PORT_RX_AGGR
/* returns port number from rd_bitmap. if ctrl port, then it clears
 * the bit and does nothing else
 * if data port then increments curr_port value also */
mlan_status wlan_get_rd_port(mlan_adapter *pmadapter, t_u32 *pport, t_u32 *rxlen, t_u32 *rxblocks, bool *aggr)
{
#if defined(SD8801)
    t_u16 rd_bitmap = pmadapter->mp_rd_bitmap;
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    t_u32 rd_bitmap = pmadapter->mp_rd_bitmap;
#endif
    t_u16 pkt_cnt = 0;
    t_u32 len_reg_l, len_reg_u;
    t_u32 rx_len;
    t_u32 rx_blocks;
    t_u16 ports      = 0;
    t_u32 start_port = -1;
    t_u32 cmd53_port = 0;
#if defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    t_u32 port_count = 0;
#endif

    *pport    = -1;
    *rxlen    = 0;
    *rxblocks = 0;

    wifi_io_d(
        "wlan_get_rd_port: mp_rd_bitmap=0x%x"
        " curr_rd_bitmap=0x%x",
        pmadapter->mp_rd_bitmap, pmadapter->curr_rd_port);

#if defined(SD8801)
    if (!(rd_bitmap & (CTRL_PORT_MASK | DATA_PORT_MASK)))
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    if (!(rd_bitmap & DATA_PORT_MASK))
#endif
        return MLAN_STATUS_FAILURE;

#if defined(SD8801)
    if (pmadapter->mp_rd_bitmap & CTRL_PORT_MASK)
    {
        pmadapter->mp_rd_bitmap &= (t_u32)(~CTRL_PORT_MASK);
        *pport = CTRL_PORT;

        len_reg_l = RD_LEN_P0_L + (*pport << 1);
        len_reg_u = RD_LEN_P0_U + (*pport << 1);
        rx_len    = ((t_u16)pmadapter->mp_regs[len_reg_u]) << 8;
        rx_len |= (t_u16)pmadapter->mp_regs[len_reg_l];
        rx_blocks = (rx_len + MLAN_SDIO_BLOCK_SIZE - 1) / MLAN_SDIO_BLOCK_SIZE;
        rx_len    = (t_u16)(rx_blocks * MLAN_SDIO_BLOCK_SIZE);
        *rxlen    = rx_len;
        *rxblocks = rx_blocks;

        *pport = mlan_adap->ioport + *pport;

        wifi_io_d("RX: port=%d rxlen=%u rx_blocks=%u\r\n", *pport, *rxlen, *rxblocks);

        wifi_io_d("wlan_get_rd_port: port=%d mp_rd_bitmap=0x%04x", *pport, pmadapter->mp_rd_bitmap);
    }
    else
    {
#endif
        /* Data */
        while (pmadapter->mp_rd_bitmap & (1 << pmadapter->curr_rd_port))
        {
            pmadapter->mp_rd_bitmap &=
#if defined(SD8801)
                (t_u16)(~(1 << pmadapter->curr_rd_port));
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
            (t_u32)(~(1 << pmadapter->curr_rd_port));
#endif
            *pport = pmadapter->curr_rd_port;

#if defined(SD8801)
            if (!pkt_cnt)
                start_port = *pport;
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
        if (start_port == -1)
            start_port              = *pport;
#endif

#if defined(SD8801)
            if (start_port <= *pport)
            {
                ports |= (1 << (pkt_cnt));
            }
            else
            {
                ports |= (1 << (pkt_cnt + 1));
            }
#endif

            len_reg_l = RD_LEN_P0_L + (*pport << 1);
            len_reg_u = RD_LEN_P0_U + (*pport << 1);
            rx_len    = ((t_u16)pmadapter->mp_regs[len_reg_u]) << 8;
            rx_len |= (t_u16)pmadapter->mp_regs[len_reg_l];
            rx_blocks = (rx_len + MLAN_SDIO_BLOCK_SIZE - 1) / MLAN_SDIO_BLOCK_SIZE;
            rx_len    = (t_u16)(rx_blocks * MLAN_SDIO_BLOCK_SIZE);
            *rxlen += rx_len;
            *rxblocks += rx_blocks;

            wifi_io_d("RX: port=%d rxlen=%u rx_blocks=%u\r\n", *pport, *rxlen, *rxblocks);

            if (++pmadapter->curr_rd_port == MAX_PORT)
#if defined(SD8801)
                pmadapter->curr_rd_port = 1;
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
            pmadapter->curr_rd_port = 0;
#endif

            pkt_cnt++;
#if defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
            ports++;
#endif
            if (pkt_cnt == SDIO_MP_AGGR_DEF_PKT_LIMIT)
                break;

#if defined(SD8801)
            if ((pmadapter->curr_rd_port < start_port) &&
                (((MAX_PORT - start_port) + pmadapter->curr_rd_port) >= SDIO_MP_AGGR_DEF_PKT_LIMIT))
                break;
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
        if (((pmadapter->curr_rd_port < start_port) &&
             (((MAX_PORT - start_port) + pmadapter->curr_rd_port) >= (pmadapter->mp_end_port >> 1))) ||
            ((pmadapter->curr_rd_port - start_port) >= (pmadapter->mp_end_port >> 1)))
            break;
#endif
        }

        if (*pport == -1)
        {
            wifi_io_e("wlan_get_rd_port : Returning FAILURE");
            return MLAN_STATUS_FAILURE;
        }

#if defined(SD8801)
        if (pkt_cnt > 1)
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    if (ports > 1)
#endif
        {
#if defined(SD8801)
            cmd53_port = (pmadapter->ioport | SDIO_MPA_ADDR_BASE | (ports << 4)) + start_port;
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
        port_count = ports - 1;
        cmd53_port = (pmadapter->ioport | SDIO_MPA_ADDR_BASE | (port_count << 8)) + start_port;
#endif
            *pport = cmd53_port;

            *aggr = true;
            // (void)PRINTF("cmd53_port=%x, ports=%x, start_port=%x rxlen=%d rxblocks=%d\r\n", cmd53_port, ports,
            // start_port, *rxlen, *rxblocks);
        }
        else
            *pport = mlan_adap->ioport + *pport;

        wifi_io_d("port=%x mp_rd_bitmap=0x%x -> 0x%x\n", *pport, rd_bitmap, pmadapter->mp_rd_bitmap);
#if defined(SD8801)
    }
#endif

    return MLAN_STATUS_SUCCESS;
}

/*
 * Assumes that pmadapter->mp_rd_bitmap contains latest values
 */
static mlan_status _handle_sdio_packet_read(mlan_adapter *pmadapter, t_u8 **packet, t_u32 *datalen, t_u32 *pkt_type)
{
    t_u32 port;
    t_u32 rx_len = 0, rx_blocks = 0;
    bool aggr = false;

    mlan_status ret = wlan_get_rd_port(pmadapter, &port, &rx_len, &rx_blocks, &aggr);

    /* nothing to read */
    if (ret != MLAN_STATUS_SUCCESS)
        return ret;

    *datalen = rx_len;

    *packet = wlan_read_rcv_packet(port, rx_len, rx_blocks, pkt_type, aggr);

    if (!*packet)
        return MLAN_STATUS_FAILURE;

    return MLAN_STATUS_SUCCESS;
}
#else
/* returns port number from rd_bitmap. if ctrl port, then it clears
 * the bit and does nothing else
 * if data port then increments curr_port value also */
mlan_status wlan_get_rd_port(mlan_adapter *pmadapter, t_u32 *pport)
{
#if defined(SD8801)
    t_u16 rd_bitmap = pmadapter->mp_rd_bitmap;
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    t_u32 rd_bitmap = pmadapter->mp_rd_bitmap;
#endif

    wifi_io_d(
        "wlan_get_rd_port: mp_rd_bitmap=0x%x"
        " curr_rd_bitmap=0x%x",
        pmadapter->mp_rd_bitmap, pmadapter->curr_rd_port);

#if defined(SD8801)
    if (!(rd_bitmap & (CTRL_PORT_MASK | DATA_PORT_MASK)))
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    if (!(rd_bitmap & DATA_PORT_MASK))
#endif
        return MLAN_STATUS_FAILURE;

#if defined(SD8801)
    if (pmadapter->mp_rd_bitmap & CTRL_PORT_MASK)
    {
        pmadapter->mp_rd_bitmap &= (t_u16)(~CTRL_PORT_MASK);
        *pport = CTRL_PORT;

        wifi_io_d("wlan_get_rd_port: port=%d mp_rd_bitmap=0x%04x", *pport, pmadapter->mp_rd_bitmap);
    }
    else
    {
#endif
        /* Data */
        if ((pmadapter->mp_rd_bitmap & (1 << pmadapter->curr_rd_port)) != 0U)
        {
            pmadapter->mp_rd_bitmap &=
#if defined(SD8801)
                (t_u16)(~(1 << pmadapter->curr_rd_port));
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
            (t_u32)(~(1 << pmadapter->curr_rd_port));
#endif
            *pport = pmadapter->curr_rd_port;

            if (++pmadapter->curr_rd_port == MAX_PORT)
#if defined(SD8801)
                pmadapter->curr_rd_port = 1;
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
            pmadapter->curr_rd_port = 0;
#endif
        }
        else
        {
            wifi_io_e("wlan_get_rd_port : Returning FAILURE");
            return MLAN_STATUS_FAILURE;
        }

        wifi_io_d("port=%d mp_rd_bitmap=0x%x -> 0x%x\n", *pport, rd_bitmap, pmadapter->mp_rd_bitmap);
#if defined(SD8801)
    }
#endif

    return MLAN_STATUS_SUCCESS;
}

/*
 * Assumes that pmadapter->mp_rd_bitmap contains latest values
 */
static mlan_status _handle_sdio_packet_read(mlan_adapter *pmadapter, t_u8 **packet, t_u32 *datalen, t_u32 *pkt_type)
{
    t_u32 port;
    t_u32 rx_len, rx_blocks;

    mlan_status ret = wlan_get_rd_port(pmadapter, &port);

    /* nothing to read */
    if (ret != MLAN_STATUS_SUCCESS)
        return ret;

    t_u32 len_reg_l = RD_LEN_P0_L + (port << 1);
    t_u32 len_reg_u = RD_LEN_P0_U + (port << 1);

    rx_len = ((t_u16)pmadapter->mp_regs[len_reg_u]) << 8;
    *datalen = rx_len |= (t_u16)pmadapter->mp_regs[len_reg_l];

    rx_blocks = (rx_len + MLAN_SDIO_BLOCK_SIZE - 1) / MLAN_SDIO_BLOCK_SIZE;
    rx_len = (t_u16)(rx_blocks * MLAN_SDIO_BLOCK_SIZE);

    port = mlan_adap->ioport + port;

    *packet = wlan_read_rcv_packet(port, rx_len, rx_blocks, pkt_type, false);

    if (!*packet)
        return MLAN_STATUS_FAILURE;

    return MLAN_STATUS_SUCCESS;
}
#endif

#if defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
static mlan_status _handle_sdio_cmd_read(
    mlan_adapter *pmadapter, t_u8 **packet, t_u32 *datalen, t_u32 *pkt_type, t_u32 rx_len, t_u32 rx_blocks)
{
    *datalen = rx_len;

    *packet = wlan_read_rcv_packet(mlan_adap->ioport | CMD_PORT_SLCT, rx_len, rx_blocks, pkt_type, false);

    if (!*packet)
        return MLAN_STATUS_FAILURE;

    return MLAN_STATUS_SUCCESS;
}
/*
 * This function keeps on looping till all the packets are read
 */
static void handle_sdio_cmd_read(mlan_adapter *pmadapter, t_u32 rx_len, t_u32 rx_blocks)
{
    t_u32 datalen = 0;

    t_u32 pkt_type = 0;
    t_u8 *packet   = NULL;

    _handle_sdio_cmd_read(pmadapter, &packet, &datalen, &pkt_type, rx_len, rx_blocks);
    if (pkt_type == MLAN_TYPE_CMD || pkt_type == MLAN_TYPE_EVENT)
    {
        /* non-data packets such as events
           and command responses are
           handled here */
        wlan_decode_rx_packet(packet, pkt_type);
    }
}
#endif

/*
 * This function keeps on looping till all the packets are read
 */
static void handle_sdio_packet_read(mlan_adapter *pmadapter)
{
    mlan_status ret = MLAN_STATUS_SUCCESS;
    t_u32 datalen   = 0;

    pmadapter->mp_rd_bitmap =
#if defined(SD8801)
        ((t_u16)pmadapter->mp_regs[RD_BITMAP_U]) << 8;
    pmadapter->mp_rd_bitmap |= (t_u16)pmadapter->mp_regs[RD_BITMAP_L];
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
        (t_u32)pmadapter->mp_regs[RD_BITMAP_L];
    pmadapter->mp_rd_bitmap |= ((t_u32)pmadapter->mp_regs[RD_BITMAP_U]) << 8;
    pmadapter->mp_rd_bitmap |= ((t_u32)pmadapter->mp_regs[RD_BITMAP_1L]) << 16;
    pmadapter->mp_rd_bitmap |= ((t_u32)pmadapter->mp_regs[RD_BITMAP_1U]) << 24;
#endif

    while (true)
    {
        t_u32 pkt_type;
        t_u32 rx_blocks;
        t_u32 size       = 0;
        t_u32 total_size = 0;
        t_u8 *packet     = NULL;
        t_u8 interface;

        ret = _handle_sdio_packet_read(pmadapter, &packet, &datalen, &pkt_type);
        if (ret != MLAN_STATUS_SUCCESS)
        {
            /* nothing to read. break out of while loop */
            break;
        }

        if (pkt_type == MLAN_TYPE_DATA)
        {
            while (total_size < datalen)
            {
                SDIOPkt *insdiopkt = (SDIOPkt *)packet;
                size               = insdiopkt->size;
                pkt_type           = insdiopkt->pkttype;

                rx_blocks = (size + MLAN_SDIO_BLOCK_SIZE - 1) / MLAN_SDIO_BLOCK_SIZE;
                size      = (t_u16)(rx_blocks * MLAN_SDIO_BLOCK_SIZE);

                interface = *((t_u8 *)packet + INTF_HEADER_LEN);

                wifi_io_info_d("IN: i/f: %d len: %d", interface, size);

                if (!size)
                    break;

                if (bus.wifi_low_level_input != NULL)
                    bus.wifi_low_level_input(interface, packet, size);

                packet += size;
                total_size += size;
            }
        }
        else
        {
            /* non-data packets such as events
               and command responses are
               handled here */
            wlan_decode_rx_packet(packet, pkt_type);
        }
    }
}

/*
 * This is supposed to be called in thread context.
 */
mlan_status wlan_process_int_status(mlan_adapter *pmadapter)
{
    mlan_status ret = MLAN_STATUS_SUCCESS;
#if defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    t_u8 cmd_rd_len_0 = CMD_RD_LEN_0;
    t_u8 cmd_rd_len_1 = CMD_RD_LEN_1;
    t_u32 rx_len;
    t_u32 rx_blocks;
#endif

    /* Get the interrupt status */
    wlan_interrupt(pmadapter);

    t_u8 sdio_ireg       = pmadapter->sdio_ireg;
    pmadapter->sdio_ireg = 0;

    if (!sdio_ireg)
        goto done;

#if defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    /* check the command port */
    if ((sdio_ireg & DN_LD_CMD_PORT_HOST_INT_STATUS) != 0U)
    {
        if (pmadapter->cmd_sent != 0U)
            pmadapter->cmd_sent = MFALSE;
        PRINTM(MINFO, "cmd_sent=%d\n", pmadapter->cmd_sent);
    }

    if ((sdio_ireg & UP_LD_CMD_PORT_HOST_INT_STATUS) != 0U)
    {
        /* read the len of control packet */
        rx_len = ((t_u32)pmadapter->mp_regs[cmd_rd_len_1]) << 8;
        rx_len |= (t_u32)pmadapter->mp_regs[cmd_rd_len_0];
        PRINTM(MINFO, "RX: cmd port rx_len=%u\n", rx_len);

        rx_blocks = (rx_len + MLAN_SDIO_BLOCK_SIZE - 1) / MLAN_SDIO_BLOCK_SIZE;

        // (void)PRINTF("CMD: cmd port rx_len=%u rx_blocks=%u\r\n", rx_len, rx_blocks);
        rx_len = (t_u32)(rx_blocks * MLAN_SDIO_BLOCK_SIZE);

        handle_sdio_cmd_read(pmadapter, rx_len, rx_blocks);
    }
#elif defined(SD8801)
    /*
     * Below two statement look like they are present for the purpose
     * of unconditional initializing of mp_wr_bitmap which will be used
     * during packet xmit. proper mlan code does not do this most
     * probably because they have used wlan_get_wr_port_data() to
     * decide on the write port which we have not done. Check this out
     * later.
     */
    pmadapter->mp_wr_bitmap = ((t_u16)pmadapter->mp_regs[WR_BITMAP_U]) << 8;
    pmadapter->mp_wr_bitmap |= (t_u16)pmadapter->mp_regs[WR_BITMAP_L];
#endif

    pmadapter->mp_wr_bitmap =
#if defined(SD8801)
        ((t_u16)pmadapter->mp_regs[WR_BITMAP_U]) << 8;
    pmadapter->mp_wr_bitmap |= (t_u16)pmadapter->mp_regs[WR_BITMAP_L];
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
        (t_u32)pmadapter->mp_regs[WR_BITMAP_L];
    pmadapter->mp_wr_bitmap |= ((t_u32)pmadapter->mp_regs[WR_BITMAP_U]) << 8;
    pmadapter->mp_wr_bitmap |= ((t_u32)pmadapter->mp_regs[WR_BITMAP_1L]) << 16;
    pmadapter->mp_wr_bitmap |= ((t_u32)pmadapter->mp_regs[WR_BITMAP_1U]) << 24;
#endif

    /*
     * DN_LD_HOST_INT_STATUS interrupt happens when the txmit sdio
     * ports are freed This is usually when we write to port most
     * significant port.
     */
    if ((sdio_ireg & DN_LD_HOST_INT_STATUS) != 0U)
    {
        pmadapter->mp_wr_bitmap =
#if defined(SD8801)
            ((t_u16)pmadapter->mp_regs[WR_BITMAP_U]) << 8;
        pmadapter->mp_wr_bitmap |= (t_u16)pmadapter->mp_regs[WR_BITMAP_L];
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
            (t_u32)pmadapter->mp_regs[WR_BITMAP_L];
        pmadapter->mp_wr_bitmap |= ((t_u32)pmadapter->mp_regs[WR_BITMAP_U]) << 8;
        pmadapter->mp_wr_bitmap |= ((t_u32)pmadapter->mp_regs[WR_BITMAP_1L]) << 16;
        pmadapter->mp_wr_bitmap |= ((t_u32)pmadapter->mp_regs[WR_BITMAP_1U]) << 24;
#endif
    }

    /*
     * As firmware will not generate download ready interrupt if the
     * port updated is command port only, cmd_sent should be done for
     * any SDIO interrupt.
     */
#if defined(SD8801)
    if (pmadapter->cmd_sent == true)
    {
        /*
         * Check if firmware has attach buffer at command port and
         * update just that in wr_bit_map.
         */
        pmadapter->mp_wr_bitmap |= (t_u16)pmadapter->mp_regs[WR_BITMAP_L] & CTRL_PORT_MASK;

        if (pmadapter->mp_wr_bitmap & CTRL_PORT_MASK)
            pmadapter->cmd_sent = false;
    }
#endif

    if ((sdio_ireg & UP_LD_HOST_INT_STATUS) != 0U)
    {
        /* This means there is data to be read */
        handle_sdio_packet_read(pmadapter);
    }

    ret = MLAN_STATUS_SUCCESS;

done:
    return ret;
}

/**
 * Interrupt callback handler registered with the SDIO driver.
 */
void handle_cdint(int error)
{
    /* Wake up LWIP thread. */
    if (wifi_core_thread && !error && g_txrx_flag)
    {
        g_txrx_flag = false;
        os_event_notify_put(wifi_core_thread);
    }
}

int wifi_raw_packet_recv(t_u8 **data, t_u32 *pkt_type)
{
    if (!data)
        return -WM_FAIL;

    wifi_core_thread = os_get_current_task_handle();

    int sta = os_enter_critical_section();
    /* Allow interrupt handler to deliver us a packet */
    g_txrx_flag = true;

    sdio_enable_interrupt();

    os_exit_critical_section(sta);

    /* Wait till we receive a packet from SDIO */
    os_event_notify_get(OS_WAIT_FOREVER);

    /* Get the interrupt status */
    wlan_interrupt(mlan_adap);

    t_u8 sdio_ireg       = mlan_adap->sdio_ireg;
    mlan_adap->sdio_ireg = 0;

#if defined(SD8801)
    if (!(sdio_ireg & UP_LD_HOST_INT_STATUS))
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    if (!(sdio_ireg & UP_LD_CMD_PORT_HOST_INT_STATUS))
#endif
        return -WM_FAIL;

    t_u32 datalen = 0;

    mlan_adap->mp_rd_bitmap =
#if defined(SD8801)
        ((t_u16)mlan_adap->mp_regs[RD_BITMAP_U]) << 8;
    mlan_adap->mp_rd_bitmap |= (t_u16)mlan_adap->mp_regs[RD_BITMAP_L];
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
        (t_u32)mlan_adap->mp_regs[RD_BITMAP_L];
    mlan_adap->mp_rd_bitmap |= ((t_u32)mlan_adap->mp_regs[RD_BITMAP_U]) << 8;
    mlan_adap->mp_rd_bitmap |= ((t_u32)mlan_adap->mp_regs[RD_BITMAP_1L]) << 16;
    mlan_adap->mp_rd_bitmap |= ((t_u32)mlan_adap->mp_regs[RD_BITMAP_1U]) << 24;
#endif

    t_u8 *packet = NULL;

#if defined(SD8801)
    int ret;
    while (1)
    {
        ret = _handle_sdio_packet_read(mlan_adap, &packet, &datalen, pkt_type);
        if (ret == MLAN_STATUS_SUCCESS)
        {
            break;
        }
    }
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)

    t_u8 cmd_rd_len_0 = CMD_RD_LEN_0;
    t_u8 cmd_rd_len_1 = CMD_RD_LEN_1;
    t_u32 rx_len;
    t_u32 rx_blocks;

    /* read the len of control packet */
    rx_len = ((t_u32)mlan_adap->mp_regs[cmd_rd_len_1]) << 8;
    rx_len |= (t_u32)mlan_adap->mp_regs[cmd_rd_len_0];
    PRINTM(MINFO, "RX: cmd port rx_len=%u\n", rx_len);

    rx_blocks = (rx_len + MLAN_SDIO_BLOCK_SIZE - 1) / MLAN_SDIO_BLOCK_SIZE;

    rx_len = (t_u32)(rx_blocks * MLAN_SDIO_BLOCK_SIZE);

    _handle_sdio_cmd_read(mlan_adap, &packet, &datalen, pkt_type, rx_len, rx_blocks);
#endif
    *data = packet;
    return WM_SUCCESS;
}

int wifi_raw_packet_send(const t_u8 *packet, t_u32 length)
{
    if (!packet || !length)
        return -WM_E_INVAL;

    if (length > SDIO_OUTBUF_LEN)
    {
        wifi_io_e("Insufficient buffer");
        return -WM_FAIL;
    }

    t_u32 tx_blocks = 0, buflen = 0;
    calculate_sdio_write_params(length, &tx_blocks, &buflen);

    (void)memcpy(outbuf, packet, length);
#ifdef CONFIG_WIFI_IO_DUMP
    dump_hex(outbuf, length);
#endif
    uint32_t resp;
#if defined(SD8801)
    sdio_drv_write(mlan_adap->ioport, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    sdio_drv_write(mlan_adap->ioport | CMD_PORT_SLCT, 1, tx_blocks, buflen, (t_u8 *)outbuf, &resp);
#endif
    return WM_SUCCESS;
}

mlan_status sd_wifi_preinit(enum wlan_fw_storage_type st)
{
    mlan_status mlanstatus = MLAN_STATUS_SUCCESS;

#if 0
	/* Initialise internal/external flash memory */
	if (st == WLAN_FW_IN_FLASH)
		flash_drv_init();
#endif

    /* initializes the driver struct */
    int sdiostatus = wlan_init_struct();
    if (sdiostatus != WM_SUCCESS)
    {
        wifi_io_e("Init failed. Cannot create init struct");
        return MLAN_STATUS_FAILURE;
    }

    /*
     * Register a callback with power manager of MC200/MW300
     * This callback will be called on entry /exit
     * of low power mode of MC200/MW300 based on first paramter
     * passed to the call.
     */
    //	pm_handle = pm_register_cb(ACTION_EXIT_PM3 | ACTION_ENTER_PM4,
    //		       sd_wifi_ps_cb, NULL);

    mlan_subsys_init();

    seqnum   = 0;
    txportno = 0;
    return mlanstatus;
}

void sd_wifi_postsdioinit()
{
    /* Initialize the mlan subsystem before initializing 878x driver */
    mlan_subsys_init();
}

mlan_status sd_wifi_post_fwload(enum wlan_type type)
{
    mlan_status mlanstatus = MLAN_STATUS_SUCCESS;
    uint32_t resp;
#if defined(SD8801)
    sdio_drv_creg_write(HOST_INT_MASK_REG, 1, 0x3, &resp);
#elif defined(SD8977) || defined(SD8978) || defined(SD8987) || defined(SD8997) || defined(SD9097) || defined(SD9098)
    sdio_drv_creg_write(HOST_INT_MASK_REG, 1, HIM_ENABLE, &resp);
#endif

    /* If we're running a Manufacturing image, start the tasks.
       If not, initialize and setup the firmware */
    switch (type)
    {
        case WLAN_TYPE_NORMAL:
            wlan_fw_init_cfg();
            sdio_enable_interrupt();
            break;
        case WLAN_TYPE_WIFI_CALIB:
            g_txrx_flag = true;
            break;
        case WLAN_TYPE_FCC_CERTIFICATION:
            g_txrx_flag = true;
            break;
        default:
            wifi_io_e("Enter a valid input to sd_wifi_init");
            return MLAN_STATUS_FAILURE;
    }

#if defined(SD8801)
    txportno = 1;
#endif

    return mlanstatus;
}

mlan_status sd_wifi_init(enum wlan_type type,
                         enum wlan_fw_storage_type st,
                         const uint8_t *fw_ram_start_addr,
                         const size_t size)
{
    mlan_status ret = MLAN_STATUS_SUCCESS;

    ret = sd_wifi_preinit(st);
    if (ret == 0)
    {
        ret = sdio_init();
        if (ret == 0)
        {
            sd_wifi_postsdioinit();
            ret = sdio_ioport_init();
            if (ret == 0)
            {
                ret = firmware_download(st, fw_ram_start_addr, size);
                if (ret == 0)
                {
                    ret = sd_wifi_post_fwload(type);
                }
            }
        }
    }
    return ret;
}

void sd_wifi_deinit(void)
{
#ifdef WLAN_LOW_POWER_ENABLE
    low_power_mode = false;
#endif
    cal_data_valid = false;
    mac_addr_valid = false;
    //	pm_deregister_cb(pm_handle);

    wlan_cmd_shutdown();
    // sdio_drv_deinit();
}

HostCmd_DS_COMMAND *wifi_get_command_buffer()
{
    /* First 4 bytes reserved for SDIO pkt header */
    return (HostCmd_DS_COMMAND *)(cmd_buf + INTF_HEADER_LEN);
}

/**
 * Function to set mlan ioport.
 */
void set_ioport_inmlan(t_u32 port)
{
    mlan_adap->ioport = port;
}
