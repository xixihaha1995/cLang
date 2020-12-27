#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define THRNUM  4
// #define FNAME   "/tmp/out"
#define LINESIZE    1024

static int num = 0;
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void *thr_func(void *p)
{   
    int n = (int)p;
    int c = 'a' + n;
    while(1)
    {
        // here to lock the static num
        pthread_mutex_lock(&mut);
        while( num != n)
        {
            pthread_cond_wait(&cond, &mut);
        }
        write(1,&c,1);
        num = (num+1)%4;
        pthread_cond_broadcast(&cond);
        // broadcast result: all thread including main thread will receive notifications
        // unlock(next(thread)) result: next thread will be assigned task
        pthread_mutex_unlock(&mut);
    }
        
    pthread_exit(NULL);

}

int main()
{
    int i, err;
    pthread_t tid[THRNUM];
    for(i = 0; i< THRNUM; i++)
    {    
        
        err = pthread_create(tid+i,NULL, thr_func,(void *)i);
        if(err)
        {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            exit(1);
        }
    }
    // use static num to determine whose turn
    alarm(5);
    for (i = 0; i <THRNUM; i++)
    {
        pthread_join(tid[i], NULL);
    }    
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mut);
}