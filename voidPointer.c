#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char *buf = "The\0wi";
    for(int i =0; i<7;i++)
        // printf("%c,",buf[i]);
        if(strncmp(&buf[i],"\0w",2) == 0)
            printf("parsed\n");
        else
        {
            printf("not parsed\n");
        }
        
        
    return 0;
}