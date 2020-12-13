#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define STRTIMESIZE 1024

int main(int argc, char **argv)
{
    time_t stamp;
    struct tm *tm;
    char strtime[STRTIMESIZE];
    stamp = time(NULL);
    tm = localtime(stamp);

    

    strftime(strtime, STRTIMESIZE,"", tm);
    puts(strtime);
    
}