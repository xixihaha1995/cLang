#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

struct aBa
{
    int i;
    char ch;
    float f;
};

int main()
{
    fork();
    fork();
    fork();
    printf("hello!\n");
    
}