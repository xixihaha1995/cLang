#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("Argc is %d\n", argc);
    puts("Argv\n");
    // fprintf(stdout, "%s\n", argv[0]);
    for(int i = 0; i < argc; i++)
    {
        fprintf(stdout, "%s ", argv[i]);
    }


    exit(0);
}