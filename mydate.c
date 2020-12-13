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
        c = getopt(argc, argv, "HMSYmd");
        if (c < 0)
            break;
        switch (c)
        {
            case 'H':
                strncat(timefmt,"%H时", TIMEFMTSIZE);
                break;
            case 'M':
                /* code */
                strncat(timefmt,"%M分", TIMEFMTSIZE);
                break;
            case 'S':
                strncat(timefmt,"%S秒", TIMEFMTSIZE);
                break;
            case 'Y':
                strncat(timefmt,"%Y年", TIMEFMTSIZE);
                break;
            case 'm':
                strncat(timefmt,"%m月", TIMEFMTSIZE);
                break;
            case 'd':
                strncat(timefmt,"%d日", TIMEFMTSIZE);
                break;
            default:
                break;
        }
    }


    strftime(strtime, STRTIMESIZE,timefmt, tm);
    puts(strtime);
    exit(0);
    
}