#include <stdio.h>
#include <stdlib.h>
// open head files
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// close head filesq
#include <unistd.h>

#define BUFFSIZE 1024

int main(int argc, char ** argv)
{
    if (argc < 3)
    {
        perror("Usage <SFD> <DFD>");
        exit(1);
    }
    int sfd, dfd;
    int rc, wc, pos;
    char buf[BUFFSIZE];


    sfd = open(argv[1], O_RDONLY);
    dfd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0600);
    if(dfd < 0)
    {
        close(sfd);
        perror("open(dfd)");
        exit(1);
    }

    while(1)
    {
        rc = read(sfd, buf, BUFFSIZE);
        if (rc < 0)
        {
            perror("read()..");
            exit(1);
        }
        if (rc == 0)
        {
            break;
        }
        pos = 0;
        while(rc > 0)
        {
            wc = write(dfd, buf+pos, rc);
            if (wc < 0)
            {
                // break;
                // break is not enough for nested for loop
                exit(1);
            }
            pos += wc;
            rc -= wc;
        }
        
    }

    close(dfd);
    close(sfd);

    exit(0);
}
