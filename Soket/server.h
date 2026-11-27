#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<sys/fcntl.h>
#include<time.h>
#include<errno.h>
#include<string.h>
#include<pthread.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/select.h>

#define _SERVER_IP "192.168.64.129"
#define _SERVER_PROT 8080
#define _BACKLOG 128


int net_initializer(char*ip,int port){
	//server init
	int server_sock;
	if((server_sock = socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket create error");
	}
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	if(!ip) 
		server_addr.sin_addr.s_addr = INADDR_ANY;
	else 
		inet_pton(AF_INET,ip,&server_addr.sin_addr.s_addr);

	if((bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1))
		perror("net init bind error");

	listen(server_sock,_BACKLOG);

	return server_sock;
}

int first_response(int sock,char*cip){
	//首次响应
	char response[1500];
	bzero(response,sizeof(response));
	sprintf(response,"Hi [%s] connect server success...\n",cip);
	send(sock,response,strlen(response),0);
	return 0;
}

