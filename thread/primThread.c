#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM (RIGHT-LEFT+1)

int main()
{
    int i, j, mark;
    pthread_t tid[THRNUM];
    for(i=LEFT; i<=RIGHT;i++)
    {   
        pid = fork();
        if (pid < 0)
        {
            perror("fork()");
            exit(1);
        }
    }
    {
        if (pid  == 0)
        {
            mark =1;
            for(j=2; j < i/2; ++j)
            {
                if (i%j == 0)
                {
                    mark = 0;
                    break;
                }
            }
            if (mark == 1)
            {
                printf("%d is a primer\n", i);
            }
            exit(0);
        }
        
    }
    exit(0);
}