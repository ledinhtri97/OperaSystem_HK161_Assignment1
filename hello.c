#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LE DINH TRI");

static int hi = 3;

module_param(hi, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

struct proc_segs {
 unsigned long mssv;
 unsigned long start_code;
 unsigned long end_code;
};

static long sys_procmem(int pid, struct proc_segs * info) {
 struct task_struct * p;
 printk(KERN_INFO "Finding...\n");
 for_each_process(p) {
	if(p->pid == pid) {
	 info->mssv = 1513656;
	 info->start_code = p->mm->start_code; info->end_code = p->mm->end_code;
	 printk(KERN_INFO "ok! found out\n");
	 return 0;
	}
 }
 return -1;
}

static int __init hello_init(void) {
	struct proc_segs info;
	long rv;
	printk(KERN_INFO "Hello, world %d\n", hi);
	rv = sys_procmem(hi, &info);
	if(rv == 0) {
	 printk(KERN_INFO "mssv = %lu \n| start_code = %lu | end_code = %lu\n", info.mssv, info.start_code, info.end_code);
	}
	else printk(KERN_INFO "not foud!\n");
	return 0;
}

static void __exit hello_exit(void) {
	printk(KERN_INFO "goodbye, ...\n");
}

module_init(hello_init);
module_exit(hello_exit);
