/*
 * @Author: yuhang.liu
 * @Date: 2021-06-25 20:04:12
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-06-25 21:09:35
 * @Description: file content
 */
#include <iostream>
#include <string>
#include <deque>
#include <mutex>
#include <future>
#include <thread>
#include <utility>

using namespace std;

/* template <>
class packaged_task<std::string(std::vector<char> *, int)>
{
public:
    template <typename Callable>
    explicit packaged_task(Callable &&f);
    std::future<std::string> get_future();
    void operator()(std::vector<char> *, int);
}; */
int g_frameNum = 0;
mutex g_mt;
deque<packaged_task<void()>> tasks;
bool guiShutdownMessageReceived() {
    return true;
};
void getAndProcessGuiMessage() {
    cout << "gui process sucessed, frame id: " << ++g_frameNum << endl;
};

void guiThread() {
    while(!guiShutdownMessageReceived()) {
        getAndProcessGuiMessage();

        packaged_task<void()> task;
        {
            lock_guard<mutex> lk(g_mt);
            if(tasks.empty()) {
                continue;
                task = move(tasks.front());
                tasks.pop_front();
            }
            task();
        }
    }
}


template<typename Func>
future<void> postTaskForGuiThread(Func f) {
    packaged_task<void()> task(f);
    future<void> res = task.get_future();
    lock_guard<mutex> lk(g_mt);
    tasks.push_back(move(task));
    return res;
}


int main()
{
    //thread guiBgThread(guiThread);


    return 0;
}