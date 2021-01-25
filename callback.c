#include <stdio.h>

void caller(int (*cb)(int formalA, int formarlB), int realA, int realB)
{
    cb(realA, realB);
}

int myCB(int a, int b)
{
    printf("this call have %d and %d\n", a, b);
    return 0;
}

int main()
{
    caller(myCB, 6,250);
    return 0;
}