#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define T_NUM 9

void* my_wait(void* args)
{
    sleep(1);
    printf("pthread id %d, do nothing ", *(int *)args);
    pthread_exit(NULL);
    return 0;
}

int main() 
{
    int ret;
    pthread_t t_arr[T_NUM];
    pthread_attr_t attr;
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    void *status;
    for(int i = 0; i < T_NUM; ++i)
    {
        ret = pthread_create(&t_arr[i], NULL, my_wait, (void*)&i);
        if(ret)
        {
            printf("create pthread error!");
            exit(-1);
        }
    }

    pthread_attr_destroy(&attr);

    for(int i = 0; i < T_NUM; ++i)
    {
        ret = pthread_join(t_arr[i], &status);
        if(ret)
        {
            printf("pthrad join error %d", ret);
        }
        printf("main, pthread id %d, exit with status %d", i, *(int *)status);
    }
    printf("main exit ");
    pthread_exit(NULL);
    return 0;
}