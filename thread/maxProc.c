#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


#define MAX      30000
#define BUFFSIZE    32
int pipe_default[2];

int main()
{
    int i,j;
    pid_t pid;
    int buffer[BUFFSIZE];
    memset(buffer,0,BUFFSIZE);
    if(pipe(pipe_default) < 0)
    {
        perror("pipe()");
        exit(1);
    }
    for(j; j<= MAX; j++)
    {
        i++;
        pid = fork();
        if (pid <0)
        {
            perror("fork()");
            exit(1);
        }
        if(pid == 0)
        {   
            close(pipe_default[1]);
            sleep(2);
            if(read(pipe_default[0],buffer,32)>0)
            {
                printf("receive data from parent = %s\n", buffer);
            }
            close(pipe_default[0]);
            // exit(0);
        }
        else
        {
            close(pipe_default[0]);
            char msg[BUFFSIZE] = "HELLO";
            if(write(pipe_default[1], msg,strlen(msg)) < 0)
            {
                perror("parent failed to write()");
                exit(1);
            }
            close(pipe_default[1]);
            waitpid(pid,NULL,0);
        }
        
    }
    // for(j = 0; j<=MAX;j++)
    // {
    //     wait(NULL);
    // }
    exit(0);
}