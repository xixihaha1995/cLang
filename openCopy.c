#include <stdio.h>
#include <stdlib.h>
// open head files
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// close head filesq
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define CPS 10
#define BUFFSIZE CPS

static volatile int loop = 0;
static void alrm_handler(int s)
{
    loop = 1;
    alarm(1);
}

int main(int argc, char ** argv)
{
    int sfd, dfd = 1;
    int rc, wc, pos;
    char buf[BUFFSIZE];

    if (argc < 2)
    {
        perror("Usage <SFD> <DFD>");
        exit(1);
    }

    alarm(1);
    signal(SIGALRM, alrm_handler);



    sfd = open(argv[1], O_RDONLY);
    // dfd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0600);
    if(dfd < 0)
    {
        close(sfd);
        perror("open(dfd)");
        exit(1);
    }

    while(1)
    {
        while (!loop)
            pause();
        loop = 0;
        while((rc = read(sfd, buf, BUFFSIZE)) < 0)
        {
            if(errno = EINTR)
                continue;
            // false failure
            perror("read()..");
            break;
            // ture failure
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

    // close(dfd);
    close(sfd);

    exit(0);
}
