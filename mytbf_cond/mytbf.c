#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include "mytbf.h"


// 令牌桶指针数组什么时候被创建
// 当 mytbf[ch]被编译链接后
static struct mytbf_st* job[MYTBF_MAX];
static int inited = 0;
static pthread_mutex_t mut_job = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_job = PTHREAD_COND_INITIALIZER;
// static pthread_mutex_t mut_num;
static pthread_once_t init_once = PTHREAD_ONCE_INIT;
static pthread_t tid;



struct mytbf_st
{
    int cps;
    int burst;
    int token;
    int pos;
    pthread_mutex_t mut_num;
    // pthread_cond_
};
static int get_free_pos_unblocked(void)
{
    for(int i = 0; i < MYTBF_MAX; i++)
    {
        if(job[i] == NULL)
            return i;
    }
    return -1;
}

static int min(int a, int b)
{
    if(a < b)
        return a;
    return b;
}
// static __sighandler_t alrm_handler_save;

static void *thread_handler(void *p)
{
    // 经典嵌套调用：alrm_handler因为alarm信号才回调，马上又预约下一个alarm
    // alarm(1);
    while(1)
    {
        pthread_mutex_lock(&mut_job);
        for(int i = 0; i< MYTBF_MAX; i++)
        {
            if(job[i] != NULL)
            {
                pthread_mutex_lock(&job[i]->mut_num);
                job[i]->token += job[i]->cps;
                if (job[i]->token > job[i]->burst)
                    job[i]->token = job[i]->burst;
                pthread_mutex_unlock(&job[i]->mut_num);
            }
        }
        pthread_mutex_unlock(&mut_job);
        pthread_cond_broadcast(&cond_job);
        sleep(1);
    }

}

static void module_unloader(void)
{
    // signal(SIGALRM, alrm_handler_save);
    // alarm(0);
    // 应该destroy每个令牌桶中的互斥量
    // unlock 只能调用一次，无需加锁解锁
    pthread_cancel(tid);
    pthread_join(tid,NULL);
    for(int i = 0; i < MYTBF_MAX; i++)
    {
        if(job[i] != NULL)
        {
            mytbf_destroy(job[i]);
        }
    }
    pthread_mutex_destroy(&mut_job);
}

static void module_loader(void)
{
    // alrm_handler_save = signal(SIGALRM, alrm_handler);
    // alarm(1);
    // pthread_t tid;
    int err;
    err = pthread_create(&tid,NULL,thread_handler,NULL);
    if(err)
    {
        fprintf(stderr,"create thread\n",strerror(err));
        // return -1;
        exit(1);
    }
    atexit(module_unloader);
    // 钩子函数到底要free多少
}

mytbf_t *mytbf_init(int cps, int burst)
{
    struct mytbf_st *me;
    // if(!inited)
    // {
    //     // module_loader();
    //     inited = 1;
    // }
    pthread_once(&init_once,module_loader);


    int pos;
    me = malloc(sizeof(*me));
    if(me  == NULL)
    {
        return NULL;
    }
    me->cps = cps;
    me->burst = burst;
    me->token = 0;
    // 
    pthread_mutex_init(&me->mut_num,NULL);
    // me->mut_num = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mut_job);
    pos = get_free_pos_unblocked();
    if(pos < 0)
        return NULL;
    me->pos = pos;
    job[pos] = me;
    pthread_mutex_unlock(&mut_job);

    return me;
}

int     mytbf_fetchtoken(mytbf_t *ptr, int size)
{   
    if(size <= 0)
        return -EINVAL;
    struct mytbf_st *me = ptr;
    int len;
    pthread_mutex_lock(&me->mut_num);
    while(me->token <= 0)
    {
        pthread_cond_wait(&cond_job,&me->mut_num);
        // pthread_mutex_unlock(&me->mut_num);
        // sched_yield;
        // pthread_mutex_lock(&me->mut_num);
    }

        // 等待分配token
    len = min(me->token, size);
    me->token -= len;
    pthread_mutex_unlock(&me->mut_num);
    return len;
}


//token银行，用来存储token（权限） 
int     mytbf_returntoken(mytbf_t *ptr, int size)
{
    if(size <= 0)
    {
        return -EINVAL;
    }
    struct mytbf_st *me = ptr;
    pthread_mutex_lock(&me->mut_num);
    me->token += size;
    if(me->token > me->burst)
        me->token = me->burst;
        // basically information can be passed via ptr from main.c to mytbf.c;

    pthread_mutex_unlock(&me->mut_num);

    return size;
}

int     mytbf_destroy(mytbf_t *ptr)
{
    struct mytbf_st *me = ptr;
    pthread_mutex_destroy(&me->mut_num);
    pthread_mutex_lock(&mut_job);
    job[me->pos] = NULL;
    pthread_mutex_unlock(&mut_job);
    
    free(me);
    
    return 0;
}