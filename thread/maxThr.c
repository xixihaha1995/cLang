#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX     3000
static int printNum;

void *func(void *p)
{
    // while(1)
    //     pause();
    // printf("printNum= %d\n",printNum);
    printNum++;
    pthread_exit(NULL);

}

int main()
{
    int j;
    pthread_t tid[MAX];
    for(j = 0;j<MAX;j++)
    {
        if(pthread_create(tid+j, NULL, func, NULL) != 0)
        {
            perror("pthread_create()");
            break;
        }

    }
    for(j = 0; j<MAX;j++)
    {
        pthread_join(tid[j],NULL);
    }
    exit(0);
}