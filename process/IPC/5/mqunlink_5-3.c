#include "unpipc.h"

int main(int argc,char** argv)
{
	if (argc != 2)
	{
		printf("usage: mqunlink <name>\n");
	}
	mq_unlink(argv[1]);
	return 0;
}
