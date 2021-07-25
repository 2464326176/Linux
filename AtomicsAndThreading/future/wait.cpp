/*
 * @Author: yuhang.liu
 * @Date: 2021-07-08 09:46:29
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-08 10:07:58
 * @Description: file content
 */
#include <iostream>
#include <future>
#include <chrono>

bool is_prime(int x) {
    for (int i = 2; i < x; ++i) {
        if(x % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int num;
    
    std::future<bool> fut;
    while (true) {
        std::cout << "\nplrease input a num: \n"; 
        std::cin >> num;
        fut = std::async(is_prime, num);
        std::cout << "checking................... \n";

        fut.wait();

        std::cout << "\n num: " << num;
        if(fut.get()) {
            std::cout << " is prime num. \n";
        } else {
            std::cout << " is not prime num. \n";
        }
    }


    return 0;
}