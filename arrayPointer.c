#include <stdio.h>
#include<stdlib.h>

int main() {
    int arr[10];
    arr[0] = 0;

    int * arrPointer = (int *)malloc(10 * sizeof(int));
    arrPointer[9] = &20;
    printf("arrPointer[9] is %d\n", arrPointer[9]);
    return 0;


}