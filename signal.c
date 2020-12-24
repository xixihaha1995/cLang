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
    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    signal(SIGINT, interRupt);
    while(1)
    {
        sigprocmask(SIG_BLOCK, &set, NULL);
        for (i=0; i < 5; i++)
        {
            write(1,"*",1);
            sleep(1);
        }
        write(1,"\n",1);
        sigprocmask(SIG_UNBLOCK, &set, NULL);

    }

    exit(0);
}