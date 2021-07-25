/*
 * @Author: yuhang.liu
 * @Date: 2021-07-02 10:13:57
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-02 10:47:07
 * @Description: file content
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable produce, consume;

int cargo = 0;

void consumer() {
    std::unique_lock<std::mutex> lck(mtx);
    while(cargo == 0) {
        consume.wait(lck);
    }
    std::cout << "consume: " << cargo << ".....\n";
    cargo = 0;
    produce.notify_one();
}

void producer (int id) {
    std::unique_lock<std::mutex> lck(mtx);
    while(cargo != 0) {
        produce.wait(lck);
    }
    std::cout << "produce id: " << id << "produce ......" << "\n";
    cargo = id;
    consume.notify_one();
}

int main() {
    std::thread consumers[10], producers[10];

    for (int i = 0; i < 10; ++i) {
        consumers[i] = std::thread(consumer);
        producers[i] = std::thread(producer, i + 1);
    }

    for (int i=0; i<10; ++i) {
        producers[i].join();
        consumers[i].join();
    }

    return 0;
}