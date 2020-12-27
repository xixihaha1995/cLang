#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define THRNUM  4
// #define FNAME   "/tmp/out"
#define LINESIZE    1024

static pthread_mutex_t mut[THRNUM];

static void *thr_func(void *p)
{   
    int n = (int)p;
    int c = 'a' + n;
    while(1)
    {
        pthread_mutex_lock(mut+n);
        write(1,&c,1);
        pthread_mutex_unlock(mut+(n+1)%3);
    }
        
    pthread_exit(NULL);

}

int main()
{
    int i, err;
    pthread_t tid[THRNUM];
    for(i = 0; i< THRNUM; i++)
    {    
        pthread_mutex_init(mut+i, NULL);
        pthread_mutex_lock(mut+i);
        err = pthread_create(tid+i,NULL, thr_func,(void *)i);
        if(err)
        {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            exit(1);
        }
    }
    pthread_mutex_unlock(mut+0);
    alarm(5);
    for (i = 0; i <THRNUM; i++)
    {
        pthread_join(tid[i], NULL);
    }    
}