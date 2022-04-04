#include <stdio.h>
#include <stdlib.h>

int main_ab()
{
    int *p;
    int num;
    num = 5;
    p = &num;
    fprintf(stdout,"test for  pointer:%p, and its value:%d\n",p,*p);
    return 0;
}