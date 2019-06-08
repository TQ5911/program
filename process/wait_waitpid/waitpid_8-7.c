#include <myerr.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	if((pid = fork()) < 0)
		err_sys("fork error\n");
	else if(pid == 0)
	{
		if((pid = fork()) < 0)
			err_sys("fork error\n");
		else if(pid > 0)
			exit(0);
		
		sleep(3);
		printf("second child,parent pid = %ld\n",(long)getppid());
		exit(0);
	}

	if(waitpid(pid,NULL,0) != pid)
		err_sys("waitpid error\n");

	exit(0);
}