#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/types.h>

//参数验证
int check_pram(int, const char*,int);
//切片
int block_curr(const char*,int);
//进程创建
int process_create(const char*,const char*,int);
//进程回收
int process_wait(void);
