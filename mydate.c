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
    char timefmt[TIMEFMTSIZE];
    timefmt[0] = '\0';
    int c;

    stamp = time(NULL);
    tm = localtime(&stamp);


    while(1)
    {
        c = getopt(argc, argv, "HMSymd");
        if (c < 0)
            break;
        switch (c)
        {
            case 'H':
                break;
            case 'M':
                /* code */
                strncat(timefmt,"%M", TIMEFMTSIZE);
                break;
            case 'S':
                strncat(timefmt,"%S", TIMEFMTSIZE);
                break;
            case 'y':
                strncat(timefmt,"%y", TIMEFMTSIZE);
                break;
            case 'm':
                strncat(timefmt,"%m", TIMEFMTSIZE);
                break;
            case 'd':
                strncat(timefmt,"%d", TIMEFMTSIZE);
                break;
            default:
                break;
        }
    }


    strftime(strtime, STRTIMESIZE,timefmt, tm);
    puts(strtime);
    exit(0);
    
}