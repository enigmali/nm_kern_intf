/*
 * Netmap data types
 */

#define IF_NAME_SIZE		44
#define NM_ERRBUF_SIZE		512


struct netmap_if {
	char			ni_name[IF_NAME_SIZE];
	const uint32_t	ni_version;
	const uint32_t	ni_flags;

	// #define NI_PRIV_MEM	0x01 ???
	
	const uint32_t	ni_tx_rings;
	const uint32_t	ni_rx_rings;

	uint32_t		ni_bufs_head;
	uint32_t		ni_spare1[5];

	const ssize_t	rings_ofs[0];
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
