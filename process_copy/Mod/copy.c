#include<copy.h>
#include<errno.h>

int main(int argc,char** argv ){

	const char * srcfile = argv[1];
	const char * destfile = argv[2];
	int offset = atoi(argv[3]);

	int blocksize = atoi(argv[4]);

	int srcfd = open(srcfile,O_RDONLY);
	int destfd = open(destfile,O_WRONLY|O_CREAT|O_EXCL,0664);
	if(destfd>=0)
	{
		printf("创建了 %s 文件\n",destfile);
	}
	else {
		if(errno == EEXIST){
			destfd = open(destfile,O_WRONLY);
		}else{
			perror("open");
			return -1;
		}
	}
		
	lseek(srcfd,offset,SEEK_SET);
	lseek(destfd,offset,SEEK_SET);

	int len;
	char buffer[blocksize];
	bzero(buffer,sizeof(buffer));

	len	= read(srcfd,buffer,sizeof(buffer));
	write(destfd,buffer,len);

	close(srcfd);
	close(destfd);

	return 0;
}
