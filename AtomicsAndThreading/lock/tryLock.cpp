/*
 * @Author: yuhang.liu
 * @Date: 2021-07-03 10:13:28
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-03 10:13:59
 * @Description: file content
 */
// std::lock example
#include <iostream> // std::cout
#include <thread>   // std::thread
#include <mutex>    // std::mutex, std::try_lock

std::mutex foo, bar;

void task_a()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    foo.lock();
    std::cout << "task a\n";
    bar.lock();
    // ...
    foo.unlock();
    bar.unlock();
}

void task_b()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    int x = try_lock(bar, foo);
    if (x == -1)
    {
        std::cout << "task b\n";
        // ...
        bar.unlock();
        foo.unlock();
    }
    else
    {
        std::cout << "[task b failed: mutex " << (x ? "foo" : "bar") << " locked]\n";
    }
}

int main()
{
    std::thread th1(task_a);
    std::thread th2(task_b);

    th1.join();
    th2.join();

    return 0;
}