#include <stdio.h>

int main()
{
    char *arr = "hello";
    // char drr[] = "hello";
    // char crr[] = "hello";
    printf("arr:%p,%s,%c\n",arr,arr,*arr);
    printf("arr[0]:%p,%c\n",&arr[0],arr[0]);
    printf("arr+1:%p,%c\n",arr+1,*(arr+1));
}