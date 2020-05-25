// 本案例，子进程往管道里读，父进程往管道里写
#include "unpipc.h"

void father_process(int pipefd[])
{
	int i = 0;
	char writebuf[128] = {0};

	/*父进程关闭写文件描述符*/
	close(pipefd[0]);
	while(1)
	{
		sprintf(writebuf, "write pipe : %d", i);
		/*父进程往管道写入数据*/
		write(pipefd[1], writebuf, strlen(writebuf));
		printf("father write pipe: %s\n", writebuf);
		i = (i + 1) % 10;
		sleep(1);	// 休眠一秒
	}
}

void child_process(int pipefd[])
{
	char readbuf[128] = {0};
	/*子进程关闭写文件描述符*/
	close(pipefd[1]);
	while(1)
	{
		/*子进程从管道中读取数据*/
		read(pipefd[0], readbuf, sizeof(readbuf));
		printf("child read pipe: %s\n", readbuf);
	}
}

int main()
{       
	int pipefd[2];	// 父子进程通信管道
	pid_t pid;
	if (pipe(pipefd) == -1)
	{
		perror("pipe error!\n");
		return -1;
	}
	pid = fork();	// 创建进程
	if (pid == 0)	// 子进程
	{
		child_process(pipefd);
	}
	else if (pid != -1)
	{
		father_process(pipefd);
	}
	else
	{
		perror("fork error!\n");
	}
        printf("hello pipe\n");
        return 0;
}
