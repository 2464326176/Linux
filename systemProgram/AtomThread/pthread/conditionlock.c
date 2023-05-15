#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;

int flag = 0;
int i = 0;
void* product(void* arg)
{   
    printf("%lu flag:%d\n", pthread_self(), flag);
    while(1)
    {
        pthread_mutex_lock(&mutex);
        printf("%lu, 1:%d\n", pthread_self(), ++i);
        flag = 1;
        pthread_mutex_unlock(&mutex);

        pthread_cond_signal(&has_product);
        sleep(rand() % 3);
    }
}


void* consumpt(void* arg)
{
    printf("%lu flag:%d\n", pthread_self(), flag);
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while(!flag)
        {
            pthread_cond_wait(&has_product, &mutex);
        }
        flag = 0;
        printf("%lu, 2:%d\n", pthread_self(), ++i);
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);
    }
}


int main()
{
    pthread_t ptid, ctid;

    pthread_create(&ptid, NULL, product, NULL);
    pthread_create(&ctid, NULL, consumpt, NULL);

    pthread_join(ptid, NULL);
    pthread_join(ctid, NULL);

    return 0;
}