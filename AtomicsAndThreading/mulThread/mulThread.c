#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int var = 100;
int main()
{
    pid_t pid = 0;
    int i;
    printf("0main child id:%u father id:%u\n", getpid(), getppid());

    for(i = 0; i < 5; ++i) {
        pid = fork();
        if (pid == 0) {
            break;
        }
    }

    if (pid > 0) {
        var = 77;
        printf("father id:%u  var:%d\n", getpid(), var);
    } else if (pid == 0) {
        sleep(i);
        if(i == 1) {
            var = 500;
            printf("i am %d child id:%u father var:%d\n", i + 1, getpid(), var);
            return 0;
        }
        printf("i am %d child id:%u father var:%d\n", i + 1, getpid(), var);
    } else if (pid < 0) {
        perror("fork error!!!");
        exit(1);
    }

    printf("main end\n");
    return 0;
}

