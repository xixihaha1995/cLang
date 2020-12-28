#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    // putchar('a');
    // fflush(NULL);
    // write(1,"b",1);

    // putchar('a');
    // write(1,"b",1);

    // putchar('a');
    // write(1,"b",1);
    int *p;
    int num;
    num = 5;
    p = &num;
    fprintf(stdout,"test for  pointer:%d, and its value:%d\n",p,*p);

    exit(0);
}