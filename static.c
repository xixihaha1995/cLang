#include <stdio.h>
void foo()
{
    static int header;
    header +=5;
    printf("header:%d\n",header);
}

int main()
{
    for(int i = 0; i <5;i++)
        foo();
        
    return 0;
}