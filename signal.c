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
    while(1)
    {
        for (i=0; i < 5; i++)
        {
            write(1,"*",1);
            sleep(1);
        }
        write(1,"\n",1);
    }

    exit(0);
}