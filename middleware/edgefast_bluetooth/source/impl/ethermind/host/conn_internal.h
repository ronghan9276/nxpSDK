/** @file
 *  @brief Internal APIs for Bluetooth connection handling.
 */

/*
 * Copyright 2021 NXP
 * Copyright (c) 2015 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __CONN_INTERNAL_H__
#define __CONN_INTERNAL_H__

typedef enum {
	BT_CONN_DISCONNECTED,
	BT_CONN_DISCONNECT_COMPLETE,
	BT_CONN_CONNECT_SCAN,
	BT_CONN_CONNECT_AUTO,
	BT_CONN_CONNECT_ADV,
	BT_CONN_CONNECT_DIR_ADV,
	BT_CONN_CONNECT,
	BT_CONN_CONNECTED,
	BT_CONN_DISCONNECT,
} bt_conn_state_t;

/* bt_conn flags: the flags defined here represent connection parameters */
enum {
	BT_CONN_AUTO_CONNECT,
	BT_CONN_BR_LEGACY_SECURE,	/* 16 digits legacy PIN tracker */
	BT_CONN_USER,			/* user I/O when pairing */
	BT_CONN_BR_PAIRING,		/* BR connection in pairing context */
	BT_CONN_BR_NOBOND,		/* SSP no bond pairing tracker */
	BT_CONN_BR_PAIRING_INITIATOR,	/* local host starts authentication */
	BT_CONN_CLEANUP,                /* Disconnected, pending cleanup */
	BT_CONN_AUTO_PHY_UPDATE,        /* Auto-update PHY */
	BT_CONN_SLAVE_PARAM_UPDATE,	/* If slave param update timer fired */
	BT_CONN_SLAVE_PARAM_SET,	/* If slave param were set from app */
	BT_CONN_SLAVE_PARAM_L2CAP,	/* If should force L2CAP for CPUP */
	BT_CONN_FORCE_PAIR,             /* Pairing even with existing keys. */

	BT_CONN_AUTO_PHY_COMPLETE,      /* Auto-initiated PHY procedure done */
	BT_CONN_AUTO_FEATURE_EXCH,	/* Auto-initiated LE Feat done */
	BT_CONN_AUTO_VERSION_INFO,      /* Auto-initiated LE version done */

	/* Auto-initiated Data Length done. Auto-initiated Data Length Update
	 * is only needed for controllers with BT_QUIRK_NO_AUTO_DLE. */
	BT_CONN_AUTO_DATA_LEN_COMPLETE,

    BT_CONN_UNPAIRING,                /* Disconnected, unpairing */

	/* Total number of flags - must be at the end of the enum */
	BT_CONN_NUM_FLAGS,
};

struct bt_conn_le {
	bt_addr_le_t		dst;

	bt_addr_le_t		init_addr;
	bt_addr_le_t		resp_addr;

	uint16_t			interval;
	uint16_t			interval_min;
	uint16_t			interval_max;

	uint16_t			latency;
	uint16_t			timeout;
	uint16_t			pending_latency;
	uint16_t			pending_timeout;

	uint8_t			features[8];

	struct bt_keys		*keys;

#if (defined(CONFIG_BT_USER_PHY_UPDATE) && ((CONFIG_BT_USER_PHY_UPDATE) > 0U))
	struct bt_conn_le_phy_info      phy;
#endif

#if (defined(CONFIG_BT_USER_DATA_LEN_UPDATE) && ((CONFIG_BT_USER_DATA_LEN_UPDATE) > 0U))
	struct bt_conn_le_data_len_info data_len;
#endif
};

#if (defined(CONFIG_BT_BREDR) && ((CONFIG_BT_BREDR) > 0U))
/* For now reserve space for 2 pages of LMP remote features */
#define LMP_MAX_PAGES 2

struct bt_conn_br {
	bt_addr_t		dst;
	uint8_t			remote_io_capa;
	uint8_t			remote_auth;
	uint8_t			pairing_method;
	/* remote LMP features pages per 8 bytes each */
	uint8_t			features[LMP_MAX_PAGES][8];

