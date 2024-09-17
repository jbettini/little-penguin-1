// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jbettini");
MODULE_DESCRIPTION("Reverse Misc Device");

char str[PAGE_SIZE];

static ssize_t my_read(struct file *_fp, char __user *user, size_t size, loff_t *offs)
{

	size_t i = 0;
	ssize_t t = strlen(str);
	char *tmp = kmalloc(sizeof(char) * PAGE_SIZE + 1, GFP_KERNEL);

	while (t >= 0)
		tmp[i++] = str[t--];
	ssize_t ret = simple_read_from_buffer(user, PAGE_SIZE, offs, tmp, i);

	if (ret < 0)
		pr_err("Error: simple_read_from_buffer Fail");
	kfree(tmp);
	pr_info("Function Read Called");
	return ret;
}

static ssize_t my_write(struct file *_fp, const char __user *user, size_t size, loff_t *offs)
{
	ssize_t ret = simple_write_to_buffer(str, size, offs, user, size);

	if (ret < 0)
		pr_err("Error: simple_read_from_buffer Fail");
	pr_info("Function Write Called");
	return ret;
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
		pr_err("Error: misc register\n");
		return -retval;
	}
	return 0;
}

static void __exit myfd_cleanup(void)
{
	misc_deregister(&myfd_device);
	pr_info("Cleaning up module.\n");
}

module_init(myfd_init);
module_exit(myfd_cleanup);
