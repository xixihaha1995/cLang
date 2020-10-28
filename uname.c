#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/utsname.h>

int main()
{
    struct utsname buff;
    errno = 0;
    if(uname(&buff) != 0){
        
    }
}
