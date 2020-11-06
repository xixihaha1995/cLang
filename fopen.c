#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
    FILE *fp;
    fp = fopen("tmp", "r");
    int * p = malloc(sizeof(int));
    if(fp == NULL)
    {
        fprintf(stderr, "fopen() failed errno = %d\n", errno);
        perror("what's happening:");
        fprintf(stderr, "fopen(): %s\n", strerror(errno));
        exit(1);
    }
    puts("OK");
    exit(0);
}