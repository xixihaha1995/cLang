#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    printf("Argc is %d\n", argc);
    puts("Argv is ");
    // fprintf(stdout, "%s\n", argv[0]);
    for(int i = 1; i < argc; i++)
    {
        fprintf(stdout, "%s ", argv[i]);
    }


    exit(0);
}