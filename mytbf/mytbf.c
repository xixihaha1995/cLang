#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "mytbf.h"

static struct mytbf_st* job[MYTBF_MAX];
struct mytbf_st
{
    int cps;
    int burst;
    int token;
    int pos;
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
    if(a > b)
        return b;
    return a;
}

mytbf_t *mytbf_init(int cps, int burst)
{
    struct mytbf_st *me;
    int pos;
    me = malloc(sizeof(*me));
    if(me  == NULL)
    {
        return NULL;
    }
    me->cps = cps;
    me->burst = burst;
    me->token = 0;
    pos = get_free_pos();
    if(pos < 0)
        return NULL;
    me->pos = pos;
    job[pos] = me;

    return me;
}

int     mytbf_fetchtoken(mytbf_t *ptr, int size)
{   
    if(size <= 0)
        return -EINVAL;
    struct mytbf_st *me = ptr;
    int len;
    while(me->token <= 0)
        pause();
        // 等待分配token
    len = min(me->token, size);
    me->token -= len;
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
    me->token += size;
    if(me->token > me->burst)
        me->token = me->burst;
        // basically information can be passed via ptr from main.c to mytbf.c;

    return size;
}

int     mytbf_destroy(mytbf_t *ptr)
{
    struct mytbf_st *me = ptr;
    job[me->pos] = NULL;
    free(me);
    return 0;
}