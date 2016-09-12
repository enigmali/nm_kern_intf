#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/hrtimer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Enigma Li <lizhilong.enigma@gmail.com>");
MODULE_DESCRIPTION("The Module to Operate Netmap in Kernel Space.");

static int time_measure_end(void)
{
	return 0;
}
EXPORT_SYMBOL(time_measure_end);

static int __init __nm_kern_init(void)
{
    printk(KERN_INFO ">>> mod nm_kern loaded!\n");
    return 0;
}
 
static void __exit __nm_kern_exit(void)
{
    printk(KERN_INFO ">>> mod nm_kern exit!\n");
}
 
module_init(__nm_kern_init);
module_exit(__nm_kern_exit);
