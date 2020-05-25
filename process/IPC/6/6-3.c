#include "unpipc.h"

int main()
{
	int msqid;
	struct msqid_ds info;
	struct msgbuf buf;

	msqid = msgget(IPC_PRIVATE,SVMSG_MODE | IPC_CREAT);

	buf.mtype = 1;
	buf.mtext[0] = 1;
	msgsnd(msqid,&buf,1,0);

	msgctl(msqid,IPC_STAT,&info);
	printf("read-write:%03o,cbytes = %lu,qnum = %lu,qbytes = %lu\n",info.msg_perm.mode & 0777,(ulong_t)info.msg_qbytes,(ulong_t)info.msg_qnum,(ulong_t)info.msg_qbytes);

	system("ipcs -q");
	msgctl(msqid,IPC_RMID,NULL);
	return 0;
}
