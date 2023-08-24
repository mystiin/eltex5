#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kobject.h>

static int value = 0;

static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
    return sprintf(buf, "%d\n", value);
}

static ssize_t sysfs_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
    sscanf(buf, "%du", &value);
    return count;
}


static struct kobj_attribute sysfs_attribute =__ATTR(myvalue, 0660, sysfs_show, sysfs_store);

static struct kobject *sysfs_kobject;


static int __init sysfs_module_init(void) {
    int error = 0;

    sysfs_kobject = kobject_create_and_add("sysfs_module", kernel_kobj);
    if(!sysfs_kobject) {
        return -ENOMEM;
    }

    error = sysfs_create_file(sysfs_kobject, &sysfs_attribute.attr);
    if(error) {
        kobject_put(sysfs_kobject);
    }
    return error;
}

static void __exit sysfs_module_exit(void) {
    kobject_put(sysfs_kobject);
}

module_init(sysfs_module_init);
module_exit(sysfs_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("mystiin");
MODULE_DESCRIPTION("SysFS Module");