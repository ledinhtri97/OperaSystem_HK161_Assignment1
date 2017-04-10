#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/stat.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LE DINH TRI");

static int pid_input = 1;

module_param(pid_input, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

struct proc_segs {
 unsigned long mssv;
 unsigned long start_code;
 unsigned long end_code;
};

static long sys_procmem(int pid, struct proc_segs * info) {
 struct task_struct * p;
 printk(KERN_INFO "Finding...\n");
 for_each_process(p) {
	printk("[%d] | [%s]\n", p->pid, p->comm);
	msleep(10);
	if(p->pid == pid) {
	 info->mssv = 1513656;
	 if(p->mm != NULL) {
	  printk(KERN_INFO "p->mm not null !\n");
	  info->start_code = p->mm->start_code; info->end_code = p->mm->end_code;
	  return 0;
	 } else if(p->active_mm == NULL)
	  printk(KERN_INFO "p->mm is null, we in a thread, useing active_mm");
	}
 }
 return -1;
}

static int __init hello_init(void) {
	struct proc_segs info;
	long rv;
	printk(KERN_INFO "Hello, world %d\n", pid_input);
	rv = sys_procmem(pid_input, &info);
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
