#include <myerr.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

#define DEF_PAGER "/bin/more"
#define filename "/root/program/process/pipe/read.txt"

int main()
{
	int n;
	int fd[2];
	pid_t pid;
	FILE *fp;
	
	char * pager,*argv0;
	char line[MAXLINE];
	if((fp = fopen(filename,"r")) == NULL)
		err_sys("fopen error\n");
	
	if(pipe(fd) < 0)
		err_sys("pipe error\n");
	if((pid = fork()) < 0)
		err_sys("fork error\n");
	else if(pid > 0 )
	{
		close(fd[0]);
		while( fgets(line,MAXLINE,fp) != NULL)
		{
			n = strlen(line);
			printf("read %d byte!\n",n);// 每次读一行(碰到EOF或\n)结束
			if(write(fd[1],line,n) != n)
				err_sys("write error\n");
			sleep(1);
		}
		 if(ferror(fp))
		 	err_sys("fgets error\n");
		close(fd[1]);

		if(waitpid(pid,NULL,0) < 0)
			err_sys("waitpid error\n");
		exit(0);
	}
	else
	{
		close(fd[1]);
		if(fd[0] != STDIN_FILENO)
		{
			if(dup2(fd[0],STDIN_FILENO) != STDIN_FILENO)
				err_sys("dup2 error\n");
			close(fd[0]);
		}
		if((pager = getenv("PAGER")) ==NULL )
			pager = DEF_PAGER;
		if((argv0 = strrchr(pager,'/')) != NULL)
			argv0++;
		else
			argv0 = pager;
		if(execl(pager,argv0,(char*)0) < 0)
			err_sys("execl error \n");
	}
	exit(0);
}
