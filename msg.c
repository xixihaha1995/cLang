#include <stdio.h>
#include <string.h>

int main()
{
    char buf[630];
    strcat(buf,"GETFILE ");
    strcat(buf,"GF_OK");
    // Line Feed(LF)
    // strcat(buf,"\r");

    // Carriage Return(CR)
    strcat(buf,"\n");

    // End of Line(CRLF)
    // strcat(buf,"\r\n");

    strcat(buf,"TEST");

    // TESTILE GF_OK

    // GETFILE GF_OK
    // TEST

    // GETFILE GF_OK
    // TEST

    // sprintf(buf,"%s ","GETFILE");
    // sprintf(buf,"%s ","GF_OK");
    // // sprintf(buf)
    printf("%s\n", buf);
    return 0;
}