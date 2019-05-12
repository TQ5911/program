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
	//创建服务端套接字
	int sockfd;
	sockfd = socket(PF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		printf("创建服务端套接字失败!\n");
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
	
	// 等待监听
	int num = 5;// 最大的客户端连接数目
	if (listen(sockfd,num) == -1)
	{
		printf("服务端监听失败!\n");
		close(sockfd);
		return -1;
	}
	printf("服务端开始监听!\n");

	// 接收客户端的连接
	struct sockaddr_in cli_addr;
	int size;
	char buf[128];
	socklen_t len;
	int newsockfd;// 新套接字描述符
	newsockfd = accept(sockfd,(struct  sockaddr*)&cli_addr,&len);
	if (newsockfd == -1)
	{
		printf("接收客户端连接请求失败!\n");
		close(sockfd);
		return -1;
	}
	printf("接收客户端连接请求成功!客户端Ip:%d\n",inet_ntoa(cli_addr.sin_addr));


	// 与客户端进行通信,内容为Q时退出连接
	while(1)
	{
		// 接收客户端的信息
		size = recv(newsockfd,buf,128,0);
		buf[size] = '\0';
		printf("客户端:%s",buf);
		
		if(strncmp(buf,"Q",1) == 0)
		{
			printf("客户端退出连接!\n");
			close(newsockfd);
			break;
		}

		// 向客户端回复信息
		printf("服务端回复:");
		fgets(buf,128,stdin);
		size = send(newsockfd,buf,strlen(buf),0);
		printf("向客户端发送%d字节信息数据!\n",size);
	}
	close(sockfd);
	return 0;
}
