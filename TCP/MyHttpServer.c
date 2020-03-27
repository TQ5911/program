#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>

#define PORT  3000

// htons:将整型变量从主机字节顺序转变成网络字节顺序
// htonl:将主机数转换成无符号长整型的网络字节顺序
// inet_ntoa:将网络地址转换成“.”点隔的字符串格式
// inet_ntop:将数值格式转化为点分十进制的ip地址格式
// ntohs:将一个16位数由网络字节顺序转换为主机字节顺序

// 本例中，服务端只会与第一个连接的客户端通信，而且是串行的方式，消息顺序发送
// 如果把5步骤中的代码放入6，服务端每次和某个客户端通行完后还能在接收另一个客户端，但依然是串行方式，而不是并发


// 读取单行
int GetLineData(int sockfd, char* buf,int size);
// 处理http请求
void HandleHttpRequest(int client_sockfd);
// 服务端反应
void HandleHttpResponse(int client_sockfd);
void BadRequest(int client_sockfd);
void NotFound(int client_sockfd);
int main()
{
	// 1.创建服务端套接字(相当于邮筒)
	int server_sockfd;
	server_sockfd = socket(PF_INET,SOCK_STREAM,0);// sockt类型
	if(server_sockfd == -1)
	{
		printf("error:%s\n",strerror(errno));// 该行等于perror("error:");
		printf("创建服务端套接字失败!\n");
		return -1;
	}
	else
		printf("创建套接字成功,套接字描述符为%d.\n",server_sockfd);
	
	// 2.记录服务端ip和端口(ser_addr相当于标签,记录着服务端的地址信息，后续只接收该地址信息的客户端的连接)
	struct sockaddr_in ser_addr;			// 记录服务端地址信息
	bzero(&ser_addr,sizeof(struct sockaddr_in));	// 清0
	ser_addr.sin_family = AF_INET;			// 绑定协议族
	ser_addr.sin_port = htons(PORT);		// 绑定段口号
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);   // 绑定服务端ip地址(INADDR_ANY为本地多有地址,即如果不知一块网卡则会有多个ip)
	
	// 3.绑定socket和服务端地址信息(标签)(相当于该socket邮箱只接收寄向该地址信息的信) 
	if(bind(server_sockfd,(struct sockaddr *)&ser_addr,sizeof(struct sockaddr)) == -1)
	{
		printf("绑定ip和端口失败!\n");
		close(server_sockfd);
		return -1;
	}
	else
		printf("绑定端口成功!端口号为%d\n",PORT);
	
	// 4.准备监听客户端的连接(相当于把信箱挂到转达室)
	int num = 5;// 最大的客户端连接数目
	if (listen(server_sockfd,num) == -1)
	{
		printf("服务端监听失败!\n");
		close(server_sockfd);
		return -1;
	}
	printf("服务端开始监听!\n");

	// 5.接收客户端的连接
	struct sockaddr_in cli_addr;
	int size;
	char buf[128];
	char client_ip[64];
	socklen_t len;

	// 6.与客户端进行通信,内容为Q时退出连接
	// 这里由于单线程所有只能顺序读写，如果要达到全双工(即同时读写，可以用同步:多线程  或 异步)
	while(1)
	{
		struct sockaddr_in cli_addr;
        	int size;
       		char buf[128];
        	char client_ip[64];
        	socklen_t len;
		len = sizeof(cli_addr);
		int client_sockfd;// 与客户端交互的套接字描述符
        	// accept函数:阻塞直到有客户端连接
                client_sockfd = accept(server_sockfd,(struct  sockaddr*)&cli_addr,&len);
                if (client_sockfd == -1)
                {
                	printf("接收客户端连接请求失败!\n");
                        close(server_sockfd);  
                        return -1;
		}
		printf("接收客户端连接请求成功!客户端Ip:%s,Port:%d\n",inet_ntop(AF_INET,&cli_addr.sin_addr.s_addr,client_ip,sizeof(client_ip)),ntohs(cli_addr.sin_port));
		HandleHttpRequest(client_sockfd);
		close(client_sockfd);
	}
	close(server_sockfd);
	return 0;
}
// 主行读取(每行的末尾为\r\n)
int GetLineData(int sockfd, char* buf,int size)
{
	int count = 0;
	char ch = '\0';
	int len = 0;	// 读取长度
	while((count < size - 1) && ch != '\n')
	{
		len = read(sockfd,&ch,1);// 每次读取一个字节
		if (len == 1)
		{
			if (ch == '\r')// 回车
				continue;
			else if (ch == '\n')
			{
				buf[count] = '\0';
				break;
			}
			buf[count ++] = ch;
		}
		else if (len == -1)// 读取出错
		{
			perror("read failed.");
			break;
		}
		else// 客户端关闭
		{
			fprintf(stderr,"client close.\n");
			break;
		}
	}
	return count;
}

