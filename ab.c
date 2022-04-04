#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *p;
    int num;
    num = 5;
    p = &num;
    fprintf(stdout,"test for  pointer:%d, and its value:%d\n",p,*p);

    exit(0);
}