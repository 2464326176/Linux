#include <iostream>
#include <thread>

using namespace std;

class A
{
public:
    A(int x) : m_id(x) {
        cout << "构造函数" << this << " thread id: " << this_thread::get_id() << endl;
    }
    A(const A& a) {
        m_id = a.m_id;
        cout << "拷贝构造函数" << this << " thread id: " << this_thread::get_id() << endl;
    }
    ~A() {
        cout << "析构函数" << this << " thread id: " << this_thread::get_id() << endl;
    } 

public:
    int m_id;
};

void fun(const A& b) {
	cout << b.m_id << endl;
	cout << "子线程  " << &b << "  Thread_id: " << this_thread::get_id() << endl;
}

int main()
{
	A a(10);
	//thread t(fun, a);
    thread t(fun, ref(a));
	t.join();
	return 0;
}