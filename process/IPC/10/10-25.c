#include "unpipc.h"
 
#define NBUFF 			10
#define MAXNTHREADS 	100
 
int nitems, nproducers, nconsumers; 
 
struct {
	int buff[NBUFF];
	int nput;
	int nputval;
	int nget;
	int ngetval;
	sem_t mutex, nempty, nstored;
} shared;
 
void *produce(void *);
void *consume(void *);
 
int main(int argc, char **argv)
{
	int i, prodcount[MAXNTHREADS], conscount[MAXNTHREADS];
	pthread_t tid_produce[MAXNTHREADS], tid_consume[MAXNTHREADS];
 
	if (argc != 4)
		printf("usgae: prodcons4 <#items> <#producers> <#consumers>\n");
 
	nitems = atoi(argv[1]);
	nproducers = min(atoi(argv[2]), MAXNTHREADS);
	nconsumers = min(atoi(argv[3]), MAXNTHREADS);
 
	sem_init(&shared.mutex, 0, 1);
	sem_init(&shared.nempty, 0, NBUFF);
	sem_init(&shared.nstored, 0, 0);
 
	pthread_setconcurrency(nproducers + nconsumers);
	for (i = 0; i < nproducers; i++) {
		prodcount[i] = 0;
		pthread_create(&tid_produce[i], NULL, produce, &prodcount[i]);
	}
	for (i = 0; i < nconsumers; i++) {
		conscount[i] = 0;
		pthread_create(&tid_consume[i], NULL, consume, &conscount[i]);
	}
 
	for (i = 0; i < nproducers; i++) {
		pthread_join(tid_produce[i], NULL);
		printf("producer count[%d] = %d\n", i, prodcount[i]);
	}
	for (i = 0; i < nconsumers; i++) {
		pthread_join(tid_consume[i], NULL);
		printf("consumer count[%d] = %d\n", i, conscount[i]);
	}
	
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
			sem_post(&shared.nstored); //重要！
			sem_post(&shared.nempty); //A
			sem_post(&shared.mutex);
			return NULL;
		}
		
		shared.buff[shared.nput % NBUFF] = shared.nputval;
		shared.nput++;
		shared.nputval++;
		sem_post(&shared.mutex);
		sem_post(&shared.nstored); //B
		*((int *)arg) += 1;
	}
	
}
 
void* consume(void *arg)
{
	int i;
 
	for ( ; ; ) {
		sem_wait(&shared.nstored); //B
		sem_wait(&shared.mutex);
		if (shared.nget >= nitems) {
			sem_post(&shared.nstored); //B
			sem_post(&shared.mutex);
			return NULL;
		}
		
		i = shared.nget % NBUFF;
		if (shared.buff[i] != shared.ngetval)
			printf("error: buff[%d] = %d\n", i, shared.buff[i]);
		shared.nget++;
		shared.ngetval++;
		sem_post(&shared.mutex);
		sem_post(&shared.nempty); //A
		*((int *)arg) += 1;
	}
	
}
