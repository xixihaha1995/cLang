#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
// the name of thread function parameters is meaningless
// it's just a name 
static void *func(void *p)
{
    puts("Thread is working!");
    return NULL;
}

int main()
{
    pthread_t tid;
    int err;
    puts("Begin!");
    err = pthread_create(&tid,NULL,func, NULL);
    if(err)
    {
        fprintf(stderr, "pthread_create():%s\n",strerror(err));
        exit(1);
    }
    puts("End!\n");
    exit(0);
}