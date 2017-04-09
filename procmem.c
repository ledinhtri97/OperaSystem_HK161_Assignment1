#include "procmem.h"
#include <linux/kernel.h>
#include <sys/syscall.h>

long procmem(pid_t pid, struct proc_segs * info) {
	long sysvalue;
	sysvalue = syscall(377, pid, info);
	if(sysvalue==0) printf("ok\n");
	else if(sysvalue==-1) printf("failed\n");
}

int main() {
	struct proc_segs info;
	pid_t pid = getpid();
	printf("pid = %d\n), pid);
	procmem(pid, info);
}