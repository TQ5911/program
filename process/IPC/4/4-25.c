#include "unpipc.h"
struct mymesg;
#define MAXMESGDATA	(PIPE_BUF - 2 * sizeof(long))
#define MESGHDRSIZE	(sizeof(struct mymesg) - MAXMESGDATA)
struct mymesg{
	long mesg_len;			// mesg_data数据长度
	long mesg_type;		// 消息类型
	char mesg_data[MAXMESGDATA];	// 数据缓冲区
};
// 发送消息
ssize_t mesg_send(int fd,struct mymesg* mptr)
{
	if (mptr) return write(fd,mptr,MESGHDRSIZE + mptr->mesg_len);
	return -1;
}

// 接收消息
ssize_t mesg_recv(int fd,struct mymesg* mptr)
{
	size_t len;
	ssize_t n;

	if ((n = read(fd,mptr,MESGHDRSIZE)) == 0)	// 先读取一个消息头(包头)
	{
		return -1;
	}
	else if (n != MESGHDRSIZE)
	{
		printf("message header: expected %d, got %d\n",MESGHDRSIZE,n);
	}

	if ((len = mptr->mesg_len) > 0)// 先判断是否有数据
	{
		if ((n = read(fd,mptr->mesg_data,len)) != len)	// 读取数据(包体)，且数据长度为mptr->mesg_len字节
		{
			printf("message header: expected %d, got %d\n",len,n);
		}
	}
	return len;
}

// 父进程写入需要打开的文件到write管道，然后从readfd管道读取子进程返回的文本数据
void client(int readfd,int writefd)
{
	size_t len;
	ssize_t n;
	struct mymesg mesg;

	fgets(mesg.mesg_data,MAXMESGDATA,stdin);// 从标准输入中读取路径
	len = strlen(mesg.mesg_data);
	if (mesg.mesg_data[len - 1] == '\n')// fgets会读取末尾的换行,所以发送是长度要-1
		len --;
	mesg.mesg_len = len;	// 要发送的数据长度
	mesg.mesg_type = 1;		// 目前随意
	
	printf("write:%s, len:%d\n",mesg.mesg_data,len);
	mesg_send(writefd,&mesg);
	
	while((n = mesg_recv(readfd,&mesg)) > 0)
	{
		write(STDOUT_FILENO,mesg.mesg_data,n);	// 读取数据，打印到标准输出
		printf("------------------------------------\n");
	}
}
// 子进程从readfd管道读取需要打开文件的路径，读取数据，写入到writefd管道
void server(int readfd,int writefd)
{
	int fd;
	ssize_t n;
	struct mymesg mesg;
	mesg.mesg_type = 1;
	
	if ((n = mesg_recv(readfd,&mesg)) == 0)	// 读取待会需要打开的文件的路径
	{
		printf("end-of-file while reading pathname!\n");
	//	err_quit("end-of-file while reading pathname!\n");
	}
	mesg.mesg_data[n] = '\0';// 末尾加'\0'
	printf("read:%s, len:%d\n",mesg.mesg_data,n);

	if ((fd = open(mesg.mesg_data,O_RDONLY)) < 0)	// 只读方式打开文本文件
	{
		snprintf(mesg.mesg_data + n,sizeof(mesg.mesg_data) - n,": can't open, %s\n",strerror(errno));
		n = strlen(mesg.mesg_data);
		mesg_send(writefd,&mesg);// 回复错误信息
	}
	else
	{
		while((n = read(fd,mesg.mesg_data,MAXMESGDATA)) > 0)// 从文件中读取数据
		{
			mesg.mesg_len = strlen(mesg.mesg_data);
			mesg_send(writefd,&mesg);
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
