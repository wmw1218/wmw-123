#include<copy.h>


int check_pram(int argc,const char*srcfile,int pronum){
	if(argc<3){
		printf("参数数量小于3\n");
		return -1;
	}
	if(access(srcfile,F_OK)!=0){
		printf("目标文件不存在\n");
		return -1;
	}
	if(pronum<1){
		printf("进程数量不能小于1\n");
		return -1;
	}
	if(pronum>100){
		printf("进程数量不能大于100\n");
		return -1;
	}
	return 0;
}
