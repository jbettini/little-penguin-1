// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/printk.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jbettini");
MODULE_DESCRIPTION("An exemple of a good coding style");

/*
 * A long sleep, and tell userspace about it
 */

static int wait_and_return_square(int *i)
{
	int y = *i;
	int x = 0;

	while (x++ < i)
		udelay(10);
	if (y < 10)
		pr_info("We slept a long time!");
	return x * y;
}

static int __init my_init(void)
{
	int x = 10;

	return wait_and_return_square(&x);
}

static void __exit my_exit(void)
{
}

module_init(my_init);
module_exit(my_exit);
