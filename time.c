#include <stdio.h>
#include <time.h>

void func_name()
{
    printf("Function starts\n");
    printf("Press any key to stop\n");
    for(;;)
    {
        if(getchar())
            break;
    }
    printf("Function ends\n");
}

int main()
{
    clock_t t;
    t = clock();
    func_name();
    t = clock() - t;
    double time_elapsed = ((double) t) / CLOCKS_PER_SEC;

    printf("The processing time of function is: %f", time_elapsed);

    return 0;
}