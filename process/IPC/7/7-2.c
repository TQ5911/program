#include "unpipc.h"

#define MAXNITEMS 1000000
#define MAXNTHREADS 100
 
int nitems;
 
struct {
	pthread_mutex_t mutex; /*互斥锁*/
	int buff[MAXNITEMS];
	int nput; /*buff数组索引*/
	int nval; /*放入buff[nput]的值*/
} shared = {
	PTHREAD_MUTEX_INITIALIZER
};
 
void *produce(void *);
void *consume(void *);
 
int main(int argc, char **argv)
{
	int i, nthreadas, count[MAXNTHREADS];
	pthread_t tid_produce[MAXNITEMS], tid_consume;
 
	if (argc != 3)
		printf("usage: prodcons2 <#items> <#threads>\n");
	nitems = min(atoi(argv[1]), MAXNITEMS);
	nthreadas = min(atoi(argv[2]), MAXNTHREADS);
 
	pthread_setconcurrency(nthreadas);
 
	/*创建nthreadas个生产者线程*/
	for (i = 0; i < nthreadas; i++) {
		count[i] = 0;
		pthread_create(&tid_produce[i], NULL, produce, &count[i]);
	}
 
	/*等待所有生产者线程完成*/
	for (i = 0; i < nthreadas; i++) {
		pthread_join(tid_produce[i], NULL);
		printf("count[%d] = %d\n", i, count[i]);
	}
	/*创建消费者线程*/
	pthread_create(&tid_consume, NULL, consume, NULL);
	pthread_join(tid_consume, NULL);
 
	exit(0);
}
 
/*生产者线程*/
void *produce(void *arg)
{
	for ( ; ; ) {
		/*修改共享的数据之前必须加锁*/
		pthread_mutex_lock(&shared.mutex);
		if (shared.nput >= nitems) {
			pthread_mutex_unlock(&shared.mutex);
			return NULL;
		}
		shared.buff[shared.nput] = shared.nval;
		shared.nput++;
		shared.nval++;
		/*数据修改完后解锁*/
		pthread_mutex_unlock(&shared.mutex);
		*((int*)arg) += 1;
	}
}
 
/*消费者线程*/
void *consume(void *arg)
{
	int i;
	for (i = 0; i < nitems; i++) {
		if (shared.buff[i] != i)
			printf("buff[%d] = %d\n", i, shared.buff[i]);
	}
	return NULL;
}
