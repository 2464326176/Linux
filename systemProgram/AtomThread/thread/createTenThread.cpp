/*
 * @Author: yuhang.liu
 * @Date: 2021-06-27 08:14:00
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-06-28 07:20:12
 * @Description: file content
 */
//
// Created by linux on 2021/6/27.
//
#include <iostream>
#include <vector>
#include <thread>
#include <list>

using namespace std;

void myPrint(const int &i) {
    cout << "thread id:" << this_thread::get_id() << "thread num:" << i << "start" << endl;
    ///
    ///
    ///
    cout << "thread id:" << this_thread::get_id() << "thread num:" << i << "endl" << endl;
}




class A {
public:
    void insertMsgQue() {
        
    }
private:
    list<string> m_msgRecvQueue;
};



int main() {
    vector<thread> Tthread;

    for(int i = 0; i < 10; ++i) {
        Tthread.push_back(thread(myPrint, i));
    }

    for(vector<thread>::iterator it = Tthread.begin(); 
            it != Tthread.end(); ++it) {
            it->join();                
    }
    
    return 0;
}



























