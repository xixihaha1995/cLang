#include <stdio.h>
#include <stdlib.h>

int main()
{
    int * p;
    p  = malloc(sizeof(int)*10);
    if(p == NULL)
    {
        return -1;
    }
    p[0]= 15;
    printf("Hellow World%d\n", p[0]);
    return 0;
}