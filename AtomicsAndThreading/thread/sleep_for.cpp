/*
 * @Author: yuhang.liu
 * @Date: 2021-07-11 11:31:55
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-12 23:37:06
 * @Description: file content
 */
#include <chrono>
#include <iostream>
#include <thread>

int main() {
    std::cout << "countdown:\n";
    for (int i = 10; i > 0; --i) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Lift off!\n";

    return 0;
}