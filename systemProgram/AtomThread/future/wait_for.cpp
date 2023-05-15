/*
 * @Author: yuhang.liu
 * @Date: 2021-07-08 10:08:55
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-08 10:47:47
 * @Description: file content
 */
#include <chrono>
#include <future>
#include <iostream>

bool is_prime(int x) {
    for (int i = 2; i < x; ++i) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    std::future<bool> fut = std::async(is_prime, 700020007);

    std::cout << "checking, please wait";
    std::chrono::milliseconds span(100);
    while (fut.wait_for(span) != std::future_status::ready) {
        std::cout << '.' << std::flush;
    }

    bool x = fut.get();

    std::cout << "\n700020007 " << (x ? "is" : "is not") << " prime.\n";

    return 0;
}