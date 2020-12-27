#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define THRNUM  4
// #define FNAME   "/tmp/out"
#define LINESIZE    1025

static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

static void *thr_func(void *p)
{
    int c = 'a' + (int)p;
    while(1)
        write(1,&c,1);
    pthread_exit(NULL);

}

int main()
{
    int i, err;
    pthread_t tid[THRNUM];
    for(i = 0; i< THRNUM; i++)
    {
        err = pthread_create(tid+i,NULL, thr_func, (void *)i);
        if(err)
        {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            exit(1);
        }
    }
    for (i = 0; i <THRNUM; i++)
    {
        pthread_join(tid[i], NULL);
    }    
    pthread_mutex_destroy(&mut);
}