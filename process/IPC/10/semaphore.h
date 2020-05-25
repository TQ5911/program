typedef struct {
		/*FIFO读和写描述符*/
		int sem_fd[2];
			int sem_magic;
} mysem_t;
 
#define SEM_MAGIC	0x89674532
#define MYSEM_FAILED ((mysem_t *)(-1))

