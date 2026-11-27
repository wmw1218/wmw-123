#include"server.h"

int server_start(void){
	//start
	int server_sock;
	int client_sock;


	struct sockaddr_in client_addr;
	socklen_t addrlen;
	char cip[16];
	char response[1500];
	int recvlen;

	time_t tp;
	char time_buf[1024];
	char* msg = "Please tryagain...\n";

	server_sock = net_initializer(_SERVER_IP,_SERVER_PROT);

	fd_set set,oset;
	FD_ZERO(&set);
	FD_SET(server_sock,&set);

	int readynum;
	oset = set;
	int maxfd = 4;
	int temp = 0;
	printf("server start...\n");
	while(1){
		oset = set;
		readynum = select(maxfd+1,&oset,NULL,NULL,NULL);
		if(readynum>0){
			temp = 0;
			for(int i=0;i<maxfd+1;i++){
				if(FD_ISSET(i,&oset)>0){
					if(server_sock == i){
						//处理连接
						addrlen = sizeof(client_addr);
						client_sock = accept(server_sock,(struct sockaddr*)&client_addr,&addrlen);
						memset(cip,0,sizeof(cip));
						inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,cip,16);
						first_response(client_sock,cip);
						printf("server [%s] connect client [%s] success...\n",_SERVER_IP,cip);
						//将新连接的sock加入set中
						FD_SET(client_sock,&set);
						if(client_sock >maxfd)maxfd+=client_sock;
					}
					else{/*处理客户端发送的消息*/
						client_sock = i;
						memset(response,0,sizeof(response));
						recvlen = recv(client_sock,response,sizeof(response),0);
						if(recvlen > 0){
						response[strlen(response)-1] = '\0';
						if(strcmp(response,"time")==0){
							/*response localtime*/
							tp = time(NULL);//获取时间种子
							memset(time_buf,0,sizeof(time_buf));
							ctime_r(&tp,time_buf);//时间种子转换为字符串时间
							send(client_sock,time_buf,strlen(time_buf),MSG_NOSIGNAL);
						}else{

							/*response please tryagain*/
							send(client_sock,msg,strlen(msg),MSG_NOSIGNAL);
						}
					}
					else if(recvlen == 0){
							printf("client exit, close client_sock = %d exit\n",client_sock);
							//将set中对应的client_sock清除
							FD_CLR(client_sock,&set);
							if(client_sock == maxfd)temp = 1;
							close(client_sock);
						}else{
							perror("server_start : recv call failed!");
						}
					}

				}
			}
			//更新maxfd大小
			if(temp == 1){
				for(int i = 0;i<maxfd +1;i++){
					if(FD_ISSET(i,&set)>0)maxfd = i;
				}
			}
		}
	}
	return 0;
}



int main(){

	server_start();


	return 0;
}
