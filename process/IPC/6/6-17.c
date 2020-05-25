#include "svmsg.h"
#include "mesg.h"

void client(int,int);

int main(int argc,char** argv)
{
	int msqid;

	msqid = msgget(MQ_KEY1,0);
	client(msqid,msqid);
	return 0;
}

void client(int readfd,int writefd)
{
	size_t len;
	ssize_t n;
	char* ptr;
	struct mymesg mesg;
	snprintf(mesg.mesg_data,MAXMESGDATA,"%ld ",(long)getpid());
	len = strlen(mesg.mesg_data);
	
	ptr = mesg.mesg_data + len;
	fgets(ptr,MAXMESGDATA - len,stdin);
	len = strlen(mesg.mesg_data);
	if (mesg.mesg_data[len - 1] == '\n')
		len --;
	mesg.mesg_len = len;
	mesg.mesg_type = 1;
	printf("write: %s\n writefd: %d",mesg.mesg_data,writefd);

	mesg_send(writefd,&mesg);
	mesg.mesg_type = getpid();
	while((n = mesg_recv(readfd,&mesg)) > 0)
	{
		write(STDOUT_FILENO,mesg.mesg_data,n);
	}
}
