#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>


std::mutex g_mut;
std::queue<data_chunk> g_data_queue;
std::condition_variable g_data_cond;

void data_preparation_thread() {
    while(more_data_to_prepare) {
        data_chunk const data = prepare_data();
        std::lock_guard<std::mutex> lk(g_mut);
        g_data_queue.push(data);
        g_data_cond.notify_one();
    }

}

void data_processing_thread() {
    while(true) {
        std::unique_lock<std::mutex> lk(g_mut);
        g_data_cond.wait(
            lk, []{return !g_data_queue.empty();}
        );
        data_chunk data = g_data_queue.front();
        g_data_queue.pop();
        lk.unlock();
        process(data);
        if(is_last_chunk(data)) {
            break;
        }

    }
}


int main() {




    return 0;
}