/*
 * @Author: yuhang.liu
 * @Date: 2021-07-03 09:49:33
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-03 09:55:53
 * @Description: file content
 */
//********************
// Author:  yh
// Time:    2021/7/4.
//
//********************
//
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

int winner;

void set_winner(int x)
{
    winner = x;
}

std::once_flag winner_flag;

void wait_1000ms(int id)
{
    for (int i = 0; i < 1000; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    std::call_once(winner_flag, set_winner, id);
}

int main()
{
    std::thread threads[10];

    for (int i = 0; i < 10; ++i)
    {
        threads[i] = std::thread(wait_1000ms, i + 1);
    }

    std::cout << "wait 10000ms\n";

    for (std::thread &th : threads)
    {
        th.join();
    }

    std::cout << "winner thread " << winner << "\n";

    return 0;
}