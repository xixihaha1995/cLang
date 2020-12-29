#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


#define MAX      30
#define BUFFSIZE    32
int pipe_default[2];

int main()
{
    int j;
    int i = 0;
    pid_t pid;
    int buffer;

    if(pipe(pipe_default) < 0)
    {
        perror("pipe()");
        exit(1);
    }

    for(j; j<= MAX; j++)
    {
        pid = fork();
        if (pid <0)
        {
            perror("fork()");
            exit(1);
        }
        if(pid == 0)
        {   
            close(pipe_default[1]);
            // sleep(1);
            if(read(pipe_default[0],&buffer,sizeof(buffer))>0)
            {
                printf("receive data from parent = %d\n", buffer);
            }
            close(pipe_default[0]);
            exit(0);
        }
        else
        {   
            close(pipe_default[0]);
            i++;
            if(write(pipe_default[1], &i,sizeof(i)) != -1)
            {
                printf("parent wrote num =%d\n",i);
            }
            // sleep(2);
            close(pipe_default[1]);
            // waitpid(pid,NULL,0);
        }
        
    }
    for(j = 0; j<=MAX;j++)
    {
        wait(NULL);
    }
    exit(0);
}