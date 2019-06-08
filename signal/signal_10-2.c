#include <myerr.h>
 
static void sig_usr1(int);

int main(void)
{
	if(signal(SIGUSR1, sig_usr1) == SIG_ERR)
		err_sys("can not catch SIGUSR1\n");
	if(signal(SIGUSR2, sig_usr1) == SIG_ERR)
		err_sys("can not catch SIGUSR2\n");
	for(;;)
		pause();
}

static void sig_usr1(int signo)
{
	if(signo == SIGUSR1)
		printf("received SIGUSR1\n");
	else if(signo == SIGUSR2)
		printf("received SIGUSR2\n");
	else
		err_dump("received signal %d\n", signo);
}

