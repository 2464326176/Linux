
/* 3个线程不定时 "写" 全局资源，5个线程不定时 "读" 同一全局资源 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int counter = 0;                          //全局资源
pthread_rwlock_t rwlock;

void *th_write(void *arg)
{
    int t;
    int i = (int)arg;

    while (1) {
        t = counter;
        sleep(1);

        pthread_rwlock_wrlock(&rwlock);
        printf("=======write %d: %lu: counter=%d ++counter=%d\n", i, pthread_self(), t, ++counter);
        pthread_rwlock_unlock(&rwlock);

        sleep(5);
    }
    return NULL;
}

void *th_read(void *arg)
{
    int i = (int)arg;
    
    while (1) {
        pthread_rwlock_rdlock(&rwlock);
        printf("----------------------------read %d: %lu: %d\n", i, pthread_self(), counter);
        pthread_rwlock_unlock(&rwlock);

        sleep(2);
    }
    return NULL;
}

int main()
{
    int i;
    pthread_t tid[3];

    pthread_rwlock_init(&rwlock, NULL);

    for (i = 0; i < 1; i++)
        pthread_create(&tid[i], NULL, th_write, (void *)i);

    for (i = 0; i < 2; i++)
        pthread_create(&tid[i+3], NULL, th_read, (void *)i);

    for (i = 0; i < 3; i++)
        pthread_join(tid[i], NULL);

    pthread_rwlock_destroy(&rwlock);            //释放读写琐

    return 0;
}
