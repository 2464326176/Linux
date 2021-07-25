#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../common/wrapFun.h"

void catchSignal(const void *str)
{
    log2screen(str);
}

int main()
{
    __sighandler_t ret;

    ret = signal(SIGINT, catchSignal);
    if(ret == SIG_ERR) 
    {
        log2screen("注册信号失败！！！");
    }

    printf("开始生成信号");
    ret = raise(SIGINT);
    if( ret !=0 ) 
    {
        printf("错误：不能生成 SIGINT 信号。\n");
        exit(0);
    }

    printf("退出...\n");
    return(0);
}