#include <stdio.h>
#include <stdlib.h>
#include "mytbf.h"

struct mytbf_st
{
    int cps;
    int burst;
    int token;
}

mytbf_t *mytbf_init(int cps, int burst)
{

}
int     mytbf_fetchtoken(mytbf_t *, int)
{

}
int     mytbf_returntoken(mytbf_t *, int)
{

}
int     mytbf_destroy(mytbf_t *)
{
    
}