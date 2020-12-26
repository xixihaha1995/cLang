#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define THRNUM  20
#define FNAME   "/tmp/out"
#define LINESIZE    1024

static void *thr_add(void *p)
{
    char linebuf[LINESIZE];
    FILE *fp;
    fp = fopen(FNAME, "r+");
    if(fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }
    fgets(linebuf,LINESIZE,fp);
    fseek(fp,0,SEEK_SET);
    sleep(1);
    fprintf(fp,"%d\n",atoi(linebuf)+1);
    fclose(fp);
    pthread_exit(NULL);

}

int main()
{
    int i, err;
    pthread_t tid[THRNUM];
    for(i = 0; i< THRNUM; i++)
    {
        err = pthread_create(tid+i,NULL, thr_add, NULL);
        if(err)
        {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            exit(1);
        }
    }
    for (i = 0; i <THRNUM; i++)
    {
        pthread_join(tid[i], NULL);
    }    
}