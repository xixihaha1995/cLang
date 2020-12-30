#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define PROCNUM  3000
#define FNAME   "/tmp/out"
#define LINESIZE    1025

// func_add parameters are not required
static void func_add(void)
{
    char linebuf[LINESIZE];
    FILE *fp;
    int fd;
    fp = fopen(FNAME, "r+");
    if(fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }
    fd = fileno(fp);
    lockf(fd, F_LOCK, 0);
    fgets(linebuf,LINESIZE,fp);
    fseek(fp,0,SEEK_SET);
    // sleep(1);
    fprintf(fp,"%d\n",atoi(linebuf)+1);
    fflush(fp);
    // fclose might mistakenly unlock file
    // to make sure each proc works independently
    lockf(fd, F_ULOCK, 0);
    fclose(fp);
    return;
    // void return to replace pthread_exit(NULL)
}

int main()
{
    int i;
    pid_t pid;
    for(i = 0; i< PROCNUM; i++)
    {
        pid = fork();
        if(pid < 0)
        {
            perror("fork()");
            exit(1);
        }
        if(pid == 0)
        {
            func_add();
            exit(0);
        }
    }
    for (i = 0; i <PROCNUM; i++)
    {
        wait(NULL);
    }    
    exit(0);
}