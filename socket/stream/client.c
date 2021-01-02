#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "proto.h"

int main(int argc, char **argv)
{
    int sd;
    struct sockaddr_in raddr;
    long long stamp;
    FILE *fp;
    if(argc <2)
    {
        perror("Usage...");
        exit(1);
    }

    sd = socket(AF_INET,SOCK_STREAM,0);
    if(sd < 0)
    {
        perror("socket()");
        exit(1);
    }
    raddr.sin_family = AF_INET;
    raddr.sin_port = htons(atoi(SERVERPORT));
    inet_pton(AF_INET, argv[1], &raddr.sin_addr);
    if(connect(sd, (void *)&raddr, sizeof(raddr)) < 0)
    {
        perror("connect()");
        exit(1);
    }
    fp = fdopen(sd, "r+");
    if(fscanf(fp, FMT_STAMP,&stamp)< 1)
    {
        fprintf(stderr, "Bad Format\n");
    }
    else
    {
        printf("%lld\n",stamp);
    }
    fclose(fp);
    exit(0);
}