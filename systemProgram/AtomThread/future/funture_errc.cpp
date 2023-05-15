/*
 * @Author: yuhang.liu
 * @Date: 2021-07-08 07:54:23
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-08 08:30:50
 * @Description: file content
 */
#include <iostream>
#include <future>

int main()
{
    std::promise<int> prom;

    try
    {
        prom.get_future();
        prom.get_future();
    }
    catch (std::future_error &e)
    {
        if (e.code() == std::make_error_code(std::future_errc::future_already_retrieved))
        {
            std::cerr << "[future already retrieved]\n";
        }
        else
        {
            std::cerr << "[unknown exception]\n";
        }
    }

    return 0;
}