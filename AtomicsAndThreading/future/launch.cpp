/*
 * @Author: yuhang.liu
 * @Date: 2021-07-08 07:11:08
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-13 00:04:22
 * @Description: file content
 */
#include <iostream>
#include <future>
#include <chrono>
#include <thread>

void print_ten(char c, int ms)
{
    std::cout << "thread id: " << std::this_thread::get_id() << " start";
    for (int i = 0; i < 10; ++i)
    {
        // std::cout << "thread id: " << std::this_thread::get_id() << " start";
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        std::cout << c << std::flush;
        // std::cout << "\nthread id: " << std::this_thread::get_id() << " end";
    }
}


int main()
{

    std::cout << "with launch::async: \n";
    std::future<void> foo = std::async(std::launch::async, print_ten, '*', 100);
    std::future<void> bar = std::async(std::launch::async, print_ten, '=', 200);

    foo.get();
    bar.get();

    std::cout << "\n-------------------------------------------\n";

    std::cout << "with launch::deferred";

    foo = std::async(std::launch::deferred, print_ten, '?', 100);
    bar = std::async(std::launch::deferred, print_ten, '~', 200);
    foo.get();
    bar.get();

    return 0;
}