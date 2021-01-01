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
    pid_t pid ;
    int state;
};

static void usr2_handler(int s)
{
    return;
}

static int server_job()
{
    
}

static int add_1_server(void)
{
    int slot;
    pid_t pid;
    if(idle_count + busy_count >= MAXCLIENTS)
    {
        return -1;
    }
    for(slot = 0; slot <MAXCLIENTS;slot++)
    {
        if(serverpool[slot].pid == -1)
        {
            break;
        }
    }
    serverpool[slot].state = STATE_IDLE;
    pid = fork();
    // only place for creating child process
    if(pid < 0)
    {
        perror("fork()");
        exit(1);
    }
    if(pid == 0)
    {
        server_job();
        exit(0);
        // 进程级别的结束，用exit（0）
    }
    else
    {
        serverpool[slot].pid = pid;
        idle_count++;

    }
    return 0;


}

static int del_1_server(void)
{
    int i = 0;
    if(idle_count == 0)
        return -1;
    for(i = 0; i< MAXCLIENTS; i++)
    {
        if(serverpool[i].pid != -1 && serverpool[i].state == STATE_IDLE)
        {
            kill(serverpool[i].pid, SIGTERM);
            serverpool[i].pid = -1;
            idle_count--;
            break;
        }
    }
    return 0;
}

static int sd;
static int idle_count = 0, busy_count = 0;
static struct server_st *serverpool;

int main()
{   
    int val = 1;
    int i;
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

    sigset_t set,oset;
    sigemptyset(&set);
    sigaddset(&set, SIG_NOTIFY);
    sigprocmask(SIG_BLOCK, &set, &oset);

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
    for(i = 0; i< MINSPARESERVER; i++)
    {
        add_1_server();
    }

    while(1)
    {
        // this should be CCTV, to continuously print all the server states
        sigsuspend(&oset);
        scan_pool();
        if(idle_count > MAXSPARESERVER)
        {
            for(i = 0; i < (idle_count - MAXSPARESERVER); i++)
            {
                del_1_server();
            }
        }
        else if(idle_count < MINSPARESERVER)
        {
            for(i = 0; i < (MINSPARESERVER - idle_count); i++)
            {
                add_1_server();
            }
        }

        for (i = 0; i< MAXCLIENTS; i++)
        {
            // if(serverpool[i].pid == )
        }

    }
    sigprocmask(SIG_SETMASK,&oset, NULL);

    exit(0);
}