	struct bt_keys_link_key	*link_key;
};

struct bt_conn_sco {
	/* Reference to ACL Connection */
	struct bt_conn          *acl;
	uint16_t                pkt_type;
};
#endif

struct bt_conn_iso {
	/* Reference to ACL Connection */
	struct bt_conn          *acl;
	/* CIG ID */
	uint8_t			cig_id;
	/* CIS ID */
	uint8_t			cis_id;
};

typedef void (*bt_conn_tx_cb_t)(struct bt_conn *conn, void *user_data);

struct bt_conn_tx {
	sys_snode_t node;

	bt_conn_tx_cb_t cb;
	void *user_data;

	/* Number of pending packets without a callback after this one */
	uint32_t pending_no_cb;
};

struct bt_pending_chan_info {
	struct bt_l2cap_chan *chan;
	struct net_buf *buf;
	size_t timeout;
};

struct bt_conn {
	uint16_t			handle;
	uint8_t			type;
	uint8_t			role;

	ATOMIC_DEFINE(flags, BT_CONN_NUM_FLAGS);

	/* Which local identity address this connection uses */
	uint8_t                    id;

	bt_security_t		sec_level;
#if ((defined(CONFIG_BT_SMP) && ((CONFIG_BT_SMP) > 0U)) || (defined(CONFIG_BT_BREDR) && ((CONFIG_BT_BREDR) > 0U)))
	bt_security_t		required_sec_level;
	uint8_t			encrypt;
#endif /* CONFIG_BT_SMP || CONFIG_BT_BREDR */

	/* Connection error or reason for disconnect */
	uint8_t			err;

	bt_conn_state_t		state;
	uint16_t rx_len;
	struct net_buf		*rx;

	/* Sent but not acknowledged TX packets with a callback */
	sys_slist_t		tx_pending;
	/* Sent but not acknowledged TX packets without a callback before
	 * the next packet (if any) in tx_pending.
	 */
	uint32_t                   pending_no_cb;

	/* Completed TX for which we need to call the callback */
	sys_slist_t		tx_complete;
#if 0
	struct bt_work           tx_complete_work;
#endif

	/* Queue for outgoing ACL data */
	osa_msgq_handle_t		tx_queue;
    OSA_MSGQ_HANDLE_DEFINE(tx_queue_handle, CONFIG_BT_MSG_QUEUE_COUNT, sizeof(void*));

	/* Active L2CAP/ISO channels */
	sys_slist_t		channels;

	atomic_t		ref;

	/* Delayed work for connection update and other deferred tasks */
	struct bt_delayed_work	update_work;

#if 0
	union {
#endif
		struct bt_conn_le	le;
#if (defined(CONFIG_BT_BREDR) && ((CONFIG_BT_BREDR) > 0U))
		struct bt_conn_br	br;
		struct bt_conn_sco	sco;
#endif
#if (defined(CONFIG_BT_AUDIO) && ((CONFIG_BT_AUDIO) > 0U))
		struct bt_conn_iso	iso;
#endif
#if 0
	};
#endif

#if (defined(CONFIG_BT_REMOTE_VERSION) && ((CONFIG_BT_REMOTE_VERSION) > 0U))
	struct bt_conn_rv {
		uint8_t  version;
		uint16_t manufacturer;
		uint16_t subversion;
	} rv;
#endif
    /* ethermind status */
	uint8_t deviceId;

#if (defined(CONFIG_BT_L2CAP_DYNAMIC_CHANNEL) && (CONFIG_BT_L2CAP_DYNAMIC_CHANNEL > 0))
	/* active chan */
	struct bt_l2cap_chan *activeChan;
	/* pending chan for outgoing active connect req */
	osa_msgq_handle_t pending_chan;
    OSA_MSGQ_HANDLE_DEFINE(pending_chan_handle, CONFIG_BT_MSG_QUEUE_COUNT, sizeof(struct bt_pending_chan_info));
#endif
};

