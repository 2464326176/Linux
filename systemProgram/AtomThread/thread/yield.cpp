/*
 * @Author: yuhang.liu
 * @Date: 2021-07-11 04:48:16
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-11 05:10:22
 * @Description: file content
 */
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<bool> ready(false);


//wait until main() sets raedy
void count1m(int id) {
    while(!ready) {
        std::this_thread::yield();
    }
    for (volatile int i = 0; i < 1000000; ++i) {}

    std::cout << "threads id: " << id << "\n";
}

int main() {
    std::thread threads[10];
    std::cout << "race of 10 threads that count to 1 million: \n";
    for (int i =0; i < 10; ++i) {
        threads[i] = std::thread(count1m, i);
    }

    ready = true;

    for (auto& th : threads) {
        th.join();
    }

    std::cout << "end\n";
    return 0;
}