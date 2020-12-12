#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static path_no_loop(const char *path)
{
    char *pos;
    pos = strrchr(path, '/');
    // strcmp(pos+1,".") == 0
    if (strcmp(pos+1, ".") == 0||strcmp(pos+1,"..")== 0 )
        return 0;
    return 1;
}

int main(int argc, char **argv)
{
    
    exit(0);
}