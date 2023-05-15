/*
 * @Author: yuhang.liu
 * @Date: 2021-07-13 00:20:36
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-13 01:05:31
 * @Description: file content
 */
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>
using namespace std;



typedef struct _TICKET {
    int nCount;
    string strTicketName;

    _TICKET() : nCount(0) {
        
    } 
}TICKET;

typedef struct _THD_DATA{
    TICKET* pTicket;
    string strThreadName;
    _THD_DATA() : pTicket(nullptr) {

    }
}THD_DATA;