void bt_conn_reset_rx_state(struct bt_conn *conn);

/* Process incoming data for a connection */
void bt_conn_recv(struct bt_conn *conn, struct net_buf *buf, uint8_t flags);

/* Send data over a connection */
int bt_conn_send_cb(struct bt_conn *conn, struct net_buf *buf,
		    bt_conn_tx_cb_t cb, void *user_data);

static inline int bt_conn_send(struct bt_conn *conn, struct net_buf *buf)
{
	return bt_conn_send_cb(conn, buf, NULL, NULL);
}

/* Check if a connection object with the peer already exists */
bool bt_conn_exists_le(uint8_t id, const bt_addr_le_t *peer);

/* Add a new LE connection */
struct bt_conn *bt_conn_add_le(uint8_t id, const bt_addr_le_t *peer);

/** Connection parameters for ISO connections */
struct bt_iso_create_param {
	uint8_t			id;
	uint8_t			num_conns;
	struct bt_conn		**conns;
	struct bt_iso_chan	**chans;
};

/* Bind ISO connections parameters */
int bt_conn_bind_iso(struct bt_iso_create_param *param);

/* Connect ISO connections */
int bt_conn_connect_iso(struct bt_conn **conns, uint8_t num_conns);

/* Add a new ISO connection */
struct bt_conn *bt_conn_add_iso(struct bt_conn *acl);

/* Cleanup ISO references */
void bt_iso_cleanup(struct bt_conn *iso_conn);

/* Add a new BR/EDR connection */
struct bt_conn *bt_conn_add_br(const bt_addr_t *peer);

/* Add a new SCO connection */
struct bt_conn *bt_conn_add_sco(const bt_addr_t *peer, int link_type);

/* Cleanup SCO references */
void bt_sco_cleanup(struct bt_conn *sco_conn);

/* Look up an existing sco connection by BT address */
struct bt_conn *bt_conn_lookup_addr_sco(const bt_addr_t *peer);

/* Look up an existing connection by BT address */
struct bt_conn *bt_conn_lookup_addr_br(const bt_addr_t *peer);

void bt_conn_disconnect_all(uint8_t id);

/* Allocate new connection object */
struct bt_conn *bt_conn_new(struct bt_conn *conns, size_t size);

/* Look up an existing connection */
struct bt_conn *bt_conn_lookup_handle(uint16_t handle);

/* Look up an existing connection by device id */
struct bt_conn *bt_conn_lookup_device_id(uint8_t device_id);

static inline bool bt_conn_is_handle_valid(struct bt_conn *conn)
{
	switch (conn->state) {
	case BT_CONN_CONNECTED:
	case BT_CONN_DISCONNECT:
	case BT_CONN_DISCONNECT_COMPLETE:
		return true;
	case BT_CONN_CONNECT:
		/* ISO connection handle assigned at connect state */
		if (IS_ENABLED(CONFIG_BT_ISO) &&
		    conn->type == BT_CONN_TYPE_ISO) {
			return true;
		}
	__fallthrough;
	default:
		return false;
	}
}

/* Check if the connection is with the given peer. */
bool bt_conn_is_peer_addr_le(const struct bt_conn *conn, uint8_t id,
			     const bt_addr_le_t *peer);

/* Helpers for identifying & looking up connections based on the the index to
 * the connection list. This is useful for O(1) lookups, but can't be used
 * e.g. as the handle since that's assigned to us by the controller.
 */
#define BT_CONN_INDEX_INVALID 0xff
struct bt_conn *bt_conn_lookup_index(uint8_t index);

/* Look up a connection state. For BT_ADDR_LE_ANY, returns the first connection
 * with the specific state
 */
struct bt_conn *bt_conn_lookup_state_le(uint8_t id, const bt_addr_le_t *peer,
					const bt_conn_state_t state);

/* Set connection object in certain state and perform action related to state */
void bt_conn_set_state(struct bt_conn *conn, bt_conn_state_t state);

