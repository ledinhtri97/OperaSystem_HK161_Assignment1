#include <procmem.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

long procmem(pid_t pid, struct proc_segs * info);

int main(int argc, char * argv[]) {
	if(argc < 2 ){
		printf("you must put pid need to find\n");
		exit(1);
	}
	else {
		pid_t mypid = (pid_t) atoi(argv[1]); // getpid();
		printf("PID: %d\n", mypid);
		struct proc_segs info;
		int res = procmem(mypid, &info);
		if(res == 0) {
			printf("Student ID: %lu\n", info.mssv);
			printf("Code segment: start = 0x%lx, end = 0x%lx\n", info.start_code, info.end_code);
			printf("Data segment: start = 0x%lx, end = 0x%lx\n", info.start_data, info.end_data);
			printf("Heap segment: start = 0x%lx, end = 0x%lx\n", info.start_heap, info.end_heap);
			printf("Stack stack: start = 0x%lx\n", info.start_stack);
		}
		else {
			printf("Cannot get information from the process %d\n", mypid);
		}
	}
}
