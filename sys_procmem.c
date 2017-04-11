#include <linux/linkage.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>

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
			struct proc_segs buff;
			if(!task->mm) {
				buff.mssv = 1513656;
				buff.start_code = task->mm->start_code;
				buff.end_code = task->mm->end_code;
				buff.start_data = task->mm->start_data;
				buff.end_data = task->mm->end_data;
				buff.start_heap = task->mm->start_brk;
				buff.end_heap = task->mm->brk;
				buff.start_stack = task->mm->start_stack;
				copy_to_user(info, &buff, sizeof(buff));
				printk("Find out pid [%d]", pid);
				return 0;
			}		
		}
	}
	return -1;
}
