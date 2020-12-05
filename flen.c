#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    FILE * fp;
    fp = fopen(argv[1], "r");
    if (fp == 0) {
        perror("fopen()");
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    printf("%ld\n", ftell(fp));
    return 0;

}