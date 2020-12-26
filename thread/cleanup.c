#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>


static void clean_func(void *p)
{
    puts(p);
}

static void *func(void *p)
{
    puts("Thread is working!");

    pthread_cleanup_push(clean_func,"reverse call: 1");
    pthread_cleanup_push(clean_func,"reverse call: 2");
    pthread_cleanup_push(clean_func,"reverse call: 3");

    puts("push over!");

    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);


    pthread_exit(NULL);
    // return NULL;
}

int main()
{
    pthread_t tid;
    int err;
    puts("Begin!");
    err = pthread_create(&tid, NULL, func, NULL);
    if(err)
    {
        fprintf(stderr, "pthread_create():%s\n", strerror(err)); 
        exit(1);
    }
    pthread_join(tid, NULL);
    puts("why pthread_join is required");

    exit(0);
}