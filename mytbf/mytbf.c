#include <stdio.h>
#include <stdlib.h>
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

int     mytbf_fetchtoken(mytbf_t *tbf, int size)
{

}

int     mytbf_returntoken(mytbf_t *tbf, int size)
{

}

int     mytbf_destroy(mytbf_t *ptr)
{
    struct mytbf_st *me = ptr;
    job[me->pos] = NULL;
    free(me);
    return 0;
}