// 处理http请求
void HandleHttpRequest(int client_sockfd)
{
	struct stat st;
	char buf[128];
	int len = 0;
	char url[256];
	char method[16];
	char path[256];
	// 请求行
	len = GetLineData(client_sockfd,buf,sizeof(buf));	
	if (len > 0)
	{
		int i = 0,j = 0;
		while(!isspace(buf[j]) && (i < sizeof(method) - 1))
		{
			method[i++] = buf[j++];
		}
		method[i] = '\0';		
			
		// 判断方法是否合理(为GET方法)
		if (strncasecmp(method,"GET",i) == 0)//i: 比较长度
		{
			printf("request = %s\n",method);
			// 获取url
			while(isspace(buf[++j]));// 跳过空格
			i = 0;
			while(!isspace(buf[j]) && (i < sizeof(url) - 1))
       	                {
                               url[i++] = buf[j++];
               	        }
			url[i] = '\0';
			printf("url: %s\n",url);
			sprintf(path,"./html_docs%s",url);// 路径拼接,最终存入path
			if (path[strlen(path) - 1] == '/')
			{
				// 设置默认路径
				strcat(path,"cur_time.html");
			}
			printf("path: %s\n",path);
			
			// 读取http头部，不做任何处理		
			printf("read line: %s\n",buf);	
		        do{
                		len = GetLineData(client_sockfd,buf,sizeof(buf));
                		printf("read line: %s\n",buf);
        		}while(len > 0);
			
			if (stat(path,&st) == -1)// 目录不存在
			{
				NotFound(client_sockfd);
			}
			else// 存在
			{
				if (S_ISDIR(st.st_mode))
				{
					strcat(path,"/cur_time.html");
					printf("final path: %s\n",path);
				}
				// 响应客户端请求
				HandleHttpResponse(client_sockfd);// 目前统一先现实时间页面
			}
		}
		else// 非"GET"请求
		{
			printf("other request = %s\n",method);
			// 读取http头部，不做任何处理
			do{
                                len = GetLineData(client_sockfd,buf,sizeof(buf));
                                printf("read line: %s\n",buf);
                        }while(len > 0);
		}
	}
	else// 出错处理
	{
		BadRequest(client_sockfd);			
	}
}


void HandleHttpResponse(int client_sockfd)
{
	const char *main_header = "HTTP/1.0 200 OK\r\nServer: ztq Server\r\nContent-Type: text/html\r\nConnection: Close\r\n";

	const char * html_content = "\
<html>\n\
<head>\n\
<meta http-equiv=\"Content-Type\" content=\"text/html\"/>\n\
<title>Dynamically display the current time</title>\n\
	<script language=\"javascript\">\n\
		var t = null;\n\
    	t = setTimeout(time,1000);\n\
    	function time()\n\
    	{\n\
       		clearTimeout(t);\n\
       		dt = new Date();\n\
			var y = dt.getYear() + 1900;\n\
			var mm = dt.getMonth() + 1;\n\
			var d = dt.getDate();\n\
			var weekday = [\"Sunday\",\"Monday\",\"Tuesday\",\"Wednesday\",\"Thursday\",\"Friday\",\"Saturday\"];\n\
			var day = dt.getDay();\n\
	       	var h = dt.getHours();\n\
	       	var m = dt.getMinutes();\n\
	       	var s = dt.getSeconds();\n\
			if(h < 10){h = \"0\" + h;}\n\
			if(m < 10){m = \"0\" + m;}\n\
			if(s < 10){s = \"0\" + s;}\n\
       		document.getElementById(\"timeShow\").innerHTML =  \"current time:\"+ y + \"-\" + mm + \"-\" + d + \"-\" + weekday[day] + \" \" + h + \":\" + m + \":\" + s + \" \";\n\
       		t = setTimeout(time,1000);\n\
    	}\n\
	</script>\n\
  	<style>\n\
    .time1{width:100%; height:50px; background:#FFF000; line-height:50px; text-align:center;}\n\
  	</style>\n\
</head>\n\
<body>\n\
	<div id=\"timeShow\" class=\"time1\"></div>\n\
</body>\n\
</html>";

	char send_buf[256];
	int len = write(client_sockfd,main_header, strlen(main_header));// 发送头部内容
	fprintf(stdout,"write[%d]:\n%s\n",len,main_header);// 头部内容
	len = snprintf(send_buf,256,"Content-Length: %d\r\n\r\n",strlen(html_content));// 添加Content-Length:正文长度\r\n 和 正文和报头之间的\r\n，因为美也页面的大小是不一定的，所以单独一行
	len = write(client_sockfd,send_buf,len);// 发送大小内容
	len = write(client_sockfd,html_content,strlen(html_content));// 发送正文内容
	fprintf(stdout,"write[%d]:\n%s\n",len,html_content);
}

void BadRequest(int client_sockfd)
{
	const char *reply = "HTTP/1.0 400 BAD REQUEST\r\nContent-Type: text/html\r\n\
\r\n\
<html>\r\n\
<head>\r\n\
<title>BAD REQUEST</title>\r\n\
</head>\r\n\
<body>\r\n\
	<p> you browser sent a bad request!\r\n\
</body>\r\n\
</html>";

        int len = write(client_sockfd,reply, strlen(reply));
	if (len <= 0)
	{
		fprintf(stderr,"send reply failed.reason: %s",strerror(errno));
	}
}
void NotFound(int client_sockfd)
{
        const char *reply = "HTTP/1.0 404 NOT FOUND\r\nContent-Type: text/html\r\n\
\r\n\
<html lang=\"zh-CN\">\r\n\
<meta content=\"text/html; charset=utf-8\" http-equiv=\"Content-Type\">\r\n\
<head>\r\n\
<title>NOT FOUND</title>\r\n\
</head>\r\n\
<body>\r\n\
        <p>页面找不到 The page you visited does not exist!\r\n\
</body>\r\n\
</html>";

        int len = write(client_sockfd,reply, strlen(reply));
        if (len <= 0)
        {
                fprintf(stderr,"send reply failed.reason: %s",strerror(errno));
        }
}


// 常见的请求类型
// 				代号			描述
// 服务器存在请求内容，		200			OK
// 并可以相应给客户端
//
// 客户端的请求有异常，		501			Method Not Implemented
// 方法有问题
//
// 服务器收到请求后，		500			Internal Server Error
// 因为自身为题没法响应
//
// 请求的内容不存在		404			Not Found
//
// 客户端发送的请求格式有问题	400			BAD REQUEST
