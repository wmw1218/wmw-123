#include<copy.h>


int main(int argc,char**argv){

if(argc<3)return 0;
	const char* srcfile = argv[1];

	const char* destfile = argv[2];

	int pronum = 2;
	if(argc > 3) pronum = atoi(argv[3]);

//校验参数
	if(check_pram(argc,srcfile,pronum)!=0) return 0;

//进程创建与文件拷贝
	process_create(srcfile,destfile,pronum);

	return 0;

}
