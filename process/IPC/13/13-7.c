#include "unpipc.h"
 
struct shmstruct{
	int count; /*计数器*/
};
 
sem_t *mutex;
 
int main(int argc, char **argv)
{
	int fd;
 
	if (argc != 3)
		printf("usage: server1 <shmname> <semname>\n");
	
	shm_unlink(argv[1]);
	/*创建内存共享区对象*/
	fd = shm_open(argv[1], O_RDWR | O_CREAT | O_EXCL, FILE_MODE);
	/*设置共享内存区对象大小*/
	ftruncate(fd, sizeof(struct shmstruct));
	close(fd);
 
	sem_unlink(argv[2]);
	/*创建信号量*/
	mutex = sem_open(argv[2], O_CREAT | O_EXCL, FILE_MODE, 1);
	sem_close(mutex);
 
	exit(0);
}
