#include <stdio.h>
#include <string.h>

int main()
{
    char str[] = "GETFILE GET /path/to/file\r\n\r\n";
    // char str[]= "hello world";
    char *token =NULL;
    char *saveptr;
    for(token = strtok_r(str," ",&saveptr); token; token = strtok_r(NULL," ",&saveptr))
    {
        printf("%s\n", token);
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