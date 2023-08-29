#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DEV_NAME "mychardev"

static dev_t dev;
static struct cdev c_dev;
static struct class *cl;

static char kernel_buf[1024];
static char user_buf[1024];

static int my_open(struct inode *i, struct file *f)
{
    return 0;
}

static int my_close(struct inode *i, struct file *f)
{
    return 0; 
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
    int to_copy = min(len, sizeof(kernel_buf));

    if (copy_to_user(buf, kernel_buf, to_copy))
        return -EFAULT;
    
    return to_copy;
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
    int to_copy = min(len, sizeof(user_buf));

    if (copy_from_user(user_buf, buf, to_copy))
        return -EFAULT;

    return to_copy;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
    .read = my_read,
    .write = my_write
};

static int __init mychardev_init(void)
{
    int ret;

    ret = alloc_chrdev_region(&dev, 0, 1, DEV_NAME);
    if (ret < 0)
        return ret;

    cdev_init(&c_dev, &fops);
    ret = cdev_add(&c_dev, dev, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev, 1);
        return ret;
    }

    cl = class_create(THIS_MODULE, DEV_NAME);
    if (IS_ERR(cl)) {
        cdev_del(&c_dev);
        unregister_chrdev_region(dev, 1);
        return PTR_ERR(cl);
    }

    device_create(cl, NULL, dev, NULL, DEV_NAME);

    return 0;
}

static void __exit mychardev_exit(void)
{
    device_destroy(cl, dev);
    class_destroy(cl);
    cdev_del(&c_dev);
    unregister_chrdev_region(dev, 1);
}

module_init(mychardev_init);
module_exit(mychardev_exit);
