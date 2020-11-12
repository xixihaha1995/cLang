#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *fps, *fpd;
    int ch;

    fps = fopen(argv[1], "r");
    fpd = fopen(argv[2], "w");

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