#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    FILE *fp;
    fp = fopen("tmp", "r");
    if(fp == NULL)
    {
        // fprintf(stderr, "fopen() failed errno = %d\n", errno);
        perror("what's happening:");
        exit(1);
    }
    puts("OK");
    exit(0);
}