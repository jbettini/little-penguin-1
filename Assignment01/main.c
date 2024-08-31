#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

static int __init hello(void) 
{ 
    printk("Hello, world\n"); 
    return 0; 
} 

static void __exit clean(void) 
{ 
    printk(KERN_INFO "Cleaning up module.\n");
} 

module_init(hello); 
module_exit(clean);

/*	METHODE 2
int init_module(void)
{
    printk(KERN_INFO "Hello, World!\n");
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
}
*/


