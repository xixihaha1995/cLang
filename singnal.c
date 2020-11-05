#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sighandler(int);
int main()
{
    signal(SIGINT, sighandler);
    for(;;)
    {
        printf("sleeping ...\n");
        sleep(3);
    }
}

void sighandler(int signum)
{
    printf("caught singal %d, and now I am exiting...\n", signum);
    exit(1);
}