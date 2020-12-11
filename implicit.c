#include <stdio.h>
#include <stdlib.h>

int main()
{
    int * p;
    p  = malloc(sizeof(int)*1);
    if(p == NULL)
    {
        return -1;
    }
    printf("Hellow World\n");
    return 0;
}