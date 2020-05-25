#include "unpipc.h"

int main()
{
	int fd[2],n;
	char c;
	pid_t childpid;

	pipe(fd);
	if ((childpid = fork()) == 0)// 子进程
	{
		sleep(3);	// 休眠三秒,这里是为了保证父进程能先执行write
		if ((n = read(fd[0],&c,1)) != 1)	// 读取一个字符到c中
		{
			printf("child: read returned %d\n",n);
		}
		printf("child: read %c\n",c);
		write(fd[1],"c",1);
		exit(0);
	}
	write(fd[1],"p",1);
	sleep(5);
	if((n = read(fd[0],&c,1)) != 1)
     {
        	printf("parent: read returned %d\n",n);
	}
	printf("parent: read %c\n",c);
	return 0;
}
