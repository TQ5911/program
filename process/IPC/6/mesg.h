struct mymesg;
#define MAXMESGDATA	(PIPE_BUF - 2 * sizeof(long))
#define MESGHDRSIZE	(sizeof(struct mymesg) - MAXMESGDATA)
struct mymesg{
	long mesg_len;			// mesg_data数据长度
	long mesg_type;		// 消息类型
	char mesg_data[MAXMESGDATA];	// 数据缓冲区
};
// 发送消息
ssize_t mesg_send(int fd,struct mymesg* mptr)
{
	if (mptr) return write(fd,mptr,MESGHDRSIZE + mptr->mesg_len);
	return -1;
}

// 接收消息
ssize_t mesg_recv(int fd,struct mymesg* mptr)
{
	size_t len;
	ssize_t n;

	if ((n = read(fd,mptr,MESGHDRSIZE)) == 0)	// 先读取一个消息头(包头)
	{
		return -1;
	}
	else if (n != MESGHDRSIZE)
	{
		printf("message header: expected %d, got %d\n",MESGHDRSIZE,n);
	}

	if ((len = mptr->mesg_len) > 0)// 先判断是否有数据
	{
		if ((n = read(fd,mptr->mesg_data,len)) != len)	// 读取数据(包体)，且数据长度为mptr->mesg_len字节
		{
			printf("message header: expected %d, got %d\n",len,n);
		}
	}
	return len;
}