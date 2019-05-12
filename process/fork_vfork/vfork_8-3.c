#include <myerr.h>

int globvar = 6;
 
int main(void)
{
	int var;
	pid_t pid;
	
	var = 88;
	printf("before fork\n");
	
	if((pid = vfork()) < 0)
	{
		err_sys("vfork error\n");
	}
	else if(pid == 0)
	{
		globvar++;
		var++;
		_exit(0);
	}

	printf("pid = %1d,glob = %d, var = %d\n",(long)getpid(),globvar,var);
	exit(0);  
}	
 
