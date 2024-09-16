// SPDX-License-Identifier: GPL-2.0
#include "debug_fs.h"
#include <linux/jiffies.h>
#include <linux/types.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jbettini");
MODULE_DESCRIPTION("Jiffies file following ass07 rules.");

int jiffies_open(struct inode *node, struct file *file)
{
	pr_info("Jiffies Device number %d %d - Open function called\n", imajor(node), iminor(node));
	if (file->f_mode & FMODE_READ)
		pr_info("Jiffies Device - Open function called with read permissions\n");
	if (file->f_mode & FMODE_WRITE) {
		pr_err("Error: Jiffies Device - Open function called with write permissions\n");
		return -EPERM;
	}
	return 0;
}

int jiffies_close(struct inode *node, struct file *file)
{
	pr_info("Jiffies Device number %d %d - Close function called\n", imajor(node), iminor(node));
	return 0;
}

ssize_t jiffies_read(struct file *file, char __user *user_buf, size_t user_len, loff_t *ppos)
{
	if (!user_buf)
		return -EINVAL;
	char buf[64];
	u64 jiffies = get_jiffies_64();
	int len = snprintf(buf, sizeof(buf), "%llu", jiffies);

	pr_info("Jiffies Device - Read function called\n");
	return simple_read_from_buffer(user_buf, user_len, ppos, buf, len);
}

const struct file_operations jiffies_fops = {
	.owner = THIS_MODULE,
	.read = jiffies_read,
	.open = jiffies_open,
	.release = jiffies_close,
};
EXPORT_SYMBOL(jiffies_fops);
