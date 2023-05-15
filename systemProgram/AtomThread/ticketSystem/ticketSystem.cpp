/*
 * @Author: yuhang.liu
 * @Date: 2021-07-13 00:17:07
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-13 01:14:05
 * @Description: file content
 */

#include "ticketSystem.h"

#define NTHREAD 10

mutex mtx;

void SaleTicket(THD_DATA tmpTicketData) {
    while (tmpTicketData.pTicket->nCount > 0) {
        mtx.lock();
        tmpTicketData.pTicket->nCount--;
        if (tmpTicketData.pTicket->nCount > 0) {
            cout << "thread_id: " << this_thread::get_id() << " ["
                 << tmpTicketData.strThreadName << "] sale \""
                 << tmpTicketData.pTicket->strTicketName
                 << "\" number of tickets remaining: "
                 << tmpTicketData.pTicket->nCount << "\n";
        } else {
            cout << "sale end\n";
        }
        mtx.unlock();

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int main() {

    TICKET ticket;
    ticket.nCount = 200;
    ticket.strTicketName = "深圳-->河南";

    THD_DATA threadSale[NTHREAD];
    thread threads[NTHREAD];
    for (int i = 0; i < NTHREAD; ++i) {
        threadSale[i].pTicket = &ticket;
        threadSale[i].strThreadName = "window " + to_string(i);
        threads[i] = thread(SaleTicket, ref(threadSale[i]));
    }

    cout << "start join thread.....\n";

    for (auto &th : threads) {
        th.join();
    }

    return 0;
}