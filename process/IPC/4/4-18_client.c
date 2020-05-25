#include "unpipc.h"

#define FIFO1 "/home/ztq/linux_test/4/fifo.1"
#define FIFO2 "/home/ztq/linux_test/4/fifo.2"
// 客户端发送要读取的文件，打印返回的数据(充当4-8中的父进程)
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

int main()
{
	int readfd,writefd;

	// 下面这两行语句不能调换
	writefd = open(FIFO1,O_WRONLY,0);	// FIFO1管道的写端
	readfd = open(FIFO2,O_RDONLY,0);	// FIFO2管道的读端

	client(readfd,writefd);

	close(readfd);
	close(writefd);
	unlink(FIFO1);
	unlink(FIFO2);
	return 0;
}
