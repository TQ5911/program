#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#define PATH "/root/server"
int main(int argc,char *argv[])
{
	struct sockaddr_un addr = {0};
	int serfd;
	ssize_t num;
	char buf[128];

	//1 套接字
	serfd = socket(AF_UNIX,SOCK_STREAM,0);
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path,PATH,sizeof(addr.sun_path) - 1);

	// 连接
	connect(serfd,(struct sockaddr*)&addr,sizeof(addr));

	// 读写
	while ((num = read(STDIN_FILENO,buf,128)) > 0)
	{
		write(serfd,buf,num);
	}
	return 0;
}
