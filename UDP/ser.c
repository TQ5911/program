#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
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
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);        

	if(bind(sockfd,(struct sockaddr *)&ser_addr,sizeof(struct sockaddr)) == -1)
	{
		printf("绑定ip和端口失败!\n");
		close(sockfd);
		return -1;
	}
	else
		printf("绑定端口成功!端口号为%d\n",PORT);
	
	//等待客户端的交互
	char buf[128];
	int size;
	struct sockaddr_in cli_addr;
	bzero(&cli_addr,sizeof(struct sockaddr_in));
	socklen_t len;

	while(1)
	{
		// 接收客户端的信息
		size = recvfrom(sockfd,buf,128,0,(struct sockaddr*)&cli_addr,&len);
		if(size == -1)
		{	
			printf("接受客户端信息失败!\n");
			break;
		}
		else if(strcmp(buf,"\0") == 0)
			continue;
		else
		{
			buf[size] = '\0';
			printf("来自客户端的信息:%s",buf);
			if(strncmp(buf,"goodbye",7) == 0)
			{
				printf("退出交互!\n");
				break;
			}
		}

		// 向客户端回复信息
		printf("服务端回复:");
		fgets(buf,128,stdin);
		size = sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&cli_addr,sizeof(struct sockaddr));
		if(size == -1)
		{	
			printf("%d    %s\n",errno,strerror(errno));
			printf("向客户端发送信息失败!\n");
			break;
		}
		else
			printf("服务端:%s\n",buf);
	}
	close(sockfd);
	return 0;
}
