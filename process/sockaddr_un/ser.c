#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define PATH "/root/server"

int main(int argc,char *argv[])
{
	//1 创建套接字
	struct sockaddr_un addr;
	memset(&addr,0,sizeof(struct sockaddr_un));
	int serfd,clifd;
	ssize_t num;
	char buf[128];
	serfd = socket(AF_UNIX,SOCK_STREAM,0);

	// 绑定
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path,PATH,sizeof(addr.sun_path) - 1);
	bind(serfd,(struct sockaddr*)&addr,sizeof(struct sockaddr_un));

	// 监听
	listen(serfd,5);

	// 读写
	while(1)
	{
		clifd = accept(serfd,NULL,NULL);
		while((num = read(clifd,buf,128)) > 0)
		{
			write(STDOUT_FILENO,buf,num);
		}
		close(clifd);

	}

	return 0;
}
