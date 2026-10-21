#include<copy.h>


int process_wait(void){
	pid_t zpid;
	while((zpid = wait(NULL))>0){
		printf("回收了一个僵尸进程 %d\n",zpid);
	}
	return 0;
}
