#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/mman.h>
#include <signal.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>
#include "proto.h"
#define _GNU_SOURCE  

#define MINSPARESERVER   5
#define MAXSPARESERVER   10
#define MAXCLIENTS      20
#define LINEBUFFSIZE    40
#define IPSTRSIZE       40

#define SIG_NOTIFY      SIGUSR2
// user_defined signal action
static int sd;
static int idle_count = 0, busy_count = 0;
static struct server_st *serverpool;


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

static void server_job(int pos)
{
    int ppid, len;
    int client_sd;
    struct sockaddr_in raddr;
    int raddr_len;
    char linebuf[LINEBUFFSIZE];
    char ipstr[IPSTRSIZE];
    time_t stamp;


    ppid = getppid();
    
    while(1)
    {
        serverpool[pos].state = STATE_IDLE;
        // I assume the above is not necessary
        kill(ppid, SIG_NOTIFY);
        raddr.sin_family = AF_INET;
        client_sd = accept(sd,(void *)&raddr, &raddr_len);
        if(client_sd < 0)
        {
            if (errno != EINTR || errno != EAGAIN)
            {
                perror("accept()");
                exit(1);
            }
        }
        serverpool[pos].state = STATE_BUSY;
        kill(ppid, SIG_NOTIFY);
        inet_ntop(AF_INET, &raddr.sin_addr, ipstr, IPSTRSIZE);
        // printf("[%d]client:%s:%d\n", getpid(),ipstr, ntohs(raddr.sin_port));
        stamp = time(NULL);
        len = snprintf(linebuf, LINEBUFFSIZE, FMT_STAMP, stamp);
        send(client_sd, linebuf, len, 0);
        sleep(5);
        close(client_sd);
    }
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
        server_job(slot);
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

static int scan_pool(void)
{
    int i, idle = 0, busy = 0;
    // idle and busy are used for avoiding confliction
    for(i = 0; i < MAXCLIENTS;i++)
    {
        if(serverpool[i].pid == -1)
            continue;
        if(kill(serverpool[i].pid, 0))
        // detect if the designated process exists
        {
            serverpool[i].pid = -1;
            continue;
        }
        if(serverpool[i].state == STATE_IDLE)
            idle++;
        else if(serverpool[i].state == STATE_BUSY)
        {
            busy++;
        }
        else
        {
            fprintf(stderr, "unknown state.\n");
            abort();
        }
    }
    idle_count = idle;
    busy_count = busy;
    return 0;
}



int main()
{   
    int val = 1;
    int i;
    struct sockaddr_in laddr, raddr;

    struct sigaction sa, osa;
    // this SIGCHLD was designed to wait to kill the child proc
    // here we redefine its action, and we ask chid proc to kill themselves
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_NOCLDWAIT;
    sigaction(SIGCHLD, &sa, &osa);

    sa.sa_handler = usr2_handler;
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
    for (i = 0; i <MAXCLIENTS; i++)
    {
        serverpool[i].pid = -1;
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
            if(serverpool[i].pid == -1 )
            {
                putchar(' ');
            }
            else if(serverpool[i].state == STATE_IDLE){
                putchar('.');
            }else 
            {
                putchar('X');
            }
        }
        putchar('\n');

    }
    sigprocmask(SIG_SETMASK,&oset, NULL);

    exit(0);
}