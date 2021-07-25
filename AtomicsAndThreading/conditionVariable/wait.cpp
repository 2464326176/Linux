/*
 * @Author: yuhang.liu
 * @Date: 2021-07-03 11:22:30
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-03 11:32:22
 * @Description: file content
 */
#include <iostream>           // std::cout
#include <thread>             // std::thread, std::this_thread::yield
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

std::mutex mtx;
std::condition_variable cv;

int cargo = 0;
bool shipment_available()
{
    std::cout << "shipment_available cargo: " << cargo << "\n";
    return cargo != 0;
}

void consume(int n)
{
    for (int i = 0; i < n; ++i)
    {
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, shipment_available);
        // consume:
        std::cout << cargo << '\n';
        cargo = 0;
    }
}

int main()
{
    std::thread consumer_thread(consume, 10);

    // produce 10 items when needed:
    for (int i = 0; i < 10; ++i)
    {
        while (shipment_available())
        {
            std::this_thread::yield();
        }
        std::unique_lock<std::mutex> lck(mtx);
        cargo = i + 1;
        cv.notify_one();
    }

    consumer_thread.join();

    return 0;
}