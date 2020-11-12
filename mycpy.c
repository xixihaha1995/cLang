#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *fps, *fpd;
    int ch;

    fps = fopen(argv[1], "r");
    if (fps == NULL){
        perror();
        exit(1);
    }
    fpd = fopen(argv[2], "w");
    if (fpd == NULL){
        perror("fopen");
        exit(1);
    }
    while(1)
    {
        ch = fgetc(fps);
        if (ch == EOF)
        {
            break;
        }
        fputc(ch, fpd);
    }
    fclose(fps);
    fclose(fpd);

    exit(0);
}