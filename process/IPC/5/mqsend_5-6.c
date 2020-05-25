#include "unpipc.h"

int main(int argc,char** argv)
{
	mqd_t mqd;
	void* ptr;	// 数据指针
	size_t len;	// 要发送的数据长度
	unsigned int prio;	// 优先级

	if (argc != 4)
	{
		printf("usage:mqsend <name><#bytes><priority>\n");
	}
	len = atoi(argv[2]);
	prio = atoi(argv[3]);

	mqd = mq_open(argv[1],O_WRONLY);
	ptr = malloc(len);
	mq_send(mqd,ptr,len,prio);
	return 0;
}
