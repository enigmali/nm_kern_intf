#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Enigma Li <lizhilong.enigma@gmail.com>");
MODULE_DESCRIPTION("The Module to Operate Netmap in Kernel Space.");

EXPORT_SYMBOL(time_measure_end);


static int nm_close(struct nm_desc *nm_d) 
{
	return 0;
}

static struct nm_desc *nm_open_kern(const char *ifname, const struct nmreq,
				uint64_t new_flags, const struct nm_desc *arg)
{
	struct nm_desc *d = NULL;
}


static int __init __nm_kern_init(void)
{
	printk(KERN_INFO ">>> mod nm_kern loaded!\n");
	// TODO: nm_open;
	return 0;
}
 
static void __exit __nm_kern_exit(void)
{
	printk(KERN_INFO ">>> mod nm_kern exit!\n");
}
 
module_init(__nm_kern_init);
module_exit(__nm_kern_exit);
