/*
 * @Author: yuhang.liu
 * @Date: 2021-07-01 09:36:39
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-01 09:54:20
 * @Description: file content
 */
// constructing threads
#include <iostream> // std::cout
#include <atomic>   // std::atomic
#include <thread>   // std::thread
#include <vector>   // std::vector
#include <chrono>
#include <mutex>          // std::mutex

std::mutex mtx;           // mutex for critical section
std::atomic<int> global_counter(0);

void increase_global(int n)
{
    for (int i = 0; i < n; ++i) {
        mtx.lock();
        ++global_counter;
        std::cout << "thread_id: " << std::this_thread::get_id() << "   global_counter: " << global_counter << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

}

void increase_reference(std::atomic<int> &variable, int n)
{
    for (int i = 0; i < n; ++i) {
        ++variable;
        std::cout << "thread_id: " << std::this_thread::get_id() << "   variable: " << variable << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

struct C : std::atomic<int>
{
    C() : std::atomic<int>(0) {}
    void increase_member(int n)
    {
        for (int i = 0; i < n; ++i)
            fetch_add(1);
    }
};

int main()
{

    std::vector<std::thread> threads;
    // std::cout << "increase global counter with 10 threads...\n";
    // for (int i = 1; i <= 10; ++i)
    //     threads.push_back(std::thread(increase_global, 1000));
        
    // std::cout << "increase counter (foo) with 10 threads using reference...\n";
    // std::atomic<int> foo(0);
    // for (int i = 1; i <= 10; ++i)
    //     threads.push_back(std::thread(increase_reference, std::ref(foo), 100));

    std::cout << "increase counter (bar) with 10 threads using member...\n";
    C bar;
    for (int i = 1; i <= 10; ++i)
        threads.push_back(std::thread(&C::increase_member, std::ref(bar), 1000));
    std::cout << "synchronizing all threads...\n";
    for (auto &th : threads)
        th.join();

    // std::cout << "global_counter: " << global_counter << '\n';
    // std::cout << "foo: " << foo << '\n';
    std::cout << "bar: " << bar << '\n';
    return 0;
}