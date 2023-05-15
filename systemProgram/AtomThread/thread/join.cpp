/*
 * @Author: yuhang.liu
 * @Date: 2021-07-11 11:58:13
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-11 12:13:46
 * @Description: file content
 */
#include <chrono>
#include <iostream>
#include <thread>

void print_(int n) {
    for (volatile int i = 0; i < n; ++i) {
        std::cout << "thread id:" << std::this_thread::get_id() << "n:" << n << " i:" << i << "\n";; 
    }
}
void pause_thread(int n) {
    print_(n);
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << "pause of " << n << " seconds ended\n";
}

int main() {
    std::cout << "main thread start" << std::endl;

    std::cout << "Spawning 3 threads...\n";
    std::thread t1(pause_thread, 1);
    std::thread t2(pause_thread, 2);
    std::thread t3(pause_thread, 3);
    

    std::thread t4(pause_thread, 4);
    std::thread t5(pause_thread, 5);
    std::thread t6(pause_thread, 6);
    t4.detach();
    t5.detach();
    t6.detach();

    std::cout << "Done spawning threads. Now waiting for them to join:\n";
    t1.join();
    t2.join();
    t3.join();

    std::cout << "main thread end" << std::endl;
    std::cout << "All threads joined!\n";
    pause_thread(10);
    return 0;
}