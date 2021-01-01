#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>


#define MINSPARESERVER   5
#define MAXSPARESERVER   10
#define MAXCLIENTS      20

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

static int sd;

int main()
{   

    
    
    socket();
    setsockopt();
    bind();
    listen();
    accept();
    close();
    
    exit(0);
}