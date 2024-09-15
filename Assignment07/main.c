#include "debug_fs.h" 

struct module_data *data;

static int __init hello_init(void)
{
	data = kmalloc(sizeof(struct module_data), GFP_KERNEL);
	if (!data) {
		pr_err("Failed to allocate memory for module_data\n");
		return -ENOMEM;
	}
	data->dir = debugfs_create_dir("fortytwo", NULL);

	if (!(data->dir)) {
		pr_err("Error: debugfs_create_dir failed, check if the kernel has been built with debugfs support");
		return -ENODEV;
	}
	data->id_file = debugfs_create_file("id", 0666, data->dir, NULL, &id_fops);
	if (!(data->id_file)) {
		debugfs_remove_recursive(data->dir);
		pr_err("Error: debugfs_create_file failed.");
		return -ENODEV;
	}
	pr_info("Module Debugfs Created.\n");
	return 0;
}

static void __exit hello_exit(void)
{
	debugfs_remove_recursive(data->dir);
	kfree(data);
	pr_info("Cleaning up module.\n");
}

module_init(hello_init);
module_exit(hello_exit);

