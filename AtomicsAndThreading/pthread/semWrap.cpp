#include <iostream>
#include <unistd.h>
#include <pthread.h>

static int ret = -1;
struct semWrap{
    pthread_mutex_t mtx;
    pthread_cond_t cond;
    int val;
    semWrap () {
        mtx = PTHREAD_MUTEX_INITIALIZER;
        cond = PTHREAD_COND_INITIALIZER;
        val = 0;
    };
};


void semInit (semWrap *s, int senNum) {
    s->val = senNum;
}


void semLock (semWrap *s) {
    printf("before semLock: %d\n", s->val);
    pthread_mutex_lock(&(s->mtx));   
    if (s->val > 0) {
        --(s->val);
    }         
    pthread_cond_signal(&(s->cond));
    printf("after semLock: %d\n", s->val);
    pthread_mutex_unlock(&(s->mtx));     
}

void semUnlock (semWrap *s) {
    printf("before semUnlock: %d\n", s->val);
    pthread_mutex_lock(&(s->mtx));  
    while (s->val == 0) {
        pthread_cond_wait(&(s->cond), &(s->mtx));
    }          
    --(s->val);
    printf("after semUnlock: %d\n", s->val);
    pthread_mutex_unlock(&(s->mtx)); 
}

/*void semDestroy (semWrap *s) {

}*/

void *thread_func(void *arg)
{
    ret = -1;
    printf("ret:%d\n", ret);
    semLock((semWrap *)arg);
    return 0;
}
 
int main(void)
{

    pthread_t tid;
    semWrap sem;
    semInit(&sem, 1);
    pthread_create(&tid, NULL, thread_func, &sem);  


    if (ret == -1) {
        printf("thread 1 is signal\n");
        semUnlock(&sem);

    }

    printf("this is ok.\n");

    pthread_cancel(tid);             
    pthread_join(tid, NULL);
    printf("All done -- exiting\n");
    return 0;
}
