#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main()
{   
    pid_t res;
    printf("[%d]:Begin\n", getpid());

    fflush(NULL);
    res = fork();
    if (res < 0)
    {
        perror("Fork() failure");
        exit(0);
    }
    if (res == 0)
    {
        printf("[%d]:Child is working\n", getpid());
    }
    else
    {
        printf("[%d]:Parent is working\n", getpid());
    }
    printf("[%d]:End!\n", getpid());
    exit(0);
    
}