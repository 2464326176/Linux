/*
 * @Author: yuhang.liu
 * @Date: 2021-06-25 11:40:41
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-01 09:15:48
 * @Description: file content
 */
#include <iostream>
#include <thread>
#include "wrap.h"

int wrap_hardware_concurrency()
{
    return std::thread::hardware_concurrency();
}

void myPrint() {
    std::cout << "myPrint start" << std::endl;
    //
    //other thing
    //

    std::cout << "myPrint end" << std::endl;
    return ;
}

void echo_print(const char* param)
{
    printf("%s\n", *param);
    return ;
}

