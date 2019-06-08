#include <myerr.h>
#include <sys/times.h>

static void  pr_times(clock_t, struct tms *, struct tms *);
static void  do_cmd(char *);
//static void  pr_exit(int);

int
main(int argc, char *argv[])
{
    int     i;

    for (i = 1; i < argc; i++)
        do_cmd(argv[i]);    /* once for each command-line arg */
    exit(0);
}
static void
do_cmd(char *cmd)       /* execute and time the "cmd" */
{
    struct tms  tmsstart, tmsend;
    clock_t     start, end;
    int         status;

    printf("\ncommand: %s\n", cmd);

    if ((start = times(&tmsstart)) == -1)  /* starting values */
        printf("times error\n");

    if ((status = system(cmd)) < 0)        /* execute command */
        printf("system() error\n");

    if ((end = times(&tmsend)) == -1)      /* ending values */
        printf("times error\n");

    pr_times(end - start, &tmsstart, &tmsend);
    pr_exit(status);
}
static void
pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend)
{
    static long     clktck = 0;

    if (clktck == 0)    /* fetch clock ticks per second first time */
        if ((clktck = sysconf(_SC_CLK_TCK)) < 0)
            err_sys("sysconf error\n");
		
    fprintf(stderr, "  real:  %7.2f\n", real / (double) clktck);
    printf("  user:  %7.2f\n",(tmsend->tms_utime - tmsstart->tms_utime) / (double) clktck);
    printf("  sys:   %7.2f\n",(tmsend->tms_stime - tmsstart->tms_stime) / (double) clktck);
    printf("  child user:  %7.2f\n",(tmsend->tms_cutime - tmsstart->tms_cutime) / (double) clktck);
    printf("  child sys:   %7.2f\n",(tmsend->tms_cstime - tmsstart->tms_cstime) / (double) clktck);
}
