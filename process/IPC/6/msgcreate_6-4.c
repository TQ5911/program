#include "unpipc.h"

int main(int argc,char** argv)
{
	int c,oflag,mqid;
	oflag = SVMSG_MODE | IPC_CREAT;

	mqid = msgget(ftok(argv[1],0),oflag);
	return 0;
}
