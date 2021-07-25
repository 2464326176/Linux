/*
 * @Author: yuhang.liu
 * @Date: 2021-07-03 10:11:29
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-03 10:12:49
 * @Description: file content
 */
#include <iostream> // std::cout
#include <thread>   // std::thread
#include <mutex>    // std::mutex, std::lock

std::mutex foo, bar;

void task_a()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    // foo.lock(); bar.lock(); // replaced by:
    std::lock(foo, bar);
    std::cout << "task a\n";
    foo.unlock();
    bar.unlock();
}

void task_b()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    // bar.lock(); foo.lock(); // replaced by:
    std::lock(bar, foo);
    std::cout << "task b\n";
    bar.unlock();
    foo.unlock();
}

int main()
{
    std::thread th1(task_a);
    std::thread th2(task_b);

    th1.join();
    th2.join();

    return 0;
}