#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define LEFT 0
#define RIGHT 3
#define THRNUM (RIGHT-LEFT+1)


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
    
    

    for(i=LEFT; i<=RIGHT;i++)
    {   
        p = malloc(sizeof(*p));
        if (p == NULL)
        {
            perror("malloc()");
            exit(1);
        }
        p->n = i;
        err = pthread_create(tid+(i-LEFT), NULL,thr_prime,p);
        if (err)
        {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            exit(1);
        }
    }
    
    for(i = LEFT; i<= RIGHT; i++)
    {
        // join needs a secondary pointer
        // or the address of void *pointer
        pthread_join(tid[i-LEFT], &returnedStP);
        free(returnedStP);
        pthread_mutex_destroy(&mut_num);
    }
        
    
    exit(0);
}
// void *p is exactly &i from which it has been called in main function
static void *thr_prime(void *p)
{
    int mark,i,j;
    // force void * to struct * pointer, then get its member n
    i = ((struct thr_arg_st *)p)->n;
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