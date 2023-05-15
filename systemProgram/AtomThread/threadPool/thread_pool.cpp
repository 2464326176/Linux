/*
 * @Author: yuhang.liu
 * @Date: 2021-07-17 14:20:36
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-07-28 01:47:29
 * @Description: file content
 */
#include "thread_pool.h"
#include <chrono>
#include <iostream>

void fun1()
{
	std::cout << "working in thread " << std::this_thread::get_id() << "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

}

void fun2(int x)
{
	std::cout << "task " << x << " working in thread " << std::this_thread::get_id() << "\n";
}

int main(int argc, char* argv[])
{
	ThreadPool thread_pool(3);
	thread_pool.start();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	for (int i = 0; i < 6; i++)
	{
		//thread_pool.appendTask(fun1);
		thread_pool.appendTask(std::bind(fun2, i));
	}

	thread_pool.stop();
	std::cout << "" << std::endl;
	return 0;
}