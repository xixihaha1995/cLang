#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char **argv)
{
    void *handle;
    double (*cosine)(double);
    // the above function pointer, where input is double and outpur is also double
    char *error;
    handle = dlopen("libm.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    dlerror();
    *(void **)(&cosine)= dlsym(handle, "cos");
    // address of funciton pointer (&cosine) secondary pointer
    // (void **) force secondary pointer to a void secondary pointer
    // value of void secondary pointer is void first pointer
    exit(0);
}