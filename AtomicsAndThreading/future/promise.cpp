/*
 * @Author: yuhang.liu
 * @Date: 2021-07-07 07:37:03
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-07 07:52:14
 * @Description: file content
 */
#include <iostream>
#include <thread>
#include <future>
#include <functional>

void print_int(std::future<int>& fut) {
    int x = fut.get();
    std::cout << "value: " << x << "\n"; 
}
int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    std::cout << "1111";

    std::thread th1(print_int, std::ref(fut));
    std::cout << "1111";
    prom.set_value(10);
    std::cout << "1111";

    th1.join();
    std::cout << "end";

    return 0;
}











