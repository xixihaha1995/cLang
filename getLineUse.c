#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv)
{
    FILE * fp;
    char * linebuf;
    size_t linesize;

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen()");
        exit(1);
    }
    linesize = 0;
    linebuf = NULL;
    while(1)
    {
        if (getline(&linebuf,&linesize, fp)<0)
            break;
        // realloc linebuf and linesize
        printf("%d\n", strlen(linebuf));
        printf("%d\n", linesize);
    }
    exit(0);

}