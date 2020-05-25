#include "svmsg.h"
#include "mesg.h"

void server(int,int);

int main(int argc,char**argv)
{
	int msqid;
	msqid = msgget(MQ_KEY1,SVMSG_MODE | IPC_CREAT);

	server(msqid,msqid);

	return 0;
}

void server(int readfd,int writefd)
{
	FILE* fp;
	char *ptr;
	pid_t pid;
	ssize_t n;
	struct mymesg mesg;

	while(1)
	{
		mesg.mesg_type = 1;
		if ((n = mesg_recv(readfd,&mesg)) == 0)
		{
			printf("pathname messing\n");
			continue;
		}
		mesg.mesg_data[n] = '\0';
		printf("read: %s\n,",mesg.mesg_data);
		getchar();
		if ((ptr = strchr(mesg.mesg_data,' ')) == NULL)
		{
			printf("bogus request: %s\n",mesg.mesg_data);
			continue;
		}

		*ptr++ = 0;
		pid = atoi(mesg.mesg_data);
		mesg.mesg_type = pid;

		if ((fp = fopen(ptr,"r")) == NULL)
		{
			snprintf(mesg.mesg_data + n,sizeof(mesg.mesg_data) - n,"can't open, %s\n",strerror(errno));
			mesg.mesg_len = strlen(ptr);
			memmove(mesg.mesg_data,ptr,mesg.mesg_len);
			mesg_send(writefd,&mesg);
		}
		else
		{
			while(fgets(mesg.mesg_data,MAXMESGDATA,fp) != NULL)
			{
				mesg.mesg_len = strlen(mesg.mesg_data);
				mesg_send(writefd,&mesg);
			}
			fclose(fp);
		}
		mesg.mesg_len = 0;
		mesg_send(writefd,&mesg);
	}
}
