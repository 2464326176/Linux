
#include <pthread.h>
#include <unistd.h>
#include <iostream>
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
 

int conMux = -1;


static void *thread_func(void *arg)
{   
    printf("1 thread_func\n");
    pthread_mutex_lock(&mtx);   
    conMux = 1;         
    //pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mtx);
    printf("2 thread_func\n");

}
 
int main(void)
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);


    printf("start ------------\n");
 
    if (conMux == -1) {
        pthread_mutex_lock(&mtx);           
        pthread_cond_wait(&cond, &mtx);                       
        pthread_mutex_unlock(&mtx);                       
    }


    printf("end ------------\n");
    pthread_cancel(tid);           
    pthread_join(tid, NULL);
    return 0;
}
