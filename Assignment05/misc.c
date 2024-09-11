#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>

#define LOGIN_SIZE 8
#define LOGIN "jbettini"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jbettini");
MODULE_DECRIPTION("A simple misc device");
	
static int my_open(struct inode *node, struct file *file) {
	printk(KERN_INFO "Misc Device number %d %d - Open function called\n", imajor(inode), iminor(inode));
	if (file->f_mode & FMODE_READ)
		printk(KERN_INFO "Misc Device - Open function called with read permissions\n");
	if (file->f_mode & FMODE_WRITE)
		printk(KERN_INFO "Misc Device - Open function called with write permissions\n");
	return 0;
}

static int my_close(struct inode *node, struct file *file) {
	printk(KERN_INFO "Misc Device number %d %d - Close function called\n", imajor(inode), iminor(inode));
	return 0;
}

static int my_write(struct file *file, const char *user_buf, size_t user_len, lofft_t *ppos) {
	char buf[LOGIN_SIZE];
	
	if (user_len != LOGIN_SIZE) {
		printk(KERN_INFO "Misc Device - Write function called with incorrect login\n");
		return -EINVAL;
	}
	if (copy_from_user(buf, user_buf, LOGIN_SIZE)) {
		printk(KERN_INFO "Misc Device - Error copying data from userspace\n");
		return -EFAULT;
	}
	if (memcmp(buf, LOGIN, LOGIN_SIZE) != 0) {
		printk(KERN_INFO "Misc Device - Write function called with incorrect login\n");
		return -EINVAL;
	}
	printk(KERN_INFO "Misc Device - Write function called\n");
	return LOGIN_SIZE;
}

static char *my_read(struct file *file, const char *user_buf, size_t user_len, lofft_t *ppos) {
	int	rest = LOGIN_SIZE - *ppos;
	if (!user_buf)
		return -EINVAL;
	if (*ppos >= LOGIN_SIZE)
		return 0;
	int len = user_len >= rest ? rest : user_len;
	if (copy_to_user(user_buf, (LOGIN + *ppos), len)) {
		printk(KERN_INFO "Misc Device - Error copying data to userspace\n");
		return -EFAULT;
	}
	printk(KERN_INFO "Misc Device - Read function called\n");
	*ppos += len;
	return len;
}


static const struct file_operations fops = {
	.owner = THIS_MODULE,
	.write = my_write,
	.read = my_read,
	.open = my_open,
	.release = my_close,
}

static struct miscdevice my_misc = {
	.name = "fortytwo",
	.minor = MISC_DYNAMIC_MINOR,
	.fops = &fops,
}

static int __init hello(void) 
{ 
	int status = misc_register(&my_misc);
	if (status) {
		printk(KERN_INFO "Error: misc register\n");
		return -status;
	}
	printk("Hello, world\n"); 
	return 0; 
} 

static void __exit clean(void) 
{ 
	printk(KERN_INFO "Cleaning up module.\n");
	misc_deregister(&my_misc);
} 

module_init(hello); 
module_exit(clean);
