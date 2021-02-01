#include <stdio.h>
#include <string.h>

int main()
{
    char strOld[] = "GET\r\n\r\nI\0love you";
    char *str =NULL;
    char *token[5];
    char *saveptrOne= NULL;
    str = strtok_r(strOld,"\r\n\r\n",&saveptrOne);
    printf("strOld is:%s; and its strlen is:%d; sizeof is:%d\n", strOld,strlen(strOld), sizeof(strOld));
    str = strtok_r(NULL, "\r\n\r\n",&saveptrOne);
    printf("str is:%s; and its strlen is:%d; sizeof is:%d\n", str,strlen(str), sizeof(str));


    // printf("str is:%s; and its strlen is:%d; sizeof is:%d\n", str,strlen(str), sizeof(str));
    // printf("saveptrOne is:%s; and its strlen is:%d; sizeof is:%d\n", saveptrOne,strlen(saveptrOne), sizeof(saveptrOne));
    // char *saveptr = NULL;

    // int i = 0;
    // for(token[i] = strtok_r(saveptrOne,"\r\n\r\n",&saveptr); ; token[++i] = strtok_r(NULL,"\r\n\r\n",&saveptr))
    // {
    //     if (token[i] == NULL)
    //         break;
    //      printf("token[%d]:%s; And its strlen:%zu; its sizeof:%zu\n", i,token[i], strlen(token[i]), sizeof(token[i]));
    // }
    // printf("%d\n", i);
    // if(i == 3 && strcmp(token[0],"GETFILE") == 0 && strcmp(token[1],"GET") ==0  && token[2][0]=='/' )
    // {
    //     printf("token[%d]: %c\n", 2,token[2][0]);
    // }

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