#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define RCVPORT     "1989"
#define NAMEMAX     512-8-8

struct msg_st
{
    u_int32_t math;
    u_int32_t chinese;
    u_int8_t name[1];
}__attribute__((packed));