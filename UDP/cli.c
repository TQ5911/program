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
	sockfd = socket(PF_INET,SOCK_DGRAM,0);
	if(sockfd == -1)
	{
		printf("创建套接字失败!\n");
		return -1;
	}
	else
		printf("创建套接字成功,套接字描述符为%d.\n",sockfd);
	
	//绑定ip和端口
	struct sockaddr_in ser_addr;
	bzero(&ser_addr,sizeof(struct sockaddr_in));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(PORT);
	ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	//向服务端发送信息
	char buf[128];
	int size;
	//struct sockaddr_in addr;
	socklen_t len;

	while(1)
	{
		// 向服务端发送消息
		printf("输入信息:");
		fgets(buf,128,stdin);
		size = sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&ser_addr,sizeof(struct sockaddr));
		if(size == -1)
		{
			printf("向服务端发送信息失败!\n");
			break;
		}
		else
		{
			buf[size] = '\0';
			printf("客户端:%s",buf);
			if(strncmp(buf,"goodbye",7) == 0)
			{
				printf("客户端退出交互!\n");
				break;
			}
		}

		// 接收服务端的回复消息
		//size = recvfrom(sockfd,buf,128,0,(struct sockaddr*)&addr,&len);
		size = recvfrom(sockfd,buf,128,0,(struct sockaddr*)&ser_addr,&len);
		if(size == -1)
		{
			printf("接收服务端信息出错!\n");
			break;
		}
		else
		{
			buf[size] = '\0';
			printf("服务端:%s\n",buf);
		}
	}
	close(sockfd);
	return 0;
}
