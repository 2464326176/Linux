#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

void *tfn(void *arg)
{
    srand(time(NULL));
    while (1) {
        pthread_mutex_lock(&mutex);
        printf("id: %lu", pthread_self());
        printf("\thello");
        sleep(rand() % 3);	/*模拟长时间操作共享资源，导致cpu易主，产生与时间有关的错误*/
        printf("\tworld\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);
    }
    return NULL;
}


int main(void)
{
    pthread_t tid;
    srand(time(NULL));
    pthread_create(&tid, NULL, tfn, NULL);
    while (1) {
        pthread_mutex_lock(&mutex);
        printf("id: %lu", pthread_self());

        printf("\tHELLO ");
        sleep(rand() % 3);
        printf("\tWORLD\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);
    }
    pthread_join(tid, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}			
