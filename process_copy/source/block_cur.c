#include<copy.h>

int block_cur(const char* srcfile,int pronum){

int fd = open(srcfile,O_RDONLY);
	

	int size = lseek(fd,0,SEEK_END);

	int blocksize = size/pronum;
	
	if(size%pronum!=0){
	blocksize += 1;
	}
close(fd);

return blocksize;

}

