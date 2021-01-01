#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/mman.h>
#include <signal.h>
#include <arpa/inet.h>
#include "proto.h"

#define MINSPARESERVER   5
#define MAXSPARESERVER   10
#define MAXCLIENTS      20

#define SIG_NOTIFY      SIGUSR2
// user_defined signal action

enum
{
    STATE_IDLE = 0,
    STATE_BUSY
};

struct server_st
{
    pid_t pid;
    int state;
};

static void usr2_handler(int s)
{
    return;
}

static int sd;
static int idle_count = 0, busy_count = 0;
static struct server_st *serverpool;

int main()
{   
    int val = 1;
    struct sockaddr_in laddr, raddr;

    struct sigaction sa, osa;
    // this SIGCHLD was designed to wait to kill the child proc
    // here we redefine its action, and we ask chid proc to kill themselves
    sa.__sigaction_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_NOCLDWAIT;
    sigaction(SIGCHLD, &sa, &osa);


    sa.__sigaction_handler = usr2_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIG_NOTIFY, &sa, &osa);

    serverpool = mmap(NULL, sizeof(struct server_st)*MAXCLIENTS, PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    if(serverpool == MAP_FAILED)
    {
        perror("mmap()");
        exit(1);
    }    

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if(sd <0)
    {
        perror("socket()");
        exit(1);
    }
   
    if(setsockopt(sd,SOL_SOCKET, SO_REUSEADDR,&val, sizeof(val)) <0)
    {
        perror("setsockopt");
        exit(1);
    }

    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(atoi(SERVERPORT));
    inet_pton(AF_INET, "0.0.0.0",&laddr.sin_addr);
    if(bind(sd,(void *)&laddr,sizeof(laddr)) < 0)
    {
        perror("bind()");
        exit(1);
    }
    if(listen(sd, 100) < 0)
    {
        perror("listen()");
        exit(1);
    }
    
    accept();
    close();
    
    exit(0);
}