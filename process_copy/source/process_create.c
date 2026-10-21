#include<copy.h>


int process_create(const char* srcfile,const char* destfile, int pronum){

pid_t pid;

int offset = 0;
int blocksize = block_cur(srcfile,pronum);

//创建多进程

int i;
for(i=0;i< pronum;i++){

pid = fork();

//父进程
if(pid > 0){
	process_wait();
}
else if(pid == 0){
	offset = i*blocksize;
	printf("%d 使用 execl %d\n",getpid(),i);

	char off_set[10];
	char block_size[10];
bzero(off_set,sizeof(10));
bzero(block_size,sizeof(10));

	sprintf(off_set,"%d",offset);
	sprintf(block_size,"%d",blocksize);
	execl("/home/colin/20251018/Process/process_copy/Mod/copy","copy",srcfile,destfile,off_set,block_size,NULL);
}

if(pid == 0) break;
}
return 0;
}
