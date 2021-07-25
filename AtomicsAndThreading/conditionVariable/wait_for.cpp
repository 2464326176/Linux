/*
 * @Author: yuhang.liu
 * @Date: 2021-07-03 11:01:38
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-03 11:11:01
 * @Description: file content
 */
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

std::condition_variable cv;
int value;

void read_value() {
    std::cin >> value;
    cv.notify_one();
}

int main() {
    std::cout << "please enter integer (this funtion will printing dots)\n";

    std::thread th(read_value);
    std::mutex mtx;
    std::unique_lock<std::mutex> lck(mtx);
    
    while(cv.wait_for(lck, std::chrono::seconds(1)) == std::cv_status::timeout) {
        std::cout << "." << std::flush;
        
    }

    std::cout << "you enered: " << value << "\n";

    th.join();

    return 0;
}