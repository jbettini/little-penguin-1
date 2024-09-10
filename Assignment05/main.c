#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>

#define MAX_SIZE 256

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

static int my_read(struct file *file, const char *user_buf, size_t user_len, lofft_t *ppos) {
		
}

static int my_write(struct file *file, const char *user_buf, size_t user_len, lofft_t *ppos) {
		
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
		printk("Hello, world\n"); 
		return -status;
	}
	return 0; 
} 

static void __exit clean(void) 
{ 
	printk(KERN_INFO "Cleaning up module.\n");
	misc_deregister(&my_misc);
} 

module_init(hello); 
module_exit(clean);
