#include <iostream>
#include <thread>


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
    //oops();
    std::cout << "1";
    return 0;
}

