#include <stdio.h>
#include <string.h>

int main()
{
    char strOld[] = "GETFILE GET /path/to\r\n\r\n I love you";
    char *str =NULL;
    char *token[5];
    char *saveptr = NULL;
    str = strtok_r(strOld,"\r\n\r\n",&saveptr);
    saveptr = NULL;

    int i = 0;
    for(token[i] = strtok_r(str," ",&saveptr); ; token[++i] = strtok_r(NULL," ",&saveptr))
    {
        if (token[i] == NULL)
            break;
         printf("token[%d]: %s\n", i,token[i]);
    }
    printf("%d\n", i);
    if(i == 3 && strcmp(token[0],"GETFILE") == 0 && strcmp(token[1],"GET") ==0  && token[2][0]=='/' )
    {
        printf("token[%d]: %c\n", 2,token[2][0]);
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