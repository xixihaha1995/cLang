#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX     30000
static int printNum;

void *func(void *p)
{
    while(1)
        pause();

    // printf("printNum= %d\n",printNum);
    // printNum++;
    pthread_exit(NULL);

}

int main()
{
    int i = MAX;
    int j;
    pthread_t tid[MAX];
    for(j;;j++)
    {
        if(pthread_create(tid+j, NULL, func, NULL) != 0)
        {
            perror("pthread_create()");
            break;
        }
        // i++;

    }
    for(j = 0; j<=i;j++)
    {
        pthread_join(tid[j],NULL);
    }
    exit(0);
}