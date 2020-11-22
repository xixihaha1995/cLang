#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    printf("Argc is %d\n", argc);
    puts("Argv is ");
    // fprintf(stdout, "%s\n", argv[0]);
    int* poinInt = (int *)malloc(1);
    poinInt = 1;

    for(int i = 1; i < argc; i++)
    {
        fprintf(stdout, "%s ", argv[i]);
    }
    free(poinInt);

    exit(0);
}