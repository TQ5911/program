#include<myerr.h>
#include<sys/wait.h>

int main(void)
{
	int status;
	if((status = system("date")) < 0)
		err_sys("system(date) error\n");
	pr_exit(status);
	
	if((status = system("nosuchcommand")) < 0)
		err_sys("system(nosuchcommand) error\n");
	pr_exit(status);
	

	if((status = system("who;exit 44")) < 0)
		err_sys("system(who;exit 44) error\n");
	pr_exit(status);

	exit(0);
}
