#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


int main(void)
{
	int i;				//默认创建5个子进程

	for(i = 0; i < 5; i++)	//出口1,父进程专用出口
		if(fork() == 0) {
            printf("%d---child ---pid = %d, ppid = %d\n", i, getpid(), getppid());
			break;	
        }
		//出口2,子进程出口,i不自增

    if (i == 3) {
        sleep(1);
        printf("-----------child ---pid = %d, ppid = %d\n", getpid(), getppid());
        kill(getpid(), SIGKILL);

    } else if (i == 5) {
        printf("I am parent, pid = %d\n", getpid());
        while(1);
    }

	return 0;
}