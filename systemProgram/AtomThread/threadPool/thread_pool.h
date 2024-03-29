/*
 * @Author: yuhang.liu
 * @Date: 2021-07-21 00:35:28
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-07-28 01:46:17
 * @Description: file content
 */
#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_
#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
class ThreadPool {
public:
    using Task = std::function<void()>;
    explicit ThreadPool(int num) : _is_running(false), _thread_num(num) {}
    // disable copy and assign construct
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool &operator=(const ThreadPool &other) = delete;

    ~ThreadPool() {
        if (_is_running) {
            stop();
        }
    }

    void start() {
        _is_running = true;

        // start threads
        for (int i = 0; i < _thread_num; i++) {
            _threads.emplace_back(std::thread(&ThreadPool::work, this));
        }
    }

    void stop() {
        {
            // stop thread pool, should notify all threads to wake
            std::unique_lock<std::mutex> lk(_mtx);
            _is_running = false;
            _cond.notify_all(); // must do this to avoid thread block
        }

        // terminate every thread job
        for (std::thread &t : _threads) {
            if (t.joinable()) {
                t.join();
            }
        }
    }

    void appendTask(const Task &task) {
        if (_is_running) {
            std::unique_lock<std::mutex> lk(_mtx);
            _tasks.push(task);
            _cond.notify_one(); // wake a thread to to the task
        }
    }

private:
    void work() {
        std::cout << "begin work thread: " << std::this_thread::get_id()
                  << "\n";
        // every thread will compete to pick up task from the queue to do the
        // task
        while (_is_running) {
            Task task;
            {
                std::unique_lock<std::mutex> lk(_mtx);
                if (!_tasks.empty()) {
                    // if tasks not empty,
                    // must finish the task whether thread pool is running or
                    // not
                    task = _tasks.front();
                    _tasks.pop(); // remove the task
                } else if (_is_running && _tasks.empty())
                    _cond.wait(lk);
            }

            if (task) {
                task(); // do the task
            }
        }
        std::cout << "end work thread: " << std::this_thread::get_id() << "\n";
    }

private:
    std::atomic_bool _is_running; // thread pool manager status
    std::mutex _mtx;
    std::condition_variable _cond;
    int _thread_num;
    std::vector<std::thread> _threads;
    std::queue<Task> _tasks;
};

#endif // !_THREAD_POOL_H_