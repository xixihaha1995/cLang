#include <stdio.h>
#include <string.h>

int main()
{
    char str[] = "GETFILE GET /path/to/file\r\n\r\n";
    char *token[3];
    char *saveptr;
    int i = 0;
    for(token[i] = strtok_r(str," ",&saveptr); token[i] != NULL; token[++i] = strtok_r(NULL," ",&saveptr))
    {
        printf("token[%d]: %s\n", i,token[i]);
    }
    return 0;
}

// #include <stdio.h>
// #include <string.h>    

// int main(void)
// {
//     char hello[] = "GETFILE GET /path/to/file\r\n\r\n";

//     char *tmp;
//     char *token = NULL;
//     for(token = strtok_r(hello, ", ", &tmp); token != NULL; token = strtok_r(NULL, ", ", &tmp))
//     {
//         printf("%s\n", token);
//     }

//     return 0;
// }