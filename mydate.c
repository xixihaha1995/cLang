#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define STRTIMESIZE 1024
#define TIMEFMTSIZE 1024

int main(int argc, char **argv)
{
    time_t stamp;
    struct tm *tm;
    char strtime[STRTIMESIZE];
    stamp = time(NULL);
    tm = localtime(stamp);
    char timefmt[TIMEFMTSIZE];
    timefmt[0] = "\0";

    while(1)
    {
        c = getopt(argc, argv, "HMSymd");
        if (c < 0)
            break;
        switch (c)
        {
        case "M":
            /* code */
            strncat(timefmt,"%M", TIMEFMTSIZE);
            break;
        
        default:
            break;
        }
    }


    strftime(strtime, STRTIMESIZE,"", tm);
    puts(strtime);
    exit(0);
    
}