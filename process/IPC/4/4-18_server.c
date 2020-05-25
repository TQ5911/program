// 无情缘关系服务端
#include "unpipc.h"

#define FIFO1 "/home/ztq/linux_test/4/fifo.1"
#define FIFO2 "/home/ztq/linux_test/4/fifo.2"
// 服务端打开要读取的文件并返回数据给客户端(充当4-8中的子进程)
void server(int readfd,int writefd)
{
	int fd;
	ssize_t n;
	char buff[MAXLINE + 1];
	if ((n = read(readfd,buff,MAXLINE)) == 0)	// 读取待会需要打开的文件的路径
	{
		printf("end-of-file while reading pathname!\n");
	//	err_quit("end-of-file while reading pathname!\n");
	}
	buff[n] = '\0';// 末尾加'\0'
	printf("read:%s, len:%d\n",buff,n);

	if ((fd = open(buff,O_RDONLY)) < 0)	// 只读方式打开文本文件
	{
		snprintf(buff + n,sizeof(buff) - n,": can't open, %s\n",strerror(errno));
		n = strlen(buff);
		write(writefd,buff,n);// 回复错误信息
	}
	else
	{
		while((n = read(fd,buff,MAXLINE)) > 0)// 从文件中读取数据
		{
			write(writefd,buff,n);// 写入数据到管道
		}
		close(fd);
	}
}

int main()
{
	int readfd,writefd;

	if ((mkfifo(FIFO1,FILE_MODE) < 0) && (errno != EEXIST))	// 创建FIFO1管道
	{
		printf("can't create %s\n",FIFO1);
	}
	if ((mkfifo(FIFO2,FILE_MODE) < 0) && (errno != EEXIST))	// 创建FIFO2管道
	{
		unlink(FIFO1);	// 会删除所给参数指定的文件
		printf("can't create %s\n",FIFO2);
	}
	readfd = open(FIFO1,O_RDONLY,0);	// FIFO1管道的读端
	writefd = open(FIFO2,O_WRONLY,0);	// FIFO2管道的写端


	server(readfd,writefd);
	return 0;
}
