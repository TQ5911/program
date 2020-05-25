#include "unpipc.h"
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
	int pipe1[2],pipe2[2];
	pid_t childpid;
	// 创建两个管道
	pipe(pipe1);
	pipe(pipe2);

	if ((childpid = fork()) == 0)
	{
		// 子进程关闭管道1的写，2的读
		close(pipe1[1]);
		close(pipe2[0]);
		server(pipe1[0],pipe2[1]);
		exit(0);
	}
	
	// 父进程关闭管道1的读，2的写
	close(pipe1[0]);
	close(pipe2[1]);
	client(pipe2[0],pipe1[1]);
	waitpid(childpid,NULL,0);

	exit(0);
}
