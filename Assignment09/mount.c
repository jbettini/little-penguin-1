// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/nsproxy.h>
#include <linux/ns_common.h>
#include <linux/init.h>
#include <../fs/mount.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jbettini");
MODULE_DESCRIPTION("An implementation of /proc/mounts");

static struct proc_dir_entry *proc_entry;

static void traverse_mounts(struct mount *mnt, struct seq_file *m)
{
    struct mount *child;
    struct path path;
    char *buf = kmalloc(PATH_MAX, GFP_KERNEL);

    list_for_each_entry(child, &mnt->mnt_mounts, mnt_child) {
	path.mnt = &child->mnt;
	path.dentry = path.mnt->mnt_root;
    	seq_printf(m, "%-15s%s\n", child->mnt_devname, d_path(&path, buf, PATH_MAX));
	kfree(buf);
	traverse_mounts(child, m);
    }
}

static int mounts_show(struct seq_file *m, void *v)
{
    struct mnt_namespace *ns = current->nsproxy->mnt_ns;

    if (!ns) {
        seq_puts(m, "Error: Unable to access mount namespace\n");
        return 0;
    }

    traverse_mounts(ns->root, m);

    return 0;
}
static int __init simple_init(void)
{
	proc_entry = proc_create_single("mymounts", 0666, NULL, mounts_show);
	return 0;
}

static void __exit simple_cleanup(void)
{
	proc_remove(proc_entry);
}

module_init(simple_init);
module_exit(simple_cleanup);
