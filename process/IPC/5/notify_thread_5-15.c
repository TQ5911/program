#include "unpipc.h"

mqd_t mqd;
struct mq_attr attr;
struct sigevent sigev;
	
static void notify_thread(union sigval arg)
{
	void *buff;
	ssize_t n;
	printf("notify_thread started\n");
	buff = malloc(attr.mq_msgsize);
	mq_notify(mqd,&sigev);
	while((n = mq_receive(mqd,buff,attr.mq_msgsize,NULL)) >= 0)
	{
		printf("read：%ld bytes\n",(long) n);
	}
	if (errno != EAGAIN)
	{
		printf("mq_receive error\n");
	}
	free(buff);
	pthread_exit(NULL);
	return;
}

int main(int argc,char** argv)
{
	if (argc != 2)
	{
		printf("usage:mqnotifysig1<name>\n");
	}
	 
	mqd = mq_open(argv[1],O_CREAT | O_RDWR, 0777, NULL);//argv[1]对应的消息队列事先不能有,直接通过命令行传入就行了
	//mqd = mq_open(argv[1],O_RDONLY | O_NONBLOCK);		// 不行
	mq_getattr(mqd,&attr);
	bzero(&sigev, sizeof(sigev));	
	sigev.sigev_notify = SIGEV_THREAD;
	sigev.sigev_notify_function = notify_thread;
	sigev.sigev_notify_attributes = NULL;
	sigev.sigev_value.sival_ptr = &mqd;
	
	int a = mq_notify(mqd,&sigev);
	printf("%d\n",a);
	//for(;;)
	{
		pause();
	}

	return 0;
}
