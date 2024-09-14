// SPDX-License-Identifier: GPL-2.0
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>

#define LOGIN_SIZE 8
#define LOGIN "jbettini"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jbettini");
MODULE_DESCRIPTION("A simple misc device");

static int my_open(struct inode *node, struct file *file)
{
	pr_info("Misc Device number %d %d - Open function called\n", imajor(node), iminor(node));
	if (file->f_mode & FMODE_READ)
		pr_info("Misc Device - Open function called with read permissions\n");
	if (file->f_mode & FMODE_WRITE)
		pr_info("Misc Device - Open function called with write permissions\n");
	return 0;
}

static int my_close(struct inode *node, struct file *file)
{
	pr_info("Misc Device number %d %d - Close function called\n", imajor(node), iminor(node));
	return 0;
}

static ssize_t my_write(struct file *file, const char __user *user_buf, size_t user_len, loff_t *ppos)
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

static ssize_t my_read(struct file *file, char __user *user_buf, size_t user_len, loff_t *ppos)
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


static const struct file_operations fops = {
	.owner = THIS_MODULE,
	.write = my_write,
	.read = my_read,
	.open = my_open,
	.release = my_close,
};

static struct miscdevice my_misc = {
	.name = "fortytwo",
	.minor = MISC_DYNAMIC_MINOR,
	.fops = &fops,
};

static int __init hello(void)
{
	int status = misc_register(&my_misc);

	if (status) {
		pr_err("Error: misc register\n");
		return -status;
	}
	pr_info("Hello, world\n");
	return 0;
}

static void __exit clean(void)
{
	int status = misc_deregister(&my_misc);

	if (status) {
		pr_err("Error: misc deregister\n");
		return -status;
	}
	pr_info("Cleaning up module.\n");
}

module_init(hello);
module_exit(clean);
