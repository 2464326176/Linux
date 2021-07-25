/*
 * @Author: yuhang.liu
 * @Date: 2021-06-27 02:53:10
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-01 09:21:51
 * @Description: file content
 */
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;


void foo()
{
    cout << "foo thread_id: " << this_thread::get_id() << " start" << endl;
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "foo thread_id: " << this_thread::get_id() << " end" << endl;
}

void bar()
{   
    cout << "bar thread_id: " << this_thread::get_id() << " start" << endl;
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "bar thread_id: " << this_thread::get_id() << " end" << endl;
}

int main()
{
    std::cout << "starting first helper...\n";
    std::thread helper1(foo);

    std::cout << "starting second helper...\n";
    std::thread helper2(bar);

    std::cout << "waiting for helpers to finish..." << std::endl;
    helper1.join();
    helper2.join();

    std::cout << "done!\n";
    return 0;
}