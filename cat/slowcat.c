#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define CPS 10
#define BUFSIZE CPS

int main(int argc, char **argv)
{
    int sfd, dfd = 1;
    char    buf[BUFSIZE];
    int len, ret, pos;

    if (argc < 2)
    {
        fprintf(stderr, "Usage ...\n" );
        exit(1);
    }

    // prevention of signal interrupt
    do
    {
        sfd = open(argv[1], O_RDONLY);
        if (sfd < 0)
        {
            if(errno != EINTR)
            {
                perror("open ");
                exit(1);
            }
        }
    }while(sfd < 0);
    while(1)
    {
        lread(sfd,buf,BUFSIZE);
    }


    return 0;
}