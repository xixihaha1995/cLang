#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int64_t count;
    int fd;
    struct stat statres;
    char *str;

    if(argc < 2)
    {
        perror("usage..");
        exit(1);
    }
    fd = open(argv[1],O_RDONLY);
    fstat(fd,&statres);
    str = mmap(NULL, statres.st_size, PROT_READ, MAP_SHARED, fd, 0);
    close(fd);
    if(str == MAP_FAILED)
    {
        perror("mmap()");
        exit(1);
    }
    for(int i = 0; i<statres.st_size;i++)
    {
        if(str[i]=='a')
        {
            count++;
        }
    }
    
    printf("%d\n", count);

    munmap(str, statres.st_size);



    exit(0);


}