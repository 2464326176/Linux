#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

typedef void (*sighandler_t) (int);

void do_sig(int a)
{
    printf("Hi, SIGINT, how do you do !\n");
}

void catchsigint(int signo)
{
    printf("-----------------catch\n");
}

int main(void)
{
    sighandler_t handler;

    handler = signal(SIGINT, catchsigint);
    if (handler == SIG_ERR) {
        perror("signal error");
        exit(1);
    }

    while (1);
    
    if (signal(SIGINT, do_sig) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    while (1) {
        printf("---------------------\n");
        sleep(1);
    }

    return 0;
}





