#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM 4


static int num = 0;
static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;

static void *thr_prime(void *p);
struct thr_arg_st
{
    int n;
};

int main()
{
    int i,err;
    pthread_t tid[THRNUM];
    struct thr_arg_st *p;
    void *returnedStP;
    
    

    for(i=0; i<THRNUM;i++)
    {   
        p = malloc(sizeof(*p));
        if (p == NULL)
        {
            perror("malloc()");
            exit(1);
        }
        p->n = i;
        err = pthread_create(tid+i, NULL,thr_prime,p);
        if (err)
        {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            exit(1);
        }
    }
    
    for(i = LEFT; i<= RIGHT; i++)
    {
        // main 线程为什么还能上锁，解锁
        pthread_mutex_lock(&mut_num);
        while(num != 0)
        {
            pthread_mutex_unlock(&mut_num);
            // small sleep without interuption of process scheduling
            sched_yield();
            pthread_mutex_lock(&mut_num);
        }
        num = i;
        pthread_mutex_unlock(&mut_num);

    }
    num = -1;

    for(i = 0; i<= THRNUM; i++)
    {
        // join needs a secondary pointer
        // or the address of void *pointer
        pthread_join(tid[i], &returnedStP);
        free(returnedStP);
    }

    pthread_mutex_destroy(&mut_num);
        
    
    exit(0);
}
// void *p is exactly &i from which it has been called in main function
static void *thr_prime(void *p)
{
    int mark,i,j;
    // force void * to struct * pointer, then get its member n
    // i = ((struct thr_arg_st *)p)->n;


    pthread_mutex_lock();
    i = num;
    num = 0;
    pthread_mutex_unlock();

    // free(p);
    mark = 1;
    for(j = 2; j<i/2; j++)
    {
        if(i%j == 0)
        {
            mark = 0;
            break;
        }
    }
    if(mark)
    {
        printf("%d is a primer\n", i);
    }
    pthread_exit(p);
    
}