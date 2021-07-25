/*
 * @Author: your name
 * @Date: 2021-06-25 11:40:41
 * @LastEditTime: 2021-07-01 09:29:40
 * @LastEditors: yuhang.liu
 * @Description: In User Settings Edit
 */
#include <future>
#include <iostream>
#include <string>
using namespace std;

//带返回值的后台任务
int findAnswer()
{
    cout << "find the answer!!!" << endl;
    return 1;
}

void doOtherStuff()
{
    cout << "do other things" << endl;
}

struct X
{
    void foo(int, string const &) {
        cout << "foo function" << endl;
    };
    string bar(string const &str) {
        cout << "bar function" << endl;
        return str;
    };
};

struct Y
{
    double operator()(double fnum) {
        cout << "struct Y () 重载 fnum：" << fnum << endl;
        return fnum;
    };
};


class move_only
{
public:
    move_only() {
        cout << "构造函数" << endl;
    };
    move_only(move_only &&) {

    };
    move_only(move_only const &) = delete;
    move_only &operator=(move_only &&);
    move_only &operator=(move_only const &) = delete;
    void operator()() {
        cout << "()重载" << endl;
    };
};

int main()
{
    /* 1. 带返回值的后台任务
    future<int> theAnswer = async(findAnswer);
    doOtherStuff();
    cout << "the answer is " << theAnswer.get() << endl;
    */

/*     X x;
    auto f1 = async(&X::foo, &x, 42, "hello");
    auto f2 = async(&X::bar, &x, "good bye"); */

    
/*     Y y;
    auto f3 = async(Y(), 3.141);
    auto f4 = async(ref(y), 2.718); */

/*     X baz(X&);
    async(baz, ref(x)); */

/*     auto f5 = async(move_only()); // 调用tmp()，tmp是通过std::move(move_only())构造得到

    auto f6=std::async(std::launch::async,Y(),1.2);  // 在新线程上执行
    auto f7=std::async(std::launch::deferred,baz,std::ref(x));  // 在wait()或get()调用时执行
    auto f8=std::async(
                std::launch::deferred | std::launch::async,
                baz,std::ref(x));  // 实现选择执行方式
    auto f9=std::async(baz,std::ref(x));
    f7.wait();  //  调用延迟函数 */


    return 0;
}