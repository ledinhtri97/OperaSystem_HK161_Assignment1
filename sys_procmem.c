#include <linux/linkage.h>
#include <linux/sched.h>
#include <linux/kernel.h>

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

asmlinkage long sys_procmem(int pid, struct proc_segs * info){
	struct task_struct * task;
	printk("Finding...\n");
	for_each_process(task) {
		if(task->pid == pid) {
			info->mssv=1513656;
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
			printk("Find out pid [%d]", pid);
			return 0;
		}
	}
	return -1;
}