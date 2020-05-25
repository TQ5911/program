#include "unpipc.h"
 
#define MAXNITEMS 1000000
#define MAXNTHREADS 100
 
int nitems;
int buff[MAXNITEMS];
 
struct {
	pthread_mutex_t mutex;
	int nput; /*生产者生产数据的索引*/
	int nval; /*放入buff[nput]的值*/
} put = {
	PTHREAD_MUTEX_INITIALIZER
};
 
/*使用条件变量，条件变量都和一个互斥锁一起使用*/
struct {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int nready;
} nready = {
	PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER
};
 
void *produce(void *);
void *consume(void *);
 
int main(int argc, char **argv)
{
	int i, nthreadas, count[MAXNTHREADS];
	pthread_t tid_produce[MAXNITEMS], tid_consume;
	int counts = 0;
	
	if (argc != 3)
		printf("usage: prodcons2 <#items> <#threads>\n");
	nitems = min(atoi(argv[1]), MAXNITEMS);
	nthreadas = min(atoi(argv[2]), MAXNTHREADS);
 
	pthread_setconcurrency(nthreadas);
 
	/*创建nthreads个生产者线程*/
	for (i = 0; i < nthreadas; i++) {
		count[i] = 0;
		pthread_create(&tid_produce[i], NULL, produce, &count[i]);
	}
	/*创建消费者线程*/
	pthread_create(&tid_consume, NULL, consume, NULL);
	
	/*等待所有线程完成*/
	for (i = 0; i < nthreadas; i++) {
		pthread_join(tid_produce[i], NULL);
		printf("count[%d] = %d\n", i, count[i]);
		counts += count[i];
	}
	pthread_join(tid_consume, NULL);
	printf("count = %d\n", counts);
 
	exit(0);
}
 
/*生产者线程*/
void *produce(void *arg)
{
	for ( ; ; ) {
		/*先放入数据*/
		pthread_mutex_lock(&put.mutex);
		if (put.nput >= nitems) {
			pthread_mutex_unlock(&put.mutex);
			return NULL;
		}
		buff[put.nput] = put.nval;
		put.nput++;
		put.nval++;
		pthread_mutex_unlock(&put.mutex);
		pthread_mutex_lock(&nready.mutex);
		/*如果nready.nready为0，则唤醒消费者线程*/
		if (nready.nready == 0)
			pthread_cond_signal(&nready.cond);
		/*nready++表示新生产一个数据*/
		nready.nready++;
		pthread_mutex_unlock(&nready.mutex);
		*((int*)arg) += 1;
	}
}
 
/*消费者线程*/
void *consume(void *arg)
{
	int i;
 
	for (i = 0; i < nitems; i++) {
		pthread_mutex_lock(&nready.mutex);
		/*nready.nready为0，表示还未生产出新数据，此时睡眠等待生产者线程生产数据后唤醒*/
		while (nready.nready == 0)
			pthread_cond_wait(&nready.cond, &nready.mutex);
		/*nready--表示消费了一个数据*/
		nready.nready--;
		pthread_mutex_unlock(&nready.mutex);
		if (buff[i] != i)
			printf("buff[%d] = %d\n", i, buff[i]);
	}
	return NULL;
}
