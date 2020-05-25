// gcc mqcreatel_5-2.c -o mqcreatel_5-2.o -lrt这样子编译，后面得加-lrt
// 运行的时候:如./mqcreatel_5-2.o /mymqueue 会在/dev/mquque下生成对应文件
#include "unpipc.h"

int main(int argc,char** argv)
{       
        int c,flags;
        mqd_t mqd;
        flags = O_RDWR | O_CREAT;
       /* while((c = getopt(argc,argv,"e")) != -1)
        {
                switch(c)
                {
                        case 'e':flags |= O_EXCL; break;
                }       
        }
        */
	printf("%d\n",c);
	printf("optind:%d\n",optind);
        if (optind != argc - 1)
        {
                printf("usage : mqcreate [ -e ] <name>\n");
        }
	printf("%s\n",argv[optind]);
        mqd = mq_open(argv[optind],flags,FILE_MODE,NULL);
        mq_close(mqd);
        return 0;
}
