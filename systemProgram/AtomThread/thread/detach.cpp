/*
 * @Author: yuhang.liu
 * @Date: 2021-07-11 11:54:00
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-11 11:55:54
 * @Description: file content
 */
#include <chrono>
#include <iostream>
#include <thread>

void pause_thread(int n) {
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << "pause of " << n << " seconds ended\n";
}

int main() {
    std::cout << "Spawning and detaching 3 threads...\n";
    std::thread(pause_thread, 1).detach();
    std::thread(pause_thread, 2).detach();
    std::thread(pause_thread, 3).detach();
    std::cout << "Done spawning threads.\n";

    std::cout << "(the main thread will now pause for 5 seconds)\n";

    // give the detached threads time to finish (but not guaranteed!):
    pause_thread(5);
    return 0;
}