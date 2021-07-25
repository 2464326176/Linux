#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_PTHREAD 5

void* do_pthread(void* args)
{
    printf("pthread create %d\n", *(int*)args);
    return 0;
}

int main() 
{
    pthread_t t_arr[NUM_PTHREAD];
    int t_index[NUM_PTHREAD];
    for(int i = 0; i < NUM_PTHREAD; ++i)
    {
        t_index[i] = i + 1;
        int ret = pthread_create(&t_arr[i], NULL, do_pthread, (void*)&(t_index[i]));
        if(ret)
        {
            printf("pthread create error %d", ret);
        }
    }
    pthread_exit(NULL);
    return 0;
}