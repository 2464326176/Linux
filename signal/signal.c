#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
typedef void (*sighandler_t)(int);

void sigHandler(int signum)
{
    printf("catch signal %d\n", signum);
    exit(1);
}

int main()
{

    sighandler_t ret_signal = signal(SIGINT, sigHandler);

    if(SIG_ERR == ret_signal)
    {
        printf("signal error");
        exit(0);
    }
    printf("start generate signal!\n");

    int ret_raise = raise(SIGINT);
    if(0 != ret_raise)
    {
        printf("generate signal error!\n");
        exit(0);
    }

    /*while(1)
    {
        printf("start sleep 1s \n");
        sleep(1);
    }*/
    printf("exit \n");
    return 0;
}