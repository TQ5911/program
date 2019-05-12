#include <myerr.h>
#include <sys/wait.h>

char *env_init[] = {"USER=unknow", "PATH=/tmp", NULL};

int main(void)
{
    pid_t pid;
    if((pid = fork()) < 0)
    {
        err_sys("fork error\n");
    }
    else if(pid == 0)
    {
        if(execle("/root/program/process/exec/echoall_8-17.o", "echoall_8-17.o", "myarg1", "MY ARG2", (char *)0, env_init) < 0)
        {
            err_sys("execle error\n");
        }
    }

	if(waitpid(pid, NULL, 0) < 0)
    {
        err_sys("waitpid error\n");
    }

    if((pid = fork()) < 0)
    {
        err_sys("fork error\n");
    }
    else if(pid == 0)
    {
        if(execlp("/root/program/process/exec/echoall_8-17.o", "echoall_8-17.o", "only 1arg", (char *)0) < 0)
        {
            err_sys("execle error\n");
        }
    }

    exit(0);
}
