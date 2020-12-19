#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    puts("Begin");

    execl("/bin/date","date","+%s",NULL);
    perror("execl()");
    exit(1);

    puts("END!");
    exit(0);
}