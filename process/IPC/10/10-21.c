// 多个生产单个消费者信号量模型
#include "unpipc.h"
 
#define NBUFF 			10
#define MAXNTHREADS 	100
 
int nitems, nproducers;
 
struct {
	int buff[NBUFF];
	int nput;
	int nputval;
	sem_t mutex, nempty, nstored;
} shared;
 
void *produce(void *);
void *consume(void *);
 
int main(int argc, char **argv)
{
	int i, count[MAXNTHREADS];
	pthread_t tid_produce[MAXNTHREADS], tid_consume;
 
	if (argc != 3)
		printf("usgae: prodcons3 <#items> <#producers>\n");
	nitems = atoi(argv[1]);
	nproducers = min(atoi(argv[2]), MAXNTHREADS); /*生产者线程数量*/
 
	sem_init(&shared.mutex, 0, 1);
	sem_init(&shared.nempty, 0, NBUFF);
	sem_init(&shared.nstored, 0, 0);
 
	pthread_setconcurrency(nproducers + 1);
	for (i = 0; i < nproducers; i++) {
		count[i] = 0;
		pthread_create(&tid_produce[i], NULL, produce, &count[i]);
	}
	pthread_create(&tid_consume, NULL, consume, NULL);
 
	for (i = 0; i < nproducers; i++) {
		pthread_join(tid_produce[i], NULL);
		printf("count[%d] = %d\n", i, count[i]);
	}
	pthread_join(tid_consume, NULL);
	
	sem_destroy(&shared.mutex);
	sem_destroy(&shared.nempty);
	sem_destroy(&shared.nstored);
 
	exit(0);
}
 
void* produce(void *arg)
{
	int i;
 
	for ( ; ; ) {
		sem_wait(&shared.nempty); //A
		sem_wait(&shared.mutex);
		if (shared.nput >= nitems) {
			sem_post(&shared.nempty); // 重要！
			sem_post(&shared.mutex);
			return NULL;
		}
		shared.buff[shared.nput % NBUFF] = shared.nputval;
		shared.nput++;
		shared.nputval++;
		sem_post(&shared.mutex);
		sem_post(&shared.nstored); //B
		*((int *)arg) += 1;// 记录执行的次数
	}
	
}
 
void* consume(void *arg)
{
	int i;
 
	for (i = 0; i < nitems; i++) {
		sem_wait(&shared.nstored); //B	消费者线程和生产者一起执行的，所以需要锁
		if (shared.buff[i % NBUFF] != i)
			printf("buff[%d] = %d\n", i, shared.buff[i % NBUFF]);
		sem_post(&shared.nempty); //A
	}
	
	return NULL;
}
