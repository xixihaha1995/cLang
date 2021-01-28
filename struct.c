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

int main()
{
    struct out outsider;
    // outsider = malloc(sizeof(*outsider));
    outsider.a = 666;
    printf("The num insider which inside out is: %d\n", outsider.a);
    return 0;
}