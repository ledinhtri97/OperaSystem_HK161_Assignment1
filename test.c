#include <linux/linkage.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mm.h>

static int pid = 1;

static struct proc_segs {
	unsigned long mssv;
	unsigned long start_code;
	unsigned long end_code;
	unsigned long start_data;
	unsigned long end_data;
	unsigned long start_heap;
	unsigned long end_heap;
	unsigned long start_stack;
};

static long sys_procmem(int pid_, struct proc_segs * info) {
	struct task_struct * task;
	printk(KERN_INFO "Inside function \n");
	for_each_process(task) {
		printk(KERN_INFO "Finding... \n");
		if(task->pid == pid_) {
			if(!task->mm) {
				info->start_code = task->mm->start_code;
				info->end_code = task->mm->end_code;
				info->start_data = task->mm->start_data;
				info->end_data = task->mm->end_data;
				info->start_heap = task->mm->start_brk;
				info->end_heap = task->mm->brk;
				info->start_stack = task->mm->start_stack;
			}
			else {
				info->start_code = task->active_mm->start_code;
				info->end_code = task->active_mm->end_code;
				info->start_data = task->active_mm->start_data;
				info->end_data = task->active_mm->end_data;
				info->start_heap = task->active_mm->start_brk;
				info->end_heap = task->active_mm->brk;
				info->start_stack = task->active_mm->start_stack;
			}
			return 0;
		}
	}
	return -1;
}

static int __init fi(void) {
	long res;
	struct proc_segs info;
	res = sys_procmem(pid, &info);
	if(res == 0) {
			printk(KERN_INFO "\nMy MSSV = %lu", info.mssv);
			printk(KERN_INFO "Code Segment start = %lu, end = %lu\n", info.start_code, info.end_code);
			printk(KERN_INFO "Data Segment start = %lu, end = %lu\n", info.start_data, task->mm->end_data);
			printk(KERN_INFO "Heap Segment start = %lu, end = %lu\n", info.start_heap, info.end_heap);
			printk(KERN_INFO "Stack Segment start = %lu\n", info.start_stack);
	}
	else
		printk(KERN_INFO "Pid not found\n");
	return 0;
}

static void __exit fe(void) {
	printk(KERN_INFO "exit\n");
}

MODULE_LICENSE("GPL");
module_init(fi);
module_exit(fe);
module_param(pid, int, 0);
