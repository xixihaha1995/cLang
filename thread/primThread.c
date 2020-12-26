#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM (RIGHT-LEFT+1)

int main()
{
    int i, j, mark,err;
    pthread_t tid[THRNUM];
    for(i=LEFT; i<=RIGHT;i++)
    {   
        err = pthread_create(tid+(i-LEFT), NULL,&i);
        if (err)
        {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            exit(1);
        }
    }
    {
        for(i = LEFT; i<= RIGHT; i++)
        {
            pthread_join(tid[i-LEFT], NULL);
        }
        
    }
    exit(0);
}