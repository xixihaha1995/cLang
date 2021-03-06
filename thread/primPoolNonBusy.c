#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sched.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM 4

static int num = 0;
static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void *thr_prime(void *p);
struct thr_arg_st
{
    int n;
};

int main()
{
    int i, err;
    pthread_t tid[THRNUM];
    struct thr_arg_st *p;
    void *returnedStP;

    for (i = 0; i < THRNUM; i++)
    {
        p = malloc(sizeof(*p));
        if (p == NULL)
        {
            perror("malloc()");
            exit(1);
        }
        p->n = i;
        err = pthread_create(tid + i, NULL, thr_prime, p);
        if (err)
        {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            exit(1);
        }
    }

    for (i = LEFT; i <= RIGHT; i++)
    {
        // main 线程为什么还能上锁，解锁
        // main thread wait to assign task: wait for num become 0
        pthread_mutex_lock(&mut_num);
        while (num != 0)
        {
            pthread_cond_wait(&cond, &mut_num);
            // pthread_mutex_unlock(&mut_num);
            // // small sleep without interuption of process scheduling
            // sched_yield();
            // pthread_mutex_lock(&mut_num);
        }
        num = i;
        // only one worker is enough
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mut_num);
    }

    pthread_mutex_lock(&mut_num);
    // make sure the last task has been taken
    while(num != 0)
    {
        pthread_mutex_unlock(&mut_num);
        sched_yield();
        pthread_mutex_lock(&mut_num);
    }
    num = -1;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mut_num);
    

    for (i = 0; i < THRNUM; i++)
    {
        // join needs a secondary pointer
        // or the address of void *pointer
        pthread_join(tid[i], &returnedStP);
        free(returnedStP);
    }

    pthread_mutex_destroy(&mut_num);
    pthread_cond_destroy(&cond);

    exit(0);
}
// void *p is exactly &i from which it has been called in main function
static void *thr_prime(void *p)
{
    int mark, i, j;
    // force void * to struct * pointer, then get its member n
    // i = ((struct thr_arg_st *)p)->n;

    while (1)
    {
        pthread_mutex_lock(&mut_num);
        // downstream thread wait for task: wait for num larger than 0
        while (num == 0)
        {
            pthread_cond_wait(&cond, &mut_num);
            // 到达这里解锁wait，得到通知，立马抢锁，lock（mut_num）
            // pthread_mutex_unlock(&mut_num);
            // sched_yield();
            // pthread_mutex_lock(&mut_num);
        }
        if (num == -1)
        {
            pthread_mutex_unlock(&mut_num);
            break;
        }
        i = num;
        num = 0;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mut_num);

        // free(p);
        mark = 1;
        for (j = 2; j < i / 2; j++)
        {
            if (i % j == 0)
            {
                mark = 0;
                break;
            }
        }
        if (mark)
        {
            // 这里的p->n 不是真正的线程编号，只是人为规定的
            printf("[%d]:%d is a primer\n",((struct thr_arg_st *)p)->n, i);
        }
    }

    pthread_exit(p);
}