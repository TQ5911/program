#include <myerr.h>
#include <pthread.h>
#include <limits.h>
#include <sys/time.h> 
 
#define NTHR   8                /* 线程数 */
#define NUMNUM 800L         	/* 待排序数 */
#define TNUM   (NUMNUM/NTHR)    /* 每个线程分配到的需要排序的数 */
int nums[NUMNUM];
int snums[NUMNUM];
pthread_barrier_t b;    //屏障
 using namespace std;
void quicksort(int a[], int left, int right);
void adjust_quicksort(int k[], int n)
{
	quicksort(k, 0, n - 1);
}
void quicksort(int a[], int left, int right)// left 和right是数组下标
{
	int i, j, t, temp;
	if (left >= right)   //（递归过程先写结束条件）
		return;

	temp = a[left]; //temp中存的就是基准数  
	i = left;
	j = right;
	while (i != j)
	{
		//顺序很重要，要先从右边开始找（最后交换基准时换过去的数要保证比基准小，因为基准                               
		//选取数组第一个数，在小数堆中） 
		while (a[j] >= temp && i < j)
			j--;
		//再找右边的  
		while (a[i] <= temp && i < j)
			i++;
		//交换两个数在数组中的位置  
		if (i < j)
		{
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
	}
	//最终将基准数归位 （之前已经temp=a[left]过了，交换只需要再进行两步）
	a[left] = a[i];
	a[i] = temp;

	quicksort(a,left, i - 1);//继续处理左边的，这里是一个递归的过程  
	quicksort(a,i + 1, right);//继续处理右边的 ，这里是一个递归的过程  
}

//排序线程
//对nums数组的从idx~idx+TNUM部分进行快速排序
void *workThread(void *arg)
{
    long    idx = (long)arg;
	adjust_quicksort(&nums[idx],TNUM);
    //sort(&nums[idx],&nums[idx+TNUM],compare);
    pthread_barrier_wait(&b);
 
    pthread_exit(NULL);
}
 
//对已经排好序数组nums的NTHR部分进行合并
void merge()
{
    long idx[NTHR];  //idx保存数组nums的NTHR部分的起始位置
    for (long i = 0; i < NTHR; i++)// 8组
        idx[i] = i * TNUM;
 
    for (long sidx = 0; sidx < NUMNUM; sidx++)
    {
        long minidx;
        long num = LONG_MAX;
 
        //从NTHR部分的数组中查找出最小的一个, 将其index保存到idx[minidx]中
        for (long i = 0; i < NTHR; i++)
        {
            //idx[i] < (i+1)*TNUM 确保是在一个部分之中,
            //不会产生两个部分相互比较的情况
            if ((idx[i] < (i+1)*TNUM) && (nums[idx[i]] < num))
            {
                num = nums[idx[i]];
                minidx = i;
            }
        }
 		// 每次循环循环结束找出8组中最小的那个
        snums[sidx] = nums[idx[minidx]];
        idx[minidx]++;// 下次判断该组的数字的位置后移一位
    }
}
 
int main()
{
    srandom(time(NULL));
    for (unsigned long i = 0; i < NUMNUM; i++)
        nums[i] = random();
 
    //创建NTHR个线程分别对数组相邻的NTHR部分进行排序
    struct timeval  start, end;
    pthread_t       tid;
    gettimeofday(&start, NULL);
    pthread_barrier_init(&b, NULL, NTHR+1);
    for (unsigned long i = 0; i < NTHR; i++)
        pthread_create(&tid, NULL,workThread, (void *)(i * TNUM));
    pthread_barrier_wait(&b);
    merge();
    gettimeofday(&end, NULL);
 
    //计算用时
    long long startusec = start.tv_sec * 1000000 + start.tv_usec;
    long long endusec = end.tv_sec * 1000000 + end.tv_usec;
    double elapsed = (double)(endusec - startusec) / 1000000.0;
    printf("sort took %.4f seconds\n", elapsed);
 
    //将排序后的结果写入文件, 以便查看是否已经排好序
    FILE *fp = fopen("save.txt", "w+");
    for (unsigned long i = 0; i < NUMNUM; i++)
        fprintf(fp, "%ld\n ", snums[i]);
}
