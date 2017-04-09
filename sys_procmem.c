#include <linux/linkage.h>
#include <linux/sched.h>

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
	for_each_process(task) {
		if(task->pid == pid) {
			info->mssv=1513656;
			info->start_code	=		task->mm->start_code;
			info->end_code		=		task->mm->end_code;
			info->start_data	=		task->mm->start_data;
			info->end_data		=		task->mm->end_data;
			info->start_heap	=		task->mm->start_sbrk;
			info->end_heap		=		task->mm->brk;
			info->start_stack	=		task->mm->start_stack;
			printk("\nMy MSSV = %d", 1513656);
			printk("Code Segment start = %lu, end = %lu\n", task->mm->start_code, task->mm->end_code);
			printk("Data Segment start = %lu, end = %lu\n", task->mm->start_data, task->mm->end_data);
			printk("Heap Segment start = %lu, end = %lu\n", task->mm->start_heap, task->mm->end_heap);
			printk("Stack Segment start = %lu\n", task->mm->start_stack);
			break;
		}
	}
	return 0;
}