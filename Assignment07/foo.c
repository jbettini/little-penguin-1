// SPDX-License-Identifier: GPL-2.0
#include "debug_fs.h"
#include <linux/types.h>

static char buf[PAGE_SIZE];
static size_t len;
struct mutex foo_mutex;

int foo_open(struct inode *node, struct file *file)
{
	if (mutex_lock_interruptible(&foo_mutex))
		return -EINTR;
	pr_info("Foo Device number %d %d - Open function called\n", imajor(node), iminor(node));
	if (file->f_mode & FMODE_READ)
		pr_info("Foo Device - Open function called with read permissions\n");
	if (file->f_mode & FMODE_WRITE)
		pr_info("Foo Device - Open function called with write permissions\n");
	return 0;
}

int foo_close(struct inode *node, struct file *file)
{
	mutex_unlock(&foo_mutex);
	pr_info("Foo Device number %d %d - Close function called\n", imajor(node), iminor(node));
	return 0;
}

ssize_t foo_read(struct file *file, char __user *user_buf, size_t user_len, loff_t *ppos)
{
	int ret = simple_read_from_buffer(user_buf, user_len, ppos, buf, len);

	if (ret < 0)
		pr_err("Error: Foo Device Read function failed.");
	else
		pr_info("Foo Device - Read function called\n");
	return ret;
}

ssize_t foo_write(struct file *file, const char __user *user_buf, size_t user_len, loff_t *ppos)
{
	if (user_len + *ppos > PAGE_SIZE)
		return -ENOMEM;
	int ret = simple_write_to_buffer(buf, PAGE_SIZE, ppos, user_buf, user_len);

	len = *ppos;
	pr_info("Foo Device - Write function called\n");
	return ret;
}

const struct file_operations foo_fops = {
	.owner = THIS_MODULE,
	.read = foo_read,
	.write = foo_write,
	.open = foo_open,
	.release = foo_close,
};
EXPORT_SYMBOL(foo_fops);
