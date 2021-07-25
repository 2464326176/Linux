/*
 * @Author: yuhang.liu
 * @Date: 2021-07-17 14:17:40
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-07-25 23:54:33
 * @Description: file content
 */
#include "threadsafe_queue.h"
#include <atomic>
#include <functional>
#include <iostream>
#include <thread>

class thread_pool {
public:
    thread_pool() : done(false), joiner(threads) {
        unsigned const thread_count =
            /*std::thread::hardware_concurrency()*/ 4; // 8
        try {
            for (unsigned i = 0; i < thread_count; ++i) {
                threads.push_back(
                    std::thread(&thread_pool::worker_thread, this)); // 9
            }
        } catch (...) {
            done = true; // 10
            throw;
        }
    }

    ~thread_pool() {
        done = true; // 11
    }

    template <typename FunctionType> void submit(FunctionType f) {
        work_queue.push(std::function<void()>(f)); // 12
    }

    void worker_thread() {
        while (!done) // 4
        {
            std::function<void()> task;
            if (work_queue.try_pop(task)) // 5
            {
                task(); // 6
            } else {
                std::this_thread::yield(); // 7
            }
        }
    }
public:
    std::atomic_bool done;
    threadsafe_queue<std::function<void()>> work_queue; // 1
    std::vector<std::thread> threads;                   // 2
    join_threads joiner;                                // 3
};

void fun1() {
    std::cout << "working in thread " << std::this_thread::get_id()
              << std::endl;
}

void fun2(int x) {
    std::cout << "task " << x << " working in thread "
              << std::this_thread::get_id() << std::endl;
}

int main(int argc, char *argv[]) {
    thread_pool threadPool;

    for(int i = 0; i < 16; ++i) {
        threadPool.submit(std::bind(fun2, i));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    for(int i = 0; i < 16; ++i) {
        threadPool.submit(std::bind(fun1));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return 0;
}