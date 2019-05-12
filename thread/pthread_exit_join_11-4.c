#include <myerr.h>
#include <pthread.h>
 
 struct foo{
	int a,b,c,d;
 };
 
 void printfoo(const char* s,const struct foo* fp)
 {
	printf("%s",s);
	printf(" structure at 0x%lx\n",(unsigned long)fp);
	printf(" foo.a = %d\n",fp->a);
	printf(" foo.b = %d\n",fp->b);
	printf(" foo.c = %d\n",fp->c);
	printf(" foo.d = %d\n",fp->d);
 }
 
void *thrd_func1(void *arg)
{
	struct foo foo = {1,2,3,4};
    printfoo("thread 1:\n",&foo);
    pthread_exit((void *)&foo);
}
 
void *thrd_func2(void *arg)
{
    printf("Thread 2:ID is %lu\n",(unsigned long)pthread_self());
    pthread_exit((void *)0);
}

 
int main(){
	int err;
    pthread_t tid1,tid2;
	struct foo *fp;
    // 创建线程tid1，线程函数thrd_func1
    if ((err = pthread_create(&tid1,NULL,thrd_func1,NULL)) != 0) 
        err_exit(err,"Create thread 1 error!\n");

    // 等待线程tid1结束，线程函数返回值放在tret中
    if ((err = pthread_join(tid1,(void *)&fp)) != 0)
        err_exit(err,"Join thread 1 error!\n");	
	
	sleep(1);
    printf("parent starting second thread\n");	
	
	
    // 创建线程tid2,线程函数thrd_func2
    if ((err = pthread_create(&tid2,NULL,thrd_func2,NULL)) != 0)
        err_exit(err,"Create thread 2 error!\n");
	sleep(1);
	printfoo("parent:\n",fp);

    exit(0);
}
 
