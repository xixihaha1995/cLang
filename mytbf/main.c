#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "mytbf.h"


#define CPS 1
#define BUFSIZE 10
#define BURST   1


int main(int argc, char **argv)
{
    int sfd, dfd = 1;
    char    buf[BUFSIZE];
    int len, ret, pos;
    int size;
    mytbf_t *tbf;

    if (argc < 2)
    {
        fprintf(stderr, "Usage ...\n" );
        exit(1);
    }
    tbf = mytbf_init(CPS,BURST);
    if(tbf == NULL)
    {
        fprintf(stderr,"mytbf_init\n");
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
        size = mytbf_fetchtoken(tbf, BUFSIZE);
        if(size <0 )
        {
            fprintf(stderr,"cannot fetch valid token: %s\n", strerror(-size));
            exit(1);
        }
        while((len = read(sfd,buf,BUFSIZE)) < 0)
        {
            if(errno == EINTR)
            {
                continue;
            }
            perror("read");
            break;
        }
        
        if((size - len) > 0)
        {
            if((mytbf_returntoken(tbf,size-len)) < 0)
            {
                fprintf(stderr,"cannot fetch valid token: %s\n", strerror(-size));
                exit(1);
            }
        }

        if(len == 0)
        {
            break;
        }
        pos = 0;
        while(len >0)
        {
            ret = write(dfd,buf+pos,len);
            if(ret <0)
            {
                if(errno == EINTR)
                {
                    continue;
                }
                perror("write");
                break;
            }
            if(ret == 0)
            {
                break;
            }
            len -= ret;
            pos += ret;
        }
    }
    close(sfd);
    mytbf_destroy(tbf);

    return 0;
}