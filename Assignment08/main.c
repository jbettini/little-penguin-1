// SPDX-License-Identifier: GPL-2.0
MODULE_LICENSE("GPL");
MODULE_AUTHOR("jbettini");
MODULE_DESCRIPTION("Misc Device");

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/slab.h>

char str[PAGE_SIZE];

ssize_t my_read(struct file *_fp, char __user *user, size_t size, loff_t *offs)
{
	char tmp[PAGE_SIZE];

	size_t t = -1;
	size_t i = -1;

	while (t < PAGE_SIZE && str[t])
		tmp[++i] = str[++t];
	tmp[++i] = '\0';

	return simple_read_from_buffer(user, size, offs, tmp, i);
}

ssize_t my_write(struct file *_fp, const char __user *user, size_t size, loff_t *offs)
{
	ssize_t res;

	res = simple_write_to_buffer(str, size, offs, user, size) + 1;
	str[size + 1] = '\0';
	return res;
}

static const struct file_operations myfd_fops = {
	.owner = THIS_MODULE,
	.read = &my_read,
	.write = &my_write
};

static struct miscdevice myfd_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "reverse",
	.fops = &myfd_fops
};

static int __init myfd_init(void)
{
	int retval = misc_register(&myfd_device);

	if (retval) {
		pr_info("Error: misc register\n");
		return -retval;
	}
	return 0;
}

static void __exit myfd_cleanup(void)
{
	pr_info("Cleaning up module.\n");
	misc_deregister(&my_misc);
}

module_init(myfd_init);
module_exit(myfd_cleanup);
