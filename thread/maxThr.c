#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *func(void *p)
{
    while(1)
        pause();
    pthread_exit(NULL);

}

int main()
{
    int i;
    pthread_t tid;
    while(1)
    {
        if(pthread_create(&tid, NULL, func, NULL) != 0)
        {
            perror("pthread_create()");
            break;
        }
        i++;
        printf("i= %d\n",i);
    }
    exit(0);
}