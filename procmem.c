#include "procmem.h"
#include <linux/kernel.h>
#include <sys/syscall.h>
#define _SYS_PROCMEM 377

long procmem(pid_t pid, struct proc_segs * info) {
	long sysvalue;
	sysvalue = syscall(_SYS_PROCMEM, pid, info);
	return sysvalue;
}

