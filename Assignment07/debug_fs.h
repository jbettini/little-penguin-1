// SPDX-License-Identifier: GPL-2.0
#ifndef MODULE_DEBUGFS_H
#define MODULE_DEBUGFS_H

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/debugfs.h>
#include <linux/fs.h>

#define LOGIN_SIZE 8
#define LOGIN "jbettini"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("An implementation of debufs");

struct module_data {
	struct dentry *dir;
	struct dentry *id_file;
};

int id_open(struct inode *node, struct file *file);
int id_close(struct inode *node, struct file *file);
ssize_t id_write(struct file *file, const char __user *user_buf, size_t user_len, loff_t *ppos);
ssize_t id_read(struct file *file, char __user *user_buf, size_t user_len, loff_t *ppos);

extern const struct file_operations id_fops;

#endif
