#include <iostream>
#include "wrap.h"

int wrap_hardware_concurrency()
{
    return std::thread::hardware_concurrency();

}

void echo_print(const char* param)
{
    printf("%s", *param);
}

