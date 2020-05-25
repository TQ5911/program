#include "unpipc.h"

int main(int argc,char** argv)
{
	int mqid;
	size_t len;
	long type;
	struct msgbuf *ptr;
	if (argc != 4)
	{
		printf("usage:msgsnd <pathname><#bytes><type>\n");
	}
	len = atoi(argv[2]);
	type = atoi(argv[3]);

	mqid = msgget(ftok(argv[1],0),MSG_W);
	ptr = malloc(sizeof(long) + len);
	ptr->mtype = type;
	
	msgsnd(mqid,ptr,len,0);
	return 0;
}
