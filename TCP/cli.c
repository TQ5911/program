#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT  3000

int main()
{
	//创建套接字
	int sockfd;
	sockfd = socket(PF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		printf("客户端创建套接字失败!\n");
		return -1;
	}
	else
		printf("创建套接字成功,套接字描述符为%d.\n",sockfd);
	
	// 向服务端发起连接请求
	struct sockaddr_in ser_addr;
	bzero(&ser_addr,sizeof(struct sockaddr_in));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(PORT);
	ser_addr.sin_addr.s_addr = inet_addr("118.24.251.43");
	if (connect(sockfd,(struct  sockaddr*)&ser_addr,sizeof(struct sockaddr)) == -1)
	{
		printf("请求连接服务器失败!\n");
		close(sockfd);
		return -1;
	}


	// 与服务端进行通信
	char buf[128];
	int size;
	while(1)
	{
		// 向服务端发送消息
		printf("输入信息:");
		fgets(buf,128,stdin);
		size = send(sockfd,buf,strlen(buf),0);
		printf("向服务端发送%d字节的数据\n",size);
		
		if(strncmp(buf,"Q",1) == 0)
		{
			printf("断开和服务端的连接!\n");
			break;
		}

		// 接收服务端的回复消息
		size = recv(sockfd,buf,128,0);
		buf[size] = '\0';
		printf("服务端:%s",buf);
	}
	close(sockfd);
	return 0;
}
