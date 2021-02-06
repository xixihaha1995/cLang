#include <stdio.h>
#include <stdlib.h>
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
// static pthread_mutex_t mut_num;
static pthread_once_t init_once = PTHREAD_ONCE_INIT;

struct mytbf_st
{
    int cps;
    int burst;
    int token;
    int pos;
    pthread_mutex_t mut_num;
};
static int get_free_pos(void)
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
static __sighandler_t alrm_handler_save;

static void thread_handler(int s)
{
    // 经典嵌套调用：alrm_handler因为alarm信号才回调，马上又预约下一个alarm
    alarm(1);
    for(int i = 0; i< MYTBF_MAX; i++)
    {

        // 闲着没事，给所有在使用的tbf加token，每次加cps
        if(job[i] != NULL)
        {
            job[i]->token += job[i]->cps;
            if (job[i]->token > job[i]->burst)
                job[i]->token = job[i]->burst;
        }
    }
}

static void module_unloader(void)
{
    // signal(SIGALRM, alrm_handler_save);
    // alarm(0);
    pthrea
    for(int i = 0; i < MYTBF_MAX; i++)
        free(job[i]);
    
}

static void module_loader(void)
{
    // alrm_handler_save = signal(SIGALRM, alrm_handler);
    // alarm(1);
    pthread_t tid;
    pthread_create(&tid,NULL,thread_handler,0);
    atexit(module_unloader);
    // 钩子函数到底要free多少
}

mytbf_t *mytbf_init(int cps, int burst)
{
    struct mytbf_st *me;
    if(!inited)
    {
        // module_loader();
        pthread_once(&init_once,module_loader);
        inited = 1;
    }


    int pos;
    me = malloc(sizeof(*me));
    if(me  == NULL)
    {
        return NULL;
    }
    me->cps = cps;
    me->burst = burst;
    me->token = 0;
    pthread_mutex_lock(&mut_job);
    pos = get_free_pos();
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
        pthread_mutex_unlock(&me->mut_num);
        sched_yield;
        pthread_mutex_lock(&me->mut_num);
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
    job[me->pos] = NULL;
    free(me);
    pthread_mutex_destroy(&me->mut_num);
    return 0;
}