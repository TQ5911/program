#include "unpipc.h"
#define MAXMSG (8192 + sizeof(long))

int main(int argc,char** argv)
{
	int c,flag,mqid;
	long type;
	ssize_t n;
	struct msgbuf* buff;
	
	type = flag = 0;
	while((c = getopt(argc,argv,"nt:")) != -1)
	{
		switch(c)
		{
			case 'n': flag |= IPC_NOWAIT;break;
			case 't': type = atol(optarg);break;
		}
	}
	printf("c:%d	optind:%d\n",c,optind);
	if (optind != argc - 1)
	{
		printf("usage: masgrcv [ -n ][ -t type ]<pathname>\n");
	}	
	mqid = msgget(ftok(argv[optind],0),MSG_R);
	buff = malloc(MAXMSG);

	n = msgrcv(mqid,buff,MAXMSG,type,flag);
	printf("read:%d bytes,type = %ld\n",n,buff->mtype);
	return 0;
}
