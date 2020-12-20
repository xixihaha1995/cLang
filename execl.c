#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    puts("Begin");
    fflush(NULL);

    execl("/bin/date","date","+%s",NULL);
    perror("execl()");
    exit(1);

    puts("END!");
    exit(0);
}