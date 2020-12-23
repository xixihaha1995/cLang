#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>


static volatile int loop = 1;
static void alarm_handler(int s)
{
    loop = 0;
}

int main()
{
    int64_t count = 0;

    signal(SIGALRM, alarm_handler);
    // replace alarm signal behavior from end to user-defined
    alarm(5);
    // after 5 seconds, this program will end.
    // alarm signal behavior should be defined first
    while(loop)
        count ++;
    printf("%lld", count);
    exit(0);
}