int bt_conn_le_conn_update(struct bt_conn *conn,
			   const struct bt_le_conn_param *param);

void notify_remote_info(struct bt_conn *conn);

void notify_le_param_updated(struct bt_conn *conn);

void notify_le_data_len_updated(struct bt_conn *conn);

void notify_le_phy_updated(struct bt_conn *conn);

bool le_param_req(struct bt_conn *conn, struct bt_le_conn_param *param);

#if (defined(CONFIG_BT_SMP) && ((CONFIG_BT_SMP) > 0U))
/* rand and ediv should be in BT order */
int bt_conn_le_start_encryption(struct bt_conn *conn, uint8_t rand[8],
				uint8_t ediv[2], const uint8_t *ltk, size_t len);

/* Notify higher layers that RPA was resolved */
void bt_conn_identity_resolved(struct bt_conn *conn);
#endif /* CONFIG_BT_SMP */

#if ((defined(CONFIG_BT_SMP) && ((CONFIG_BT_SMP) > 0U)) || (defined(CONFIG_BT_BREDR) && ((CONFIG_BT_BREDR) > 0U)))
/* Notify higher layers that connection security changed */
void bt_conn_security_changed(struct bt_conn *conn, uint8_t hci_err,
			      enum bt_security_err err);
#endif /* CONFIG_BT_SMP || CONFIG_BT_BREDR */

/* Prepare a PDU to be sent over a connection */
#if (defined(CONFIG_NET_BUF_LOG) && ((CONFIG_NET_BUF_LOG) > 0U))
struct net_buf *bt_conn_create_pdu_timeout_debug(struct net_buf_pool *pool,
						 size_t reserve,
						 size_t timeout,
						 const char *func, int line);
#define bt_conn_create_pdu_timeout(_pool, _reserve, _timeout) \
	bt_conn_create_pdu_timeout_debug(_pool, _reserve, _timeout, \
					 __func__, __LINE__)

#define bt_conn_create_pdu(_pool, _reserve) \
	bt_conn_create_pdu_timeout_debug(_pool, _reserve, osaWaitForever_c, \
					 __func__, __LINE__)
#else
struct net_buf *bt_conn_create_pdu_timeout(struct net_buf_pool *pool,
					   size_t reserve, size_t timeout);

#define bt_conn_create_pdu(_pool, _reserve) \
	bt_conn_create_pdu_timeout(_pool, _reserve, osaWaitForever_c)
#endif

/* Prepare a PDU to be sent over a connection */
#if (defined(CONFIG_NET_BUF_LOG) && ((CONFIG_NET_BUF_LOG) > 0U))
struct net_buf *bt_conn_create_frag_timeout_debug(size_t reserve,
						  size_t timeout,
						  const char *func, int line);

#define bt_conn_create_frag_timeout(_reserve, _timeout) \
	bt_conn_create_frag_timeout_debug(_reserve, _timeout, \
					  __func__, __LINE__)

#define bt_conn_create_frag(_reserve) \
	bt_conn_create_frag_timeout_debug(_reserve, osaWaitForever_c, \
					  __func__, __LINE__)
#else
struct net_buf *bt_conn_create_frag_timeout(size_t reserve,
					    size_t timeout);

#define bt_conn_create_frag(_reserve) \
	bt_conn_create_frag_timeout(_reserve, osaWaitForever_c)
#endif

/* Initialize connection management */
int bt_conn_init(void);

/* Selects based on connecton type right semaphore for ACL packets */
osa_semaphore_handle_t bt_conn_get_pkts(struct bt_conn *conn);

/* k_poll related helpers for the TX thread */
void bt_conn_process_tx(struct bt_conn *conn);

/* false - continue, true - stop */
typedef bool (*bt_conn_scan_cb_t)(struct bt_conn *conn, void *param);

int bt_conn_scan(bt_conn_scan_cb_t cb, void *param);

#endif /* __CONN_INTERNAL_H__ */
