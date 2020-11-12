#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    puts("Argc %d\n");
    putchar(argc);
    puts("Argv\n");
    for(int i = 0; i < argc - 1; i++)
    {
        printf("%s", *argv[i]);
    }


    exit(0);
}