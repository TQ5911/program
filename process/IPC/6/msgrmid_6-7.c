#include "unpipc.h"

int main(int argc,char** argv)
{
	int mqid;
	if (argc != 2)
	{
		printf("usage:msgrmid <pathname>\n");
	}
	mqid = msgget(ftok(argv[1],0),0);
	msgctl(mqid,IPC_RMID,NULL);
	return 0;
}
