#include <stdio.h>
#include<stdlib.h>

int main() {
    int arr[10];
    arr[0] = 0;

    int oldSize = 5;
    int * arrPointer = (int *)malloc(oldSize * sizeof(int));
    if (arrPointer == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    else
    {
        printf("Memory allocated successfully with malloc\n");
        for (int i = 0; i < oldSize; ++i) {
            arrPointer[i] = i + 1;
        printf("The elements for the arrPointer is: \n");
        for(i =0; i < oldSize; i++) {
            printf(" %d", arrPointer[i]);
        }
        printf("\n\nI'll resize the array of arrPointer\n");
        oldSize = 6;
        printf("Re-allocated via realloc, and the new size is %d\n", oldSize);
        arrPointer = realloc(arrPointer, oldSize*sizeof(int));
        for(i = 0; i< oldSize; i++) {
            arrPointer[i] = i+6;
        }
        printf("New elements are:\n");
        for(i =0; i < oldSize; i++) {
            printf(" %d", arrPointer[i]);
        }
    }
    }
    
    
    // printf("arrPointer[9] is %d\n", arrPointer[9]);
    
    return 0;


}