#include <iostream>
#include <thread>


/*
(1) sleep()会使线程进入阻塞状态，yield()不会时线程进入阻塞态而是进入可运行态，
当线程重新获得CPU执行权后又可以执行。
(2) sleep()释放CPU后其他都可以竞争CPU的执行权，
而yield()只会让线程优先级大于等于自己的线程竞争CPU执行权的机会。
线程2先启动，当运行到thread1.join()时，线程2停止运行，等待线程1执行结束，
虽然线程1启动比线程2迟，但是只有当线程1运行结束后，线程2才能继续运行。
join()可以保证让一个线程在另一个线程之前执行结束。
如何保证一个工作在另一个工作结束之前完成，就可以使用join()方法。
wait()可以让线程从运行态转换为阻塞态，同时还会释放线程的同步锁。
*/

void hello()
{
    std::cout<<"Hello Concurrent World\n";
}

void do_something(int& i)
{
    ++i;
}

struct func
{
    int& i;

    func(int& i_):i(i_){}

    void operator()()
    {
        for(unsigned j=0;j<1000000;++j)
        {
            do_something(i);
        }
    }
};


void oops()
{
    int some_local_state=0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    std::cout<< some_local_state << std::endl;
    my_thread.detach();
}

int main()
{
    oops();
}

