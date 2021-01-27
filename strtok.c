#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char *str= "GETFILE GET /path/to/file\r\n\r\n";
    char *token;
    char *saveptr;
    for(token = strtok_r(str," ",&saveptr); token != NULL; token = strtok_r(NULL," ",&saveptr))
    {
        printf("%s\n", token);
    }
    return 0;
}