/* SPDX-License-Identifier: GPL-2.0 */
#ifndef MODULE_DEBUG_FS_H
#define MODULE_DEBUG_FS_H

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jbettini");

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/debugfs.h>
#include <linux/fs.h>

struct module_data {
	struct dentry *dir;
	struct dentry *id_file;
	struct dentry *jiffies_file;
	struct dentry *foo_file;
};

int id_open(struct inode *node, struct file *file);
int id_close(struct inode *node, struct file *file);
ssize_t id_write(struct file *file, const char __user *user_buf, size_t user_len, loff_t *ppos);
ssize_t id_read(struct file *file, char __user *user_buf, size_t user_len, loff_t *ppos);

int jiffies_open(struct inode *node, struct file *file);
int jiffies_close(struct inode *node, struct file *file);
ssize_t jiffies_read(struct file *file, char __user *user_buf, size_t user_len, loff_t *ppos);

int foo_open(struct inode *node, struct file *file);
int foo_close(struct inode *node, struct file *file);
ssize_t foo_write(struct file *file, const char __user *user_buf, size_t user_len, loff_t *ppos);
ssize_t foo_read(struct file *file, char __user *user_buf, size_t user_len, loff_t *ppos);

extern const struct file_operations id_fops;
extern const struct file_operations jiffies_fops;
extern const struct file_operations foo_fops;

#endif
