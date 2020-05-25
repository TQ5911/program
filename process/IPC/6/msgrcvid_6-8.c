#include "unpipc.h"
#define MAXMSG (8192 + sizeof(long))

int main(int argc,char** argv)
{
	int mqid;
	ssize_t n;
	struct msgbuf *buff;
	if (argc != 2)
	{
		printf("usage ：msgrcvid <mqid>\n");
	}
	mqid = atoi(argv[1]);
	buff = malloc(MAXMSG);
	n = msgrcv(mqid,buff,MAXMSG,0,0);
	printf("read:%d bytes, type = %ld\n",n,buff->mtype);
	return 0;
}

