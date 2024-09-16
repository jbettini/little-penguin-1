// SPDX-License-Identifier: GPL-2.0
#include "debug_fs.h"

#define LOGIN_SIZE 8
#define LOGIN "jbettini"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jbettini");
MODULE_DESCRIPTION("id file following ass07 rules");

int id_open(struct inode *node, struct file *file)
{
	pr_info("Misc Device number %d %d - Open function called\n", imajor(node), iminor(node));
	if (file->f_mode & FMODE_READ)
		pr_info("Misc Device - Open function called with read permissions\n");
	if (file->f_mode & FMODE_WRITE)
		pr_info("Misc Device - Open function called with write permissions\n");
	return 0;
}

int id_close(struct inode *node, struct file *file)
{
	pr_info("Misc Device number %d %d - Close function called\n", imajor(node), iminor(node));
	return 0;
}

ssize_t id_write(struct file *file, const char __user *user_buf, size_t user_len, loff_t *ppos)
{
	char buf[LOGIN_SIZE];

	if (user_len != LOGIN_SIZE) {
		pr_warn("Misc Device - Write function called with incorrect login size\n");
		return -EINVAL;
	}
	if (copy_from_user(buf, user_buf, LOGIN_SIZE)) {
		pr_err("Misc Device - Error copying data from userspace\n");
		return -EFAULT;
	}
	if (memcmp(buf, LOGIN, LOGIN_SIZE) != 0) {
		pr_warn("Misc Device - Write function called with incorrect login\n");
		return -EINVAL;
	}
	pr_info("Misc Device - Write function called\n");
	return LOGIN_SIZE;
}

ssize_t id_read(struct file *file, char __user *user_buf, size_t user_len, loff_t *ppos)
{
	int	rest = LOGIN_SIZE - *ppos;

	if (!user_buf)
		return -EINVAL;
	if (*ppos >= LOGIN_SIZE)
		return 0;
	int len = user_len >= rest ? rest : user_len;

	if (copy_to_user(user_buf, (LOGIN + *ppos), len)) {
		pr_err("Misc Device - Error copying data to userspace\n");
		return -EFAULT;
	}
	pr_info("Misc Device - Read function called\n");
	*ppos += len;
	return len;
}

const struct file_operations id_fops = {
	.owner = THIS_MODULE,
	.write = id_write,
	.read = id_read,
	.open = id_open,
	.release = id_close,
};
EXPORT_SYMBOL(id_fops);
