#include "mytbf.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define     CPS 10
#define     BUFSIZE 1024
#define     BURST   100

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage ...\n" );
        exit(1);
    }
    mytbf_t *tbf;
    mytbf_init();
    return 0;
}