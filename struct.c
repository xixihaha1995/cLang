#include <stdlib.h>
#include <stdio.h>

// struct inside
// {
//     int inC;
// };

struct out
{
    int a;
    // struct inside anotherStruct;

};

static void example(int **x)
{
    printf("I got a number:%d from a double pointer\n", **x);
}

int main()
{
    // struct out outsider;
    // outsider = malloc(sizeof(*outsider));
    // outsider.a = 666;
    // printf("The num insider which inside out is: %d\n", outsider.a);
    int a = 666;
    int *aP = &a;
    // int **aPP = &(&(a));
    example(&aP);
    return 0;
}