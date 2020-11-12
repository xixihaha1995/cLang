#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("Argc is %d\n", argc);
    puts("Argv\n");
    for(int i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }


    exit(0);
}