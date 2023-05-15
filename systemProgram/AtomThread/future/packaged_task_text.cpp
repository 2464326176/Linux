//********************
// Author:  yh 
// Time:    2021/6/26.
// 
//********************
//

// packaged_task::get_future
#include <iostream>     // std::cout
#include <utility>      // std::move
#include <future>       // std::packaged_task, std::future
#include <thread>       // std::thread

// function that launches an int(int) packaged_task in a new thread:
std::future<int> launcher (std::packaged_task<int(int)>& tsk, int arg) {
    if (tsk.valid()) {
        std::future<int> ret = tsk.get_future();
        std::thread (std::move(tsk),arg).detach();
        return ret;
    }
    else return std::future<int>();
}

int main ()
{
    std::packaged_task<int(int)> tsk ([](int x){return x*2;});

    std::future<int> fut = launcher (tsk,25);

    std::cout << "The double of 25 is " << fut.get() << ".\n";

    return 0;
}


int main1() {
    std::packaged_task<void()> task; // 缺省构造、默认构造
    std::cout << std::boolalpha << task.valid() << std::endl; // false

    std::packaged_task<void()> task2(std::move(task)); // 右值构造
    std::cout << std::boolalpha << task.valid() << std::endl; // false

//    task = std::packaged_task<void()>([](){});  // 右值赋值, 可调用对象
//    std::cout << std::boolalpha << task.valid() << std::endl; // true

    return 0;
}