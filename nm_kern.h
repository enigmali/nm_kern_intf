/*
 * Netmap data types
 */

#define IF_NAME_SIZE		44
#define NM_ERRBUF_SIZE		512

#define NM_CACHE_ALIGN		128

struct netmap_if {
	char			ni_name[IF_NAME_SIZE];
	const uint32_t	ni_version;
	const uint32_t	ni_flags;

#define NI_PRIV_MEM	0x01 
	
	const uint32_t	ni_tx_rings;
	const uint32_t	ni_rx_rings;

	uint32_t		ni_bufs_head;
	uint32_t		ni_spare1[5];

	const ssize_t	rings_ofs[0];
};

struct nmreq {
	char		nr_name[IF_NAME_SIZE];
	uint32_t	nr_version;
	uint32_t	nr_offset;
	uint32_t	nr_memsize;
	uint32_t	nr_tx_slots;
	uint32_t	nr_rx_slots;
	uint16_t	nr_tx_rings;
	uint16_t	nr_rx_rings;

	uint16_t	nr_ringid;

#define	NETMAP_HW_RING			0x4000
#define NETMAP_SW_RING			0x2000
#define NETMAP_RING_MASK		0x0fff
#define NETMAP_NO_TX_POLL		0x1000
#define NETMAP_DO_RX_POLL		0x8000
	uint16_t	nr_cmd;
#define NETMAP_BDG_ATTACH		1
#define NETMAP_BDG_DETACH		2
#define NETMAP_BDG_REGOPS		3
#define NETMAP_BDG_LIST			4
#define NETMAP_BDG_VNET_HDR		5
#define NETMAP_BDG_OFFSET		NETMAP_BDG_VNET_HDR
#define NETMAP_BDG_NEWIF		6
#define NETMAP_BDG_DELIF		7
#define NETMAP_PT_HOST_CREATE	8
#define NETMAP_PT_HOST_DELETE	9
#define NETMAP_BDG_POLLING_ON	10
#define NETMAP_BDG_POLLING_OFF	11
#define NETMAP_VNET_HDR_GET		12
	uint16_t	nr_arg1;
#define NETMAP_BDG_HOST			1

	uint16_t	nr_arg2;
	uint32_t	nr_arg3;
	uint32_t	nr_flags;
	uint32_t	spare2[1];
};

struct timeval {
	uint64_t	tv_sec;
	uint64_t	tv_usec;
};

struct netmap_slot {
	uint32_t	buf_idx;
	uint16_t	len;
	uint16_t	flags;
	uint64_t	ptr;
};

struct nm_pkthdr {
	struct timeval		ts;
	uint32_t			caplen;
	uint32_t			len;
	uint64_t			flags;

#define NM_MORE_PKTS	1
	
	struct nm_desc		*d;
	struct netmap_slot	*slot;
	uint8_t				*buf;
};

struct netmap_ring {
	const int64_t		buf_ofs;
	const uint32_t		num_slots;
	const uint32_t		nr_buf_size;
	const uint16_t		ringid;
	const uint16_t		dir;

	uint32_t			head;
	uint32_t			cur;
	uint32_t			tail;
	uint32_t			flags;

	struct timeval		ts;

	uint8_t	__attribute__((__aligned__(NM_CACHE_ALIGN)))	sem[128];

	struct netmap_slot	slot[0];
	
};

struct nm_stat {
	uint32_t	ps_recv;
	uint32_t	ps_drop;
	uint32_t	ps_ifdrop;
};

struct nm_desc {
	struct nm_desc		*self;
	int					fd;
	void				*mem;
	uint32_t			memsize;
	int					done_mmap;
	struct netmap_if	*const nifp;
	uint16_t			first_tx_ring, last_tx_ring, cur_tx_ring;
	uint16_t			first_rx_ring, last_rx_ring, cur_rx_ring;
	struct nmreq		req;
	struct nm_pkthdr	hdr;
	
	struct netmap_ring	*const some_ring;
	void				*const buf_start;
	void				*const buf_end;

	int					snaplen;
	int					promisc;
	int					to_ms;
	char				*errbuf;

	uint32_t			if_flags;
	uint32_t			if_reqcap;
	uint32_t			if_curcap;

	struct nm_stat		st;
	char				msg[NM_ERRBUF_SIZE];
};


/*
 *	Functions ported from user space to kernel space
 */
static int nm_close(struct nm_desc *nm_d);
static struct nm_desc *nm_open(const char *ifname, const struct nmreq *req, uint64_t new_flags, conststruct nm_desc *arg);
