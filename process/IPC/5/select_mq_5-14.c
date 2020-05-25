#include "unpipc.h"

int pipefd[2];

static void sig_usr1(int signo)
{
	static char c = 'a';
	write(pipefd[1],&c,1);
	printf("sig_usr1() %c\n",c);
	c++;
	return;
}

int main(int argc,char** argv)
{
	int nfds;
	char c;
	fd_set rset;
	mqd_t mqd;
	void *buff;
	ssize_t n;
	struct mq_attr attr;
	struct sigevent sigev;
	if (argc != 2)
	{
		printf("usage:mqnotifysig1<name>\n");
	}
	mqd = mq_open(argv[1],O_RDONLY | O_NONBLOCK);
	mq_getattr(mqd,&attr);
	buff = malloc(attr.mq_msgsize);
	pipe(pipefd);
	
	signal(SIGUSR1,sig_usr1);
	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = SIGUSR1;
	mq_notify(mqd,&sigev);
	
	while(1)
	{
		FD_SET(pipefd[0],&rset);
		nfds = select(pipefd[0] + 1,&rset,NULL,NULL,NULL);// 阻塞直到数据进来
		if (FD_ISSET(pipefd[0],&rset))
			read(pipefd[0],&c,1);
		mq_notify(mqd,&sigev);
		while((n = mq_receive(mqd,buff,attr.mq_msgsize,NULL)) >= 0)
		{
			printf("read：%ld bytes\n",(long) n);
		}
		if (errno != EAGAIN)
		{
			printf("mq_receive error\n");
		}
	}

	return 0;
}
