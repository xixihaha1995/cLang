#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static void interRupt(int sig)
{
    // printf("caught singal %d, I'm exiting\n", sig);
    write(1,"!",1);
    // exit(1);
}


int main()
{
    int i;
    signal(SIGINT, interRupt);
    for (i=0; i < 10; i++)
    {
        write(1,"*",1);
        sleep(1);
    }
    exit(0);
}