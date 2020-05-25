#include "unpipc.h"

int main(int argc,char** argv)
{
	int c,flags;
	mqd_t mqd;
	ssize_t n;
	unsigned int prio;
	void* buff;
	struct mq_attr attr;

	flags = O_RDONLY;
	
	mqd = mq_open(argv[1],flags);
	mq_getattr(mqd,&attr);
	buff = malloc(attr.mq_msgsize);
	n = mq_receive(mqd,buff,attr.mq_msgsize,&prio);
	printf("read: %ld bytes,priority = %u\n",(long)n,prio);

	return 0;
}
	
