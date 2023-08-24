#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>

static int value = 0; 

static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", value); 
}

static ssize_t sysfs_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    sscanf(buf, "%du", &value);

    if (value & 1)
        turn_on_led1(); 
    else
        turn_off_led1();

    if (value & 2)
        turn_on_led2();
    else
        turn_off_led2();

    if (value & 4)
        turn_on_led3();
    else
        turn_off_led3();

    return count;
}

static struct kobject *kobj_ref;
static struct kobj_attribute sysfs_attr = __ATTR(leds, 0660, sysfs_show, sysfs_store);

static int __init sysfs_keyboard_init(void) 
{
    ...

    kobj_ref = kobject_create_and_add("kbd_leds", kernel_kobj);
    if (!kobj_ref)
        return -ENOMEM;

    if (sysfs_create_file(kobj_ref, &sysfs_attr.attr)) {
        kobject_put(kobj_ref);
        return -EFAULT;
    }

    return 0;
}

static void __exit sysfs_keyboard_exit(void)
{
    kobject_put(kobj_ref);
}

module_init(sysfs_keyboard_init);
module_exit(sysfs_keyboard_exit);