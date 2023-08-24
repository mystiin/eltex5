#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define BUFFER_SIZE 1024

static char proc_buffer[BUFFER_SIZE]; 

static ssize_t proc_read(struct file *file, char __user *ubuf, size_t count, loff_t *ppos)
{
    int ret = 0;
    if (*ppos > 0 || count < BUFFER_SIZE) 
        return 0;

    if (copy_to_user(ubuf, proc_buffer, BUFFER_SIZE)) {
        ret = -EFAULT;
    } else {
        *ppos = BUFFER_SIZE;
        ret = BUFFER_SIZE; 
    }

    return ret;
}

static ssize_t proc_write(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos)
{
    if (copy_from_user(proc_buffer, ubuf, count))
        return -EFAULT;

    return count;
}


static const struct file_operations proc_fops = {
    .owner = THIS_MODULE,
    .read = proc_read,
    .write = proc_write,
};

static int __init proc_module_init(void)
{
    proc_create("proc_module", 0, NULL, &proc_fops);
    return 0;
}

static void __exit proc_module_exit(void)
{
    remove_proc_entry("proc_module", NULL);
}

module_init(proc_module_init);
module_exit(proc_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Proc FS Module");
MODULE_AUTHOR("mystiin");