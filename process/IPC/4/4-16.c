#include "unpipc.h"

#define FIFO1 "/home/ztq/linux_test/4/fifo.1"
#define FIFO2 "/home/ztq/linux_test/4/fifo.2"
// 父进程写入需要打开的文件到write管道，然后从readfd管道读取子进程返回的文本数据
void client(int readfd,int writefd)
{
	size_t len;
	ssize_t n;
	char buff[MAXLINE];

	fgets(buff,MAXLINE,stdin);// 从标准输入中读取路径
	len = strlen(buff);
	if (buff[len - 1] == '\n')// fgets会读取末尾的换行,所以发送是长度要-1
		len --;

	printf("write:%s, len:%d\n",buff,len);
	write(writefd,buff,len);
	
	while((n = read(readfd,buff,MAXLINE)) > 0)
		write(STDOUT_FILENO,buff,n);	// 读取数据，打印到标准输出
}
// 子进程从readfd管道读取需要打开文件的路径，读取数据，写入到writefd管道
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
	pid_t childpid;

	if ((mkfifo(FIFO1,FILE_MODE) < 0) && (errno != EEXIST))	// 创建FIFO1管道
	{
		printf("can't create %s\n",FIFO1);
	}
	if ((mkfifo(FIFO2,FILE_MODE) < 0) && (errno != EEXIST))	// 创建FIFO2管道
	{
		unlink(FIFO1);	// 会删除所给参数指定的文件
		printf("can't create %s\n",FIFO2);
	}
	if ((childpid = fork()) == 0)
	{
		readfd = open(FIFO1,O_RDONLY,0);	// FIFO1管道的读端
		writefd = open(FIFO2,O_WRONLY,0);	// FIFO2管道的写端
		server(readfd,writefd);
		exit(0);
	}
	// 下面这两行语句不能调换
	writefd = open(FIFO1,O_WRONLY,0);	// FIFO1管道的写端
	readfd = open(FIFO2,O_RDONLY,0);	// FIFO2管道的读端

	client(readfd,writefd);

	waitpid(childpid,NULL,0);

	close(readfd);
	close(writefd);
	unlink(FIFO1);
	unlink(FIFO2);
	return 0;
}
