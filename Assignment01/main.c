// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Hello World module");

static int __init hello_init(void)
{
	pr_info("Hello, world\n");
	return 0;
}

static void __exit hello_exit(void)
{
	pr_info("Cleaning up module.\n");
}

module_init(hello_init);
module_exit(hello_exit);

/* Method 2
int init_module(void)
{
	pr_info("Hello, world\n");
	return 0;
}

void cleanup_module(void)
{
	pr_info("Cleaning up module.\n");
}
*/

