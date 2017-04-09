#include <linux/linkage.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mm.h>

struct proc_segs {
	unsigned long mssv;
	unsigned long start_code;
	unsigned long end_code;
	unsigned long start_data;
	unsigned long end_data;
	unsigned long start_heap;
	unsigned long end_heap;
	unsigned long start_stack;
};

long sys_procmem(int pid, struct proc_segs * info){
	struct task_struct * task;
	printk("Inside function \n");
	for_each_process(task) {
		printk("Finding... \n");
		if(task->pid == pid) {
			info->mssv=1513656;
			info->start_code	=		task->mm->start_code;
			info->end_code		=		task->mm->end_code;
			info->start_data	=		task->mm->start_data;
			info->end_data		=		task->mm->end_data;
			info->start_heap	=		task->mm->start_brk;
			info->end_heap		=		task->mm->brk;
			info->start_stack	=		task->mm->start_stack;
			printk("\nMy MSSV = %d", 1513656);
			printk("Code Segment start = %lu, end = %lu\n", task->mm->start_code, task->mm->end_code);
			printk("Data Segment start = %lu, end = %lu\n", task->mm->start_data, task->mm->end_data);
			printk("Heap Segment start = %lu, end = %lu\n", task->mm->start_brk, task->mm->brk);
			printk("Stack Segment start = %lu\n", task->mm->start_stack);
			return 0;
		}
	}
	printk("Pid not found\n");
	return 0;
}

int fi(void) {
	struct proc_segs info;
	int pid = 828;
	sys_procmem(pid, &info);
	return 0;
}

void fe(void) {
	printk("exit\n");
}

MODULE_LICENSE("GPL");
module_init(fi);
module_exit(fe);

