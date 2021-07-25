#include <wrapFun.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void log2screen(const void *str)
{
    perror(str);
    exit(-1);
}