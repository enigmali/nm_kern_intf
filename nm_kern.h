/*
 * Netmap data types
 */

struct nm_desc {};


static int nm_close(struct nm_desc *nm_d);
static struct nm_desc *nm_open(const char *ifname, const struct nmreq *req, uint64_t new_flags, conststruct nm_desc *arg);
