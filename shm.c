#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#define BUFFSIZE    1024

int main(int argc, char **argv)
{
    char *ptr;
    pid_t pid;
    ptr = mmap(NULL,BUFFSIZE, PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    if(ptr == MAP_FAILED)
    {
        perror("mmap()");
        exit(1);
    }
    pid = fork();
    if(pid < 0)
    {
        perror("fork()");
        exit(1);
    }
    if(pid == 0)
    {
        strcpy(ptr, "talk via shared mmap");
        munmap(ptr, BUFFSIZE);
        exit(0);
    }
    else
    {
        wait(NULL);
        puts(ptr);
        munmap(ptr, BUFFSIZE);
        exit(0);
    }
}