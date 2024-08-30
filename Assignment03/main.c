// SPDX-License-Identifier: GPL-2.0

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/printk.h>

MODULE_LICENSE("GPL");

/* 
A long sleep, and tell userspace about it
*/
int wait_and_return_square(int i)
{
	udelay(10 * i);
	if (i < 10)
		pr_info("We slept a long time!");
	return i * i;
}

static int __init my_init(void)
{
	return wait_and_return_square(10);
}

static void __exit my_exit(void)
{
}

module_init(my_init);
module_exit(my_exit);
