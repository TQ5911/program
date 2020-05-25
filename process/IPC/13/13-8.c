#include "unpipc.h"
 
/*共享的数据结构*/
struct shmstruct{
	int count;  /*计数器*/
};
 
sem_t *mutex;
 
int main(int argc, char **argv)
{
	int fd, i, nloop;
	pid_t pid;
	struct shmstruct *ptr;
 
	if (argc != 4)
		printf("usage: client1 <shmname> <semname> <#loops>\n");
	nloop = atoi(argv[3]);
 
	/*打开共享内存区对象*/
	fd = shm_open(argv[1], O_RDWR, FILE_MODE);
	/*映射共享内存区对象*/
	ptr = mmap(NULL, sizeof(struct shmstruct), PROT_READ | PROT_WRITE, 
				MAP_SHARED, fd, 0);
	close(fd);
 
	/*打开信号量*/
	mutex = sem_open(argv[2], 0);
 
	pid = getpid();
	/*给共享内存区计数器持续加1*/
	for (i = 0; i < nloop; i++) {
		sem_wait(mutex);
		printf("pid %ld: %d\n", (long)pid, ptr->count++);
		sem_post(mutex);
	}
 
	exit(0);
 
}
